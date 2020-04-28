#include <iostream>
#include "Graphe.h"
#include "Sommet.h"

int main()
{

    Graphe monGraphe("fichier1.txt","fichier_poids.txt");
    monGraphe.afficher();

    int sommetDepart = -1;
    std::vector<std::vector<int>> resDijkstra;
    //recherche des chemine les plus courts à partir d'un sommet
    std::cout<<"\t --execution de Dijkstra--"<<std::endl;
    //blindage pour avoir un sommet qui existe et qui est dans le graphe
    while(sommetDepart < 0 || sommetDepart > monGraphe.getOrdre())
    {
        std::cout<<"Entrez le sommet de depart"<<std::endl;
        std::cin>>sommetDepart;
    }
    //recuperation du resultat de l'algo de Dijkstra
    resDijkstra = monGraphe.dijkstra(sommetDepart);
    //il est demande de trouver le plus court chemin
    //on affiche les valeurs trouvées ci dessous
    std::cout << "En partant du sommet numero "<< sommetDepart<< " on obtient les distances suivantes :" << '\n';
        for(int i=0 ; i< monGraphe.getOrdre() ; ++i)
        {
        std::cout   <<"\t le sommet d indice "<<i
                    <<" est a une distance de "<<resDijkstra[i][1]<<" du sommet de depart \n";
                if(resDijkstra[i][2] != -1)
                {
                    std::cout<<" et a comme predecesseur le sommet "<<resDijkstra[i][2];
                }
                else if(resDijkstra[i][2] == -1)
                {
                    std::cout<<" et est le premier sommet";
                }
        std::cout<<std::endl;
        }
}
