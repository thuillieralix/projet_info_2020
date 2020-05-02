#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string>
#include <windows.h>

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    int k ;

    std::string fichier1, fichier2;
    // Graphe g("fichier1.txt","fichier_poids.txt");
    int choix, stop=1;
    int saisie_fichier1=0, saisie_fichier2=0, saisie_nouv_fichier=0;


    std::cout << std::endl<< std::endl<< std::endl;
    SetConsoleTextAttribute(hConsole,3) ;
    std::cout << "                              ACCESSIBILITE ET VULNERABILITE DES RESEAUX                  " << std::endl ;
    std::cout << std::endl << std::endl << std::endl ;
    SetConsoleTextAttribute(hConsole,3) ;
    std::cout<<"Quel est le nom du fichier de topologie ? mettre le.txt a la fin"<<std::endl;
    std::cin>>fichier1;
    std::cout << std::endl<< std::endl<< std::endl;


    std::cout << std::endl<< std::endl<< std::endl;
    std::cout<<"quel est le nom du fichier de ponderation ? mettre le.txt a la fin"<<std::endl;
    std::cin>>fichier2;
    std::cout << std::endl<< std::endl<< std::endl;

    Graphe g(fichier1,fichier2);
    g.mettre_fichier_topo(fichier1);
    g.mettre_fichier_ponderation(fichier2);
    while (stop!=0)
    {
        std::cout << std::endl<< std::endl<< std::endl;
        SetConsoleTextAttribute(hConsole,15) ;
        std::cout << "Que voulez-vous faire ?" << std::endl;
        std::cout << " 0: changer fichier ponderation " << std::endl;
        std::cout << " 1: trouver indice de centralite de degre " << std::endl;
        std::cout << " 2: trouver indice de centralite vecteur propre" << std::endl;
        std::cout << " 3: trouver indice de centralite d'intermediarite" << '\n';
        std::cout << " 4: supprimer une arrete" << std::endl;
        std::cout << " 5: tester la connexite du graphe" << std::endl;
        std::cout << " 6: afficher composantes graphe " << std::endl;
        std::cout << " 7: quitter" << std::endl;
        std::cout << " 8: comparer indice (choix de quel indice apres)" << std::endl;
        std::cout << " 9: centralite de proximite" << std::endl;
        std::cout << " 10: EXTENSION afficher indice degre NORMALISE en svgout" << std::endl;
        std::cout << " 11: EXTENSION afficher indice vecteur propre NORMALISE en svgout" << std::endl;
        std::cout << " 12: EXTENSION afficher indice proximite NORMALISE en svgout" << std::endl;
        std::cout << " 13: EXTENSION afficher parcours DFS\n" ;
        std::cin>>choix;
        std::cout << std::endl<< std::endl<< std::endl;
        switch (choix)
        {
        case 0:
        {
            saisie_nouv_fichier=0;
            while (saisie_nouv_fichier!=1)
            {
                std::cout<<"quel est le nom du fichier de ponderation ? mettre le.txt à la fin"<<std::endl;
                std::cin>>fichier2;
                saisie_nouv_fichier=1;
                g.mettre_fichier_ponderation(fichier2);
                g.charger_nouveau_fichier_ponderation(fichier2);

            }

            std::cout << std::endl<< std::endl<< std::endl;
            break;
        }

        case 1:
            g.trouver_centralite_degres(0);
            std::cout << std::endl<< std::endl<< std::endl;
            break;

        case 2:
            g.trouver_indice_centralite_vecteur_propre(0);
            std::cout << std::endl<< std::endl<< std::endl;
            break;

        case 3:
            g.centralite_intermediarite();
            break;
        case 4:
            g.supprimer_arrete();
            std::cout << std::endl<< std::endl<< std::endl;
            break;

        case 5:
            g.tester_connexite();
            std::cout << std::endl<< std::endl<< std::endl;
            break;

        case 6:
            g.afficher();
            std::cout << std::endl<< std::endl<< std::endl;
            break;

        case 7:
            stop=0;
            break;

        case 8:
        {
            int choix2;
            int stop2=0;
            while(stop2!=1)
            {
                std::cout<<"quel indice voulez vous comparer ?"<<std::endl;
                std::cout<<"1: indice de centralite de degre"<<std::endl;
                std::cout<<"2: indice de centrzlite de vecteur propre"<<std::endl;
                std::cout<<"3: indice de centralite de proximite"<<std::endl;
                std::cout<<"4: indice de centralite d'intermediarite"<<std::endl;
                std::cin>>choix2;

                switch(choix2)
                {
                case 1:
                {
                    stop2=1;
                    //d'abord le faire avec le graphe normal (normalisé et non normalisé)
                    g.trouver_centralite_degres(1);
                    //après supprimer une ou plusieurs arrete
                    g.supprimer_arrete();
                    //refaire calcul indice degré
                    g.trouver_centralite_degres(2);
                    std::cout << std::endl<< std::endl<<"voici la comparaison pour l'indice de centralite des degres"<< std::endl;
                    //g.comparer_valeurs_indice_degre();
                    g.comparer_valeurs_indice();
                    break;
                }
                case 2:
                {
                    stop2=1;

                    g.trouver_indice_centralite_vecteur_propre(1);

                    g.supprimer_arrete();

                    g.trouver_indice_centralite_vecteur_propre(2);

                    //g.comparer_valeurs_indice_vecteur_propre();
                    g.comparer_valeurs_indice();
                    break;
                }
                case 3:
                {
                    g.centralite_de_proximite(1);
                    g.supprimer_arrete();
                    g.centralite_de_proximite(2);
                    g.comparer_valeurs_indice();
                    break;
                }
                case 4:
                {

                }
                default:
                {

                    break;
                }

                }
            }
            break;
        }
        case 9:
            g.centralite_de_proximite(0);
            std::cout << std::endl<< std::endl<< std::endl;
            break;

        case 10:
            g.trouver_centralite_degres(3);
            break;

        case 11:
            g.trouver_indice_centralite_vecteur_propre(3);
            break;

        case 12:
            g.centralite_de_proximite(3);
            break;

        case 13:
            int indice ;
            std::cout <<"Saisissez un sommet pour appliquer le DFS:";
            std::cin>>indice ;
            g.DFS(indice);
            break ;

        default:
            std::cout << "Erreur de saisie, il faut recommencer" << std::endl;
            std::cout << std::endl<< std::endl<< std::endl;
            break;
        }

    }

}
