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
    // Code couleur pour console windows, source : stackoverflow
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices

    std::string fichier1, fichier2;
    // Graphe g("fichier1.txt","fichier_poids.txt");
    int choix, stop=1;
    int saisie_nouv_fichier=0;


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
    /// début menu 
    while (stop!=0)
    {
        std::cout << std::endl<< std::endl<< std::endl;
        SetConsoleTextAttribute(hConsole,15) ;
        std::cout << "Que voulez-vous faire ?" << std::endl;
        std::cout << " 0: changer fichier ponderation " << std::endl;
        std::cout << " 1: trouver indice de centralite de degre " << std::endl;
        std::cout << " 2: trouver indice de centralite vecteur propre" << std::endl;
        std::cout << " 3: trouver indice de centralite d'intermediarite" << '\n';
        std::cout << " 4: trouver indice de centralite de proximite" << std::endl;
        std::cout << " 5: tester la connexite du graphe" << std::endl;
        std::cout << " 6: afficher composantes graphe " << std::endl;
        std::cout << " 7: quitter" << std::endl;
        std::cout << " 8: comparer indice (choix de quel indice + suppression d'arrete apres)" << std::endl;
        std::cout << " 9: supprimer une arrete" << std::endl;
        std::cout << " 10: EXTENSION afficher indice degre NORMALISE en svgout" << std::endl;
        std::cout << " 11: EXTENSION afficher indice vecteur propre NORMALISE en svgout" << std::endl;
        std::cout << " 12: EXTENSION afficher indice proximite NORMALISE en svgout" << std::endl;
        std::cout << " 13: EXTENSION afficher parcours DFS\n" ;
        std::cout << " 14: afficher graphe en SVG\n" ;
        std::cout << " 15: EXTENSION afficher indice intermediarite NORMALISE en svgout" << std::endl;
        std::cout << " 16: sauvegarde des indices dans un fichier txt" << '\n';
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
            {
                std::vector<std::vector<float>> v = {{0,0},{0,0}};
                g.trouver_centralite_degres(0, v);
                std::cout << std::endl<< std::endl<< std::endl;
            }

            break;

        case 2:
            {
                std::vector<std::vector<float>> v = {{0,0},{0,0}};
                g.trouver_indice_centralite_vecteur_propre(0, v);
                std::cout << std::endl<< std::endl<< std::endl;
            }
            break;

        case 3:
            {
                std::vector<std::vector<float>> v = {{0,0},{0,0}};
                g.centralite_intermediarite(0,v);
            }

            break;
        case 4:
            {
                std::vector<std::vector<float>> v = {{0,0},{0,0}};
                g.centralite_de_proximite(0,v);
                std::cout << std::endl<< std::endl<< std::endl;
            }
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
                    std::vector<std::vector<float>> v = {{0,0},{0,0}};
                    stop2=1;
                    //d'abord le faire avec le graphe normal (normalisé et non normalisé)
                    g.trouver_centralite_degres(1,v);
                    //après supprimer une ou plusieurs arrete
                    g.supprimer_arrete();
                    //refaire calcul indice degré
                    g.trouver_centralite_degres(2,v);
                    std::cout << std::endl<< std::endl<<"voici la comparaison pour l'indice de centralite des degres"<< std::endl;
                    //g.comparer_valeurs_indice_degre();
                    g.comparer_valeurs_indice();
                    break;
                }
                case 2:
                {
                    std::vector<std::vector<float>> v = {{0,0},{0,0}};
                    stop2=1;

                    g.trouver_indice_centralite_vecteur_propre(1,v);

                    g.supprimer_arrete();

                    g.trouver_indice_centralite_vecteur_propre(2,v);

                    //g.comparer_valeurs_indice_vecteur_propre();
                    g.comparer_valeurs_indice();
                    break;
                }
                case 3:
                {
                    stop2=1;
                    std::vector<std::vector<float>> v = {{0,0},{0,0}};
                    g.centralite_de_proximite(1,v);
                    g.supprimer_arrete();
                    g.centralite_de_proximite(2,v);
                    g.comparer_valeurs_indice();
                    break;
                }
                case 4:
                {

                    stop2=1;
                    std::vector<std::vector<float>> v = {{0,0},{0,0}};
                    g.centralite_intermediarite(1,v);
                    g.supprimer_arrete();
                    g.centralite_intermediarite(2,v);
                    g.comparer_valeurs_indice();
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
            g.supprimer_arrete();
            std::cout << std::endl<< std::endl<< std::endl;
            break;

        case 10:
            {
                std::vector<std::vector<float>> v = {{0,0},{0,0}};
                std::cout<<std::endl;
                std::cout<<"en rouge : indice le + haut"<<std::endl;
                std::cout<<"en orange : 2eme indice le + haut"<<std::endl;
                std::cout<<"en jaune : 3eme indice le + haut"<<std::endl<<std::endl<<std::endl;
                g.trouver_centralite_degres(3,v);
            }
            break;

        case 11:
        {
            std::vector<std::vector<float>> v = {{0,0},{0,0}};
            std::cout<<std::endl;
            std::cout<<"en rouge : indice le + haut"<<std::endl;
            std::cout<<"en orange : 2eme indice le + haut"<<std::endl;
            std::cout<<"en jaune : 3eme indice le + haut"<<std::endl<<std::endl<<std::endl;
            g.trouver_indice_centralite_vecteur_propre(3,v);
        }
            break;

        case 12:
        {
                std::vector<std::vector<float>> v = {{0,0},{0,0}};
                std::cout<<std::endl;
                std::cout<<"en rouge : indice le + haut"<<std::endl;
                std::cout<<"en orange : 2eme indice le + haut"<<std::endl;
                std::cout<<"en jaune : 3eme indice le + haut"<<std::endl<<std::endl<<std::endl;
                g.centralite_de_proximite(3,v);

        }
            break;

        case 13:
            int indice ;
            std::cout <<"Saisissez un sommet pour appliquer le DFS:";
            std::cin>>indice ;
            g.DFS(indice);
            break ;

        case 14:
            g.afficher_svg();
            break;

        case 15:
            {
            std::vector<std::vector<float>> v = {{0,0},{0,0}};
            std::cout<<std::endl;
            std::cout<<"en rouge : indice le + haut"<<std::endl;
            std::cout<<"en orange : 2eme indice le + haut"<<std::endl;
            std::cout<<"en jaune : 3eme indice le + haut"<<std::endl<<std::endl<<std::endl;
            g.centralite_intermediarite(3,v);
            break;
            }

        case 16:
            {
                int succes = 0;
                while(succes != 1)
                {
                    succes = g.saveIndices();
                }
            }
            break;

        default:
            std::cout << "Erreur de saisie, il faut recommencer" << std::endl;
            std::cout << std::endl<< std::endl<< std::endl;
            break;
        }

    }

}
