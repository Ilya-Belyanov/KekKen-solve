#include "borderrule.h"

BorderRule::BorderRule(QObject *parent) : QObject(parent)
{

}

QString BorderRule::getOperation()
{
    switch (op)
    {
        case(PLUS):
            return QString::number(resultOp) + "+";
        case(MINUS):
            return QString::number(resultOp) + "-";
        case(MULTI):
            return QString::number(resultOp) + "*";
        case(DEVIDE):
            return QString::number(resultOp) + "/";
    }
}

bool BorderRule::checkRules(GridItem *grid)
{
    QList<int> items;
    foreach(QPoint p, points)
        items.append(grid->getCell(p.x(), p.y())->getNumber());
    int result;
    if(op == PLUS)
    {
        result = 0;
        foreach(int i, items)
            result += i;
    }
    else if(op == MULTI)
    {
        result = 1;
        foreach(int i, items)
            result *= i;
    }
    else
    {
        int max = *std::max_element(items.begin(), items.end());
        int min = *std::min_element(items.begin(), items.end());
        if(op == MINUS)
            result = max - min;
        else
            result = max / min;
    }

    return result == resultOp;
}
