#pragma once

#include <QtWidgets/QMainWindow>
#include <cmath>
#include "ui_WinowMain.h"
#include "WindowHelp.h"
#include "WindowSet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WinowMainClass; };
QT_END_NAMESPACE

class WinowMain : public QMainWindow
{
    Q_OBJECT

public:
    WinowMain(QWidget *parent = nullptr);
    ~WinowMain();

    QTreeWidgetItem* pCurrentItem;

public slots:
    void stackedWidget_setCurrentIndex();
    void show_result();
    void show_win(QWidget* widget);

private:
    Ui::WinowMainClass *ui;
    WindowHelp* WinHelp;
    WindowSet* WinSet;
    void init();
};

// 计算类
class Calculate
{
public:
    Calculate();
    ~Calculate();

    double a = 0;
    double b = 0;
    double c = 0;
    double d = 0;
    double e = 0;

    double xs = 0;
    double jz = 0;
    double r = 0;

    double cal_xs();
    double cal_jz();
    double cal_r();
};
