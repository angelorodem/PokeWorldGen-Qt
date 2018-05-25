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
    std::vector<std::vector<uint32_t>> *hold = new
    std::vector<std::vector<uint32_t>>();

    noise_machine.SetSeed(rand() % INT32_MAX);

    for (uint32_t x = 0; x < xsize; ++x) {
        hold->push_back(std::vector<uint32_t>());
        for (uint32_t y = 0; y < ysize; ++y) {
            float a = noise_machine.GetNoise(x, y);
            uint32_t val = ((a * 255) + 128 < 0 ? 0 : (a * 255) + 128 > 255 ? 255 :
                            (a * 255) + 128);
            uint32_t res = val / (255 / levels);
            res *= (255 / levels);

            hold[0][x].push_back(res);

        }
    }


#ifdef QT_DEBUG
    QImage map(xsize, ysize, QImage::Format_Grayscale8);

    for (uint32_t x = 0; x < hold->size(); ++x) {
        for (uint32_t y = 0; y < hold[0][x].size(); ++y) {
            uint32_t res = hold[0][x][y];
            map.setPixel(x, y, qRgb(res, res, res));
        }
    }

    show_map_label->setPixmap(QPixmap::fromImage(map.scaled(xsize + 200,
                              ysize + 200)));
    show_map_label->show();

    /*QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }/*/
#endif

    return hold;
}

std::shared_ptr<std::vector<std::vector<Generator::tile_type> > >
Generator::analyse_map(std::shared_ptr<std::vector<std::vector<uint32_t>>>
                       noise) {

    std::shared_ptr<std::vector<std::vector<Generator::tile_type>>> tiles;
    tiles = std::make_shared<std::vector<std::vector<Generator::tile_type>>>
            (noise->size());

    for (uint32_t x = 0; x < noise->size(); ++x) {
        tiles->at(x).resize(noise->at(x).size());
    }


    for (uint32_t x = 0; x < noise->size(); ++x) {
        for (uint32_t y = 0; y < noise->at(x).size(); ++y) {
            tiles[0][x].push_back(categorize_dots(x, y, noise));
        }
    }




}

Generator::tile_type Generator::categorize_dots(uint32_t x, uint32_t y,
        std::shared_ptr<std::vector<std::vector<uint32_t> > > noise) {
    static std::array<tile_type, 14> check = {
        quina_ne_inter,
        quina_nw_inter,

        quina_ne_exter,
        quina_se_exter,
        quina_sw_exter,
        quina_nw_exter,

        muro_horizontal_w,
        muro_horizontal_e,
        muro_vertical_n,
        muro_vertical_s,

        linha_vertical,
        linha_horizontal,
        ponto,
        solo


    };




}















