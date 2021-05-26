#include "kenkenparser.h"

KenkenParser::KenkenParser(QObject *parent) : QObject(parent)
{

}

void KenkenParser::parse(QFile &file)
{
    QTextStream in(&file);
}
