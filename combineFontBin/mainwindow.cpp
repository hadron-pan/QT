#include "mainwindow.h"
#include "config.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initScene();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initScene()
{
    setFixedSize(MAINWINDOW_WIDTH,MAINWINDOW_HEIGHT);
    setWindowTitle(MAINWINDOW_TITLE);
    setWindowIcon(QIcon(MAINWINDOW_ICON));

    btn = new QPushButton("合并",this);
    btn->setGeometry(216,200,80,40);

    btnSelect1 = new QPushButton("选择文件",this);
    btnSelect1->setGeometry(370,50,80,30);

    btnSelect2 = new QPushButton("选择文件",this);
    btnSelect2->setGeometry(370,100,80,30);

    lineeditFile1 = new QLineEdit("",this);
    lineeditFile1->setGeometry(156,50,200,30);
    lineeditFile1->setPlaceholderText("");

    lineeditFile2 = new QLineEdit("",this);
    lineeditFile2->setGeometry(156,100,200,30);
    lineeditFile2->setPlaceholderText("");

    label1 = new QLabel("Font文件:",this);
    label1->setGeometry(75,50,200,30);

    label2 = new QLabel("Font文件:",this);
    label2->setGeometry(75,100,200,30);

    labOffset = new QLabel("偏移地址:",this);
    labOffset->setGeometry(76,150,200,30);
    lineeditLab = new QLineEdit("0x100000",this);
    lineeditLab->setGeometry(156,150,200,30);
    lineeditLab->setPlaceholderText("例:0x100000");

    connect(btnSelect1,SIGNAL(clicked()),this,SLOT(OpenFile_Clicked()));
    connect(btnSelect2,SIGNAL(clicked()),this,SLOT(OpenFile_Clicked()));
    connect(btn,SIGNAL(clicked()),this,SLOT(SaveFile_Clicked()));
}


int i = 0; //i-1:选中文件1 i-2:选中文件2
QString offsetData;
QStringList fileName_list;
QStringList filePath_list;

uint8_t readBuf[READ_LENGTH];


bool MainWindow::OpenFile_Clicked()
{
    QFileInfo info;
    QString filePath;

    filePath = fileDialog->getOpenFileName(this,"Open Files","",tr("BIN(*.BIN)"));
    if (filePath.isEmpty())
    {
        QMessageBox::warning(this, "提示", "未选择数据文件", "确定");
        return false;
    }
    else
    {
        filePath_list << filePath;
        //利用qfileinfo获取文件名
        info = QFileInfo(filePath_list[i]);//获得每个路径的文件信息
        fileName_list << info.fileName();//将文件名一个一个存入列表中
        QPushButton *btnRecive  = (QPushButton*) sender();
        if (btnRecive == btnSelect1)
        {
            lineeditFile1->setText(fileName_list[i]);
        }
        else if(btnRecive == btnSelect2)
        {
            lineeditFile2->setText(fileName_list[i]);
        }
        i++;
    }

    return true;
}

bool MainWindow::SaveFile_Clicked()
{
    uint32_t file1Size,file2Size;
    uint32_t outfileSize;
    uint32_t checkFont1 = 0,checkFont2 = 0;
    int offsetValue;
    QByteArray array;
    QString fileUrl;
    /*偏移信息处理*/
    if(lineeditLab->text().isEmpty())
    {
        QMessageBox::warning(this, "提示", "请输入偏移地址", "确定");
        return false;
    }
    else
    {
        offsetData = lineeditLab->text();
        offsetValue = offsetData.toInt(nullptr,16);
    }

    /*初始化文件头信息*/
    FileHeadTypeDef fileHead;
    memcpy(fileHead.name,"BIN",sizeof(fileHead.name));
    memcpy(fileHead.ver,MAINWINDOW_TITLE,sizeof(fileHead.ver));
    fileHead.base_add = FLASHADDR_FONT;
    fileHead.data_offset = FILEHEAD_SIZE;
    fileHead.font_num = FONT_NUM;
    fileHead.checkType = 0;
    memset(headMsg.fileHeadbuf,0,FILEHEAD_SIZE);
    headMsg.getNameMsg(fileHead.name,sizeof(fileHead.name));
    headMsg.getVerMsg(fileHead.ver,sizeof(fileHead.ver));

    /*文件合并*/
    if(filePath_list.size() < 2)
    {
        QMessageBox::warning(this, "提示", "请选择文件", "确定");
        return false;
    }
    fileUrl = filePath_list[i - 2].section('/',0,-2) + "/combineFonBin.bin";

    file.setFileName(filePath_list[i - 2]);
    if(file.size() > offsetValue )
    {
        QMessageBox::warning(this, "提示", "偏移地址不足", "确定");
        return false;
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "提示", "文件打开失败", "确定");
        return false;
    }

    while(file.atEnd() == false)
    {
        array += file.readLine();
    }
    memcpy(readBuf,array.data(),array.size());
    file1Size = array.size();
    array.clear();
    file.close();
    /*计算字体文件1的校验和*/
    for(uint32_t i = 0;i < file1Size; i++)
    {
        checkFont1 += readBuf[i];
    }
    /*剩余没满1M空间补0*/
    for(uint32_t i = file1Size; i < (uint32_t)offsetValue;i++)
    {
        readBuf[i] = 0;
    }

    file.setFileName(filePath_list[i - 1]);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "提示", "文件打开失败", "确定");
        return false;
    }

    while(file.atEnd() == false)
    {
        array += file.readLine();
    }
    memcpy(&readBuf[offsetValue],array.data(),array.size());
    file2Size = array.size();
    array.clear();
    file.close();
    /*计算字体文件2校验和*/
    outfileSize = file2Size + offsetValue;
    for(uint32_t i = offsetValue;i < outfileSize; i++)
    {
        checkFont2 += readBuf[i];
    }

    fileHead.check = checkFont1 + checkFont2;
    headMsg.getCheckMsg(fileHead.checkType,fileHead.check);

    /*导出合并后的文件*/
    fileHead.data_size = outfileSize;
    headMsg.getResMsg(fileHead.base_add,fileHead.data_offset,fileHead.data_size,fileHead.font_num);

    file.setFileName(fileUrl);
    file.open(QIODevice::NewOnly|QIODevice::ReadWrite|QIODevice::Truncate);
    file.write(headMsg.fileHeadbuf,FILEHEAD_SIZE);
    file.write((const char*)readBuf,outfileSize);
    QMessageBox::warning(this, "提示", "文件保存成功", "确定");
    file.close();

    i = 0;
    fileName_list.clear();
    filePath_list.clear();
    return true;
}
