#ifndef YDLOGO_H
#define YDLOGO_H

#include <QWidget>

class YDLogo : public QWidget {
  Q_OBJECT
 public:
  explicit YDLogo(QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *);

 signals:

 private:
  QPixmap m_pix;
};

#endif  // YDLOGO_H
