#ifndef TILESETBIOMA_H
#define TILESETBIOMA_H

#include <generator.h>
#include <QPixmap>
#include <unordered_map>
#include <memory>

class TilesetBioma {
    public:
        TilesetBioma();
        void add_tile(Generator::tile_type tipo,
                      std::shared_ptr<std::vector<std::shared_ptr<QPixmap> > > tile_img);
        std::shared_ptr<std::vector<std::shared_ptr<QPixmap>>> getTile(
            Generator::tile_type tipo);
        //talvez é mais rapido só fazer um array grande ao invez de hashlist
        std::unordered_map<uint32_t, std::shared_ptr<std::vector<std::shared_ptr<QPixmap>>>>
        tiles;


};

#endif // TILESETBIOMA_H
