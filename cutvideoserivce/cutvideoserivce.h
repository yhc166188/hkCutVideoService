#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cutvideoserivce.h"

class cutvideoserivce : public QMainWindow
{
    Q_OBJECT

public:
    cutvideoserivce(QWidget *parent = Q_NULLPTR);

private:
    Ui::cutvideoserivceClass ui;
};
