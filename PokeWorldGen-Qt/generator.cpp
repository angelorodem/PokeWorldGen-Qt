#include "generator.h"



Generator::Generator() {
    srand(time(NULL));

    show_map_label = new QLabel();

    noise_machine.SetNoiseType(FastNoise::SimplexFractal);
    noise_machine.SetFrequency(0.01);
    noise_machine.SetInterp(FastNoise::Quintic); // Linear, Hermite, Quintic
    noise_machine.SetFractalOctaves(10);      //quant noise layers
    noise_machine.SetFractalLacunarity(2.0); //frequency octave multiplayer
    noise_machine.SetFractalGain(0.5);
    noise_machine.SetFractalType(FastNoise::FBM); //FBM, Billow, RigidMulti


}

std::shared_ptr<std::vector<std::vector<uint32_t> > > Generator::simplexNoise(
    uint32_t xsize,
    uint32_t ysize, uint32_t levels) {

    levels_map = levels;

    std::shared_ptr<std::vector<std::vector<uint32_t>>> hold = std::make_shared <
            std::vector<std::vector<uint32_t> >> ();

    noise_machine.SetSeed(rand() % INT32_MAX);

    for (uint32_t x = 0; x < xsize; ++x) {
        hold->push_back(std::vector<uint32_t>());
        for (uint32_t y = 0; y < ysize; ++y) {
            float a = noise_machine.GetNoise(x, y);
            uint32_t val = ((a * 255) + 128 < 0 ? 0 : (a * 255) + 128 > 255 ? 255 :
                            (a * 255) + 128);
            uint32_t res = val / (255 / levels);
            res *= (255 / levels);

            (*hold)[x].push_back(res);

        }
    }


#ifdef QT_DEBUG
    QImage map(xsize, ysize, QImage::Format_Grayscale8);

    for (uint32_t x = 0; x < hold->size(); ++x) {
        for (uint32_t y = 0; y < (*hold)[x].size(); ++y) {
            uint32_t res = (*hold)[x][y];
            map.setPixel(x, y, qRgb(res, res, res));
        }
    }

    show_map_label->setPixmap(QPixmap::fromImage(map.scaled(xsize + 405,
                              ysize + 405)));
    show_map_label->show();

    /*QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }/*/
#endif

    return hold;
}

std::shared_ptr<std::vector<std::vector<Generator::tile_type> > >
Generator::analyse_map(std::shared_ptr<std::vector<std::vector<uint32_t> > >
                       &noise) {


    tiles = std::make_shared<std::vector<std::vector<Generator::tile_type>>>
            (noise->size());

    for (uint32_t x = 0; x < noise->size(); ++x) {
        tiles->at(x).resize(noise->at(x).size());
    }

    qDebug() << "Categorize tiles";
    for (uint32_t x = 1; x < noise->size() - 1; ++x) {
        for (uint32_t y = 1; y < noise->at(x).size() - 1; ++y) {
            (*tiles)[x][y] = categorize_dots(x, y, noise);
        }
    }


    return tiles;

}

Generator::tile_type Generator::categorize_dots(uint32_t x, uint32_t y,
        std::shared_ptr<std::vector<std::vector<uint32_t> > > &noise) {
    static const std::array<tile_type, 8> check = {
        muro_vertical_w,
        muro_vertical_e,
        muro_horizontal_n,
        muro_horizontal_s,

        quina_ne_exter,
        quina_se_exter,
        quina_sw_exter,
        quina_nw_exter,
/*
        linha_vertical,
        linha_horizontal,

        linha_quina_ne,
        linha_quina_se,
        linha_quina_sw,
        linha_quina_nw,

        linha_vertical_end_s,
        linha_vertical_end_n,

        linha_horizontal_end_e,
        linha_horizontal_end_w,

        ponto*/
    };

    static const std::array<tile_type, 5> big_tiles = {
        solo,

        quina_nw_inter,
        quina_ne_inter,
        quina_sw_inter,
        quina_se_inter

    };

    uint32_t height = (*noise)[x][y];
    std::array<uint32_t, 9> vals;

    uint32_t soma = 0;

    for (uint32_t y_g = 0; y_g < 3; ++y_g) {
        for (uint32_t x_g = 0; x_g < 3; ++x_g) {
            vals[(y_g*3)+x_g] = (*noise)[x - 1 + x_g][y - 1 + y_g];
            if ((*noise)[x - 1 + x_g][y - 1 + y_g] == height) {
                soma += pow(2, (x_g + (y_g * 3)));
            } else if ((*noise)[x - 1 + x_g][y - 1 + y_g] > height) {
                //TODO: seems wrong
                soma += pow(2, (x_g + (y_g * 3)));
                //deveria ser um muro do mesmo sentido
                qDebug() << "crosh?";
                //return solo;
            }
        }
    }

    //verifies if a tile structure is inside the current tile
    //using logical AND operation
    for (uint32_t con_c = 0; con_c < 5; ++con_c) {
        uint32_t res = soma & static_cast<uint32_t>(big_tiles[con_c]);
        if (res == static_cast<uint32_t>(big_tiles[con_c])) {
            return big_tiles[con_c];
        }
    }

    if ((soma & 186) == 186) {
        qDebug() << "solo by 186" << soma << " " << x  << " " << y;
        return solo;
    }

    //verifies if a tile structure is inside the current tile
    //using logical AND operation
    for (uint32_t con_c = 0; con_c < 8; ++con_c) {
        uint32_t res = soma & static_cast<uint32_t>(check[con_c]);
        if (res == static_cast<uint32_t>(check[con_c])) {
            return check[con_c];
        }
    }


    (*noise)[x][y] = common_height(vals);
    qDebug() << "invalid? " << (*noise)[x][y];

    uint32_t max_x = x+2, max_y=y+2;

    if(x+2 >= (*noise).size()){
        max_x--;
    }
    if(y+2 >= (*noise).at(0).size()){
        max_y--;
    }

    for(uint32_t recalc_x = x - 1;recalc_x < max_x; ++recalc_x){
        for (uint32_t recalc_y = y - 1; recalc_y < max_y; ++recalc_y) {
            tile_type temp = categorize_dots(recalc_x, recalc_y, noise);
            if(temp != (*tiles)[recalc_x][recalc_y]){
                qDebug() << "new value " << temp << " was " << (*tiles)[recalc_x][recalc_y];
                (*tiles)[recalc_x][recalc_y] = temp;
            }

        }
    }


    return solo;

}

uint32_t Generator::common_height(std::array<uint32_t, 9>& array)
{
    uint32_t topCount = 0, count = 0, topElement = 0;

    for (uint32_t i=0; i < array.size(); i++) {
        count = 0;
        if(i == 4){
            continue;
        }
        for (uint32_t j=0 ; j<array.size() ; j++) {
            if(j == 4){
                continue;
            }
            if (array[i] == array[j])
                count++;
        }
        if (count > topCount) {
            topCount = count;
            topElement = array[i];
        }else if (count == topCount && array[i] < topElement){
            topCount = count;
            topElement = array[i];
        }
    }

    return topElement;
}



