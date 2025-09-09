//
// Created by Administrator on 25-9-8.
//
#ifndef PB_BASIC_H
#define PB_BASIC_H

#include <QProgressBar>
#include <QPainter>
#include <QStyleOption>
#include <QTimer>
#include <QPropertyAnimation>
#include <QLinearGradient>
#include <thread>

class pb_basic : public QProgressBar
{
    Q_OBJECT
public:
    pb_basic(QWidget *parent = nullptr) : QProgressBar(parent) {
        // 初始化范围，通常进度条是0-100
        setRange(0, 100);
    }

    // 虚函数，用于子类设置特定样式
    virtual void set_style() {
        // 基础样式可以在这里设置，或者子类重写
        setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px; } QProgressBar::chunk { background-color: #05B8CC; }");
    }

    // 设置值，并确保在有效范围内
    void set_value_(int num) {
        num = qBound(0, num, 100); // 确保值在0-100之间
        num = qBound(0, num, 100);
        int current = value();

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=]() mutable {
            if (current < num) {
                current++;
                setValue(current);
            } else {
                timer->stop();
                timer->deleteLater();
            }
        });
        timer->start(speed_); // 每80毫秒更新一次

        // setValue(num); // 使用QProgressBar自身的setValue方法
    }

    // 设置速度，并确保在有效范围内
    void set_speed_(double num) {
        num = qBound(0.0, num, 100.0); // 确保速度在0.0-100.0之间
        speed_ = num;
    }

private:
    double speed_ = 80.0; // 默认位80ms更新一次
};

class pb_circle : public pb_basic
{
public:
    pb_circle(QWidget *parent = nullptr) : pb_basic(parent) {}

    void set_style() override {
        // 圆形进度条通常需要自定义绘制，QSS支持有限
        // 这里先清空可能的样式表，依赖paintEvent
        setStyleSheet("");
    }

protected:
    void paintEvent(QPaintEvent *event) override;
};

class pb_block : public pb_basic
{
public:
    pb_block(QWidget *parent = nullptr) : pb_basic(parent) {}

    void set_style() override;
};

class pb_power : public pb_basic
{
public:
    pb_power(QWidget *parent = nullptr) : pb_basic(parent) {}

    void set_style() override {
        // 电量样式通常有颜色变化，低电量红色，高电量绿色
        // 更复杂的颜色动态变化可在paintEvent或通过QSS代理实现
        setStyleSheet("");
    }

protected:
    void paintEvent(QPaintEvent *event) override;
};

class pb_highlight : public pb_basic
{
public:
    pb_highlight(QWidget *parent = nullptr) : pb_basic(parent) {}

    void set_style() override;
};

#endif // PB_BASIC_H