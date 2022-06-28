#include "YDMenuItem.h"

#include <QHoverEvent>
#include <QPainter>

YDMenuItem::YDMenuItem(int type, QWidget *parent)
    : YDWidget(type, parent), m_isHover{false} {
  setFixedHeight(30);
  m_icon = ":/Icon/Debug.png";
  m_text = "自定义脚本";
  setAttribute(Qt::WA_Hover);
}

YDMenuItem::~YDMenuItem() {}

void YDMenuItem::setIcon(const QString &str) { m_icon = str; }

void YDMenuItem::setText(const QString &text) { m_text = text; }

void YDMenuItem::paintEvent(QPaintEvent *) {
  QPainter p(this);

  if (m_isHover)
    p.setBrush(QColor(0xe5, 0xf1, 0xfb));
  else
    p.setBrush(Qt::white);

  p.setPen(Qt::NoPen);
  p.drawRect(rect());

  auto W = width();
  auto H = height();
  p.save();
  QPen pen(Qt::black);
  pen.setWidthF(1.42);
  p.setPen(pen);
  // p.drawLine(W, 0, W, H);
  p.drawLine(0, H, W, H);
  p.restore();

  int x = 10, y = 0, w = 0, h = 0;

  if (!m_icon.isEmpty()) {
    QPixmap pix(m_icon);
    pix = pix.scaled(QSize(16, 16), Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation);
    x = x + w + 20;
    w = pix.width();
    h = pix.height();
    y = (H - h) / 2;
    p.drawPixmap(x, y, w, h, pix);
  }

  if (!m_text.isEmpty()) {
    p.setPen(Qt::black);
    QFont font;
    font.setPixelSize(14);
    p.setFont(font);
    x = x + w + 10;
    auto m = p.fontMetrics();
    h = m.height();
    w = m.horizontalAdvance(m_text);
    y = (H - h) / 2;

    p.drawText(x, y, w, h, Qt::AlignCenter, m_text);
  }

  p.end();
}

bool YDMenuItem::event(QEvent *e) {
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

void YDMenuItem::hoverEnter(QHoverEvent *e) {
  m_isHover = true;
  update();

  QWidget::event(e);
}

void YDMenuItem::hoverLeave(QHoverEvent *e) {
  m_isHover = false;
  update();

  QWidget::event(e);
}
