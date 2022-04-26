//
// Created by Mathéo Auer on 16/03/2022.
//

#include "tuile.h"
#include "mur.hpp"
#include "site.hpp"
#include <cassert>
#include <algorithm>

namespace MMaze{
    MMaze::Tuile::Tuile(int y, int x) {
        this->x = x;
        this->y = y;
        vec_murs.resize(24, true);
        for (int i = 0; i < 16; ++i) {
            vec_sites.push_back(Site(i));
        }
    }

    void Tuile::setType(unsigned int ligne, unsigned int colonne, Type type) {
        int index = getCaseIndex(ligne, colonne);
        vec_sites[index].type = type;
    }
    /**
     * Calcul l'index basé sur la x et y donné
     * @param ligne compris entre 0 et 3 inclus
     * @param colonne compris entre 0 et 3 inclus
     * @return index 0-15
     */
    int Tuile::getCaseIndex(unsigned int ligne, unsigned int colonne) {
        assert(ligne >= 0 && ligne <= 3);
        assert(colonne >= 0 && colonne <= 3);
        int index = ((ligne)*4)+(colonne);
        return index;
    }

    void Tuile::setMur(int index, bool isSolid) {
        this->vec_murs[index] = isSolid;
    }


    void Tuile::setMur(Case case1, Case case2, bool isSolid) {
        Mur mur(case1, case2);
        int index = mur.index();
        setMur(index, isSolid);
    }

    Site* Tuile::getSite(int ligne, int colonne) {
        int index = getCaseIndex(ligne, colonne);
        return getSite(index);
    }

    Site* Tuile::getSite(int index) {
        return &vec_sites[index];
    }

    bool Tuile::isMur(Case case1, Case case2) {
        Mur mur(case1, case2);
        int murIndex = mur.index();
        return this->vec_murs[murIndex];
    }

    // -1 if wall 1 if clear
    int[] possiblePath(int index){
        int val[4] = {0, 0, 0, 0};
        Case c = Case(index);
        //up = [2]; down = [0]; right = [1]; left = [3]
        if(c.ligne() == 1){
            val[2] = -1;
        }
        if(c.ligne() == 4){
            val[0] = -1;
        }
        if(c.colonne() == 1){
            val[3] = -1;
        }
        if(c.colonne() == 4){
            val[1] = -1;
        }
        for(int i = 0; i < 4; i++){
            if(val[i] == 0){
                if(!this->isMur(c, c.voisine((Direction)i))){
                    val[i] = 1;
                }else{
                    val[i] = -1;
                }
            }
        }
        return val;
    }

    int[] dijkstra(int index1, int index2, int[] path, int cout) {
        int tmp[4][16];
        int val[4] = possiblePath(index1);
        int lowest;
        Case c = Case(index1);

        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 16; j++){
                path[j] = 20; // poid a 20 qui est au dessus du possible
                tmp[i][j] = 20;
            }
        }

        for(int i = 0; i < 4; i++){
            if(val[i] == 1){
                int voisine = c.voisine((Direction)i).index();
                if(voisine == index2){
                    path[voisine] = cout;
                    return path;
                }
                if(cout > path[voisine]){
                    return path;
                }
                path[voisine] = cout;
                tmp[i] = dijkstra(voisine, index2, path, cout++);
            }
        }

        lowest = std::min(tmp[0][index2], std::min(tmp[1][index2], std::min(tmp[2][index2], tmp[3][index2])));

        for(int i = 0; i < 4; i++){
            if(tmp[i][index2] == lowest){
                return tmp[i];
            }
        }
    }
}

