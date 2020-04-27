

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "Arrete.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>


class Sommet
{
private :
    int m_indice;
    int m_x;
    int m_y;
    char m_nom;
    std::vector<Sommet*> m_adjacent;
public :
    Sommet();
    Sommet(int indice, char nom,int m_x, int m_y);
    ~Sommet();
    int getIndice();
    char getNom();
    int getTabSize();
    void Ajouter_adj(Sommet* adj);
    void Afficher_adj();

    void actualiserDijkstra(int plusPetitSommet, std::vector<std::vector<int>> &tableau , std::vector<Arrete*> tab_arrete);

};

#endif // SOMMET_H_INCLUDED
