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

        /*
            u3_t3_floresta_tropical,
            u3_t2_floresta_temperada,
            u3_t1_floresta_boreal,
            u3_t0_neve,

            u2_t3_floresta_temperada,
            u2_t2_floresta_temperada,
            u2_t1_floresta_boreal,
            u2_t0_neve,

            u1_t3_grassland_deserto,
            u1_t2_grassland_deserto,
            u1_t1_grassland_boreal,
            u1_t0_neve_tundra,

            u0_t3_deserto,
            u0_t2_grassland_deserto,
            u0_t1_grassland,
            u0_t0_tundra,*/



        enum biomas_type : uint32_t {
            floresta_tropical,
            floresta_temperada,
            floresta_boreal,

            grassland_deserto,
            grassland,
            grasslan_boreal,

            neve,
            neve_tundra,
            tundra,
            deserto
        };


        enum tile_type : uint32_t {
            quina_ne_exter = 216,
            quina_se_exter = 27,
            quina_sw_exter = 54,
            quina_nw_exter = 432,

            quina_ne_inter = 447,
            quina_se_inter = 510,
            quina_sw_inter = 507,
            quina_nw_inter = 255,

            linha_vertical = 146,
            linha_horizontal = 56,

            linha_vertical_end_s = 18,
            linha_vertical_end_n = 144,

            linha_horizontal_end_e = 24,
            linha_horizontal_end_w = 48,

            linha_quina_ne = 152,
            linha_quina_se = 26,
            linha_quina_sw = 50,
            linha_quina_nw = 176,

            muro_vertical_w = 154,
            muro_vertical_e = 178,
            muro_horizontal_n = 58,
            muro_horizontal_s = 184,

            ponto = 16,

            solo = 511,

            the_void = 0
        };

        Generator();

        std::shared_ptr<std::vector<std::vector<Generator::tile_type>>> tiles;

        std::shared_ptr<std::vector<std::vector<uint32_t>>> simplexNoise(uint32_t xsize,
                uint32_t ysize,
                uint32_t levels);

        uint32_t levels_map;

        std::shared_ptr<std::vector<std::vector<tile_type>>> analyse_map(
            std::shared_ptr<std::vector<std::vector<uint32_t> > > &noise);

        tile_type categorize_dots(uint32_t x, uint32_t y,
                                  std::shared_ptr<std::vector<std::vector<uint32_t> > > &noise);
        uint32_t common_height(std::array<uint32_t, 9> &array);


};

#endif // GENERATOR_H
