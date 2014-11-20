#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qsrand(QTime::currentTime().msec());
    p1 = QPointF(width()/2, height()/2);
    segCount = 6;
    recursive(QPointF(width()/2, height()-20), QPointF(width()/2, 20), segCount);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::recursive(QPointF start, QPointF end, int seg)
{
    if(seg <= 0) {
        return;
    }
    QPointF mid = average(start, end);

    QPointF vecPerp = createVec(start, end);

    vecPerp = normalizeVec(vecPerp);

    vecPerp = perpendicular(vecPerp);

    vecPerp *= (seg * random(10));

    mid.setX(mid.x()+vecPerp.x());
    mid.setY(mid.y()+vecPerp.y());

    if(seg == 1) {
        QLineF t = QLineF(start, mid);
        line.push_back(t);
        t = QLineF(mid, end);
        line.push_back(t);

    }

    recursive(start, mid, seg - 1);
    recursive(mid, end, seg - 1);
}

inline QPointF Dialog::average(QPointF p1, QPointF p2)
{
    return QPointF((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);
}

int Dialog::random(int a)
{
    int result = qrand() % a;
    if(qrand() % 2) {
        result = -result;
    }
    return result;
}

float Dialog::lengthLine(QPointF p1, QPointF p2)
{
    float x = (p2.x() - p1.x()) * (p2.x() - p1.x());
    float y = (p2.y() - p1.y()) * (p2.y() - p1.y());
    return qSqrt(x + y);
}

QPointF Dialog::createVec(QPointF p1, QPointF p2)
{
    return QPointF(p2 - p1);
}

float Dialog::lengthVec(QPointF p)
{
    return qSqrt(p.x()*p.x() + p.y()*p.y());
}

QPointF Dialog::normalizeVec(QPointF p)
{
    float len = lengthVec(p);
    return QPointF(p.x()/len, p.y()/len);
}

QPointF Dialog::perpendicular(QPointF p)
{
    return QPointF(p.y()* - 1, p.x());
}

void Dialog::paintEvent(QPaintEvent *pe)
{
    QPainter p(this);
    p.setPen(Qt::blue);

    for(int i = 0; i < line.length(); i++) {
        p.drawLine(line.at(i));
    }
}

void Dialog::mousePressEvent(QMouseEvent *me)
{
    if(me->button()) {
        line.clear();
        p1 = QPointF(me->pos().x(), me->pos().y());
        recursive(QPointF(width()/2, height()-20), p1, segCount);
    }
    repaint();
}
