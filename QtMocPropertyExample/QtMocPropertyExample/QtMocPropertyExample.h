#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtMocPropertyExample.h"
#include "ExPerson.h"

class QtMocPropertyExample : public QMainWindow
{
    Q_OBJECT

public:
    QtMocPropertyExample(QWidget *parent = nullptr);
    ~QtMocPropertyExample();

private slots:
    void onAgeChange(int val); //自定义的槽函数
    void onSpinValChange(int val);

    void onBtnClear(); //UI界面的槽函数
    void onBtnBoyInc();
    void onBtnGrilInc();
    void onClassInfo();

private:
    Ui::QtMocPropertyExampleClass ui;
    std::shared_ptr<ExPerson> m_boy;
    std::shared_ptr<ExPerson> m_girl;
};
