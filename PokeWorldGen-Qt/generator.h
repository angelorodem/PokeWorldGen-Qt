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
                    vline_east = 32,
                    vline_west = 8,
                    hline_north = 2,
                    hline_south = 128,
                    edge_nw = 11,
                    edge_ne = 38,
                    edge_sw = 416,
                    edge_se = 200
                   };



    Generator();

    std::vector<std::vector<uint32_t>>* simplexNoise(uint32_t xsize, uint32_t ysize, uint32_t levels);
    std::vector<std::vector<uint32_t>>* analyseNoise(std::vector<std::vector<uint32_t>>* noise, uint32_t levels);
private:
    tile_type check_rules(const std::vector<std::vector<uint32_t>>* noise,const uint32_t& x,const uint32_t& y) const;
};

#endif // GENERATOR_H
