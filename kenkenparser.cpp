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
        int pos = 0;
        while ((pos = coordSearch.indexIn(line, pos)) != -1)
        {
             rule.points << QPoint(coordSearch.cap(1).toInt() - 1,
                                   coordSearch.cap(2).toInt() - 1);
             pos += coordSearch.matchedLength();
             points++;
         }
        opSearch.indexIn(line);
        rule.setOperation(opSearch.cap(2));
        rule.resultOp = opSearch.cap(1).toInt();
        rules.push_back(rule);
    }
    createGrids();
    emit success(grid, rules);
}

void KenkenParser::createGrids()
{
    int size = sqrt(points);
    grid = new GridItem(size, size);
}
