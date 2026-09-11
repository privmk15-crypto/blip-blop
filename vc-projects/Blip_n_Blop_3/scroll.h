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

// Must stay comfortably wider than globals.h's SCREEN_W - this is a
// lookahead cache buffer for drawScrolling()'s tile pre-rendering,
// not the visible width itself. Was briefly 1054 while SCREEN_W was
// widened to 854 for a since-reverted true-widescreen experiment
// (see the SCREEN_W comment in globals.h); back to its original 840
// (640 + 200 margin) now that SCREEN_W is 640 again.
#define WANTED_VBUFFER_WIDE	840

extern int	vbuffer_wide;
extern int	next_x;
extern int	xTex;
extern int	n_img;
extern int	n_cache;


// Gère le scroll
//
void updateScrolling(bool forceOk = true);
void drawScrolling();