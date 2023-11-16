#include "mainwindow.h"
#include "ui_mainwindow.h"

Form1::Form1(QMainWindow *parent) : QMainWindow(parent) {
    setMouseTracking(true);
    ui->setupUi(this);
    connect(ui->Button1, &QPushButton::clicked, this, &Form1::Button1Click);
}

void Form1::mousePressEvent(QMouseEvent *event) {
    Points.push_back({ event->x(), event->y() });
    update();
}


void Form1::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.setPen(Qt::black);

    // Проверяем, что количество вершин многоугольника больше 2
    if (Points.size() >= 3) {
        QPolygon polygon;

        for (const Point& p: Points) {
            polygon << QPoint(p.x, p.y);
        }

        painter.drawPolygon(polygon);
    }
}



bool Form1::isPolygonConvex(const std::vector<Point>& polygon) {
    int n = polygon.size();
    bool isNegative = false;
    bool isPositive = false;

    for (int i = 0; i < n; i++) {
        double dx1 = polygon[(i + 2) % n].x - polygon[(i + 1) % n].x;
        double dy1 = polygon[(i + 2) % n].y - polygon[(i + 1) % n].y;
        double dx2 = polygon[i].x - polygon[(i + 1) % n].x;
        double dy2 = polygon[i].y - polygon[(i + 1) % n].y;

        double crossProduct = dx1 * dy2 - dx2 * dy1;

        if (crossProduct < 0) {
            isNegative = true;
        } else if (crossProduct > 0) {
            isPositive = true;
        }

        if (isNegative && isPositive) {
            return false;
        }
    }

    return true;
}

void Form1::Button1Click() {
    if (isPolygonConvex(Points)) {
        QMessageBox::information(this, "Результат", "Многоугольник выпуклый");
    } else {
        QMessageBox::warning(this, "Результат", "Многоугольник невыпуклый");
    }
}


