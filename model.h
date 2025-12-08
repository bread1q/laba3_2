#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject
{
    Q_OBJECT

private:
    int a_;
    int b_;
    int c_;

    void applyConstraints();

public:
    Model(QObject *parent = nullptr);
    int getA() const;
    int getB() const;
    int getC() const;

    void setA(int value);
    void setB(int value);
    void setC(int value);

signals:
    void valuesChanged();
};

#endif // MODEL_H
