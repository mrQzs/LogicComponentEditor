#include "YDModuleWidget.h"

#include <QDateTime>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

#include "common/YDHelper.h"
#include "debug/YDDgHelper.h"
#include "model/YDModulePropModel.h"
#include "modules/YDModule.h"

YDModuleWidget::YDModuleWidget(YDModule *m, const QColor &bgColor,
                               const QColor &fontColor, QWidget *parent)
    : QWidget{parent},
      m_color{bgColor},
      m_fontColor{fontColor},
      m_module{m},
      m_text1{YDModuleWidget::tr("状态:")} {
  m_pix = QPixmap(m_module->icon())
              .scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

YDModuleWidget::~YDModuleWidget() {}

void YDModuleWidget::setText(const QString &text) { m_text = text; }

void YDModuleWidget::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.save();
  p.setBrush(QBrush(m_color));
  p.drawRect(rect());
  p.restore();

  p.save();
  p.setPen(QPen(m_fontColor));
  QFont font;
  font.setPixelSize(14);
  p.setFont(font);
  auto m = p.fontMetrics();
  auto h = m.height();
  auto w = m.horizontalAdvance(m_text);
  auto x = 30;
  auto y = (height() - h) / 2;

  p.drawPixmap(5, 4, 16, 16, m_pix);
  p.drawText(x, y, w, h, Qt::AlignLeft, m_text);

  p.setPen(QPen(Qt::red));
  if (m_module == selectModule) {
    auto str = YDModuleWidget::tr("(已选中)");
    x = x + w + 15;
    w = m.horizontalAdvance(str);
    p.drawText(x, y, w, h, Qt::AlignCenter, str);
  }

  p.restore();
  p.setPen(QPen("#fefefe"));
  p.drawLine(0, height() - 2, width(), height() - 2);

  if (YDHelper::isDebugMode()) {
    QString strState = getStateInfo();
    p.setFont(font);
    p.setPen(QPen(m_fontColor));
    w = m.horizontalAdvance(strState);
    h = m.height();
    x = width() - w - 50;

    p.drawText(x, y, w, h, Qt::AlignLeft, strState);

    x = width() - w - 50 - 20 - m.horizontalAdvance(m_text1);
    w = m.horizontalAdvance(m_text1);
    p.drawText(x, y, w, h, Qt::AlignLeft, m_text1);
  }

  p.end();
}

QString YDModuleWidget::getStateInfo() {
  yd::proto::ProcState state = m_module->getDebugState();
  QString strState = YDModuleWidget::tr("未知");
  QString startTime{""}, endTime{""};

  if (state.begin > 0 && state.end > 0 /* && YDHelper::getTestStart()*/) {
    uint64 ullCurrent = yd::CTimestamp::GetCurrentMicroseconds();
    uint64 timedx = 3600000000;
    uint64 ullMin = ullCurrent - timedx;
    uint64 ullMax = ullCurrent + timedx;

    //    qDebug() << __FUNCTION__ << "---------1" << ullCurrent << ullMin <<
    //    ullMax
    //             << state.begin << state.end;
    if (state.begin >= ullMin && state.end <= ullMax) {
      startTime = STRTQSTR(
          yd::CTimestamp::FormatTimeFromMicroseconds(state.begin).c_str());
      endTime = STRTQSTR(
          yd::CTimestamp::FormatTimeFromMicroseconds(state.end).c_str());
    }
  }

  switch (state.state) {
    case LOGIC_TASK_STATE_INVALID:
      strState = YDModuleWidget::tr("不可用");
      break;
    case LOGIC_TASK_STATE_READY:
      strState = YDModuleWidget::tr("已就绪");
      break;
    case LOGIC_TASK_STATE_IN_PROCESSING:
      strState = YDModuleWidget::tr("运行中");
      break;
    case LOGIC_TASK_STATE_COMPLETED:
      strState = YDModuleWidget::tr("已完成");
      break;
    case LOGIC_TASK_STATE_FAILED:
      strState = YDModuleWidget::tr("已失败");
      break;
  }
  return strState.append(" 起始: " + startTime + " 结束: " + endTime);
}
