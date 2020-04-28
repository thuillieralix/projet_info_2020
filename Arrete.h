#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED

#include <iostream>
#include <vector>
#include <queue>
#include <string>


class Arrete
{
private :
    int m_depart;
    int m_arrivee;
    int m_indice;
    int m_poids;
public :
    Arrete();
    Arrete(int m_depart,int m_arrivee,int m_indice);
    ~Arrete();
    int getDepart();
    int getArrivee();
    int getIndice();
    int getPoids();
    void mettre_poids(int poids);

};

#endif // ARRETE_H_INCLUDED
