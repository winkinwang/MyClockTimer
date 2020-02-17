/*********************************************************************/
/* Filename:    MyClockTimer.cpp                                                                           	   */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: A analog clock timer widget component  of QT                     */
/*                                                                   */
/*                                                                                               */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*  Email:      wyj0617mail@aliyun.com                                                             */
/*   Create:   2020-02-17                                                          		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2020-02-17     wangyunjin  Created                                                             */
/*********************************************************************/

#define TAG "MyClockTimer"
#include "MyClockTimer.h"
#include "QPainter"
#include "QTime"
#include "QFile"


#define LOGI(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__,__func__,__LINE__, ##__VA_ARGS__);}
#define LOGW(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}
#define LOGE(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}
#define LOGT(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}

MyClockTimer::MyClockTimer(QWidget *parent)
    : QWidget(parent)
{
    LOGI("enter")
    setGeometry(100, 100, 500, 500);

    mBackgroudPixmap = nullptr;
    mTimerNum = 0;

//    mDigitFont = QFont("楷体", 15, QFont::Bold, true);
    mDigitFont = QFont();
    mDigitFont.setBold(true);
    mDigitFont.setPixelSize(20);
//    mDigitFont.setUnderline(true);
//    mDigitFont.setOverline(true);
//    mDigitFont.setLetterSpacing(QFont::AbsoluteSpacing, 5);

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(tipsSlots()));
}

MyClockTimer::~MyClockTimer()
{
    if (mBackgroudPixmap != nullptr)
        delete mBackgroudPixmap;
    mTimer->stop();
    delete mTimer;
}

bool MyClockTimer::setBackgroundPicture(QString filePath) {

//    QString filePath = "D:\\project\\qt_workspace\\res\\black.jpg";
    QFile file(filePath);
    if (!file.exists()) {
        LOGI("file not exist")
        return false;
    }
    if (mBackgroudPixmap != nullptr) {
        delete mBackgroudPixmap;
    }
    mBackgroudPixmap = new QPixmap(filePath);
    return true;
}

void MyClockTimer::setDigitFont(QFont font) {
    mDigitFont = font;
}

bool MyClockTimer::start(int timerNum) {
    if (timerNum <= 0) {
        return false;
    }

    mTimerNum = timerNum;
    mTimer->stop();
    mTimer->start(1000);
}

void MyClockTimer::stop() {
    mTimer->stop();
    mTimerNum = 0;
}

void MyClockTimer::tipsSlots() {
//    LOGI("enter");

    if (mTimerNum <= 0) {
        return;
    }

    mTimerNum--;

    this->update();
}


void MyClockTimer::paintEvent(QPaintEvent *) {
    LOGI("enter");

    QPainter painter(this);

//    painter.drawLine(QPointF(width()/2, 0), QPointF(width()/2, height()));
//    painter.drawLine(QPointF(0, height()/2), QPointF(width(), height()/2));

    int oneCycleNum = 60;

    if (mBackgroudPixmap != nullptr) {
        QRect rec(QPoint(0,0), QPoint(this->width(), this->height()));
        painter.drawPixmap(rec, *mBackgroudPixmap);
    }

    int handSize = 3;

    static const QPoint handPoints[3] = {
        QPoint(handSize, 8),
        QPoint(-1*handSize, 8),
        QPoint(0, -90)
    };
//    static const QPoint handPoints[4] = {
//        QPoint(5, 8),
//        QPoint(-1*5, 8),
//        QPoint(5, -90),
//        QPoint(-5, -90)
//    };

    QColor fiveDegreeMarkColor(0, 127, 127, 191);
    QColor handColor(0, 0, 255, 191);
    QColor degreeMarkColor(127, 0, 127);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(degreeMarkColor);
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setFont(mDigitFont);
    painter.setPen(Qt::green);
    QString digitStr = QString::number(mTimerNum);
    QFontMetrics fontMetrics(mDigitFont);
    int nFontWidth = fontMetrics.width(digitStr);
    int nFontHight = fontMetrics.height();
    LOGI("font w:%d, h:%d", nFontWidth, nFontHight);
//    painter.drawText(0, nFontHight+8, digitStr);
    painter.drawText(-1*(nFontWidth)/2, nFontHight+8, digitStr);
//        painter.drawText(this->geometry(), Qt::AlignCenter,  "30");

    painter.setPen(Qt::NoPen);
    painter.setBrush(handColor);

    painter.save();
    painter.rotate(360 - 6.0 * (mTimerNum));
    painter.drawConvexPolygon(handPoints, 3);
    painter.restore();

    painter.setPen(fiveDegreeMarkColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }

    painter.setPen(QColor(0, 160, 230));
    painter.drawEllipse(-3,-3,6,6);

//    painter.setRenderHint(QPainter::Antialiasing, true);
//        // 设置画笔颜色
//    painter.setPen(QColor(0, 160, 230));
//    painter.drawLine(QPointF(0, height()/2), QPointF(width() / 2, height() / 2));
}


void MyClockTimer::resizeEvent(QResizeEvent *resizeEvent)
{
    LOGI("enter");
}
