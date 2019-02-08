#include "world.h"

World::World(uint32_t width_, uint32_t height_) {
    width = width_;
    height = height_;

    world_map = std::make_shared<std::vector<std::vector<tileset>>>();


}
