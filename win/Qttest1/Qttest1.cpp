#include "Qttest1.h"

Qttest1::Qttest1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Qttest1Class())
{
    ui->setupUi(this);
}

Qttest1::~Qttest1()
{
    delete ui;
}
