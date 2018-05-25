#ifndef GENERATOR_H
#define GENERATOR_H

#include <QImage>
#include <QDebug>
#include <QLabel>
#include <QRgb>
#include <QApplication>
#include <QTime>

#include <random>
#include <ctime>
#include <cmath>
#include <array>
#include <memory>

#include "../FastNoise/FastNoise.h"

#define contem(a,b) (((a)&(b))==(a))

class Generator {
        FastNoise noise_machine;
        QLabel *show_map_label;
    public:
        /*   N
         * W   E
         *   S
        */

        /*
        tile 16x16

        total: 8x426

        */

        enum tile_type : uint32_t {
            quina_ne_exter = 136,
            quina_se_exter = 10,
            quina_sw_exter = 34,
            quina_nw_exter = 160,

            quina_ne_inter = 140,
            quina_nw_inter = 161,

            linha_vertical = 130,
            linha_horizontal = 40,

            muro_horizontal_w = 138,
            muro_horizontal_e = 162,
            muro_vertical_n = 42,
            muro_vertical_s = 168,

            solo = 511,

            ponto = 16,

        }



        Generator();
        std::shared_ptr<std::vector<std::vector<uint32_t>>> simplexNoise(uint32_t xsize,
                uint32_t ysize,
                uint32_t levels);


        std::shared_ptr<std::vector<std::vector<tile_type>>> analyse_map(
            std::shared_ptr<std::vector<std::vector<uint32_t>>> noise);

        tile_type categorize_dots(uint32_t x, uint32_t y,
                                  std::shared_ptr<std::vector<std::vector<uint32_t>>> noise);

};

#endif // GENERATOR_H
