#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH  512
#define GAME_HEIGHT 768
#define GAMW_TITLE  "万闯打飞机 v1.0"
#define GAME_RES_PATH "./plane.rcc" //rcc文件路径
#define GAME_ICON   ":/res/app.ico"

/********** 地图配置数据 **********/
#define MAP_PATH ":/res/img_bg_level_1.jpg" //地图图片路径
#define MAP_SCROLL_SPEED 2 //地图滚动速度

#define GAME_RATE 10 //刷新间隔，帧率 单位毫秒

/********** 飞机配置数据 **********/
#define HERO_PATH ":/res/chuang.png"

/********** 子弹配置数据 **********/
#define BULLET_PATH ":/res/bullet_11.png"
#define BULLET_SPEED 5
#define BULLET_NUM 30 //弹夹中子弹总数
#define BULLET_INTERVAL 20 //发射子弹时间间隔

/********** 敌机配置数据 **********/
#define ENEMY_PATH ":/res/img-plane_5.png"
#define ENEMY_SPEED 5
#define ENEMY_NUM 20 //敌机总数
#define ENEMY_INTERVAL 30 //敌机出场时间间隔

/********** 爆炸配置数据 **********/
#define BOMB_PATH ":/res/bomb-%1.png"
#define BOMB_MAX 7 //爆炸图片最大索引
#define BOMB_NUM 20 //爆炸数量
#define BOMB_INTERVAL 20 //爆炸切图时间间隔

/********** 音效配置数据 **********/
#define SOUND_BACKGROUND ":/res/bg.wav"
#define SOUND_BOMB ":/res/bomb.wav"

#endif // CONFIG_H
