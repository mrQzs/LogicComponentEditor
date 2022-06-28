#include "YDDTComBoBox.h"

#include "common/YDHelper.h"

YDDTComboBox::YDDTComboBox(QWidget *parent) : QComboBox{parent} {
  auto list = YDHelper::getDataTypeList();
  addItems(list);
}
