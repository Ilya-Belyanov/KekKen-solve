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

void MainWindow::parseFile(const QString fileName)
{
    QFile pFile(fileName);
    if (!pFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Don't open file"),
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
    QMessageBox::information(this, tr("Check file"), message);
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
        QMessageBox::information(this, tr("Solve Kenken"), tr("Load map!"));
        return;
    } 
    QProgressDialog *pr = new QProgressDialog(this, Qt::FramelessWindowHint);
    pr->setLabelText( tr("Kenken solve...") );
    pr->setMaximum(0);
    pr->setMinimum(0);
    pr->setCancelButton( nullptr );
    pr->show();
    qApp->processEvents();

    KenkenSolver solver;
    connect(&solver, SIGNAL(result(QString)), this, SLOT(resultSolve(QString)));
    solver.solve(board->getGrid(), rules);
    board->update();
    pr->close();
    delete pr;
}

void MainWindow::resultSolve(QString message)
{
    QMessageBox::information(this, tr("Solve Kenken"), message);
}
