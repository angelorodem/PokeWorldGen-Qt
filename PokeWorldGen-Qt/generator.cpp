#include "generator.h"



Generator::Generator()
{
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

std::vector<std::vector<uint32_t> > *Generator::simplexNoise(uint32_t xsize, uint32_t ysize,uint32_t levels)
{
    std::vector<std::vector<uint32_t>>* hold = new std::vector<std::vector<uint32_t>>();

    noise_machine.SetSeed(rand()%INT32_MAX);

    for (uint32_t x = 0; x < xsize; ++x) {
        hold->push_back(std::vector<uint32_t>());
        for (uint32_t y = 0; y < ysize; ++y) {
            float a = noise_machine.GetNoise(x,y);
            uint32_t val = ((a*255)+128<0?0:(a*255)+128>255?255:(a*255)+128);
            uint32_t res = val / (255/levels);
            res *= (255/levels);

            hold[0][x].push_back(res);

        }
    }


#ifdef QT_DEBUG
    QImage map(xsize,ysize,QImage::Format_Grayscale8);

    for (uint32_t x = 0; x < hold->size(); ++x) {
        for (uint32_t y = 0; y < hold[0][x].size(); ++y) {
            uint32_t res = hold[0][x][y];
            map.setPixel(x,y, qRgb(res,res,res));
        }
    }

    show_map_label->setPixmap(QPixmap::fromImage(map.scaled(xsize+200,ysize+200)));
    show_map_label->show();

    /*QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }/*/
#endif

    return hold;
}


std::vector<std::vector<Generator::tile_type> > *Generator::analyseNoise(std::vector<std::vector<uint32_t>>* noise){
    std::vector<std::vector<tile_type>>* hold = new std::vector<std::vector<tile_type>>();

    for (uint32_t x = 0; x < noise->size(); ++x) {
        hold->push_back(std::vector<tile_type>());
        for (uint32_t y = 0; y < noise[0][x].size(); ++y) {
            hold->back().push_back(nothing);
        }
    }

    for (uint32_t x = 2; x < hold->size()-2; ++x) {
        for (uint32_t y = 2; y < hold[0][x].size()-2; ++y) {
            hold[0][x].push_back(check_rules(noise,x,y));
        }
    }


    delete noise;
    return hold;
}


Generator::tile_type Generator::getTileType(const uint32_t sum) const
{
    if(check_if_contains(sum,495)){
        return dot;
    }else if(check_if_contains(sum,488)){
        return end_south;
    }else if(check_if_contains(sum,422)){
        return end_east;
    }else if(check_if_contains(sum,203)){
        return end_west;
    }else if(check_if_contains(sum,47)){
        return end_north;
    }else if(check_if_contains(sum,416)){
        return se_edge;
    }else if(check_if_contains(sum,200)){
        return sw_edge;
    }else if(check_if_contains(sum,130)){
        return hconnection;
    }else if(check_if_contains(sum,40)){
        return vconnection;
    }else if(check_if_contains(sum,38)){
        return ne_edge;
    }else if(check_if_contains(sum,11)){
        return nw_edge;
    }else if(check_if_contains(sum,128)){
        return hline_south;
    }else if(check_if_contains(sum,32)){
        return vline_east;
    }else if(check_if_contains(sum,8)){
        return vline_west;
    }else if(check_if_contains(sum,2)){
        return hline_north;
    }
    return nothing;

}

bool Generator::check_if_contains(uint32_t number_src, uint32_t number_chk) const
{
    return (number_src|number_chk)==number_src?true:false;
}




Generator::tile_type Generator::check_rules(const std::vector<std::vector<uint32_t> > *noise, const uint32_t &x_, const uint32_t &y_) const
{

    static std::array<uint32_t,9> dirs;

    dirs.fill(0);

    for (uint32_t x = 0; x < 3; ++x) {
        for (uint32_t y = 0; y < 3; ++y) {


            if(noise[0][x+x_][y+y_] > noise[0][x_+(3-x)][y_+(3-y)]){
                dirs[x+y*3] = pow(2,);
            }else if(noise[0][x+x_][y+y_] < noise[0][x_+(3-x)][y_+(3-y)]){
                dirs[(x+y*3)-9] = pow(2,);
            }
        }
    }


    uint32_t sum = 0;
    for (int sum_c = 0; sum_c < 9; ++sum_c) {
        sum += dirs[sum_c];
    }

    return getTileType(sum);

}










