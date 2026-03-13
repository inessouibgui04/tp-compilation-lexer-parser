#pragma once

#include <vector>
#include "state.h"
#include "lexer.h"

class Automate {

public:
    Automate(string chaine);
    ~Automate();

    //meme methode vues dans le polycopié du cours
    void decalage(Symbole * s, Etat * e);
    void transitionsimple(Symbole * s, Etat * e);
    void reduction(int n, Symbole * s);

    Symbole * popSymbol();
    void popAndDestroySymbol();
    Symbole * peekSymbol() const { if (symbolstack.empty()) return nullptr; return symbolstack.back(); }

    Lexer * getLexer() { return lexer; }

    int getResultat() const { return resultat; }

    void setResultat(int r) { resultat = r; }
    
    bool hasErreurSyntaxe() const { return erreurSyntaxe; }
    
    void setErreurSyntaxe() { erreurSyntaxe = true; }

private:
    vector<Symbole*> symbolstack;
    vector<Etat*> statestack;

    Lexer * lexer;

    //pour afficher le résultat à la fin de l'analyse syntaxique (question 2)
    int resultat;
    
    bool erreurSyntaxe;  //pour indiquer une erreur syntaxique

public:
    // pour permettre aux états de manipuler les piles directement
    vector<Symbole*>& getSymbolStack() { return symbolstack; }
    vector<Etat*>& getStateStack() { return statestack; }
};
