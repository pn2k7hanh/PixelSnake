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

    rwidth=rheight=0;
    scale={600,400};
    connect(ui->startGameButton,SIGNAL(clicked()),this,SLOT(startSnakeGame()));

    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(aboutMessageBox()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newGameAction()));

//    startSnakeGame();

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

void MainWindow::startSnakeGame()
{
    scene->gameArea.startGame();
}

void MainWindow::aboutMessageBox()
{
    QMessageBox::information(nullptr,"About","Made by PhamNamKhanh");
}

void MainWindow::newGameAction()
{
    scene->gameArea.gameLose();
    scene->gameArea.startGame();
}

//void MainWindow::updateStatus()
//{
//    scene->updateStatus();
//}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    if(rwidth<1)
//    {
//        rwidth=width();
//        rheight=height();
//    }
//    else
//    {
////        if(qAbs(width()-rwidth)>qAbs(height()-rheight))
//        if((width()-rwidth)>(height()-rheight))
//        {
//            resize(width(),width()*scale.h/scale.w);
//        }
//        else
//        {
//            resize(height()*scale.w/scale.h,height());
//        }
//        // scale.w/scale.h
//        // width()/height()
//    }
    ui->graphicsView->resize(ui->widget->width()-10-ui->graphicsView->pos().x(),
                             ui->widget->height()-10-ui->graphicsView->pos().y());
    ui->startGameButton->setGeometry(width()-80,height()-60,70,30);
////    QMainWindow::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    //        QMessageBox::information(NULL,"Hello World","Hello World");
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{

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
