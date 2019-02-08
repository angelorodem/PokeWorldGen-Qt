#ifndef TILESETBIOMA_H
#define TILESETBIOMA_H

#include <generator.h>
#include <QPixmap>
#include <unordered_map>
#include <memory>

class TilesetBioma {
    public:
        TilesetBioma();

        typedef std::shared_ptr<QPixmap> texture;
        typedef std::shared_ptr<std::vector<texture>> texture_vector;

        void add_tile(Generator::tile_type tipo, texture_vector tile_img);

        texture_vector getTile(Generator::tile_type tipo);
        std::unordered_map<uint32_t, texture_vector> tiles;


};

#endif // TILESETBIOMA_H
