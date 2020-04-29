#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"
#include "svgfile.h"

Graphe::Graphe()
{
    m_orientation = 0;
    m_ordre = 0;
    m_taille = 0;
    fichier_topologie=" ";
    fichier_ponderation=" ";

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
    int x1, y1, x2, y2;

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
    for (int y=0; y<m_nbre_arrete; y++)
    {
        lire2>>indice;

        lire2>>poids;
        m_arrete[indice]->mettre_poids(poids);
    }
}

/*
void Graphe::dessiner_graphe(std::string fichier)
{
    Svgfile svgout ;
    std::ifstream lire(fichier.c_str());
    Sommet*s ;
    int x1, y1, x2, y2 ;

    for (int i =0;i<m_ordre; i++ )
    {
        svgout.addCross(s->m_x,s->m_y,5,"red");
        svgout.addGrid() ;
    }
    for(int i=0; i<m_taille; i++)
    {
        lire >> x1 ;
        lire >> y1 ;
        lire >> x2 ;
        lire >> y2 ;
        svgout.addLine(x1,y1,x2,y2,"black");
    }
}*/


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
void Graphe::trouver_indice_centralite_vecteur_propre(int num_pour_comparer)
{
    ///pour comparaison
    std::string fichier1;
    if (num_pour_comparer==1)
    {
        //cas ou on a pas encore supprimé d'arrete

        fichier1="indice_sans_suppression.txt";

    }
    if (num_pour_comparer==2)
    {
        //cas ou on a pas encore supprimé d'arrete

        fichier1="indice_avec_suppression.txt";

    }

    std::ofstream ecrire1(fichier1.c_str());


    int c;
    float lambda;
    int somme_c_sommets=0;

    for (size_t i=0; i<m_sommet.size(); i++) //initialisation
    {
        m_sommet[i]->mettre_indice_cvp_a_1();
        m_sommet[i]->ADJ_mettre_indice_cvp_a_1();
    }

    ecrire1<<"NonNormalise"<<std::endl;

    //faire
    std::cout<<"pour l'indice de centralite du vecteur propre NON NORMALISE : "<<std::endl;
    for (size_t x=0; x<m_sommet.size(); x++) //pour le calcul de lambda
    {
        c=0;
        c=m_sommet[x]->calculer_somme_cvp_adj();
        std::cout<<"pour le sommet "<<m_sommet[x]->getIndice()<<" : "<<c<<std::endl;
        somme_c_sommets=somme_c_sommets+pow(c,2);
        ecrire1<<c<<std::endl;
    }


    lambda=pow(somme_c_sommets,0.5);//4.41

    ecrire1<<"Normalise"<<std::endl;

    float cvp=0;
    int c2;
    std::vector<float> tableau_cvp;
    std::cout<<"pour l'indice de centralite du vecteur propre NORMALISE : "<<std::endl;
    float dlambda=0;
    for (size_t j=0; j<m_sommet.size(); j++) //pour calcul cvp de chaque sommet
    {
        c2=0;
        c2=m_sommet[j]->calculer_somme_cvp_adj();
        dlambda=dlambda-c2;
        int nb_div;
        nb_div=(10)^(-2);
        if (dlambda>nb_div)
            cvp=c2/lambda;
        else
            cvp=c2;
        tableau_cvp.push_back(cvp);
        std::cout<<"pour le sommet "<<m_sommet[j]->getIndice()<<" : "<<cvp<<std::endl;
        ecrire1<<cvp<<std::endl;
    }
    for (size_t z=0; z<m_sommet.size(); z++) //pour calcul cvp de chaque sommet
    {
        m_sommet[z]->mettre_indice_cvp(tableau_cvp[z]);
    }
}
void Graphe::trouver_centralite_degres(int num_pour_comparer)
{
    std::string fichier1;
    if (num_pour_comparer==1)
    {
        //cas ou on a pas encore supprimé d'arrete

        fichier1="indice_sans_suppression.txt";

    }
    if (num_pour_comparer==2)
    {
        //cas ou on a pas encore supprimé d'arrete

        fichier1="indice_avec_suppression.txt";

    }

    std::ofstream ecire1(fichier1.c_str());


    float nb_degre;
    float deg_max=0;
    std::cout<<"indice de degre non normalise : "<<std::endl;

    ecire1<<"nonNormalise "<<std::endl;

//    if (num_pour_comparer==2)
//        { //cas ou on a pas encore supprimé d'arrete
//
//            ecire2<<"indice de degre non normalise "<<std::endl;
//        }
    for (size_t i=0; i<m_sommet.size(); i++)
    {
        nb_degre=0;
        for (size_t j=0; j<m_arrete.size(); j++)
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

        ecire1<<nb_degre<<std::endl;

//        if (num_pour_comparer==2)
//        { //cas ou on a pas encore supprimé d'arrete
//
//            ecire2<<nb_degre<<std::endl;
//        }

    }
    std::cout<<std::endl<<std::endl<<std::endl;
    std::cout<<"voici le deg max du graph : "<<deg_max<<std::endl;
    std::cout<<std::endl;

    float indice_deg=0.00;
    std::cout<<"indice normalise de degre : "<<std::endl;

    ecire1<<"Normalise "<<std::endl;

//    if (num_pour_comparer==2)
//        { //cas ou on a pas encore supprimé d'arrete
//
//            ecire2<<"indice de degre normalise "<<std::endl;
//        }
    for (size_t x=0; x<m_sommet.size(); x++)
    {
        nb_degre=0;
        for (size_t z=0; z<m_arrete.size(); z++)
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

        ecire1<<indice_deg<<std::endl;

//        if (num_pour_comparer==2)
//        { //cas ou on a pas encore supprimé d'arrete
//
//            ecire2<<indice_deg<<std::endl;
//        }
    }
}


void Graphe::supprimer_arrete()
{
    std::string supp_arrete;
    int stop=1;
    int indice_arrete_a_supp;
    std::vector<int> tab_indices_arretes;
    int nb_test;
    for (size_t j=0; j<m_arrete.size(); j++)
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

            ///rajouter blindage
            if (indice_arrete_a_supp <= m_arrete.size())
            {
                for (size_t x=0; x<tab_indices_arretes.size(); x++)
                {
                    if (tab_indices_arretes[x]==indice_arrete_a_supp)
                    {
                        nb_test++;

                        ///parcourir tableau adjacences pour enlever cette connexion
                        int g=0,k=0;
                        do
                        {
                            g++;
                        }
                        while (m_sommet[g]->getIndice()!=m_arrete[indice_arrete_a_supp]->getDepart());
                        do
                        {
                            k++;
                        }
                        while (m_sommet[k]->getIndice()!=m_arrete[indice_arrete_a_supp]->getArrivee());

                        m_sommet[g]->supprimer_adjacence(m_sommet[k]->getIndice()); ///supp  adj
                        m_sommet[k]->supprimer_adjacence(m_sommet[g]->getIndice());

                        m_arrete.erase (m_arrete.begin()+(indice_arrete_a_supp));
                    }
                    if (nb_test==0)
                    {
                        std::cout<<"cette arrete n'existe pas, veuillez recommencer"<<std::endl;
                    }

                }
            }
            else
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
    for (size_t i=0; i<m_sommet.size(); i++)
    {
        std::cout<<"i : "<<i<<std::endl;
        int nb_arrete;
        nb_arrete=0;
        for (size_t j=0; j<m_arrete.size(); j++)
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
    for (int y=0; y<m_nbre_arrete; y++)
    {
        lire2>>indice;

        lire2>>poids;
        m_arrete[indice]->mettre_poids(poids);
    }
}

int Graphe::getOrdre()
{
    return m_ordre;
}

void Graphe::centralite_de_proximite()
{
    int sommetDepart = -1;
    std::vector<std::vector<int>> resDijkstra;

    //blindage pour avoir un sommet qui existe et qui est dans le graphe
    while(sommetDepart < 0 || sommetDepart > getOrdre())
    {
        std::cout<<"Entrez le sommet de depart"<<std::endl;
        std::cin>>sommetDepart;
    }
    //recuperation du resultat de l'algo de Dijkstra
    resDijkstra = dijkstra(sommetDepart);

    //calcul de la centralité de proximité
    int numerateur = 0;
    int denominateur = 0;

    //le dénominateur est la somme des distances du point de départ
    for(unsigned int i=0 ; i < resDijkstra.size() ; ++i)
    {
        denominateur = denominateur + resDijkstra[i][1];
    }
    numerateur = getOrdre() - 1;

    std::cout << "Indice de proximite non normalise du sommet "<<sommetDepart<<" est : " << 1<<'/'<<denominateur<< '\n';
    std::cout << "Indice de proximite normalise du sommet "<<sommetDepart<<" est : " << numerateur<<'/'<<denominateur<< '\n';
}

std::vector<std::vector<int>> Graphe::dijkstra(int depart)
{
    //std::cout<< "entree dans le dijkstra graphe"<<std::endl;
    //varible comptant les sommets
    int comptSommets=0;
    int plusPetitSommet;
    //On recoit un sommet de départ
    //on cree un tableau de la taille de l'ordre du Graphe capable de stocker l'etat, le prédécesseur et le poids des sommets
    std::vector<std::vector<int>> tableau;
    //On initialise les etats des sommets a 0_infini_? comme spécifié dans le cours
    //on prendra la premiere case de la seconde dimension du vector pour stocker les etats, les distances ,et les prédecesseurs
    //on prendra 0 pour un sommet en cours de découverte et 1 pour un sommet complètement découvert
    // une valeur négative représentera une distance infinie ou une absence de prédecesseurs
    for( int i=0 ; i<m_ordre ; ++i)
    {
        tableau.push_back({0,-1,-1});
    }
    tableau[depart] = {0,0,-1};
    //le plus petit sommet est est celui de sommetDepart
    plusPetitSommet = depart;
    //on peut mettre maintenant en palce une boucle contenant la partie répétitive de l'algorithme de dijkstra
    //la boucle s'arrète quand on a exploré tous les sommets
    while(comptSommets != m_ordre)
    {
        //on cherche le sommet avec l'arrète la plus petite
        //note: a letape 1 le sommet de départ est le premier pris, son poids d'arrte etant de 0
        for( int i=0 ; i < m_ordre ; ++i)
        {
            //std::cout << "sommet numero "<<i<<" a pour valeurs \t"<<tableau[i][0]<<'\t'<<tableau[i][1]<<'\t'<<tableau[i][2] << '\n';
            if(plusPetitSommet == -1 && tableau[i][0] == 0 && tableau[i][1] > 0)
            {
                plusPetitSommet = i;
            }
            //blindage pour empecher de relire des cases par inadvertance
            if( plusPetitSommet != -1 )
            {
                //sinon on regarde si la valeur de la case i est plus petite
                //la valeur doit etre positive sinon elle est non découverte
                if((tableau[plusPetitSommet][1] > tableau[i][1]) && (tableau[i][1] > 0) && (tableau[i][0] != 1) )
                {
                    plusPetitSommet = i;
                }
            }

        }
        //std::cout << "plusPetitSommet"<<plusPetitSommet << '\n';
        tableau[plusPetitSommet][0] = 1;
        ++comptSommets;
        //on marque le sommet explore
        //on cherche les successeurs du plus sommet a la plus petite arrete
        //on va stocker dans le tableau les valeurs suivantes
        // l'etat du sommet (decouvert ou non)
        // la distance au sommet d'origine (on additione les distances avec le sommet courant)
        // le numero du sommet courant dans la case précédent
        //pour accéder aux propriétés du sommet facilement on doit faire un sous programme propre à la classe sommet
        //std::cout << "\n indice du sommet selectionne " <<plusPetitSommet<<std::endl;
        m_sommet[plusPetitSommet]->actualiserDijkstra( plusPetitSommet, tableau, m_arrete);
        plusPetitSommet = -1;

    }
    //On retourne le résultat sous forme d'un tableau
    return tableau;
}

void Graphe::mettre_fichier_topo(std::string fichier)
{
    fichier_topologie=fichier;
}
void Graphe::mettre_fichier_ponderation(std::string fichier)
{
    fichier_ponderation=fichier;
}
std::string Graphe::getFichierTopo()
{
    return fichier_topologie;
}
std::string Graphe::getFichierPonderation()
{
    return fichier_ponderation;
}

void Graphe::comparer_valeurs_indice()
{
    std::vector<float> tab_avant_supp_non_normalise;
    std::vector<float> tab_apres_supp_non_normalise;
    std::vector<float> tab_avant_supp_normalise;
    std::vector<float> tab_apres_supp_normalise;

    std::string fichier_avant = "indice_sans_suppression.txt";
    std::ifstream lire_avant(fichier_avant.c_str());

    std::string fichier_apres = "indice_avec_suppression.txt";
    std::ifstream lire_apres(fichier_apres.c_str());

    std::string ligne, ligne2;

    lire_apres>>ligne;
    lire_avant>>ligne2;

    float nombre_avant, nombre_apres;
    for (size_t i=0;i<m_sommet.size();i++)
    {
        lire_avant>>nombre_avant;
        tab_avant_supp_non_normalise.push_back(nombre_avant);

        lire_apres>>nombre_apres;
        tab_apres_supp_non_normalise.push_back(nombre_apres);
    }

    lire_apres>>ligne;
    lire_avant>>ligne2;

    for (size_t j=0;j<m_sommet.size();j++)
    {
        lire_avant>>nombre_avant;
        tab_avant_supp_normalise.push_back(nombre_avant);

        lire_apres>>nombre_apres;
        tab_apres_supp_normalise.push_back(nombre_apres);
    }
    float nombre;


    std::cout<<"DIFFERENCE INDICE NON NORMALISE"<<std::endl<<std::endl;
    for (size_t z=0;z<m_sommet.size();z++)
    {
        nombre=tab_avant_supp_non_normalise[z]-tab_apres_supp_non_normalise[z];

        std::cout<<nombre<<std::endl;

        if(tab_avant_supp_non_normalise[z]<tab_apres_supp_non_normalise[z]&&nombre!=tab_avant_supp_non_normalise[z])
            std::cout<<" ; l'indice a augmente avec la suppression"<<std::endl;
        if(tab_avant_supp_non_normalise[z]>tab_apres_supp_non_normalise[z]&&nombre!=tab_avant_supp_non_normalise[z]&&tab_apres_supp_non_normalise[z]!=0)
            std::cout<<" ; l'indice a baisse avec la suppression"<<std::endl;
        if(tab_apres_supp_non_normalise[z]==0)
            std::cout<<" ; l'indice du sommet est passe a 0 avec la suppression"<<std::endl;
        if(nombre==0)
            std::cout<<" ; l'indice est reste  pareil avec la suppression"<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<" DIFFERENCE INDICE NORMALISE   "<<std::endl<<std::endl;
    nombre=0;
    for (size_t z=0;z<m_sommet.size();z++)
    {
        nombre=tab_avant_supp_normalise[z]-tab_apres_supp_normalise[z];

        std::cout<<nombre<<std::endl;

        if(tab_avant_supp_normalise[z]<tab_apres_supp_normalise[z]&&nombre!=tab_avant_supp_normalise[z])
            std::cout<<" ; l'indice a augmente avec la suppression"<<std::endl;
        if(tab_avant_supp_normalise[z]>tab_apres_supp_normalise[z]&&nombre!=tab_avant_supp_normalise[z]&&tab_apres_supp_normalise[z]!=0)
            std::cout<<" ; l'indice a baisse avec la suppression"<<std::endl;
        if(tab_apres_supp_normalise[z]==0)
            std::cout<<" ; l'indice du sommet est passe a 0 avec la suppression"<<std::endl;
        if(nombre==0)
            std::cout<<" ;l'indice est reste  pareil avec la suppression"<<std::endl;
    }

}
