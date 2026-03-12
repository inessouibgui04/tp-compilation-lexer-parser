#include "state.h"
#include "automate.h"
#include <iostream>

using namespace std;

bool Etat::transition(Automate & automate, Symbole * s) {

    switch(numero) {

        // ETAT 0
        // ===========================================================================================

        case 0:

            switch(*s) {

                case INT:
                    automate.decalage(s,new Etat(3));
                    break;

                case OPENPAR:
                    automate.decalage(s,new Etat(2));
                    break;

                case EXPR:
                    automate.transitionsimple(s,new Etat(1));
                    break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        // ETAT 1
        // ===========================================================================================

        case 1:

            switch(*s) {

                case PLUS:
                    automate.decalage(s,new Etat(4));
                    break;

                case MULT:
                    automate.decalage(s,new Etat(5));
                    break;

                case FIN:
                    {
                        Expr * e = (Expr*) automate.popSymbol();

                         automate.setResultat(e->getValeur());

                         //cout<<"Résultat : "<<automate.getResultat()<<endl;

                        delete e;

                        return false;
                    }

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        // ETAT 2
        // ===========================================================================================

        case 2:

            switch(*s) {

                case INT:
                    automate.decalage(s,new Etat(3));
                    break;

                case OPENPAR:
                    automate.decalage(s,new Etat(2));
                    break;

                case EXPR:
                    automate.transitionsimple(s,new Etat(6));
                    break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        
        // ETAT 3  
        // ===========================================================================================

        case 3:

            switch(*s) {

                case PLUS:
                case MULT:
                case CLOSEPAR:
                case FIN:
                {
                    Entier * e = (Entier*) automate.peekSymbol();

                    Expr * expr = new Expr(e->getValeur());

                    automate.reduction(1, expr);
                }
                break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        
        // ETAT 4
        // ===========================================================================================

        case 4:

            switch(*s) {

                case INT:
                    automate.decalage(s,new Etat(3));
                    break;

                case OPENPAR:
                    automate.decalage(s,new Etat(2));
                    break;

                case EXPR:
                    automate.transitionsimple(s,new Etat(7));
                    break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        
        // ETAT 5
        // ===========================================================================================

        case 5:

            switch(*s) {

                case INT:
                    automate.decalage(s,new Etat(3));
                    break;

                case OPENPAR:
                    automate.decalage(s,new Etat(2));
                    break;

                case EXPR:
                    automate.transitionsimple(s,new Etat(8));
                    break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        
        // ETAT 6
        // ===========================================================================================

        case 6:

            switch(*s) {

                case PLUS:
                    automate.decalage(s,new Etat(4));
                    break;

                case MULT:
                    automate.decalage(s,new Etat(5));
                    break;

                case CLOSEPAR:
                    automate.decalage(s,new Etat(9));
                    break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        
        // ETAT 7  
        // ===========================================================================================

        case 7:

            switch(*s) {

                case MULT:
                    automate.decalage(s,new Etat(5));
                    break;

                case PLUS:
                case CLOSEPAR:
                case FIN:
                {
                    auto& symstack = automate.getSymbolStack();
                    
                    int size = symstack.size();
                    Expr * e2 = (Expr*) symstack[size - 1];
                    Expr * e1 = (Expr*) symstack[size - 3];
                    
                    int res = e1->getValeur() + e2->getValeur();
                    
                    automate.reduction(3, new Expr(res));
                }
                break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        
        // ETAT 8  
        // ===========================================================================================

        case 8:

            switch(*s) {

                case PLUS:
                case MULT:
                case CLOSEPAR:
                case FIN:
                {
                    auto& symstack = automate.getSymbolStack();
                    
                    int size = symstack.size();
                    Expr * e2 = (Expr*) symstack[size - 1];
                    Expr * e1 = (Expr*) symstack[size - 3];
                    
                    int res = e1->getValeur() * e2->getValeur();
                    
                    automate.reduction(3, new Expr(res));
                }
                break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;

        
        // ETAT 9 
        // ===========================================================================================

        case 9:

            switch(*s) {

                case PLUS:
                case MULT:
                case CLOSEPAR:
                case FIN:
                {
                    auto& symstack = automate.getSymbolStack();
                    
                    int size = symstack.size();
                    Expr * e = (Expr*) symstack[size - 2];  
                    
                    int val = e->getValeur();
                    
                    automate.reduction(3, new Expr(val));
                }
                break;

                default:
                    cout<<"Erreur syntaxe"<<endl;
                    automate.setErreurSyntaxe();
                    return false;
            }

        break;
    }

    return true;
}