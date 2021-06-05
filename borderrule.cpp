#include "borderrule.h"

BorderRule::BorderRule(QObject *parent) : QObject(parent)
{
    opMap = {{PLUS, "+"}, {MINUS, "-"},
             {MULTI, "*"}, {DEVIDE, ":"},
             {FIXED, ""}};
}

BorderRule::BorderRule(const BorderRule &other)
    :QObject(other.parent())
{
    op = other.op;
    resultOp = other.resultOp;
    points = other.points;
    opMap = other.opMap;
}

BorderRule& BorderRule::operator=(const BorderRule& other)
{
    op = other.op;
    resultOp = other.resultOp;
    points = other.points;
    opMap = other.opMap;
    return *this;
}

bool operator== (const BorderRule &c1, const BorderRule &c2)
{
    bool res = true;
    res |= (c1.points.size() == c2.points.size());
    foreach(QPoint p, c2.points)
        res |= (c1.points.contains(p));
    res |= (c1.op == c2.op);
    res |= (c1.resultOp == c2.resultOp);
    return res;
}

QString BorderRule::getOperation()
{
    return QString::number(resultOp) + opMap[op];
}

void BorderRule::setOperation(QString operation)
{
    auto it = opMap.begin();
    while(it != opMap.end())
    {
        if(it.value() == operation)
        {
            op = it.key();
            break;
        }
        it++;
    }
}

bool BorderRule::checkRules(GridItem *grid)
{
    QList<int> items;
    foreach(QPoint p, points)
        items.append(grid->getCell(p.y(), p.x())->getNumber());
    return _checkRules(items);
}

bool BorderRule::checkRules(QVector<QVector<short>> grid)
{
    QList<int> items;
    foreach(QPoint p, points)
        items.append(grid[p.y()][p.x()]);
    return _checkRules(items);
}

bool BorderRule::_checkRules(QList<int> items)
{
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
    else if(op == FIXED)
        result = resultOp;

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
