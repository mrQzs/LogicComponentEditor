#ifndef YDMOVECONTROLWIDGET_H
#define YDMOVECONTROLWIDGET_H

#include <QMap>
#include <QWidget>

#include "YDDgHelper.h"
#include "yd_project.h"

class QLabel;
class QCheckBox;
class QSlider;
class YDJogButton;
class QLineEdit;
class YDAXisListView;
class YDAxisListModel;
class YDState;

class YDMoveControlWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDMoveControlWidget(QWidget* parent = nullptr);

 public:
  void updateData();

  int getSliderValue(int row) const;

  double getDistance(int row) const;

 signals:

 private slots:
  void box1checked(bool);

  void box2checked(bool);

  void sliderchanged(int);

  void slotViewClicked(const QModelIndex& index);

  void slotJogStart();

  void slotJogStop();

  void slotDJogStart();

  void slotDJogStop();

  void textChanged(const QString&);

 private:
  bool setData();

 private:
  YDAXisListView* m_view;
  YDAxisListModel* m_model;

  QLabel* m_lab1;
  QCheckBox* m_cbox1;
  QCheckBox* m_cbox2;

  QLabel* m_lab2;
  QLabel* m_sliderLab;
  QSlider* m_slider;

  QLabel* m_lab3;
  QLineEdit* m_edit3;
  QLabel* m_lab4;

  QLabel* m_lab5;
  QLineEdit* m_edit5;

  QLabel* m_lab6;
  QLineEdit* m_edit6;

  QLabel* m_lab7;
  YDState* m_lab8;
  YDState* m_lab9;
  YDState* m_lab10;

  QLabel* m_lab11;
  YDJogButton* m_btn1;
  YDJogButton* m_btn2;

  QMap<int, int> m_slideMap;
  QMap<int, double> m_distanceMap;
  yd::dev::MCAxisInfo* m_axis;
  yd::dev::MCAxisMoveSetup* m_move;
};

#endif  // YDMOVECONTROLWIDGET_H
