#ifndef YDIOMODEL_H
#define YDIOMODEL_H

#include <QAbstractListModel>

class YDModuleTreeView;

class YDIOModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDIOModel(QObject *parent = nullptr);
  ~YDIOModel();
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  virtual QStringList mimeTypes() const override;
  virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;

 private:
  QStringList m_strlist;
};

#endif  // YDIOMODEL_H
