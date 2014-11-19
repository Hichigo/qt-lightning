#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    p1 = QPointF(width()/2, height()/2);

    recursive(QPointF(width()/2, height()-20), QPointF(width()/2, 20), 8);
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
    mid.setX(mid.x() + (seg * 10));
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

void Dialog::paintEvent(QPaintEvent *pe)
{
    QPainter p(this);
    p.setPen(Qt::red);

    p.drawEllipse(p1, 20, 20);

    for(int i = 0; i < line.length(); i++) {
        p.drawLine(line.at(i));
    }
}

void Dialog::mousePressEvent(QMouseEvent *me)
{
    if(me->button()) {
        p1 = QPointF(me->pos().x(), me->pos().y());
    }
    repaint();
}
