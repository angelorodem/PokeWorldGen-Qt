#include "generator.h"



Generator::Generator() {
}

Generator::tile_2d_vector Generator::generate_map()
{
    uint32_t size = 400;

    generate_terrain(size,size,5);
    generate_rain(size,size,20);
    generate_temperature(size,size,100);

    return analyse_map(terrain_noise);

}

void Generator::generate_terrain(uint32_t width_p, uint32_t height_p, uint32_t deepness)
{
    srand(time(NULL));

    noise_machine.SetNoiseType(FastNoise::SimplexFractal);
    noise_machine.SetFrequency(0.01);
    noise_machine.SetInterp(FastNoise::Quintic); // Linear, Hermite, Quintic
    noise_machine.SetFractalOctaves(10);      //quant noise layers
    noise_machine.SetFractalLacunarity(2.0); //frequency octave multiplayer
    noise_machine.SetFractalGain(0.5);
    noise_machine.SetFractalType(FastNoise::FBM); //FBM, Billow, RigidMulti


    terrain_noise = simplexNoise(width_p, height_p, deepness);
    // mapa = gen.analyse_map(noise);

    show_terrain(width_p,height_p);


}

void Generator::generate_temperature(uint32_t width_p, uint32_t height_p, uint32_t deepness)
{
    srand(time(NULL));

    noise_machine.SetNoiseType(FastNoise::SimplexFractal);
    noise_machine.SetFrequency(0.002);
    noise_machine.SetInterp(FastNoise::Quintic); // Linear, Hermite, Quintic
    noise_machine.SetFractalOctaves(5);      //quant noise layers
    noise_machine.SetFractalLacunarity(2.0); //frequency octave multiplayer
    noise_machine.SetFractalGain(0.5);
    noise_machine.SetFractalType(FastNoise::FBM); //FBM, Billow, RigidMulti


    temperature_noise = simplexNoise(width_p, height_p, deepness);
    // mapa = gen.analyse_map(noise);

    show_temperature(width_p,height_p);
}

void Generator::generate_rain(uint32_t width_p, uint32_t height_p, uint32_t deepness)
{
    srand(time(NULL));

    noise_machine.SetNoiseType(FastNoise::SimplexFractal);
    noise_machine.SetFrequency(0.002);
    noise_machine.SetInterp(FastNoise::Quintic); // Linear, Hermite, Quintic
    noise_machine.SetFractalOctaves(5);      //quant noise layers
    noise_machine.SetFractalLacunarity(2.0); //frequency octave multiplayer
    noise_machine.SetFractalGain(0.5);
    noise_machine.SetFractalType(FastNoise::FBM); //FBM, Billow, RigidMulti


    rain_noise = simplexNoise(width_p, height_p, deepness);
    // mapa = gen.analyse_map(noise);

    show_rain(width_p,height_p);
}

void Generator::generate_rivers()
{
    //Find a mountain BASE within a high rain area
    //Find a noisy path to the sea respecting height starting by the mountain base
    //Erode reducing the height of the path and change tiles to water
}

void Generator::generate_lakes()
{
    //Find a random 0 height block
    //check its type, and if its not water, flood fill it to water
}

void Generator::show_terrain(uint32_t xsize, uint32_t ysize)
{
     terrain_window = new QLabel();

     QImage map(xsize, ysize, QImage::Format_Grayscale8);

     for (uint32_t x = 0; x < terrain_noise->size(); ++x) {
         for (uint32_t y = 0; y < (*terrain_noise)[x].size(); ++y) {
             uint32_t res = (*terrain_noise)[x][y];
             map.setPixel(x, y, qRgb(res, res, res));
         }
     }

     terrain_window->setPixmap(QPixmap::fromImage(map.scaled(xsize + 405,
                                                             ysize + 405)));
     terrain_window->setWindowTitle("TERRAIN");
     terrain_window->show();
}


void Generator::show_temperature(uint32_t xsize, uint32_t ysize)
{
    temperature_window = new QLabel();

    QImage map(xsize, ysize, QImage::Format_RGB32);

    for (uint32_t x = 0; x < temperature_noise->size(); ++x) {
        for (uint32_t y = 0; y < (*temperature_noise)[x].size(); ++y) {
            uint32_t res = (*temperature_noise)[x][y];
            map.setPixel(x, y, qRgb(200, res, res));
        }
    }

    temperature_window->setPixmap(QPixmap::fromImage(map.scaled(xsize + 405,
                                                            ysize + 405)));
    temperature_window->setWindowTitle("TEMPERATURE");
    temperature_window->show();
}

void Generator::show_rain(uint32_t xsize, uint32_t ysize)
{
    rain_window = new QLabel();

    QImage map(xsize, ysize, QImage::Format_RGB32);

    for (uint32_t x = 0; x < rain_noise->size(); ++x) {
        for (uint32_t y = 0; y < (*rain_noise)[x].size(); ++y) {
            uint32_t res = (*rain_noise)[x][y];
            map.setPixel(x, y, qRgb(res, res, 200));
        }
    }

    rain_window->setPixmap(QPixmap::fromImage(map.scaled(xsize + 405,
                                                            ysize + 405)));
    rain_window->setWindowTitle("RAIN");
    rain_window->show();
}

Generator::ui32_2d_vector Generator::simplexNoise(
        uint32_t xsize,
        uint32_t ysize, uint32_t levels) {

    ui32_2d_vector hold = std::make_shared <
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

    return hold;
}

Generator::tile_2d_vector Generator::analyse_map(ui32_2d_vector &noise) {


    tiles = std::make_shared<std::vector<std::vector<Generator::tile_type>>>
                                                                           (noise->size());

    for (uint32_t x = 0; x < noise->size(); ++x) {
        tiles->at(x).resize(noise->at(x).size());
    }

    //qDebug() << "Categorize tiles";
    for (uint32_t x = 1; x < noise->size() - 1; ++x) {
        for (uint32_t y = 1; y < noise->at(x).size() - 1; ++y) {
            (*tiles)[x][y] = categorize_dots(x, y, noise);
        }
    }


    return tiles;

}

Generator::tile_type Generator::categorize_dots(int32_t x, int32_t y,
                                                ui32_2d_vector &noise) {
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
                //soma += pow(2, (x_g + (y_g * 3)));
                //deveria ser um muro do mesmo sentido
                //qDebug() << "crosh?";
                return solo;
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
        //qDebug() << "solo by 186" << soma << " " << x  << " " << y;
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

    uint32_t new_height = common_height(vals,height);

    //qDebug() << "Not valid, val: " << soma << " CHei " << (*noise)[x][y] << " NHei " << new_height << " x: " << x << " y: " << y;
    (*noise)[x][y] = new_height;

    int32_t max_x = x+2, max_y=y+2;
    int32_t min_x = x-1, min_y= y-1;


    if(x+2 >= (*noise).size() ){
        max_x-=1;
        //qDebug("opsmax");
    }else if(x - 2 <= 1){
        min_x+=1;
        //qDebug("opsmix");
    }

    if(y+2 >= (*noise).at(0).size()){
        max_y-=1;
        //qDebug("opsmay");
    }else if(y-2 <= 1){
        //qDebug("opsmiy");
        min_y+=1;
    }

    tile_type return_value;
    for(int32_t recalc_x = min_x;recalc_x < max_x; ++recalc_x){
        for (int32_t recalc_y = min_y; recalc_y < max_y; ++recalc_y) {
            tile_type temp = categorize_dots(recalc_x, recalc_y, noise);
            if(temp != (*tiles)[recalc_x][recalc_y]){
                //qDebug() << "new value " << temp << " was " << (*tiles)[recalc_x][recalc_y];
                if(recalc_x == x && recalc_y == y){
                    return_value = temp;
                    continue;
                }
                (*tiles)[recalc_x][recalc_y] = temp;
            }

        }
    }

    return return_value;

}

uint32_t Generator::common_height(std::array<uint32_t, 9>& array, uint32_t current_height)
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
        if(current_height != array[i]){
            if (count > topCount) {
                topCount = count;
                topElement = array[i];
            }else if (count == topCount && array[i] < topElement){
                topCount = count;
                topElement = array[i];
            }
        }
    }

    return topElement;
}




