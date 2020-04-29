#include "Sommet.h"

Sommet::Sommet()
{
    m_nom =' ';
    m_indice=0;
    int m_x =0;
    int m_y=0;

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
<<<<<<< Updated upstream
=======
float Sommet::getCvp()
{
    return indice_cvp;
}
void Sommet::mettre_indice_cvp(float nb)
{
     indice_cvp=nb;
}
void Sommet::mettre_indice_cvp_a_1()
{
    indice_cvp=1;
}
void Sommet::ADJ_mettre_indice_cvp_a_1()
{
    for(size_t i=0; i< m_adjacent.size(); ++i)
    {
        m_adjacent[i]->indice_cvp=1;
    }
}
int Sommet::calculer_somme_cvp_adj()
{
    int somme_cvp=0;
     for(size_t i=0; i< m_adjacent.size(); ++i)
    {
        somme_cvp=somme_cvp+m_adjacent[i]->getCvp();

    }
    return somme_cvp;
}

void Sommet::actualiserDijkstra(int plusPetitSommet, std::vector<std::vector<int>> &tableau, std::vector<Arrete*> tab_arrete)
{
    int poidsArreteI=0;
    //std::cout<<"entree dans le dijkstra Sommet"<<std::endl;
    //std::cout << "tableau[plusPetitSommet][1] : " <<tableau[plusPetitSommet][1]<< '\n';
    for( int i=0 ; i<getTabSize() ; ++i)
    {
        //si le sommet a des sucesseurs
        if(m_adjacent[i] != nullptr)
        {
            //on doit d'abord trouver les arretes correspondant aux sommets adjacents
            for(size_t j=0 ; j<tab_arrete.size() ; ++j)
            {
                //si les 2 extrmités sont trouvés pour une arrete
                if ((m_adjacent[i]->getIndice() == tab_arrete[j]->getDepart()) || (m_indice == tab_arrete[j]->getDepart()))
                {
                    if((m_adjacent[i]->getIndice() == tab_arrete[j]->getArrivee()) || (m_indice == tab_arrete[j]->getArrivee()))
                    {
                        //on enregistre le poids de l'arrete en question
                        poidsArreteI = tab_arrete[j]->getPoids();
                        //std::cout << "poidsArreteI : " <<poidsArreteI<< '\n';
                    }
                }
            }
            //si la case n'a pas été "terminée"
            if(tableau[m_adjacent[i]->getIndice()][0] != 1)
            {
                //si on a une distance plus petite que celle renseignée ou un nouveau sommet
                if((tableau[m_adjacent[i]->getIndice()][1] > tableau[plusPetitSommet][1] + poidsArreteI) || tableau[m_adjacent[i]->getIndice()][1] == -1 )
                {
                    //on met le numero, le poids et le predecesseur dans la case correspondante tableau
                    tableau[m_adjacent[i]->getIndice()] = { 0 , tableau[plusPetitSommet][1] + poidsArreteI , plusPetitSommet };
                    //std::cout << "sommets decouvert" << m_adjacent[i]->getIndice() << '\n';
                    //std::cout << "poidsArreteI dans ajout : " <<poidsArreteI<< '\n';
                }
            }
        }
    }
}

std::vector<Sommet*> Sommet::getAdj()
    {
        return m_adjacent;
    }
>>>>>>> Stashed changes
