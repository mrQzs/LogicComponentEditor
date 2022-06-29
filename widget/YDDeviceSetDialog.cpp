#include "YDDeviceSetDialog.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "model/YDDeviceAxisModel.h"
#include "model/YDDeviceInputModel.h"
#include "model/YDDeviceModel.h"
#include "model/YDDeviceOutputModel.h"
#include "property/YDAddDeviceDialog.h"
#include "view/YDListView.h"
#include "view/YDTableView.h"

YDDeviceSetDialog::YDDeviceSetDialog(QWidget *parent)
    : YDDialog{parent},
      m_addDevice{new QToolButton(this)},
      m_editDevice{new QToolButton(this)},
      m_delDevice{new QToolButton(this)},
      m_download{new QToolButton(this)},
      m_tabWidget{new QTabWidget(this)},
      m_addDeviceDlg{nullptr},
      m_deviceView{new YDListView(this)},
      m_deviceModel{new YDDeviceModel(this)},
      m_axisW{new QWidget(this)},
      m_axisView{new YDSingleTableView(m_axisW)},
      m_axisModel{new YDDeviceAxisModel(m_axisW)},
      m_inputW{new QWidget(this)},
      m_inputView{new YDSingleTableView(m_inputW)},
      m_inputModel{new YDDeviceInputModel(m_inputW)},
      m_outputW{new QWidget(this)},
      m_outputView{new YDSingleTableView(m_outputW)},
      m_outputModel{new YDDeviceOutputModel(m_outputW)} {
  setWindowTitle(YDDeviceSetDialog::tr("设备管理"));

  auto size = QSize(25, 25);
  m_addDevice->setIconSize(size);
  m_editDevice->setIconSize(size);
  m_delDevice->setIconSize(size);
  m_download->setIconSize(size);

  m_addDevice->setToolTip(YDDeviceSetDialog::tr("添加设备"));
  m_editDevice->setToolTip(YDDeviceSetDialog::tr("修改设备"));
  m_delDevice->setToolTip(YDDeviceSetDialog::tr("删除设备"));
  m_download->setToolTip(YDDeviceSetDialog::tr(""));

  m_addDevice->setIcon(QIcon(":/Icon/addBtn.png"));
  m_editDevice->setIcon(QIcon(":/Icon/edit.png"));
  m_delDevice->setIcon(QIcon(":/Icon/delBtn.png"));
  m_download->setIcon(QIcon(":/Icon/redo.png"));
  m_download->hide();  //暂无接口 隐藏 2022-06-20

  m_deviceView->setModel(m_deviceModel);

  initTabWidget();
  initLayout();
  initConnect();

  resize(1100, 760);
}

QStringList YDDeviceSetDialog::textList() const {
  QStringList list;
  return list;
}

void YDDeviceSetDialog::setTextList(const QStringList &) {}

void YDDeviceSetDialog::slotDeviceAddClicked(bool) {
  if (m_addDeviceDlg) delete m_addDeviceDlg;
  m_addDeviceDlg =
      new YDAddDeviceDialog(YDAddDeviceDialog::tr("添加设备"), this);
  connect(m_addDeviceDlg, &YDAddDeviceDialog::finished, this,
          &YDDeviceSetDialog::slotAddDeviceFinished);
  m_addDeviceDlg->open();
}

void YDDeviceSetDialog::slotDeviceEditClicked(bool) {
  auto index = m_deviceView->currentIndex();
  if (index.isValid()) {
    slotDeviceItemDoubleClick(index);
  } else {
    QMessageBox::warning(nullptr, YDDeviceSetDialog::tr("提示"),
                         YDDeviceSetDialog::tr("请选择要修改的设备!"));
  }
}

void YDDeviceSetDialog::slotDeviceDelClicked(bool) {
  auto index = m_deviceView->currentIndex();
  if (index.isValid()) {
    auto rb = QMessageBox::information(
        this, YDDeviceSetDialog::tr("提示"), YDDeviceSetDialog::tr("是否删除?"),
        YDDeviceSetDialog::tr("确认"), YDDeviceSetDialog::tr("取消"));
    if (0 == rb) {
      int row = index.row();
      auto list = YDProjectManage::getMotionDevices();
      if (row < list.size()) {
        auto device = list[row];
        YDProjectManage::deleteMotionDevice(device->base.id);
        updateDeviceModels();
        m_axisModel->clearModel();
        m_inputModel->cleaerModel();
        m_outputModel->cleaerModel();
      }
    }
  } else {
    QMessageBox::warning(nullptr, YDDeviceSetDialog::tr("提示"),
                         YDDeviceSetDialog::tr("请选择要删除的设备!"));
  }
}

void YDDeviceSetDialog::slotAddDeviceFinished() {
  if (m_addDeviceDlg->result() == QDialog::Accepted) {
    auto types = YDProjectManage::getPredefinedDeviceTypes();
    auto infos = m_addDeviceDlg->textList();
    int i = 0;
    for (; i < types.size(); ++i) {
      auto t = types[i];
      auto str =
          QString("%1 %2").arg(STRTQSTR(t->vendor.c_str()), STRTQSTR(t->model));
      if (str == infos[2]) break;
    }
    if (i < types.size()) {
      std::string name = YDHelper::qstringToString(infos[0]);
      yd::dev::MCDevice *dev = nullptr;
      auto type = types[i];
      if (YDProjectManage::createMotionDevice(name, type, dev)) {
        dev->base.name = YDHelper::qstringToString(infos[0]);
        dev->card.index = infos[1].toUInt();
        dev->card.config = YDHelper::qstringToString(infos[3]);
        dev->base.remarks = YDHelper::qstringToString(infos[4]);
        YDProjectManage::updateMCDeviceVariables(dev);
        updateDeviceModels();
        m_axisModel->updateModel(dev->listAxises);
        m_inputModel->updateModel(dev->listDIGroups);
        m_outputModel->updateModel(dev->listDOGroups);
      }
    }
  }
}

void YDDeviceSetDialog::slotChangeDeviceFinished() {
  if (m_addDeviceDlg->result() == QDialog::Accepted) {
    int row = m_deviceIndex.row();
    auto list = YDProjectManage::getMotionDevices();
    auto dev = list[row];
    auto infos = m_addDeviceDlg->textList();
    dev->base.name = YDHelper::qstringToString(infos[0]);
    dev->card.index = infos[1].toUInt();
    dev->card.config = YDHelper::qstringToString(infos[3]);
    dev->base.remarks = YDHelper::qstringToString(infos[4]);
    if (YDProjectManage::updateMCDeviceVariables(dev)) {
      updateDeviceModels();
      m_axisModel->updateModel(dev->listAxises);
      m_inputModel->updateModel(dev->listDIGroups);
      m_outputModel->updateModel(dev->listDOGroups);
    }
  }
}

void YDDeviceSetDialog::slotDeviceItemSingleClick(const QModelIndex &index) {
  auto row = index.row();
  auto list = YDProjectManage::getMotionDevices();
  if (row < list.size()) {
    auto device = list.at(row);
    m_axisModel->updateModel(device->listAxises);
    m_inputModel->updateModel(device->listDIGroups);
    m_outputModel->updateModel(device->listDOGroups);
  }
}

void YDDeviceSetDialog::slotDeviceItemDoubleClick(const QModelIndex &index) {
  int row = index.row();
  auto list = YDProjectManage::getMotionDevices();
  if (row < list.size()) {
    m_deviceIndex = index;
    auto dev = list[row];
    QStringList infos;
    infos << STRTQSTR(dev->base.name.c_str());
    infos << QString::number(dev->card.index);
    infos << QString("%1 %2").arg(STRTQSTR(dev->base.vendor.c_str()),
                                  STRTQSTR(dev->base.model));
    infos << STRTQSTR(dev->card.config.c_str());
    infos << STRTQSTR(dev->base.remarks.c_str());
    if (m_addDeviceDlg) delete m_addDeviceDlg;
    m_addDeviceDlg =
        new YDAddDeviceDialog(YDAddDeviceDialog::tr("编辑设备"), this);
    m_addDeviceDlg->setTextList(infos);
    connect(m_addDeviceDlg, &YDAddDeviceDialog::finished, this,
            &YDDeviceSetDialog::slotChangeDeviceFinished);
    m_addDeviceDlg->open();
  }
}

void YDDeviceSetDialog::initTabWidget() {
  auto valy1 = new QVBoxLayout(m_axisW);
  valy1->setContentsMargins(0, 0, 0, 0);
  valy1->setSpacing(0);
  valy1->addWidget(m_axisView);

  auto valy2 = new QVBoxLayout(m_inputW);
  valy2->setContentsMargins(0, 0, 0, 0);
  valy2->setSpacing(0);
  valy2->addWidget(m_inputView);

  auto valy3 = new QVBoxLayout(m_outputW);
  valy3->setContentsMargins(0, 0, 0, 0);
  valy3->setSpacing(0);
  valy3->addWidget(m_outputView);

  m_tabWidget->addTab(m_axisW, YDDeviceSetDialog::tr("轴"));
  m_tabWidget->addTab(m_inputW, YDDeviceSetDialog::tr("输入"));
  m_tabWidget->addTab(m_outputW, YDDeviceSetDialog::tr("输出"));

  m_axisView->setEditTriggers(QTableView::CurrentChanged);
  m_axisView->setModel(m_axisModel);
  m_axisView->setColumnWidth(21, 135);
  m_axisView->setItemDelegate(new YDDeviceAxisDelegate(m_axisView));
  m_inputView->setEditTriggers(QTableView::CurrentChanged);
  m_inputView->setModel(m_inputModel);
  m_inputView->setItemDelegate(new YDDeviceInputDelegate(m_inputView));
  m_outputView->setEditTriggers(QTableView::CurrentChanged);
  m_outputView->setModel(m_outputModel);
  m_outputView->setItemDelegate(new YDDeviceOutputDelegate(m_outputView));
}

void YDDeviceSetDialog::initLayout() {
  QHBoxLayout *hlay = new QHBoxLayout;
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->addWidget(m_addDevice);
  hlay->addWidget(m_editDevice);
  hlay->addWidget(m_delDevice);
  hlay->addWidget(m_download);
  hlay->addStretch();

  m_deviceView->setFixedWidth(200);

  QHBoxLayout *hlay2 = new QHBoxLayout;
  hlay2->setContentsMargins(0, 0, 0, 0);
  hlay2->setSpacing(0);
  hlay2->addWidget(m_deviceView);
  hlay2->addWidget(m_tabWidget);

  QVBoxLayout *vl = new QVBoxLayout(this);
  vl->setContentsMargins(0, 0, 0, 0);
  vl->setSpacing(0);
  vl->addLayout(hlay);
  vl->addLayout(hlay2);
}

void YDDeviceSetDialog::initConnect() {
  connect(m_deviceView, &QListView::clicked, this,
          &YDDeviceSetDialog::slotDeviceItemSingleClick);
  connect(m_deviceView, &QListView::doubleClicked, this,
          &YDDeviceSetDialog::slotDeviceItemDoubleClick);

  connect(m_addDevice, SIGNAL(clicked(bool)), this,
          SLOT(slotDeviceAddClicked(bool)));
  connect(m_editDevice, SIGNAL(clicked(bool)), this,
          SLOT(slotDeviceEditClicked(bool)));
  connect(m_delDevice, SIGNAL(clicked(bool)), this,
          SLOT(slotDeviceDelClicked(bool)));
}

void YDDeviceSetDialog::updateDeviceModels() {
  m_deviceView->setModel(nullptr);
  m_deviceView->setModel(m_deviceModel);
}
