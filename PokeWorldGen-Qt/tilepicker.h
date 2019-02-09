#ifndef TILEPICKER_H
#define TILEPICKER_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QLabel>
#include <QVarLengthArray>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>

#include "tilesetbioma.h"

#include <memory>

namespace Ui {
class TilePicker;
}

class TilePicker : public QDialog {
    Q_OBJECT

public:
    bool loaded = false;
    explicit TilePicker(std::shared_ptr<TilesetBioma> bioma);
    ~TilePicker();

private slots:
    void on_ok_but_clicked();

    void on_load_but_clicked();

    void update_tile_pos();

    void on_proximo_but_clicked();

    void on_add_but_clicked();

    void on_pushButton_clicked();

private:


    Ui::TilePicker *ui;
    QImage imagem;
    uint32_t current_tile = 0;

    QVarLengthArray<TilesetBioma::tex_rect_vector> vetor_tipos;
    TilesetBioma::tex_rect_vector temp_vector;

    std::shared_ptr<TilesetBioma> bioma_ref;

    uint32_t tile_width = 16, tile_height = 16;

    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t x_o = 0;
    uint32_t y_o = 0;

    const uint32_t tiles_size = 13;
    const QString tiles_string[13] = {
        "NE External edge",
        "SE External edge",
        "SW External edge",
        "NW External edge",

        "NE Internal edge",
        "SE Internal edge",
        "SW Internal edge",
        "NW Internal edge",

        "Vertical Wall West",
        "Vertical Wall East",
        "Horizontal Wall North",
        "Horizontal Wall South",

        "Ground"
    };

    const uint32_t biomas_size = 10;
    const QString biomas_string[10] = {
        "Tropical Forest",
        "Temperate Forest",
        "Boreal Forest",

        "Grassland/Desert",
        "Grassland",
        "Grassland/Boreal",

        "Snow",
        "Snow/Tundra",
        "Tundra",
        "Desert",
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
