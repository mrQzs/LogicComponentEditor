#ifndef YDSPEEDSETWIDGET_H
#define YDSPEEDSETWIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class YDAXisListView;
class YDAxisListModel;

class YDSpeedSetWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDSpeedSetWidget(QWidget* parent = nullptr);

 signals:

 public:
  void updateData();

 private slots:
  void slotItemClicked(const QModelIndex& index);
  void slotBtnClicked(bool);
  void slotBtn1Clicked(bool);
  void slotupdateData();

 private:
  YDAXisListView* m_view;
  YDAxisListModel* m_model;

  QLabel* m_lab1;
  QLineEdit* m_edit1;

  QLabel* m_lab2;
  QLineEdit* m_edit2;

  QLabel* m_lab3;
  QLineEdit* m_edit3;

  QLabel* m_lab4;
  QLineEdit* m_edit4;

  QLabel* m_lab5;
  QLineEdit* m_edit5;

  QLabel* m_lab6;
  QLineEdit* m_edit6;

  QLabel* m_lab7;
  QLineEdit* m_edit7;

  QPushButton* m_btn;
  QPushButton* m_btn1;
};

#endif  // YDSPEEDSETWIDGET_H
