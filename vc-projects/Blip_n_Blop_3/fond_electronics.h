/******************************************************************
*
*
*		---------------------------
*		    FondElectronics.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/


#include "sprite.h"

#ifndef _FondElectronics_
#define _FondElectronics_


class FondElectronic1 : public Sprite
{
public:

	virtual void update();
	virtual void affiche(RenderQueue& rq);
};

class FondElectronic2 : public Sprite
{
public:

	virtual void update();
	virtual void affiche(RenderQueue& rq);
};

class FondElectronic3 : public Sprite
{
public:

	virtual void update();
	virtual void affiche(RenderQueue& rq);
};

class FondElectronic4 : public Sprite
{
public:

	virtual void update();
};


#endif
