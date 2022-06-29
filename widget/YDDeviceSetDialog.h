#ifndef YDDEVICESETDIALOG_H
#define YDDEVICESETDIALOG_H

#include <QModelIndex>

#include "YDDialog.h"

class QToolButton;
class YDListView;
class YDTableView;
class YDSingleTableView;
class QTabWidget;
class QPushButton;
class YDAddDeviceDialog;
class YDDeviceModel;
class YDDeviceAxisModel;
class YDDeviceInputModel;
class YDDeviceOutputModel;

class YDDeviceSetDialog : public YDDialog {
  Q_OBJECT
 public:
  YDDeviceSetDialog(QWidget *parent = nullptr);

 public:
  // get
  virtual QStringList textList() const;

  // set
  virtual void setTextList(const QStringList &list);

 private slots:
  void slotDeviceAddClicked(bool);
  void slotDeviceEditClicked(bool);
  void slotDeviceDelClicked(bool);
  void slotAddDeviceFinished();
  void slotChangeDeviceFinished();

  void slotDeviceItemSingleClick(const QModelIndex &);
  void slotDeviceItemDoubleClick(const QModelIndex &);

 private:
  void initTabWidget();
  void initLayout();
  void initConnect();
  void updateDeviceModels();

 private:
  QToolButton *m_addDevice;
  QToolButton *m_editDevice;
  QToolButton *m_delDevice;
  QToolButton *m_download;
  QTabWidget *m_tabWidget;

  YDAddDeviceDialog *m_addDeviceDlg;

  YDListView *m_deviceView;
  YDDeviceModel *m_deviceModel;

  QWidget *m_axisW;
  YDSingleTableView *m_axisView;
  YDDeviceAxisModel *m_axisModel;

  QWidget *m_inputW;
  YDSingleTableView *m_inputView;
  YDDeviceInputModel *m_inputModel;

  QWidget *m_outputW;
  YDSingleTableView *m_outputView;
  YDDeviceOutputModel *m_outputModel;

  QModelIndex m_deviceIndex;
};

#endif  // YDDEVICESETDIALOG_H
