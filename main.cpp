#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    app.setWindowIcon(QIcon(":/Images/Snake/upArr"));
    MainWindow window;
    int w,h;
    bool ok;
    w=QInputDialog::getInt(NULL,"Số dòng:","Nhập số dòng:",0,0,100,1,&ok);
    h=QInputDialog::getInt(NULL,"Số cột:", "Nhập số cột:", 0,0,100,1,&ok);
    if(!ok) return 0;
//    window.scene->gameArea.updateSize(15,15,16,16);
    window.scene->gameArea.updateSize(w,h,16,16);
//    window.setWindowFlag(Qt::FramelessWindowHint);
//    window.showMaximized();
    window.show();

    return app.exec();
}
