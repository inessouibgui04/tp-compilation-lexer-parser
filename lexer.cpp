#include "lexer.h"

Symbole * Lexer::Consulter() {
   if (!tampon) {

      if (tete>=(int)flux.length())
         tampon = new Symbole(FIN);
      else
      {

         switch (flux[tete]) {
            case '(':
               tampon = new Symbole(OPENPAR);
               tete++;
               break;
            case ')':
               tampon = new Symbole(CLOSEPAR);
               tete++;
               break;
            case '*':
               tampon = new Symbole(MULT);
               tete++;
               break;
            case '+':
               tampon = new Symbole(PLUS);
               tete++;
               break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
               // Ignorer les espaces et caractères de whitespace
               tete++;
               // Rappeler récursivement pour lire le prochain symbole
               return Consulter();
               break;
            default:
               if (flux[tete]<='9' && flux[tete]>='0') {
                  int resultat = flux[tete]-'0';
                  int i=1;
                  // correction de cette ligne pour éviter la segmentation fault  
                  // while (flux[tete+i]<='9' && flux[tete+i]>='0')
                  // vérifier que tete+i < flux.length() pour éviter l'accès hors limites
                  while (tete+i < (int)flux.length() && flux[tete+i]<='9' && flux[tete+i]>='0') {
                     resultat = resultat*10+(flux[tete+i]-'0');
                     i++;
                  }
                  tete = tete+i;
                  tampon = new Entier(resultat);
               }
               else {
                  tete++;  // avancer même pour les caractères invalides
                  tampon = new Symbole(ERREUR);
               }
         }
      }
   }
   return tampon;
}

void Lexer::Avancer() {
   tampon = nullptr;
}

