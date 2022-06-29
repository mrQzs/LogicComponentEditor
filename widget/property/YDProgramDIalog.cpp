#include "YDProgramDIalog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "modules/YDModule.h"
#include "widget/YDCodeEditor.h"

YDProgramDIalog::YDProgramDIalog(YDModule *m, QWidget *parent)
    : YDDialog{parent},
      m_titleLabel{new QLabel(this)},
      m_btn{new QPushButton(this)},
      m_module{m},
      m_widget{new YDCodeEditor(this)},
      m_isCompile{false},
      m_clicked{false} {
  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  setStyleSheet("QDialog#YDProgramDIalog{background:#ffffff;}");

  QString titleName = m_module->name();
  switch (m_module->getCodeType() + SCRIPT_TYPE_VB_NET) {
    case SCRIPT_TYPE_VB_NET:
      titleName.append(" - VB.NET");
      break;
    case SCRIPT_TYPE_CSHARP_NET:
      titleName.append(" - C#.NET");
      break;
    default:
      break;
  }
  m_titleLabel->setText(titleName);
  m_btn->setStyleSheet("border:none");
  m_btn->setIcon(QIcon(":/Icon/x.png"));
  m_btn->setIconSize(QSize(20, 20));

  auto hlay = new QHBoxLayout;
  hlay->setContentsMargins(5, 5, 5, 0);
  hlay->addWidget(m_titleLabel);
  hlay->addStretch();
  hlay->addWidget(m_btn);

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(5, 5, 5, 5);
  vlay->addSpacing(0);
  vlay->addLayout(hlay);
  vlay->addWidget(m_widget);

  auto name = QSTRTSTR(m_module->name());
  auto type = m_module->getCodeType() + SCRIPT_TYPE_VB_NET;
  auto file = YDProjectManage::getProgrammableProcessCodeFilePath(name, type);
  auto filestr = STRTQSTR(file.c_str());
  auto code = YDHelper::readFile(filestr);
  if (code.isEmpty()) {
    if (type == SCRIPT_TYPE_VB_NET)
      code = YDProjectManage::getVbCode();
    else
      code = YDProjectManage::getVcCode();
    QString str = QString("YDTemplate_%1").arg(m->getLogicProcessId());
    code.replace("YDTemplate", str);
  }
  m_code = code;
  m_widget->setText(code);
  connect(m_widget, &YDCodeEditor::sigSave, this,
          &YDProgramDIalog::slotSaveClicked);

  connect(m_widget, &YDCodeEditor::sigCompile, this,
          &YDProgramDIalog::slotCompileClicked);

  connect(this, &YDProgramDIalog::sigResult, m_widget,
          &YDCodeEditor::slotResult);

  connect(m_btn, &QPushButton::clicked, this, &YDProgramDIalog::slotClose);
}

QStringList YDProgramDIalog::textList() const {
  QStringList list;

  if (m_widget->getText().isEmpty())
    list << YDProgramDIalog::tr("无代码");
  else {
    if (!m_isCompile)
      list << YDProgramDIalog::tr("待检查");
    else
      list << YDProgramDIalog::tr("已编译");
  }

  return list;
}

void YDProgramDIalog::setTextList(const QStringList &) {}

void YDProgramDIalog::setType(int type) {
  QString str;
  if (0 == type)
    str = "VB.Net";
  else
    str = "C#.Net";
  QString name = QString("%1 - %2").arg(m_module->name(), str);
  setWindowTitle(name);
  m_widget->changeType(type);
}

void YDProgramDIalog::mousePressEvent(QMouseEvent *e) {
  if (e->button() & Qt::LeftButton && e->pos().y() < 40) {
    m_curPos = e->globalPosition().toPoint() - frameGeometry().topLeft();
    m_clicked = true;
  }
  QDialog::mousePressEvent(e);
}

void YDProgramDIalog::mouseMoveEvent(QMouseEvent *e) {
  if (e->buttons() & Qt::LeftButton && m_clicked) {
    move(e->globalPosition().toPoint() - m_curPos);
  }

  QDialog::mouseMoveEvent(e);
}

void YDProgramDIalog::mouseReleaseEvent(QMouseEvent *e) { m_clicked = false; }

void YDProgramDIalog::paintEvent(QPaintEvent *event) {
  QPainterPath path;
  path.setFillRule(Qt::WindingFill);
  path.addRect(5, 5, this->width() - 10, this->height() - 10);

  QColor bgcolor{0xF0, 0xF0, 0xF0};
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.fillPath(path, QBrush(bgcolor));

  int r = bgcolor.red() - 100;
  int g = bgcolor.green() - 100;
  int b = bgcolor.blue() - 100;
  r = r < 0 ? 0 : r;
  g = g < 0 ? 0 : g;
  b = b < 0 ? 0 : b;
  QColor shadowcolor(r, g, b, 50);
  for (int i = 0; i < 5; i++) {
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(5 - i, 5 - i, this->width() - (5 - i) * 2,
                 this->height() - (5 - i) * 2);
    shadowcolor.setAlpha(150 - sqrt(i) * 50);
    painter.setPen(shadowcolor);
    painter.drawPath(path);
  }
}

void YDProgramDIalog::slotSaveClicked() {
  auto name = QSTRTSTR(m_module->name());
  auto type = m_module->getCodeType() + SCRIPT_TYPE_VB_NET;
  auto code = m_widget->getText();
  auto file = YDProjectManage::getProgrammableProcessCodeFilePath(name, type);
  auto filestr = STRTQSTR(file.c_str());
  m_code = code;
  YDHelper::writeFile(filestr, code);
}

void YDProgramDIalog::slotCompileClicked() {
  m_isCompile = true;
  auto name = QSTRTSTR(m_module->name());
  auto type = m_module->getCodeType() + SCRIPT_TYPE_VB_NET;
  auto cpu = TARGET_CPU_X64 - m_widget->getBuildCpu();
  std::vector<std::string> fram;
  YDProjectManage::enumFrameworks(cpu, fram);
  int findex = m_widget->getBuildFram();
  auto str = YDHelper::getAvaliableFram(fram)[findex];
  auto framstr = QSTRTSTR(str);
  std::string result;
  YDProjectManage::compileProgrammableProcess(name, type, framstr, cpu, result);
  auto ret = STRTQSTR(result.c_str());
  emit sigResult(ret);
}

void YDProgramDIalog::slotClose(bool) {
  if (m_code != m_widget->getText()) {
    auto rt = QMessageBox::information(
        nullptr, YDProgramDIalog::tr("提示"),
        YDProgramDIalog::tr("代码未保存,是否保存?"), YDProgramDIalog::tr("是"),
        YDProgramDIalog::tr("否"));
    if (0 == rt) {
      slotSaveClicked();
    }
  }

  accept();
}
