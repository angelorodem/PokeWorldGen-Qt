#include "generator.h"

Generator::Generator()
{
    srand(time(NULL));
    aaa = new QLabel();

    noise_machine.SetNoiseType(FastNoise::SimplexFractal);
    noise_machine.SetFrequency(0.01);
    noise_machine.SetInterp(FastNoise::Quintic); // Linear, Hermite, Quintic
    noise_machine.SetFractalOctaves(10);      //quant noise layers
    noise_machine.SetFractalLacunarity(2.0); //frequency octave multiplayer
    noise_machine.SetFractalGain(0.5);
    noise_machine.SetFractalType(FastNoise::FBM); //FBM, Billow, RigidMulti


}

QPixmap *Generator::simplexNoise(uint32_t xsize, uint32_t ysize)
{
    for (int var = 0; var < 10; ++var) {
       /* xsize+=3;
        ysize+=3;*/
        QImage map(xsize,ysize,QImage::Format_Grayscale8);

        noise_machine.SetSeed(rand()%9999999);

        for (int x = 0; x < xsize; ++x) {
            for (int y = 0; y < ysize; ++y) {
                float a = noise_machine.GetNoise(x,y);
                uint32_t val = ((a*255)+128<0?0:(a*255)+128>255?255:(a*255)+128);
                uint32_t res = val / 85;
                res *= 85;


                map.setPixel(x,y, qRgb(res,res,res));
            }
        }


        aaa->setPixmap(QPixmap::fromImage(map.scaled(800,800)));
        aaa->show();

        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

    }


    ///QApplication::exit(0);







}
