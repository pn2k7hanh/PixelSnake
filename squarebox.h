#ifndef SQUAREBOX_H
#define SQUAREBOX_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QRandomGenerator>
#include "define.h"
//#include "timeout.h"

struct Matrix
{
    QRectF rect;
    bool isSnake=false;
    bool isApple=false;
};

class SquareBox : public QGraphicsItem, public QObject
{
public:
    SquareBox();
    void updateSize(int row, int col, int w, int h);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
    void startGame();
    bool isApple;
private:
    QVector<Matrix> v_box;
    QVector<XY> v_snake;
    qint32 m_score;
    qint8 m_direction;
    qint8 speed;

    int m_row,m_col,m_width,m_height;
    WH m_spacing;
//    XY coor;
    QRectF m_box;
    QRectF m_rect;

    QPointF m_mouse;
    bool Pressed;

    XY getC(QPointF pos,bool *kt);
    void snakeForward();
    void timeOut();

    QRandomGenerator rand;
    void generateApple(qint8 s);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
};

#endif // SQUAREBOX_H
