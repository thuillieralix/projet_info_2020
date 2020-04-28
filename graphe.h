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

    void supprimer_arrete();
    void tester_connexite();
};


#endif // GRAPHE_H_INCLUDED
