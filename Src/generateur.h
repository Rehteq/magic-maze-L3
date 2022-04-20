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

        int getRoot(int x);

        bool join(int elem1, int elem2);
    private:
        std::vector<int> m_union;
    };
}


#endif //SRC_GENERATEUR_H
