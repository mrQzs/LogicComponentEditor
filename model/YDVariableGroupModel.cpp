#include "YDVariableGroupModel.h"

#include <QMimeData>

#include "MainWindow.h"
#include "common/YDHelper.h"
#include "core/YDVariable.h"
#include "widget/YDNameLineEdit.h"

YDVariableGroupModel::YDVariableGroupModel(YDVariable *root, QObject *parent)
    : QAbstractItemModel{parent}, m_root{root}, m_enable{true} {}

YDVariableGroupModel::~YDVariableGroupModel() {}

void YDVariableGroupModel::setState(bool b) { m_enable = b; }

QVariant YDVariableGroupModel::headerData(int section,
                                          Qt::Orientation orientation,
                                          int role) const {
  if ((orientation != Qt::Horizontal) || (role != Qt::DisplayRole))
    return QVariant();
  if (section == 0) return YDVariableGroupModel::tr("变量组");
  return QVariant();
}

QModelIndex YDVariableGroupModel::index(int row, int column,
                                        const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();

  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDVariable *>(parent.internalPointer());

  auto pChild = p->child(row);
  if (pChild) return createIndex(row, column, pChild);
  return QModelIndex();
}

QModelIndex YDVariableGroupModel::parent(const QModelIndex &child) const {
  if (!child.isValid()) return QModelIndex();
  auto c = static_cast<YDVariable *>(child.internalPointer());
  auto p = c->parent();
  if (p == m_root) return QModelIndex();
  return createIndex(p->row(), 0, p);
}

int YDVariableGroupModel::rowCount(const QModelIndex &parent) const {
  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDVariable *>(parent.internalPointer());
  return p->childSize();
}

int YDVariableGroupModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 1;
}

QVariant YDVariableGroupModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  const YDVariable *o = reinterpret_cast<YDVariable *>(index.internalPointer());

  if (Qt::DisplayRole == role) return o->name();
  return QVariant();
}

bool YDVariableGroupModel::setData(const QModelIndex &index,
                                   const QVariant &value, int role) {
  if (role != Qt::DisplayRole && role != Qt::EditRole) {
    return false;
  }

  auto *p = m_root;
  if (index.isValid()) {
    p = static_cast<YDVariable *>(index.internalPointer());
  }

  p->setName(value.toString());
  emit dataChanged(index, index);
  return true;
}

Qt::ItemFlags YDVariableGroupModel::flags(const QModelIndex &index) const {
  if (!m_enable) return Qt::ItemIsEnabled;

  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool YDVariableGroupModel::insertRows(int row, int count,
                                      const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  auto *p = m_root;

  if (parent.isValid()) {
    p = static_cast<YDVariable *>(parent.internalPointer());
  }

  YDVariable *var = nullptr;
  yd::vr::VariableGroup *vg = nullptr;

  if (p->parent() != m_root) {
    YDProjectManage::createVariableMainGroup(vg);
  } else {
    YDProjectManage::createVariableSubGroup(p->groupId(), vg);
  }

  var = new YDVariable(vg, p);

  p->insertChild(row, var);
  endInsertRows();
  return true;
}

bool YDVariableGroupModel::removeRows(int row, int count,
                                      const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDVariable *>(parent.internalPointer());

  p->removeChild(p->child(row));
  endRemoveRows();
  return true;
}

QModelIndex YDVariableGroupModel::addTree(const QModelIndex &parent) {
  auto *p = m_root;
  auto pp = parent;
  if (parent.isValid()) p = static_cast<YDVariable *>(parent.internalPointer());
  if (p->parent() && p->parent()->parent() == m_root) {
    p = p->parent();
    pp = pp.parent();
  }

  int row = p->childSize();

  insertRows(row, 1, pp);

  QModelIndex index = this->index(row, 0, parent);
  return index;
}

QModelIndex YDVariableGroupModel::addTree(int row, const QModelIndex &parent) {
  auto *p = m_root;
  if (parent.isValid()) p = static_cast<YDVariable *>(parent.internalPointer());
  if (p->parent() && p->parent()->parent() == m_root) return QModelIndex();

  insertRows(row, 1, parent);

  QModelIndex index = this->index(row, 0, parent);
  // setData(index, str, Qt::DisplayRole);
  return index;
}

void YDVariableGroupModel::removeTree(QModelIndex &index) {
  if (index.isValid()) {
    removeRows(index.row(), 1, index.parent());
  }
}

void YDVariableGroupModel::updateRoot(YDVariable *root) {
  m_root = root;
  beginResetModel();
  endResetModel();
}

YDVarGroupDeletegate::YDVarGroupDeletegate(QObject *parent)
    : QStyledItemDelegate{parent} {}

QWidget *YDVarGroupDeletegate::createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
  Q_UNUSED(option);
  if (!index.isValid() || (index.column() != 0)) return nullptr;
  auto var = reinterpret_cast<YDVariable *>(index.internalPointer());
  if (var) {
    auto lineedit = static_cast<YDNameLineEdit *>(var->editor(parent));

    connect(lineedit, SIGNAL(editingFinished()), this,
            SLOT(commitAndCloseEditor()));
    return lineedit;
  }
  return nullptr;
}

void YDVarGroupDeletegate::setEditorData(QWidget *editor,
                                         const QModelIndex &index) const {
  if (!index.isValid() || (index.column() != 0)) return;

  YDNameLineEdit *YDEditor = qobject_cast<YDNameLineEdit *>(editor);
  auto str = index.data(Qt::DisplayRole).toString();
  YDEditor->setText(str);
}

void YDVarGroupDeletegate::setModelData(QWidget *editor,
                                        QAbstractItemModel *model,
                                        const QModelIndex &index) const {
  if (index.data(Qt::DisplayRole).canConvert<QString>()) {
    YDNameLineEdit *YDEditor = qobject_cast<YDNameLineEdit *>(editor);
    auto var = reinterpret_cast<YDVariable *>(index.internalPointer());
    var->setName(YDEditor->text());
  } else {
    QStyledItemDelegate::setModelData(editor, model, index);
  }
}

bool YDVarGroupDeletegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) {
  //禁止双击编辑
  if (event->type() == QEvent::MouseButtonDblClick) {
    return true;
  }
  return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize YDVarGroupDeletegate::sizeHint(const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  auto size = QStyledItemDelegate::sizeHint(option, index);
  return size;
}

void YDVarGroupDeletegate::commitAndCloseEditor() {
  YDNameLineEdit *editor = qobject_cast<YDNameLineEdit *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}
