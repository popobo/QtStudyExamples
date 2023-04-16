#include "MyModel.h"
#include <QBrush>
#include <QFont>
#include <QTime>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent), m_timer(new QTimer(this)) {
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &MyModel::timerHint);
    m_timer->start();
}

int MyModel::rowCount(const QModelIndex &parent) const { return 2; }

int MyModel::columnCount(const QModelIndex &parent) const { return 3; }

QVariant MyModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole && row == 0 && col == 0) {
        return QTime::currentTime().toString();
    }

    return QVariant();
}

void MyModel::timerHint() {
    // we identify the top left cell
    QModelIndex topLeft = createIndex(0, 0);
    // emit a signal to make the view reread identified data
    emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}
