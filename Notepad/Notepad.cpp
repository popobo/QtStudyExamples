#include "Notepad.h"
#include "./ui_Notepad.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

Notepad::Notepad(QWidget *parent) : QMainWindow(parent), ui(new Ui::Notepad) {
    ui->setupUi(this);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::save);
}

Notepad::~Notepad() { delete ui; }

void Notepad::newDocument() {}

void Notepad::on_actionNew_triggered() {}

// name can not change
void Notepad::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::on_actionSave_as_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty())
        return;
    QFile file{fileName};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot save as file: " + file.errorString());
        return;
    }

    QTextStream out{&file};
    out << ui->textEdit->toPlainText();
    file.close();

    setWindowTitle(fileName);
    currentFile = fileName;
}

void Notepad::on_actionExit_triggered() {}

void Notepad::save() {
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty())
            return;
    } else {
        fileName = currentFile;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionPrint_triggered() {
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif QT_CONFIG(printer)
}

void Notepad::on_actionFont_triggered() {
    bool fontSelected = false;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}
