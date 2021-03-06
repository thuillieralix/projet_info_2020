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
    void trouver_indice_centralite_vecteur_propre(int num_pour_comparer, std::vector<std::vector<float> > &indices );
    void trouver_centralite_degres(int num_pour_comparer, std::vector<std::vector<float> > &indices);

    void charger_nouveau_fichier_ponderation(std::string fichier);
    int getOrdre();

    std::vector<std::vector<int>> dijkstra(int depart);

    void composantesConnexe();
    void dfspath(int sommet_number, std::deque<int>& resultat, bool silence);
    void dijkstra_inter(int sommetDepart, std::vector<std::vector<std::vector<int>>> & resDijkstra);

    void centralite_de_proximite(int numero, std::vector<std::vector<float> > &indices);
    void centralite_intermediarite(int numero, std::vector<std::vector<float>> &indice);



    void tester_connexite();
    void supprimer_arrete();

    void comparer_valeurs_indice();

    void mettre_fichier_topo(std::string fichier);
    void mettre_fichier_ponderation(std::string fichier);
    std::string getFichierTopo();
    std::string getFichierPonderation();

    std::vector<int> DFS (int indice0)  ;
    //std::vector<int> BFS (int indice0) const ;
    void afficher_svg();

    int saveIndices();



};


#endif // GRAPHE_H_INCLUDED
