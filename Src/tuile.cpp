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

    int getCaseCoordinate(int caseNumber){
        int j = 0;
        for(int i = 0; i < caseNumber; i+=4){
            j++;
        }
        return j;
    }

    int getWallCoordinate(int caseNumber1, int caseNumber2){
        if(caseNumber1 == caseNumber2 
            || caseNumber1 < 0 
            || caseNumber2 < 0 
            || caseNumber1 > 15 
            || caseNumber2 > 15
        ){
            return -1;
        }
        int lineC1 = getCaseCoordinate(caseNumber1);
        int lineC2 = getCaseCoordinate(caseNumber2);
        if(lineC1 == lineC2){
            int diff = caseNumber1 - caseNumber2;
            if(diff*diff != 1){
                return -1;
            }
            else{
                if(caseNumber1 < caseNumber2){
                    return 12+lineC1+(caseNumber1*4);
                }
                if(caseNumber2 < caseNumber1){
                    return 12+lineC1+((caseNumber1-1)*4);
                }
            }
        }
        if(lineC1!=lineC2){
            if(caseNumber1 == caseNumber2-4 || caseNumber1 == caseNumber2+4){
                return (caseNumber1<caseNumber2) ? caseNumber1 : caseNumber2;
            }
            else{
                return -1;
            }
        }
    }

}

