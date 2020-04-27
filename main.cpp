#include <iostream>
#include "Graphe.h"
#include "Sommet.h"

int main()
{
    Graphe g("fichier1.txt","fichier_poids.txt");
    g.trouver_indice_centralite();
    g.afficher();
}
