#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new GraphicsScene();
    ui->graphicsView->setScene(scene);
//    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->scale(1,1);
//    connect(scene->gameArea.timer,SIGNAL(timeout()),this,SLOT(updateStatus()));
//    connect(ui->pushButton,SIGNAL(clicked));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(_startTimer()));
    connect(ui->startGameButton,SIGNAL(clicked()),this,SLOT(startSnakeGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::showInformation()
{
    QMessageBox::information(NULL,"Hello","Halo");
}

void MainWindow::_startTimer()
{
//    startTimer(1500);
//    QMessageBox::information(nullptr,"startTimer","startTimer");
    scene->gameArea.isApple=true;
}

void MainWindow::startSnakeGame()
{
    scene->gameArea.startGame();
}

//void MainWindow::updateStatus()
//{
//    scene->updateStatus();
//}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    ui->widget->setGeometry(0,0,width(),height()-ui->menubar->height());
//    ui->graphicsView->setGeometry(10,10,ui->widget->width()-19,ui->widget->height()-19);
//    scene->resize(0,0,ui->widget->width()-19,ui->widget->height()-19);
    QMainWindow::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //    QMessageBox::information(NULL,"Hello World","Hello World");
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    QMessageBox::information(nullptr,"Timer Event","Timer Event "+QString::number(event->timerId()));
    killTimer(event->timerId());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    scene->keyPress(event);
//    if(event->nativeVirtualKey()==Qt::Key_0) ;
//    QMessageBox::information(nullptr,"Key","Key "+QString::number(event->key())+" was pressed");
//    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    scene->keyRelease(event);
//    QMessageBox::information(nullptr,"Text Key","Key "+QString::number(event->key()));
//    QMainWindow::keyReleaseEvent(event);
}
