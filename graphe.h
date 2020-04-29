#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include "Sommet.h"
#include "Arrete.h"
#include <math.h>

class Graphe
{
private :
      int m_ordre;
      int m_taille;
      bool m_orientation;
    std::string fichier_topologie;
    std::string fichier_ponderation;

    std::vector<Sommet*> m_sommet;
    std::vector<Arrete*> m_arrete;
public :
    Graphe();
    Graphe(std::string fichier,std::string fichier2);
    ~Graphe();
    void afficher();
    //void dessiner_graphe(std::string fichier) ;
    void trouver_indice_centralite_vecteur_propre(int num_pour_comparer);
    void trouver_centralite_degres(int num_pour_comparer);

    void charger_nouveau_fichier_ponderation(std::string fichier);
    int getOrdre();

    std::vector<std::vector<int>> dijkstra(int depart);
    void centralite_de_proximite();


    void tester_connexite();
    void supprimer_arrete();

    void comparer_valeurs_indice();

    void mettre_fichier_topo(std::string fichier);
    void mettre_fichier_ponderation(std::string fichier);
    std::string getFichierTopo();
    std::string getFichierPonderation();


};


#endif // GRAPHE_H_INCLUDED
