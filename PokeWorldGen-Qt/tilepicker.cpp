#include "tilepicker.h"
#include "ui_tilepicker.h"

TilePicker::TilePicker(std::shared_ptr<TilesetBioma> bioma) :
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
    temp_vector = std::make_shared<QVarLengthArray<std::shared_ptr<QRectF>>>();


    QFile file("save.bin");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream out(&file);

        uint32_t size_tipos = 0;
        uint32_t size_textures = 0;
        QRectF temp_rect;

        out >> imagem;
        bioma_ref->tileset_pixmap = std::make_shared<QPixmap>();
        *bioma_ref->tileset_pixmap = QPixmap::fromImage(imagem);

        out >> size_tipos;
        for (uint32_t vt = 0;vt < size_tipos;++vt) {
            out >> size_textures;
            vetor_tipos.push_back(std::make_shared<QVarLengthArray<std::shared_ptr<QRectF>>>());
            for (uint32_t tx = 0;tx < size_textures;++tx) {
                out >> temp_rect;
                vetor_tipos[vt]->push_back(std::make_shared<QRectF>(temp_rect));
            }
        }
        loaded = true;
        on_ok_but_clicked();

    }else{
        QMessageBox::information(this, tr("Unable to open file"),
                                 "Your tileset will be stored in the save.bin");
    }



}

TilePicker::~TilePicker() {
    delete ui;
}



void TilePicker::on_ok_but_clicked() {
    for (int i = 0; i < vetor_tipos.size(); ++i) {
        bioma_ref->add_tile(tile_seq[i], vetor_tipos[i]);
    }

    if(loaded){
        this->close();
        return;
    }
    QFile file("save.bin");
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return;
    }

    QDataStream out(&file);
    out << imagem;

    out << vetor_tipos.size();
    for (int vt = 0;vt < vetor_tipos.size();++vt) {
        out << vetor_tipos[vt]->size();
        for (int tx = 0;tx < vetor_tipos[vt]->size();++tx) {
            out << *vetor_tipos[vt]->at(tx);
        }
    }

    this->close();

}

void TilePicker::on_load_but_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load Image"), QDir::currentPath(),
                                                    tr("Images (*.png *.jpg *.bmp *.jpeg)"));

    imagem.load(fileName);
    bioma_ref->tileset_pixmap = std::make_shared<QPixmap>();
    *bioma_ref->tileset_pixmap = QPixmap::fromImage(imagem);
    update_tile_pos();
    ui->load_but->setEnabled(false);

    populate_tile_picker();
}

void TilePicker::on_proximo_but_clicked() {


    if (imagem.isNull()) {
        return;
    }

    if (temp_vector->empty()) {
        return;
    }

    if (current_tile >= tiles_size) {
        return;
    }
    current_tile++;


    if(current_tile < tiles_size){
        ui->label_tile->setText(tiles_string[current_tile]);
    }
    vetor_tipos.push_back(temp_vector);
    temp_vector = std::make_shared<QVarLengthArray<std::shared_ptr<QRectF>>>();


}

void TilePicker::on_add_but_clicked() {


    update_tile_pos();
    if (imagem.isNull()) {
        return;
    }

    /*std::shared_ptr<QPixmap> temp;
    temp = std::make_shared<QPixmap>();
    (*temp) = QPixmap::fromImage(imagem.copy(x * tile_width + x_o,
                                             y * tile_height + y_o,
                                             tile_width,
                                             tile_height));*/
    std::shared_ptr<QRectF> temp_rect;
    temp_rect = std::make_shared<QRectF>();
    *temp_rect = QRectF(x * tile_width + x_o,
                        y * tile_height + y_o,
                        tile_width,
                        tile_height);

    temp_vector->push_back(temp_rect);

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
    temp = temp.scaled(ui->img_tile->width()-4, ui->img_tile->height()-4);
    ui->img_tile->setPixmap(temp);
    ui->img_tile->update();

}




void TilePicker::on_pushButton_clicked()
{
    on_load_but_clicked();
    for (int i = 0;i < 30; ++i) {
        on_add_but_clicked();
        on_proximo_but_clicked();
    }
    on_ok_but_clicked();
}

void TilePicker::populate_tile_picker()
{
    if (imagem.isNull()) {
        return;
    }

    int x_populate = 0;
    int y_populate = 0;
    tile_width = tile_height = ui->size_spin->value();
    x_o = ui->offset_coluna->value();
    y_o = ui->offset_linha->value();

    QImage temp_tile = imagem.copy(x * tile_width + x_o, y * tile_height + y_o,
                                   tile_width,
                                   tile_height);

    QPixmap temp = QPixmap::fromImage(temp_tile);
    temp = temp.scaled(ui->img_tile->width()-4, ui->img_tile->height()-4);
    ui->img_tile->setPixmap(temp);
    ui->img_tile->update();
}
