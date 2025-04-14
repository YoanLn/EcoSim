# Écosystème Virtuel

Un simulateur d'écosystème en C qui modélise les interactions entre proies et prédateurs dans un environnement virtuel.

## Description

Ce projet implémente un écosystème virtuel où des animaux (proies et prédateurs) interagissent dans un environnement 2D. Le système simule des comportements tels que :
- Le déplacement aléatoire des animaux
- La reproduction
- La prédation
- La gestion de l'énergie
- L'évolution de la population

## Structure du Projet

- `ecosys.h` : Définition des structures et prototypes des fonctions
- `ecosys.c` : Implémentation des fonctions de l'écosystème
- `main_ecosys.c` : Programme principal
- `main_tests.c` : Tests unitaires
- `Makefile` : Script de compilation

## Fonctionnalités

- Création et gestion d'animaux (proies et prédateurs)
- Simulation de déplacements aléatoires
- Système de reproduction
- Interaction prédateur-proie
- Affichage graphique de l'écosystème
- Sauvegarde et chargement de l'état de l'écosystème

## Compilation

Pour compiler le projet, utilisez la commande :
```bash
make
```

## Utilisation

Pour exécuter la simulation principale :
```bash
./ecosys
```

Pour exécuter les tests :
```bash
./tests_ecosys
```

## Représentation Visuelle

- `*` : Représente une proie
- `O` : Représente un prédateur
- `@` : Représente un prédateur et une proie au même endroit

## Configuration

Les paramètres de l'écosystème peuvent être modifiés dans le fichier `ecosys.h` :
- `SIZE_X` : Largeur de l'écosystème
- `SIZE_Y` : Hauteur de l'écosystème

## Tests

Le projet inclut un ensemble de tests pour vérifier le bon fonctionnement des différentes fonctionnalités. Les tests couvrent :
- La création et la gestion des animaux
- Les mouvements
- Les interactions entre espèces
- La reproduction
- La gestion de l'énergie

## Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails. 