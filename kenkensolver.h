#ifndef KENKENSOLVER_H
#define KENKENSOLVER_H

#include <QObject>

#include "griditem.h"
#include "borderrule.h"

class KenkenSolver : public QObject
{
    Q_OBJECT

    QVector<QVector<short>> combinations;
    QVector<QVector<short>> indexs;
    QVector<bool> isEnd;
    QVector<int> curPos;

public:
    explicit KenkenSolver(QObject *parent = nullptr);
    void solve(GridItem *g, QVector<BorderRule> rule);

private:
    void generateCombinations(int size);
    void generateIndexs(GridItem *g, int size);
    void createEndFalse(int size);
    void createStartPos(int size);
    QVector<short> generateIndexsForFixed(QMap<int, int> fixed, int size);
    bool nextCombination(QVector<short> &combination);
    void swap(QVector<short> &combination, int i, int j);
    int factor(int n);

    void startSolve(GridItem *g, QVector<BorderRule> rule);
    void setGrid(GridItem *g);
    void setGrid(GridItem *g, int row);
    bool allEnd();
    bool checkCols();
    void upPos(GridItem *g, int pos = 0);

signals:
    void result(QString message);
};

#endif // KENKENSOLVER_H
