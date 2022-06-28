#include "YDProperty.h"

#include <QTextEdit>

#include "modules/YDModule.h"
#include "widget/YDNameLineEdit.h"

YDProperty::YDProperty(YDProperty *parent) : m_parent{parent} {}

YDProperty::~YDProperty() { qDeleteAll(m_childs); }

bool YDProperty::hasEditor() const { return false; }

QWidget *YDProperty::editor(QWidget *parent) {
  Q_UNUSED(parent);
  return nullptr;
}

QVariant YDProperty::defaultValue() const { return QVariant(); }

QVariant YDProperty::value(YDModule *m) const {
  Q_UNUSED(m);
  return QVariant();
}

QJsonValue YDProperty::toJson(YDModule *m) const {
  return QJsonValue::fromVariant(value(m));
}

QStringList YDProperty::function(YDModule *m) const {
  Q_UNUSED(m);
  return QStringList();
}

void YDProperty::updateEditor(YDModule *m) { Q_UNUSED(m); }

void YDProperty::updateWidget(YDModule *m) { Q_UNUSED(m); }

void YDProperty::setValue(YDModule *m, QVariant value) {
  Q_UNUSED(m);
  Q_UNUSED(value);
}

bool YDProperty::isShow() const { return true; }

const YDProperty *YDProperty::parent() const { return m_parent; }

const YDProperty *YDProperty::child(int index) const {
  Q_ASSERT((index > 0) && (index < m_childs.size()));
  return m_childs.at(index);
}

int YDProperty::count() const { return m_childs.size(); }

int YDProperty::row() const { return m_parent ? m_parent->indexof(this) : 0; }

int YDProperty::indexof(const YDProperty *item) const {
  return m_childs.indexOf(item);
}
