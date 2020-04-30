

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "Arrete.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include<math.h>
class Sommet
{
private :
    int m_indice;
    int m_x;
    int m_y;
    char m_nom;
    float indice_cvp;
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
    float getCvp();
    void mettre_indice_cvp(float nb);
    void mettre_indice_cvp_a_1();
    void ADJ_mettre_indice_cvp_a_1();
    int calculer_somme_cvp_adj();

    void actualiserDijkstra(int plusPetitSommet, std::vector<std::vector<int>> &tableau , std::vector<Arrete*> tab_arrete);

    void supprimer_adjacence(int indice_arrivee_arrete_a_supp);
    void parcoursDFS(std::deque<int>& pile , std::vector<int>& temoinParcours, std::deque<int>& resultat, bool silence);

};

#endif // SOMMET_H_INCLUDED
