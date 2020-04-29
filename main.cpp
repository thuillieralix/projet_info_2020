#include <iostream>
#include "Graphe.h"
#include "Sommet.h"

int main()
{
    std::string fichier1, fichier2;
    // Graphe g("fichier1.txt","fichier_poids.txt");
    int choix, stop=1, fichier_ok;
    int test=1, saisie_fichier1=0, saisie_fichier2=0, saisie_nouv_fichier=0;
    int choix2;
                            int stop2 = 0 ;

    while (saisie_fichier1!=1)
    {
        std::cout << std::endl<< std::endl<< std::endl;
        std::cout<<"quel est le nom du fichier de topologie ? mettre le.txt à la fin"<<std::endl;
        std::cin>>fichier1;
        std::cout << std::endl<< std::endl<< std::endl;

        if (fichier1=="fichier1.txt"||fichier1=="fichier1V2.txt")
        {
            saisie_fichier1=1;
            std::cout<<"ok"<<std::endl;
            std::cout<<"le fichier a bien charge"<<std::endl;

            while (saisie_fichier2!=1)
            {
                std::cout << std::endl<< std::endl<< std::endl;
                std::cout<<"quel est le nom du fichier de ponderation ? mettre le.txt à la fin"<<std::endl;
                std::cin>>fichier2;
                std::cout << std::endl<< std::endl<< std::endl;

                if (fichier2=="fichier_poids.txt"||fichier2=="fichier_poids_V2.txt")
                {
                    saisie_fichier2=1;
                    std::cout<<"ok"<<std::endl;
                    std::cout<<"le fichier a bien charge"<<std::endl;


                    Graphe g(fichier1,fichier2);

                    while (stop!=0)
                    {
                        std::cout << "Que voulez-vous faire ?" << std::endl;
                        std::cout << " 0: changer fichier pondération " << std::endl;
                        std::cout << " 1: trouver indice de centralite de degre " << std::endl;
                        std::cout << " 2: trouver indice de centralite vecteur propre" << std::endl;
                        std::cout << " 3: supprimer une arrete" << std::endl;
                        std::cout << " 4: tester la connexite du graphe" << std::endl;
                        std::cout << " 5: afficher composantes graphe " << std::endl;
                        std::cout << " 6: trouver l'indice de proximité d'un sommet" << std::endl;
                        std::cout << " 7: comparer indices (avec suppression)" << std::endl<< std::endl;
                        std::cout << " 8: quitter" << std::endl<< std::endl;
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
                                if (fichier2=="fichier_poids.txt"||fichier2=="fichier_poids_V2.txt")
                                {
                                    saisie_nouv_fichier=1;
                                    std::cout<<"ok fichier existe"<<std::endl;
////

                                    g.charger_nouveau_fichier_ponderation(fichier2);
                                    //g.dessiner_graphe(fichier2);

                                }
                                else
                                {
                                    std::cout<<"saisie incorrecte, veuillez recommencer"<<std::endl;
                                }
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
                            g.centralite_de_proximite();
                            std::cout << std::endl<< std::endl<< std::endl;
                            break;

                        case 7:

                            while(stop2 != 1 )
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
                                    g.comparer_valeurs_indice_degre();
                                    break;
                                }
                                case 2:
                                {
                                    stop2=1;

                                    g.trouver_indice_centralite_vecteur_propre(1);

                                    g.supprimer_arrete();

                                    g.trouver_indice_centralite_vecteur_propre(2);

                                    g.comparer_valeurs_indice_vecteur_propre();

                                    break;
                                }
                            
                                
                                default:
                                {
                                    break;
                                }
                                    
                                }
                            }

                        break;

                        case 8:
                            stop = 0;
                        break;

                        default:
                            std::cout << "Erreur de saisie, il faut recommencer" << std::endl;
                            std::cout << std::endl<< std::endl<< std::endl;
                        break;
                        }

                    }
                }
                else
                {
                    std::cout<<"saisie incorrecte, veuillez recommencer"<<std::endl;
                }
            }
        }
        else
        {
            std::cout<<"saisie incorrecte, veuillez recommencer"<<std::endl;
        }
    }
}
