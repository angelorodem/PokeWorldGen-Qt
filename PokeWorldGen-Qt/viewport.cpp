#include "viewport.h"

void Viewport::tick() {
    update();
    //QTimer::singleShot(16, this, SLOT(tick()));
}

Viewport::Viewport() {
    setFixedSize(800, 800);
    Generator gen;

    QCoreApplication::processEvents(QEventLoop::AllEvents, 300);

    mapa = gen.generate_map(28);
    noise = gen.terrain_noise;

    tileset_texture = std::make_shared<TilesetBioma>();
    TilePicker picker(tileset_texture);
    picker.exec();

    QTimer::singleShot(100, this, SLOT(tick()));
}

void Viewport::paintEvent(QPaintEvent *e) {
    QOpenGLWidget::paintEvent(e);
    QPainter p(this);
    p.setClipRect(e->rect());

    drawTiles(p);
    //drawDebug(p);



}

void Viewport::drawDebug(QPainter &p)
{
    p.fillRect(0, 0, width(), height(), Qt::white);
    p.setBrush(QBrush(Qt::white, Qt::SolidPattern));

    float x_m = static_cast<float>(width()) / mapa->size();
    float y_m = static_cast<float>(height()) / mapa->at(0).size();

    bool show_text = mapa->size() <= 32?true:false;

    for (uint32_t x = 0; x < mapa->size(); ++x) {
        for (uint32_t y = 0; y < (*mapa)[x].size(); ++y) {
            QString hei_t = QString::number((*noise)[x][y]);
            uint32_t hei_v = (*noise)[x][y];
            switch ((*mapa)[x][y]) {
            case Generator::muro_vertical_e:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::darkMagenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇒\n" + hei_t);
                break;
            case Generator::muro_vertical_w:
                p.fillRect(QRectF(x * x_m, y * y_m, y_m, y_m), Qt::darkMagenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇐\n" + hei_t);
                break;
            case Generator::muro_horizontal_n:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::magenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇑\n" + hei_t);
                break;
            case Generator::muro_horizontal_s:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::magenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇓\n" + hei_t);
                break;
            case Generator::quina_ne_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::gray);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "↗\n" + hei_t);
                break;
            case Generator::quina_nw_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::gray);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "↖\n" + hei_t);
                break;
            case Generator::quina_se_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::gray);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "↘\n" + hei_t);
                break;
            case Generator::quina_sw_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::gray);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "↙\n" + hei_t);
                break;
            case Generator::quina_ne_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::cyan);

                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇗\n" + hei_t);
                break;
            case Generator::quina_nw_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::cyan);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇖\n" + hei_t);
                break;
            case Generator::quina_se_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::cyan);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇘\n" + hei_t);
                break;
            case Generator::quina_sw_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::cyan);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "⇙\n" + hei_t);
                break;
            case Generator::solo:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), QColor(0, 90
                                                                      + hei_v / 1.5 > 255 ? 255 : 90
                                                                                            + hei_v / 1.5, 0));
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "" + hei_t);

                break;
            case Generator::water:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), QColor(0, 128, 255));
                break;
            case Generator::the_void:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), QColor(0, 0, 0));
                break;
            }
        }
    }
}

void Viewport::drawTiles(QPainter &p)
{
    p.fillRect(0, 0, width(), height(), Qt::white);
    p.setBrush(QBrush(Qt::white, Qt::SolidPattern));

    float x_m = static_cast<float>(width()) / mapa->size();
    float y_m = static_cast<float>(height()) / mapa->at(0).size();

    //p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), QColor(0, 0, 0));
    QPixmap* drawn_tile;

    for (uint32_t x = 0; x < mapa->size(); ++x) {
        for (uint32_t y = 0; y < (*mapa)[x].size(); ++y) {
            switch ((*mapa)[x][y]) {
            case Generator::muro_vertical_e:
                drawn_tile = (*tileset_texture->getTile(Generator::muro_vertical_e))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::muro_vertical_w:
                drawn_tile = (*tileset_texture->getTile(Generator::muro_vertical_w))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::muro_horizontal_n:
                drawn_tile = (*tileset_texture->getTile(Generator::muro_horizontal_n))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::muro_horizontal_s:
                drawn_tile = (*tileset_texture->getTile(Generator::muro_horizontal_s))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_ne_inter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_ne_inter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_nw_inter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_nw_inter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_se_inter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_se_inter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_sw_inter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_sw_inter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_ne_exter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_ne_exter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_nw_exter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_nw_exter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_se_exter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_se_exter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::quina_sw_exter:
                drawn_tile = (*tileset_texture->getTile(Generator::quina_sw_exter))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::solo:
                drawn_tile = (*tileset_texture->getTile(Generator::solo))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::water:
                drawn_tile = (*tileset_texture->getTile(Generator::water))[0].get();
                p.drawPixmap(QRectF(x * x_m, y * y_m, x_m, y_m),*drawn_tile,QRectF(0,0,16,16));

                break;
            case Generator::the_void:
                break;
            }
        }
    }
}
