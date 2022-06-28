#ifndef YDJOGBUTTON_H
#define YDJOGBUTTON_H

#include <QPushButton>

class YDJogButton : public QPushButton {
  Q_OBJECT
 public:
  YDJogButton(QWidget *parent = nullptr);

 signals:
  void sigStart();
  void sigStop();

  // QWidget interface
 protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
};

#endif  // YDJOGBUTTON_H
