#ifndef YDMODULEHEAD_H
#define YDMODULEHEAD_H

#include <QWidget>

class YDModule;

class YDModuleHead : public QWidget {
  Q_OBJECT

 public:
  YDModuleHead(YDModule *m, QWidget *parent = nullptr);
  ~YDModuleHead();

 public:
  void setIcon(const QString &str);
  void setText(const QString &text);
  void setBgColor(const QString &str);
  void setFtColor(const QString &str);

 protected:
  void paintEvent(QPaintEvent *);
  void mouseReleaseEvent(QMouseEvent *);

 signals:
  void sigClicked(bool);

 private:
  YDModule *m_module;
  QString m_icon;
  QString m_text;
  QPixmap m_iconp;
  QPixmap m_arrow1;
  QPixmap m_arrow2;
  bool m_isHaveChild;
  bool m_isPreessed;

  QColor m_bgColor;
  QColor m_ftColor;
};

#endif  // YDMODULEHEAD_H
