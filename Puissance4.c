#include "positionJeton.h"
#include "prototypes_Puissance4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOMBRE_LIGNES 6
#define NOMBRE_COLONNES 7

/**
TODO : - SI aucun des joueur n'arrive à gagner et que la grille est pleine ou a au moins une case vide ALORS le signaler et stopper la partie
       - SI un joueur aligne 4 pions (en ligne, en colonne ou en diagonale) ALORS signaler que la partie est gagner, stopper la partie
       - Gérer quand un caractère est entré et pas un int
**/

char grille[NOMBRE_LIGNES][NOMBRE_COLONNES];
const char jetonJoueur1 = 'x';
const char jetonJoueur2 = 'o';

int main(int argc, char const *argv[]) {
  // Appel des fonctions
  initGrille();
  afficheGrille();
  tourJoueurs();

  return 0;
}

void initGrille() {
   char lignes, colonnes;

  // Les for permettent d'initialiser la grille à vide avec des " "
  for (lignes = 0; lignes < NOMBRE_LIGNES; lignes++)
    for (colonnes = 0; colonnes < NOMBRE_COLONNES; colonnes++)
      grille[lignes][colonnes] = ' ';

}

void afficheGrille() {
  char lignes, colonnes;

  puts("   1 2 3 4 5 6 7");

  // Dans le premier for on parcours une ligne et dans le deuxième on s'occupe des colonnes
  for (lignes = 0; lignes < NOMBRE_LIGNES; lignes ++) {
    printf("%d ", lignes+1);
    for (colonnes = 0; colonnes < NOMBRE_COLONNES; colonnes++) {
      printf("|%c", grille[lignes][colonnes]);
    }
    printf("|\n");
  }

}

Coordonnees tourJoueur1() {
  int choixColonne;
  Coordonnees positionJetonAjoute;

  // Traitement pour le Joueur1
  printf("Joueur1 entrez le numéro de la colonne où placer le jeton : ");
  do {
    scanf("%d", &choixColonne);
    /* L'index commence à 0 (et pas 1) donc si le Joueur rentre 1 le jeton sera à l'index 1 et pas à la colonne 1 de la grille
       On doit donc prendre l'index - 1
    */
    choixColonne = choixColonne-1;
    positionJetonAjoute = ajouteJeton(choixColonne, jetonJoueur1);
    afficheGrille();
    if (positionJetonAjoute.indexLigne < 0) {
      switch (positionJetonAjoute.indexLigne) {
        case -1 :
          printf("Cette colonne est déjà pleine.\n");
          break;
        case -2 :
          printf("Entrez un choix de colonne compris entre 1 et %d.\n", NOMBRE_COLONNES);
          break;
      }
      printf("Entrez un choix valide : ");
    }

  } while (positionJetonAjoute.indexLigne < 0);

  return positionJetonAjoute;
}

Coordonnees tourJoueur2() {
  int choixColonne;
  Coordonnees positionJetonAjoute;

  // Traitement pour le Joueur2
  printf("Joueur 2 entrez un numéro de colonne : ");
  do {
    scanf("%d", &choixColonne);
    choixColonne = choixColonne-1;
    positionJetonAjoute = ajouteJeton(choixColonne, jetonJoueur2);
    afficheGrille();
    if (positionJetonAjoute.indexLigne < 0) {
      switch (positionJetonAjoute.indexLigne) {
        case -1 :
          printf("Cette colonne est déjà pleine.\n");
          break;
        case -2 :
          printf("Entrez un choix de colonne compris entre 1 et %d.\n", NOMBRE_COLONNES);
          break;
      }
      printf("Entrez un choix valide : ");
    }

  } while(positionJetonAjoute.indexLigne < 0);

  return positionJetonAjoute;
}

void tourJoueurs() {
  Coordonnees coordonnees;
  int resultatJeuFini;

// Traitement pour un tour complet durant la partie
/* A chaque fois on récupère le résultat renvoyé par la fonction jeuFIni()
   afin de déterminer si un des joueurs à gagné
*/
  do {
    coordonnees = tourJoueur1();
    resultatJeuFini = jeuFini(coordonnees);
    if (resultatJeuFini == 1) {
      puts("Le joueur 1 a gagné.");
      exit(0);
    }

    if (resultatJeuFini == 2) {
      puts("La grille est pleine.");
      exit(0);
    }

    coordonnees = tourJoueur2();
    resultatJeuFini = jeuFini(coordonnees);
    if (resultatJeuFini == 1) {
      puts("Le joueur 2 a gagné.");
      exit(0);
    }

  } while(resultatJeuFini == 0);
  printf("La grille est pleine.\n");
}

Coordonnees ajouteJeton(int indexColonne, char jetonJoueur) {
  char indexLigne = -1;
  Coordonnees coordonnees;

  if (indexColonne < 0 || indexColonne >= NOMBRE_COLONNES) {
    coordonnees.indexColonne = -2;
    coordonnees.indexLigne = -2;
    return coordonnees;
  }

  // Simule la descente du jeton dans la grille et permet de déterminer sur quelle ligne il sera placé
  while (indexLigne != NOMBRE_LIGNES-1 && grille[indexLigne+1][indexColonne] == ' ') {
    indexLigne++;
  }

  // Ajout du jeton, on modifie la valeur stockée à l'index courant, attention il ne s'agit pas ici de L'AFFICHER (cf afficheGrille)
  if (indexLigne >= 0) {
    grille[indexLigne][indexColonne] = jetonJoueur;
  }

/* Dans le cas où la condition indexLigne >= 0 est vrai, alors on return les coordonnées auxquelles on a ajouté le jetons
   Dans le cas contraire, quand le jeton n'a pas été ajouté on return les coordonnées dont l'index de la ligne est -1
*/
  coordonnees.indexLigne = indexLigne;
  coordonnees.indexColonne = indexColonne;

  return coordonnees;

}

int colonneGagante(Coordonnees positionJeton) {

  // On test s'il y a au moins 3 pions en dessous du pion qui vient d'être joué
  if (positionJeton.indexLigne >= NOMBRE_LIGNES-3) {
    // Il y a moins de trois pions en dessous du pions joué, il est donc impossible qu'il y ai une combinaison de 4 pions sur cette colonne
    return 0;
  }

  if (grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+1][positionJeton.indexColonne] && // Vérifie si le jeton en dessous de celui qui vient d'être placé est le même
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+2][positionJeton.indexColonne] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+3][positionJeton.indexColonne]) {
    return 1; // Il y a une combinaison gagnante
  }
  return 0;
}

int grillePleine() {
  int colonnes;

  // Il suffit de verifier si la première ligne est remplie pour savoir que la grille est pleine parce que on ajoute toujours un jeton le plus bas possible
  // On parcours donc les colonnes de la ligne du haut
  for (colonnes = 0; colonnes < NOMBRE_COLONNES; colonnes++) {
    if (grille[0][colonnes] == ' ') {
      return 0;
    }
  }
  return 1;
}

int ligneGagnante(Coordonnees positionJeton) {

   // On test s'il est possible d'avoir une combinaison avec 3 jetons à droite de celui qui vient d'être joué
  if (positionJeton.indexColonne <= NOMBRE_COLONNES-4 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne+2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne+3]) {
    return 1;
  }

  // On test s'il est possible d'avoir une combinaison avec 3 jetons à gauche de celui qui vient d'être joué
  if (positionJeton.indexColonne >= 3 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne-2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne-3]) {
    return 1;
  }

  // On test s'il est possible d'avoir une combinaison avec 1 jeton à gauche et deux à droite de celui qui vient d'être joué
  if (positionJeton.indexColonne >= 1 && positionJeton.indexColonne <= NOMBRE_COLONNES-3 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne+2]) {
    return 1;
  }

  // On test s'il est possible d'avoir une combinaison avec 1 jeton à droite et deux à gauche de celui qui vient d'être joué
  if (positionJeton.indexColonne <= NOMBRE_COLONNES-2 && positionJeton.indexColonne >= 2 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne][positionJeton.indexColonne-2]) {
    return 1;
  }
  return 0;
}

int diagonaleGagnante(Coordonnees positionJeton) {

  // Cas où il peut y avoir deux jetons vers le haut à droite et un en bas à gauche du jeton qui vient d'être joué
  if (positionJeton.indexLigne >= 2 && positionJeton.indexLigne <= NOMBRE_LIGNES-2 &&
      positionJeton.indexColonne >= 1 && positionJeton.indexColonne <= NOMBRE_COLONNES-3 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-1][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-2][positionJeton.indexColonne+2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+1][positionJeton.indexColonne-1]) {
    return 1;
  }

  // Cas où il peut y avoir deux jetons vers le haut à gauche et un en bas à droite du jeton qui vient d'être joué
  if (positionJeton.indexLigne >= 2 && positionJeton.indexLigne <= NOMBRE_LIGNES-2 &&
      positionJeton.indexColonne >= 2 && positionJeton.indexColonne <= NOMBRE_COLONNES-2 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-1][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-2][positionJeton.indexColonne-2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+1][positionJeton.indexColonne+1]) {
    return 1;
  }

  // Cas où il peut y avoir un jeton vers le haut à gauche et deux en bas à droite du jeton qui vient d'être joué
  if (positionJeton.indexLigne >= 1 && positionJeton.indexLigne <= NOMBRE_LIGNES-3 &&
      positionJeton.indexColonne >= 1 && positionJeton.indexColonne <= NOMBRE_COLONNES-3 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-1][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+1][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+2][positionJeton.indexColonne+2]) {
    return 1;
  }

  // Cas où il peut y avoir un jeton vers le haut à droite et deux en bas à gauche du jeton qui vient d'être joué
  if (positionJeton.indexLigne >= 1 && positionJeton.indexLigne <= NOMBRE_LIGNES-3 &&
      positionJeton.indexColonne >= 2 && positionJeton.indexColonne <= NOMBRE_COLONNES-2 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-1][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+1][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+2][positionJeton.indexColonne-2]) {
    return 1;
  }

  // Cas où il peut y avoir trois jetons vers le haut à droite du jeton qui vient d'être joué
  if (positionJeton.indexLigne >= 3 && positionJeton.indexColonne <= NOMBRE_COLONNES-4 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-1][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-2][positionJeton.indexColonne+2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-3][positionJeton.indexColonne+3]) {
    return 1;
  }

  // Cas où il peut y avoir trois jetons vers le haut à gauche du jeton qui vient d'être joué
  if (positionJeton.indexLigne >= 3 && positionJeton.indexColonne <= 3 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-1][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-2][positionJeton.indexColonne-2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne-3][positionJeton.indexColonne-3]) {
    return 1;
  }

  // Cas où il peut y avoir trois jetons vers le bas à gauche du jeton qui vient d'être joué
  if (positionJeton.indexLigne <= NOMBRE_LIGNES-4 && positionJeton.indexColonne >= 3 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+1][positionJeton.indexColonne-1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+2][positionJeton.indexColonne-2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+3][positionJeton.indexColonne-3]) {
    return 1;
  }

  // Cas où il peut y avoir trois jetons vers le bas à droite du jeton qui vient d'être joué
  if (positionJeton.indexLigne <= NOMBRE_LIGNES-4 && positionJeton.indexColonne >= NOMBRE_COLONNES-4 &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+1][positionJeton.indexColonne+1] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+2][positionJeton.indexColonne+2] &&
      grille[positionJeton.indexLigne][positionJeton.indexColonne] == grille[positionJeton.indexLigne+3][positionJeton.indexColonne+3]) {
    return 1;
  }
  return 0;
}

int jeuFini(Coordonnees positionJeton) {
  int retourColonneGagnante, retourLigneGagnante, retourDiagonaleGagnante;
  int retourGrillePleine;

  // On récupère ce que renvoient colonneGagante, ligneGagnante, diagonaleGagnante et grillePleine dans des variables
  retourColonneGagnante = colonneGagante(positionJeton);
  retourLigneGagnante = ligneGagnante(positionJeton);
  retourDiagonaleGagnante = diagonaleGagnante(positionJeton);
  retourGrillePleine = grillePleine();

  // On test les retours et selon les conditions vérifiées on renvoie 1 ou 2
  if (retourColonneGagnante == 1 || retourLigneGagnante == 1 || retourDiagonaleGagnante == 1) {
    return 1;
  }
  if (retourGrillePleine == 1) {
    return 2;
  }
  return 0;
}
