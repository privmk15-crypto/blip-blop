/******************************************************************
*
*
*		-----------------
*		   TexteCool.h
*		-----------------
*
*		Pour les textes "tetra tuerie"
*
*
*		Prosper / LOADED -   V 0.1 - 17 Aout 2000
*
*
*
******************************************************************/

#ifndef _TexteCool_
#define _TexteCool_

#ifndef TEXTE_COOL_CPP
extern bool txt_cool_free[];
#endif

// RenderSystem migration, step 2: TexteCool isn't Sprite-derived (no
// base class at all) but participates in Game::DrawCollection<T> the
// same way (duck-typed, called as pl->affiche(rq) - DrawCollection is
// a template, not a virtual dispatch, so this works without
// inheritance). Its affiche() renders text via Fonte::printC(), not a
// Picture, so it doesn't fit RenderCommand{x,y,Picture*} - signature
// updated for compatibility with DrawCollection's new rq parameter,
// body deliberately left calling Fonte::printC() directly (same
// "signature-only" treatment as the 5 hard SDL::Surface cases from
// the Sprite/Renderer audit - see texte_cool.cpp).
class RenderQueue;

class TexteCool
{
public:
	int		y;
	int		nn;
	int		ntxt;
	int		x;
	int		t;

	TexteCool();

	void update();
	void affiche(RenderQueue& rq);

	bool aDetruire()
	{
		return x <= -320;
	};
};

void clearTexteCool();

#endif


