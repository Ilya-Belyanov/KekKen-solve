#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>


class Cell: public QGraphicsItem
{
    Q_PROPERTY(int width READ getWidth WRITE setWidth)
    Q_PROPERTY(int height READ getHeight WRITE setHeight)
    Q_PROPERTY(QString operation READ getOperation WRITE setOperation)
    Q_PROPERTY(int text READ getText WRITE setText)
    Q_PROPERTY(bool top READ isTop WRITE setTop)
    Q_PROPERTY(bool buttom READ isButtom WRITE setButtom)
    Q_PROPERTY(bool right READ isRight WRITE setRight)
    Q_PROPERTY(bool left READ isLeft WRITE setLeft)
    Q_PROPERTY(bool fixedText READ isfixedText WRITE setfixedText)

    int _width;
    int _height;
    int _defaultWidth;
    int _defaultHeight;
    int _fontSize;
    int _opFontSize;
    int _lineWidth;
    float _rectWidth;

    QString _operation;
    int _text;

    bool _isTop, _isButtom, _isRight, _isLeft;
    bool _fixedText = false;

public:
    explicit Cell(int width = 0, int height = 0, QGraphicsItem *parent = 0);
    ~Cell();

    Cell(const Cell& );
    Cell& operator=(const Cell& );

    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void paintRect(QPainter *painter);
    void paintBorder(QPainter *painter);
    void paintText(QPainter *painter);
    void paintOp(QPainter *painter);

    int getWidth() {return _width;}
    int getHeight() {return _height;}
    void setWidth(const int w);
    void setHeight(const int h);
    void setDefaulSize();
    void setDefaulWidth();
    void setDefaulHeight();

    QString getOperation() {return _operation;}
    QString getText() {return QString::number(_text);}
    int getNumber() {return _text;}
    void setOperation(const QString op);
    void setText(const int txt);

    bool isTop()    {return _isTop;}
    bool isButtom() {return _isButtom;}
    bool isRight()  {return _isRight;}
    bool isLeft()   {return _isLeft;}
    void setTop(const bool t)    {_isTop = t;};
    void setButtom(const bool b) {_isButtom = b;};
    void setRight(const bool r)  {_isRight = r;};
    void setLeft(const bool l)   {_isLeft = l;};

    bool isFixedText()   {return _fixedText;}
    void setFixedText(const bool fixedText)   {_fixedText = fixedText;};

private:
    void updateFont();
};

#endif // CELL_H
