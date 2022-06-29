#ifndef YDMENUHEAD_H
#define YDMENUHEAD_H

#include <QWidget>

class YDMenuHead : public QWidget {
  Q_OBJECT

 public:
  YDMenuHead(QWidget *parent = nullptr);
  ~YDMenuHead();

 public:
  void setIcon(const QString &str);
  void setText(const QString &text);
  void haveChild(bool);
  void setItemModel(bool);

 protected:
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);

  bool event(QEvent *e);
  void hoverEnter(QHoverEvent *e);
  void hoverLeave(QHoverEvent *e);

 signals:
  void sigClicked(bool);

 private:
  QString m_icon;
  QString m_text;
  QPixmap m_iconp;
  QPixmap m_arrow1;
  QPixmap m_arrow2;
  bool m_isHaveChild;
  bool m_isPreessed;
  bool m_isItem;
  QString m_bgColor;
  QString m_ftColor;

  bool m_isHover;
  QFont m_font;
};
#endif  // YDMENUHEAD_H
