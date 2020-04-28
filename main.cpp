#include <iostream>
#include "Graphe.h"
#include "Sommet.h"

int main()
{

    Graphe g("fichier1.txt","fichier_poids.txt");

    int choix, stop=1;
    while (stop!=0)
    {
        std::cout << "Que voulez-vous faire ?" << std::endl;
        std::cout << " 0: afficher composantes graphe " << std::endl;
        std::cout << " 1: trouver indice de centralite de degre " << std::endl;
        std::cout << " 2: trouver indice de centralite vecteur propre" << std::endl;
        std::cout << " 3: supprimer une arrete" << std::endl;
        std::cout << " 4: tester la connexite du graphe" << std::endl;
        std::cout << " 5: quitter" << std::endl<< std::endl;
        std::cin>>choix;
        std::cout << std::endl<< std::endl<< std::endl;
        switch (choix)
        {
            case 0:
                g.afficher();
                std::cout << std::endl<< std::endl<< std::endl;
                break;

            case 1:
                g.trouver_centralite_degres();
                std::cout << std::endl<< std::endl<< std::endl;
                break;

            case 2:
                g.trouver_indice_centralite_vecteur_propre();
                std::cout << std::endl<< std::endl<< std::endl;
                break;

            case 3:
                g.supprimer_arrete();
                std::cout << std::endl<< std::endl<< std::endl;
                break;

            case 4:
                g.tester_connexite();
                std::cout << std::endl<< std::endl<< std::endl;
                break;

            case 5:
                stop=0;
                break;

            default:
                std::cout << "Erreur de saisie, il faut recommencer" << std::endl;
                std::cout << std::endl<< std::endl<< std::endl;
                break;
        }

    }
}
