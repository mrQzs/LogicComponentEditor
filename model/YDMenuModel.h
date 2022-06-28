#ifndef YDMENUMODEL_H
#define YDMENUMODEL_H

#include <QAbstractItemModel>
#include <QStyledItemDelegate>

class YDTask;

class YDMenuModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit YDMenuModel(YDTask *root, QObject *parent = nullptr);
  ~YDMenuModel();

 public:
  void updateModel();

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent) const override;
  QModelIndex parent(const QModelIndex &child) const override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const;

 public:
  bool insertRows(int row, int count, const QModelIndex &parent);
  bool removeRows(int row, int count, const QModelIndex &parent);

  QModelIndex addTree(const QModelIndex &parent);
  QModelIndex addTree(int row, const QModelIndex &parent);
  void removeTree(QModelIndex &parent);

  YDTask *getRoot();

 public:
  // drag and drap
  Qt::DropActions supportedDropActions() const;
  QStringList mimeTypes() const;
  QMimeData *mimeData(const QModelIndexList &indexes) const;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                    int column, const QModelIndex &parent);

 private:
  YDTask *m_root;
};

class YDMenuDeletegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  YDMenuDeletegate(QObject *parent = nullptr);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index);

 protected:
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;

 private slots:
  void commitAndCloseEditor();
};

#endif  // YDMENUMODEL_H
