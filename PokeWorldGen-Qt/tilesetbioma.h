#ifndef TILESETBIOMA_H
#define TILESETBIOMA_H

#include <generator.h>
#include <QPixmap>
#include <unordered_map>
#include <QVarLengthArray>
#include <memory>

class TilesetBioma {
    public:
        TilesetBioma();

        std::shared_ptr<QPixmap> tileset_pixmap;

        typedef std::shared_ptr<QRectF> texture_rect;
        typedef std::shared_ptr<QVarLengthArray<texture_rect>> tex_rect_vector;

        void add_tile(Generator::tile_type tipo, tex_rect_vector tile_img);

        tex_rect_vector getTile(Generator::tile_type tipo);
        std::unordered_map<uint32_t, tex_rect_vector> tiles;


};

#endif // TILESETBIOMA_H
