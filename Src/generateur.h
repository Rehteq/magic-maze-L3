//
// Created by Mathéo Auer on 13/04/2022.
//
#include "tuile.h"

#ifndef SRC_GENERATEUR_H
#define SRC_GENERATEUR_H

namespace MMaze {
    enum TuileType {
        TUILEDEPART,
        TUILECLASSIQUE
    };

    class Generateur {
    public :
        Generateur();

        ~Generateur();

        Tuile *genererTuile(Tuile *tuile, TuileType tuileType);

        int getRoot(int x);

        bool join(int elem1, int elem2);

        bool ajouterObjectif(Couleur c, Tuile *tuile);

        bool retirerObjectif(Site site);
        
    private:
        std::vector<bool> objectifs;
        std::vector<int> m_union;
        int missingWall(Tuile *tuile, int index, int *val);
        Tuile* initTuileDepart(Tuile *tuile);
        Tuile* initTuileClassique(Tuile *tuile);
        int * possibleDirection(Tuile *tuile, int index, int *val);
        void close(Tuile *tuile);

    };
}


#endif //SRC_GENERATEUR_H
