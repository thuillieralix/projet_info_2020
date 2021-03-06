#include "Sommet.h"
#include "Arrete.h"

Sommet::Sommet()
{
    m_nom =' ';
    m_indice=0;
    m_x =0;
    m_y=0;
    indice_cvp=0;
}
Sommet::Sommet(int indice, std::string nom,int x, int y)
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

std::string Sommet::getNom()
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
        //std::cout << "adjacent" << '\n';
        if(m_adjacent[i] != nullptr)
        {
            //std::cout << "arrete seeker" << '\n';
            //on doit d'abord trouver les arretes correspondant aux sommets adjacents
            for(unsigned int j=0 ; j<tab_arrete.size() ; ++j)
            {
                //si les 2 extrmités sont trouvés pour une arrete
                if ((m_adjacent[i]->getIndice() == tab_arrete[j]->getDepart()) || (m_indice == tab_arrete[j]->getDepart()))
                {
                    //std::cout << "arrete seeker depart" << '\n';
                    if((m_adjacent[i]->getIndice() == tab_arrete[j]->getArrivee()) || (m_indice == tab_arrete[j]->getArrivee()))
                    {
                        //std::cout << "arrete seeker arrivee" << '\n';
                        //on enregistre le poids de l'arrete en question
                        poidsArreteI = tab_arrete[j]->getPoids();
                        //std::cout << "poidsArreteI : " <<poidsArreteI<< '\n';
                    }
                }
            }
            //std::cout << "si pas termine" << '\n';
            //si la case n'a pas été "terminée"
            if(tableau[m_adjacent[i]->getIndice()][0] != 1)
            {
                //std::cout << "si plus petit" << '\n';
                //si on a une distance plus petite que celle renseignée ou un nouveau sommet
                if((tableau[m_adjacent[i]->getIndice()][1] > tableau[plusPetitSommet][1] + poidsArreteI) || tableau[m_adjacent[i]->getIndice()][1] == -1 )
                {
                    //std::cout << "ajout du sommet" << '\n';
                    //on met le numero, le poids et le predecesseur dans la case correspondante tableau
                    tableau[m_adjacent[i]->getIndice()] = { 0, tableau[plusPetitSommet][1] + poidsArreteI, plusPetitSommet };
                    //std::cout << "sommets decouvert" << m_adjacent[i]->getIndice() << '\n';
                    //std::cout << "poidsArreteI dans ajout : " <<poidsArreteI<< '\n';
                }
            }
        }
    }
}

void Sommet::supprimer_adjacence(int indice_arrivee_arrete_a_supp)
{
    for(size_t i=0; i<m_adjacent.size(); i++)
    {
        if (m_adjacent[i]->getIndice()==indice_arrivee_arrete_a_supp)
        {
            m_adjacent.erase(m_adjacent.begin()+i);
        }
    }
}


//partie du dfs propre a la classe sommet
void Sommet::parcoursDFS(std::deque<int>& pile, std::vector<int>& temoinParcours, std::deque<int>& resultat, bool silence)
{
    //recursif pour les sommets
    //passe le sommet parcouru a gris
    temoinParcours[m_indice] = 1;
    //il ajoute le sommet actuel a la pile
    pile.push_front(m_indice);
    resultat.push_back(m_indice);
    //affichage de la liste actuelle
    if(!silence)
    {
        for(unsigned int j=0 ; j<pile.size() ; ++j)
        {
            std::cout << "--" << pile[j];
        }
        std::cout<<std::endl;
    }

    //on explore les suivants si ils sont "blancs"cad non explorés
    for(unsigned int i=0 ; i<m_adjacent.size() ; ++i)
    {
        if(m_adjacent[i] != nullptr)
        {
            if(temoinParcours[m_adjacent[i]->getIndice()] == 0)
            {
                m_adjacent[i]->parcoursDFS(pile,temoinParcours,resultat,silence);
            }
        }
    }
    //passe a noir
    temoinParcours[m_indice] = 2;
    //enlève le premier element de la pile car c'est celui parcouru : il n'a plus de successeur non exploré
    pile.pop_front();
}

float Sommet::get_x()
{
    return m_x;
}
float Sommet::get_y()
{
    return m_y;
}
std::vector <Sommet*> Sommet::getAdj()
{
    return m_adjacent;
}

void Sommet::actualiserDijkstra_inter(int plusPetitSommet, std::vector<std::vector<std::vector<int>>> &tableau, std::vector<Arrete*> tab_arrete)
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
            for(unsigned int j=0 ; j<tab_arrete.size() ; ++j)
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
            if(tableau[m_adjacent[i]->getIndice()][0][0] != 1)
            {
                //si on a 2 chemins de longueur égale
                if((tableau[m_adjacent[i]->getIndice()][0][1] == tableau[plusPetitSommet][0][1] + poidsArreteI) )
                {
                    //on met le numero, le poids et le predecesseur dans la case correspondante tableau
                    tableau[m_adjacent[i]->getIndice()].push_back( { 0, tableau[plusPetitSommet][0][1] + poidsArreteI, plusPetitSommet } );
                    //std::cout << "sommets decouvert" << m_adjacent[i]->getIndice() << '\n';
                    //std::cout << "poidsArreteI dans ajout : " <<poidsArreteI<< '\n';
                }
                //si on a une distance plus petite que celle renseignée ou un nouveau sommet
                if((tableau[m_adjacent[i]->getIndice()][0][1] > tableau[plusPetitSommet][0][1] + poidsArreteI) || tableau[m_adjacent[i]->getIndice()][0][1] == -1 )
                {
                    //on met le numero, le poids et le predecesseur dans la case correspondante tableau
                    tableau[m_adjacent[i]->getIndice()][0] = { 0, tableau[plusPetitSommet][0][1] + poidsArreteI, plusPetitSommet };
                    //std::cout << "sommets decouvert" << m_adjacent[i]->getIndice() << '\n';
                    //std::cout << "poidsArreteI dans ajout : " <<poidsArreteI<< '\n';
                }

            }

        }
    }
}
