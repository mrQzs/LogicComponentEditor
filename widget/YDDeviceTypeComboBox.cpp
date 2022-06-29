#include "YDDeviceTypeComboBox.h"

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDDeviceTypeComboBox::YDDeviceTypeComboBox(QWidget *parent)
    : QComboBox{parent} {
  QStringList strlist;
  auto list = YDProjectManage::getPredefinedDeviceTypes();
  for (auto d : list) {
    strlist << QString("%1 %2").arg(STRTQSTR(d->vendor), STRTQSTR(d->model));
  }
  addItems(strlist);
}
