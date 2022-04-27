//
// Created by Mathéo Auer on 25/04/2022.
//

#include "graphe.h"
#include "case.hpp"
#include "mur.hpp"
#include <ostream>
#include <iostream>
#include <queue>

namespace MMaze{

    Graphe::~Graphe() {

    }

    Graphe::Graphe() {

    }

    node *Graphe::find_noeud(Tuile *t, Site *s) {
        for (int i = 0; i < noeuds.size(); ++i) {
            node *n = noeuds[i];
            if (n->tuile == t && n->site->index() == s->index()) {
                return n;
            }
        }
        return nullptr;
    }

    Graphe Graphe::fromTuile(Tuile *t) {
        Graphe g;
        for (int i = 0; i < 16; i++){
            node* n = new node(t, &t->vec_sites[i]);
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
                            g.noeuds[i]->voisins.push_back(g.noeuds[index]);
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
            node *n = graphe.noeuds[i];
            std::cout << "(Tuile : "<< n->tuile->x << ","<< n->tuile->y <<")(Case : " << n->site->index() << ") -> | ";
            for (int j = 0; j < n->voisins.size(); ++j) {
                node voisin = *n->voisins[j];
                std::cout << voisin.site->index() << ",";
            }
            std::cout << "|"<< std::endl;
        }
        return os;
    }
    //Dijkstra algorithm for finding the shortest path from a node to all the other nodes
    std::map<node *, int> Graphe::dijkstra(node src){
        struct cmp { // Comparator for the priority queue
            bool operator()(const node *a, const node *b) {
                return a->distance > b->distance;
            }
        };
        std::map<node *, int> distances;
        node *start = find_noeud(src.tuile, src.site);
        std::priority_queue<node*, std::vector<node*>, cmp> pq;

        for (int i = 0; i < noeuds.size(); ++i) {
            node *n = noeuds[i];
            n->distance = INT16_MAX;
            n->parent = nullptr;
            n->visited = false;
        }
        start->distance = 0;
        start->parent = start;
        start->visited = true;
        pq.push(start);
        while(!pq.empty()){
            node *current = pq.top();
            pq.pop();
            for (int i = 0; i < current->voisins.size(); ++i) {
                node *neighbor = current->voisins[i];
                if (!neighbor->visited) {
                    int alt = current->distance + 1;
                    if (alt < neighbor->distance) {
                        neighbor->distance = alt;
                        neighbor->parent = current;
                        pq.push(neighbor);
                    }
                }
            }
            current->visited = true;
            distances.insert(std::pair<node *, int>(current, current->distance));
        }
        return distances;
    }

    //Print all distance from map of dijkstra
    void Graphe::print_distances(node src){
        std::map<node *, int> distances = dijkstra(src);
        for(auto & it : distances) {
            std::cout << "Distance " << "("<< src.site->index() << ")->(" <<it.first->site->index() <<") : "<<it.second << std::endl;
        }
    }
}