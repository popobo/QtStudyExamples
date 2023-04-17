#include "MyModel.h"
#include <QBrush>
#include <QFont>
#include <QTime>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent) {
}

int MyModel::rowCount(const QModelIndex &parent) const { return 2; }

int MyModel::columnCount(const QModelIndex &parent) const { return 3; }

QVariant MyModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole && checkIndex(index)) {
        return m_girdData[row][col];
    }

    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value,
                      int role) {
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        m_girdData[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emit a joined string
        QString result;
        for(int row = 0; row < ROWS; row++){
            for(int col = 0; col < COLS; col++){
                result += m_girdData[row][col] + " ";
            }
        }
        emit editCompleted(result);
    }
    return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

