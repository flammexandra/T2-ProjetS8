# Simulation de l'Algorithme Cyclon

Cette simulation consiste en une simulation de l'algorithme Cyclon, où des nœuds échangent des informations entre eux de manière cyclique. 
Chaque nœud est connecté à un certain nombre de ses voisins et peut échanger des vues avec eux selon l'algorithme Cyclon.

## Contenu des fichiers

- `main.c`: Le point d'entrée du programme. Il initialise le réseau et coordonne les échanges entre les nœuds selon l'algorithme Cyclon.
- `display.c`: Contient des fonctions pour afficher les informations, telles que les voisins d'un nœud ou une liste.
- `exchange.c`: Implémente les fonctions nécessaires pour l'échange d'informations entre les nœuds selon l'algorithme Cyclon.
- `auxiliary.c`: Contient des fonctions auxiliaires utilisées dans d'autres parties du programme.
- `networkInitialization.c`: Initialise le réseau en attribuant des voisins à chaque nœud.
- `exchangeInitialization.c`: Gère l'initialisation des échanges entre les nœuds selon l'algorithme Cyclon.
- `parameters.h`: Définit les paramètres du réseau, tels que le nombre de nœuds, le nombre de voisins par nœud, etc.
- `Makefile`: Un fichier de configuration pour compiler le projet.

## Compilation et exécution

Pour compiler le projet, utilisez la commande `make` dans le terminal. Cela générera un exécutable appelé `main`.

Pour exécuter le programme, utilisez la commande `./main` dans le terminal après avoir compilé le projet avec succès.

## Dépendances

Ce projet nécessite un compilateur C et les bibliothèques standard du langage C.

## Auteurs

Ce projet a été développé par MONY Alexandra dans le cadre du projet S8 de la filière Télécommunication à l'ENSEIRB-MATMECA.
