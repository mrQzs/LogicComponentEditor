#ifndef YDDEVICEMODEL_H
#define YDDEVICEMODEL_H

#include <QAbstractItemModel>

class YDDeviceModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDDeviceModel(QObject *parent = nullptr);
  ~YDDeviceModel();

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  int rowCount(const QModelIndex &parent) const override;

  QVariant data(const QModelIndex &index, int role) const override;
};

#endif  // YDDEVICEMODEL_H
