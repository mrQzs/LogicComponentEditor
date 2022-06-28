#include "YDLogo.h"

#include <QPainter>

YDLogo::YDLogo(QWidget *parent) : QWidget{parent} {
  m_pix =
      QPixmap(":/Icon/Logo.png")
          .scaled(512, 155, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  setFixedSize(512, 155);
}

void YDLogo::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.drawPixmap(0, 0, m_pix);
  p.end();
}
