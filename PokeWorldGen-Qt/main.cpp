#include <QApplication>
#include "generator.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    Generator gen;
    gen.simplexNoise(150,150,5);


    return app.exec();
}
