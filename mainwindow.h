#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
#include <QTimerEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include "graphicsscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    GraphicsScene *scene;
public slots:
    void showInformation();
    void startSnakeGame();
    void aboutMessageBox();
    void newGameAction();
//    void updateStatus();
private:
    Ui::MainWindow *ui;

    qint32 rwidth,rheight;
    struct{
        int w,h;
    } scale;

    QPoint m_dragPosition;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void timerEvent(QTimerEvent *event) override;
};
#endif // MAINWINDOW_H
