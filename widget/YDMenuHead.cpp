#include "YDMenuHead.h"

#include <QDebug>
#include <QEvent>
#include <QHoverEvent>
#include <QPainter>

YDMenuHead::YDMenuHead(QWidget *parent)
    : QWidget(parent),
      m_arrow1{QPixmap(":/Icon/arrow_up.png")},
      m_arrow2{QPixmap(":/Icon/arrow_down.png")},
      m_isHaveChild(false),
      m_isPreessed(false),
      m_isItem{false},
      m_isHover{false} {
  setFixedHeight(30);
  m_icon = ":/Icon/plus.png";
  m_text = "自定义脚本";
  setAttribute(Qt::WA_Hover);
}

YDMenuHead::~YDMenuHead() {}

void YDMenuHead::setIcon(const QString &str) {
  m_icon = str;
  m_iconp = QPixmap(m_icon).scaled(QSize(22, 22), Qt::IgnoreAspectRatio,
                                   Qt::SmoothTransformation);
}

void YDMenuHead::setText(const QString &text) { m_text = text; }

void YDMenuHead::haveChild(bool b) { m_isHaveChild = b; }

void YDMenuHead::setItemModel(bool b) { m_isItem = b; }

void YDMenuHead::paintEvent(QPaintEvent *) {
  QPainter p(this);

  if (m_isHover)
    p.setBrush(QColor(0xe5, 0xf1, 0xfb));
  else
    p.setBrush(Qt::white);

  p.setPen(Qt::NoPen);
  p.drawRect(rect());

  auto H = height();
  int x = 0, y = 0, w = 0, h = 0;

  if (m_isItem) {
    if (m_isHaveChild) {
      w = m_arrow1.width() * 0.5;
      h = m_arrow1.height() * 0.5;
      x = 10;
      y = (H - h) / 2;

      if (m_isPreessed)
        p.drawPixmap(x, y, w, h, m_arrow1);
      else
        p.drawPixmap(x, y, w, h, m_arrow2);
    }

    if (!m_icon.isEmpty()) {
      QPixmap pix(m_icon);
      pix = pix.scaled(QSize(16, 16), Qt::IgnoreAspectRatio,
                       Qt::SmoothTransformation);
      x = x + w + 10;
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
  } else {
    if (m_isHaveChild) {
      w = m_arrow1.width() * 0.6;
      h = m_arrow1.height() * 0.6;
      x = 5;
      y = (H - h) / 2;
      if (m_isPreessed)
        p.drawPixmap(x, y, w, h, m_arrow1);
      else
        p.drawPixmap(x, y, w, h, m_arrow2);
    }

    if (!m_icon.isEmpty()) {
      x = x + w + 20;
      w = m_iconp.width();
      h = m_iconp.height();
      y = (H - h) / 2;
      p.drawPixmap(x, y, w, h, m_iconp);
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
  }

  p.end();
}

void YDMenuHead::mousePressEvent(QMouseEvent *) {
  m_isPreessed = !m_isPreessed;
  emit sigClicked(m_isPreessed);
}

void YDMenuHead::mouseReleaseEvent(QMouseEvent *) { update(); }

bool YDMenuHead::event(QEvent *e) {
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

void YDMenuHead::hoverEnter(QHoverEvent *e) {
  m_isHover = true;
  update();

  QWidget::event(e);
}

void YDMenuHead::hoverLeave(QHoverEvent *e) {
  m_isHover = false;
  update();

  QWidget::event(e);
}
