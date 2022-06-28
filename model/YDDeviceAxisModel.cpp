#include "YDDeviceAxisModel.h"

#include <QComboBox>

#include "common/YDHelper.h"
#include "widget/YDNameLineEdit.h"

YDDeviceAxisModel::YDDeviceAxisModel(QObject *parent)
    : QAbstractTableModel{parent} {}

QVariant YDDeviceAxisModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return YDDeviceAxisModel::tr("轴序号");
      case 1:
        return YDDeviceAxisModel::tr("轴名称");
      case 2:
        return YDDeviceAxisModel::tr("是否使能");
      case 3:
        return YDDeviceAxisModel::tr("脉冲当量");
      case 4:
        return YDDeviceAxisModel::tr("最大速度");
      case 5:
        return YDDeviceAxisModel::tr("最大加速度");
      case 6:
        return YDDeviceAxisModel::tr("最大减速度");
      case 7:
        return YDDeviceAxisModel::tr("平停减速度");
      case 8:
        return YDDeviceAxisModel::tr("急停减速度");
      case 9:
        return YDDeviceAxisModel::tr("到位误差");
      case 10:
        return YDDeviceAxisModel::tr("到位超时");
      case 11:
        return YDDeviceAxisModel::tr("使用编码器");
      case 12:
        return YDDeviceAxisModel::tr("绝对值编码器");
      case 13:
        return YDDeviceAxisModel::tr("软限位启用");
      case 14:
        return YDDeviceAxisModel::tr("正向软限位");
      case 15:
        return YDDeviceAxisModel::tr("负向软限位");
      case 16:
        return YDDeviceAxisModel::tr("正向限位启用");
      case 17:
        return YDDeviceAxisModel::tr("负向限位启用");
      case 18:
        return YDDeviceAxisModel::tr("暂停模式");
      case 19:
        return YDDeviceAxisModel::tr("手控模式");
      case 20:
        return YDDeviceAxisModel::tr("回零优先级");
      case 21:
        return YDDeviceAxisModel::tr("自动回原点模式");
      case 22:
        return YDDeviceAxisModel::tr("搜索距离");
      case 23:
        return YDDeviceAxisModel::tr("复位移动速度");
      case 24:
        return YDDeviceAxisModel::tr("搜索速度(高速)");
      case 25:
        return YDDeviceAxisModel::tr("搜索速度(低速)");
      case 26:
        return YDDeviceAxisModel::tr("原点偏移量");
      case 27:
        return YDDeviceAxisModel::tr("原点捕获电平选中");
      case 28:
        return YDDeviceAxisModel::tr("停稳延时");
      case 29:
        return YDDeviceAxisModel::tr("备注");
      default:
        break;
    }
  }
  return QVariant();
}

int YDDeviceAxisModel::rowCount(const QModelIndex &parent) const {
  return (int)m_axisList.size();
}

int YDDeviceAxisModel::columnCount(const QModelIndex &parent) const {
  return 30;
}

QVariant YDDeviceAxisModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  if (index.row() >= m_axisList.size() || index.row() < 0) return QVariant();

  auto column = index.column();
  const auto &var = m_axisList.at(index.row());

  switch (column) {
    case 0:
      if (role == Qt::DisplayRole) return QString::number(var->index);
      break;
    case 1:
      if (role == Qt::DisplayRole)
        return QString::fromLocal8Bit(var->name.c_str());
      break;
    case 2:
      if (role == Qt::CheckStateRole)
        return var->enable;
      else if (role == Qt::DisplayRole)
        return YDDeviceAxisModel::tr("是");
      break;
    case 3:
      if (role == Qt::DisplayRole) return QString::number(var->equivalent);
      break;
    case 4:
      if (role == Qt::DisplayRole) return QString::number(var->max_velocity);
      break;
    case 5:
      if (role == Qt::DisplayRole)
        return QString::number(var->max_acceleration);
      break;
    case 6:
      if (role == Qt::DisplayRole)
        return QString::number(var->max_deceleration);
      break;
    case 7:
      if (role == Qt::DisplayRole)
        return QString::number(var->smooth_stop_deceleration);
      break;
    case 8:
      if (role == Qt::DisplayRole)
        return QString::number(var->urgent_stop_deceleration);
      break;
    case 9:
      if (role == Qt::DisplayRole) return QString::number(var->arrive_error);
      break;
    case 10:
      if (role == Qt::DisplayRole) return QString::number(var->arrive_timeout);
      break;
    case 11:
      if (role == Qt::CheckStateRole)
        return var->use_hw_encoder;
      else if (role == Qt::DisplayRole)
        return YDDeviceAxisModel::tr("是");
      break;
    case 12:
      if (role == Qt::CheckStateRole)
        return var->use_abs_encoder;
      else if (role == Qt::DisplayRole)
        return YDDeviceAxisModel::tr("是");
      break;
    case 13:
      if (role == Qt::CheckStateRole)
        return var->sw_limit.enable;
      else if (role == Qt::DisplayRole)
        return YDDeviceAxisModel::tr("是");
      break;
    case 14:
      if (role == Qt::DisplayRole)
        return QString::number(var->sw_limit.positive);
      break;
    case 15:
      if (role == Qt::DisplayRole)
        return QString::number(var->sw_limit.negative);
      break;
    case 16:
      if (role == Qt::CheckStateRole)
        return var->hw_limit.positive_enable;
      else if (role == Qt::DisplayRole)
        return YDDeviceAxisModel::tr("是");
      break;
    case 17:
      if (role == Qt::CheckStateRole)
        return var->hw_limit.negative_enable;
      else if (role == Qt::DisplayRole)
        return YDDeviceAxisModel::tr("是");
      break;
    case 18:
      if (role == Qt::DisplayRole) {
        switch (var->pause_mode) {
          case AXIS_PAUSEMODE_WAITFOR_MOVES_COMPLETED:
            return YDDeviceAxisModel::tr("自动模式");
          case AXIS_PAUSEMODE_SMOOTH_STOP_IMMEDIATELY:
            return YDDeviceAxisModel::tr("减停模式");
          case AXIS_PAUSEMODE_URGENT_STOP_IMMEDIATELY:
            return YDDeviceAxisModel::tr("急停模式");
          default:
            return YDDeviceAxisModel::tr("无暂停");
        }
      }
      break;
    case 19:
      if (role == Qt::DisplayRole) {
        switch (var->manual_control_mode + 1) {
          case AXIS_MANUALCTRL_HORIZONTAL_LEFTPOS_RIGHTNEG:
            return "平移_左正右负";
          case AXIS_MANUALCTRL_HORIZONTAL_LEFTNEG_RIGHTPOS:
            return "平移_左负右正";
          case AXIS_MANUALCTRL_VERTICAL_UPPOS_DOWNNEG:
            return "平移_上正下负";
          case AXIS_MANUALCTRL_VERTICAL_UPNEG_DOWNPOS:
            return "平移_上负下正";
          case AXIS_MANUALCTRL_ROTATE_CLOCKWISE_INCREASE:
            return "旋转_顺时针加";
          case AXIS_MANUALCTRL_ROTATE_CLOCKWISE_DECREASE:
            return "旋转_顺时针减";
          default:
            break;
        }
      }
      break;
    case 20:
      if (role == Qt::DisplayRole) return QString::number(var->home.priority);
      break;
    case 21:
      if (role == Qt::DisplayRole) {
        switch (var->home.mode) {
          case AXIS_HOMEMODE_NONE:
            return "不用回原点";
          case AXIS_HOMEMODE_CHECKSIGNAL_BY_POSITIVEMOVE_IF_NEGATIVELIMIT_ON:
            return "负限位触碰后正向查找";
          case AXIS_HOMEMODE_CHECKSIGNAL_BY_NEGATIVEMOVE_IF_POSITIVELIMIT_ON:
            return "正限位触碰后负向查找";
          case AXIS_HOMEMODE_CHECKSIGNAL_BY_ANTICLOCKWISEMOVE:
            return "逆时针(负方向查找)";
          case AXIS_HOMEMODE_CHECKSIGNAL_BY_CLOCKWISEMOVE:
            return "顺时针(正方向)查找";
          case AXIS_HOMEMODE_IF_POSITIVELIMIT_ON:
            return "正限位作为原点";
          case AXIS_HOMEMODE_IF_NEGATIVELIMIT_ON:
            return "负限位作为原点";
          default:
            break;
        }
      }
      break;
    case 22:
      if (role == Qt::DisplayRole)
        return QString::number(var->home.search_distance);
      break;
    case 23:
      if (role == Qt::DisplayRole)
        return QString::number(var->home.move_velocity);
      break;
    case 24:
      if (role == Qt::DisplayRole)
        return QString::number(var->home.search_high_velocity);
      break;
    case 25:
      if (role == Qt::DisplayRole)
        return QString::number(var->home.search_low_velocity);
      break;
    case 26:
      if (role == Qt::DisplayRole)
        return QString::number(var->home.origin_offset);
      break;
    case 27:
      if (role == Qt::DisplayRole) {
        switch (var->home.capture_electric_level + 1) {
          case ELECTRIC_CAPTURE_RISING_EDGE:
            return "上升沿";
          case ELECTRIC_CAPTURE_FALLING_EDGE:
            return "下降沿";
          default:
            break;
        }
      }
      break;
    case 28:
      if (role == Qt::DisplayRole) return QString::number(var->stoped_delay);
      break;
    case 29:
      if (role == Qt::DisplayRole)
        return QString::fromLocal8Bit(var->remarks.c_str());
      break;
    default:
      break;
  }

  return QVariant();
}

bool YDDeviceAxisModel::setData(const QModelIndex &index, const QVariant &value,
                                int role) {
  switch (role) {
    case Qt::CheckStateRole: {
      auto column = index.column();
      const auto &var = m_axisList.at(index.row());
      switch (column) {
        case 1:
          var->name = QSTRTSTR(value.toString());
          break;
        case 2:
          var->enable = !var->enable;
          break;
        case 3:
          var->equivalent = value.toDouble();
        case 4:
          var->max_velocity = value.toDouble();
        case 5:
          var->max_acceleration = value.toDouble();
        case 6:
          var->max_deceleration = value.toDouble();
        case 7:
          var->smooth_stop_deceleration = value.toDouble();
        case 8:
          var->urgent_stop_deceleration = value.toDouble();
        case 9:
          var->arrive_error = value.toDouble();
        case 10:
          var->arrive_timeout = value.toUInt();
        case 11:
          var->use_hw_encoder = !var->use_hw_encoder;
          break;
        case 12:
          var->use_abs_encoder = !var->use_abs_encoder;
          break;
        case 13:
          var->sw_limit.enable = !var->sw_limit.enable;
          break;
        case 14:
          var->sw_limit.positive = value.toDouble();
          break;
        case 15:
          var->sw_limit.negative = value.toDouble();
          break;
        case 16:
          var->hw_limit.positive_enable = !var->hw_limit.positive_enable;
          break;
        case 17:
          var->hw_limit.negative_enable = !var->hw_limit.negative_enable;
          break;
        case 22:
          var->home.search_distance = value.toDouble();
          break;
        case 23:
          var->home.move_velocity = value.toDouble();
          break;
        case 24:
          var->home.search_high_velocity = value.toDouble();
          break;
        case 25:
          var->home.search_low_velocity = value.toDouble();
          break;
        case 26:
          var->home.origin_offset = value.toDouble();
          break;
        case 28:
          var->stoped_delay = value.toUInt();
          break;
        case 29:
          var->remarks = QSTRTSTR(value.toString());
          break;
      }
      emit dataChanged(index, index);
      return true;
    } break;
    default: {
      auto column = index.column();
      const auto &var = m_axisList.at(index.row());
      switch (column) {
        case 1:
          var->name = QSTRTSTR(value.toString());
          break;
        case 3:
          var->equivalent = value.toDouble();
          break;
        case 4:
          var->max_velocity = value.toDouble();
          break;
        case 5:
          var->max_acceleration = value.toDouble();
          break;
        case 6:
          var->max_deceleration = value.toDouble();
          break;
        case 7:
          var->smooth_stop_deceleration = value.toDouble();
          break;
        case 8:
          var->urgent_stop_deceleration = value.toDouble();
          break;
        case 9:
          var->arrive_error = value.toDouble();
          break;
        case 10:
          var->arrive_timeout = value.toUInt();
          break;
        case 14:
          var->sw_limit.positive = value.toDouble();
          break;
        case 15:
          var->sw_limit.negative = value.toDouble();
          break;
        case 18:
          var->pause_mode = value.toUInt();
          break;
        case 19:
          var->manual_control_mode = value.toUInt();
          break;
        case 20:
          var->home.priority = value.toUInt();
          break;
        case 21:
          var->home.mode = value.toUInt();
          break;
        case 22:
          var->home.search_distance = value.toDouble();
          break;
        case 23:
          var->home.move_velocity = value.toDouble();
          break;
        case 24:
          var->home.search_high_velocity = value.toDouble();
          break;
        case 25:
          var->home.search_low_velocity = value.toDouble();
          break;
        case 26:
          var->home.origin_offset = value.toDouble();
          break;
        case 27:
          var->home.capture_electric_level = value.toUInt();
          break;
        case 28:
          var->stoped_delay = value.toUInt();
          break;
        case 29:
          var->remarks = QSTRTSTR(value.toString());
          break;
      }
      emit dataChanged(index, index);
      return true;
    }
  }

  return false;
}

Qt::ItemFlags YDDeviceAxisModel::flags(const QModelIndex &index) const {
  if (index.isValid()) {
    switch (index.column()) {
      case 0:
        return Qt::ItemIsEnabled;
      case 2:
      case 11:
      case 12:
      case 13:
      case 16:
      case 17:
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  } else
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void YDDeviceAxisModel::updateModel(
    const std::vector<yd::dev::MCAxis *> &list) {
  m_axisList = list;
  beginResetModel();
  endResetModel();
}

void YDDeviceAxisModel::clearModel() {
  m_axisList.clear();
  beginResetModel();
  endResetModel();
}

QSize YDDeviceAxisDelegate::sizeHint(const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *YDDeviceAxisDelegate::createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
  switch (index.column()) {
    case 2:
    case 11:
    case 12:
    case 13:
    case 16:
    case 17:
      return QStyledItemDelegate::createEditor(parent, option, index);
    case 18: {
      QComboBox *editor = new QComboBox(parent);
      QStringList itemList{"无暂停", "自动模式", "减停模式", "急停模式"};

      editor->addItems(itemList);
      editor->setEditable(false);
      return editor;
    }
    case 19: {
      QComboBox *editor = new QComboBox(parent);
      QStringList itemList{"平移_左正右负", "平移_左负右正", "平移_上正下负",
                           "平移_上负下正", "旋转_顺时针加", "旋转_顺时针减"};
      editor->addItems(itemList);
      editor->setEditable(false);
      return editor;
    }
    case 20: {
      QComboBox *editor = new QComboBox(parent);
      for (int i = 0; i <= 20; i++) {
        editor->addItem(QString::number(i));
      }
      editor->setEditable(false);
      return editor;
    }
    case 21: {
      QComboBox *editor = new QComboBox(parent);
      QStringList itemList{"不用回原点",           "负限位触碰后正向查找",
                           "正限位触碰后负向查找", "逆时针(负方向查找)",
                           "顺时针(正方向)查找",   "正限位作为原点",
                           "负限位作为原点"};
      editor->addItems(itemList);
      editor->setEditable(false);
      return editor;
    }
    case 27: {
      QComboBox *editor = new QComboBox(parent);
      QStringList itemList{"上升沿", "下降沿"};
      editor->addItems(itemList);
      editor->setEditable(false);
      return editor;
    }
    default: {
      auto *editor = new QLineEdit(parent);
      connect(editor, &QLineEdit::editingFinished, this,
              &YDDeviceAxisDelegate::commitAndCloseEditor2);
      return editor;
    }
  }

  return QStyledItemDelegate::createEditor(parent, option, index);
}

void YDDeviceAxisDelegate::setEditorData(QWidget *editor,
                                         const QModelIndex &index) const {
  switch (index.column()) {
    case 2:
    case 11:
    case 12:
    case 13:
    case 16:
    case 17:
      break;
    case 18:
    case 19:
    case 20:
    case 21:
    case 27: {
      QString value = index.model()->data(index, Qt::DisplayRole).toString();
      QComboBox *comboBox = static_cast<QComboBox *>(editor);
      comboBox->setCurrentText(value);
      break;
    }
    default: {
      auto str = index.data().toString();
      auto *ed = static_cast<QLineEdit *>(editor);
      ed->setText(str);
    }
  }
}

void YDDeviceAxisDelegate::setModelData(QWidget *editor,
                                        QAbstractItemModel *model,
                                        const QModelIndex &index) const {
  switch (index.column()) {
    case 2:
    case 11:
    case 12:
    case 13:
    case 16:
    case 17:
      break;
    case 18:
    case 19:
    case 20:
    case 21:
    case 27: {
      QComboBox *comboBox = static_cast<QComboBox *>(editor);
      model->setData(index, comboBox->currentIndex(), Qt::EditRole);
      break;
    }
    default: {
      auto *ed = static_cast<QLineEdit *>(editor);
      model->setData(index, ed->text());
    }
  }
}

void YDDeviceAxisDelegate::commitAndCloseEditor() {
  auto *ed = static_cast<QComboBox *>(sender());
  emit commitData(ed);
  emit closeEditor(ed);
}

void YDDeviceAxisDelegate::commitAndCloseEditor2() {
  auto *ed = static_cast<QLineEdit *>(sender());
  emit commitData(ed);
  emit closeEditor(ed);
}
