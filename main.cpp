#include <QApplication>

#include "src/MyClockTimer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString currentPath = QCoreApplication::applicationDirPath();
    printf("cur dir:%s\n", currentPath.toStdString().data());



    MyClockTimer *myClock = new MyClockTimer();
    myClock->show();
    QString filePath = "res/bg.jpg";
    myClock->setBackgroundPicture(filePath);
    myClock->start(30);



    return a.exec();
}
