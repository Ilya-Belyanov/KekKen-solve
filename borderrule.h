#ifndef BORDERRULE_H
#define BORDERRULE_H

#include <QObject>

#include "griditem.h"

enum Operations
{
    PLUS, MINUS, MULTI, DEVIDE
};

class BorderRule: public QObject
{
    Q_OBJECT

public:
    BorderRule(QObject *parent = 0);
    Operations op;
    int resultOp;
    QList<QPoint> points;
    QString getOperation();
    bool checkRules(GridItem *grid);
};

#endif // BORDERRULE_H
