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
        POINT_DEPART
    };

    class Site : Case {
    public:
        Type type;
        Couleur couleur;
        Site(unsigned int li, unsigned int col, Couleur c = Couleur::AUCUNE, Type t = AUCUN);
        Site(unsigned int index, Couleur c, Type t);
    };
} //end of namespace MMaze

#endif
