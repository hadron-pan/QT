#ifndef CONFIG_H
#define CONFIG_H

/********** 主窗口配置数据 **********/
#define MAINWINDOW_WIDTH  512
#define MAINWINDOW_HEIGHT 300
#define MAINWINDOW_TITLE  "combineFontBin v1.0"
#define MAINWINDOW_PATH   "./plane.rcc" //rcc文件路径
#define MAINWINDOW_ICON   ":/res/hadron.png"

/********** 内存空间配置数据 **********/
#define PAGE_LENGTH		1024
#define READ_LENGTH     (8*1024*PAGE_LENGTH)//读取缓冲buff长度，最大8M

/********** Flash配置数据 **********/
#define FILEHEAD_SIZE 256
#define DATA_OFFSET 1024*1024
#define FLASHADDR_FONT 0x60800000

/********** 字体文件配置数据 **********/
#define FONT_NUM 2

#endif // CONFIG_H
