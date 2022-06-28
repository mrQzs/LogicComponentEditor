#ifndef YDSTATE_H
#define YDSTATE_H

#include <QLabel>

class YDState : public QLabel {
  Q_OBJECT

 public:
  YDState(QWidget* parent = nullptr);

 public:
  void setState(int state);
  int getState() const;
  void setMidText(const QString&);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent*);

 private:
  int m_state;
  QString m_gray;
  QString m_green;
  QString m_text;
};

#endif  // YDSTATE_H
