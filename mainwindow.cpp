#include "mainwindow.h"
#include "ui_mainwindow.h" // 如果使用了Qt Designer的.ui文件，需要包含此头文件
#include "pb_basic.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStatusBar> // 添加statusBar()函数所需的头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建一个 widget 作为中央部件，并设置其布局
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建一个垂直布局，用于排列多个进度条
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 1. 创建块状进度条 (pb_block)
    pb_block *blockProgressBar = new pb_block(centralWidget);
    blockProgressBar->setRange(0, 100);
    blockProgressBar->set_value_(50); // 使用正确的函数名set_value_
    blockProgressBar->set_style();
    mainLayout->addWidget(blockProgressBar);

    // 2. 创建圆形进度条 (pb_circle)
    pb_circle *circleProgressBar = new pb_circle(centralWidget);
    circleProgressBar->setRange(0, 100);
    circleProgressBar->set_value_(30);
    circleProgressBar->set_style();
    circleProgressBar->setFixedSize(100, 100);
    mainLayout->addWidget(circleProgressBar);

    // 3. 创建电量样式进度条 (pb_power)
    pb_power *powerProgressBar = new pb_power(centralWidget);
    powerProgressBar->setRange(0, 100);
    powerProgressBar->set_value_(80);
    powerProgressBar->set_style();
    mainLayout->addWidget(powerProgressBar);

    // 4. 创建高亮进度条 (pb_highlight)
    pb_highlight *highlightProgressBar = new pb_highlight(centralWidget);
    highlightProgressBar->setRange(0, 100);
    highlightProgressBar->set_value_(70);
    highlightProgressBar->set_style();
    mainLayout->addWidget(highlightProgressBar);

    // 显示状态栏消息
    statusBar()->showMessage("进度条已就绪", 3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}