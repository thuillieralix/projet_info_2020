#include <iostream>
#include "Graphe.h"
#include "Sommet.h"
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int main()
{

    std::string fichier1, fichier2;
    int choix, stop=1;
    int  saisie_nouv_fichier=0;


        std::cout << std::endl<< std::endl<< std::endl;
        std::cout<<"quel est le nom du fichier de topologie ? mettre le.txt à la fin"<<std::endl;
        std::cin>>fichier1;
        std::cout << std::endl<< std::endl<< std::endl;


                    std::cout << std::endl<< std::endl<< std::endl;
                    std::cout<<"quel est le nom du fichier de ponderation ? mettre le.txt à la fin"<<std::endl;
                    std::cin>>fichier2;
                    std::cout << std::endl<< std::endl<< std::endl;

                        Graphe g(fichier1,fichier2);
                        g.mettre_fichier_topo(fichier1);
                        g.mettre_fichier_ponderation(fichier2);

                        while (stop!=0)
                                    {
                                                    std::cout << std::endl<< std::endl<< std::endl;
                                                    std::cout << "Que voulez-vous faire ?" << std::endl;
                                                    std::cout << " 0: changer fichier pondération " << std::endl;
                                                    std::cout << " 1: trouver indice de centralite de degre " << std::endl;
                                                    std::cout << " 2: trouver indice de centralite vecteur propre" << std::endl;
                                                    std::cout << " 3: supprimer une arrete" << std::endl;
                                                    std::cout << " 4: tester la connexite du graphe" << std::endl;
                                                    std::cout << " 5: afficher composantes graphe " << std::endl;
                                                    std::cout << " 6: quitter" << std::endl<< std::endl;
                                                    std::cout << " 7: comparer indice degre" << std::endl<< std::endl;
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
                                                                    std::cout<<"ok fichier existe"<<std::endl;
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
                                                            g.supprimer_arrete();
                                                            std::cout << std::endl<< std::endl<< std::endl;
                                                            break;

                                                        case 4:
                                                            g.tester_connexite();
                                                            std::cout << std::endl<< std::endl<< std::endl;
                                                            break;

                                                        case 5:
                                                            g.afficher();
                                                            std::cout << std::endl<< std::endl<< std::endl;
                                                            break;

                                                        case 6:
                                                            stop=0;
                                                            break;

                                                        case 7:
                                                            {
                                                                int choix2;
                                                                int stop2=0;
                                                                while(stop2!=1)
                                                                {
                                                                        std::cout<<"quel indice voulez vous comparer ?"<<std::endl;
                                                                        std::cout<<"1: indice de centralite de degre"<<std::endl;
                                                                        std::cout<<"2: indice de centrzlite de vecteur propre"<<std::endl;
                                                                        std::cout<<"3: indice de centralite de proximite"<<std::endl;
                                                                        std::cout<<"4: indoce de centralite d'intermediarite"<<std::endl;
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
                                                                                std::cout << std::endl<< std::endl<<"voici la comparaison pour l'indice de centralité des degrés"<< std::endl;
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
                                                                        default:
                                                                            {

                                                                                break;
                                                                            }

                                                                        }
                                                                }
                                                                break;
                                                            }

                                                        default:
                                                            std::cout << "Erreur de saisie, il faut recommencer" << std::endl;
                                                            std::cout << std::endl<< std::endl<< std::endl;
                                                            break;
                                                    }

                                    }

}
