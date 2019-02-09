#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QTimer>
#include <cstdint>
#include <memory>

#include "tilepicker.h"
#include "tilesetbioma.h"
#include "generator.h"

class Viewport : public QOpenGLWidget {
        Q_OBJECT
    private slots:
        void tick();
    public:
        Viewport();

        void paintEvent(QPaintEvent *e);
        void keyPressEvent(QKeyEvent *e);

        void drawDebug(QPainter &p);
        void drawTiles(QPainter &p);
    private:
        bool activate_debug = true;
        Generator::tile_2d_vector mapa;
        Generator::ui32_2d_vector noise;
        std::shared_ptr<TilesetBioma> tileset_texture;
};

#endif // VIEWPORT_H
