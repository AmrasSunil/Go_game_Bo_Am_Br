#include <gtest/gtest.h>
#include "general.h"
using namespace std;
 
Case jeu_TEST[TAILLE][TAILLE];
int nbCap;

int main (int argc, char** argv)
{
  cout << "hello" << endl;
  ::testing::InitGoogleTest (&argc, argv);
  
  return RUN_ALL_TESTS();
}

TEST(InitPlateau, PlateauVide)
{
    initGoban(jeu_TEST);
    for(int i=0; i<TAILLE; i++)
    {
        for(int j=0; j<TAILLE; j++)
        {
            EXPECT_EQ(vide, jeu_TEST[i][j]);
        }
    }
}

TEST(PositionJouable, CaseVide){
    EXPECT_TRUE(jouerCoup(jeu_TEST, 0, 0, blanc, nbCap));
    EXPECT_FALSE(jouerCoup(jeu_TEST, 0, 0, blanc, nbCap));
}

TEST(PositionJouable, HorsLimites){
    EXPECT_FALSE(jouerCoup(jeu_TEST, -1, -1, blanc, nbCap));
    EXPECT_FALSE(jouerCoup(jeu_TEST, TAILLE, TAILLE/2, blanc, nbCap));
    EXPECT_FALSE(jouerCoup(jeu_TEST, TAILLE/2, TAILLE, blanc, nbCap));
}


 TEST(PositionJouable, Suicide){
     initGoban(jeu_TEST);
     jouerCoup(jeu_TEST, 0, 1, blanc, nbCap);
     jouerCoup(jeu_TEST, 1, 0, blanc, nbCap);
     EXPECT_FALSE(jouerCoup(jeu_TEST, 0, 0, noir, nbCap));
     jouerCoup(jeu_TEST, 2, 0, blanc, nbCap);
     jouerCoup(jeu_TEST, 3, 0, blanc, nbCap);
     jouerCoup(jeu_TEST, 4, 1, blanc, nbCap);
     jouerCoup(jeu_TEST, 4, 2, blanc, nbCap);
     jouerCoup(jeu_TEST, 2, 3, blanc, nbCap);
     jouerCoup(jeu_TEST, 3, 3, blanc, nbCap);
     jouerCoup(jeu_TEST, 2, 4, blanc, nbCap);
     jouerCoup(jeu_TEST, 0, 2, blanc, nbCap);
     
     jouerCoup(jeu_TEST, 0, 3, noir, nbCap);
     jouerCoup(jeu_TEST, 0, 4, noir, nbCap);
     jouerCoup(jeu_TEST, 1, 1, noir, nbCap);
     jouerCoup(jeu_TEST, 1, 2, noir, nbCap);
     jouerCoup(jeu_TEST, 1, 4, noir, nbCap);
     jouerCoup(jeu_TEST, 2, 2, noir, nbCap);
     jouerCoup(jeu_TEST, 3, 1, noir, nbCap);
     jouerCoup(jeu_TEST, 3, 2, noir, nbCap);
     EXPECT_TRUE(jouerCoup(jeu_TEST, 1, 3, noir, nbCap));
     EXPECT_FALSE(jouerCoup(jeu_TEST, 2, 1, noir, nbCap));
     
 }
 
 TEST(Points, capture){
     initGoban(jeu_TEST);
     jeu_TEST[0][1] = blanc;
     nbCap = 0;
     capture(jeu_TEST, 0, 1, blanc, nbCap);
     EXPECT_EQ(0, nbCap);
     jouerCoup(jeu_TEST, 0, 0, noir, nbCap);
     jeu_TEST[1][0] = blanc;
     capture(jeu_TEST, 1, 0, blanc,nbCap);
     EXPECT_EQ(1, nbCap);
     
     jouerCoup(jeu_TEST, 2, 0, blanc, nbCap);
     jouerCoup(jeu_TEST, 3, 0, blanc, nbCap);
     jouerCoup(jeu_TEST, 4, 1, blanc, nbCap);
     jouerCoup(jeu_TEST, 4, 2, blanc, nbCap);
     jouerCoup(jeu_TEST, 2, 3, blanc, nbCap);
     jouerCoup(jeu_TEST, 3, 3, blanc, nbCap);
     jouerCoup(jeu_TEST, 2, 4, blanc, nbCap);
     jouerCoup(jeu_TEST, 0, 2, blanc, nbCap);
     
     jouerCoup(jeu_TEST, 0, 3, noir, nbCap);
     jouerCoup(jeu_TEST, 0, 4, noir, nbCap);
     jouerCoup(jeu_TEST, 1, 1, noir, nbCap);
     jouerCoup(jeu_TEST, 1, 2, noir, nbCap);
     jouerCoup(jeu_TEST, 1, 4, noir, nbCap);
     jouerCoup(jeu_TEST, 2, 2, noir, nbCap);
     jouerCoup(jeu_TEST, 3, 1, noir, nbCap);
     jouerCoup(jeu_TEST, 3, 2, noir, nbCap);
     jeu_TEST[1][3] = blanc;
     capture(jeu_TEST, 1, 3, blanc, nbCap);
     EXPECT_EQ(4, nbCap);
     EXPECT_EQ(vide, jeu_TEST[1][4]);
 }
 