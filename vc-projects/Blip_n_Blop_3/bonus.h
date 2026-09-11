/******************************************************************
 *
 *
 *		----------------
 *		    Bonus.h
 *		----------------
 *
 *
 *
 *		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
 *
 *
 *
 ******************************************************************/

#ifndef _Bonus_
#define _Bonus_

#include "ben_maths.h"
#include "couille.h"
#include "sprite.h"
#include "game_state.h"
#include "globals.h"

#define DIST_BITONIO 25

class Bonus : public Sprite {
   public:
    int phi;
    bool local_phase;

    Bonus() : phi(0), local_phase(0){};

    virtual void estPris(Couille* c) {
        a_detruire = true;
        col_on = false;
    };

    virtual void update() {
        tombe();

        phi += 12;
        phi %= 360;

        etape += 1;
        etape %= 10;

        if (etape == 0) local_phase = !local_phase;

        if (x < offset - 50) a_detruire = true;

        y -= 15;
        colFromPic();
        y += 15;
    };

    // Etap 3 (Sprite/Renderer separation, step 1): moved out-of-line to
    // bonus.cpp - was the last of 4 affiche() bodies still inline in a
    // header across the whole Sprite hierarchy. Unchanged otherwise.
    virtual void affiche();

    virtual void colFromPic() {
        Sprite::colFromPic();

        x1 -= 10;
        y1 -= 10;
        x2 += 10;
        y2 += 10;
    };
};

#endif
