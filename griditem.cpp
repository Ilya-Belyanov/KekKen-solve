#include "griditem.h"

GridItem::GridItem(int row, int cols, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    _defaultWidth = 360;
    _defaultHeight = 360;
    _rows = 4;
    _cols = 4;
    setRows(row);
    setCols(cols);
    createNewGrid();
}

GridItem::~GridItem()
{
    foreach(qrow row, _grid)
        foreach(Cell *cell, row)
            delete cell;
}

QPainterPath GridItem::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _defaultWidth, _defaultHeight);
    return path;
}

QRectF GridItem::boundingRect() const
{
    return QRectF(0, 0, _defaultWidth, _defaultHeight);
}

void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
}

void GridItem::setRows(int r)
{
    if(r > 0)
        _rows = r;
}

void GridItem::setCols(int c)
{
    if(c > 0)
        _cols = c;
}

void GridItem::createNewGrid()
{
    _grid.clear();
    int h = _defaultHeight / _rows;
    int w = _defaultWidth / _cols;
    for(int i = 0; i < _rows; i++)
    {
        qrow row;
        for(int j = 0; j < _cols; j++)
        {
            Cell *cell = new Cell(w, h, this);
            row.push_back(cell);
        }
        _grid.append(row);
    }
    compose();
    defaultFrame();

}

void GridItem::compose()
{
    int h = _defaultHeight / _rows;
    int w = _defaultWidth / _cols;
    for(int i = 0; i < _rows; i++)
        for(int j = 0; j < _cols; j++)
            _grid[i][j]->setPos(j*w, i*h);
}

void GridItem::defaultFrame()
{
    for(int j = 0; j < _cols; j++)
        _grid[0][j]->setTop(true);
    for(int j = 0; j < _cols; j++)
        _grid[_rows - 1][j]->setButtom(true);
    for(int i = 0; i < _rows; i++)
        _grid[i][0]->setLeft(true);
    for(int i = 0; i < _rows; i++)
        _grid[i][_cols - 1]->setRight(true);
}
