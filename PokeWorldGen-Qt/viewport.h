#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPaintEvent>
#include <QTimer>
#include <cstdint>
#include <memory>

#include "generator.h"

class Viewport : public QOpenGLWidget {
        Q_OBJECT
    private slots:
        void tick();
    public:
        Viewport();

        void paintEvent(QPaintEvent *e);
    private:
        Generator::tile_2d_vector mapa;
        Generator::ui32_2d_vector noise;
};

#endif // VIEWPORT_H
