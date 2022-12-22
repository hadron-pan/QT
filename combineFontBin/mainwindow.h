#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QIcon>
#include "filehead.h"

typedef struct
{
    char name[16];          /* 资源的头名字 */
    char ver[32];           /* 资源的版本号 */
    quint32 base_add;       /* 资源在flash中的基地址 */
    quint32 data_offset;    /* 资源中字体数据的偏移 */
    quint32 data_size;      /* 资源中字体数据的大小 */
    quint32 font_num;       /* 资源中字体的数量 */
    quint32 checkType;      /* 资源的校验类型 0:和校验*/
    quint32 check;          /* 资源的校验 */ //仅校验资源中的图片数据
} FileHeadTypeDef;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initScene();

public:
    QPushButton *btn,*btnSelect1,*btnSelect2;
    QLineEdit *lineeditFile1,*lineeditFile2;
    QLabel *label1,*label2;
    QLabel *labOffset;
    QLineEdit *lineeditLab;
    QFileDialog *fileDialog;
    QFile file;
    fileHead headMsg;

private slots:
    bool OpenFile_Clicked();
    bool SaveFile_Clicked();
};
#endif // MAINWINDOW_H
