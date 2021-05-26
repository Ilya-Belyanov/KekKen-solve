#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Kenken"));

    connect(ui->bLoad, &QPushButton::clicked, this, &MainWindow::load);
    connect(ui->bSolve, &QPushButton::clicked, this, &MainWindow::solve);
    loadStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadStyle()
{
    this -> setAcceptDrops(true);
    QFile file(":/style/style");
    file.open(QIODevice::ReadOnly);
    this -> setStyleSheet(file.readAll());
    file.close();
}

void MainWindow::load()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open file"), "",
             tr("Kenken (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
}

void MainWindow::solve()
{

}
