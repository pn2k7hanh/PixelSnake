#ifndef SQUAREBOX_H
#define SQUAREBOX_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QRandomGenerator>
#include <QImage>
#include <QDateTime>
#include "define.h"
//#include "timeout.h"

struct Matrix
{
    QRectF rect;
    QImage img;
    bool isSnake=false;
    bool isApple=false;
};

struct Snake
{
    XY coor;
    Direction dir;
};

namespace Img
{
    const QImage up(":/Images/Snake/up");
    const QImage down(":/Images/Snake/down");
    const QImage left(":/Images/Snake/left");
    const QImage right(":/Images/Snake/right");

    const QImage updown(":/Images/Snake/updown");
    const QImage leftright(":/Images/Snake/leftright");

    const QImage upleft(":/Images/Snake/upleft");
    const QImage upright(":/Images/Snake/upright");
    const QImage downleft(":/Images/Snake/downleft");
    const QImage downright(":/Images/Snake/downright");
//    QImage getImage(Direction dir1, Direction dir2)
//    {
//        if(dir1>dir2)
//        {
//            Direction temp=dir1;
//            dir1=dir2;
//            dir2=temp;
//        }
//        if(dir1==UP)
//        {
//            if(dir2==DOWN);
//        }
//    }

    const QImage upArr(":/Images/Snake/upArr");
    const QImage downArr(":/Images/Snake/downArr");
    const QImage leftArr(":/Images/Snake/leftArr");
    const QImage rightArr(":/Images/Snake/rightArr");
}

class SquareBox : public QGraphicsItem, public QObject
{
public:
    SquareBox();
    void updateSize(int row, int col, int w, int h);
    QRectF boundingRect() const override;

    QSize size() { return QSize(m_rect.width(),m_rect.height()); };
    qreal width() { return m_rect.width(); };
    qreal height() { return m_rect.height(); };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
    void startGame();
    void startGame(int row, int col, int w, int h);
    void gameLose();
private:
    QVector<Matrix> v_box;
    QVector<Snake> v_snake;
    qint32 m_score;
    QImage getImage(Direction dir);
    QImage getImage(Direction dir, Direction nextDir);

    Direction m_direction;
    QVector<Direction> v_direction;
    qint8 isPress;
    qint8 speed;
    int id_speed=0;


    int m_row,m_col,m_width,m_height;
    WH m_spacing;
//    XY coor;
//    QRectF m_box;
//    QPixmap m_box;
    QRectF m_rect;

    QPointF m_mouse;
    bool Pressed;

    bool isStart;

    XY getC(QPointF pos,bool *kt);
    void snakeForward();
    void timeOut();

    QRandomGenerator rand;
    void generateApple(qint8 s);
    bool isApple;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
};

#endif // SQUAREBOX_H
