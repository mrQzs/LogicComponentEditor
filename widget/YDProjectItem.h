#ifndef YDPROJECTITEM_H
#define YDPROJECTITEM_H

#include <QWidget>

class YDModule;

class YDProjectItem : public QWidget {
  Q_OBJECT

 public:
  YDProjectItem(QWidget *parent = nullptr);
  ~YDProjectItem();

 public:
  void setIcon(const QString &str);
  void setText(const QString &text);
  void setBgColor(const QString &str);
  void setFtColor(const QString &str);
  void setTime(const QString &str);
  int height() const;

 protected:
  void paintEvent(QPaintEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  bool event(QEvent *e);
  void hoverEnter(QHoverEvent *e);
  void hoverLeave(QHoverEvent *e);

 signals:
  void sigClicked(const QString &);

 private:
  int m_height;
  QString m_icon;
  QString m_text;
  QPixmap m_iconp;
  QString m_time;

  QColor m_bgColor;
  QColor m_ftColor;

  bool m_isHover;

  QFont m_font;
  QFont m_font1;
};

#endif  // YDPROJECTITEM_H
