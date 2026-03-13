# tp-compilation-lexer-parser

Projet de compilation : implémentation d’un analyseur lexical (lexer) et d’un analyseur syntaxique ascendant LALR(1) capable d’évaluer des expressions arithmétiques.

## Structure du projet

```
tp-compilation-lexer-parser/
├── main.cpp              # Programme principal (parser + évaluation)
├── lexer.h / lexer.cpp   # Analyseur lexical
├── symbole.h / symbole.cpp # Définition des symboles et tokens
├── automate.h / automate.cpp # Automate LALR(1)
├── state.h / state.cpp   # États de l'automate
├── Tests.cpp             # Tests du lexer et du parser
├── Makefile              # Compilation du projet
└── README.md             # Documentation
```

## Grammaire utilisée

Le parser implémente la grammaire suivante :

```
E' → E
E  → E + E
E  → E * E
E  → ( E )
E  → val
```

## Compilation

Compiler le projet :

```bash
make
```

Cette commande génère deux exécutables :

* `parser` : programme principal
* `tests` : programme de tests

## Utilisation

### Lancer le parser

```bash
./parser
```

Permet d’analyser et d’évaluer une expression arithmétique.


### Lancer les tests

```bash
./tests
```

Exécute les tests du lexer et du parser.

## Nettoyage

Supprimer les fichiers générés :

```bash
make clean
```
