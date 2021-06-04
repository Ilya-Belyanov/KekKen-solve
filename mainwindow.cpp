#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Kenken"));

    board = new Board(this, ui->graphicsView);
    connect(ui->bLoad, &QPushButton::clicked, this, &MainWindow::load);
    connect(ui->bSolve, &QPushButton::clicked, this, &MainWindow::solve);
    loadStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board;
}

void MainWindow::loadStyle()
{
    this->setAcceptDrops(true);
    QFile file(":/style/style");
    file.open(QIODevice::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();
}

void MainWindow::load()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open file"), "",
             tr("Kenken (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
        parseFile(fileName);
}

void MainWindow::parseFile(QString fileName)
{
    QFile pFile(fileName);
    if (!pFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Невозможно открыть файл"),
            pFile.errorString());
        return;
    }
    KenkenParser parser;
    connect(&parser, SIGNAL(success(GridItem *, QVector<BorderRule>)), this, SLOT(successParse(GridItem *, QVector<BorderRule>)));
    connect(&parser, SIGNAL(fail(QString)), this, SLOT(failParse(QString)));
    parser.parse(pFile);
}

void MainWindow::failParse(QString message)
{
    QMessageBox::information(this, tr("Проверка файла"), message);
}

void MainWindow::successParse(GridItem *g, QVector<BorderRule> rule)
{
    board->setGrid(g);
    rules = rule;
}

void MainWindow::solve()
{
    if(rules.size() == 0)
    {
        QMessageBox::information(this, tr("Решение Kenken"), tr("Загрузите карту!"));
        return;
    }

    KenkenSolver solver;
    connect(&solver, SIGNAL(result(QString)), this, SLOT(resultSolve(QString)));

    int start = clock();

    solver.solve(board->getGrid(), rules);
    board->update();
    qDebug() << clock() - start;
}

void MainWindow::resultSolve(QString message)
{
    QMessageBox::information(this, tr("Решение Kenken"), message);
}
