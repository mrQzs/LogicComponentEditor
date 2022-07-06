#ifndef YDSTATEWIDGET_H
#define YDSTATEWIDGET_H

#include <QWidget>

class YDState;
class QLabel;
class QLineEdit;
class QPushButton;
class YDAXisListView;
class YDAxisListModel;
class YDLoadingDialog;

class YDStateWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDStateWidget(YDAXisListView* view, QWidget* parent = nullptr);

 public:
  void updateData();
  void clearStateInfo();

 private:
  void setReturnState(qint32 code, const QString& name);

 signals:

 private slots:
  void slotbtn1Clicked(bool);
  void slotbtn2Clicked(bool);
  void slotbtn3Clicked(bool);
  void slotbtn4Clicked(bool);
  void slotbtn5Clicked(bool);

 private:
  YDAXisListView* m_view;
  YDAxisListModel* m_model;
  YDLoadingDialog* m_loading;

  QLabel* m_lab1;
  YDState* m_zero;
  QLabel* m_lab2;
  YDState* m_enable;
  QLabel* m_lab3;
  YDState* m_drive;
  QLabel* m_lab4;
  YDState* m_motion;
  QLabel* m_lab5;
  YDState* m_plus;
  QLabel* m_lab6;
  YDState* m_nagetive;
  QLabel* m_lab7;
  YDState* m_point;
  QLabel* m_lab8;
  YDState* m_emerg;

  QLabel* m_lab11;
  QLineEdit* m_edit1;
  QLabel* m_lab12;
  QLineEdit* m_edit2;
  QLabel* m_lab13;
  QLineEdit* m_edit3;
  QLabel* m_lab14;
  QLineEdit* m_edit4;

  QPushButton* m_btn1;
  QPushButton* m_btn2;
  QPushButton* m_btn3;
  QPushButton* m_btn4;
  QPushButton* m_btn5;

  QLabel* m_state;
};

#endif  // YDSTATEWIDGET_H
