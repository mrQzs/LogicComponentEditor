#ifndef YDPICBUTTON_H
#define YDPICBUTTON_H

#include <QPushButton>

class YDPicButton : public QPushButton {
  Q_OBJECT
 public:
  YDPicButton(QWidget* parent = nullptr);

 public:
  void setPic(const QString& str);
  void setText(const QString& text);

 protected:
  void paintEvent(QPaintEvent*);

  bool event(QEvent* e);

  void hoverEnter(QHoverEvent* e);

  void hoverLeave(QHoverEvent* e);

 private:
  QPixmap m_pix;
  QString m_text;

  bool m_isHover;
};

#endif  // YDPICBUTTON_H
