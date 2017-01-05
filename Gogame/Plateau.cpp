/* 
 * File:   Plateau.cpp
 * Author: user
 * 
 * Created on 5 janvier 2017, 08:41
 */

#include <iostream>
#include "Plateau.h"
using namespace std;

Plateau::Plateau() {
    /**
     Le plateau gère l'ensemble du déroulement de la partie ainsi que l'état du jeu
    */
    
    for (int i=0; i<TAILLE; i++)
    {
        for (int j=0; j<TAILLE; j++)
        {
            plateau[i][j]=vide;
        }
    }
}

void Plateau::afficher()
{
    /**
    Affichage du plateau
    */
    
    cout << endl << "  ";
    for (int k=0; k<TAILLE; k++)
    {
        cout << k+1 << " ";
    }
    cout << endl;
    for (int i=0; i<TAILLE; i++)
    {
        cout << i+1;
        for (int j=0; j<TAILLE; j++)
        {
            switch(plateau[i][j])
            {
                case vide :
                    cout << " +" ;
                    break;
                case blanc :
                    cout << " O" ;
                    break;
                case noir :
                    cout << " X" ;
                    break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool Plateau::jouerCoup(Pos pos, Case joueur, int &nbCapture)
{
    /**
    Permet de jouer un coup à partir d'un doublet d'entiers, utilisé dans les appels internes
    */
     
    return jouerCoup(pos.i, pos.j, joueur, nbCapture);
}
bool Plateau::jouerCoup(int i, int j, Case joueur, int &nbCapture)
{
    /**
     * Cette méthode permet de poser une pièce sur le plateau, elle traite la validité du coup et ses éventuelles conséquences
     * @param i ligne
     * @param j colonne
     * @param joueur joueur dont c'est le tour
     * @param nbCapture référence pour récupérer le nombre de pierres capturées
     * @return validité du coup
     */
    
    //vérifie que le coup est possible
    if(i>=0 && i<TAILLE && j>=0 && j<TAILLE){
        if (plateau[i][j]==vide){
            //On s'assure dans un premier temps que la case est vide
            nbCapture = 0;
            
            //On regarde ensuite si cette pose entraîne la capture de pierres adverses
            capture(i, j, joueur, nbCapture);
            if(nbCapture != 0 || nonSuicide(i, j, joueur))
            {
                //On poursuit si des pierres ont été capturées ou si la position n'est pas une position suicidaire
                plateau[i][j] = joueur;
                cout<< nbCapture << " Pierres ont ete capturees"<<endl;
                
                //Si la pose est une réussite on renvoie true
                return true;
            }
        } else {
            //On affiche la cause de l'échec de la pose
            cout<< "Case déjà occupée"<<endl;
        }
    }
    else
    {
        //On affiche la cause de l'échec de la pose
        cout<< "Hors limites"<<endl;
    }
    //Si la pose est impossible à cet endroit on renvoie false
    return false;
}

/*bool Plateau::estEntoure(int i, int j, Case couleur)
{
    queue<Pos> aTester;
    bool teste[TAILLE][TAILLE];
    for (int _i=0; _i<TAILLE; _i++)
    {
        for (int _j=0; _j<TAILLE; _j++)
        {
            teste[_i][_j] = false;
        }
    }
}*/

bool Plateau::nonSuicide(int i, int j, Case joueur)
{
    /**
     * Cette fonction permet de s'assurer que la position demandée n'est pas une position suicidaire
     * On s'en sert aussi pour la capture des pièces
     * @param i ligne
     * @param j colonne
     * @param joueur joueur dont c'est le tour
     * @return caractère suicidaire de la position
     */
    
    //Pour déterminer si le groupe de pierres est isolé et entouré on utilise une structure de file
    queue<Pos> aTester;
    //On initialise également un tableau des positions déjà testées
    bool teste[TAILLE][TAILLE];
    for (int _i=0; _i<TAILLE; _i++)
    {
        for (int _j=0; _j<TAILLE; _j++)
        {
            teste[_i][_j] = false;
        }
    }
    
    //On rajoute immédiatement les quatres cases entourant la pierre aux cases à tester
    aTester.push(Pos(i-1, j));
    aTester.push(Pos(i, j-1));
    aTester.push(Pos(i+1, j));
    aTester.push(Pos(i, j+1));
    
    //La case initiale étant vide dans certains cas elle doit être considérée comme déjà testée
    teste[i][j] = true;
    
    //La boucle va s'exécuter tant que la file n'est pas vide
    while(aTester.size() > 0)
    {
        // On récupère le premier élément de la file
        Pos a = aTester.front();
        aTester.pop();
        
        //On vérifie si ces coordonnées appartiennent au tableau et si la case n'a pas encore été testée
        if (a.i>=0 && a.i<TAILLE && a.j>=0 && a.j<TAILLE && !teste[a.i][a.j])
        {
            if(plateau[a.i][a.j] == vide){
                //Dès que l'on trouve une case vide on sait que la position n'est pas suicidaire, on peut arrêter de chercher
                return true;
            } 
            else if(plateau[a.i][a.j] == joueur)
            {
                //Si la case est au même joueur on va mettre dans la file tous ses voisins et changer sa valeur de test
                aTester.push(Pos(a.i-1, a.j));
                aTester.push(Pos(a.i, a.j-1));
                aTester.push(Pos(a.i+1, a.j));
                aTester.push(Pos(a.i, a.j+1));
                teste[a.i][a.j] = true;
            }
            //Si la case est possédée par le joueur adverse on ne fait rien et on passe directement à la suivante
        }
    }
    //On signale que la position ne peut être jouée
    cout << "Pierre en danger"<<endl;
    return false;
}

void Plateau::capture(int i, int j, Case joueur, int &nbCapture)
{
    /**
     * Test et réalisation de la capture de pierres
     * @param i ligne
     * @param j colonne
     * @param joueur joueur dont c'est le tour
     * @param nbCapture nombre de pierres capturées
     */
    queue<Pos> aTester;
    Case couleur;
    if (joueur == noir){
        couleur = blanc;
    } else {
        couleur = noir;
    }
    bool teste[TAILLE][TAILLE];   
    plateau[i][j]= joueur;
    //Test capture haut
    for (int _i=0; _i<TAILLE; _i++)
    {
        for (int _j=0; _j<TAILLE; _j++)
        {
            teste[_i][_j] = false;
        }
    }
    if (i-1>=0 && i-1<TAILLE && j>=0 && j<TAILLE &&plateau[i-1][j] == couleur){
        if (!nonSuicide(i-1, j, couleur)){
            aTester.push(Pos(i-1, j));
            while(aTester.size() > 0){
                Pos a = aTester.front();
                aTester.pop();
                if (a.i>=0 && a.i<TAILLE && a.j>=0 && a.j<TAILLE && !teste[a.i][a.j] && plateau[a.i][a.j] == couleur){
                    aTester.push(Pos(a.i-1, a.j));
                    aTester.push(Pos(a.i, a.j-1));
                    aTester.push(Pos(a.i+1, a.j));
                    aTester.push(Pos(a.i, a.j+1));
                    teste[a.i][a.j] = true;
                    plateau[a.i][a.j] = vide;
                    nbCapture +=1;
                }
            }
        }
    }
    // Test capture Gauche
    for (int _i=0; _i<TAILLE; _i++)
    {
        for (int _j=0; _j<TAILLE; _j++)
        {
            teste[_i][_j] = false;
        }
    }
    if (i>=0 && i<TAILLE && j-1>=0 && j-1<TAILLE &&plateau[i][j-1] == couleur){
        if (!nonSuicide(i, j-1, couleur)){
            aTester.push(Pos(i, j-1));
            while(aTester.size() > 0){
                Pos a = aTester.front();
                aTester.pop();
                if (a.i>=0 && a.i<TAILLE && a.j>=0 && a.j<TAILLE && !teste[a.i][a.j] && plateau[a.i][a.j] == couleur){
                    aTester.push(Pos(a.i-1, a.j));
                    aTester.push(Pos(a.i, a.j-1));
                    aTester.push(Pos(a.i+1, a.j));
                    aTester.push(Pos(a.i, a.j+1));
                    teste[a.i][a.j] = true;
                    plateau[a.i][a.j] = vide;
                    nbCapture +=1;
                }
            }
        }
    }
    // Test Capture Bas
    for (int _i=0; _i<TAILLE; _i++)
    {
        for (int _j=0; _j<TAILLE; _j++)
        {
            teste[_i][_j] = false;
        }
    }
    if (i+1>=0 && i+1<TAILLE && j>=0 && j<TAILLE &&plateau[i+1][j] == couleur){
        if (!nonSuicide(i+1, j, couleur)){
            aTester.push(Pos(i+1, j));
            while(aTester.size() > 0){
                Pos a = aTester.front();
                aTester.pop();
                if (a.i>=0 && a.i<TAILLE && a.j>=0 && a.j<TAILLE && !teste[a.i][a.j] && plateau[a.i][a.j] == couleur){
                    aTester.push(Pos(a.i-1, a.j));
                    aTester.push(Pos(a.i, a.j-1));
                    aTester.push(Pos(a.i+1, a.j));
                    aTester.push(Pos(a.i, a.j+1));
                    teste[a.i][a.j] = true;
                    plateau[a.i][a.j] = vide;
                    nbCapture +=1;
                }
            }
        }
    }
    // Test capture Droit
    for (int _i=0; _i<TAILLE; _i++)
    {
        for (int _j=0; _j<TAILLE; _j++)
        {
            teste[_i][_j] = false;
        }
    }
    if (i>=0 && i<TAILLE && j+1>=0 && j+1<TAILLE &&plateau[i][j+1] == couleur){
        if (!nonSuicide(i, j+1, couleur)){
            aTester.push(Pos(i, j+1));
            while(aTester.size() > 0){
                Pos a = aTester.front();
                aTester.pop();
                if (a.i>=0 && a.i<TAILLE && a.j>=0 && a.j<TAILLE && !teste[a.i][a.j] && plateau[a.i][a.j] == couleur){
                    aTester.push(Pos(a.i-1, a.j));
                    aTester.push(Pos(a.i, a.j-1));
                    aTester.push(Pos(a.i+1, a.j));
                    aTester.push(Pos(a.i, a.j+1));
                    teste[a.i][a.j] = true;
                    plateau[a.i][a.j] = vide;
                    nbCapture +=1;
                }
            }
        }
    }
    plateau[i][j]= vide;
}

bool Plateau::Tour(Case joueur, int& score, bool& passe)
{
    /**
     * Gestion du tour de joueur
     * @param joueur joueur dont c'est le tour
     * @param score score actuel du joueur
     * @param passe le joueur précédent a-t-il passé son tour
     * @return  arrêt ou non du jeu
     */
    if(joueur == noir)
    {
        cout << "Tour du Joueur Noir" << endl;
    }
    else
    {
        cout << "Tour du Joueur Blanc" << endl;
    }
    int newCap = 0;
    int choixi = 0;
    int choixj = 0;
    do
    {
        cout << "Entrez une position valide (ligne puis colonne) ou -1 pour passer" << endl;
        cin >> choixi;
        if(choixi != -1){
            cin >> choixj;
        }
    } while(choixi != -1 && choixj != -1 && !jouerCoup(choixi-1, choixj-1, joueur, newCap));
    if (choixi == -1 || choixj == -1){
        if (passe){
            return true;
        }
        passe = true;
    } else {
        passe = false;
    }
    score += newCap;
    return false;
    
}

Case Plateau::operator()(int i, int j) const
{
    return plateau[i][j];
}