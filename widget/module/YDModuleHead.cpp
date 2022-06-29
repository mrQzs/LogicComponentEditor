#include "YDModuleHead.h"

#include <QDateTime>
#include <QPainter>

#include "common/YDHelper.h"
#include "model/YDModulePropModel.h"
#include "modules/YDModule.h"

YDModuleHead::YDModuleHead(YDModule *m, QWidget *parent)
    : QWidget(parent),
      m_module{m},
      m_arrow1{QPixmap(":/Icon/arrow_up.png")},
      m_arrow2{QPixmap(":/Icon/arrow_down.png")},
      m_isHaveChild(true),
      m_isPreessed(false) {
  setFixedHeight(28);
}

YDModuleHead::~YDModuleHead() {}

void YDModuleHead::setIcon(const QString &str) {
  m_icon = str;
  m_iconp = QPixmap(m_icon).scaled(QSize(20, 20), Qt::IgnoreAspectRatio,
                                   Qt::SmoothTransformation);
}

void YDModuleHead::setText(const QString &text) { m_text = text; }

void YDModuleHead::setBgColor(const QString &str) { m_bgColor = QColor(str); }

void YDModuleHead::setFtColor(const QString &str) { m_ftColor = QColor(str); }

void YDModuleHead::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.setBrush(m_bgColor);
  p.setPen(Qt::NoPen);
  p.drawRect(rect());

  auto W = width();
  auto H = height();
  p.save();
  QPen pen(Qt::black);
  pen.setWidthF(1.4);
  p.setPen(pen);
  p.drawLine(0, 0, W, 0);
  p.restore();

  int x = 0, y = 0, w = 0, h = 0;

  w = m_arrow1.width() * 0.6;
  h = m_arrow1.height() * 0.6;
  x = 5;
  y = (H - h) / 2;
  if (m_isPreessed)
    p.drawPixmap(x, y, w, h, m_arrow1);
  else
    p.drawPixmap(x, y, w, h, m_arrow2);

  if (!m_icon.isEmpty()) {
    x = x + w + 20;
    w = m_iconp.width();
    h = m_iconp.height();
    y = (H - h) / 2;
    p.drawPixmap(x, y, w, h, m_iconp);
  }

  QFont font;
  font.setPixelSize(14);
  if (!m_text.isEmpty()) {
    p.setPen(m_ftColor);
    p.setFont(font);
    x = x + w + 10;
    auto m = p.fontMetrics();
    h = m.height();
    w = m.horizontalAdvance(m_text);
    y = (H - h) / 2;

    p.drawText(x, y, w, h, Qt::AlignCenter, m_text);
  }

  p.setPen(QPen(Qt::red));
  if (m_module == selectModule) {
    auto str = YDModuleHead::tr("(已选中)");
    x = x + w + 15;
    auto m = p.fontMetrics();
    w = m.horizontalAdvance(str);
    p.drawText(x, y, w, h, Qt::AlignCenter, str);
  }

  if (YDHelper::isDebugMode()) {
    QString strState = getStateInfo();
    p.setFont(font);
    p.setPen(QPen(m_ftColor));
    auto m = p.fontMetrics();
    w = m.horizontalAdvance(strState);
    h = m.height();
    x = width() - w - 50;

    p.drawText(x, y, w, h, Qt::AlignLeft, strState);

    QString m_text1 = "状态:";
    x = width() - w - 50 - 20 - m.horizontalAdvance(m_text1);
    w = m.horizontalAdvance(m_text1);
    p.drawText(x, y, w, h, Qt::AlignLeft, m_text1);
  }

  p.end();
}

void YDModuleHead::mouseReleaseEvent(QMouseEvent *) {
  m_isPreessed = !m_isPreessed;
  emit sigClicked(m_isPreessed);
  selectModule = m_module;
  YDHelper::getModPropModel()->setModule(m_module);
  update();
}

QString YDModuleHead::getStateInfo() {
  yd::proto::ProcState state = m_module->getDebugState();
  QString strState = YDModuleHead::tr("未知");
  QString startTime{""}, endTime{""};

  if (state.begin > 0 && state.end > 0 && YDHelper::getTestStart()) {
    startTime = STRTQSTR(
        yd::CTimestamp::FormatTimeFromMicroseconds(state.begin).c_str());
    endTime =
        STRTQSTR(yd::CTimestamp::FormatTimeFromMicroseconds(state.end).c_str());
  }

  switch (state.state) {
    case LOGIC_TASK_STATE_INVALID:
      strState = YDModuleHead::tr("不可用");
      break;
    case LOGIC_TASK_STATE_READY:
      strState = YDModuleHead::tr("已就绪");
      break;
    case LOGIC_TASK_STATE_IN_PROCESSING:
      strState = YDModuleHead::tr("运行中");
      break;
    case LOGIC_TASK_STATE_COMPLETED:
      strState = YDModuleHead::tr("已完成");
      break;
    case LOGIC_TASK_STATE_FAILED:
      strState = YDModuleHead::tr("已失败");
      break;
  }
  return strState.append(" 起始: " + startTime + " 结束: " + endTime);
}
