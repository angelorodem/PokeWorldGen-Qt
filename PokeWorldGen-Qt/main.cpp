#include <QApplication>
#include "viewport.h"

#include "tilepicker.h"
#include "tilesetbioma.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Viewport vp;
    vp.show();

    return app.exec();
}
