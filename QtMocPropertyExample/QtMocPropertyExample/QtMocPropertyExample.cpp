#include "QtMocPropertyExample.h"
#include <QMetaProperty>

QtMocPropertyExample::QtMocPropertyExample(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_boy = std::make_shared<ExPerson>("张三");
    m_boy->setProperty("score", 90);
    m_boy->setProperty("age", 20);
    m_boy->setProperty("sex", "Boy"); //动态属性
    connect(m_boy.get(), &ExPerson::ageChanged, this, &QtMocPropertyExample::onAgeChange);
    
    m_girl = std::make_shared<ExPerson>("张丽");
    m_girl->setProperty("score", 80);
    m_girl->setProperty("age", 20);
    m_girl->setProperty("sex", "Girl"); //动态属性
    connect(m_girl.get(), &ExPerson::ageChanged, this, &QtMocPropertyExample::onAgeChange);

    ui.spinBoxBoy->setProperty("isBoy", true); //动态属性
    ui.spinBoxGirl->setProperty("isBoy", false); //动态属性
    connect(ui.spinBoxGirl, SIGNAL(valueChanged(int)), this, SLOT(onSpinValChange(int)));
    connect(ui.spinBoxBoy, SIGNAL(valueChanged(int)), this, SLOT(onSpinValChange(int)));

    connect(ui.pushButtonBoyAdd, SIGNAL(clicked()), this, SLOT(onBtnBoyInc()));
    connect(ui.pushButtonGirlAdd, SIGNAL(clicked()), this, SLOT(onBtnGrilInc()));
    
    connect(ui.pushButtonMetaObject, SIGNAL(clicked()), this, SLOT(onClassInfo()));
    connect(ui.pushButtonClean, SIGNAL(clicked()), this, SLOT(onBtnClear()));

    setWindowTitle(QObject::tr("元对象MetaObject和(含动态)属性Propert的用法"));
}

QtMocPropertyExample::~QtMocPropertyExample()
{}


void QtMocPropertyExample::onAgeChange(int val) {
    Q_UNUSED(val); //表明val未被使用，避免警告
    
    ExPerson* person = qobject_cast<ExPerson*>(sender());
    QString name = person->property("name").toString();
    QString sex = person->property("sex").toString();
    int age = person->getAge();
    
    ui.textEdit->append(name + ", " + sex + QString::asprintf(", age=%d", age));
}

void QtMocPropertyExample::onSpinValChange(int val)
{
    Q_UNUSED(val);

    QSpinBox* spin = qobject_cast<QSpinBox*>(sender());
    if (spin->property("isBoy").toBool())
        m_boy->setAge(ui.spinBoxBoy->value());
    else
        m_girl->setAge(ui.spinBoxGirl->value());
}

void QtMocPropertyExample::onBtnClear()
{
    ui.textEdit->clear();
}

void QtMocPropertyExample::onBtnBoyInc()
{
    m_boy->incAge();
}

void QtMocPropertyExample::onBtnGrilInc()
{
    m_girl->incAge();
}

void QtMocPropertyExample::onClassInfo()
{
    const QMetaObject* meta = m_boy->metaObject();
    
    ui.textEdit->clear();
    ui.textEdit->append("===Meta Object Info===");
    ui.textEdit->append(QString("class name:%1\n").arg(meta->className()));
    ui.textEdit->append("property");

    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);
        const char* propName = prop.name();
        QString propValue = m_boy->property(propName).toString();
        ui.textEdit->append(QString("property name=%1, value=%2").arg(propName).arg(propValue));
    }

    ui.textEdit->append("");
    ui.textEdit->append("classInfo:");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++i) {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui.textEdit->append(QString("classInfo name=%1, value=%2").arg(classInfo.name()).arg(classInfo.value()));
    }
}
