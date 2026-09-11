/******************************************************************
*
*
*		----------------
*		    Scroll.h
*		----------------
*
*
*		Fonctions pour le scroll. Gère le scrolling
*		avec le super buffer qui marche bizarrement sur cette
*		merde de GeForce.
*
*
*		Prosper / LOADED -   V 0.1 - 3 Juillet 2000
*
*
*
******************************************************************/

// Etap 4 (Full HD prep, step 3): must stay comfortably wider than
// globals.h's SCREEN_W (854) - this is a lookahead cache buffer for
// drawScrolling()'s tile pre-rendering, not the visible width itself.
// Was 840 (640 + 200 margin) before SCREEN_W widened to 854; kept the
// same ~200px margin here (854 + 200 = 1054).
#define WANTED_VBUFFER_WIDE	1054

extern int	vbuffer_wide;
extern int	next_x;
extern int	xTex;
extern int	n_img;
extern int	n_cache;


// Gère le scroll
//
void updateScrolling(bool forceOk = true);
void drawScrolling();