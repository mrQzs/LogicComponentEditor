#include "YDOtherModel.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMimeData>
#include <QPushButton>

#include "common/YDGlobal.h"
#include "common/YDHelper.h"

YDOtherModel::YDOtherModel(QObject *parent) : QAbstractListModel{parent} {
  m_strlist << YDOtherModel::tr("例程调用") << YDOtherModel::tr("任务完成等待")
            << YDOtherModel::tr("报警确认") << YDOtherModel::tr("可编程控件")
            << YDOtherModel::tr("跳转控件");
}

YDOtherModel::~YDOtherModel() {}

int YDOtherModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_strlist.size();
}

QVariant YDOtherModel::data(const QModelIndex &index, int role) const {
  if (Qt::DisplayRole == role)
    return m_strlist[index.row()];
  else if (Qt::DecorationRole == role)
    return QIcon(":/Module/Module.png");
  return QVariant();
}

Qt::ItemFlags YDOtherModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
  if (index.isValid())
    return Qt::ItemIsDragEnabled | defaultFlags;
  else
    return defaultFlags;
}

QStringList YDOtherModel::mimeTypes() const {
  return QStringList() << "YD/Module";
}

QMimeData *YDOtherModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *mimeData = new QMimeData();
  QByteArray encodedata;

  YDModuleCast cast;
  QDataStream stream(&encodedata, QIODeviceBase::WriteOnly);
  for (const QModelIndex &index : indexes) {
    if (index.isValid() && index.column() == 0) {
      Module::Type type = Module::SubTask_Call;
      switch (index.row()) {
        case 0:
          type = Module::SubTask_Call;
          break;
        case 1:
          type = Module::Wait_Complete;
          break;
        case 2:
          type = Module::Alarm_Confirm;
          break;
        case 3:
          type = Module::Programable;
          break;
        case 4:
          type = Module::Jump_To_Task;
          break;
        default:
          break;
      }
      cast.ptr = YDHelper::getModule(type);
      stream << cast.i;
    }
  }

  mimeData->setData("YD/Module", encodedata);
  return mimeData;
}
