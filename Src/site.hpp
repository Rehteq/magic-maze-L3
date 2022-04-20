#ifndef MMAZE_SITE_HPP
#define MMAZE_SITE_HPP

#include "case.hpp"
#include "couleurs.hpp"

namespace MMaze {
    enum Type {
        AUCUN,
        PORTE,
        OBJECTIF,
        SORTIE,
        DEPART,
        VORTEX,
        BOUTIQUE
    };

    class Site : public Case {
    public:
        Type type;
        Couleur couleur;
        Site(unsigned int li, unsigned int col, Couleur c = Couleur::AUCUNE, Type t = AUCUN);
        Site(unsigned int index, Couleur c = Couleur::AUCUNE, Type t = AUCUN);
        const char* getSymbol();
    };
} //end of namespace MMaze

#endif
