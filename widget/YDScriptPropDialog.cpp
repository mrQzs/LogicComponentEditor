#include "YDScriptPropDialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "common/YDLogger.h"
#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDScriptPropDialog::YDScriptPropDialog(QWidget *parent)
    : QDialog{parent},
      m_name{new QLabel(this)},
      m_nameEdit{new YDNameLineEdit(this)},
      m_type{new QLabel(this)},
      m_typeBox{new QComboBox(this)},
      m_way{new QLabel(this)},
      m_wayBox{new QComboBox(this)},
      m_time{new QLabel(this)},
      m_timeEdit{new QLineEdit(this)},
      m_data{new QLabel(this)},
      m_dataEdit{new QLineEdit(this)},
      m_ok{new QPushButton(this)},
      m_cancel{new QPushButton(this)},
      m_isAdd{false} {
  auto grid = new QGridLayout;
  grid->addWidget(m_name, 0, 0, 1, 1);
  grid->addWidget(m_nameEdit, 0, 1, 1, 1);

  grid->addWidget(m_type, 1, 0, 1, 1);
  grid->addWidget(m_typeBox, 1, 1, 1, 1);

  grid->addWidget(m_way, 2, 0, 1, 1);
  grid->addWidget(m_wayBox, 2, 1, 1, 1);

  grid->addWidget(m_time, 3, 0, 1, 1);
  grid->addWidget(m_timeEdit, 3, 1, 1, 1);

  grid->addWidget(m_data, 4, 0, 1, 1);
  grid->addWidget(m_dataEdit, 4, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_ok);
  hlay->addWidget(m_cancel);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(10, 10, 10, 10);
  vlay->setSpacing(10);
  vlay->addLayout(grid);
  vlay->addLayout(hlay);

  m_name->setText(YDScriptPropDialog::tr("脚本名称"));
  m_type->setText(YDScriptPropDialog::tr("脚本类型"));
  m_way->setText(YDScriptPropDialog::tr("执行方式"));
  m_time->setText(YDScriptPropDialog::tr("定时间隔"));
  m_data->setText(YDScriptPropDialog::tr("数据缓存大小(字节)"));
  m_ok->setText(YDScriptPropDialog::tr("确认"));
  m_cancel->setText(YDScriptPropDialog::tr("取消"));
  m_data->setVisible(false);
  m_dataEdit->setVisible(false);
  m_dataEdit->setEnabled(false);
  m_dataEdit->setText("0");

  QStringList type;
  type << "VB.NET"
       << "C#.NET";
  //       << "C/C++";
  m_typeBox->addItems(type);

  QStringList way;
  way << YDScriptPropDialog::tr("执行一次")
      << YDScriptPropDialog::tr("循环执行")
      << YDScriptPropDialog::tr("定时执行");
  m_wayBox->addItems(way);
  m_timeEdit->setText("0");
  m_timeEdit->setEnabled(false);

  connect(m_wayBox, &QComboBox::currentIndexChanged, this,
          &YDScriptPropDialog::slotWayCurrentIndexChange);
  connect(m_ok, &QPushButton::clicked, this,
          &YDScriptPropDialog::slotOkClicked);

  connect(m_cancel, &QPushButton::clicked, this,
          &YDScriptPropDialog::slotCancelClicked);
}

void YDScriptPropDialog::setScritp(yd::adv::ExtendScript *script) {
  m_script = script;
  m_nameEdit->setText(STRTQSTR(m_script->script_name));

  if (m_script->script_type < 1)
    m_typeBox->setCurrentIndex(0);
  else
    m_typeBox->setCurrentIndex(m_script->script_type - SCRIPT_TYPE_VB_NET);
  m_wayBox->setCurrentIndex(m_script->execute_mode -
                            SCRIPT_EXECUTE_METHOD_ONCE);
  m_timeEdit->setText(QString::number(m_script->timer_interval));
  //  m_dataEdit->setText(QString::number(m_script->data_cache_size));
}

int YDScriptPropDialog::getType() { return m_typeBox->currentIndex(); }

void YDScriptPropDialog::setAddOrUpdate(bool flag) {
  m_isAdd = flag;
  if (flag) {
    auto list = YDProjectManage::getScripts();
    auto name = QString("%1%2").arg(YDScriptPropDialog::tr("自定义脚本"),
                                    QString::number(list.size() + 1));
    m_nameEdit->setText(name);
    m_typeBox->setCurrentIndex(0);
    m_wayBox->setCurrentIndex(0);

    m_script = new yd::adv::ExtendScript;
  }
}

void YDScriptPropDialog::slotOkClicked() {
  if (m_nameEdit->text().isEmpty()) {
    QMessageBox::warning(nullptr, YDScriptPropDialog::tr("错误"),
                         YDScriptPropDialog::tr("名字不能为空!"));
    return;
  }
  if (m_timeEdit->text().isEmpty()) {
    QMessageBox::warning(nullptr, YDScriptPropDialog::tr("错误"),
                         YDScriptPropDialog::tr("定时间隔不能为空!"));
    return;
  }

  auto name = QSTRTSTR(m_nameEdit->text());
  if (name == HOME_MOVE_SCRIPT_NAME) {
    QMessageBox::warning(nullptr, YDScriptPropDialog::tr("错误"),
                         YDScriptPropDialog::tr("名称已重复!"));
    return;
  }

  if (m_isAdd) {
    YDProjectManage::createScript(name, m_script);
    YDLogger::info(
        YDScriptPropDialog::tr("添加脚本: %1 成功").arg(m_nameEdit->text()));
  } else {
    auto result = YDProjectManage::updateScript(m_script);
    result = YDProjectManage::updateScript(m_script);
    switch (result) {
      case -1:
        QMessageBox::warning(nullptr, YDScriptPropDialog::tr("提示"),
                             YDScriptPropDialog::tr("修改自定义脚本名称失败!"));
        return;
      case 0:
        YDLogger::info(YDScriptPropDialog::tr("修改自定义脚本名称成功!"));
        break;
      case 1:
        QMessageBox::warning(nullptr, YDScriptPropDialog::tr("提示"),
                             YDScriptPropDialog::tr("自定义脚本名称有重复!"));
        return;
      default:
        break;
    }
  }
  m_script->script_name = YDHelper::qstringToString(m_nameEdit->text());
  m_script->script_type = m_typeBox->currentIndex() + SCRIPT_TYPE_VB_NET;
  m_script->execute_mode =
      m_wayBox->currentIndex() + SCRIPT_EXECUTE_METHOD_ONCE;
  m_script->timer_interval = m_timeEdit->text().toUInt();
  m_script->data_cache_size = m_dataEdit->text().toUInt();
  accept();
}

void YDScriptPropDialog::slotCancelClicked() { reject(); }

void YDScriptPropDialog::slotWayCurrentIndexChange(int index) {
  if (index != 2) {
    m_timeEdit->setText("0");
    m_timeEdit->setEnabled(false);
  } else {
    m_timeEdit->setEnabled(true);
  }
}
