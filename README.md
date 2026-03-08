# tp-compilation-lexer-parser

Projet de compilation : un analyseur lexical et syntaxique LALR(1) avec évaluation d'expressions arithmétiques (en c++).

## Structure du projet
tp-compilation-lexer-parser/
├── main.cpp # Point d'entrée principal
├── lexer.h / lexer.cpp # Analyseur lexical
├── symbole.h / symbole.cpp # Définition des symboles et tokens
├── automate.h / automate.cpp # Automate LALR(1)
├── state.h / state.cpp # États de l'automate
├── Tests.cpp # Tests unitaires et cas d'erreur
├── Makefile # Compilation
└── README.md # Documentation


---

## Compilation

Pour compiler le parser principal :

```bash
make parser
./parser
```

Pour compiler et exécuter les tests unitaires :

```bash
make tests
./tests
```

Pour nettoyer les fichiers générés :
```bash
make clean
```