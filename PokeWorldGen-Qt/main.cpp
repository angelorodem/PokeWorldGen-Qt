#include <QApplication>
#include "generator.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    Generator gen;
    gen.simplexNoise(300,300);


    return app.exec();
}
