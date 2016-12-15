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
    
    bool passe = false;
    bool fini = false;
    while(!fini)
    {
        newCap = 0;
        cout << "Scores :"<< endl;
        cout << "Noir " << scoreNo << " - " << scoreBl << " Blanc"<<endl<<endl;
        cout << "Tour du Joueur Noir" << endl;
        do
        {
            cout << "Entrez une position valide (ligne puis colonne) ou -1 pour passer" << endl;
            cin >> choixi;
            if(choixi != -1){
                cin >> choixj;
            }
        } while(choixi != -1 && choixj != -1 && !jouerCoup(jeu, choixi-1, choixj-1, noir, newCap));
        if (choixi == -1 || choixj == -1){
            if (passe){
                fini = true;
                continue;
            }
            passe = true;
        } else {
            passe = false;
        }
        scoreNo += newCap;
        newCap = 0;
        afficher(jeu);
        cout << "Tour du Joueur Blanc" << endl;
        do
        {
            cout << "Entrez une position valide (ligne puis colonne) ou -1 pour passer" << endl;
            cin >> choixi;
            if(choixi != -1){
                cin >> choixj;
            }
        } while(choixi != -1 && choixj != -1 && !jouerCoup(jeu, choixi-1, choixj-1, blanc, newCap));
        if (choixi == -1 || choixj == -1){
            if (passe){
                fini = true;
            }
            passe = true;
        } else {
            passe = false;
        }
        scoreBl += newCap;
        afficher(jeu);
    }
    
    return 0;
}

