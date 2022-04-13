//
// Created by Mathéo Auer on 30/03/2022.
//
#include <iostream>
#include "plateau.h"

Site* Plateau::worldCoordinatesToSite(int ligne, int colonne) {
    Tuile* tuile = this->worldCoordinatesToTuile(ligne, colonne);

    return nullptr;
}

Tuile* Plateau::worldCoordinatesToTuile(int ligne, int colonne) {
    int ligneTuile = ((ligne) % 4);
    int colonneTuile = ((colonne) % 4);

    std::cout << "ligneTuile : " << ligneTuile << std::endl;
    std::cout << "colonneTuile : " << colonneTuile << std::endl;
    return getTuile(ligneTuile, colonneTuile);
}

Tuile* Plateau::getTuile(int y, int x) {
    for (auto & vec_tuile : vec_tuiles) {
        if (vec_tuile->x == x && vec_tuile->y == y) {
            return vec_tuile;
        }
    }
    return nullptr;
}

void Plateau::ajouterTuile(Tuile* t) {
    vec_tuiles.push_back(t);
}

Plateau::Plateau() {

}
