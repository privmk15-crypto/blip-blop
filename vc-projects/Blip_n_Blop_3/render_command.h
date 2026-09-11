/******************************************************************
 *
 *		----------------
 *		 RenderCommand.h
 *		----------------
 *
 *		A single, plain-data draw request: "put this Picture at
 *		(x, y)". This is the entire rendering vocabulary the Sprite
 *		hierarchy actually needs today - every affiche() body in the
 *		~166 non-exempt classes (see the Sprite/Renderer audit) boils
 *		down to one or more calls shaped exactly like this.
 *
 *		Deliberately SDL-free: Picture is forward-declared, not
 *		included. This is what lets gameplay code (Sprite::affiche()
 *		and its overrides, once migrated) build RenderCommands
 *		without linking or even seeing SDL - only RenderSystem's own
 *		.cpp (render_system.cpp), which actually executes these
 *		commands, needs the real SDL/Picture types.
 *
 *		Not built yet, not wired into anything: this is step 1 of the
 *		RenderSystem migration plan (see the RenderSystem design
 *		analysis) - an isolated, inert foundation. Sprite::affiche(),
 *		DrawCollection(), and Game::drawAll() are unchanged; nothing
 *		constructs a RenderCommand anywhere yet.
 *
 ******************************************************************/

#pragma once

class Picture;

struct RenderCommand {
    int x = 0;
    int y = 0;
    const Picture* pic = nullptr;
};
