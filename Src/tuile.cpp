//
// Created by Mathéo Auer on 16/03/2022.
//

#include "tuile.h"
namespace MMaze{
    MMaze::Tuile::Tuile(int x, int y): vec_sites(4*4), vec_murs(4*4) {
        this->x = x;
        this->y = y;
        std::fill(vec_murs.begin(), vec_murs.end(), true); //Fill all the walls
    }

    void Tuile::setType(unsigned int ligne, unsigned int colonne, Type type) {
        int index = getCaseIndex(ligne, colonne);
        vec_sites[index].type = type;
    }
    /**
     * Calcul l'index basé sur la ligne et colonne donné
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

    int Tuile::getMurIndex(Case case1, Case case2) {
        return 0;
    }

    void Tuile::setMur(Case case1, Case case2, bool isSolid) {
        int index = getMurIndex(case1, case2);
        setMur(index, isSolid);
    }

    Site Tuile::getSite(int ligne, int colonne) {
        int index = getCaseIndex(ligne, colonne);
        return getSite(index);
    }

    Site Tuile::getSite(int index) {
        return vec_sites[index];
    }

}

