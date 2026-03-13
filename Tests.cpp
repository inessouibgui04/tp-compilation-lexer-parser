#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"
#include "automate.h"
#include "symbole.h"

using namespace std;

// Fonction pour tester le lexer
void testLexer(const string & expr, const vector<int> & expectedTokens) {
    Lexer l(expr);
    vector<int> tokens;
    Symbole * s;

    while ((s = l.Consulter())) {
        tokens.push_back(*s);

        if (*s == FIN) break;

        l.Avancer();
    }

    if (tokens == expectedTokens) {
        cout << "[Lexer OK] " << expr << endl;
    } else {
        cout << "[Lexer FAIL] " << expr << " -> ";
        for (int t : tokens) cout << t << " ";
        cout << endl;
    }
}

// Fonction pour tester l'automate (évaluation)
void testAutomate(const string & expr, int expectedResult, bool expectError = false) {
    try {
        Automate a(expr);
        int res = a.getResultat();

        if (!expectError && res == expectedResult)
            cout << "[OK] " << expr << " = " << res << endl;
        else
            cout << "[FAIL] " << expr << endl;

    } catch (...) {
        cout << (expectError ? "[OK] " : "[FAIL] ") << expr << endl;
    }
}

int main() {
    // **********************Tests du lexer
    cout << "*** Tests Lexer ***" << endl;

    // cas simples
    testLexer("1", {INT, FIN});
    testLexer("123", {INT, FIN});

    // opérateurs
    testLexer("1+2", {INT, PLUS, INT, FIN});
    testLexer("3*4", {INT, MULT, INT, FIN});

    // parenthèses
    testLexer("(1)", {OPENPAR, INT, CLOSEPAR, FIN});
    testLexer("(1+2)", {OPENPAR, INT, PLUS, INT, CLOSEPAR, FIN});

    // espaces
    testLexer("  7 + 8 ", {INT, PLUS, INT, FIN});

    // plusieurs chiffres
    testLexer("12345+678", {INT, PLUS, INT, FIN});

    // caractères invalides
    testLexer("a", {ERREUR, FIN});
    testLexer("1+a", {INT, PLUS, ERREUR, FIN});
    testLexer("1+abc", {INT, PLUS, ERREUR, ERREUR, ERREUR, FIN});

    // mélange
    testLexer("(2*3)+x", {OPENPAR, INT, MULT, INT, CLOSEPAR, PLUS, ERREUR, FIN});


    // **********************Tests de l'automate et de l'évaluation
    cout << "\n *** Tests Automate / Evaluation  ***" << endl;
    testAutomate("1+2", 3);
    testAutomate("2*3+4", 10);
    testAutomate("2*(3+4)", 14);
    testAutomate("(1+34)*123", 4305);

    cout << "\n *** Tests d'erreurs syntaxiques  ***" << endl;
    testAutomate("(1+2", 0, true);     
    testAutomate("1+", 0, true);       
    testAutomate("+1", 0, true);       
    testAutomate("1+*2", 0, true);     
    testAutomate("(1+2))", 0, true);   
    testAutomate("((1+2)", 0, true);    
    
    //***********************Tests du Parser avec toute les regles de calcul
    cout << "\n *** Tests du Parser (Toutes les règles) ***" << endl;

    cout << "\n *** E->val  ***" << endl;
    testAutomate("5", 5);
    testAutomate("123", 123);

    cout << "\n *** E->E+E  ***" << endl;
    testAutomate("1+2", 3);
    testAutomate("10+20", 30);

    cout << "\n *** E->E*E  ***" << endl;
    testAutomate("2*3", 6);
    testAutomate("4*5", 20);

    cout << "\n *** E->(E)  ***" << endl;
    testAutomate("(3)", 3);
    testAutomate("(1+2)", 3);

    cout << "\n *** priorité * > +  ***" << endl;
    testAutomate("2+3*4", 14);
    testAutomate("1+2*3", 7);
    testAutomate("2*3+4", 10);

    cout << "\n *** Tests avec parenthèses  ***" << endl;
    testAutomate("(2+3)*4", 20);
    testAutomate("2*(3+4)", 14);
    testAutomate("(1+2)*(3+4)", 21);

    cout << "\n *** Expressions longues  ***" << endl;
    testAutomate("1+2+3+4", 10);
    testAutomate("2*3*4", 24);
    testAutomate("1+2*3+4", 11);
    testAutomate("(1+2)*(3+4)*2", 42);

    cout << "\n *** Cas limites  ***" << endl;
    testAutomate("0", 0);
    testAutomate("0+0", 0);
    testAutomate("1*0", 0);
    testAutomate("999*0", 0);

    return 0;
}