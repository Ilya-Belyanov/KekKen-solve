#ifndef KENKENPARSER_H
#define KENKENPARSER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "griditem.h"
#include "borderrule.h"

class KenkenParser: public QObject
{
    Q_OBJECT

public:
    KenkenParser(QObject *parent = 0);
    void parse(QFile &file);

signals:
    void success(GridItem *grid, QList<BorderRule> rule);
    void fail(QString line);
};

#endif // KENKENPARSER_H
