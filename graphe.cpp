#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"
#include "svgfile.h"

Graphe::Graphe()
{
    m_orientation = 0;
    m_ordre = 0;
    m_taille = 0;
}

Graphe::Graphe(std::string fichier, std::string fichier2)
{
    std::ifstream lire(fichier.c_str());
    Svgfile svgout ; 

    lire >> m_orientation;
    lire >> m_ordre;
    int sommet_x, sommet_y;
    int m_indice;
    char m_nom;
    for(int i=0; i<m_ordre; i++)
    {
        lire >> m_indice;
        lire >> m_nom;
        lire >> sommet_x;
        lire >> sommet_y;
        Sommet* s = new Sommet(m_indice, m_nom,sommet_x,sommet_y);
        m_sommet.push_back(s);
        svgout.addCross(sommet_x,sommet_y,5,"red");
        svgout.addGrid() ; 
    }
    lire >> m_taille;
    int indice, extremite_dep, extremite_ar;
    int x1, y1, x2, y2 ;

    for(int i=0; i<m_taille; i++)
    {
        lire >> indice;
        lire >> extremite_dep;
        lire >> extremite_ar;
        lire >> x1 ;
        lire >> y1 ;
        lire >> x2 ;
        lire >> y2 ;


        ///faire adjacence
        Arrete* a=new Arrete(extremite_dep,extremite_ar,indice);
        m_arrete.push_back(a);
        m_sommet[extremite_dep]->Ajouter_adj(m_sommet[extremite_ar]);
        m_sommet[extremite_ar]->Ajouter_adj(m_sommet[extremite_dep]);
        svgout.addLine(x1,y1,x2,y2,"black");

    }


    std::ifstream lire2(fichier2.c_str());
    int m_nbre_arrete, poids;

    lire2>>m_nbre_arrete;
    for (int y=0; y<m_nbre_arrete;y++)
    {
        lire2>>indice;

        lire2>>poids;
        m_arrete[indice]->mettre_poids(poids);
    }
}
Graphe::~Graphe()
{ }
void Graphe::afficher()
{

    for(unsigned int i=0; i<m_sommet.size(); i++)
    {
        std::cout << "Sommet " << m_sommet[i]->getIndice() << " : " << m_sommet[i]->getNom()<< std::endl;
        std::cout << "voici les adjacents ";
        m_sommet[i]->Afficher_adj();
        std::cout << std::endl;
    }
    for(unsigned int j=0; j<m_arrete.size(); j++)
    {
        std::cout << "Arrete " << m_arrete[j]->getIndice() << " : " << m_arrete[j]->getDepart()<<" "<< m_arrete[j]->getArrivee();
        std::cout<< "              Poids " <<m_arrete[j]->getPoids();
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl;

}

void Graphe:: Dikjstra (int depart, int arrivee)
{
    std::vector<bool> marque ;
    for (size_t i = 0 ; i<m_sommet.size(); ++i)
        marque.push_back(false) ;
    std::vector <int> pred ;
    for (size_t i=0 ; i<m_sommet.size();++i)
    {
        if(i==depart)
        {
            pred.push_back(depart);
        }
        else pred.push_back(100) ;
    }

      std::vector<int> distance;
        for(size_t i=0; i<m_sommet.size(); ++i)
        {
            if(i==depart)
            {
              distance.push_back(0);
            }else distance.push_back(100);
        }

    std::priority_queue<int, std::vector<int>, std::greater<int>> liste;
        bool fin = false;
        int temp = 0;
        marque[depart]=true;
        for(size_t i =0; i < m_sommet[depart]->getAdj().size();++i)
        {
            liste.push(m_sommet[depart]->getDist()[i]);
            distance[m_sommet[depart]->getAdj()[i]->getNum()] = m_sommet[depart]->getDist()[i];
            pred[m_sommet[depart]->getAdj()[i]->getNum()] = depart;
        }
        while (fin != true)
        {
            fin = true;
            for (size_t i= 0; i<marque.size();++i)
            {
                if (marque[i]==false)
                {
                    fin = false;
                }
            }
            for (size_t i =0; i < distance.size();++i)
            {
                if (distance[i]==liste.top() && marque[i]==false)
                {
                    temp = i;
                    break;
                }
            }
            marque[temp]=true;
            for(size_t i =0; i < m_sommet[temp]->getAdj().size();++i)
            {
                if(distance[m_sommet[temp]->getAdj()[i]->getNum()] > distance[temp] + m_sommet[temp]->getDist()[i] )
                {
                    liste.push(m_sommet[temp]->getDist()[i] + distance[temp]);
                    distance[m_sommet[temp]->getAdj()[i]->getNum()] = m_sommet[temp]->getDist()[i] + distance[temp];
                    pred[m_sommet[temp]->getAdj()[i]->getNum()] = temp;
                }
            }
            liste.pop();
        }
        ///std::cout << "Distance entre " << depart << " et " << arrivee << " : " << distance[arrivee] << std::endl;
        int suiv=arrivee;
        std::queue<int> chemin;
        do
        {
            std::cout << suiv << "<--";
            for(size_t i=0; i<m_sommet[pred[suiv]]->getAdj().size();++i)
            {

                if(m_sommet[pred[suiv]]->getAdj()[i]->getNum()==suiv)
                {
                    chemin.push(m_sommet[pred[suiv]]->getDist()[i]);
                    break;
                }
            }
            suiv=pred[suiv];

        }while (suiv != depart);
        std::cout << depart << " : longueur ";
        while(!chemin.empty())
        {
            std::cout << chemin.front();
            if(chemin.size()!= 1)
                std::cout << "+";
            chemin.pop();
        }


        std::cout << "=" << distance[arrivee]<<std::endl;


}


/*
void Graphe::Dessiner (Svgfile& svgout)
{

    svgout.addLine(2,1,2,3, "black") ;
    svgout.addLine(1,2,3,2,"black");
    svgout.addCross(2,2,0,"red") ;
}*/
