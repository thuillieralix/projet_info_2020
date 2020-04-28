#include <iostream>
#include "Graphe.h"
#include "Sommet.h"

int main()
{
    Graphe g("fichier1.txt","fichier_poids.txt");
    g.trouver_indice_centralite_vecteur_propre();
    g.afficher();

    bool test = false ;
    int debut, fin ;
    while(!test)
    {
        std::cout << "Debut:" ;
        std::cin >> debut ;
        std::cout << "Fin:";
        std::cin >> fin ;
        g.Dikjstra(debut,fin) ;
        std::cout << "\n" ;
    }
    return 0 ;
}
