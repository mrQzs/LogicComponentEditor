#ifndef YDDCYLINDERWIDGET_H
#define YDDCYLINDERWIDGET_H

#include <QWidget>

#include "YDState.h"

class YDDCylinderView;
class YDCylinderModel;
class QLabel;
class QPushButton;

class YDDCylinderWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDDCylinderWidget(QWidget* parent = nullptr);

 signals:

 private slots:
  void slotItemClicked(const QModelIndex& index);

 public:
  void updateData();

 private slots:
  void slotForward(bool);
  void slotBack(bool);

 private:
  YDDCylinderView* m_view;
  YDCylinderModel* m_model;
  QLabel* m_lab1;
  YDState* m_state1;
  QLabel* m_lab2;
  YDState* m_state2;
  QLabel* m_lab3;
  YDState* m_state3;
  QLabel* m_lab4;
  YDState* m_state4;

  QLabel* m_lab5;
  YDState* m_state5;
  QLabel* m_lab6;
  YDState* m_state6;

  QPushButton* m_forwardBtn;
  QPushButton* m_backBtn;
};

#endif  // YDDCYLINDERWIDGET_H
