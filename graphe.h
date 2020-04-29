#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include "Sommet.h"
#include "Arrete.h"

class Graphe
{
private :
      int m_ordre;
      int m_taille;
      bool m_orientation;

    std::vector<Sommet*> m_sommet;
    std::vector<Arrete*> m_arrete;
public :
    Graphe();
    Graphe(std::string fichier,std::string fichier2);
    ~Graphe();
    void afficher();
    void trouver_indice_centralite_vecteur_propre();
    void trouver_centralite_degres();

    void charger_nouveau_fichier_ponderation(std::string fichier);
    int getOrdre();

    std::vector<std::vector<int>> dijkstra(int depart);
    void dijkstra_inter(int sommetDepart, std::vector<std::vector<std::vector<int>>> & resDijkstra);
    void centralite_de_proximite();


    void tester_connexite();
    void supprimer_arrete();
};


#endif // GRAPHE_H_INCLUDED
