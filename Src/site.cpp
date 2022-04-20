#include "site.hpp"

namespace MMaze {
    Site::Site(unsigned int li, unsigned int col, Couleur c, Type t) : Case(li, col) {
        type = t;
        couleur = c;
    }

    Site::Site(unsigned int index, Couleur c, Type t) : Case(index) {
        type = t;
        couleur = c;
    }

    const char *Site::getSymbol() {
        switch (type) {
            case (Type::AUCUN): return " ";
            case (Type::SORTIE): return "[->";
            case (Type::BOUTIQUE): return "#";
            case (Type::OBJECTIF): return "{$}";
            case (Type::VORTEX): return "@";
            case (Type::PORTE): return "";
            case (Type::DEPART): return "";
        }
        return nullptr;
    }
} //end of namespace MMaze