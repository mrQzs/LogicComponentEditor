#include "YDDAxisVarModel.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QStyleOption>
#include <QToolTip>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDDAxisVarModel::YDDAxisVarModel(QObject *parent)
    : QAbstractTableModel{parent} {
  memset(&m_coords, 0, sizeof(yd::COORDS));
}

QVariant YDDAxisVarModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDDAxisVarModel::tr("名称");
      case 1:
        return YDDAxisVarModel::tr("位置");
      case 2:
        return YDDAxisVarModel::tr("操作");
    }
  }
  return QVariant();
}

int YDDAxisVarModel::rowCount(const QModelIndex &) const {
  return (int)m_coords.ucNumber;
}

int YDDAxisVarModel::columnCount(const QModelIndex &) const { return 3; }

QVariant YDDAxisVarModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  int row = index.row();
  int column = index.column();

  if (Qt::DisplayRole == role) {
    switch (column) {
      case 0:
        return m_axisNames[row];
      case 1:
        return m_values[row];
    }
  }

  return QVariant();
}

bool YDDAxisVarModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  if (Qt::UserRole == role) {
    if (index.column() == 1) {
      auto str = value.toString();
      if (!str.isEmpty()) {
        m_values[index.row()] = str;
      }
    }
  }
  return true;
}

Qt::ItemFlags YDDAxisVarModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::ItemIsEditable;
  switch (index.column()) {
    case 0:
      return Qt::ItemIsEditable;
  }

  return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void YDDAxisVarModel::updateData(const yd::COORDS &coords) {
  m_coords = coords;
  m_axisNames.clear();
  auto axlist = YDProjectManage::getAxisList();
  for (int i = 0; i < m_coords.ucNumber; ++i) {
    auto coor = m_coords.arrCoords[i];
    for (auto ax : axlist) {
      if (ax->device_id == coor.uiDeviceId && ax->card_index == coor.usCard &&
          ax->axis_index == coor.usAxis) {
        m_axisNames.push_back(QString::fromLocal8Bit(ax->axis_name.c_str()));
        std::string value = std::string(coor.refTarget.szValue);
        m_values.push_back(QString::fromLocal8Bit(value.c_str()));
      }
    }
  }

  if (m_initValues.isEmpty()) m_initValues = m_values;

  beginResetModel();
  endResetModel();
}

void YDDAxisVarModel::updateData(const QStringList &values) {
  m_values = values;
  beginResetModel();
  endResetModel();
}

QStringList YDDAxisVarModel::getValues() const { return m_values; }

QStringList YDDAxisVarModel::getInitValues() const { return m_initValues; }

YDDAxisVarDeletegate::YDDAxisVarDeletegate(QStringList btnNames,
                                           QWidget *parent)
    : QStyledItemDelegate(parent), m_btnNames(btnNames) {}

YDDAxisVarDeletegate::~YDDAxisVarDeletegate() {}

void YDDAxisVarDeletegate::paint(QPainter *painter,
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
                                QPushButton:hover{border-color:rgba(2, 182, 212, 1);}");

    pushBtn.style()->drawControl(QStyle::CE_PushButton, &button, painter,
                                 &pushBtn);
  }
}

bool YDDAxisVarDeletegate::editorEvent(QEvent *event, QAbstractItemModel *model,
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
        break;
      }
      case QEvent::MouseButtonPress: {
        m_nType = 1;
        switch (i) {
          case 1:
            emit sigStartJog(index);
            break;
          case 2:
            emit sigStartDJog(index);
            break;
        }
        break;
      }
      case QEvent::MouseButtonRelease: {
        switch (i) {
          case 0: {
            emit sigShow(index);
            break;
          }
          case 1: {
            emit sigStopJog(index);
            break;
          }
          case 2: {
            emit sigStopDJog(index);
            break;
          }
          case 3: {
            emit sigMove(index);
            break;
          }
        }
        break;
      }
      default:
        break;
    }
  }

  return bRepaint;
}

YDDAxisVarDeletegate2::YDDAxisVarDeletegate2(QWidget *parent)
    : QStyledItemDelegate(parent) {}

QWidget *YDDAxisVarDeletegate2::createEditor(QWidget *parent,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;
  Q_UNUSED(option);
  auto lineedit = new QLineEdit(parent);

  connect(lineedit, SIGNAL(editingFinished()), this,
          SLOT(commitAndCloseEditor()));
  return lineedit;
}

void YDDAxisVarDeletegate2::setEditorData(QWidget *editor,
                                          const QModelIndex &index) const {
  if (!index.isValid()) return;

  auto lineedit = qobject_cast<QLineEdit *>(editor);
  auto str = index.data(Qt::DisplayRole).toString();
  lineedit->setText(str);
}

void YDDAxisVarDeletegate2::setModelData(QWidget *editor,
                                         QAbstractItemModel *model,
                                         const QModelIndex &index) const {
  if (!index.isValid()) return;

  auto lineedit = qobject_cast<QLineEdit *>(editor);
  model->setData(index, lineedit->text(), Qt::UserRole);
}

void YDDAxisVarDeletegate2::commitAndCloseEditor() {
  QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}
