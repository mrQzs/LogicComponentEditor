#include "YDDVariableModel.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QStyleOption>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDDVariableModel::YDDVariableModel(QObject *parent)
    : QAbstractTableModel{parent} {}

QVariant YDDVariableModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDDVariableModel::tr("名称");
      case 1:
        return YDDVariableModel::tr("数据类型");
      case 2:
        return YDDVariableModel::tr("最小值");
      case 3:
        return YDDVariableModel::tr("最大值");
      case 4:
        return YDDVariableModel::tr("当前值");
      case 5:
        return YDDVariableModel::tr("更新时间");
    }
  }
  return QVariant();
}

int YDDVariableModel::rowCount(const QModelIndex &) const {
  return (int)m_varList.size();
}

int YDDVariableModel::columnCount(const QModelIndex &) const { return 6; }

QVariant YDDVariableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  auto row = index.row();
  auto column = index.column();

  if (row < 0 || row >= m_varList.size()) return QVariant();

  auto var = m_varList[row];

  yd::proto::VariableRTValue varstate = m_stateMap.at(var->variable_id);

  QString time;
  if (varstate.ullTimestamp > 0)
    time = STRTQSTR(
        yd::CTimestamp::FormatTimeFromMicroseconds(varstate.ullTimestamp)
            .c_str());

  if (Qt::DisplayRole == role) {
    switch (column) {
      case 0:
        return STRTQSTR(var->variable_name.c_str());
      case 1:
        return YDHelper::getDataType(var->value_type);
      case 2:
        return STRTQSTR(var->min_value.c_str());
      case 3:
        return STRTQSTR(var->max_value.c_str());
      case 4:
        return STRTQSTR(varstate.strRealtimeValue.c_str());
      case 5:
        return time;
    }
  }

  return QVariant();
}

bool YDDVariableModel::setData(const QModelIndex &index, const QVariant &value,
                               int role) {
  return true;
}

Qt::ItemFlags YDDVariableModel::flags(const QModelIndex &index) const {
  if (index.isValid() && index.column() == 6)
    return Qt::ItemIsEnabled | Qt::ItemIsEditable;

  return Qt::ItemIsEnabled;
}

void YDDVariableModel::updateData(uint16 id) {
  m_varList.clear();
  m_varList = YDProjectManage::getAllVariables(id);

  YDDgHelper::getGroupedVariableValues(id, m_stateMap);

  beginResetModel();
  endResetModel();
}

vr::SystemVariable *YDDVariableModel::getVar(int row) { return m_varList[row]; }

YDDVarDeletedage::YDDVarDeletedage(QStringList btnNames, QWidget *parent)
    : QStyledItemDelegate(parent), m_btnNames(btnNames) {}

YDDVarDeletedage::~YDDVarDeletedage() {}

void YDDVarDeletedage::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const {
  QStyleOptionViewItem viewOption(option);
  initStyleOption(&viewOption, index);
  if (option.state.testFlag(QStyle::State_HasFocus))
    viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

  QStyledItemDelegate::paint(painter, viewOption, index);

  int nCount = m_btnNames.count();

  int w = nCount != 0 ? option.rect.width() / nCount : 0;
  if (w < 0) {
    return;
  }

  for (int i = 0; i < nCount; ++i) {
    QStyleOptionButton button;
    button.rect =
        option.rect.adjusted(4 + i * w, 4, -(w * (nCount - i - 1) + 4), -4);
    button.text = m_btnNames.at(i);
    button.state |= QStyle::State_Enabled;

    if (button.rect.contains(m_mousePoint)) {
      if (m_nType == 0) {
        button.state |= QStyle::State_MouseOver;
      } else if (m_nType == 1) {
        button.state |= QStyle::State_Sunken;
      }
    }

    QPushButton pushBtn;
    pushBtn.setStyleSheet(
        "QPushButton{border-width: 0px;\
                                position: absolute;\
                                left: 0px;\
                                top: 0px;\
                                max-width:120px; \
                                width:120px;\
                                height: 30px;\
                                background: inherit;\
                                background-color: rgba(255, 255, 255, 0);\
                                border-width: 1px;\
                                border-style: solid;\
                                border-color: red;\
                                border-radius: 10px;\
                                font-size: 11px;\
                                color: #000000;}\
                                QPushButton:hover{background-color:rgba(2, 182, 212, 1); color:#FFFFFF;}");

    pushBtn.style()->drawControl(QStyle::CE_PushButton, &button, painter,
                                 &pushBtn);
  }
}

bool YDDVarDeletedage::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {
  m_nType = -1;
  bool bRepaint = false;
  QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
  m_mousePoint = pEvent->pos();

  int nCount = m_btnNames.count();

  int w = nCount != 0 ? option.rect.width() / nCount : 0;
  if (w < 0) {
    return false;
  }

  for (int i = 0; i < nCount; ++i) {
    QStyleOptionButton button;
    button.rect =
        option.rect.adjusted(4 + i * w, 4, -(w * (nCount - i - 1) + 4), -4);

    if (!button.rect.contains(m_mousePoint)) continue;

    bRepaint = true;
    switch (event->type()) {
      case QEvent::MouseMove: {
        m_nType = 0;
      } break;
      case QEvent::MouseButtonPress: {
        m_nType = 1;
      } break;
      case QEvent::MouseButtonRelease: {
        emit sigPress(index);
      } break;
      default:
        break;
    }
  }

  return bRepaint;
}
