#include "TextFinder.h"
#include "./ui_TextFinder.h"
#include <QFile>
#include <QTextStream>

TextFinder::TextFinder(QWidget *parent)
    : QWidget(parent), ui(new Ui::TextFinder) {
    ui->setupUi(this);
    loadTextFile();
}

TextFinder::~TextFinder() { delete ui; }

void TextFinder::on_findButton_clicked() {
    QString searchString = ui->lineEdit->text();
    ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
}

void TextFinder::loadTextFile() {
    QFile input_file(":/input.txt");
    input_file.open(QIODevice::ReadOnly);

    QTextStream in_stream(&input_file);
    QString line = in_stream.readAll();
    ui->textEdit->setPlainText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}
