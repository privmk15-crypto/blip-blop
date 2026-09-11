/******************************************************************
 *
 *		----------------
 *		 RenderSystem.h
 *		----------------
 *
 *		The one place allowed to turn a RenderQueue into actual
 *		pixels: Execute() walks a queue's commands and blits each
 *		Picture onto the given target surface, at (x - offset, y) -
 *		exactly what the free function draw() (globals.h) does today
 *		for a single Picture, just applied to a whole queue's worth
 *		at once. Unlike RenderCommand/RenderQueue, this class is
 *		explicitly allowed to depend on SDL/Picture (see
 *		render_system.cpp) - it IS the rendering layer, not gameplay;
 *		the point of the SDL-free RenderCommand/RenderQueue is to
 *		keep gameplay code from needing to make that same call
 *		itself, not to keep SDL out of the codebase entirely.
 *
 *		target and offset are taken as explicit parameters rather
 *		than read from the backSurface/offset globals, matching the
 *		pattern already used by ScreenShake::Draw(SDL::Surface*) and
 *		CollisionSystem::Update(int) - dependencies stay visible in
 *		the signature instead of being implicit.
 *
 *		Deliberately not a global (no g_render_system): unlike
 *		GameState, which hundreds of files reach directly because it
 *		represents long-lived world state, RenderSystem is only ever
 *		called from one place (Game::drawAll(), once the migration
 *		plan's later steps wire it up - NOT done yet). It's meant to
 *		be owned by Game (alongside collision_system_/event_system_/
 *		etc.) and threaded through as a reference/parameter, not
 *		reached globally.
 *
 *		Not wired into anything yet: nothing constructs a
 *		RenderSystem or calls Execute() anywhere in the codebase. This
 *		is step 1 of the RenderSystem migration plan - an isolated,
 *		inert foundation. Game::drawAll()/DrawCollection() are
 *		unchanged.
 *
 ******************************************************************/

#pragma once

namespace SDL {
class Surface;
}

class RenderQueue;

class RenderSystem {
   public:
    void Execute(const RenderQueue& queue, SDL::Surface* target, int offset);
};
