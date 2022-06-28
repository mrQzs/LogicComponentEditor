#ifndef YDSCRIPTMODEL_H
#define YDSCRIPTMODEL_H

#include <QAbstractItemModel>

class YDScriptModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDScriptModel(QObject *parent = nullptr);
  ~YDScriptModel();

 public:
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const override;

 public:
  void updatedata();

 private:
  QStringList m_strlist;
};

#endif  // YDSCRIPTMODEL_H
