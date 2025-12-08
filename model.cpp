#include "model.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>

Model::Model(QObject *parent) : QObject(parent), a_(0), b_(50), c_(100)
{
    loadFromSettings();
}

int Model::getA() const
{
    return a_;
}

int Model::getB() const
{
    return b_;
}

int Model::getC() const
{
    return c_;
}

void Model::setA(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    int oldA = a_;
    int oldB = b_;
    int oldC = c_;

    a_ = value;

    if (a_ > b_) {
        b_ = a_;
        if (b_ > c_) {
            c_ = b_;
        }
    }

    if (oldA != a_ || oldB != b_ || oldC != c_) {
        saveToSettings();
        emit valuesChanged();
    }

    qDebug() << "Model: A = " << a_ << "B = " << b_ << "C = " << c_;
}

void Model::setB(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    int oldA = a_;
    int oldB = b_;
    int oldC = c_;

    if (value < a_) b_ = a_;
    else if (value > c_) b_ = c_;
    else b_ = value;

    if (oldA != a_ || oldB != b_ || oldC != c_) {
        saveToSettings();
        emit valuesChanged();
    }

    qDebug() << "Model: A = " << a_ << "B = " << b_ << "C = " << c_;
}

void Model::setC(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    int oldA = a_;
    int oldB = b_;
    int oldC = c_;

    c_ = value;

    if (c_ < b_) {
        b_ = c_;
        if (a_ > b_) {
            a_ = b_;
        }
    }

    if (oldA != a_ || oldB != b_ || oldC != c_) {
        saveToSettings();
        emit valuesChanged();
    }

    qDebug() << "Model: A = " << a_ << "B = " << b_ << "C = " << c_;
}

int Model::getMinB() const
{
    return a_;
}

int Model::getMaxB() const
{
    return c_;
}

void Model::saveToSettings()
{
    QString filePath = "/Users/dmitry/Desktop/ООП/laba3_2/model_settings.txt";

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << a_ << "\n" << b_ << "\n" << c_;
        file.close();
        qDebug() << "SAVED to" << filePath << ": A=" << a_ << " B=" << b_ << " C=" << c_;
    } else {
        qDebug() << "ERROR: Could not save to" << filePath;
    }
}

void Model::loadFromSettings()
{
    QString filePath = "/Users/dmitry/Desktop/ООП/laba3_2/model_settings.txt";

    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;

        if (!in.atEnd()) {
            line = in.readLine();
            a_ = line.toInt();
        }
        if (!in.atEnd()) {
            line = in.readLine();
            b_ = line.toInt();
        }
        if (!in.atEnd()) {
            line = in.readLine();
            c_ = line.toInt();
        }

        file.close();
        qDebug() << "LOADED: A=" << a_ << " B=" << b_ << " C=" << c_;
    } else {
        // Файла нет - значения по умолчанию
        a_ = 0;
        b_ = 50;
        c_ = 100;
        qDebug() << "DEFAULT: A=0 B=50 C=100";
    }

    // Все равно применяем ограничения
    if (a_ < 0) a_ = 0;
    if (a_ > 100) a_ = 100;
    if (c_ < 0) c_ = 0;
    if (c_ > 100) c_ = 100;
    if (b_ < a_) b_ = a_;
    if (b_ > c_) b_ = c_;
}
