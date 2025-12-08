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
    connect(&model, SIGNAL(valuesChanged()), this, SLOT(onModelChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSpinBoxAChanged(int value)
{
    model.setA(value);
    onModelChanged();
}

void MainWindow::onSpinBoxBChanged(int value)
{
    model.setB(value);
    onModelChanged();
}

void MainWindow::onSpinBoxCChanged(int value)
{
    model.setC(value);
    onModelChanged();
}

void MainWindow::onModelChanged()
{
    ui->spinBox_A->blockSignals(true);
    ui->spinBox_B->blockSignals(true);
    ui->spinBox_C->blockSignals(true);

    ui->spinBox_A->setValue(model.getA());
    ui->spinBox_B->setValue(model.getB());
    ui->spinBox_C->setValue(model.getC());

    ui->spinBox_A->blockSignals(false);
    ui->spinBox_B->blockSignals(false);
    ui->spinBox_C->blockSignals(false);
}
