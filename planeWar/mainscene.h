#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include "config.h"
#include "map.h"
#include "heroplane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"
#include <QIcon>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <ctime>
#include <QSound>

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void initScene();
    //启动游戏 用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //敌机出场
    void enemyToScene();
    //碰撞检测
    void collisionDetection();
public:
    QTimer m_Timer;
    //地图对象
    Map m_map;
    heroplane m_hero;
//    Bullet temp_bullet;
    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];
    //敌机出场时间间隔
    int m_recorder;
    //爆炸数组
    Bomb m_bombs[BOMB_NUM];
};
#endif // MAINSCENE_H
