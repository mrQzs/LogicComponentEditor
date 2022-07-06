#include "YDLoadingDialog.h"

#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QMovie>
#include <QPushButton>

YDLoadingDialog::YDLoadingDialog(QWidget *parent) : QDialog(parent) {
  setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
  setModal(true);
  setAttribute(Qt::WA_TranslucentBackground, true);

  setFixedSize(240, 240);
  m_frame = new QFrame(this);
  m_frame->setGeometry(10, 10, 230, 230);

  m_loading = new QMovie(":/Icon/loading.gif");
  m_loading->setScaledSize(QSize(120, 120));

  m_movieLabel = new QLabel(m_frame);
  m_movieLabel->setGeometry(55, 10, 120, 120);
  m_movieLabel->setScaledContents(true);
  m_movieLabel->setMovie(m_loading);
  m_loading->start();

  m_tipsLabel = new QLabel(m_frame);
  m_tipsLabel->setGeometry(5, 130, 220, 50);
  m_tipsLabel->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
  m_tipsLabel->setObjectName("tips");
  m_tipsLabel->setText("加载中,请稍候...");
  m_tipsLabel->setStyleSheet(
      "QLabel#tips{font-family:\"Microsoft YaHei\";font-size: 15px;color: "
      "#333333;}");

  QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
  shadow->setOffset(0, 0);
  shadow->setColor(QColor(32, 101, 165));
  shadow->setBlurRadius(10);
  this->setGraphicsEffect(shadow);
}
