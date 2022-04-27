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

    void Tuile::rotateTuile(int rotation){
        std::vector<bool> vec_murs_tmp;
        vec_murs_tmp.reserve(24);
        for (int i = 0; i < vec_murs.size(); ++i) {
            Mur m(i);
            bool isSolid = vec_murs[i];
            Mur tmp_mur = m.tourne(rotation);
            vec_murs_tmp[tmp_mur.index()] = isSolid;
        }
        //vec_murs = vec_murs_tmp;
        for (int i = 0; i < vec_murs.size(); ++i) {
            vec_murs[i] = vec_murs_tmp[i];
        }

        std::vector<Site> vec_sites_tmp;
        vec_sites_tmp.reserve(vec_sites.size());
        for (int i = 0; i < vec_sites.size(); ++i) {
            Site s = vec_sites[i];
            Site tmp_site(s.tourne(rotation).index());
            tmp_site.couleur = s.couleur;
            tmp_site.type = s.type;
            vec_sites_tmp[tmp_site.index()] = tmp_site;
        }
        //vec_sites = vec_sites_tmp;
        for (int i = 0; i < vec_sites.size(); ++i) {
            vec_sites[i] = vec_sites_tmp[i];
        }
    }


}

