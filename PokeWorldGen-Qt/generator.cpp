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

    for (int x = 0; x < xsize; ++x) {
        hold->push_back(std::vector<uint32_t>());
        for (int y = 0; y < ysize; ++y) {
            float a = noise_machine.GetNoise(x,y);
            uint32_t val = ((a*255)+128<0?0:(a*255)+128>255?255:(a*255)+128);
            uint32_t res = val / (255/levels);
            res *= (255/levels);

            hold[0][x].push_back(res);

        }
    }


#ifdef QT_DEBUG
    QImage map(xsize,ysize,QImage::Format_Grayscale8);

    for (int x = 0; x < hold->size(); ++x) {
        for (int y = 0; y < hold[0][x].size(); ++y) {
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
}


std::vector<std::vector<uint32_t> > *Generator::analyseNoise(std::vector<std::vector<uint32_t>>* noise,
                                                             uint32_t levels){

}


Generator::tile_type Generator::check_rules(const std::vector<std::vector<uint32_t> > *noise, const uint32_t &x, const uint32_t &y) const
{

    uint32_t dirs[9];
    for (int var = 0; var < 9; ++var) {
        dirs[var] = 0;
    }

    static uint32_t xposf,xposb;
    static uint32_t yposf,yposb;
    for (uint32_t pos = 0; pos < 9; ++pos) {
        if(pos == 4){
            continue;
        }
        yposf = floor(pos/3);
        xposf = pos - (ypos*3) + x;
        yposf += y;

        yposb = floor((9-pos)/3);
        xposb = (9-pos) - (ypos*3) + x;
        yposb += y;


        if(noise[0][xposf][yposf] > noise[0][xposb][yposb]){
            dirs[pos] = pow(2,pos);
        }else if(noise[0][xposf][yposf] < noise[0][xposb][yposb]){
            dirs[9-pos] = pow(2,9-pos);
        }
    }

    uint32_t sum = 0;
    for (int sum_c = 0; sum_c < 9; ++sum_c) {
        sum += dirs[sum_c];
    }

    return sum;

}








