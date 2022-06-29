#include "YDPicButton.h"

#include <QHoverEvent>
#include <QPainter>

YDPicButton::YDPicButton(QWidget *parent)
    : QPushButton{parent}, m_isHover{false} {}

void YDPicButton::setPic(const QString &str) {
  m_pix = QPixmap(str).scaled(28, 28, Qt::IgnoreAspectRatio,
                              Qt::SmoothTransformation);
}

void YDPicButton::setText(const QString &text) { m_text = text; }

void YDPicButton::paintEvent(QPaintEvent *) {
  QPainter p(this);

  p.save();
  p.setPen(Qt::NoPen);

  if (m_isHover) {
    p.setBrush(QColor(0xe5, 0xf1, 0xfb));
  } else {
    p.setBrush(QColor(0x95, 0xb3, 0xca));
  }

  p.drawRect(rect());
  p.restore();

  auto W = width();
  auto H = height();

  auto x = 0.05 * W;
  auto y = (H - 28) / 2;
  auto w = 28;
  auto h = 28;

  if (!m_pix.isNull()) p.drawPixmap(x, y, 28, 28, m_pix);

  if (!m_text.isEmpty()) {
    QFont font;
    font.setPixelSize(28);
    p.setFont(font);
    x = x + w + 15;
    auto m = p.fontMetrics();
    y = (H - m.height()) / 2;
    w = m.horizontalAdvance(m_text);
    h = m.height();

    p.drawText(x, y, w, h, Qt::AlignCenter, m_text);
  }

  p.end();
}

bool YDPicButton::event(QEvent *e) {
  switch (e->type()) {
    case QEvent::HoverEnter:
      hoverEnter(static_cast<QHoverEvent *>(e));
      return true;
    case QEvent::HoverLeave:
      hoverLeave(static_cast<QHoverEvent *>(e));
      return true;
    default:
      break;
  }
  return QWidget::event(e);
}

void YDPicButton::hoverEnter(QHoverEvent *e) {
  m_isHover = true;
  update();

  QPushButton::event(e);
}

void YDPicButton::hoverLeave(QHoverEvent *e) {
  m_isHover = false;
  update();

  QPushButton::event(e);
}
