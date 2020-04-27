# projet_info_2020

#include <iostream>
#include "Graphe.h"
#include "Sommet.h"

int main()
{
    Graphe g("fichier1.txt","fichier_poids.txt");
    g.afficher();
}
