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
#include <iostream>

namespace MMaze {

    Tuile* Generateur::genererTuile(MMaze::Tuile *tuile, TuileType tuileType) {

        switch (tuileType) {
            case TuileType::TUILECLASSIQUE :
                initTuileClassique(tuile);
                break;
            case TuileType::TUILEDEPART :
                initTuileDepart(tuile);
                break;
        }

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

        close(tuile);
        return tuile;
    }

    Tuile* Generateur::initTuileDepart(MMaze::Tuile *tuile) {
        std::random_device seed;
        std::mt19937 rd(seed());
        std::uniform_int_distribution<int> rdGen(1, 4);
        Melangeur<Couleur> couleurs;
        for (int i = 1; i <= 4; ++i) {
            couleurs.inserer((Couleur)i);
        }
        tuile->setType(1,0, Type::PORTE);
        tuile->getSite(1,0)->couleur = couleurs.retirer();
        tuile->setType(0,2, Type::PORTE);
        tuile->getSite(0,2)->couleur = couleurs.retirer();
        tuile->setType(2,3, Type::PORTE);
        tuile->getSite(2,3)->couleur = couleurs.retirer();
        tuile->setType(3,1, Type::PORTE);
        tuile->getSite(3,1)->couleur = couleurs.retirer();
        m_union = std::vector<int>();
        for (int i = 0; i < 16; ++i) {
            m_union.push_back(i);
        }
        tuile->setType(1, 1, DEPART);
        tuile->setType(1, 2, DEPART);
        tuile->setType(2, 1, DEPART);
        tuile->setType(2, 2, DEPART);
        tuile->setMur(5, false);
        tuile->setMur(6,false);
        tuile->setMur(17, false);
        tuile->setMur(18, false);

        for (int i = 0; i < 4; ++i) {
            objectifs.push_back(false);
        }

        return tuile;
    }

    Tuile* Generateur::initTuileClassique(MMaze::Tuile *tuile) {
        std::random_device seed;
        std::mt19937 rd(seed());
        std::uniform_int_distribution<int> rdGen(0, 3);
        Melangeur<Couleur> couleurs;
        for (int i = 1; i <= 4; ++i) {
            couleurs.inserer((Couleur)i);
        }
        for(int i = 0; i < 4; i++){
            switch(rdGen(rd)){
                case 0:
                    tuile->getSite(1,0)->couleur = couleurs.retirer();
                    tuile->setType(1,0, Type::PORTE);
                    break;
                case 1:
                    tuile->getSite(0,2)->couleur = couleurs.retirer();
                    tuile->setType(0,2, Type::PORTE);
                    break;
                case 2:
                    tuile->getSite(2,3)->couleur = couleurs.retirer();
                    tuile->setType(2,3, Type::PORTE);
                    break;
            }
        }
        tuile->setType(3,1, Type::PORTE);
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
    int * Generateur::possibleDirection(Tuile *tuile, int index, int *val){
        Case c = Case(index);
        for(int i = 0; i < 4; i++){
            val[i] = -1;
        }
        val[4] = 0;
        //nb of wall around a case = [4]; up = [2]; down = [0]; right = [1]; left = [3]
        if(c.ligne() == 0){
            val[2] = 1;
            val[4] += 1;
        }
        if(c.ligne() == 3){
            val[0] = 1;
            val[4] += 1;
        }
        if(c.colonne() == 0){
            val[3] = 1;
            val[4] += 1;
        }
        if(c.colonne() == 3){
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
        return val;
    }
    //search for missing walls
    int Generateur::missingWall(Tuile *tuile, int index, int *val){
        possibleDirection(tuile, index, val);
        Case c = Case(index);
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

    void Generateur::close(Tuile *tuile){
        int changes;
        int toClose;
        int val[5];
        do{
            for(int i = 0; i < 16; i++){
                changes = 0;
                toClose = missingWall(tuile, i, val);
                if(toClose != -1 && tuile->getSite(i)->type == Type::AUCUN){
                    tuile->setMur(toClose, true);
                    tuile->getSite(i)->type = Type::BOUTIQUE;
                    changes += 1;
                }
                if(val[4] == 4){
                    tuile->getSite(i)->type = Type::BOUTIQUE;
                }
            }
        } while (changes != 0);

    }

    bool Generateur::ajouterObjectif(Couleur c, Tuile *tuile){
        if(objectifs[((int)c)-1]){
            return false;
        }
        std::random_device seed;
        std::mt19937 rd(seed());
        std::uniform_int_distribution<int> rdGen(0, 15);
        int random = rdGen(rd);
        while(tuile->getSite(random)->type != Type::AUCUN){
            random = rdGen(rd);
        }
        Site objectifSite = Site(random);
        tuile->setType(objectifSite.ligne(), objectifSite.colonne(), OBJECTIF);
        std::cout << "Objectif ajouté en " << "Tuile : " << tuile->x << "," << tuile->y << " Case : "<<objectifSite.index() << std::endl;
        tuile->getSite(random)->couleur = c;
        objectifs[((int)c)-1] = true;
        return true;
    }

    bool Generateur::retirerObjectif(Site site){
        if(!objectifs[((int)site.couleur)-1] || site.type != OBJECTIF){
            return false;
        }
        objectifs[((int)site.couleur)-1] = false;
        site.couleur = Couleur::AUCUNE;
        site.type = AUCUN;
        return true;
    }

}