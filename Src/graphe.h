//
// Created by Mathéo Auer on 25/04/2022.
//
#ifndef SRC_GRAPHE_H
#define SRC_GRAPHE_H

#pragma once
#include "case.hpp"
#include "tuile.h"
#include "site.hpp"
#include <vector>


namespace MMaze {
    struct node {
        std::vector<node *> voisins;
        Tuile *tuile;
        Site* site;
    };
    class Graphe {
    public:
        Graphe();
        ~Graphe();
        std::vector<node> noeuds;
        node * find_noeud(Tuile *t, Site *s);
        static Graphe fromTuile(Tuile *t); //Problème de référence et de dépendance circulaire
        friend std::ostream& operator<<(std::ostream& os, const Graphe& graphe);
    };
}
#endif //SRC_GRAPHE_H
