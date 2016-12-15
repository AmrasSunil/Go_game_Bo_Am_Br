#ifndef GENERAL_H
#define	GENERAL_H


#include <queue>

enum Case
{
    vide =0,
    blanc =1,
    noir =2
};

struct Pos
{
    int i;
    int j;
    Pos(int _i, int _j)
    { i=_i;j=_j;}
};

const int TAILLE = 5;

void initGoban(Case plateau[TAILLE][TAILLE]);

void afficher(Case plateau[TAILLE][TAILLE]);

bool jouerCoup(Case plateau[TAILLE][TAILLE], int i, int j, Case joueur, int &nbCapture);
bool jouerCoup(Case plateau[TAILLE][TAILLE], Pos pos, Case joueur, int &nbCapture);

bool nonSuicide(Case plateau[TAILLE][TAILLE], int i, int j, Case joueur);
void capture(Case plateau[TAILLE][TAILLE], int i, int j, Case joueur, int &nbCapture);

#endif	/* GENERAL_H */

