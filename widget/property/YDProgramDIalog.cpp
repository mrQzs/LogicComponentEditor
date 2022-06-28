#include "YDProgramDIalog.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "modules/YDModule.h"
#include "widget/YDCodeEditor.h"

YDProgramDIalog::YDProgramDIalog(YDModule *m, QWidget *parent)
    : YDDialog{parent},
      m_btn{new QPushButton(this)},
      m_module{m},
      m_widget{new YDCodeEditor(this)},
      m_isSaved{false},
      m_isCompile{false} {
  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  setStyleSheet("QDialog#YDProgramDIalog{background:#ffffff;}");
  m_btn->setStyleSheet("border:none");

  m_btn->setIcon(QIcon(":/Icon/close.png"));
  m_btn->setIconSize(QSize(20, 20));

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_btn);

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(0, 0, 0, 0);
  vlay->addSpacing(0);
  vlay->addLayout(hlay);
  vlay->addWidget(m_widget);

  auto name = QSTRTSTR(m_module->name());
  auto type = m_module->getCodeType() + SCRIPT_TYPE_VB_NET;
  auto file = YDProjectManage::getProgrammableProcessCodeFilePath(name, type);
  auto filestr = QString::fromLocal8Bit(file.c_str());
  auto code = YDHelper::readFile(filestr);
  if (code.isEmpty()) {
    if (type == SCRIPT_TYPE_VB_NET)
      code = YDProjectManage::getVbCode();
    else
      code = YDProjectManage::getVcCode();
    QString str = QString("YDTemplate_%1").arg(m->getLogicProcessId());
    code.replace("YDTemplate", str);
  }

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

bool YDProgramDIalog::isSaved() { return m_isSaved; }

void YDProgramDIalog::slotSaveClicked() {
  m_isSaved = true;
  auto name = QSTRTSTR(m_module->name());
  auto type = m_module->getCodeType() + SCRIPT_TYPE_VB_NET;
  auto code = m_widget->getText();
  auto file = YDProjectManage::getProgrammableProcessCodeFilePath(name, type);
  auto filestr = QString::fromLocal8Bit(file.c_str());

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
  auto ret = QString::fromLocal8Bit(result.c_str());
  emit sigResult(ret);
}

void YDProgramDIalog::slotClose(bool) {
  if (!m_isSaved) {
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
