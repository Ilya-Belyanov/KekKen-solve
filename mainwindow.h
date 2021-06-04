#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ctime>

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>

#include "board.h"
#include "kenkenparser.h"
#include "kenkensolver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void failParse(QString message);
    void successParse(GridItem *g, QVector<BorderRule> rule);
    void resultSolve(QString message);

private:
    Ui::MainWindow *ui;
    Board *board;
    QVector<BorderRule> rules;

    void loadStyle();

private slots:
    void load();
    void parseFile(QString fileName);
    void solve();
};
#endif // MAINWINDOW_H
