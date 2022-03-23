//
// Created by Mathéo Auer on 16/03/2022.
//

#include "tuiles.h"
namespace MMaze{
    MMaze::Tuiles::Tuiles(int x, int y): vec_sites(4*4), vec_murs(4*4) {
        this->x = x;
        this->y = y;
        std::fill(vec_murs.begin(), vec_murs.end(), true); //Fill all the walls
    }

    void Tuiles::setType(unsigned int ligne, unsigned int colonne, Type type) {
        int index = getIndex(ligne, colonne);
        vec_sites[index].type = type;
    }
    /**
     *  Calcul l'index basé sur la ligne et colonne donné
     * @param ligne compris entre 0 et 3 inclus
     * @param colonne compris entre 0 et 3 inclus
     * @return index 0-15
     */
    int Tuiles::getIndex(unsigned int ligne, unsigned int colonne) {
        assert(ligne >= 0 && ligne <= 3);
        assert(colonne >= 0 && colonne <= 3);
        int index = ((ligne)*4)+(colonne);
        return index;
    }
}

