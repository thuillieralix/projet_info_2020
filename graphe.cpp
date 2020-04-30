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
        sommet_x=sommet_x*100;
        sommet_y=sommet_y*100;
        Sommet* s = new Sommet(m_indice, m_nom,sommet_x,sommet_y);
        m_sommet.push_back(s);


    }
    lire >> m_taille;
    int indice, extremite_dep, extremite_ar;
    int x1, y1, x2, y2;
    int ymax=0,xmax=0;
    for (size_t g=0;g<m_sommet.size();g++)
    {
        if (m_sommet[g]->get_x()>xmax)
        {
            xmax=m_sommet[g]->get_x();
        }
        if (m_sommet[g]->get_y()>ymax)
        {
            ymax=m_sommet[g]->get_y();
        }
    }
    int agrandireX, agrandireY;
    agrandireX=900/xmax;
    agrandireY=800/ymax;
    std::string tmp;
    for (size_t d=0; d<m_sommet.size();d++)
    {
        svgout.addDisk(m_sommet[d]->get_x()*agrandireX-50,m_sommet[d]->get_y()*agrandireY-50,5,"red");

        tmp=m_sommet[d]->getNom();
        svgout.addText(m_sommet[d]->get_x()*agrandireX -35, m_sommet[d]->get_y()*agrandireY-35, tmp, "black");
        svgout.addGrid() ;
    }
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
        //svgout.addLine(x1,y1,x2,y2,"black");
        svgout.addLine(m_sommet[extremite_dep]->get_x()*agrandireX-50,m_sommet[extremite_dep]->get_y()*agrandireY-50
                       ,m_sommet[extremite_ar]->get_x()*agrandireX-50,m_sommet[extremite_ar]->get_y()*agrandireY-50,"black");
        int x_poids, y_poids;
        int x_ar=(m_sommet[extremite_ar]->get_x()*agrandireX-50);
        int y_ar =(m_sommet[extremite_ar]->get_y()*agrandireY-50);
        int x_dep=(m_sommet[extremite_dep]->get_x()*agrandireX-50);
        int y_dep=(m_sommet[extremite_dep]->get_y()*agrandireY-50);
        x_poids=x_dep+(x_ar-x_dep)/2;
        y_poids=y_dep+(y_ar-y_dep)/2-20;
        svgout.addText(x_poids, y_poids, indice, "blue");
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
        dlambda=c2-dlambda;
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

void Graphe::centralite_de_proximite(int numero)
{
    std::string fichier1;
    if (numero==1)
    {
        //cas ou on a pas encore supprimé d'arrete

        fichier1="indice_sans_suppression.txt";

    }
    if (numero==2)
    {
        //cas ou on a pas encore supprimé d'arrete

        fichier1="indice_avec_suppression.txt";

    }

    std::ofstream ecrire1(fichier1.c_str());



    int sommetDepart = -1;
    std::vector<std::vector<int>> resDijkstra;
    std::vector<float> tab_indice_prox_NON_NORMALISE;
    std::vector<float> tab_indice_prox_NORMALISE;
    for (size_t y=0;y<m_sommet.size();y++)
    {
            sommetDepart=m_sommet[y]->getIndice();
            resDijkstra = dijkstra(sommetDepart);
            //std::cout << "sortie du dijkstra" << '\n';
            float numerateur = 0;
            float denominateur = 0;
            std::deque<int> resultat;

            dfspath(sommetDepart, resultat,1);

            for(unsigned int i=0 ; i < resDijkstra.size() ; ++i)
            {
                if(resDijkstra[i][1] > 0)
                {denominateur = denominateur + resDijkstra[i][1];}
            }
            numerateur = resultat.size() - 1;
            float nb, nb2;
            if(denominateur > 0)
            {
                nb=1/denominateur;
                        }
            //std::cout << "Indice de proximite non normalise du sommet "<<sommetDepart<<" est : " <<nb<< '\n';
            tab_indice_prox_NON_NORMALISE.push_back(nb);
            nb2=numerateur/denominateur;
            //std::cout << "Indice de proximite normalise du sommet "<<sommetDepart<<" est : " << nb2<< '\n';
            tab_indice_prox_NORMALISE.push_back(nb2);
    }

        ecrire1<<"NonNormalise "<<std::endl;
        std::cout<<"affichage indice prox non normalise"<<std::endl;
        for (size_t y=0;y<m_sommet.size();y++)
        {
            std::cout<<"pour le sommet "<<y<<" : "<<tab_indice_prox_NON_NORMALISE[y]<<std::endl;
            ecrire1<<tab_indice_prox_NON_NORMALISE[y]<<std::endl;
        }
        ecrire1<<"Normalise "<<std::endl;
        std::cout<<"affichage indice prox normalise"<<std::endl;
        for (size_t z=0;z<m_sommet.size();z++)
        {
            std::cout<<"pour le sommet "<<z<<" : "<<tab_indice_prox_NORMALISE[z]<<std::endl;
            ecrire1<<tab_indice_prox_NORMALISE[z]<<std::endl;
        }
    if (numero==3)
    {
            Svgfile svgout;
            svgout.addGrid() ;
            int ymax=0,xmax=0;
            for (size_t g=0;g<m_sommet.size();g++)
            {
                if (m_sommet[g]->get_x()>xmax)
                {
                    xmax=m_sommet[g]->get_x();
                }
                if (m_sommet[g]->get_y()>ymax)
                {
                    ymax=m_sommet[g]->get_y();
                }
            }
            int agrandireX, agrandireY;
            agrandireX=900/xmax;
            agrandireY=800/ymax;
            std::string tmp;
            ///on dessine dans svgout
             float max1=0, max2=0,max3=0;
             std::cout<<"size tab : "<<tab_indice_prox_NORMALISE.size()<<std::endl;
             for (size_t m=0;m<tab_indice_prox_NORMALISE.size();m++)
             {
                 std::cout<< "voici le tab indice de degré indice "<<m<<" valeur : "<<tab_indice_prox_NORMALISE[m]<<std::endl;
             }

            for (size_t i=0;i<tab_indice_prox_NORMALISE.size();i++)
            {
                if (tab_indice_prox_NORMALISE[i]>max3)
                {
                    max1=max2;
                    max2=max3;
                    max3=tab_indice_prox_NORMALISE[i];
                    std::cout<<"1"<<std::endl;
                }
                else if (tab_indice_prox_NORMALISE[i]<max3&&tab_indice_prox_NORMALISE[i]>max2)
                {
                    max1=max2;
                    //std::swap(max1,max2);
                    max2=tab_indice_prox_NORMALISE[i];
                     std::cout<<"2"<<std::endl;
                }
                else if (tab_indice_prox_NORMALISE[i]<max2&&tab_indice_prox_NORMALISE[i]>max1)
                {
                    max1=tab_indice_prox_NORMALISE[i];
                     std::cout<<"3"<<std::endl;
                }
            }
            std::cout<<"max3 final : "<<max3<<std::endl;
            std::cout<<"max2 final : "<<max2<<std::endl;
            std::cout<<"max1 final : "<<max1<<std::endl;
            std::cout<<"size tableau : "<<tab_indice_prox_NORMALISE.size()<<std::endl;

            for (size_t r=0;r<tab_indice_prox_NORMALISE.size();r++)
            {
                std::cout<<"pour le sommet "<<r<<" indice prox = "<<tab_indice_prox_NORMALISE[r]<<std::endl;
            }

            for(size_t h=0;h<tab_indice_prox_NORMALISE.size();h++)
            {
                if(tab_indice_prox_NORMALISE[h]==max3) //plus haut indice
                {
                    std::cout<<" 1 sommet d'indice egal à max3 "<<std::endl;
                    svgout.addDisk(m_sommet[h]->get_x()*agrandireX-50,m_sommet[h]->get_y()*agrandireY-50,15,"red");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -15, m_sommet[h]->get_y()*agrandireY-15, "indProx = ", "black");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -5, m_sommet[h]->get_y()*agrandireY,max3, "black");
                }
                else if(tab_indice_prox_NORMALISE[h]==max2)
                {
                    std::cout<<" 1 sommet d'indice egal à max2 "<<std::endl;
                    svgout.addDisk(m_sommet[h]->get_x()*agrandireX-50,m_sommet[h]->get_y()*agrandireY-50,15,"orange");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -15, m_sommet[h]->get_y()*agrandireY-15, "indProx = ", "black");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -5, m_sommet[h]->get_y()*agrandireY,max2, "black");
                }
                else if(tab_indice_prox_NORMALISE[h]==max1)//3e plus haut indice
                {
                    std::cout<<" 1 sommet d'indice egal à max1 "<<std::endl;
                    svgout.addDisk(m_sommet[h]->get_x()*agrandireX-50,m_sommet[h]->get_y()*agrandireY-50,15,"yellow");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -15, m_sommet[h]->get_y()*agrandireY-15, "indProx = ", "black");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -5, m_sommet[h]->get_y()*agrandireY,max1, "black");
                }
                else
                {
                    std::cout<<" ELSE : 1 sommet d'indice inferieur "<<std::endl;
                    svgout.addDisk(m_sommet[h]->get_x()*agrandireX-50,m_sommet[h]->get_y()*agrandireY-50,5,"black");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -15, m_sommet[h]->get_y()*agrandireY-15, "indProx = ", "black");
                    svgout.addText(m_sommet[h]->get_x()*agrandireX -5, m_sommet[h]->get_y()*agrandireY,tab_indice_prox_NORMALISE[h], "black");
                }
            }

            for (size_t d=0; d<m_sommet.size();d++)
            {
                //svgout.addDisk(m_sommet[d]->get_x()*agrandireX-50,m_sommet[d]->get_y()*agrandireY-50,5,"red");

                tmp=m_sommet[d]->getNom();
                svgout.addText(m_sommet[d]->get_x()*agrandireX -35, m_sommet[d]->get_y()*agrandireY-35, tmp, "black");

            }
            int extremite_dep,extremite_ar,indice;
            for(int i=0; i<m_taille; i++)
            {
                extremite_dep=m_arrete[i]->getDepart();
                extremite_ar=m_arrete[i]->getArrivee();
                indice =m_arrete[i]->getIndice();

                svgout.addLine(m_sommet[extremite_dep]->get_x()*agrandireX-50,m_sommet[extremite_dep]->get_y()*agrandireY-50
                               ,m_sommet[extremite_ar]->get_x()*agrandireX-50,m_sommet[extremite_ar]->get_y()*agrandireY-50,"black");
                int x_poids, y_poids;
                int x_ar=(m_sommet[extremite_ar]->get_x()*agrandireX-50);
                int y_ar =(m_sommet[extremite_ar]->get_y()*agrandireY-50);
                int x_dep=(m_sommet[extremite_dep]->get_x()*agrandireX-50);
                int y_dep=(m_sommet[extremite_dep]->get_y()*agrandireY-50);
                x_poids=x_dep+(x_ar-x_dep)/2;
                y_poids=y_dep+(y_ar-y_dep)/2-20;
                svgout.addText(x_poids, y_poids, indice, "blue");

            }

    }

}

std::vector<std::vector<int>> Graphe::dijkstra(int depart)
{
    //std::cout<< "entree dans le dijkstra graphe"<<std::endl;
    //varible comptant les sommets
    int comptSommets=0;
    int plusPetitSommet;
    bool sortie = false;
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
    while(!sortie)
    {
        //std::cout << "top boucle" << '\n';
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
                //std::cout << "plus petit sommet =/ 1" << '\n';
                //sinon on regarde si la valeur de la case i est plus petite
                //la valeur doit etre positive sinon elle est non découverte
                if((tableau[plusPetitSommet][1] > tableau[i][1]) && (tableau[i][1] > 0) && (tableau[i][0] != 1) )
                {
                    plusPetitSommet = i;
                }
            }

        }
        //std::cout << "plusPetitSommet"<<plusPetitSommet << '\n';
        if(plusPetitSommet != -1)
        {
            tableau[plusPetitSommet][0] = 1;
            ++comptSommets;
            //on marque le sommet explore
            //on cherche les successeurs du plus sommet a la plus petite arrete
            //on va stocker dans le tableau les valeurs suivantes
            // l'etat du sommet (decouvert ou non)
            // la distance au sommet d'origine (on additione les distances avec le sommet courant)
            // le numero du sommet courant dans la case précédent
            //pour accéder aux propriétés du sommet facilement on doit faire un sous programme propre à la classe sommet
            m_sommet[plusPetitSommet]->actualiserDijkstra( plusPetitSommet, tableau, m_arrete);
        }
        if(plusPetitSommet == -1)
        {
            sortie = true;
        }


        //std::cout << "\n indice du sommet selectionne " <<plusPetitSommet<<std::endl;

        plusPetitSommet = -1;

    }
    //std::cout << "fin du Dijkstra" << '\n';
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

///sert a avoir toutes les composantes connexes d'un graphe
void Graphe::composantesConnexe()
{
    std::cout<<"\n recherche de composantes connexes"<<std::endl;
    int compteur = 0, nbr_composantes = 0, variable = 0;
    std::vector<bool> temoinParcours;
    std::deque<int> resultat;
    //cree les cases du tableau temoin qui est initialisé à 0
    for(unsigned int i = 0; i < m_sommet.size(); ++i)
    {
        temoinParcours.push_back(0);
    }
    //tant qu'on a pas visité tous les sommets
    while(compteur < m_sommet.size())
    {
        //on effectue un parcours a partir d'un sommet non parcouru
        while(temoinParcours[variable] != 0)
        {
            ++variable;
        }
        //on parcours la composante connexe
        dfspath(variable, resultat,1);
        //on incremente le nombre de composantes connexes
        ++nbr_composantes;
        //on affiche la composante connexe
        std::cout<<"\n\t composante connexe numero "<<nbr_composantes<<" : "<<std::endl;
        //on affiche la composante
        for(unsigned int k=0 ; k<resultat.size() ; ++k)
        {
            std::cout<<"--"<<resultat[k];
            //on en profite pour actualiser le tableau de temoinParcours
            temoinParcours[resultat[k]] = 1;
        }
        //on regarde si on a tout vu
        compteur = compteur + resultat.size();
        //on nettoie la pile
        resultat.clear();
        std::cout<<std::endl;
    }
    std::cout<<"il y a "<<nbr_composantes<<" composantes connexes dans le graphe "<<std::endl;
}

//dfs fonctionnel aussi utilise pour les composantes connexes
void Graphe::dfspath(int sommet_number, std::deque<int>& resultat, bool silence)
{
    //std::cout<<"Debut du parcours a partir du sommet "<< sommet_number<<std::endl;
    std::vector<int> temoinParcours;
    ///IMPORTANT on doit utiliser deque car sinon on ne peut pas faire l'affichage demandé (pas d'accès a toutes les cases a tout moment)
    std::deque<int> pile;
    //cree les cases du tableau temoin qui est initialisé à 0
    for(unsigned int i = 0; i < m_sommet.size(); ++i)
    {
        temoinParcours.push_back(0);
    }
    //met le sommet actuel a gris
    temoinParcours[sommet_number] = 1;
    ///appel de la fonction dfs récursive
    m_sommet[sommet_number]->parcoursDFS(pile , temoinParcours,resultat,silence);
}
