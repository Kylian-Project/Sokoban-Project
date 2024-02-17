# Sokoban project | Tech Dev 1.0
Sokoban est un projet de Tech Dev L2S3 réaliser en C.  
Ce projet à pour but d'apprendre les bonnes pratiques vue en cours lors de la création d'un projet seul ou en équipe.

### Règles du jeu
Le but du jeux et de placer les caisses (C) sur les cibles (o) uniquement en les poussant avec le joueur (P). Il n'est pas possible de tirer les caisses.

## Installation / Execution

**Prérequis :** Le jeu utilise `ncurses` donc il doit être installer sur votre machine.

Pour lancer Sokoban il faut d'abord le compiler.  
Puis ce rendre dans le dossier `/bin` et le lancer avec `./sokoban`

#### Compilation :
```bash
  make
```

#### Nettoyage :
```bash
  make clean
```

#### Crée une archive :
```bash
  make archive
```

**Prérequis :** Assurez vous d'avoir `doxygen` et `graphviz` sur votre machine.

#### Crée une doc :
```bash
  make doc
```

## Utilisation

Dans ce jeu vous avez 4 niveaux à votre disposition de base.  
Vous pouvez lancer ces niveaux 1 par 1 simplement en choisissant **Lancer le jeu**.  
Vous pouvez également lancer celui que vous voulez en choisissant **Selectionner un niveau**.

### Touches

| Haut | Bas | Gauche | Droite |Quitter Niveau|
| - | - | - | - | - |
| Z | S | Q | D | C |

### Ajouter des niveaux personalisé
Il est également possible d'ajouter vos propres niveaux.
  
#### Etapes à respecter :
- Il doit être en `.txt`
- Il doit respecter les codes ASCII du jeu. (#-Murs / P-Joueur / C-Caisses / o-Cibles)
- Il doit être placer dans le dossier `/data/lvl/` pour apparaitre dans la liste des niveaux.
## Aperçu

#### Accueil du jeu :
![App Screenshot](https://i.imgur.com/FlTKiwF.png)

#### Fin de niveau :
![App Screenshot](https://imgur.com/rWGYlyO.png)

#### Selection de niveaux :
![App Screenshot](https://imgur.com/TzRYm28.png)

#### Jeu (1er niveau) :
![App Screenshot](https://imgur.com/dtFHy0y.png)

## BONUS

Pour s'amuser, il y a une version bonus utilisant SDL disponible sur la branche SDL :)

## Auteurs

- [@khafdi](https://git.unistra.fr/khafdi)
- [@kylian.gerard](https://github.com/Kylian-Project)
- [@yayyildiz](https://git.unistra.fr/yayyildiz)
