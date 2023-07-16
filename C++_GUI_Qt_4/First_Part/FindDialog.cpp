#include "FindDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

FindDialog::FindDialog(QWidget* parent)
    : QDialog(parent)
{
    m_label = new QLabel(tr("Find &what:"));
    m_lineEdit = new QLineEdit;

    m_label->setBuddy(m_lineEdit);

    m_caseCheckBox = new QCheckBox(tr("Match &case"));
    m_backwardCheckBox = new QCheckBox(tr("Search &backward"));

    m_findButton = new QPushButton(tr("Find"));
    m_findButton->setDefault(true);
    m_findButton->setEnabled(false);

    m_closeButton = new QPushButton(tr("Close"));

    connect(m_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableFindButton(QString)));
    connect(m_findButton, SIGNAL(clicked(bool)), this, SLOT(findClicked()));
    connect(m_closeButton, SIGNAL(clicked(bool)), this, SLOT(close())); // close默认行为是将窗口隐藏起来

    QHBoxLayout* topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(m_label);
    topLeftLayout->addWidget(m_lineEdit);

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(m_caseCheckBox);
    leftLayout->addWidget(m_backwardCheckBox);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_findButton);
    rightLayout->addWidget(m_closeButton);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());
    /*
        QWidget::sizeHint()是Qt框架中的一个函数，用于提供一个建议的窗口大小（尺寸）。

        在Qt中，当我们创建自定义的QWidget或派生自QWidget的小部件时，通常需要指定其初始大小。这个初始大小可以通过重写QWidget::sizeHint()函数来设置。

        sizeHint()函数的作用是返回一个QSize对象，表示小部件的建议大小。这个建议大小通常是基于小部件的内容、布局和其他因素计算得出的。当小部件被放置在父容器中或由布局管理器管理时，父容器或布局管理器会根据这个建议大小来调整小部件的大小和位置。

        当我们不显式设置小部件的大小时，布局管理器会根据小部件的sizeHint()函数返回的建议大小进行自动调整。如果我们设置了小部件的大小，布局管理器会尊重我们的设置。但是，在没有设置大小时，布局管理器会根据小部件的sizeHint()提供的建议大小来进行布局。

        重写sizeHint()函数可以根据小部件的特性和需求来提供合适的建议大小，以确保小部件在布局中能够正确地调整大小和布置。

        需要注意的是，sizeHint()函数提供的只是一个建议大小，父容器或布局管理器可以根据实际情况进行调整。如果我们希望设置小部件的固定大小，可以使用QWidget::setFixedSize()函数来实现。
    */
}

void FindDialog::findClicked()
{
    QString text = m_lineEdit->text();
    Qt::CaseSensitivity caseSen = m_caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    if (m_backwardCheckBox->isChecked())
    {
        emit findPrevious(text, caseSen);
    }
    else
    {
        emit findNext(text, caseSen);
    }
}

void FindDialog::enableFindButton(const QString& text)
{
    m_findButton->setEnabled(!text.isEmpty());
}

