#include "YDDeviceTypeComboBox.h"

#include "core/YDProjectManage.h"

YDDeviceTypeComboBox::YDDeviceTypeComboBox(QWidget *parent)
    : QComboBox{parent} {
  QStringList strlist;
  auto list = YDProjectManage::getPredefinedDeviceTypes();
  for (auto d : list) {
    strlist << QString("%1 %2").arg(QString::fromLocal8Bit(d->vendor),
                                    QString::fromLocal8Bit(d->model));
  }
  addItems(strlist);
}
