#ifndef DEF_PROTOTYPES
#define DEF_PROTOTYPES
#endif

// Initialise la grille à vide
void initGrille();

// Affiche la grille
void afficheGrille();

// Gère le tour du Joueur1
Coordonnees tourJoueur1();

// Gère le tour du Joueur2
Coordonnees tourJoueur2();

// Gère un tour complet, on y appel tourJoueur1 et tourJoueur2
void tourJoueurs();

// Demande au Joueur d'entrer le numéro de colonne dans laquelle ajouter un jeton et si c'est le tour du Joueur1 ou du Joueur2
Coordonnees ajouteJeton(int indexColonne, char jetonJoueur);

// Dit si la colonne est gagnante ou non
int colonneGagante(Coordonnees positionJeton);

// Dit si la ligne est gagnante ou non
int ligneGagnante(Coordonnees positionJeton);

// Dit si la diagonale est gagnante ou non
int diagonaleGagnante(Coordonnees positionJeton);

// Signal quand la grille est pleine ou s'il reste au moins une case vide
int grillePleine();


// Signal la fin de la partie et le joueur gagnant ou l'ex-aequo
int jeuFini();
