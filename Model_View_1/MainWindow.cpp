#include "MainWindow.h"
#include "MyModel.h"
#include <QHeaderView>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, m_tableView{new QTableView{this}} {
    setCentralWidget(m_tableView);

    auto myModel = new MyModel{this};

    m_tableView->setModel(myModel);

    connect(myModel, &MyModel::editCompleted, this, &MainWindow::showWindowTitle);
}

void MainWindow::showWindowTitle(const QString &title)
{
    setWindowTitle(title);
}
