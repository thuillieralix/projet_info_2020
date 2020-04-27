#include "Arrete.h"

Arrete::Arrete(int depart,int arrivee,int indice)
{
    m_depart=depart;
    m_arrivee=arrivee;
    m_indice=indice;
    m_poids=0;
}

Arrete::~Arrete()
{

}
int Arrete::getDepart()
{
    return m_depart;
}
int Arrete::getArrivee()
{
    return m_arrivee;
}
int Arrete::getIndice()
{
    return m_indice;
}
int Arrete::getPoids()
{
    return m_poids;
}

void Arrete::mettre_poids(int poids)
{

    m_poids = poids;
}
