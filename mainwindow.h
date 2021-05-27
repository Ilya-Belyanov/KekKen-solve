#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "board.h"
#include "kenkenparser.h"

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
    void setGrid(GridItem *g, QVector<BorderRule> rule);

private:
    Ui::MainWindow *ui;
    Board *board;

    void loadStyle();

private slots:
    void load();
    void parseFile(QString fileName);
    void solve();
};
#endif // MAINWINDOW_H
