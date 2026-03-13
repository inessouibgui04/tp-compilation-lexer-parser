#include <iostream>
#include "lexer.h"
#include "symbole.h"
#include "automate.h"

int main(void) {
   
   string chaine;
   cout<<"Expression : ";
   cin>>chaine;
    

   //string chaine("6+(1*5+34)*123");

   Lexer l(chaine);

   Symbole * s;
   while(*(s=l.Consulter())!=FIN) {
      s->Affiche();
      cout<<endl;
      l.Avancer();
   }

   Automate automate(chaine);

    cout << "Resultat = " << automate.getResultat() << endl;

   return 0;
}