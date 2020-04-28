#include <iostream>
#include "Graphe.h"
#include "Sommet.h"

int main()
{

    Graphe monGraphe("fichier1.txt","fichier_poids.txt");
    monGraphe.afficher();

    monGraphe.centralite_de_proximite();
}
