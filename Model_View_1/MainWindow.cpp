#include "MainWindow.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, m_treeView{new QTreeView{this}},
      m_standardItemModel{new QStandardItemModel{this}} {
  setCentralWidget(m_treeView);

  auto preparedRow = prepareRow("first", "second", "third");
  auto item = m_standardItemModel->invisibleRootItem();
  item->appendRow(preparedRow);

  auto secondRow = prepareRow("111", "222", "333");
  preparedRow.first()->appendRow(secondRow);

  m_treeView->setModel(m_standardItemModel);
  m_treeView->expandAll();
}

QList<QStandardItem *> MainWindow::prepareRow(const QString &first,
                                              const QString &second,
                                              const QString &third) const {
  return {new QStandardItem{first}, new QStandardItem{second},
          new QStandardItem{third}};
}

MainWindow::~MainWindow() { delete m_treeView; }
