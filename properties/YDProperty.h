#ifndef YDPROPERTY_H
#define YDPROPERTY_H

#include <QCoreApplication>
#include <QJsonValue>
#include <QVariant>
#include <functional>

class YDModule;

class YDProperty {
  Q_DECLARE_TR_FUNCTIONS(YDModule)
 public:
  YDProperty(YDProperty *parent = nullptr);
  virtual ~YDProperty();

 public:
  // virtual
  virtual QString name() const = 0;
  virtual QString codeName() const = 0;
  virtual bool hasEditor() const;
  virtual QWidget *editor(QWidget *parent);
  virtual QVariant defaultValue() const;
  virtual QVariant value(YDModule *m) const;
  virtual QJsonValue toJson(YDModule *m) const;
  virtual QStringList function(YDModule *m) const;

  virtual void updateEditor(YDModule *m);
  virtual void updateWidget(YDModule *m);
  virtual void setValue(YDModule *m, QVariant value);
  virtual bool isShow() const;

 public:
  const YDProperty *parent() const;
  const YDProperty *child(int index) const;
  int count() const;
  int row() const;
  int indexof(const YDProperty *item) const;

 protected:
  YDProperty *m_parent;
  QList<const YDProperty *> m_childs;
};

template <class T>
class YDPropertyType : public YDProperty {
 public:
  inline YDPropertyType(YDProperty *parent = nullptr) : YDProperty(parent) {}

 public:
  virtual QString name() const { return QString(); }
  virtual QString codeName() const { return QString(); }
  inline QVariant value(YDModule *m) const override { return get(m); }
  inline void setValue(YDModule *m, QVariant value) override {
    return set(m, value.value<T>());
  }
  inline bool hasEditor() const override { return true; }

 protected:
  virtual T get(YDModule *m) const = 0;
  virtual void set(YDModule *m, T value) = 0;
};

#endif  // YDPROPERTY_H
