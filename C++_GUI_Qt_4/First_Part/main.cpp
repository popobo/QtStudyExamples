#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    window->setWindowTitle("Enter Your Age");

    QSlider* slider = new QSlider(Qt::Horizontal);
    QSpinBox* spinBox = new QSpinBox();

    slider->setRange(0, 130);
    spinBox->setRange(0, 130);

    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(spinBox);
    layout->addWidget(slider);

    window->setLayout(layout);
    window->show();

    return app.exec();
}
