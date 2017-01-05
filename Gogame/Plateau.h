/* 
 * File:   Plateau.h
 * Author: user
 *
 * Created on 5 janvier 2017, 08:41
 */

#ifndef PLATEAU_H
#define	PLATEAU_H
#include "general.h"

class Plateau {
public:
    Plateau();
    void afficher();
    bool jouerCoup(int i, int j, Case joueur, int &nbCapture);
    bool jouerCoup(Pos pos, Case joueur, int &nbCapture);
    
    /*bool estEntoure(int i, int j, Case couleur);*/
    bool nonSuicide(int i, int j, Case joueur);
    void capture(int i, int j, Case joueur, int &nbCapture);
    bool Tour(Case joueur, int& score, bool& passe);
    Case operator()(int i, int j) const;

    
private:
    Case plateau[TAILLE][TAILLE];

};

#endif	/* PLATEAU_H */

