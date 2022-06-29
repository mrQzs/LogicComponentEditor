#include "YDControlModel.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMimeData>
#include <QPushButton>

#include "common/YDGlobal.h"
#include "common/YDHelper.h"

YDControlModel::YDControlModel(QObject *parent) : QAbstractListModel{parent} {
  m_strlist << YDControlModel::tr("IF判定条件")
            << YDControlModel::tr("IF-ELSE判定条件")
            << YDControlModel::tr("次数循环") << YDControlModel::tr("条件循环")
            << YDControlModel::tr("跳出循环") << YDControlModel::tr("延时等待");
}

YDControlModel::~YDControlModel() {}

int YDControlModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_strlist.size();
}

QVariant YDControlModel::data(const QModelIndex &index, int role) const {
  if (Qt::DisplayRole == role)
    return m_strlist[index.row()];
  else if (Qt::DecorationRole == role)
    return QIcon(":/Module/ModuleS.png");
  return QVariant();
}

Qt::ItemFlags YDControlModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
  if (index.isValid())
    return Qt::ItemIsDragEnabled | defaultFlags;
  else
    return defaultFlags;
}

QStringList YDControlModel::mimeTypes() const {
  return QStringList() << "YD/Module";
}

QMimeData *YDControlModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *mimeData = new QMimeData();
  QByteArray encodedata;

  YDModuleCast cast;
  QDataStream stream(&encodedata, QIODeviceBase::WriteOnly);
  for (const QModelIndex &index : indexes) {
    if (index.isValid() && index.column() == 0) {
      Module::Type type = Module::Abs_Motion;
      switch (index.row()) {
        case 0:
          type = Module::If_Condition;
          break;
        case 1:
          type = Module::IfElse_Condition;
          break;
        case 2:
          type = Module::Times_Loop;
          break;
        case 3:
          type = Module::Condition_Loop;
          break;
        case 4:
          type = Module::Jump_Loop;
          break;
        case 5:
          type = Module::Delay_Wait;
          break;
      }
      cast.ptr = YDHelper::getModule(type);
      stream << cast.i;
    }
  }

  mimeData->setData("YD/Module", encodedata);
  return mimeData;
}
