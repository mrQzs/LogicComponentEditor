#ifndef YDMOVEMODEL_H
#define YDMOVEMODEL_H

#include <QAbstractListModel>

class YDModuleTreeView;

class YDMoveModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDMoveModel(QObject *parent = nullptr);
  ~YDMoveModel();
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  virtual QStringList mimeTypes() const override;
  virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;

 private:
  QStringList m_strlist;
};

#endif  // YDMOVEMODEL_H
