#ifndef YDLABEL_H
#define YDLABEL_H

#include <QWidget>

class YDLabel : public QWidget {
  Q_OBJECT
 public:
  explicit YDLabel(QWidget *parent = nullptr);

 public:
  void setPix(const QString &icon);
  void setText(const QString &text);

 protected:
  void paintEvent(QPaintEvent *);

 signals:

 private:
  QString m_pixStr;
  QPixmap m_pix;

  QString m_text;
  QFont m_font;
};

#endif  // YDLABEL_H
