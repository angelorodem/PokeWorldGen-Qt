#include "viewport.h"

void Viewport::tick() {
    update();
    //QTimer::singleShot(16, this, SLOT(tick()));
}

Viewport::Viewport() {
    setFixedSize(800, 800);
    Generator gen;

    QCoreApplication::processEvents(QEventLoop::AllEvents, 300);

    mapa = gen.generate_map();
    noise = gen.terrain_noise;

    QTimer::singleShot(16, this, SLOT(tick()));
}

void Viewport::paintEvent(QPaintEvent *e) {
    QOpenGLWidget::paintEvent(e);
    QPainter p(this);
    p.setClipRect(e->rect());
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
            case Generator::linha_horizontal:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LH\n" + hei_t);
                break;
            case Generator::linha_horizontal_end_e:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                           "LHEe\n" + hei_t);
                break;
            case Generator::linha_horizontal_end_w:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LHEw\n" + hei_t);
                break;
            case Generator::linha_vertical:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LV\n" + hei_t);
                break;
            case Generator::linha_vertical_end_n:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LVEn\n" + hei_t);
                break;
            case Generator::linha_vertical_end_s:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LVEs\n" + hei_t);
                break;
            case Generator::linha_quina_ne:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LQne\n" + hei_t);
                break;
            case Generator::linha_quina_se:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LQsw\n" + hei_t);
                break;
            case Generator::linha_quina_sw:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LQsw\n" + hei_t);
                break;
            case Generator::linha_quina_nw:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::yellow);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "LQnw\n" + hei_t);
                break;
            case Generator::muro_vertical_e:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::darkMagenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "MVe\n" + hei_t);
                break;
            case Generator::muro_vertical_w:
                p.fillRect(QRectF(x * x_m, y * y_m, y_m, y_m), Qt::darkMagenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "MVw\n" + hei_t);
                break;
            case Generator::muro_horizontal_n:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::magenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "MHn\n" + hei_t);
                break;
            case Generator::muro_horizontal_s:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::magenta);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "MHs\n" + hei_t);
                break;
            case Generator::ponto:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::red);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "P\n" + hei_t);
                break;
            case Generator::quina_ne_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::white);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QneI\n" + hei_t);
                break;
            case Generator::quina_nw_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::white);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QnwI\n" + hei_t);
                break;
            case Generator::quina_se_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::gray);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QseI\n" + hei_t);
                break;
            case Generator::quina_sw_inter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::gray);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QswI\n" + hei_t);
                break;
            case Generator::quina_ne_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::blue);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QneE\n" + hei_t);
                break;
            case Generator::quina_nw_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::blue);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QnwE\n" + hei_t);
                break;
            case Generator::quina_se_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::blue);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QseE\n" + hei_t);
                break;
            case Generator::quina_sw_exter:
                p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), Qt::blue);
                if(show_text)
                    p.drawText(QRectF(x * x_m, y * y_m, (x + 1) * x_m, (y + 1) * y_m),
                               "QswE\n" + hei_t);
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
                //p.fillRect(QRectF(x * x_m, y * y_m, x_m, y_m), QColor(255, 0, 0));

                break;
            default:
                break;
            }
        }
    }




}
