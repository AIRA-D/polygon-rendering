#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <vector>
#include <cmath>

struct Point {
    int x, y;
};

namespace Ui {
class MainWindow;
}

class Form1 : public QMainWindow {
    Q_OBJECT

public:
    explicit Form1(QMainWindow *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    std::vector<Point> Points;
    bool isPolygonConvex(const std::vector<Point>& polygon);

private slots:
    void Button1Click();
};

#endif // MAINWINDOW_H
