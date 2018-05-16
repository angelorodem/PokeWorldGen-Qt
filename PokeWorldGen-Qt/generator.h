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
    QLabel* aaa;
public:
    Generator();

    QPixmap* simplexNoise(uint32_t xsize, uint32_t ysize);
};

#endif // GENERATOR_H
