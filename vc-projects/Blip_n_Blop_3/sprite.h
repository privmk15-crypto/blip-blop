/******************************************************************
*
*
*		----------------
*		    Sprite.h
*		----------------
*
*		La classe surpuissante!
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _SPRITE_
#define _SPRITE_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

// Etap 3 (Sprite/Renderer separation, step 0): forward-declared, not
// included. Sprite only ever holds a Picture* (pointer), never
// dereferences it inline in this header - the three methods that used
// to need Picture/globals.h complete inline (estSurMur/affiche/
// updateADetruire, see below) are now declared here and defined
// out-of-line in sprite.cpp, which includes the real headers. This is
// what lets every one of the ~170 Sprite-derived gameplay classes stop
// transitively requiring <SDL2/SDL.h> just to parse their own header -
// see the Sprite/Renderer audit for the full include-chain trace
// (sprite.h -> picture.h -> dd_gfx.h -> graphics.h -> SDL2/SDL.h, and
// sprite.h -> globals.h -> control_p1.h -> input.h -> SDL2/SDL.h).
// Behavior is unchanged; this is a pure code-motion, not a redesign.
class Picture;

//-----------------------------------------------------------------------------
//		Définition de la classe Sprite
//-----------------------------------------------------------------------------

class Sprite
{
public:

	int			x;
	int			y;
	int			dy;
	int			etape;
	int			ss_etape;
	Picture *	pic;
	bool		a_detruire;
	int			dir;
	int			lat_grav;

	int			wait_bulle;

	int			x1;	// Pour les collisions
	int			y1;
	int			x2;
	int			y2;
	bool		col_on;

	Sprite();

	inline virtual int getX() const
	{
		return x;
	};
	inline virtual int getY() const
	{
		return y;
	};
	inline virtual int getEtape() const
	{
		return etape;
	};
	inline virtual Picture * getPic() const
	{
		return pic;
	};
	inline virtual bool aDetruire() const
	{
		return a_detruire;
	};

	// Moved out-of-line to sprite.cpp - see the forward-declaration
	// comment above.
	virtual bool estSurMur() const;   // (sanglant)

	inline virtual int anime(const int * tab, int nb_etapes, int latence)
	{
		ss_etape += 1;
		ss_etape %= latence;

		if (ss_etape == 0)
			etape += 1;

		if (etape < 0)
			etape = 0;

		etape %= nb_etapes;
		return tab[etape];
	};

	// Moved out-of-line to sprite.cpp - see the forward-declaration
	// comment above.
	virtual void affiche();

	// Moved out-of-line to sprite.cpp - see the forward-declaration
	// comment above.
	virtual void updateADetruire();

	virtual void update() = 0;

	virtual void tombe();
	virtual void tombe2();
	virtual void marche(int speed);
	virtual void colFromPic();
	virtual void noCol();

	inline virtual bool collision(const Sprite * s) const
	{
		if (!col_on || !s->col_on)
			return false;
		else
			return !((s->x2 < x1) || (s->x1 > x2) || (s->y2 < y1) || (s->y1 > y2));
	};

	virtual ~Sprite()
	{
	};

};

#endif