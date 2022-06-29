#include "YDLabel.h"

#include <QPainter>

YDLabel::YDLabel(QWidget *parent) : QWidget{parent} {
  m_font.setPixelSize(34);
  m_font.setBold(true);
}

void YDLabel::setPix(const QString &icon) {
  auto w = width();
  auto h = height();
  m_pixStr = icon;
  m_pix = QPixmap(icon).scaled(w, h, Qt::IgnoreAspectRatio,
                               Qt::SmoothTransformation);
}

void YDLabel::setText(const QString &text) { m_text = text; }

void YDLabel::paintEvent(QPaintEvent *) {
  QPainter p(this);
  if (!m_text.isEmpty()) {
    auto W = width();
    auto H = height();
    auto w = 0;
    auto h = 0;
    auto x = 0;
    auto y = 0;

    p.setFont(m_font);
    auto m = p.fontMetrics();
    w = m.horizontalAdvance(m_text);
    h = m.height();
    x = (W - w) / 2;
    y = (H - h) / 2;
    p.drawText(x, y, w, h, Qt::AlignCenter, m_text);
  }

  if (!m_pixStr.isEmpty()) p.drawPixmap(0, 0, m_pix);

  p.end();
}
