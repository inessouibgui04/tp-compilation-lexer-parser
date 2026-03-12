#include "automate.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Automate::Automate(string chaine) {

    lexer = new Lexer(chaine);
    erreurSyntaxe = false;

    // mon état initial
    statestack.push_back(new Etat(0));

    bool continuer = true;

    while (continuer) {
        Symbole * s = lexer->Consulter();
        continuer = statestack.back()->transition(*this, s);
    }
    

    if (erreurSyntaxe) {
        while(!symbolstack.empty()) {
            delete symbolstack.back();
            symbolstack.pop_back();
        }
        while(!statestack.empty()) {
            delete statestack.back();
            statestack.pop_back();
        }
        if (lexer) {
            delete lexer;
            lexer = nullptr;
        }
        throw runtime_error("Erreur syntaxique");
    }
}

Automate::~Automate() {

    while(!symbolstack.empty()) {
        delete symbolstack.back();
        symbolstack.pop_back();
    }

    while(!statestack.empty()) {
        delete statestack.back();
        statestack.pop_back();
    }

    if (lexer) {
        delete lexer;
    }
}

void Automate::decalage(Symbole * s, Etat * e) {

    symbolstack.push_back(s);
    statestack.push_back(e);

    lexer->Avancer();
}

void Automate::transitionsimple(Symbole * s, Etat * e) {

    symbolstack.push_back(s);
    statestack.push_back(e);
}

    void Automate::reduction(int n, Symbole * s) {
        // Supprime n états et n symboles
        for(int i = 0 ; i < n ; i++ ) {
            if (!statestack.empty()) { delete statestack.back(); statestack.pop_back(); }
            if (!symbolstack.empty()) { delete symbolstack.back(); symbolstack.pop_back(); }
        }

        // Si la pile d'états est vide, on est en haut niveau --> pas de transition
        if (statestack.empty()) {
            statestack.push_back(new Etat(0));
        }

        statestack.back()->transition(*this, s);
    }

Symbole * Automate::popSymbol() {

    Symbole * s = symbolstack.back();
    symbolstack.pop_back();

    return s;
}

void Automate::popAndDestroySymbol() {

    delete symbolstack.back();
    symbolstack.pop_back();
}