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
<<<<<<< Updated upstream
=======
    float indice_cvp;

>>>>>>> Stashed changes
    std::vector<Sommet*> m_adjacent;
public :
    Sommet();
    Sommet(int indice, char nom,int m_x, int m_y);
    ~Sommet();
    int getIndice();
    char getNom();
    void Ajouter_adj(Sommet* adj);
    void Afficher_adj();
<<<<<<< Updated upstream
=======
    float getCvp();
    void mettre_indice_cvp(float nb);
    void mettre_indice_cvp_a_1();
    void ADJ_mettre_indice_cvp_a_1();
    int calculer_somme_cvp_adj();

    std::vector<Sommet*> getAdj();

    void actualiserDijkstra(int plusPetitSommet, std::vector<std::vector<int>> &tableau , std::vector<Arrete*> tab_arrete);

>>>>>>> Stashed changes
};

#endif // SOMMET_H_INCLUDED
