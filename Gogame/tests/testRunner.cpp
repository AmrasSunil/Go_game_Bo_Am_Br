#include <gtest/gtest.h>
#include "../general.h"
#include "../Plateau.h"
using namespace std;
 

int nbCap;

int main (int argc, char** argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  
  return RUN_ALL_TESTS();
}

TEST(InitPlateau, PlateauVide)
{
    Plateau jeu_TEST;
    for(int i=0; i<TAILLE; i++)
    {
        for(int j=0; j<TAILLE; j++)
        {
            EXPECT_EQ(vide, jeu_TEST(i, j));
        }
    }
}

TEST(PositionJouable, CaseVide){
    Plateau jeu_TEST;
    EXPECT_TRUE(jeu_TEST.jouerCoup(0, 0, blanc, nbCap));
    EXPECT_FALSE(jeu_TEST.jouerCoup(0, 0, blanc, nbCap));
}

TEST(PositionJouable, HorsLimites){
    Plateau jeu_TEST;
    EXPECT_FALSE(jeu_TEST.jouerCoup(-1, -1, blanc, nbCap));
    EXPECT_FALSE(jeu_TEST.jouerCoup(TAILLE, TAILLE/2, blanc, nbCap));
    EXPECT_FALSE(jeu_TEST.jouerCoup(TAILLE/2, TAILLE, blanc, nbCap));
}


 TEST(PositionJouable, Suicide){
     Plateau jeu_TEST;
     jeu_TEST.jouerCoup(0, 1, blanc, nbCap);
     jeu_TEST.jouerCoup(1, 0, blanc, nbCap);
     EXPECT_FALSE(jeu_TEST.jouerCoup(0, 0, noir, nbCap));
     jeu_TEST.jouerCoup(2, 0, blanc, nbCap);
     jeu_TEST.jouerCoup(3, 0, blanc, nbCap);
     jeu_TEST.jouerCoup(4, 1, blanc, nbCap);
     jeu_TEST.jouerCoup(4, 2, blanc, nbCap);
     jeu_TEST.jouerCoup(2, 3, blanc, nbCap);
     jeu_TEST.jouerCoup(3, 3, blanc, nbCap);
     jeu_TEST.jouerCoup(2, 4, blanc, nbCap);
     jeu_TEST.jouerCoup(0, 2, blanc, nbCap);
     
     jeu_TEST.jouerCoup(0, 3, noir, nbCap);
     jeu_TEST.jouerCoup(0, 4, noir, nbCap);
     jeu_TEST.jouerCoup(1, 1, noir, nbCap);
     jeu_TEST.jouerCoup(1, 2, noir, nbCap);
     jeu_TEST.jouerCoup(1, 4, noir, nbCap);
     jeu_TEST.jouerCoup(2, 2, noir, nbCap);
     jeu_TEST.jouerCoup(3, 1, noir, nbCap);
     jeu_TEST.jouerCoup(3, 2, noir, nbCap);
     EXPECT_TRUE(jeu_TEST.jouerCoup(1, 3, noir, nbCap));
     EXPECT_FALSE(jeu_TEST.jouerCoup(2, 1, noir, nbCap));
     
 }
 /*
 TEST(Deroulement, tour){
     Plateau jeu_TEST;
     bool passe = false;
     cout<<"Entrez 1 puis 1"<<endl;
     EXPECT_FALSE(jeu_TEST.Tour(blanc, nbCap, passe));
     cout<<"Entrez -1"<<endl;
     EXPECT_FALSE(jeu_TEST.Tour(blanc, nbCap, passe));
 }
 
 TEST(Deroulement, fin){
     Plateau jeu_TEST;
     bool passe = true;
     cout<<"Entrez -1"<<endl;
     EXPECT_TRUE(jeu_TEST.Tour(blanc, nbCap, passe));
 }
 */
 TEST(Points, capture){
     Plateau jeu_TEST;
     nbCap = 0;
     jeu_TEST.jouerCoup(0, 1, blanc, nbCap);
     EXPECT_EQ(0, nbCap);
     jeu_TEST.jouerCoup(0, 0, noir,nbCap);
     jeu_TEST.jouerCoup(1, 0, blanc,nbCap);
     EXPECT_EQ(1, nbCap);
     
     jeu_TEST.jouerCoup(2, 0, blanc, nbCap);
     jeu_TEST.jouerCoup(3, 0, blanc, nbCap);
     jeu_TEST.jouerCoup(4, 1, blanc, nbCap);
     jeu_TEST.jouerCoup(4, 2, blanc, nbCap);
     jeu_TEST.jouerCoup(2, 3, blanc, nbCap);
     jeu_TEST.jouerCoup(3, 3, blanc, nbCap);
     jeu_TEST.jouerCoup(2, 4, blanc, nbCap);
     jeu_TEST.jouerCoup(0, 2, blanc, nbCap);
     
     jeu_TEST.jouerCoup(0, 3, noir, nbCap);
     jeu_TEST.jouerCoup(0, 4, noir, nbCap);
     jeu_TEST.jouerCoup(1, 1, noir, nbCap);
     jeu_TEST.jouerCoup(1, 2, noir, nbCap);
     jeu_TEST.jouerCoup(1, 4, noir, nbCap);
     jeu_TEST.jouerCoup(2, 2, noir, nbCap);
     jeu_TEST.jouerCoup(3, 1, noir, nbCap);
     jeu_TEST.jouerCoup(3, 2, noir, nbCap);
     jeu_TEST.jouerCoup(1, 3, blanc, nbCap);
     EXPECT_EQ(3, nbCap);
     EXPECT_EQ(vide, jeu_TEST(1, 4));
 }
 