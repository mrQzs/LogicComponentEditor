#include "YDIntVarComboBox.h"

#include "core/YDProjectManage.h"

YDIntVarComboBox::YDIntVarComboBox(QWidget *parent) : QComboBox{parent} {
  QStringList strlist;

  auto list = YDProjectManage::getAllVirtualVariables();
  for (auto v : list) {
    if ((v->value_type >= DATA_TYPE_INT8) &&
        (v->value_type <= DATA_TYPE_UINT64)) {
      strlist << QString::fromLocal8Bit(v->variable_name);
    }
  }

  addItems(strlist);
}
