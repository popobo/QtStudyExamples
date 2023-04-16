#include "MyModel.h"
#include <QApplication>
#include <QHeaderView>
#include <QTableView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTableView tableView;
    MyModel myModel{nullptr};

    tableView.setModel(&myModel);
    tableView.show();

    return a.exec();
}
