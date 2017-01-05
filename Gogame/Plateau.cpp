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
    return jouerCoup(pos.i, pos.j, joueur, nbCapture);
}
bool Plateau::jouerCoup(int i, int j, Case joueur, int &nbCapture)
{
    //vérifie que le coup est possible
    if(i>=0 && i<TAILLE && j>=0 && j<TAILLE){
        if (plateau[i][j]==vide){
            nbCapture = 0;
            capture(i, j, joueur, nbCapture);
            if(nbCapture != 0 || nonSuicide(i, j, joueur))
            {
                plateau[i][j] = joueur;
                cout<< nbCapture << " Pierres ont ete capturees"<<endl;
                return true;
            }
        } else {
            cout<< "Case déjà occupée"<<endl;
        }
    }
    else
    {
        cout<< "Hors limites"<<endl;
    }
    return false;
}

bool Plateau::nonSuicide(int i, int j, Case joueur)
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
    
    aTester.push(Pos(i-1, j));
    aTester.push(Pos(i, j-1));
    aTester.push(Pos(i+1, j));
    aTester.push(Pos(i, j+1));
    teste[i][j] = true;
    
    while(aTester.size() > 0){
        Pos a = aTester.front();
        aTester.pop();
        if (a.i>=0 && a.i<TAILLE && a.j>=0 && a.j<TAILLE && !teste[a.i][a.j])
        {
            if(plateau[a.i][a.j] == vide){
                return true;
            } 
            else if(plateau[a.i][a.j] == joueur)
            {
                aTester.push(Pos(a.i-1, a.j));
                aTester.push(Pos(a.i, a.j-1));
                aTester.push(Pos(a.i+1, a.j));
                aTester.push(Pos(a.i, a.j+1));
                teste[a.i][a.j] = true;
            }
        }
    }
    cout << "Pierre en danger"<<endl;
    return false;
}

void Plateau::capture(int i, int j, Case joueur, int &nbCapture)
{
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