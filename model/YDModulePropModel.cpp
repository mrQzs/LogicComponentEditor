#include "YDModulePropModel.h"

#include <QComboBox>
#include <QDebug>
#include <QSpinBox>
#include <QVariant>

#include "common/YDGlobal.h"
#include "modules/YDModule.h"
#include "properties/YDProperty.h"
#include "widget/YDNameLineEdit.h"

YDModulePropModel::YDModulePropModel(QObject *parent)
    : QAbstractItemModel{parent}, m_module(nullptr) {}

QVariant YDModulePropModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if ((Qt::Horizontal != orientation) || (Qt::DisplayRole != role))
    return QVariant();

  if (0 == section)
    return YDModulePropModel::tr("属性");
  else if (1 == section)
    return YDModulePropModel::tr("值");
  return QVariant();
}

QModelIndex YDModulePropModel::index(int row, int column,
                                     const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent) || (nullptr == m_module))
    return QModelIndex();

  if (parent.isValid()) {
    const YDProperty *p = static_cast<YDProperty *>(parent.internalPointer());
    const YDProperty *c = p->child(row);
    return createIndex(row, column, const_cast<YDProperty *>(c));
  } else {
    auto props = m_module->properties();
    Q_ASSERT(row < props.size());
    return createIndex(row, column, const_cast<YDProperty *>(props.at(row)));
  }
  return QModelIndex();
}

QModelIndex YDModulePropModel::parent(const QModelIndex &child) const {
  if (!child.isValid() || (m_module == nullptr)) return QModelIndex();

  const YDProperty *item =
      static_cast<const YDProperty *>(child.internalPointer());
  const YDProperty *p = item->parent();
  if (nullptr == p) return QModelIndex();
  return createIndex(p->row(), 0, const_cast<YDProperty *>(p));
}

int YDModulePropModel::rowCount(const QModelIndex &parent) const {
  if (nullptr == m_module) return 0;

  if (parent.isValid()) {
    const YDProperty *p =
        static_cast<const YDProperty *>(parent.internalPointer());
    return p->count();
  }

  return m_module->properties().size();
}

int YDModulePropModel::columnCount(const QModelIndex &) const { return 2; }

QVariant YDModulePropModel::data(const QModelIndex &index, int role) const {
  if ((m_module == nullptr) || !index.isValid()) return QVariant();
  auto prop = reinterpret_cast<YDProperty *>(index.internalPointer());

  if (prop->isShow()) {
    if (role == Qt::DisplayRole) {
      if (index.column() == 0) {
        return prop->name();
      } else if (index.column() == 1) {
        QVariant val = prop->value(m_module);
        if (val.typeId() != QMetaType::QStringList) return val;

        QStringList ret;
        for (const QVariant &v : val.toList()) ret << v.toString();
        return "[" + ret.join(",") + "]";
      }
    } else if ((Qt::UserRole + 1) == role) {
      YDModuleCast cast;
      cast.ptr = m_module;
      return cast.i;
    }
  }
  return QVariant();
}

Qt::ItemFlags YDModulePropModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
  auto prop = reinterpret_cast<YDProperty *>(index.internalPointer());
  if (index.isValid() && (1 == index.column()) && prop && prop->hasEditor())
    return Qt::ItemIsEditable | defaultFlags;
  else
    return defaultFlags;
}

void YDModulePropModel::setModule(YDModule *m) {
  m_module = m;
  beginResetModel();
  endResetModel();
}

void YDModulePropModel::updateView() {
  beginResetModel();
  endResetModel();
}

YDPropertyDelegate::YDPropertyDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {}

QWidget *YDPropertyDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &index) const {
  if (!index.isValid() || (1 != index.column())) return nullptr;
  auto prop = reinterpret_cast<YDProperty *>(index.internalPointer());
  if (prop && prop->isShow()) return prop->editor(parent);
  return nullptr;
}

void YDPropertyDelegate::setEditorData(QWidget *,
                                       const QModelIndex &index) const {
  if (!index.isValid() || (1 != index.column())) return;
  YDModuleCast cast;
  auto prop = reinterpret_cast<YDProperty *>(index.internalPointer());
  if (prop->isShow()) {
    cast.i = index.data(Qt::UserRole + 1).toLongLong();
    if ((nullptr == cast.ptr) || (nullptr == prop)) return;
    prop->updateEditor(cast.ptr);
  }
}

void YDPropertyDelegate::setModelData(QWidget *, QAbstractItemModel *model,
                                      const QModelIndex &index) const {
  if (!index.isValid() || (1 != index.column())) return;
  YDModuleCast cast;
  auto prop = reinterpret_cast<YDProperty *>(index.internalPointer());
  if (prop->isShow()) {
    cast.i = index.data(Qt::UserRole + 1).toLongLong();
    if ((nullptr == cast.ptr) || (nullptr == prop)) return;
    prop->updateWidget(cast.ptr);
    emit model->dataChanged(index, index);
  }
}

QSize YDPropertyDelegate::sizeHint(const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
  return QStyledItemDelegate::sizeHint(option, index);
}
