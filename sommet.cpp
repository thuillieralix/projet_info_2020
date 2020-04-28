#include "Sommet.h"
#include "Arrete.h"

Sommet::Sommet()
{
    m_nom =' ';
    m_indice=0;
    m_x =0;
    m_y=0;

}
Sommet::Sommet(int indice, char nom,int x, int y)
{
    m_indice = indice;
    m_nom=nom;
    m_x=x;
    m_y=y;
}

Sommet::~Sommet()
{ }

int Sommet::getIndice()
{
    return m_indice;
}

char Sommet::getNom()
{
    return m_nom;
}

int Sommet::getTabSize()
{
    return m_adjacent.size();
}
void Sommet::Ajouter_adj(Sommet* adj)
{
   m_adjacent.push_back(adj);
}
void Sommet::Afficher_adj()
{
    for(size_t i=0; i< m_adjacent.size(); ++i)
    {
        std::cout<<m_adjacent[i]->m_nom<<",";
    }
    std::cout<<std::endl;
}

void Sommet::actualiserDijkstra(int plusPetitSommet, std::vector<std::vector<int>> &tableau, std::vector<Arrete*> tab_arrete)
{
    std::cout<<"entree dans le dijkstra Sommet"<<std::endl;
    for( int i=0 ; i<getTabSize() ; ++i)
    {
        //si le sommet a des sucesseurs
        if(m_adjacent[i] != nullptr)
        {
            //si la case n'a pas été "terminée"
            if(tableau[m_adjacent[i]->getIndice()][0] != 1)
            {
                //si on a une distance plus petite que celle renseignée ou un nouveau sommet
                if((tableau[m_adjacent[i]->getIndice()][1] > tableau[plusPetitSommet][1] + tab_arrete[i]->getPoids()) || tableau[m_adjacent[i]->getIndice()][1] == -1 )
                {
                    //on met le numero, le poids et le predecesseur dans la case correspondante tableau
                    tableau[m_adjacent[i]->getIndice()] = { 0 , tableau[plusPetitSommet][1] + tab_arrete[i]->getPoids(), plusPetitSommet };
                    std::cout << "sommets decouvert" << m_adjacent[i]->getIndice() << '\n';
                }
            }
        }
    }
}
