#include <cstdlib>
#include <iostream>

#include "general.h"

using namespace std;

Case jeu[TAILLE][TAILLE];

int main(int argc, char** argv)
{
    initGoban(jeu);
    afficher(jeu);
    int choixi = 0;
    int choixj = 0;
    
    int scoreBl = 0;
    int scoreNo = 0;
    
    int newCap = 0;
    
    bool fini = false;
    while(!fini)
    {
        newCap = 0;
        cout << "Tour du Joueur Noir" << endl;
        do
        {
            cout << "Entrez une position valide (ligne puis colonne)" << endl;
            cin >> choixi >> choixj;
        } while(!jouerCoup(jeu, choixi-1, choixj-1, noir, newCap));
        scoreNo += newCap;
        newCap = 0;
        afficher(jeu);
        cout << "Tour du Joueur Blanc" << endl;
        do
        {
            cout << "Entrez une position valide (ligne puis colonne)" << endl;
            cin >> choixi >> choixj;
        } while(!jouerCoup(jeu, choixi-1, choixj-1, blanc, newCap));
        scoreBl += newCap;
        afficher(jeu);
    }
    
    return 0;
}

