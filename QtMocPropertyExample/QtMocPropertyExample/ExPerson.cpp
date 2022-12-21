#include "ExPerson.h"

ExPerson::ExPerson(QString name, QObject * prarent) : QObject(prarent) {
    m_name = name;
}

int ExPerson::getAge()
{
    return m_age;
}

void ExPerson::setAge(int value)
{
    m_age = value;
    emit ageChanged(m_age); //∑¢…‰–≈∫≈
}

void ExPerson::incAge()
{
    ++m_age;
    emit ageChanged(m_age);
}
