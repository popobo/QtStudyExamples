#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow {
    Q_OBJECT

  public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

    void newDocument();

  private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void save();

    void on_actionPrint_triggered();

    void on_actionFont_triggered();

  private:
    Ui::Notepad *ui;

    QString currentFile;
};
#endif // NOTEPAD_H
