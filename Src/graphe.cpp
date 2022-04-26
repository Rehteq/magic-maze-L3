//
// Created by Mathéo Auer on 25/04/2022.
//

#include "graphe.h"
#include "case.hpp"
#include "mur.hpp"
#include <ostream>
#include <iostream>

namespace MMaze{

    Graphe::~Graphe() {

    }

    Graphe::Graphe() {

    }

    node *Graphe::find_noeud(Tuile *t, Site *s) {
        for (int i = 0; i < noeuds.size(); ++i) {
            node n = noeuds[i];
            if (n.tuile == t && n.site == s) {
                return &noeuds[i];
            }
        }
        return nullptr;
    }

    Graphe Graphe::fromTuile(Tuile *t) {
        Graphe g;
        for (int i = 0; i < 16; i++){
            node n;
            n.site = &t->vec_sites[i];
            n.tuile = t;
            n.voisins = std::vector<node*>();
            g.noeuds.push_back(n);
        }

        //Ajout des voisins en style de croix,
        //Le même style que les tours au échec puisque c'est considéré comme un seul mouvement
        for (int i = 0; i < 16; ++i) {
            Site s = t->vec_sites[i];
            for (int j = 0; j < 4; ++j) {
                Direction d = (Direction)j;
                bool isWalled = false;
                Case c(s.index());
                while(!isWalled){
                    try{
                        Case voisin = c.voisine(d);
                        int index = voisin.index();
                        Mur m = Mur(c, voisin);
                        isWalled = t->vec_murs[m.index()];
                        if (!isWalled) {
                            g.noeuds[i].voisins.push_back(&g.noeuds[index]);
                        }
                        c = voisin;
                    }
                    catch(...){
                        break;
                        //std::cout << "erreur" << std::endl;
                    }
                }
            }
        }

        return g;
    }

    std::ostream& operator<<(std::ostream &os, const Graphe &graphe) {
        for (int i = 0; i < graphe.noeuds.size(); ++i) {
            node n = graphe.noeuds[i];
            std::cout << "(Tuile : "<< n.tuile->x << ","<< n.tuile->y <<")(Case : " << n.site->index() << ") -> | ";
            for (int j = 0; j < n.voisins.size(); ++j) {
                node voisin = *n.voisins[j];
                std::cout << voisin.site->index() << ",";
            }

            std::cout << "|"<< std::endl;
        }
        return os;
    }
}