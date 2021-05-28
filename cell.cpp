#include "cell.h"

Cell::Cell(int width, int height, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      _isTop(false),
      _isButtom(false),
      _isRight(false),
      _isLeft(false)
{
    _defaultWidth = 10;
    _defaultHeight = 10;
    _lineWidth = 4;
    _rectWidth = 1;

    if(width != 0)
        setWidth(width);
    else
        setDefaulWidth();

    if(height != 0)
        setHeight(height);
    else
        setDefaulHeight();
}

Cell::~Cell()
{

}

Cell::Cell(const Cell &other)
    :QGraphicsItem(other.parentItem()),
     _defaultWidth(other._defaultWidth),
     _defaultHeight(other._defaultHeight),
     _lineWidth(other._lineWidth),
     _rectWidth(other._rectWidth),
     _isTop(false),
     _isButtom(false),
     _isRight(false),
     _isLeft(false)
{
    setWidth(other._width);
    setHeight(other._height);
}

Cell& Cell::operator=(const Cell& other)
{
    _width = other._width;
    _height = other._height;
    return *this;
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, _width, _height);
    return path;
}

QRectF Cell::boundingRect() const
{
    return QRectF(0, 0, _width, _height);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen(Qt::darkGray);
    pen.setWidth(_rectWidth);
    painter->setPen(pen);

    paintRect(painter);

    pen.setColor(Qt::green);
    pen.setWidth(_lineWidth);
    painter->setPen(pen);

    paintBorder(painter);
    paintText(painter);
    paintOp(painter);
}

void Cell::paintRect(QPainter *painter)
{
    QRect rect(0, 0, _width, _height);
    painter->drawRect(rect);
}

void Cell::paintBorder(QPainter *painter)
{
    if(_isTop)
        painter->drawLine(0, 0, _width, 0);
    if(_isButtom)
        painter->drawLine(0, _height, _width, _height);
    if(_isRight)
        painter->drawLine(_width, 0, _width, _height);
    if(_isLeft)
        painter->drawLine(0, 0, 0, _height);
}

void Cell::paintText(QPainter *painter)
{
    QRect rect(0, 0, _width, _height);
    QFont font = painter->font();
    font.setPixelSize(_fontSize);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, _text);
}

void Cell::paintOp(QPainter *painter)
{
    QRect rect(_lineWidth, _lineWidth, _width, _height);
    QFont font = painter->font();
    font.setPixelSize(_opFontSize);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignTop | Qt::AlignLeft, _operation);
}

void Cell::setWidth(int w)
{
    if(w > 0)
        _width = w;
}

void Cell::setHeight(int h)
{
    if(h > 0)
    {
        _height = h;
        updateFont();
    }
}

void Cell::setDefaulSize()
{
    setDefaulWidth();
    setDefaulHeight();
}

void Cell::setDefaulWidth()
{
    _width = _defaultWidth;
}

void Cell::setDefaulHeight()
{
    _height = _defaultHeight;
    updateFont();
}

void Cell::setOperation(QString op)
{
    _operation = op;
}

void Cell::setText(QString txt)
{
    if(!_fixedText)
        _text = txt;
}

void Cell::updateFont()
{
    _fontSize = _height / 2;
    _opFontSize = _height / 5;
}
