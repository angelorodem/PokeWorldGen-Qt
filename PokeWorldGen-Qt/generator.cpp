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

    std::shared_ptr<std::vector<std::vector<Generator::tile_type>>> tiles;
    tiles = std::make_shared<std::vector<std::vector<Generator::tile_type>>>
            (noise->size());

    for (uint32_t x = 0; x < noise->size(); ++x) {
        tiles->at(x).resize(noise->at(x).size());
    }


    for (uint32_t x = 1; x < noise->size() - 1; ++x) {
        for (uint32_t y = 1; y < noise->at(x).size() - 1; ++y) {
            (*tiles)[x][y] = categorize_dots(x, y, noise);
        }
    }


    return tiles;

}

Generator::tile_type Generator::categorize_dots(uint32_t x, uint32_t y,
        std::shared_ptr<std::vector<std::vector<uint32_t> > > &noise) {
    static const std::array<tile_type, 19> check = {
        muro_vertical_w,
        muro_vertical_e,
        muro_horizontal_n,
        muro_horizontal_s,

        quina_ne_exter,
        quina_se_exter,
        quina_sw_exter,
        quina_nw_exter,

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

        ponto
    };

    static const std::array<tile_type, 5> big_tiles = {
        solo,

        quina_nw_inter,
        quina_ne_inter,
        quina_sw_inter,
        quina_se_inter

    };

    uint32_t height = (*noise)[x][y];

    int32_t soma = 0;

    for (uint32_t y_g = 0; y_g < 3; ++y_g) {
        for (uint32_t x_g = 0; x_g < 3; ++x_g) {
            if ((*noise)[x - 1 + x_g][y - 1 + y_g] == height) {
                int32_t pos = (x_g + y_g * 3); //x na verdade contem  as colulas
                soma += pow(2, pos);
            } else if ((*noise)[x - 1 + x_g][y - 1 + y_g] > height) {
                return solo;
            }
        }
    }

    for (uint32_t con_c = 0; con_c < 5; ++con_c) {
        int32_t res = soma & (int32_t)big_tiles[con_c];
        if (res == big_tiles[con_c]) {
            return big_tiles[con_c];
        }
    }

    if ((soma & 186) == 186) {
        qDebug() << "solo by 186" << soma << " " << x  << " " << y;
        return solo;
    }

    for (uint32_t con_c = 0; con_c < 19; ++con_c) {
        int32_t res = soma & (int32_t)check[con_c];
        if (res == check[con_c]) {
            return check[con_c];
        }
    }

    if (soma > 255) {
        qDebug() << "solo by " << soma;
        return solo;
    }
    qDebug() << "void";
    return the_void;

}















