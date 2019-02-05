#ifndef WORLD_H
#define WORLD_H

#include "tilesetbioma.h"
#include "generator.h"


class World {
    public:
        World(uint32_t width_, uint32_t height_);

        uint32_t width;
        uint32_t height;

        struct tileset {
            tileset() {}
            Generator::tile_type tipo_tile;
            Generator::biomas_type tipo_bioma;
            uint32_t variante = 0;
        };

        std::shared_ptr<std::vector<std::vector<tileset>>> mapa;


};

#endif // WORLD_H
