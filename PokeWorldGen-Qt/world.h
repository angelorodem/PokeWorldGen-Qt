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
        Generator::tile_type type;
        Generator::biome_type biome;
        uint32_t height; //not used yet
        bool blocks;
    };

    typedef std::shared_ptr<std::vector<std::vector<tileset>>> Map;

    Map world_map;

};

#endif // WORLD_H
