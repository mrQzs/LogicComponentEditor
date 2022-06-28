#ifndef YDMENU_H
#define YDMENU_H

#include <QWidget>

class YDMenuHead;

class YDMenu : public QWidget {
  Q_OBJECT
 public:
  explicit YDMenu(QWidget* parent = nullptr);

 public:
  void setIcon(const QString& str);
  void setText(const QString& text);

  void setWidget(QWidget* w);
  void setHaveChild(bool b);
  void setItemModel(bool b);

 signals:
  void sigClicked();

 private slots:
  void slotClicked(bool);

 private:
  void addWidget();

 private:
  YDMenuHead* m_head;
  QWidget* m_widget;
};

#endif  // YDMENU_H
