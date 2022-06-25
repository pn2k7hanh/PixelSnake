#include "squarebox.h"

SquareBox::SquareBox() : m_rect(QRectF(0,0,100,100))
{
    m_spacing.w=0;
    m_spacing.h=0;
    speed=8;
    m_score=0;
    m_direction=RIGHT;
    isApple=false;
//    coor={0,0};
    isStart=false;
    isPress=2;
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
    v_box.clear();
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
    QBrush snakeBrush(Qt::green);
    QBrush appleBrush(Qt::red);
    QPen borderPen(Qt::black);

    painter->setPen(Qt::transparent);

    for(int i=0;i<m_row;i++)
    {
        for(int j=0;j<m_col;j++)
        {
            Matrix &curRect=v_box[i*m_col+j];
            if(curRect.isSnake) painter->setBrush(snakeBrush);
            else if(curRect.isApple) painter->setBrush(appleBrush);
            else painter->setBrush(defaultBrush);
//            QImage img;
            painter->drawEllipse(curRect.rect);
            if(curRect.isSnake) painter->drawImage(curRect.rect,curRect.img);
//            else painter->drawEllipse(curRect.rect);
        }
    }
    painter->setPen(borderPen);
    painter->setBrush(Qt::transparent);
    painter->drawRect(m_rect);
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
//    QMessageBox::information(nullptr,"Key Press","Key " + QString::number(event->key()) + " just pressed");
    Direction *p_direction1=&m_direction;
    Direction *p_direction2;
    if(!v_direction.isEmpty())
    {
        p_direction1=&v_direction[v_direction.size()-1];
    }
    if(v_direction.size()<2)
    {
//        v_direction.resize(v_direction.size()+1);
        v_direction.push_back(DOWN);
//        p_direction2=v_direction.end();
        p_direction2=&v_direction[v_direction.size()-1];
        switch(event->key())
        {
        case Qt::Key_W:
            if(*p_direction1!=DOWN && *p_direction1!=UP)
            {
                *p_direction2=UP;
//                v_direction.push_back(m_direction);
            }
            else v_direction.pop_back();
            break;
        case Qt::Key_S:
            if(*p_direction1!=DOWN && *p_direction1!=UP)
            {
                *p_direction2=DOWN;
//                v_direction.push_back(m_direction);
            }
            else v_direction.pop_back();
            break;
        case Qt::Key_A:
            if(*p_direction1!=RIGHT && *p_direction1!=LEFT)
            {
                *p_direction2=LEFT;
//                v_direction.push_back(m_direction);
            }
            else v_direction.pop_back();
            break;
        case Qt::Key_D:
            if(*p_direction1!=RIGHT && *p_direction1!=LEFT)
            {
                *p_direction2=RIGHT;
//                v_direction.push_back(m_direction);
            }
            else v_direction.pop_back();
            break;
        default:
            v_direction.pop_back();
            break;
        }
    }
//    update();
}

void SquareBox::keyRelease(QKeyEvent *event)
{

}

void SquareBox::startGame()
{
    rand.seed(time(0));
    if(isStart) return;
    isStart=true;

    // default value
    updateSize(m_row,m_col,m_width,m_height);
    m_direction=RIGHT;
    v_direction.clear();

    generateApple(1);
    id_speed=startTimer(qreal(1)/speed*1000);
}

void SquareBox::startGame(int row, int col, int w, int h)
{
    updateSize(row,col,w,h);
    startGame();
}

void SquareBox::gameLose()
{
    isStart=false;
    killTimer(id_speed);
    QMessageBox::information(nullptr,"Game Lose","Game Lose");
}

QImage SquareBox::getImage(Direction dir)
{
    switch (dir)
    {
    case UP:
        return Img::downArr;
        break;
    case DOWN:
        return Img::upArr;
        break;
    case LEFT:
        return Img::rightArr;
        break;
    case RIGHT:
        return Img::leftArr;
        break;

    }
}

QImage SquareBox::getImage(Direction dir, Direction nextDir)
{

    if(dir==NONE)
    {
        if(nextDir==UP) return Img::down;
        else if(nextDir==DOWN) return Img::up;
        else if(nextDir==LEFT) return Img::right;
        else if(nextDir==RIGHT) return Img::left;
    }
    else if(nextDir==NONE)
    {
        if(nextDir==UP) return Img::up;
        else if(nextDir==DOWN) return Img::down;
        else if(nextDir==LEFT) return Img::left;
        else if(nextDir==RIGHT) return Img::right;
    }
    if(dir>nextDir)
    {
        Direction temp=dir;
        dir=nextDir;
        nextDir=temp;
    }
    if(dir==UP)
    {
        if(nextDir==UP) return Img::updown;
        else if(nextDir==LEFT) return Img::upright;
        else if(nextDir==RIGHT) return Img::upleft;
    }
    else if(dir==DOWN)
    {
        if(nextDir==DOWN) return Img::updown;
        else if(nextDir==LEFT) return Img::downright;
        else if(nextDir==RIGHT) return Img::downleft;
    }
    else if(dir==LEFT)
    {
        if(nextDir==LEFT) return Img::leftright;
        else if(nextDir==UP) return Img::downleft;
        else if(nextDir==DOWN) return Img::upleft;
    }
    else if(dir==RIGHT)
    {
        if(nextDir==RIGHT) return Img::leftright;
        else if(nextDir==UP) return Img::downright;
        else if(nextDir==DOWN) return Img::upright;
    }

}

void SquareBox::timeOut()
{
    if(!v_direction.isEmpty())
    {
        m_direction=v_direction.first();
        v_direction.pop_front();
    }
    isPress=false;
    snakeForward();
    update();
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

void SquareBox::snakeForward()
{
    XY nextCoor=v_snake.first().coor;
    Snake &last=v_snake.back();
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
    if(nextBox.isSnake)
    {
        gameLose();
        return;
    }
    int EOS=v_snake.size()-1;

    if(isApple)
    {
        v_snake.push_back(v_snake.back());
        isApple=false;
    }
    else
    {
        v_box[last.coor.x*m_col+last.coor.y].isSnake=false;
    }

//    v_box[last.x+m_col+last.y];

    for(int i=EOS;i>=0;i--)
    {
        Snake &snake=v_snake[i];
//        XY before,after;
        if(i==0) snake={nextCoor,m_direction};
        else snake=v_snake[i-1];
        // Update the Matrix
        v_box[snake.coor.x*m_col+snake.coor.y].isSnake=true;
        v_box[snake.coor.x*m_col+snake.coor.y].img=getImage(snake.dir);
//        if(i==0)
//        {
//            v_box[snake.coor.x*m_col+snake.coor.y].img=getImage(NONE,snake.dir);
//            QMessageBox::information(nullptr,"error","error2");
//        }
//        else if(i==EOS)
//        {
//            v_box[snake.coor.x*m_col+snake.coor.y].img=getImage(snake.dir,NONE);
//            QMessageBox::information(nullptr,"error","error");
//        }
//        else v_box[snake.coor.x*m_col+snake.coor.y].img=getImage(snake.dir,v_snake[i+1].dir);
    }
}
