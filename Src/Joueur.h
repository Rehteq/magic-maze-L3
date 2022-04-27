//
// Created by Mathéo Auer on 27/04/2022.
//

#ifndef SRC_JOUEUR_H
#define SRC_JOUEUR_H

#include "couleurs.hpp"
#include <vector>
#include "graphe.h"
namespace MMaze {
    class Joueur {
    public:
        Couleur couleur;
        std::vector<node *> path;
        Tuile *tuile;
        Site *site;
        Joueur(Couleur couleur);
        ~Joueur();
    };
}

#endif //SRC_JOUEUR_H
