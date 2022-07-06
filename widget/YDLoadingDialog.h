#ifndef YDLOADINGDIALOG_H
#define YDLOADINGDIALOG_H

#include <QDialog>

class QMovie;
class QLabel;
class QFrame;
class QPushButton;

class YDLoadingDialog : public QDialog {
  Q_OBJECT
 public:
  YDLoadingDialog(QWidget *parent = nullptr);

 private:
  QFrame *m_frame;
  QMovie *m_loading;
  QLabel *m_movieLabel;
  QLabel *m_tipsLabel;
};

#endif  // YDLOADINGDIALOG_H
