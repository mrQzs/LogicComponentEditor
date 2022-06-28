#ifndef YDMENUITEM_H
#define YDMENUITEM_H

#include "YDWidget.h"

class YDMenuItem : public YDWidget {
  Q_OBJECT

 public:
  YDMenuItem(int type = 0, QWidget *parent = nullptr);
  ~YDMenuItem();

 public:
  void setIcon(const QString &str);
  void setText(const QString &text);

 protected:
  void paintEvent(QPaintEvent *);

  bool event(QEvent *e);
  void hoverEnter(QHoverEvent *e);
  void hoverLeave(QHoverEvent *e);

 private:
  QString m_icon;
  QString m_text;
  bool m_isHover;
};

#endif  // YDMENUITEM_H
