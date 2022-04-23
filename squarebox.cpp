#include "squarebox.h"

SquareBox::SquareBox() : m_rect(QRectF(0,0,100,100))
{
    m_spacing.w=5;
    m_spacing.h=5;
    speed=5;
    m_score=0;
    m_direction=RIGHT;
    isApple=false;
//    coor={0,0};
    Pressed=false;
}

void SquareBox::updateSize(int row, int col, int w, int h)
{
    m_row=row;
    m_col=col;
    m_width=w;
    m_height=h;
    m_rect.setRect(0,0,
                 m_col*(m_width+ m_spacing.w)-m_spacing.w,
                 m_row*(m_height+m_spacing.h)-m_spacing.h);
    v_box.resize(row*col);
    v_snake.clear();
    v_snake.push_back({0,0});
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            Matrix &curRect=v_box[i*col+j];
            curRect.rect=QRectF(j*(m_width +m_spacing.w),
                           i*(m_height+m_spacing.h),
                           m_width,
                           m_height);
            curRect.isSnake=false;
//            curRect.setX(j*(m_width+spacing.w));
//            curRect.setY(i*(m_height+spacing.h));
        }
    }
    v_box[0].isSnake=true;
    update();
}

QRectF SquareBox::boundingRect() const
{
    return m_rect;
//    return QRectF(0,0,100,100);
}

void SquareBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRectF rec=boundingRect();
    QBrush defaultBrush(Qt::transparent);
    QBrush snakeBrush(Qt::yellow);
    QBrush appleBrush(Qt::red);
    QColor borderColor(Qt::white);
    painter->setPen(borderColor);
    painter->setBrush(Qt::black);
    painter->drawRect(m_rect);
    painter->setPen(Qt::transparent);
    for(int i=0;i<m_row;i++)
    {
        for(int j=0;j<m_col;j++)
        {
            Matrix &curRect=v_box[i*m_col+j];
            if(curRect.isSnake) painter->setBrush(snakeBrush);
            else if(curRect.isApple) painter->setBrush(appleBrush);
            else painter->setBrush(defaultBrush);
            painter->drawEllipse(curRect.rect);
        }
    }
    //    painter->drawRect(rec);
//    QGraphicsItem::paint(painter,option,widget);
}

XY SquareBox::getC(QPointF pos,bool *kt)
{
    int w=m_width+m_spacing.w,
        h=m_height+m_spacing.h;
    int i=pos.x()/w,
            j=pos.y()/h;
    //kt
    {
        w=int(pos.x())%w;
        h=int(pos.y())%h;
        if(w>m_width||h>m_height)
            *kt=false;
        else
            *kt=true;
    }
    return {i,j};
}

void SquareBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    m_mouse=event->scenePos();
//    bool kt;
//    XY c=getC(m_mouse,&kt);
//    if(kt) v_box[c.y*m_col+c.x].isSnake=true;
//    update();
//    Pressed=true;
////    QGraphicsItem::mousePressEvent(event);
}

void SquareBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
////    QMessageBox::information(nullptr,"gameArea",
////                             "Mouse Press Event<br>"+
////                             QString::number(int(m_mouse.x()))+" "+
////                             QString::number(int(m_mouse.y())));
//    bool kt;
//    XY c=getC(m_mouse,&kt);
//    if(kt) v_box[c.y*m_col+c.x].isSnake=false;
//    update();
//    Pressed=false;
    //    //    QGraphicsItem::mouseReleaseEvent(event);
}

void SquareBox::timerEvent(QTimerEvent *event)
{
    timeOut();
//    switch(event->timerId())
//    {
//    case 1:
//    }
}

void SquareBox::keyPress(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        m_direction=UP;
        break;
    case Qt::Key_S:
        m_direction=DOWN;
        break;
    case Qt::Key_A:
        m_direction=LEFT;
        break;
    case Qt::Key_D:
        m_direction=RIGHT;
        break;
    }
    update();
}

void SquareBox::keyRelease(QKeyEvent *event)
{

}

void SquareBox::startGame()
{
    static bool isStart=false;
    if(isStart) return;
    isStart=true;
    generateApple(10);
    startTimer(qreal(1)/speed*1000);
}

void SquareBox::snakeForward()
{
    XY nextCoor=v_snake.first();
    switch (m_direction)
    {
    case UP:
//        if(nextCoor.x>0)
        nextCoor.x--;
        break;
    case DOWN:
//        if(nextCoor.x<m_row-1)
        nextCoor.x++;
        break;
    case LEFT:
//        if(nextCoor.y>0)
        nextCoor.y--;
        break;
    case RIGHT:
//        if(nextCoor.y<m_col-1)
        nextCoor.y++;
        break;
    }

    { // teleport
        if(nextCoor.x<0)
        {
            nextCoor.x=m_row-1;
        }
        else if(nextCoor.x>=m_row)
        {
            nextCoor.x=0;
        }
        if(nextCoor.y<0)
        {
            nextCoor.y=m_col-1;
        }
        else if(nextCoor.y>=m_col)
        {
            nextCoor.y=0;
        }
    } // END teleport

    Matrix &nextBox=v_box[nextCoor.x*m_col+nextCoor.y];
    if(nextBox.isApple)
    {
        nextBox.isApple=false;
        isApple=true;
        generateApple(1);
    }

    int EOS=v_snake.size()-1;

    if(isApple)
    {
        v_snake.push_back(v_snake.back());
        isApple=false;
    }
    else
    {
        XY &last=v_snake.back();
        v_box[last.x*m_col+last.y].isSnake=false;
    }

    for(int i=EOS;i>=0;i--)
    {
        XY &snakeCoor=v_snake[i];
        if(i==0) v_snake[i]=nextCoor;
        else v_snake[i]=v_snake[i-1];
        v_box[snakeCoor.x*m_col+snakeCoor.y].isSnake=true;
    }
    update();
}

void SquareBox::timeOut()
{
    snakeForward();
}

void SquareBox::generateApple(qint8 s)
{
    for(int i=0;i<s;i++)
    {
        Matrix *curBox;
        do
        {
            curBox=&v_box[rand.bounded(1,m_row*m_col)-1];
        }while(curBox->isApple||curBox->isSnake);
        curBox->isApple=true;
    }
}
