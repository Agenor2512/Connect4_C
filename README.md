# __Le Puissance 4 en C__
Ce jeu consiste à aligner 4 jetons dans une grille. Il faut pour le moment deux joueurs pour y jouer. Ce projet à pour origine un TP donné lors d'une journée d'immersion en BUT1 d'Informatique.

## Le Déroulement d'une Partie
1. La grille s'affiche et le **Joueur1** doit jouer en premier. Lors de son tour il est indiqué : _'Joueur1 entrez le numéro de la colonne où placer le jeton'_. En effet, il faut entrer le numéro d'une colonne entre 1 et 7.
2. Une fois le numéro de la colonne entré, le jeton '**x**' s'affiche sur la dernière ligne de la grille dans la colonne choisie par le **Joueur1**.
3. C'est ensuite le tour du **Joueur2**, il lui est signalé _'Joueur2 entrez un numéro de colonne'_. Une fois entré, la grille s'affiche de nouveau avec le jeton '**o**' joué par le **Joueur2**.
4. Lorsque **4 jetons** sont alignés en _ligne_, _colonne_ ou _diagonale_ la partie est terminée. De-même, si aucun joueur ne réussi à aligner 4 jetons et que la grille est pleine, la partie est terminée.

## **TODO**

### Jeu
- Ajouter un mode singleplayer

### Documentation
- Ajouter des captures des parties
- Traduire le readme en anglais

### Autres
- Ajouter un makefile
