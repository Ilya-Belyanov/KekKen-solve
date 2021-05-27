#ifndef KENKENPARSER_H
#define KENKENPARSER_H

#include "math.h"

#include <QFile>
#include <QObject>
#include <QRegExp>
#include <QTextStream>
#include <QDebug>

#include "griditem.h"
#include "borderrule.h"

class KenkenParser: public QObject
{
    Q_OBJECT

    QVector<BorderRule> rules;
    GridItem *grid;
    int points = 0;

public:
    KenkenParser(QObject *parent = 0);
    ~KenkenParser();

    void parse(QFile &file);
    void createGrids();

private:
    QRegExp coordSearch;
    QRegExp opSearch;

signals:
    void success(GridItem *grid, QVector<BorderRule> rule);
    void fail(QString line);
};

#endif // KENKENPARSER_H
