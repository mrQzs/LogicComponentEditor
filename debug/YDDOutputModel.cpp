#include "YDDOutputModel.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "YDDgHelper.h"
#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDDOutputModel::YDDOutputModel(QObject *parent)
    : QAbstractTableModel{parent}, m_id{0} {
  updateData();
}

QVariant YDDOutputModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDDOutputModel::tr("名称");
      case 1:
        return YDDOutputModel::tr("状态");
      case 2:
        return YDDOutputModel::tr("标识");
    }
  }

  return QVariant();
}

int YDDOutputModel::rowCount(const QModelIndex &) const {
  auto infosize = m_ioInfos.size();

  if (0 == infosize) return 0;

  if (0 == m_id) {
    infosize = infosize / 2 + 1;
  } else
    infosize = infosize - (infosize / 2 + 1);

  return (int)infosize;
}

int YDDOutputModel::columnCount(const QModelIndex &) const { return 3; }

QVariant YDDOutputModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  auto size = m_ioInfos.size() / 2 + 1;
  if (0 != m_id) size = m_ioInfos.size() - size;

  if (index.row() >= size || index.row() < 0) return QVariant();

  auto column = index.column();
  auto row = index.row();
  if (0 != m_id) row = row + (int)m_ioInfos.size() / 2 + 1;

  const auto &var = m_ioInfos.at(row);

  uint64 ullData = ((uint64)var->device_id << 32) + var->io_index;

  auto state = false;
  auto itor = m_mapState.find(ullData);
  if (itor != m_mapState.end()) state = (*itor).second;

  if (role == Qt::DisplayRole) {
    switch (column) {
      case 0:
        return STRTQSTR(var->io_name.c_str());
      case 1:
        return state ? "True" : "False";
      case 2:
        return STRTQSTR(var->io_label.c_str());
    }
  } else if ((Qt::UserRole + 1) == role) {
    return state;
  }

  return QVariant();
}

bool YDDOutputModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {
  return true;
}

Qt::ItemFlags YDDOutputModel::flags(const QModelIndex &) const {
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void YDDOutputModel::updateData() {
  m_mapState.clear();
  YDDgHelper::getDOStates(0, m_mapState);

  m_ioInfos = YDProjectManage::getDOInfos();
  beginResetModel();
  endResetModel();
}

void YDDOutputModel::setGroup(int id) { m_id = id; }

void YDDOutputModel::SlotButtonClicked(const QModelIndex &index) {
  const auto &var = m_ioInfos.at(index.row());
  uint64 ullData = ((uint64)var->device_id << 32) + var->io_index;

  auto state = false;
  auto itor = m_mapState.find(ullData);
  if (itor != m_mapState.end()) state = (*itor).second;

  uint16 usIndex = var->io_index % 1000;
  uint16 usType = var->io_index / 1000;

  YDDgHelper::sendDOState(var->device_id, usIndex, usType, !state);

  m_ioInfos = YDProjectManage::getDOInfos();
}

YDDOutputDeletegate::YDDOutputDeletegate(QWidget *parent)
    : QStyledItemDelegate(parent) {}

void YDDOutputDeletegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const {
  QStyleOptionViewItem viewOption(option);
  initStyleOption(&viewOption, index);
  if (option.state.testFlag(QStyle::State_HasFocus))
    viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

  QStyledItemDelegate::paint(painter, viewOption, index);

  int nCount = 1;

  int w = nCount != 0 ? option.rect.width() / nCount : 0;
  if (w < 0) {
    return;
  }

  auto rect = option.rect.adjusted(4, 4, -4, -4);

  if (index.data(Qt::UserRole + 1).toBool())
    painter->setBrush(QBrush(Qt::green));
  else
    painter->setBrush(QBrush(Qt::gray));

  painter->setPen(Qt::NoPen);
  painter->drawRect(rect);
}

bool YDDOutputDeletegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) {
  switch (event->type()) {
    case QEvent::MouseButtonPress:
      emit sigClicked(index);
      break;
    default:
      break;
  }
  return QStyledItemDelegate::editorEvent(event, model, option, index);
}
