#include "YDMenuModel.h"

#include <QMessageBox>
#include <QMimeData>

#include "MainWindow.h"
#include "common/YDHelper.h"
#include "core/YDTask.h"
#include "widget/YDNameLineEdit.h"

YDMenuModel::YDMenuModel(YDTask *root, QObject *parent)
    : QAbstractItemModel{parent}, m_root{root} {}

YDMenuModel::~YDMenuModel() {}

void YDMenuModel::updateModel() {
  beginResetModel();
  endResetModel();
}

QVariant YDMenuModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  if ((orientation != Qt::Horizontal) || (role != Qt::DisplayRole))
    return QVariant();
  if (section == 0) return YDMenuModel::tr("任务列表");
  return QVariant();
}

QModelIndex YDMenuModel::index(int row, int column,
                               const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();

  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDTask *>(parent.internalPointer());

  auto pChild = p->child(row);
  if (pChild) return createIndex(row, column, pChild);
  return QModelIndex();
}

QModelIndex YDMenuModel::parent(const QModelIndex &child) const {
  if (!child.isValid()) return QModelIndex();
  auto c = static_cast<YDTask *>(child.internalPointer());
  auto p = c->parent();
  if (p == m_root) return QModelIndex();
  return createIndex(p->row(), 0, p);
}

int YDMenuModel::rowCount(const QModelIndex &parent) const {
  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDTask *>(parent.internalPointer());
  return p->childSize();
}

int YDMenuModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 1;
}

QVariant YDMenuModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  const YDTask *o = reinterpret_cast<YDTask *>(index.internalPointer());

  if (Qt::DisplayRole == role)
    return o->name();
  else if (Qt::DecorationRole == role)
    return QIcon(o->Icon());
  else if ((Qt::UserRole + 1) == role)
    return o->Icon();
  return QVariant();
}

bool YDMenuModel::setData(const QModelIndex &index, const QVariant &value,
                          int role) {
  if (role != Qt::DisplayRole && role != Qt::EditRole) {
    return false;
  }

  auto *p = m_root;
  if (index.isValid()) {
    p = static_cast<YDTask *>(index.internalPointer());
  }

  p->setName(value.toString());
  emit dataChanged(index, index);
  return true;
}

Qt::ItemFlags YDMenuModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }

  // auto task = reinterpret_cast<YDTask *>(index.internalPointer());
  //   if (task->parent() == m_root)
  //     return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
  //            Qt::ItemIsDropEnabled;

  //  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
  //         Qt::ItemIsDragEnabled;

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool YDMenuModel::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  auto *p = m_root;
  if (parent.isValid()) {
    p = static_cast<YDTask *>(parent.internalPointer());
  }

  auto task = new YDTask(p);
  task->initLogicProcess();

  p->insertChild(row, task);
  endInsertRows();
  return true;
}

bool YDMenuModel::removeRows(int row, int count, const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDTask *>(parent.internalPointer());

  p->removeChild(p->child(row));
  endRemoveRows();
  return true;
}

QModelIndex YDMenuModel::addTree(const QModelIndex &parent) {
  auto *p = m_root;
  auto pp = parent;
  if (parent.isValid()) p = static_cast<YDTask *>(parent.internalPointer());
  if (p->parent() && p->parent()->parent() == m_root) {
    p = p->parent();
    pp = parent.parent();
  }

  int row = p->childSize();

  insertRows(row, 1, pp);

  QModelIndex index = this->index(row, 0, parent);
  return index;
}

QModelIndex YDMenuModel::addTree(int row, const QModelIndex &parent) {
  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDTask *>(parent.internalPointer());
  if (p->parent() && p->parent()->parent() == m_root) return QModelIndex();

  insertRows(row, 1, parent);

  QModelIndex index = this->index(row, 0, parent);
  // setData(index, str, Qt::DisplayRole);
  return index;
}

void YDMenuModel::removeTree(QModelIndex &index) {
  if (index.isValid()) {
    removeRows(index.row(), 1, index.parent());
  }
}

YDTask *YDMenuModel::getRoot() { return m_root; }

// drag and drap
Qt::DropActions YDMenuModel::supportedDropActions() const {
  return Qt::MoveAction;
}

QStringList YDMenuModel::mimeTypes() const {
  QStringList types;
  types << "application/tree.item.list";
  return types;
}

QMimeData *YDMenuModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *mimeData = new QMimeData();
  QByteArray encodeData;

  QDataStream stream(&encodeData, QIODeviceBase::WriteOnly);
  foreach (const QModelIndex &index, indexes) {
    if (index.isValid()) {
      stream << reinterpret_cast<quint64>(index.internalPointer());
    }
  }
  mimeData->setData("application/tree.item.list", encodeData);
  return mimeData;
}

bool YDMenuModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                               int row, int column, const QModelIndex &parent) {
  if (action == Qt::IgnoreAction) {
    return true;
  }
  if (!data->hasFormat("application/tree.item.list")) {
    return false;
  }
  if (column > 0) {
    return false;
  }
  if (action == Qt::MoveAction) {
    QByteArray encodeData = data->data("application/tree.item.list");
    QDataStream stream(&encodeData, QIODeviceBase::ReadOnly);

    quint64 intPoint;
    stream >> intPoint;
    auto task = reinterpret_cast<YDTask *>(intPoint);
    YDTask *newTask = nullptr;
    auto pTask = static_cast<YDTask *>(parent.internalPointer());
    if (-1 == row)
      newTask = static_cast<YDTask *>(
          addTree(pTask->childSize(), parent).internalPointer());
    else
      newTask = static_cast<YDTask *>(addTree(row, parent).internalPointer());

    if (newTask) newTask->copy(task);
  }
  return true;
}

YDMenuDeletegate::YDMenuDeletegate(QObject *parent)
    : QStyledItemDelegate{parent} {}

QWidget *YDMenuDeletegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
  Q_UNUSED(option);
  if (!index.isValid() || (index.column() != 0)) return nullptr;
  auto task = reinterpret_cast<YDTask *>(index.internalPointer());
  if (task) {
    auto lineedit = static_cast<YDNameLineEdit *>(task->editor(parent));

    connect(lineedit, SIGNAL(editingFinished()), this,
            SLOT(commitAndCloseEditor()));
    return lineedit;
  }
  return nullptr;
}

void YDMenuDeletegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {
  if (!index.isValid() || (index.column() != 0)) return;

  YDNameLineEdit *YDEditor = qobject_cast<YDNameLineEdit *>(editor);
  auto str = index.data(Qt::DisplayRole).toString();
  YDEditor->setText(str);
}

void YDMenuDeletegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const {
  if (index.data(Qt::DisplayRole).canConvert<QString>()) {
    YDNameLineEdit *YDEditor = qobject_cast<YDNameLineEdit *>(editor);
    auto task = reinterpret_cast<YDTask *>(index.internalPointer());
    auto name = QSTRTSTR(YDEditor->text());
    int ret = YDProjectManage::updateLogicTaskName(task->id(), name);
    switch (ret) {
      case -1:
        QMessageBox::warning(nullptr, QObject::tr("错误"),
                             QObject::tr("更新名称失败!"));
        break;
      case 0:
        task->setName(YDEditor->text());
        break;
      case 1:
        QMessageBox::warning(nullptr, QObject::tr("错误"),
                             QObject::tr("名称已重复!"));
        break;
    }
  } else {
    QStyledItemDelegate::setModelData(editor, model, index);
  }
}

bool YDMenuDeletegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {
  //禁止双击编辑
  if (event->type() == QEvent::MouseButtonDblClick) {
    return true;
  }
  return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize YDMenuDeletegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
  auto size = QStyledItemDelegate::sizeHint(option, index);
  return size;
}

void YDMenuDeletegate::commitAndCloseEditor() {
  YDNameLineEdit *editor = qobject_cast<YDNameLineEdit *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}
