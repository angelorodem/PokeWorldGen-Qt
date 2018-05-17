#include <QApplication>
#include "generator.h"
#include "viewport.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    Viewport vp;
    vp.show();

    return app.exec();
}
