#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AES_KEY.h"

#include <QMainWindow>
#include <QPushButton>
#include <qtoolbutton.h>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextEdit>
#include <QWidgetAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton *Openfile;
    QPushButton *Decode;
    QToolButton *btn;
    QLineEdit *lineedit;
    QWidgetAction *action;
    QTextEdit *text;
    QLabel *label,*hintLbel;
    QFileDialog *fileDialog;
    QFile file;
private slots:
    bool Openfile_Clicked();

    bool Decode_Clicked();
};
#endif // MAINWINDOW_H
