#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include "cell.h"

typedef QVector<QVector<Cell>> qmatrix;
typedef QVector<Cell> qrow;

class GridItem : public QGraphicsItem
{
    Q_PROPERTY(int rows READ getRows WRITE setRows)
    Q_PROPERTY(int cols READ getCols WRITE setCols)

    int _rows;
    int _cols;
    int _defaultWidth;
    int _defaultHeight;
    qmatrix _grid;

public:
    explicit GridItem(int row = 0, int cols = 0, QGraphicsItem *parent = 0);
    ~GridItem();

    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int getRows() {return _rows;}
    int getCols() {return _cols;}
    void setRows(int r);
    void setCols(int c);

    void createNewGrid();
    qmatrix *getGrid() {return &_grid;};
    Cell *getCell(int row, int col) {return &_grid[row][col];};

private:
    void compose();
    void defaultFrame();
};

#endif // GRIDITEM_H
