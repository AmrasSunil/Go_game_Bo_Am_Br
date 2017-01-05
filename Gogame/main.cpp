#include <cstdlib>
#include <iostream>

#include "general.h"
#include "Plateau.h"

using namespace std;

//Case jeu[TAILLE][TAILLE];

int main(int argc, char** argv)
{
    Plateau jeu;
    jeu.afficher();
    
    int scoreBl = 0;
    int scoreNo = 0;
    
    bool passe = false;
    bool fini = false;
    bool tourJNoir = true;
    while(!fini)
    {
        cout << "Scores :"<< endl;
        cout << "Noir " << scoreNo << " - " << scoreBl << " Blanc"<<endl<<endl;
        if(tourJNoir){
            fini = jeu.Tour(noir,scoreNo,passe);
        } else {
            fini = jeu.Tour(blanc,scoreBl,passe);
        }
        jeu.afficher();
        tourJNoir = !tourJNoir;
    }
    
    return 0;
}
