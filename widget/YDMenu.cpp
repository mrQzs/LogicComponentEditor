#include "YDMenu.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "YDMenuHead.h"

YDMenu::YDMenu(QWidget *parent)
    : QWidget{parent}, m_head{new YDMenuHead(this)}, m_widget{nullptr} {
  auto hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_head);

  setMinimumHeight(30);
  connect(m_head, &YDMenuHead::sigClicked, this, &YDMenu::slotClicked);
}

void YDMenu::setIcon(const QString &str) { m_head->setIcon(str); }

void YDMenu::setText(const QString &text) { m_head->setText(text); }

void YDMenu::setWidget(QWidget *w) {
  if (w) {
    delete layout();
    m_widget = w;
    addWidget();
    m_widget->hide();
  }
}

void YDMenu::setHaveChild(bool b) { m_head->haveChild(b); }

void YDMenu::setItemModel(bool b) { m_head->setItemModel(b); }

void YDMenu::slotClicked(bool b) {
  if (b && m_widget)
    m_widget->show();
  else if (!b && m_widget)
    m_widget->hide();

  emit sigClicked();
}

void YDMenu::addWidget() {
  m_head->haveChild(true);
  auto vlay = new QVBoxLayout(this);
  vlay->setContentsMargins(0, 0, 0, 0);
  vlay->setSpacing(0);
  vlay->addWidget(m_head);
  vlay->addWidget(m_widget);
}
