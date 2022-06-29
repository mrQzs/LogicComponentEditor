#include "YDProjectItem.h"

#include <QDateTime>
#include <QHoverEvent>
#include <QPainter>

YDProjectItem::YDProjectItem(QWidget *parent)
    : QWidget(parent), m_height{36}, m_isHover{false} {
  setFixedHeight(m_height);
  setAttribute(Qt::WA_Hover);
  m_font.setPixelSize(24);
  m_font1.setPixelSize(20);
}

YDProjectItem::~YDProjectItem() {}

void YDProjectItem::setIcon(const QString &str) {
  m_icon = str;
  m_iconp = QPixmap(m_icon).scaled(QSize(28, 28), Qt::IgnoreAspectRatio,
                                   Qt::SmoothTransformation);
}

void YDProjectItem::setText(const QString &text) { m_text = text; }

void YDProjectItem::setBgColor(const QString &str) { m_bgColor = QColor(str); }

void YDProjectItem::setFtColor(const QString &str) { m_ftColor = QColor(str); }

void YDProjectItem::setTime(const QString &str) { m_time = str; }

int YDProjectItem::height() const { return m_height; }

void YDProjectItem::paintEvent(QPaintEvent *) {
  QPainter p(this);

  p.save();
  p.setPen(Qt::NoPen);

  if (m_isHover) {
    p.setBrush(QColor(0xe5, 0xf1, 0xfb));
  } else {
    p.setBrush(m_bgColor);
  }

  p.drawRect(rect());
  p.restore();

  auto H = height();

  int x = 0, y = 0, w = 0, h = 0;

  if (!m_icon.isEmpty()) {
    x = x + w + 20;
    w = m_iconp.width();
    h = m_iconp.height();
    y = (H - h) / 2;
    p.drawPixmap(x, y, w, h, m_iconp);
  }

  if (!m_text.isEmpty()) {
    p.setPen(m_ftColor);
    p.setFont(m_font);
    x = x + w + 10;
    auto m = p.fontMetrics();
    h = m.height();
    w = m.horizontalAdvance(m_text);
    y = (H - h) / 2;

    p.drawText(x, y, w, h, Qt::AlignCenter, m_text);
  }

  p.setFont(m_font1);
  p.setPen(QPen(m_ftColor));
  auto m = p.fontMetrics();
  w = m.horizontalAdvance(m_time);
  h = m.height();
  x = width() - w - 5;

  p.drawText(x, y, w, h, Qt::AlignLeft, m_time);

  p.end();
}

void YDProjectItem::mouseReleaseEvent(QMouseEvent *) {
  emit sigClicked(m_text);
}

bool YDProjectItem::event(QEvent *e) {
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

void YDProjectItem::hoverEnter(QHoverEvent *e) {
  m_isHover = true;
  update();

  QWidget::event(e);
}

void YDProjectItem::hoverLeave(QHoverEvent *e) {
  m_isHover = false;
  update();

  QWidget::event(e);
}
