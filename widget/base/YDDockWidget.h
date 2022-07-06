#ifndef YDDOCKWIDGET_H
#define YDDOCKWIDGET_H

#include <QDockWidget>

class YDDockWidget : public QDockWidget {
  Q_OBJECT
 public:
  YDDockWidget(QWidget *parent = nullptr);

 signals:
  void sigCloseClicked();

 protected:
  void closeEvent(QCloseEvent *event) override;
};

#endif  // YDDOCKWIDGET_H
