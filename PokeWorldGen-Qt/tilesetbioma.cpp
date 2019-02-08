#include "tilesetbioma.h"

TilesetBioma::TilesetBioma() {

}

void TilesetBioma::add_tile(Generator::tile_type tipo,
                            TilesetBioma::texture_vector tile_img) {

    tiles.insert(std::make_pair(static_cast<uint32_t>(tipo), tile_img));

}

TilesetBioma::texture_vector TilesetBioma::getTile(Generator::tile_type tipo) {
    return tiles[static_cast<uint32_t>(tipo)];
}
