#include "tilepicker.h"
#include "ui_tilepicker.h"

TilePicker::TilePicker(std::shared_ptr<TilesetBioma> bioma, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TilePicker) {
    ui->setupUi(this);
    bioma_ref = bioma;
    connect(ui->size_spin, SIGNAL(valueChanged(int)), this,
            SLOT(update_tile_pos()));
    connect(ui->coluna_spin, SIGNAL(valueChanged(int)), this,
            SLOT(update_tile_pos()));
    connect(ui->linha_spin, SIGNAL(valueChanged(int)), this,
            SLOT(update_tile_pos()));
    connect(ui->offset_coluna, SIGNAL(valueChanged(int)), this,
            SLOT(update_tile_pos()));
    connect(ui->offset_linha, SIGNAL(valueChanged(int)), this,
            SLOT(update_tile_pos()));

    ui->label_tile->setText(tiles_string[current_tile]);
    temp_vector = std::make_shared<std::vector<std::shared_ptr<QPixmap>>>();

}

TilePicker::~TilePicker() {
    delete ui;
}



void TilePicker::on_ok_but_clicked() {
    for (int i = 0; i < vetor_tipos.size(); ++i) {
        bioma_ref->add_tile(tile_seq[i], vetor_tipos[i]);
    }
    this->close();
}

void TilePicker::on_load_but_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Carregar Imagem"), QDir::currentPath(),
                       tr("Imagens (*.png *.jpg *.bmp *.jpeg)"));

    imagem.load(fileName);
    update_tile_pos();
}

void TilePicker::on_proximo_but_clicked() {


    if (imagem.isNull()) {
        return;
    }
    if (temp_vector->empty()) {
        return;
    }

    current_tile++;
    if ((current_tile) >= tiles_size) {
        return;
    }


    ui->label_tile->setText(tiles_string[current_tile]);
    vetor_tipos.push_back(temp_vector);
    temp_vector = std::make_shared<std::vector<std::shared_ptr<QPixmap>>>();


}

void TilePicker::on_add_but_clicked() {
    update_tile_pos();
    if (imagem.isNull()) {
        return;
    }

    std::shared_ptr<QPixmap> temp;
    temp = std::make_shared<QPixmap>();
    (*temp) = QPixmap::fromImage(imagem.copy(x * tile_width + x_o,
                                 y * tile_height + y_o,
                                 tile_width,
                                 tile_height));

    temp_vector->push_back(temp);

    if ((current_tile + 1) >= tiles_size && temp_vector->size()) {
        ui->ok_but->setEnabled(true);
    }


}

void TilePicker::update_tile_pos() {
    if (imagem.isNull()) {
        return;
    }

    x = ui->coluna_spin->value();
    y = ui->linha_spin->value();
    tile_width = tile_height = ui->size_spin->value();
    x_o = ui->offset_coluna->value();
    y_o = ui->offset_linha->value();

    QImage temp_tile = imagem.copy(x * tile_width + x_o, y * tile_height + y_o,
                                   tile_width,
                                   tile_height);

    QPixmap temp = QPixmap::fromImage(temp_tile);
    temp = temp.scaled(ui->img_tile->width(), ui->img_tile->height());
    ui->img_tile->setPixmap(temp);
    ui->img_tile->update();

}



