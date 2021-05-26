#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsView>

class Board : public QObject
{
    Q_OBJECT

public:
    explicit Board(QObject *parent = nullptr, QGraphicsView *graph = nullptr );
    void setGraphicsView(QGraphicsView *graph);

private:
    QGraphicsView *graphics;
    QGraphicsScene *scene;

signals:

};

#endif // BOARD_H
