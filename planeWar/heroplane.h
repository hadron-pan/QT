#ifndef HEROPLANE_H
#define HEROPLANE_H

#include <QPixmap>
#include <QRect>
#include "bullet.h"

class heroplane
{
public:
    heroplane();
    void shoot();
    void setPosition(int x,int y);

public:
    QPixmap m_Plane;

    int m_planex;
    int m_planey;
    //飞机的矩形边框
    QRect m_Rect;
    //弹夹
    Bullet m_bullets[BULLET_NUM];
    //发射间隔时间记录
    int m_recorder;
};

#endif // HEROPLANE_H
