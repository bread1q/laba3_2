#include "model.h"
#include <QDebug>

Model::Model(QObject *parent) : QObject(parent), a_(0), b_(50), c_(100)
{

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

    if (oldA != a_ || oldB != b_ || oldC != c_) emit valuesChanged();

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

    if (oldA != a_ || oldB != b_ || oldC != c_) emit valuesChanged();

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

    if (oldA != a_ || oldB != b_ || oldC != c_) emit valuesChanged();

    qDebug() << "Model: A = " << a_ << "B = " << b_ << "C = " << c_;
}
