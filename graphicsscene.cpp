#include "graphicsscene.h"
GraphicsScene::GraphicsScene()
{
//    addItem(&squareBox);
//    addItem();
    addItem(&gameArea);
//    gameArea.setPos();
}
void GraphicsScene::resize(int x,int y,int w, int h)
{
//    update(x,y,w,h);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    posMouse=event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    QMessageBox::information(NULL,"Hello World",
//                             "Hello World 2<br>"+
//                             QString::number(posMouse.x())+" "+
//                             QString::number(posMouse.y())+"<br>"+
//                             QString::number(width())+" "+
//                             QString::number(height()));
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::keyPress(QKeyEvent *event)
{
    gameArea.keyPress(event);
//    QGraphicsScene::keyPressEvent(event);
}

void GraphicsScene::keyRelease(QKeyEvent *event)
{
    gameArea.keyRelease(event);
    //    QGraphicsScene::keyReleaseEvent(event);
}

//void GraphicsScene::updateStatus()
//{
//    gameArea.timeOut();
//}
