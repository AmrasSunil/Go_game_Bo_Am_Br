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

#endif	/* GENERAL_H */

