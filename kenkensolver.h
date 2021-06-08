#ifndef KENKENSOLVER_H
#define KENKENSOLVER_H

#include <ctime>

#include <QObject>

#include "griditem.h"
#include "borderrule.h"

class KenkenSolver : public QObject
{
    Q_OBJECT

    QVector<QVector<short>> combinations;
    QVector<QVector<short>> indexs;
    QVector<int> curPos;

    QVector<QVector<short>> _grid;
    QVector<BorderRule> _rules;

    int timeStartSolve;

public:
    explicit KenkenSolver(QObject *parent = nullptr);
    void solve(GridItem *g, QVector<BorderRule> rule);

private:
    void generateCombinations(int size);
    void generateIndexs(GridItem *g, int size);
    void createStartPos(int size);
    void createGrid(GridItem *g);
    QVector<short> generateIndexsForFixed(const QMap<int, int> &fixed, int size);
    bool nextCombination(QVector<short> &combination);
    void swap(QVector<short> &combination, int i, int j);
    int factor(int n);

    void startSolve(GridItem *g);
    void setGrid();
    void setGrid(int row);
    bool allEnd();
    bool checkCols();
    void upPos(int pos = 0);

    void setSolveGrid(GridItem *g);

signals:
    void result(QString message);
};

#endif // KENKENSOLVER_H
