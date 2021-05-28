#ifndef BORDERRULE_H
#define BORDERRULE_H

#include <QObject>
#include <QDebug>

#include "griditem.h"

enum Operations
{
    PLUS, MINUS, MULTI, DEVIDE, FIXED
};

class BorderRule: public QObject
{
    Q_OBJECT
    QMap<Operations, QString> opMap;

public:
    BorderRule(QObject *parent = 0);

    BorderRule(const BorderRule& );
    BorderRule& operator=(const BorderRule& );
    friend bool operator== (const BorderRule &c1, const BorderRule &c2);

    Operations op;
    int resultOp;
    QList<QPoint> points;

    QString getOperation();
    void setOperation(QString operation);
    bool checkRules(GridItem *grid);
};

#endif // BORDERRULE_H
