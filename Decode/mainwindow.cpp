#include "mainwindow.h"

#define PAGE_LENGTH		1024
#define READ_LENGTH     (8*1024*PAGE_LENGTH+1024)//读取缓冲buff长度，最大8M

QString filename,path;
uint8_t readBuf[READ_LENGTH];
QStringList filePath_list;
QStringList fileName_list;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(400,400);
    this->setWindowTitle("花样解密软件");
    btn = new QToolButton;
    Decode = new QPushButton("解密",this);
    lineedit = new QLineEdit("",this);
    label = new QLabel(this);
    hintLbel = new QLabel(this);
    fileDialog = new QFileDialog(this);
    action = new QWidgetAction(lineedit);

    btn->setText("..");
    btn->setCursor(Qt::ArrowCursor);
    lineedit->setGeometry(80, 150, 240, 30);
    action->setDefaultWidget(btn);
    lineedit->addAction(action, QLineEdit::TrailingPosition);

    Decode->setGeometry(160,200,80,40);
    label->setGeometry(80, 130, 240, 20);
    label->setText("请选择JED加密文件:");

    hintLbel->setGeometry(80,180,240,20);
    Decode->setEnabled(false);

    connect(btn,SIGNAL(clicked()),this,SLOT(Openfile_Clicked()));
    connect(Decode,SIGNAL(clicked()),this,SLOT(Decode_Clicked()));
}

MainWindow::~MainWindow()
{
}

bool MainWindow::Openfile_Clicked()
{
    QFileInfo info;
    filePath_list = fileDialog->getOpenFileNames(this,"Open Files","",tr("JED(*.JED)"));

    //利用qfileinfo获取文件名
    for(int i=0;i<filePath_list.size();i++)
    {
        info = QFileInfo(filePath_list[i]);//获得每个路径的文件信息
        fileName_list << info.fileName();//将文件名一个一个存入列表中
    }
    hintLbel->setText("");
    lineedit->setText(fileName_list[0]);
    Decode->setEnabled(true);

    return true;
}

bool MainWindow::Decode_Clicked()
{
    int fileLenth;
    QByteArray array;
    QByteArray arrayOut;
    QString newPath;
    QString fileUrl;

    newPath = filePath_list[0].section('/',0,-2) + "/DecodePat";

    QDir dir(newPath);
    if(!dir.exists(newPath))
    {
        //路径不存在，则创建路径
        if(!dir.mkdir(newPath))
        {
            hintLbel->setText("创建解密后花样存储文件夹失败！");
            return false;//路径创建失败就没办法了，通常不会失败
        }

    }

    for(int patNum=0;patNum<filePath_list.size();patNum++)
    {
        file.setFileName(filePath_list[patNum]);
        lineedit->setText(fileName_list[patNum]);
        QString newFileName = fileName_list[patNum];
        if (!file.open(QIODevice::ReadOnly))
            return false;
        fileLenth = file.size();
        array.resize(256);
        if(fileLenth < READ_LENGTH)
        {
            array = file.read(256);
        }
        else //花样文件大于2M
        {
            hintLbel->setText("当前文件超过2M了！");
            Decode->setEnabled(false);
            return false;
        }
        //处理头数据
        char *readHeadBuf;
        uint32_t noAesNum;
        uint8_t ReadCheckH,ReadCheckL;
        uint16_t ReadChecksum;
        uint16_t wholeBlockNum = 0;
        uint16_t remainBlockNum = 0;
        uint32_t i,j;
        readHeadBuf = array.data();
        if(readHeadBuf[0] == 0x4A && readHeadBuf[1] == 0x45 && readHeadBuf[2] == 0x44)
        {
            ExtendKey();
        }
        else
        {
            hintLbel->setText("当前文件不是一个花样加密文件！");
            file.close();
            Decode->setEnabled(false);
            return false;
        }
        noAesNum =((readHeadBuf[19] & 0xff) | (((uint32_t)(readHeadBuf[18]) << 8) & 0xff00) | (((uint32_t)(readHeadBuf[17]) << 16) & 0xff0000)| (((uint32_t)(readHeadBuf[16]) << 24) & 0xff000000));
        ReadCheckH = readHeadBuf[178]; //获取校验值
        ReadCheckL = readHeadBuf[179];
        ReadChecksum = ((ReadCheckH << 8) | ReadCheckL) & 0xffff;
        wholeBlockNum = (noAesNum) / 256; //以256一包为单位进行解密
        remainBlockNum = (noAesNum) % 256;
        //处理数据内容
        while(file.atEnd() == false)
        {
            array += file.readLine();
        }
        memcpy(readBuf,array.data(),array.size());
        for (i = 0; i < wholeBlockNum; i++)
        {
            UnLockBox((uint8_t *)(&readBuf[256 + 256 * i]));
        }
        if (remainBlockNum)
        {
            UnLockBox((uint8_t *)(&readBuf[256 + 256 * i]));
        }

        //重新计算解密后的校验和
        uint16_t Checksum = 0;
        for (i = 0; i < wholeBlockNum; i++)
        {
            for (j = 0; j < 256; j++)
            {
                Checksum += readBuf[256 * (1 + i) + j];
            }
        }
        if (remainBlockNum)
        {
            for (j = 0; j < remainBlockNum; j++)
            {
                Checksum += readBuf[256 * (1 + i) + j];
            }
        }
        //比较和校验值
        if (Checksum != ReadChecksum)
        {
            hintLbel->setText("当前文件和检验通不过啊！");
            file.close();
            Decode->setEnabled(false);
            return false;
        }
        file.close();

        //解密后导出文件
        arrayOut.resize(noAesNum);
        memcpy(arrayOut.data(), &readBuf[256], noAesNum);
        fileUrl = newPath + "/" + newFileName;
        file.setFileName(fileUrl);
        file.open(QIODevice::ReadWrite);
        file.write(arrayOut);
        file.close();
        hintLbel->setText("当前文件解密成功！");
    }
    Decode->setEnabled(false);
    hintLbel->setText("全部文件解密成功！");
    filePath_list.clear();//清空列表
    fileName_list.clear();
    return true;
}
