#include "pb_basic.h"
#include <QPainter>

// pb_circle 的 paintEvent 实现
void pb_circle::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    int side = qMin(width(), height());
    QRectF outerRect(0, 0, side, side);

    // 绘制背景圆环
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(220, 220, 220)); // 灰色背景
    painter.drawEllipse(outerRect);

    // 绘制进度圆弧
    double progress = (value() - minimum()) / double(maximum() - minimum());
    int startAngle = 90 * 16; // 从90度（顶部）开始
    int spanAngle = -progress * 360 * 16; // 顺时针绘制，负值表示顺时针

    painter.setBrush(QColor(72, 177, 255)); // 蓝色进度
    painter.drawPie(outerRect, startAngle, spanAngle);

    // 绘制中心文本（可选）
    painter.setPen(Qt::black);
    painter.drawText(outerRect, Qt::AlignCenter, QString::number(value()) + "%");
}

// pb_block 的 set_style 实现
void pb_block::set_style() {
    // 使用QSS设置块状样式
    setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid #C0C0C0;"
        "    border-radius: 3px;"
        "    text-align: center;"
        "    background-color: #F0F0F0;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #76ee00;"
        "    border-radius: 2px;"
        "    margin: 1px;"
        "    width: 10px;" // 块宽
        "}"
    );
}

// pb_power 的 paintEvent 实现
void pb_power::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 根据值选择颜色
    QColor fillColor;
    if (value() < 20) {
        fillColor = Qt::red;
    } else if (value() < 50) {
        fillColor = Qt::yellow;
    } else {
        fillColor = Qt::green;
    }

    // 绘制背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::lightGray);
    painter.drawRoundedRect(rect(), 2, 2);

    // 绘制进度
    int fillWidth = static_cast<int>(rect().width() * value() / 100.0);
    QRect fillRect(rect().left(), rect().top(), fillWidth, rect().height());
    painter.setBrush(fillColor);
    painter.drawRoundedRect(fillRect, 2, 2);

    // 绘制文本
    painter.setPen(Qt::black);
    painter.drawText(rect(), Qt::AlignCenter, QString::number(value()) + "%");
}

// pb_highlight 的 set_style 实现
void pb_highlight::set_style() {
    // 使用QSS设置高亮渐变样式
    setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid #808080;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #E0E0E0, stop:1 #F5F5F5);"
        "    color: white;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #00C9FF, stop:1 #00FFE0);"
        "    border-radius: 3px;"
        "}"
    );
}

