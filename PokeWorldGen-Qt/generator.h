#ifndef GENERATOR_H
#define GENERATOR_H

#include <QImage>
#include <QDebug>
#include <QLabel>
#include <QRgb>
#include <QApplication>
#include <QTime>
#include <QVarLengthArray>

#include <random>
#include <ctime>
#include <cmath>
#include <array>
#include <memory>

#include "../FastNoise/FastNoise.h"

class Generator {
        FastNoise noise_machine;

        QLabel *terrain_window;
        QLabel *temperature_window;
        QLabel *rain_window;
    public:

        enum biome_type : uint32_t {
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

            muro_vertical_w = 178,
            muro_vertical_e = 154,
            muro_horizontal_n = 184,
            muro_horizontal_s = 58,

            solo = 511,
            the_void = 0,
            water = 999
        };

        Generator();

        typedef std::shared_ptr<std::vector<std::vector<uint32_t>>> ui32_2d_vector;
        typedef std::shared_ptr<std::vector<std::vector<Generator::tile_type>>> tile_2d_vector;

        ui32_2d_vector terrain_noise;
        ui32_2d_vector temperature_noise;
        ui32_2d_vector rain_noise;

        tile_2d_vector generate_map(uint32_t size);

        void show_terrain(uint32_t xsize, uint32_t ysize);
        void show_temperature(uint32_t xsize, uint32_t ysize);
        void show_rain(uint32_t xsize, uint32_t ysize);

        void generate_terrain(uint32_t width_p, uint32_t height_p, uint32_t deepness);
        void generate_temperature(uint32_t width_p, uint32_t height_p, uint32_t deepness);
        void generate_rain(uint32_t width_p, uint32_t height_p, uint32_t deepness);
        void generate_biomes();

        void generate_rivers();
        void generate_lakes();
        void generate_trees();
        void generate_cities();
        void generate_villages();
        void generate_paths();


        tile_2d_vector tiles;

        ui32_2d_vector simplexNoise(uint32_t xsize,
                uint32_t ysize,
                uint32_t levels);

        tile_2d_vector analyse_map(
            ui32_2d_vector &noise);

        tile_type categorize_dots(int32_t x, int32_t y,
                                  ui32_2d_vector &noise);
        uint32_t common_height(std::array<uint32_t, 9> &array, uint32_t current_height);


};

#endif // GENERATOR_H
