#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QTimer>

const int ROWS = 2;
const int COLS = 3;

class MyModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    explicit MyModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

  private:
    QString m_girdData[ROWS][COLS];

  signals:
    void editCompleted(const QString &);
};

#endif // MYMODEL_H
