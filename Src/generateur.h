//
// Created by Mathéo Auer on 13/04/2022.
//
#include "tuile.h"

#ifndef SRC_GENERATEUR_H
#define SRC_GENERATEUR_H

namespace MMaze {
    class Generateur {
    public :
        Generateur();

        ~Generateur();
        Tuile *genererTuile(Tuile *tuile);
    };
}

#endif //SRC_GENERATEUR_H
