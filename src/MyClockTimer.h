/*********************************************************************/
/* Filename:    MyAnalogClock.h                                                                           	   */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: A analog clock widget component  of QT                     */
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

#ifndef MYCLOCKTIMER_H
#define MYCLOCKTIMER_H

#include <QWidget>
#include "QTimer"

class MyClockTimer : public QWidget
{
    Q_OBJECT
public:
    explicit MyClockTimer(QWidget *parent = 0);
    ~MyClockTimer();

    bool setBackgroundPicture(QString filePath);

    void setDigitFont(QFont font);

    bool start(int timerNum);

    void stop();

public slots:
    void tipsSlots();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QTimer *mTimer;
    QPixmap *mBackgroudPixmap;
    int mTimerNum;
    int mCurNum;
    QFont mDigitFont;
};



#endif // MYCLOCKTIMER_H
