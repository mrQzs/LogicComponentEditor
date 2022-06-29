#ifndef YDPROJECTDIALOG_H
#define YDPROJECTDIALOG_H

#include <QDialog>

class QListWidget;
class YDNameLineEdit;
class YDLabel;
class QLabel;
class YDPicButton;
class YDNameDialog;

class YDProjectDialog : public QDialog {
  Q_OBJECT
 public:
  YDProjectDialog(QWidget* parent = nullptr);

 public:
  QString getProjectPath();
  QString getProjectName();

 private slots:
  void slotCreateClicked();
  void slotDiaFinished();
  void slotItemClicked(const QModelIndex& index);
  void slotWidgetClicked(const QString& text);

 private:
  void init();
  void initWidget1();
  void initWidget2();
  QString getFileChangeTime(const QString& path);

 private:
  YDLabel* m_logo;
  YDLabel* m_text;

  QWidget* m_widget1;
  QLabel* m_lab;
  QListWidget* m_listW;

  QWidget* m_widget2;
  QLabel* m_lab2;
  YDPicButton* m_create;

  YDNameDialog* m_createPDlg;

  QString m_name;
};

#endif  // YDPROJECTDIALOG_H
