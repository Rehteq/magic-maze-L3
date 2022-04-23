//
// Created by Mathéo Auer on 30/03/2022.
//
#include <iostream>
#include "plateau.h"
#include "draw.hpp"
#include <cassert>

Site* Plateau::worldCoordinatesToSite(int ligne, int colonne) {
    Tuile* tuile = this->worldCoordinatesToTuile(ligne, colonne);
    int resteX = colonne - tuile->x*4;
    int resteY = ligne - tuile->y*4;
    return tuile->getSite(resteY,resteX);
}

Tuile* Plateau::worldCoordinatesToTuile(int ligne, int colonne) {
    int ligneTuile = ((ligne) % 4);
    int colonneTuile = ((colonne) % 4);

    std::cout << "ligneTuile : " << ligneTuile << std::endl;
    std::cout << "colonneTuile : " << colonneTuile << std::endl;
    return getTuile(ligneTuile, colonneTuile);
}

Tuile* Plateau::getTuile(int y, int x) {
    Tuile * tuile;
    for (auto & vec_tuile : vec_tuiles) {
        if (vec_tuile->x == x && vec_tuile->y == y) {
            tuile = vec_tuile;
        }
    }
    assert(tuile != nullptr); // tuile non trouvée
    return tuile;
}

void Plateau::ajouterTuile(Tuile* t) {
    vec_tuiles.push_back(t);
}

Plateau::Plateau() {

}

PadPlateau Plateau::toPadPlateau() {

    PadPlateau padPlateau;
    for (int i = 0; i < vec_tuiles.size(); ++i) {
        Tuile* tuile = vec_tuiles[i];
        padPlateau.ajouter_tuile(tuile->y, tuile->x);
        for (int j = 0; j < tuile->vec_murs.size(); ++j) {
            Mur mur(j);
            padPlateau.ajouter_mur(tuile->y,tuile->x,mur, tuile->vec_murs[j]);
        }
        for (int j = 0; j < tuile->vec_sites.size(); ++j) {
            Site site = tuile->vec_sites[j];
            padPlateau.ajouter_site(tuile->y,tuile->x, site);
        }
        
    }
    return padPlateau;
}
