#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSpinBoxAChanged(int value);
    void onSpinBoxBChanged(int value);
    void onSpinBoxCChanged(int value);
    void onModelChanged();
    void onSliderAChanged(int value);
    void onSliderBChanged(int value);
    void onSliderCChanged(int value);

private:
    Ui::MainWindow *ui;
    Model model;
};
#endif // MAINWINDOW_H
