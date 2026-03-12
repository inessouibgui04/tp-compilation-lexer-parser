#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"
#include "automate.h"
#include "symbole.h"

using namespace std;

// Fonction utilitaire pour tester le lexer
void testLexer(const string & expr, const vector<int> & expectedTokens) {
    Lexer l(expr);
    Symbole * s = nullptr;
    vector<int> tokens;

    while (true) {
        s = l.Consulter();
        if (!s) { // pointeur nul
            cout << "[Lexer FAIL] pointeur nul pour " << expr << endl;
            break;
        }

        tokens.push_back(*s);

        if (*s == FIN) break; // fin de flux

        l.Avancer(); // toujours avancer, même si ERREUR
    }

    if (tokens == expectedTokens) {
        cout << "[Lexer OK] " << expr << endl;
    } else {
        cout << "[Lexer FAIL] " << expr << " → tokens : ";
        for (auto t : tokens) cout << t << " ";
        cout << endl;
    }
}

// Fonction utilitaire pour tester l'automate (évaluation)
void testAutomate(const string & expr, int expectedResult, bool expectError = false) {
    try {
        Automate a(expr);
        int res = a.getResultat();

        if (!expectError && res == expectedResult) {
            cout << "[Automate OK] " << expr << " = " << res << endl;
        } else if (expectError) {
            cout << "[Automate FAIL] " << expr << " → erreur attendue mais a réussi" << endl;
        } else {
            cout << "[Automate FAIL] " << expr << " → résultat attendu : "
                 << expectedResult << ", obtenu : " << res << endl;
        }
    } catch (...) {
        if (expectError) {
            cout << "[Automate OK] " << expr << " → erreur détectée" << endl;
        } else {
            cout << "[Automate FAIL] " << expr << " → exception inattendue" << endl;
        }
    }
}

int main() {
    cout << "*** Tests Lexer ***" << endl;
    testLexer("1 + 2", {INT, PLUS, INT, FIN});
    testLexer("(123*4)+5", {OPENPAR, INT, MULT, INT, CLOSEPAR, PLUS, INT, FIN});
    testLexer("42", {INT, FIN});
    testLexer("1+abc", {INT, PLUS, ERREUR, ERREUR, ERREUR, FIN}); // test ERREUR pour les caractères invalides

    cout << "\n *** Tests Automate / Evaluation  ***" << endl;
    testAutomate("1+2", 3);
    testAutomate("2*3+4", 10);
    testAutomate("2*(3+4)", 14);
    testAutomate("(1+34)*123", 4305);

    cout << "\n *** Tests d'erreurs syntaxiques  ***" << endl;
    testAutomate("(1+2", 0, true);       
    testAutomate("1+", 0, true);          
    testAutomate("abc", 0, true);        
    testAutomate("1+*2", 0, true);      

    return 0;
}