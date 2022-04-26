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
        int x; // Colonne
        int y; // Ligne
        std::vector<Site> vec_sites;
        std::vector<bool> vec_murs;
        Site * getSite(int index);
        Site * getSite(int ligne, int colonne);
        void setType(unsigned int ligne, unsigned colonne, Type type);
        void setMur(Case case1, Case case2, bool isSolid);
        void setMur(int index, bool isSolid);
        bool isMur(Case case1, Case case2);
        Tuile(int y, int x);
        int[] possiblePath(int index);
        int[] dijkstra(int index1, int index2, int[] path, int cout);

    private:
        int getCaseIndex(unsigned int ligne, unsigned colonne);
    };
}

#endif //MAGIC_MAZE_L3_TUILES_H
