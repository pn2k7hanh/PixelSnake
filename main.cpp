#include "mainwindow.h"

#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    int w,h;
    bool ok;
    w=QInputDialog::getInt(NULL,"Số dòng:","Nhập số dòng:",0,0,20,1,&ok);
    if(ok) h=QInputDialog::getInt(NULL,"Số cột:", "Nhập số cột:", 0,0,20,1,&ok);
    else return 0;
    window.scene->gameArea.updateSize(w,h,25,25);
    window.show();

    return app.exec();
}
