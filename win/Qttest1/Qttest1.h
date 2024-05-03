#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qttest1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Qttest1Class; };
QT_END_NAMESPACE

class Qttest1 : public QMainWindow
{
    Q_OBJECT

public:
    Qttest1(QWidget *parent = nullptr);
    ~Qttest1();

private:
    Ui::Qttest1Class *ui;
};
