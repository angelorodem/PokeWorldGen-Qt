#include "viewport.h"

void Viewport::tick()
{
    update();
    QTimer::singleShot(16,this,SLOT(tick()));
}

Viewport::Viewport()
{    
    setFixedSize(300,300);
    Generator gen;
    mapa = gen.analyseNoise(gen.simplexNoise(150,150,5),5);

    QTimer::singleShot(16,this,SLOT(tick()));
}

void Viewport::paintEvent(QPaintEvent *e)
{
    QOpenGLWidget::paintEvent(e);
    QPainter p(this);
    p.setClipRect(e->rect());
    //p.fillRect(0,0,width(),height(),Qt::black);
    p.setBrush(QBrush(Qt::white,Qt::SolidPattern));

    for (uint32_t x = 0; x < mapa->size(); ++x) {
        for (uint32_t y = 0; y < mapa[0][x].size(); ++y) {
            p.fillRect(x*2,y*2,2,2,Qt::red);
        }
    }



}
