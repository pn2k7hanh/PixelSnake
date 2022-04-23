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
    void _startTimer();
    void startSnakeGame();
//    void updateStatus();
private:
    Ui::MainWindow *ui;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
};
#endif // MAINWINDOW_H
