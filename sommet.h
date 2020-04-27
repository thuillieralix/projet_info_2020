#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

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
    void Ajouter_adj(Sommet* adj);
    void Afficher_adj();
};

#endif // SOMMET_H_INCLUDED
