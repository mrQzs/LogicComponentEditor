#include "YDProjectDialog.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "YDLogo.h"
#include "YDNameDialog.h"
#include "YDPicButton.h"
#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "widget/YDNameLineEdit.h"

YDProjectDialog::YDProjectDialog(QWidget *parent)
    : QDialog{parent},
      m_logo{new YDLogo(this)},
      m_widget1{new QWidget(this)},
      m_lab{new QLabel(m_widget1)},
      m_listW{new QListWidget(m_widget1)},
      m_widget2{new QWidget(this)},
      m_lab2{new QLabel(m_widget2)},
      m_create{new YDPicButton(m_widget2)},
      m_createPDlg{new YDNameDialog(this)} {
  setWindowTitle(YDProjectDialog::tr("打开/创建项目"));
  m_createPDlg->setBtnName(YDProjectDialog::tr("创建"));

  init();

  auto hlay = new QHBoxLayout;
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_widget1);
  hlay->addWidget(m_widget2);
  hlay->setStretch(0, 3);
  hlay->setStretch(1, 2);

  auto hlay2 = new QHBoxLayout;
  hlay2->setContentsMargins(256, 15, 256, 10);
  hlay2->setSpacing(0);
  hlay2->addWidget(m_logo);

  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(0, 0, 0, 0);
  vlay->setSpacing(0);
  vlay->addLayout(hlay2);
  vlay->addLayout(hlay);

  resize(1024, 680);

  connect(m_create, &YDPicButton::clicked, this,
          &YDProjectDialog::slotCreateClicked);

  connect(m_createPDlg, &YDNameDialog::finished, this,
          &YDProjectDialog::slotDiaFinished);

  connect(m_listW, &QListWidget::clicked, this,
          &YDProjectDialog::slotItemClicked);
}

QString YDProjectDialog::getProjectPath() {
  return QCoreApplication::applicationDirPath() + "/configs";
}

QString YDProjectDialog::getProjectName() { return m_name; }

void YDProjectDialog::slotCreateClicked() { m_createPDlg->open(); }

void YDProjectDialog::slotDiaFinished() {
  if (QDialog::Accepted == m_createPDlg->result()) {
    m_name = m_createPDlg->getName();
    auto name = YDHelper::qstringToString(m_name);

    if (YDProjectManage::CreateProject(name)) accept();
  }
}

void YDProjectDialog::slotItemClicked(const QModelIndex &index) {
  auto item = m_listW->item(index.row());
  m_name = item->text();
  auto name = YDHelper::qstringToString(m_name);
  if (YDProjectManage::openProject(name)) accept();
}

void YDProjectDialog::init() {
  initWidget1();
  initWidget2();
}

void YDProjectDialog::initWidget1() {
  auto vlay = new QVBoxLayout(m_widget1);
  vlay->setContentsMargins(20, 20, 20, 20);
  vlay->setSpacing(0);
  vlay->addWidget(m_lab);
  vlay->addWidget(m_listW);

  QFont font;
  font.setPixelSize(24);
  m_lab->setFixedHeight(60);
  m_lab->setFont(font);

  m_lab->setText(YDProjectDialog::tr("打开最近使用的项目"));
  m_listW->setStyleSheet("background:#f0f0f0;border:none;color:#000009;");

  std::vector<std::string> names;
  YDProjectManage::enumuerateProjects(names);

  QFont itemf;
  itemf.setPixelSize(18);

  for (int i = 0; i < names.size(); ++i) {
    m_listW->addItem(QString::fromLocal8Bit(names[i].c_str()));
    m_listW->item(i)->setFont(itemf);
  }
}

void YDProjectDialog::initWidget2() {
  auto vlay = new QVBoxLayout(m_widget2);
  vlay->setContentsMargins(20, 20, 20, 20);
  vlay->setSpacing(0);
  vlay->addWidget(m_lab2);
  vlay->addWidget(m_create);
  vlay->addStretch();

  QFont font;
  font.setPixelSize(24);
  m_lab2->setFixedHeight(60);
  m_lab2->setFont(font);

  m_create->setFixedHeight(70);
  m_create->setText("创建新项目");
  m_create->setPic(":/Icon/Project.png");

  m_lab2->setText(YDProjectDialog::tr("开始使用"));
}
