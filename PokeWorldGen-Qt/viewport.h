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
        std::shared_ptr<std::vector<std::vector<Generator::tile_type>>> mapa;
        std::shared_ptr<std::vector<std::vector<uint32_t>>> noise;
};

#endif // VIEWPORT_H
