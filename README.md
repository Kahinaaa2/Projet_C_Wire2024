## Analyse et Gestion des Données Énergétiques

Ce projet a pour objectif d'analyser les données des systèmes de distribution d'énergie, afin de détecter les stations en surproduction ou sous-production d'énergie. Le projet utilise un script shell pour le pré-traitement des données et un programme en langage C avec une structure en arbre AVL pour le traitement et l'analyse.

##  Objectifs
- Analyser les données énergétiques 
- Détecter les surproductions et sous-productions dans les stations 
- Utiliser un arbre AVL pour analyser les données.

##  Contenu du Projet
Les composants principaux du projet sont :
- script.sh : Script shell pour le pré-traitement et l'analyse initiale des données énergétiques.
- avl.c : Programme C pour le traitement des données avec une structure en arbre AVL.
- help.txt : Guide et documentation d'utilisation pour le script shell en cas de non respect du nombre d'arguments d'entrée.
- c-wire_v00.dat : Fichier de données énergétiques contenant les données chiffrées des stations.
  
##  Prérequis
Avant de commencer, vous devez avoir :
- Un environnement Linux/Unix.
- Le compilateur GCC pour compiler le programme en langage C.
- Les fichiers requis dans le répertoire du projet :
  -script.sh 
  -avl.c
  -help.txt 
  -c-wire_v00.dat


##  Installation

1. Compiler le programme C : Pour préparer le traitement des données avec l'arbre AVL : gcc -o exec avl.c 
2. Rendre le script exécutable : Pour utiliser le script d'analyse : chmod +x script.sh

##  Utilisation

- script.sh
Ce script effectue l'analyse et prépare les données sous forme CSV.
### Syntaxe : 
./script.sh <répertoire> <type> <consommateur> <numéro_centrale>
### Paramètres :
- <répertoire> : Le chemin du répertoire où se trouve le fichier c-wire_v00.dat.
- <type> : Le type de centrale.
  - hvb : Haute tension
  - hva : Haute tension
  - lv : Basse tension.
- <consommateur> : Le type de consommateurs :
  - all : Tous les consommateurs.
  - comp : Consommateurs commerciaux.
  - indiv : Consommateurs individuels.
- <numéro_centrale> : Le numéro de la centrale (entre 1 et 5)

- Analyser avec le Programme C
Une fois le fichier CSV généré, utilisez le programme C pour analyser ces données avec la structure en arbre AVL.
Exemple : Analyser les données avec la commande suivante : cat lv_all.csv | ./exec

##  Fonctionnement du Code

 script.sh :
- Analyse le fichier c-wire_v00.dat.
- Génère un fichier CSV basé sur nos paramètres d'entrée (type de centrale, numéro de la centrale, consommateur...).
avl.c :
- Trie les données en utilisant un arbre AVL pour optimiser la recherche et l'analyse des données.
- Affiche une synthèse après traitement.


##  Gestion des erreurs

Dans le script shell :
- Vérification des arguments invalides sinon affichage de la page d'aide.
- Validation de l'existence des fichiers nécessaires.
- Affichage d'erreurs en cas de paramètres manquants.

Dans le programme C :
- Gestion mémoire avec des vérifications pour éviter les erreurs de segmentation.
- Gestion avec des AVL pour éviter les déséquilibres.



## 9 Auteurs
- Melanie Avel,
- Kahina Hammad,
- Ashana Maheswaran.




