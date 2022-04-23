#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include "squarebox.h"
class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene();
//    ~GraphicsScene();
    void resize(int x,int y,int w, int h);
    SquareBox gameArea;
    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
private:
    QPointF posMouse;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GRAPHICSSCENE_H
