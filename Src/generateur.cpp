//
// Created by Mathéo Auer on 13/04/2022.
//

#include "generateur.h"
#include "mur.hpp"
#include "melangeur.hpp"
#include <algorithm>
#include <cassert>
#include <random>
#include <chrono>

namespace MMaze {

    Tuile* Generateur::genererTuile(MMaze::Tuile *tuile) {

        //tuile->setType(1,0, Type::PORTE);
        //tuile->setType(0,2, Type::PORTE);
        tuile->setType(2,3, Type::PORTE);
        tuile->setType(3,1, Type::PORTE);

        //Reset the union of the Tuile
        m_union = std::vector<int>(); 
        for (int i = 0; i < 16; ++i) {
            m_union.push_back(i);
        }

        //Get list of all interesting sites
        std::vector<Site> sites = std::vector<Site>();
        for (auto & vec_site : tuile->vec_sites) {
            if (vec_site.type != Type::AUCUN) {
                sites.push_back(vec_site);
            }
        }

        Melangeur<int> mel;
        for (int i = 0; i < 24; ++i) {
            mel.inserer(i);
        }

        for (int i = 0; i < 24; ++i){
            bool isAllConnected = true;
            int elem = mel.retirer();
            for (int j = 0; j < sites.size()-1; ++j) {
                if (getRoot(sites[j].index()) != getRoot(sites[j + 1].index())) {
                    isAllConnected = false;
                    break;
                }
            }
            if (!isAllConnected) {
                Mur mur(elem);
                tuile->vec_murs[mur.index()] = false;
                join(mur[0].index(), mur[1].index());
            }
        }
        return tuile;
    }

    Generateur::~Generateur() {

    }

    Generateur::Generateur() {

    }

    int Generateur::getRoot(int x){
        int i = x;
        while (m_union[i] != i) {
            i = m_union[i];
        }
        return i;
    }
    bool Generateur::join(int elem1, int elem2) {
        int root1 = getRoot(elem1);
        int root2 = getRoot(elem2);
        //std::cout << "Elem 1 : " << elem1 << ", Elem 2 : "<< elem2 << std::endl;
        //std::cout << "Root 1 : " << root1 << ", Root 2 : "<< root2 << std::endl;
        m_union[root1] = root2;
        return true;
    }

}