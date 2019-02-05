#include "tilesetbioma.h"

TilesetBioma::TilesetBioma() {

}

void TilesetBioma::add_tile(Generator::tile_type tipo,
                            std::shared_ptr<std::vector<std::shared_ptr<QPixmap>>> tile_img) {

    tiles.insert(std::make_pair(static_cast<uint32_t>(tipo), tile_img));

}

std::shared_ptr<std::vector<std::shared_ptr<QPixmap>>> TilesetBioma::getTile(
    Generator::tile_type tipo) {
    return tiles[static_cast<uint32_t>(tipo)];
}
