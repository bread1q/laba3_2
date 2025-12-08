#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(this)
{
    ui->setupUi(this);

    connect(ui->spinBox_A, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxAChanged(int)));
    connect(ui->spinBox_B, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxBChanged(int)));
    connect(ui->spinBox_C, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxCChanged(int)));

    connect(ui->horizontalSlider_A, SIGNAL(valueChanged(int)), this, SLOT(onSliderAChanged(int)));
    connect(ui->horizontalSlider_B, SIGNAL(valueChanged(int)), this, SLOT(onSliderBChanged(int)));
    connect(ui->horizontalSlider_C, SIGNAL(valueChanged(int)), this, SLOT(onSliderCChanged(int)));

    connect(ui->lineEdit_A, &QLineEdit::editingFinished, [this]() { onLineEditAChanged(); });
    connect(ui->lineEdit_B, &QLineEdit::editingFinished, [this]() { onLineEditBChanged(); });
    connect(ui->lineEdit_C, &QLineEdit::editingFinished, [this]() { onLineEditCChanged(); });

    connect(&model, SIGNAL(valuesChanged()), this, SLOT(onModelChanged()));

    onModelChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSpinBoxAChanged(int value)
{
    model.setA(value);
}

void MainWindow::onSpinBoxBChanged(int value)
{
    model.setB(value);
    int newValue = model.getB();

    if (newValue != value) {
        ui->spinBox_B->blockSignals(true);
        ui->spinBox_B->setValue(newValue);
        ui->spinBox_B->blockSignals(false);
    }
}

void MainWindow::onSpinBoxCChanged(int value)
{
    model.setC(value);
}

void MainWindow::onModelChanged()
{

    ui->lineEdit_A->setText(QString::number(model.getA()));
    ui->lineEdit_B->setText(QString::number(model.getB()));
    ui->lineEdit_C->setText(QString::number(model.getC()));

    ui->horizontalSlider_A->setValue(model.getA());
    ui->horizontalSlider_B->setValue(model.getB());
    ui->horizontalSlider_C->setValue(model.getC());

    ui->spinBox_A->blockSignals(true);
    ui->spinBox_B->blockSignals(true);
    ui->spinBox_C->blockSignals(true);

    ui->spinBox_A->setValue(model.getA());
    ui->spinBox_B->setValue(model.getB());
    ui->spinBox_C->setValue(model.getC());

    ui->spinBox_A->blockSignals(false);
    ui->spinBox_B->blockSignals(false);
    ui->spinBox_C->blockSignals(false);

    ui->horizontalSlider_B->setMinimum(model.getMinB());
    ui->horizontalSlider_B->setMaximum(model.getMaxB());
}

void MainWindow::onSliderAChanged(int value)
{
    model.setA(value);
}

void MainWindow::onSliderBChanged(int value)
{
    model.setB(value);
}

void MainWindow::onSliderCChanged(int value)
{
    model.setC(value);
}

void MainWindow::onLineEditAChanged()
{
    QString text = ui->lineEdit_A->text();
    bool ok;
    int value = text.toInt(&ok);

    if (ok) model.setA(value);
    else ui->lineEdit_A->setText(QString::number(model.getA()));
}

void MainWindow::onLineEditBChanged()
{
    QString text = ui->lineEdit_B->text();
    bool ok;
    int value = text.toInt(&ok);

    if (ok) {
        model.setB(value);

        if (model.getB() != value) {
            ui->lineEdit_B->setText(QString::number(model.getB()));
        }
    } else {
        ui->lineEdit_B->setText(QString::number(model.getB()));
    }
}

void MainWindow::onLineEditCChanged()
{
    QString text = ui->lineEdit_C->text();
    bool ok;
    int value = text.toInt(&ok);

    if (ok) model.setC(value);
    else ui->lineEdit_C->setText(QString::number(model.getC()));
}
