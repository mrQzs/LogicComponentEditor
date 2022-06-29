#include "YDBuildOptDialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/YDHelper.h"
#include "core/YDProjectManage.h"

YDBuildOptDialog::YDBuildOptDialog(QWidget *parent)
    : QDialog{parent},
      m_struct{new QLabel(this)},
      m_structBox{new QComboBox(this)},
      m_cpu{new QLabel(this)},
      m_cpuBox{new QComboBox(this)},
      m_ok{new QPushButton(this)},
      m_cancel{new QPushButton(this)} {
  setWindowTitle(YDBuildOptDialog::tr("编译选项"));

  auto grid = new QGridLayout;
  grid->addWidget(m_struct, 0, 0, 1, 1);
  grid->addWidget(m_structBox, 0, 1, 1, 1);
  grid->addWidget(m_cpu, 1, 0, 1, 1);
  grid->addWidget(m_cpuBox, 1, 1, 1, 1);

  auto hlay = new QHBoxLayout;
  hlay->addStretch();
  hlay->addWidget(m_ok);
  hlay->addWidget(m_cancel);
  hlay->addStretch();

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(10, 10, 10, 10);
  vlay->setSpacing(15);
  vlay->addLayout(grid);
  vlay->addLayout(hlay);

  QStringList way;
  way << "x64"
      << "x86";
  m_cpuBox->addItems(way);

  m_struct->setText(YDBuildOptDialog::tr("目标框架:"));
  m_cpu->setText(YDBuildOptDialog::tr("目标CPU:"));
  m_ok->setText(YDBuildOptDialog::tr("确认"));
  m_cancel->setText(YDBuildOptDialog::tr("取消"));

  m_struct->setAlignment(Qt::AlignCenter);
  m_cpu->setAlignment(Qt::AlignCenter);

  connect(m_ok, &QPushButton::clicked, this, &YDBuildOptDialog::slotOkClicked);
  connect(m_cancel, &QPushButton::clicked, this,
          &YDBuildOptDialog::slotCancelClicked);

  connect(m_cpuBox, &QComboBox::currentIndexChanged, this,
          &YDBuildOptDialog::slotCpuChanged);
  std::vector<std::string> fram;
  YDProjectManage::enumFrameworks(TARGET_CPU_X64, fram);
  QStringList list = YDHelper::getAvaliableFram(fram);
  m_structBox->addItems(list);
}

int YDBuildOptDialog::getStruct() const { return m_structBox->currentIndex(); }

int YDBuildOptDialog::getWay() const { return m_cpuBox->currentIndex(); }

void YDBuildOptDialog::slotOkClicked(bool) {
  if (m_structBox->currentText().isEmpty()) {
    QMessageBox::warning(nullptr, YDBuildOptDialog::tr("错误"),
                         YDBuildOptDialog::tr("没有可用的.Net库!"));
  } else
    accept();
}

void YDBuildOptDialog::slotCancelClicked(bool) { reject(); }

void YDBuildOptDialog::slotCpuChanged(int index) {
  m_structBox->clear();
  if (0 == index) {
    std::vector<std::string> fram;
    YDProjectManage::enumFrameworks(TARGET_CPU_X64, fram);
    QStringList list;
    for (auto i : fram) list.push_back(STRTQSTR(i.c_str()));
    m_structBox->addItems(list);
  } else {
    std::vector<std::string> fram;
    YDProjectManage::enumFrameworks(TARGET_CPU_X86, fram);
    QStringList list;
    for (auto i : fram) list.push_back(STRTQSTR(i.c_str()));
    m_structBox->addItems(list);
  }
}
