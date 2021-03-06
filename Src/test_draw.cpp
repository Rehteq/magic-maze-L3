#include "draw.hpp"

#include <iostream>
#include <algorithm>
#include "plateau.h"
#include "generateur.h"
#include "graphe.h"
#include "melangeur.hpp"

using namespace MMaze ;

Plateau p;
Generateur gen;
int main() {
    MelangeurOptions::imprevisible();
    /*
  PadPlateau pad ;
  
  pad.ajouter_tuile(0,0);
  pad.ajouter_boutique(0,0,Case(0)) ;
  pad.ajouter_sortie(0,0, Case(15), Couleur::JAUNE) ;
  pad.ajouter_mur(0,0,Mur(Case(0), Case(1))) ;
  pad.ajouter_mur(0,0,Mur(Case(0), Case(4))) ;
  pad.ajouter_porte(0,0, Case(11), Couleur::JAUNE) ;

  pad.ajouter_tuile(0,1) ;
  pad.ajouter_sortie(0,1, Case(0), Couleur::VIOLET) ;
  pad.ajouter_porte(0,1, Case(4), Couleur::AUCUNE) ;
  pad.ajouter_porte(0,1, Case(11), Couleur::VIOLET) ;
  pad.ajouter_porte(0,1, Case(13), Couleur::VERT) ;
  pad.ajouter_mur(0,1, Mur(Case(4), Case(5))) ;
  pad.ajouter_mur(0,1, Mur(Case(4), Case(8))) ;

  pad.ajouter_tuile(1,0) ;
  pad.ajouter_porte(1,0,Case(11), Couleur::AUCUNE) ;
  pad.ajouter_vortex(1,0,Case(6), Couleur::JAUNE) ;

  pad.ajouter_tuile(1,1) ;
  pad.ajouter_porte(1,1,Case(2), Couleur::AUCUNE) ;
  pad.ajouter_porte(1,1,Case(4), Couleur::JAUNE) ;

  pad.placer_joueur(0,0,Case(5),Couleur::JAUNE) ;
  pad.placer_joueur(0,0,Case(6),Couleur::VERT) ;
  pad.placer_joueur(0,0,Case(9),Couleur::VIOLET) ;
  pad.placer_joueur(0,0,Case(10),Couleur::ORANGE) ;

    pad.ajouter_tuile(0,2);
    pad.ajouter_porte(1,1,Case(2), Couleur::AUCUNE) ;
    pad.ajouter_porte(1,1,Case(4), Couleur::JAUNE) ;

    pad.ajouter_tuile(0,3);
    pad.ajouter_porte(1,1,Case(2), Couleur::AUCUNE) ;
    pad.ajouter_porte(1,1,Case(4), Couleur::JAUNE) ;

    pad.ajouter_tuile(0,4);
    pad.ajouter_porte(1,1,Case(2), Couleur::AUCUNE) ;
    pad.ajouter_porte(1,1,Case(4), Couleur::JAUNE) ;

#ifndef NO_CAIRO
  pad.dessiner("/tmp/plateau.svg") ;
  pad.dessiner("/tmp/plateau.png") ;
#endif

  std::cout << pad << std::endl ;

  pad.save("/tmp/pad.json") ;

  PadPlateau cpy ;
  cpy.load("/tmp/pad.json") ;
  std::cout << cpy << std::endl ;
    */
    Tuile tuile(0,0);
    gen.genererTuile(&tuile, TUILEDEPART);
    p.ajouterTuile(&tuile);
    std::cout << p.toPadPlateau() << std::endl;
    int c = getchar();

    /*
    Joueur j(Couleur::JAUNE);
    j.tuile = &tuile;
    j.site = tuile.getSite(0);
    p.joueurs.push_back(&j);
     */
    //std::vector<Tuile> tuiles;

    if (tuile.getSite(11)->type == Type::PORTE){
        std::cout << "Ajout ?? droite" << std::endl;
        Tuile tuile2(0,1);
        gen.genererTuile(&tuile2, MMaze::TUILECLASSIQUE);
        p.ajouterTuile(&tuile2);
        tuile2.rotateTuile(-1);
        std::cout << p.toPadPlateau() << std::endl;
        c = getchar();
    }
    if (tuile.getSite(13)->type == Type::PORTE){
        std::cout << "Ajout en dessous" << std::endl;
        //Tuile 3
        Tuile tuile3(1,0);
        gen.genererTuile(&tuile3, MMaze::TUILECLASSIQUE);
        p.ajouterTuile(&tuile3);
        tuile3.rotateTuile(2);
        std::cout << p.toPadPlateau() << std::endl;
        c = getchar();
    }

    if (tuile.getSite(4)->type == Type::PORTE){
        std::cout << "Ajout ?? gauche" << std::endl;
        //Tuile 4
        Tuile tuile4(0,-1);
        gen.genererTuile(&tuile4, MMaze::TUILECLASSIQUE);
        p.ajouterTuile(&tuile4);
        tuile4.rotateTuile(1);
        std::cout << p.toPadPlateau() << std::endl;
        c = getchar();
    }

    //Dessins d'un graphe et voisins
    std::cout<< "Dessin du graphe de la tuile de d??part" << std::endl;
    Graphe g = Graphe::fromTuile(&tuile);
    std::cout << g << std::endl;
    c = getchar();
    //Dessins du r??sultat de Dijkstra
    std::cout<< "Dessin des distance depuis la tuile de d??part en 0 0" << std::endl;
    node *n = g.find_noeud(&tuile, tuile.getSite(1,1));
    g.print_distances(*n);

  return 0 ;
}
void handle_input(){
  int c = getchar();
  if(c == 'w'){

  }
}
void move_player(Couleur c, Direction d){

}