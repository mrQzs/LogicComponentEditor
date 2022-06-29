#include "YDDAxisVarWidget.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "RapidJsonHelper.h"
#include "YDDAxisVarModel.h"
#include "YDDAxisVarView.h"
#include "YDDgHelper.h"
#include "YDMoveControlWidget.h"
#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "core/YDVariable.h"

YDDAxisVarWidget::YDDAxisVarWidget(QWidget *parent)
    : QWidget{parent},
      m_tree{new QTreeWidget(this)},
      m_view{new YDDAxisVarView(this)},
      m_model{new YDDAxisVarModel(this)},
      m_btn1{new QPushButton(this)} {
  m_tree->setFixedWidth(200);
  m_view->horizontalHeader()->setStretchLastSection(true);
  m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  auto hhlay = new QHBoxLayout;
  hhlay->addStretch();
  hhlay->addWidget(m_btn1);
  hhlay->addStretch();

  auto vvlay = new QVBoxLayout;
  vvlay->addLayout(hhlay);
  vvlay->addWidget(m_view);

  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_tree);
  hlay->addLayout(vvlay);

  m_view->setModel(m_model);

  m_btn1->setText(YDDAxisVarWidget::tr("更新坐标"));

  QStringList list;
  list << YDDAxisVarWidget::tr("示数") << YDDAxisVarWidget::tr("正向")
       << YDDAxisVarWidget::tr("反向") << YDDAxisVarWidget::tr("运动");

  m_view->setMouseTracking(true);
  m_deletegate = new YDDAxisVarDeletegate(list, m_view);
  m_view->setItemDelegateForColumn(2, m_deletegate);

  m_deletegate2 = new YDDAxisVarDeletegate2(m_view);
  m_view->setItemDelegateForColumn(1, m_deletegate2);

  initTree();

  connect(m_tree, &QTreeWidget::clicked, this,
          &YDDAxisVarWidget::slotViewSingleClicked);

  connect(m_deletegate, &YDDAxisVarDeletegate::sigShow, this,
          &YDDAxisVarWidget::slotShowClicked);
  connect(m_deletegate, &YDDAxisVarDeletegate::sigStartJog, this,
          &YDDAxisVarWidget::slotStartJogMove);
  connect(m_deletegate, &YDDAxisVarDeletegate::sigStartJog, this,
          &YDDAxisVarWidget::slotStopJogMove);
  connect(m_deletegate, &YDDAxisVarDeletegate::sigStartDJog, this,
          &YDDAxisVarWidget::slotStartDJogMove);
  connect(m_deletegate, &YDDAxisVarDeletegate::sigStopDJog, this,
          &YDDAxisVarWidget::slotStopDJogMove);
  connect(m_deletegate, &YDDAxisVarDeletegate::sigMove, this,
          &YDDAxisVarWidget::slotMoveClicked);

  updateData();
}

void YDDAxisVarWidget::initTree() {
  auto head = m_tree->headerItem();
  head->setText(0, YDDAxisVarWidget::tr("多轴变量列表"));

  auto root = YDProjectManage::getVarRoot();
  auto vars = root->childs();
  for (int i = 0; i < vars.size(); ++i) {
    auto item = new QTreeWidgetItem(m_tree);
    item->setText(0, vars[i]->name());
    item->setData(0, Qt::UserRole + 1, 0);

    auto cvars = vars[i]->childs();
    for (int j = 0; j < cvars.size(); ++j) {
      auto citem = new QTreeWidgetItem(item);
      citem->setText(0, cvars[j]->name());
      citem->setData(0, Qt::UserRole + 1, 0);

      // auto list = YDProjectManage::getAllVariables(cvars[j]->groupId());
      auto list = YDProjectManage::getAllVariables(cvars[j]->groupId());

      for (int y = 0; y < list.size(); ++y) {
        if (list[y]->value_type == DATA_TYPE_AXIS_COORD) {
          auto yitem = new QTreeWidgetItem(citem);
          YDVarCast cast;
          cast.ptr = list[y];
          yitem->setData(0, Qt::UserRole + 1, cast.i);
          yitem->setText(
              0, STRTQSTR(list[y]->variable_name.c_str()));
        }
      }
    }
  }
}

void YDDAxisVarWidget::updateData() {
  auto index = m_tree->currentIndex();
  YDVarCast cast;
  cast.i = index.data(Qt::UserRole + 1).toLongLong();
  auto var = cast.ptr;
  if (var) {
    yd::COORDS m_coords;
    memset(&m_coords, 0, sizeof(yd::COORDS));
    yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &m_coords);

    m_model->updateData(m_coords);
  }
}

void YDDAxisVarWidget::slotViewSingleClicked(const QModelIndex &) {
  updateData();
}

void YDDAxisVarWidget::slotShowClicked(const QModelIndex &index) {
  YDVarCast cast;
  cast.i = m_tree->currentIndex().data(Qt::UserRole + 1).toLongLong();
  auto var = cast.ptr;
  if (var) {
    yd::COORDS coords;
    memset(&coords, 0, sizeof(yd::COORDS));
    yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &coords);

    auto axis = getAxis(coords, index.row());
    yd::proto::AxisState axisState;
    YDDgHelper::getAxisState(axis->device_id, axis->axis_index, &axisState);
    auto list = m_model->getValues();
    list[index.row()] = QString::number(axisState.encoder_position);
    m_model->updateData(list);
  }
}

void YDDAxisVarWidget::slotStartJogMove(const QModelIndex &index) {
  YDVarCast cast;
  cast.i = m_tree->currentIndex().data(Qt::UserRole + 1).toLongLong();
  auto var = cast.ptr;
  if (var) {
    yd::COORDS coords;
    memset(&coords, 0, sizeof(yd::COORDS));
    yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &coords);
    auto row = index.row();
    auto axis = getAxis(coords, row);

    std::vector<yd::dev::MCAxisMoveSetup *> list;
    YDProjectManage::getMotionAxisMoveSetups(list);

    dev::MCAxisMoveSetup *move = nullptr;
    for (auto ms : list) {
      if (ms->device_id == axis->device_id &&
          ms->axis_index == axis->axis_index) {
        move = ms;
        break;
      }
    }

    if (move) {
      double value = 0.5 * move->max_manual_velocity;
      std::string speed = QString::number(value).toUtf8().toStdString();
      YDDgHelper::startJogMove(axis->device_id, axis->axis_index, false, speed,
                               1);
    }
  }
}

void YDDAxisVarWidget::slotStopJogMove(const QModelIndex &index) {
  YDVarCast cast;
  cast.i = m_tree->currentIndex().data(Qt::UserRole + 1).toLongLong();
  auto var = cast.ptr;
  if (var) {
    yd::COORDS coords;
    memset(&coords, 0, sizeof(yd::COORDS));
    yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &coords);
    auto row = index.row();
    auto axis = getAxis(coords, row);
    YDDgHelper::stopAxisMove(axis->device_id, axis->axis_index, true);
  }
}

void YDDAxisVarWidget::slotStartDJogMove(const QModelIndex &index) {
  YDVarCast cast;
  cast.i = m_tree->currentIndex().data(Qt::UserRole + 1).toLongLong();
  auto var = cast.ptr;
  if (var) {
    yd::COORDS coords;
    memset(&coords, 0, sizeof(yd::COORDS));
    yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &coords);
    auto row = index.row();
    auto axis = getAxis(coords, row);

    std::vector<yd::dev::MCAxisMoveSetup *> list;
    YDProjectManage::getMotionAxisMoveSetups(list);

    dev::MCAxisMoveSetup *move = nullptr;
    for (auto ms : list) {
      if (ms->device_id == axis->device_id &&
          ms->axis_index == axis->axis_index) {
        move = ms;
        break;
      }
    }

    if (move) {
      double value = 0.5 * move->max_manual_velocity;
      std::string speed = QString::number(value).toUtf8().toStdString();
      YDDgHelper::startJogMove(axis->device_id, axis->axis_index, false, speed,
                               2);
    }
  }
}

void YDDAxisVarWidget::slotStopDJogMove(const QModelIndex &index) {
  YDVarCast cast;
  cast.i = m_tree->currentIndex().data(Qt::UserRole + 1).toLongLong();
  auto var = cast.ptr;
  if (var) {
    yd::COORDS coords;
    memset(&coords, 0, sizeof(yd::COORDS));
    yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &coords);
    auto row = index.row();
    auto axis = getAxis(coords, row);
    YDDgHelper::stopAxisMove(axis->device_id, axis->axis_index, true);
  }
}

void YDDAxisVarWidget::slotMoveClicked(const QModelIndex &index) {
  YDVarCast cast;
  cast.i = m_tree->currentIndex().data(Qt::UserRole + 1).toLongLong();
  auto var = cast.ptr;
  if (var) {
    yd::COORDS coords;
    memset(&coords, 0, sizeof(yd::COORDS));
    yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &coords);
    auto row = index.row();
    auto axis = getAxis(coords, row);

    std::vector<yd::dev::MCAxisMoveSetup *> list;
    YDProjectManage::getMotionAxisMoveSetups(list);

    dev::MCAxisMoveSetup *move = nullptr;
    for (auto ms : list) {
      if (ms->device_id == axis->device_id &&
          ms->axis_index == axis->axis_index) {
        move = ms;
        break;
      }
    }

    if (move) {
      std::string val = m_model->getInitValues().at(row).toUtf8().constData();
      double value = 0.5 * move->max_manual_velocity;
      std::string speed = QString::number(value).toUtf8().toStdString();

      YDDgHelper::startRelativeMove(axis->device_id, axis->axis_index, false,
                                    val, false, speed, 1);
    }
  }
}

void YDDAxisVarWidget::slotUpdateAxis(bool) {
  auto index = m_view->currentIndex();
  if (index.isValid()) {
    YDVarCast cast;
    cast.i = index.data(Qt::UserRole + 1).toLongLong();
    auto var = cast.ptr;
    if (var) {
      yd::COORDS coords;
      memset(&coords, 0, sizeof(yd::COORDS));
      yd::CRapidJsonHelper::Json2AxisCoords(var->init_value, &coords);

      auto values = m_model->getValues();

      for (int i = 0; i < coords.ucNumber; ++i) {
        auto coor = coords.arrCoords[i];
        auto str = values[i];
        auto data = str.toUtf8().constData();
        //        if (!str.isEmpty())
        //          YDHelper::copyData(coor.refTarget.szValue, data,
        //          str.size());
      }

      yd::CRapidJsonHelper::AxisCoords2Json(&coords, var->init_value);

      YDDgHelper::setSingleVariableValue(var->variable_id, var->init_value);
    }
  }
}

yd::dev::MCAxisInfo *YDDAxisVarWidget::getAxis(const COORDS &coords, int row) {
  dev::MCAxisInfo *p = nullptr;
  auto axlist = YDProjectManage::getAxisList();
  auto coor = coords.arrCoords[row];
  for (auto ax : axlist) {
    if (ax->device_id == coor.uiDeviceId && ax->card_index == coor.usCard &&
        ax->axis_index == coor.usAxis) {
      p = ax;
      break;
    }
  }

  return p;
}
