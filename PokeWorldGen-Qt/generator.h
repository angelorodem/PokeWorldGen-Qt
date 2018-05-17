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

#include "../FastNoise/FastNoise.h"

class Generator
{
    FastNoise noise_machine;
    QLabel* show_map_label;
public:
    /*   N
     * W   E
     *   S
    */

    enum tile_type :uint32_t {
        dot = 495,
        hline_north= 2,
        hline_south= 128,
        vline_west= 8,
        vline_east= 32,
        vconnection= 40,
        hconnection= 130,

        se_edge=416,
        sw_edge=200,
        nw_edge=11,
        ne_edge=38,

        end_north=47,
        end_east=422,
        end_south=488,
        end_west=203

                   };

    inline tile_type getTileType(const uint32_t sum) const;
    inline bool check_if_contains(uint32_t number_src, uint32_t number_chk) const;

    Generator();


    std::vector<std::vector<uint32_t>>* simplexNoise(uint32_t xsize, uint32_t ysize, uint32_t levels);
    std::vector<std::vector<tile_type>>* analyseNoise(std::vector<std::vector<uint32_t>>* noise, uint32_t levels);
private:
    tile_type check_rules(const std::vector<std::vector<uint32_t>>* noise,const uint32_t& x,const uint32_t& y) const;
};

#endif // GENERATOR_H
