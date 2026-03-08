#pragma once

#include "symbole.h"

class Automate;

class Etat {

public:
    Etat(int num) : numero(num) {}
    virtual ~Etat() {}

    bool transition(Automate & automate, Symbole * s);

    int getNumero() { return numero; }

private:
    int numero;
};
