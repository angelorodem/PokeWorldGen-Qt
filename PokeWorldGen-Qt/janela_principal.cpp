#include "janela_principal.h"
#include "ui_janela_principal.h"

Janela_principal::Janela_principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela_principal) {
    ui->setupUi(this);



    std::shared_ptr<TilesetBioma> bioma = std::make_shared<TilesetBioma>();
    TilePicker tp(bioma);
    tp.show();

}

Janela_principal::~Janela_principal() {
    delete ui;
}
