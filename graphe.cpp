#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"

Graphe::Graphe()
{
    m_orientation = 0;
    m_ordre = 0;
    m_taille = 0;
}

Graphe::Graphe(std::string fichier, std::string fichier2)
{
    std::ifstream lire(fichier.c_str());

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
    }
    lire >> m_taille;
    int indice, extremite_dep, extremite_ar;


    for(int i=0; i<m_taille; i++)
    {
        lire >> indice;
        lire >> extremite_dep;
        lire >> extremite_ar;

        ///faire adjacence
        Arrete* a=new Arrete(extremite_dep,extremite_ar,indice);
        m_arrete.push_back(a);
        m_sommet[extremite_dep]->Ajouter_adj(m_sommet[extremite_ar]);
        m_sommet[extremite_ar]->Ajouter_adj(m_sommet[extremite_dep]);
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
void Graphe::trouver_indice_centralite_vecteur_propre()
{
    int c;
    float lambda;
    int somme_c_sommets=0;

    for (size_t i=0;i<m_sommet.size();i++)//initialisation
    {
        m_sommet[i]->mettre_indice_cvp_a_1();
        m_sommet[i]->ADJ_mettre_indice_cvp_a_1();
    }


    //faire
        std::cout<<"pour l'indice de centralite du vecteur propre NON NORMALISE : "<<std::endl;
    for (size_t x=0;x<m_sommet.size();x++)//pour le calcul de lambda
    {
        c=0;
        c=m_sommet[x]->calculer_somme_cvp_adj();
        std::cout<<"pour le sommet "<<m_sommet[x]->getIndice()<<" : "<<c<<std::endl;
        somme_c_sommets=somme_c_sommets+pow(c,2);
    }


    lambda=pow(somme_c_sommets,0.5);//4.41
    std::cout<<" lambda "<<" : "<<lambda<<std::endl;


    float cvp=0;
    int c2;
    std::vector<float> tableau_cvp;
    std::cout<<"pour l'indice de centralite du vecteur propre NORMALISE : "<<std::endl;
    for (size_t j=0;j<m_sommet.size();j++)//pour calcul cvp de chaque sommet
    {
        c2=0;
        c2=m_sommet[j]->calculer_somme_cvp_adj();
        cvp=c2/lambda;
        tableau_cvp.push_back(cvp);
        std::cout<<"pour le sommet "<<m_sommet[j]->getIndice()<<" : "<<cvp<<std::endl;
    }
    for (size_t z=0;z<m_sommet.size();z++)//pour calcul cvp de chaque sommet
    {
       m_sommet[z]->mettre_indice_cvp(tableau_cvp[z]);
    }
    
}
void Graphe::trouver_centralite_degres()
{
    float nb_degre;
    float deg_max=0;
    std::cout<<"indice de degre non normalise : "<<std::endl;
    for (size_t i=0; i<m_sommet.size();i++)
    {
        nb_degre=0;
        for (size_t j=0;j<m_arrete.size();j++)
        {
            if (m_arrete[j]->getDepart()==m_sommet[i]->getIndice())
            {
                nb_degre++;
            }
            if (m_arrete[j]->getArrivee()==m_sommet[i]->getIndice())
            {
                nb_degre++;
            }
        }
        if (nb_degre>deg_max)
        {
            deg_max=nb_degre;
        }
        std::cout<<"pour le sommet "<<m_sommet[i]->getIndice()<<" : "<<nb_degre<<std::endl;
    }
    std::cout<<std::endl<<std::endl<<std::endl;
    std::cout<<"voici le deg max du graph : "<<deg_max<<std::endl;
    std::cout<<std::endl;

    float indice_deg=0.00;
    std::cout<<"indice normalise de degre : "<<std::endl;
    for (size_t x=0;x<m_sommet.size();x++)
    {
        nb_degre=0;
        for (size_t z=0;z<m_arrete.size();z++)
        {
            if (m_arrete[z]->getDepart()==m_sommet[x]->getIndice())
            {
                nb_degre++;
            }
            if (m_arrete[z]->getArrivee()==m_sommet[x]->getIndice())
            {
                nb_degre++;
            }
        }
        indice_deg=nb_degre/deg_max;
        std::cout<<"pour le sommet "<<m_sommet[x]->getIndice()<<" : "<<indice_deg<<std::endl;
    }

}
void Graphe::supprimer_arrete()
{
    std::string supp_arrete;
    int stop=1;
    int indice_arrete_a_supp;
    std::vector<int> tab_indices_arretes;
    int nb_test;
    for (size_t j=0;j<m_arrete.size();j++)
        {
            tab_indices_arretes.push_back(m_arrete[j]->getIndice());
        }
    while (stop!=0)
    {
            std::cout<<"voulez vous supprimer une arrete ?"<<std::endl;
            std::cin>>supp_arrete;


            if (supp_arrete=="oui")
            {
                std::cout<<"quelle arrete ? mettre indice"<<std::endl;
                std::cin>>indice_arrete_a_supp;

                ///blindage
                for (size_t x=0; x<tab_indices_arretes.size();x++)
                {
                    if (tab_indices_arretes[x]==indice_arrete_a_supp)
                    {
                        m_arrete.erase (m_arrete.begin()+(indice_arrete_a_supp));
                        nb_test++;
                    }
                }
                if (nb_test==0)
                {
                    std::cout<<"cette arrete n'existe pas, veuillez recommencer"<<std::endl;
                }
            }
            else if (supp_arrete=="non")///si c'est non
            {
                stop=0;
            }
            else
            {
                std::cout<<"saisie incorrecte, veuillez recommencer"<<std::endl;
            }
    }
}


void Graphe::tester_connexite()
{
    ///graphe connexe si pour chaque sommet, il y a une arrete
    int connexe_test=1;
    for (size_t i=0;i<m_sommet.size();i++)
    {
        std::cout<<"i : "<<i<<std::endl;
        int nb_arrete;
        nb_arrete=0;
        for (size_t j=0;j<m_arrete.size();j++)
        {

            if (m_arrete[j]->getDepart()==m_sommet[i]->getIndice()||m_arrete[j]->getArrivee()==m_sommet[i]->getIndice())
            {
                nb_arrete++;
            }
        }
        if(nb_arrete==0)
        {
            std::cout<<"le graphe n'est pas connexe"<<std::endl<<std::endl;
            connexe_test=0;
            break;

        }
    }
    if(connexe_test==1)
        std::cout<<"le graphe est connexe"<<std::endl;
}
void Graphe::charger_nouveau_fichier_ponderation(std::string fichier)
{
    std::ifstream lire2(fichier.c_str());
    int m_nbre_arrete, poids, indice;

    lire2>>m_nbre_arrete;
    for (int y=0; y<m_nbre_arrete;y++)
    {
        lire2>>indice;

        lire2>>poids;
        m_arrete[indice]->mettre_poids(poids);
    }
}