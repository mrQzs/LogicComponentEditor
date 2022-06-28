#ifndef YDAXISLISTMODEL_H
#define YDAXISLISTMODEL_H

#include <QAbstractListModel>

class YDAxisListModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDAxisListModel(QObject *parent = nullptr);
  ~YDAxisListModel();
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

 public:
  void updateData();

 private:
  QStringList m_strlist;
};

#endif  // YDAXISLISTMODEL_H
