# projet_info_2020

#include "Sommet.h"

Sommet::Sommet()
{
    m_nom =' ';
    m_indice=0;
    int m_x =0;
    int m_y=0;
    indice_cvp=0;
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


