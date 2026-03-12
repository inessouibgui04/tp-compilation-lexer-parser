#pragma once

#include <string>
#include <iostream>
using namespace std;

enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR, EXPR };

const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR", "EXPR" };

class Symbole {
   public:
      Symbole(int i) : ident(i) {  }
      virtual ~Symbole() { }
      operator int() const { return ident; }
      virtual void Affiche();

   protected:
      int ident;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT), valeur(v) { }
      ~Entier() { }

      int getValeur() { return valeur; }
      virtual void Affiche();
   protected:
      int valeur;
};

// classe expression : hérite de Symbole avec identifiant de EXPR, Symbole(EXPR)
//un int valeur
//meme fonctionement que le code dans le policopié du cours

class Expr : public Symbole {
   public:
      Expr(int v) : Symbole(EXPR), valeur(v) {}
      virtual ~Expr() {}

      int getValeur() { return valeur; }

      virtual void Affiche() {
         cout << "EXPR(" << valeur << ")";
      }

   protected:
      int valeur;
   };
