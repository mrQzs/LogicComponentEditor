#ifndef YDCONTROLMODEL_H
#define YDCONTROLMODEL_H

#include <QAbstractListModel>

class YDModuleTreeView;

class YDControlModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDControlModel(QObject *parent = nullptr);
  ~YDControlModel();
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  virtual QStringList mimeTypes() const override;
  virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;

 private:
  QStringList m_strlist;
};

#endif  // YDCONTROLMODEL_H
