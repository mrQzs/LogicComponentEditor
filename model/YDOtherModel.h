#ifndef YDOTHERMODEL_H
#define YDOTHERMODEL_H

#include <QAbstractListModel>

class YDModuleTreeView;

class YDOtherModel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit YDOtherModel(QObject *parent = nullptr);
  ~YDOtherModel();
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  virtual QStringList mimeTypes() const override;
  virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;

 private:
  QStringList m_strlist;
};

#endif  // YDOTHERMODEL_H
