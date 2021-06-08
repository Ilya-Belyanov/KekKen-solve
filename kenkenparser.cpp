#include "kenkenparser.h"

KenkenParser::KenkenParser(QObject *parent) : QObject(parent)
{
    coordSearch.setPattern("(\\d+),(\\d+)");;
    opSearch.setPattern("(\\d+)([\\+\\*-:])?$");;
}

KenkenParser::~KenkenParser()
{

}

void KenkenParser::parse(QFile &file)
{
    QTextStream in(&file);
    QString line;
    while(!in.atEnd())
    {
        BorderRule rule;
        line = in.readLine();
        if(line.isEmpty())
            break;
        int pos = 0;
        bool res = true;
        while ((pos = coordSearch.indexIn(line, pos)) != -1)
        {
             rule.points << QPoint(coordSearch.cap(1).toInt(&res) - 1,
                                   coordSearch.cap(2).toInt(&res) - 1);
             pos += coordSearch.matchedLength();
             points++;
        }
        opSearch.indexIn(line);
        rule.setOperation(opSearch.cap(2));
        rule.resultOp = opSearch.cap(1).toInt(&res);
        if((rule.points.size() == 1 && rule.op != FIXED) || !res || rule.points.size() == 0)
        {
            emit fail("Error on line: " + line);
            return;
        }
        rules.push_back(rule);
    }
    createGrids();
    emit success(grid, rules);
}

void KenkenParser::createGrids()
{
    int size = sqrt(points);
    grid = new GridItem(size, size);
    QVector<BorderRule> ruleWithoutFixed;
    foreach(auto rule, rules)
    {
        Cell *cell = grid->getCell(rule.points[0].y(), rule.points[0].x());
        cell->setOperation(rule.getOperation());
        if(rule.op != FIXED)
            ruleWithoutFixed.append(rule);
        else
        {
            cell->setText(rule.resultOp);
            cell->setFixedText(true);
        }

        foreach(QPoint point, rule.points)
            setCellBorder(point, rule);
    }
    rules = ruleWithoutFixed;
}

void KenkenParser::setCellBorder(const QPoint &point, const BorderRule &rule)
{
    int size = grid->getRows();
    Cell *cell = grid->getCell(point.y(), point.x());
    for(int dx = -1; dx <= 1; dx += 2)
    {
        if(point.x() + dx >= size || point.x() + dx < 0)
            continue;
        if(rule.points.contains(QPoint(point.x() + dx, point.y())))
            continue;
        if(dx == -1)
            cell->setLeft(true);
        else
            cell->setRight(true);
    }
    for(int dy = -1; dy <= 1; dy += 2)
    {
        if(point.y() + dy >= size || point.y() + dy < 0)
            continue;
        if(rule.points.contains(QPoint(point.x(), point.y() + dy)))
            continue;
        if(dy == -1)
            cell->setTop(true);
        else
            cell->setButtom(true);
    }
}
