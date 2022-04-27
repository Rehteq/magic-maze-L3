//
// Created by Mathéo Auer on 25/04/2022.
//
#ifndef SRC_GRAPHE_H
#define SRC_GRAPHE_H

#pragma once
#include "case.hpp"
#include "tuile.h"
#include "site.hpp"
#include <ostream>
#include <vector>
#include <map>


namespace MMaze {
    struct node {
        std::vector<node *> voisins;
        Tuile *tuile;
        Site* site;
        int distance;
        node *parent;
        bool visited;
        node(Tuile *t, Site* s) : voisins(std::vector<node*>()), tuile(t), site(s), distance(0), parent(nullptr), visited(false) {}
    };
    class Graphe {
    public:
        Graphe();
        ~Graphe();
        std::vector<node*> noeuds;
        node * find_noeud(Tuile *t, Site *s);
        static Graphe fromTuile(Tuile *t); //Problème de référence et de dépendance circulaire
        friend std::ostream& operator<<(std::ostream& os, const Graphe& graphe);

        std::map<node *, int> dijkstra(node src);

        void print_distances(node src);
    };
}
#endif //SRC_GRAPHE_H
