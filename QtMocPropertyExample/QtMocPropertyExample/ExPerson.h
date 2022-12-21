#pragma once

#include <QObject>

class ExPerson: public QObject
{
	Q_OBJECT

		// 类的附加信息：名称-值
		Q_CLASSINFO("author", "bo")
		Q_CLASSINFO("version", "1.0.0")
		Q_CLASSINFO("info", "Qt6 Meta Object and Propery Example")

		//属性定义
		Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged) //属性age; 方法getAge()和setAge()对其读写; 设置信号ageChanged()
		Q_PROPERTY(QString name MEMBER m_name) //属性name 与类成员变量m_name关联
		Q_PROPERTY(int score MEMBER m_score)

public:
	explicit ExPerson(QString name, QObject* prarent = nullptr);

public:
	int getAge(); //属性age READ函数
	void setAge(int value); //属性age WRITE函数

	void incAge(); //单独写一个接口，与属性无关

signals:
	void ageChanged(int value); //属性age发生改变的信号函数

private:
	int m_age = 5;
	QString m_name;
	int m_score = 50;
};

