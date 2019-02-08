#ifndef TILEPICKER_H
#define TILEPICKER_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QDir>

#include "tilesetbioma.h"

#include <memory>

namespace Ui {
class TilePicker;
}

class TilePicker : public QWidget {
        Q_OBJECT

    public:
        explicit TilePicker(std::shared_ptr<TilesetBioma> bioma, QWidget *parent = 0);
        ~TilePicker();

    private slots:
        void on_ok_but_clicked();

        void on_load_but_clicked();

        void update_tile_pos();

        void on_proximo_but_clicked();

        void on_add_but_clicked();

    private:
        Ui::TilePicker *ui;
        QImage imagem;
        uint32_t current_tile = 0;
        std::vector<std::shared_ptr<std::vector<std::shared_ptr<QPixmap>>>> vetor_tipos;
        std::shared_ptr<std::vector<std::shared_ptr<QPixmap>>> temp_vector;

        std::shared_ptr<TilesetBioma> bioma_ref;

        uint32_t tile_width = 16, tile_height = 16;
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t x_o = 0;
        uint32_t y_o = 0;

        const uint32_t tiles_size = 13;
        const QString tiles_string[13] = {
            "Quina NE Externa",
            "Quina SE Externa",
            "Quina SW Externa",
            "Quina NW Externa",

            "Quina NE Interna",
            "Quina SE Interna",
            "Quina SW Interna",
            "Quina NW Interna",

            "Muro vertical west",
            "Muro vertical east",
            "Muro horizontal norte",
            "Muro horizontal sul",

            "Solo"
        };

        const uint32_t biomas_size = 10;
        const QString biomas_string[10] = {
            "Floresta tropical",
            "Floresta temperada",
            "Floresta boreal",

            "Grassland/Deserto",
            "Grassland",
            "Grassland/Boreal",

            "Neve",
            "Neve/Tundra",
            "Tundra",
            "Deserto",
        };

        Generator::tile_type tile_seq[13]  {
            Generator::quina_ne_exter,
            Generator::quina_se_exter,
            Generator::quina_sw_exter,
            Generator::quina_nw_exter,

            Generator::quina_ne_inter,
            Generator::quina_se_inter,
            Generator::quina_sw_inter,
            Generator::quina_nw_inter,

            Generator::muro_vertical_w,
            Generator::muro_vertical_e,
            Generator::muro_horizontal_n,
            Generator::muro_horizontal_s,

            Generator::solo
        };


};

#endif // TILEPICKER_H
