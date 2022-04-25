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
        std::random_device seed;
        std::mt19937 rd(seed());
        std::uniform_int_distribution<int> rdGen(0, 3);
        for(int i = 0; i < 4; i++){
            switch(rdGen(rd)){
                case 0: tuile->setType(1,0, Type::PORTE); break;
                case 1: tuile->setType(0,2, Type::PORTE); break;
                case 2: tuile->setType(2,3, Type::PORTE); break;
            }
        }
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

    // Closing walls

    //search for missing walls
    int missingWall(Tuile *tuile, int index){
        int val[5] = {-1, -1, -1, -1, 4};
        Case c = Case(index);
        //nb of wall around a case = [4]; up = [2]; down = [0]; right = [1]; left = [3]
        if(c.ligne() == 1){
            val[2] = 1;
            val[4] += 1;
        }
        if(c.ligne() == 4){
            val[0] = 1;
            val[4] += 1;
        }
        if(c.colonne() == 1){
            val[3] = 1;
            val[4] += 1;
        }
        if(c.colonne() == 4){
            val[1] = 1;
            val[4] += 1;
        }
        for(int i = 0; i < 4; i++){
            if(val[i] != 1){
                if(tuile->isMur(c, c.voisine((Direction)i))){
                    val[4] += 1;
                    val[i] = 1;
                }
            }
        }
        if(val[4] == 3){
            for(int i = 0; i < 4; i++){
                if(val[i] == -1){
                    if(i == 2){
                        return index-4;
                    }
                    if(i == 0){
                        return index+4;
                    }
                    if(i == 3){
                        return c.ligne()+12+(4*(index-(c.ligne()*4)-1));
                    }
                    if(i == 1){
                        return c.ligne()+12+(4*(index-(c.ligne()*4)));
                    }
                }
            }
        }
        return -1;
    }

    void close(Tuile *tuile){
        int changes;
        int toClose;
        while(changes != 0){
            changes = 0;
            for(int i = 0; i < 16; i++){
                toClose = missingWall(tuile, i);
                if(toClose != -1){
                    tuile->setMur(toClose, true);
                    changes += 1;
                }
            }
        }
    }

}