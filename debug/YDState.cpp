#include "YDState.h"

#include <Qpainter>

YDState::YDState(QWidget *parent)
    : QLabel(parent), m_state{0}, m_gray("#7f7f7f"), m_green{"#22b14c"} {}

void YDState::setState(int state) { m_state = state; }

int YDState::getState() const { return m_state; }

void YDState::setMidText(const QString &text) { m_text = text; }

void YDState::paintEvent(QPaintEvent *) {
  QPainter p(this);
  switch (m_state) {
    case 0:
      p.setBrush(QColor(m_gray));
      break;
    case 1:
      p.setBrush(QColor(m_green));
      break;
    default:
      break;
  }

  p.drawRect(rect());

  p.setPen(Qt::white);
  p.setBrush(Qt::NoBrush);

  if (!m_text.isEmpty()) {
    QFont font;
    font.setPixelSize(14);
    p.setFont(font);
    auto m = p.fontMetrics();
    auto h = m.height();
    auto w = m.horizontalAdvance(m_text);
    auto x = (width() - w) / 2;
    auto y = (height() - h) / 2;

    p.drawText(x, y, w, h, Qt::AlignCenter, m_text);
  }

  p.end();
}
