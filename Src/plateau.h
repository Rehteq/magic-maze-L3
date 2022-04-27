//
// Created by Mathéo Auer on 30/03/2022.
//

#ifndef SRC_PLATEAU_H
#define SRC_PLATEAU_H
#include <vector>
#include "tuile.h"
#include "draw.hpp"
#include "Joueur.h"

using namespace MMaze;
class Plateau {
public:
    Plateau();
    void ajouterTuile(Tuile* t);

    Tuile * worldCoordinatesToTuile(int ligne, int colonne);
    Site * worldCoordinatesToSite(int ligne, int colonne);
    Tuile * getTuile(int y, int x);
    PadPlateau toPadPlateau();
    std::vector<Joueur*> joueurs;
    Joueur * currentPlayer;
    Joueur * getNextPlayer();
private:
    std::vector<Tuile*> vec_tuiles;
};



#endif //SRC_PLATEAU_H
