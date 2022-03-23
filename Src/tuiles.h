//
// Created by Mathéo Auer on 16/03/2022.
//

#ifndef MAGIC_MAZE_L3_TUILES_H
#define MAGIC_MAZE_L3_TUILES_H

#include <vector>
#include <array>
#include "couleurs.hpp"
#include "site.hpp"
namespace MMaze {
    class Tuiles {
    public :
        int x;
        int y;
        std::vector<Site> vec_sites;
        std::vector<bool> vec_murs;
        void setType(unsigned int ligne, unsigned colonne, Type type);
        Tuiles(int x, int y);

    private:
        int getIndex(unsigned int ligne, unsigned colonne);
    };
}

#endif //MAGIC_MAZE_L3_TUILES_H
