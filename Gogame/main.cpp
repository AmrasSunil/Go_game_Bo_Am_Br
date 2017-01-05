#include <cstdlib>
#include <iostream>

#include "general.h"
#include "Plateau.h"

using namespace std;

int main(int argc, char** argv)
{
    Plateau jeu; // initialisation du plateau de jeu
    jeu.afficher();
    
    // Scores des deux joueurs
    int scoreBl = 0;
    int scoreNo = 0;
    
    bool passe = false; // sert à détecter deux passages successifs
    bool fini = false; // détecte la fin de la partie
    bool tourJNoir = true; // pour savoir si c'est le tour du joueur noir ou du joueur blanc
    
    // Boucle principale de la partie
    while(!fini)
    {
        // Affichage des scores
        cout << "Scores :"<< endl;
        cout << "Noir " << scoreNo << " - " << scoreBl << " Blanc"<<endl<<endl;
        if(tourJNoir){
            fini = jeu.Tour(noir,scoreNo,passe); // tour du joueur noir
        } else {
            fini = jeu.Tour(blanc,scoreBl,passe); // tour du joueur blanc
        }
        jeu.afficher();
        tourJNoir = !tourJNoir; // passage au tour du joueur suivant
    }
    
    return 0;
}
