#ifndef YDWIDGET_H
#define YDWIDGET_H

#include <QWidget>

class YDWidget : public QWidget {
  Q_OBJECT
 public:
  YDWidget(int type = 0, QWidget* parent = nullptr);

 public:
  int getType();
  void setType(int type);

 protected:
  void mouseReleaseEvent(QMouseEvent*);

 signals:
  void sigClicked(int);

 private:
  int m_type;
};

#endif  // YDWIDGET_H
