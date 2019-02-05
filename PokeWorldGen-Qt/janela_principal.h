#ifndef JANELA_PRINCIPAL_H
#define JANELA_PRINCIPAL_H

#include <QWidget>
#include "generator.h"
#include "viewport.h"
#include "tilepicker.h"
#include "tilesetbioma.h"
#include <memory>

namespace Ui {
class Janela_principal;
}

class Janela_principal : public QWidget {
        Q_OBJECT

    public:
        explicit Janela_principal(QWidget *parent = 0);
        ~Janela_principal();

    private:
        Ui::Janela_principal *ui;
};

#endif // JANELA_PRINCIPAL_H
