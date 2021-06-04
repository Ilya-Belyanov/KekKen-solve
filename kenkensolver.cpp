#include "kenkensolver.h"

KenkenSolver::KenkenSolver(QObject *parent) : QObject(parent)
{

}

void KenkenSolver::solve(GridItem *g, QVector<BorderRule> rule)
{
    Q_UNUSED(rule);
    generateCombinations(g->getRows());
    generateIndexs(g, g->getRows());
    createEndFalse(g->getRows());
    createStartPos(g->getRows());
    startSolve(g, rule);
}

void KenkenSolver::generateCombinations(int size)
{
    combinations.clear();
    QVector<short> row;
    for(int i = 1; i <= size; i++)
        row.append(i);
    combinations.append(row);
    while(nextCombination(row))
        combinations.append(row);
}

void KenkenSolver::generateIndexs(GridItem *g, int size)
{
    indexs.clear();
    int max = factor(size);
    for(int i = 0; i < size; i++)
    {
        QVector<short> rowIndex;
        QMap<int, int> fixed = g->fixedCells(i);
        if(fixed.empty())
            for(int j = 0; j < max; j++)
                rowIndex.append(j);
        else
            rowIndex = generateIndexsForFixed(fixed, max);
        indexs.append(rowIndex);
    }
}

void KenkenSolver::createEndFalse(int size)
{
    isEnd.clear();
    for(int i = 0; i < size; i++)
        isEnd.append(false);
}

void KenkenSolver::createStartPos(int size)
{
    curPos.clear();
    for(int i = 0; i < size; i++)
        curPos.append(0);
}

QVector<short> KenkenSolver::generateIndexsForFixed(QMap<int, int> fixed, int size)
{
    QVector<short> rowIndex;
    for(int j = 0; j < size; j++)
    {
        bool res = true;
        foreach(int col, fixed.keys())
        {
            if(combinations[j][col] != fixed[col])
            {
                res = false;
                break;
            }
        }
        if(res)
            rowIndex.append(j);
    }
    return rowIndex;
}

bool KenkenSolver::nextCombination(QVector<short> &combination)
{
    int size = combination.size();
    int j = size - 2;
    while(j != -1 && combination[j] > combination[j+1])
        j--;
    if(j == -1)
        return false;
    int k = size - 1;

    while(combination[j] >= combination[k])
        k--;
    swap(combination, j, k);
    int l = j + 1, r = size - 1;
    while( l < r)
        swap(combination, l++, r--);
    return true;
}

void KenkenSolver::swap(QVector<short> &combination, int i, int j)
{
    int s = combination[i];
    combination[i] = combination[j];
    combination[j] = s;
}

int KenkenSolver::factor(int n)
{
    if (n == 1 || n == 0)
        return 1;
    return factor(n - 1) * n;
}

void KenkenSolver::startSolve(GridItem *g, QVector<BorderRule> rule)
{
    setGrid(g);
    while(!allEnd())
    {
        if(!checkCols())
        {
            upPos(g);
            continue;;
        }
        bool res = true;
        foreach(BorderRule r, rule)
        {
            if(!r.checkRules(g))
            {
                res = false;
                upPos(g);
                break;
            }
        }
        if(res)
            break;
    }
}

void KenkenSolver::setGrid(GridItem *g)
{
    for(int i = 0; i < curPos.size(); i++)
        for(int j = 0; j < curPos.size(); j++)
            g->getCell(i, j)->setText(combinations[indexs[i][curPos[i]]][j]);
}

void KenkenSolver::setGrid(GridItem *g, int row)
{
    for(int j = 0; j < curPos.size(); j++)
        g->getCell(row, j)->setText(combinations[indexs[row][curPos[row]]][j]);
}

bool KenkenSolver::allEnd()
{
    foreach(bool end, isEnd)
        if(!end)
            return false;
    return true;
}

bool KenkenSolver::checkCols()
{
    for(int i = 0; i < curPos.size(); i++)
    {
        QVector<short> curIndexs;
        for(int j = 0; j < curPos.size(); j++)
            if(!curIndexs.contains(combinations[indexs[j][curPos[j]]][i]))
                curIndexs.append(combinations[indexs[j][curPos[j]]][i]);
            else
                return false;
    }
    return true;
}

void KenkenSolver::upPos(GridItem *g, int pos)
{
    if(pos >= curPos.size())
        return;
    curPos[pos]++;
    if (curPos[pos] >= indexs[pos].size())
    {
       curPos[pos] = 0;
       setGrid(g, pos);
       isEnd[pos]  = true;
       upPos(g, ++pos);
    }
    else
        setGrid(g, pos);
}
