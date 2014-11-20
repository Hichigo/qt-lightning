#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QTime>
#include <qmath.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QPointF p1;
    QVector<QPointF> light;
    QVector<QLineF> line;
    int segCount;

    void recursive(QPointF start, QPointF end, int seg);
    inline QPointF average(QPointF p1, QPointF p2);
    inline int random(int a);
    float lengthLine(QPointF p1, QPointF p2);
    QPointF createVec(QPointF p1, QPointF p2);
    float lengthVec(QPointF p);
    inline QPointF normalizeVec(QPointF p);
    inline QPointF perpendicular(QPointF p);

private:
    Ui::Dialog *ui;
    void paintEvent(QPaintEvent *pe);
    void mousePressEvent(QMouseEvent *me);
};

#endif // DIALOG_H
