#ifndef YDCYLINDERMODEL_H
#define YDCYLINDERMODEL_H

#include <QAbstractListModel>

class YDCylinderModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDCylinderModel(QObject *parent = nullptr);
  ~YDCylinderModel();

  void updateModel();

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  int rowCount(const QModelIndex &parent) const override;

  QVariant data(const QModelIndex &index, int role) const override;
};

#endif  // YDCYLINDERMODEL_H
