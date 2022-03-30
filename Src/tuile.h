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
    class Tuile {
    public :
        int x;
        int y;
        std::vector<Site> vec_sites;
        std::vector<bool> vec_murs;
        Site getSite(int index);
        Site getSite(int ligne, int colonne);
        void setType(unsigned int ligne, unsigned colonne, Type type);
        void setMur(Case case1, Case case2, bool isSolid);
        void setMur(int index, bool isSolid);
        int getCaseCoordinate(int caseNumber);
        int getWallCoordinate(int caseNumber1, int caseNumber2);

        Tuile(int x, int y);

    private:
        int getCaseIndex(unsigned int ligne, unsigned colonne);
        int getMurIndex(Case case1, Case case2);

    };
}

#endif //MAGIC_MAZE_L3_TUILES_H
