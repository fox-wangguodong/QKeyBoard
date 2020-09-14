#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Keyboard/keyboardinstaller.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏

    KeyboardInstaller::installObject(this);
}

MainWindow::~MainWindow()
{
    KeyboardInstaller::removeObject(this);
    delete ui;
}
