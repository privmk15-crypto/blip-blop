/******************************************************************
 *
 *		----------------
 *		 ScreenShake.h
 *		----------------
 *
 *		Owns the screen-shake ("tremblement") effect state and
 *		logic.
 *
 *		Stage 2 architecture migration: this replaces four
 *		independent globals that used to live in globals.h/.cpp
 *		(dy_tremblement, etape_tremblement, amplitude_tremblement,
 *		ddy_tremblement) plus the logic that used to live in the free
 *		function tremblement() (globals.cpp) and in
 *		Game::updateTremblements() / Game::drawTremblements()
 *		(game.cpp), all of which read/wrote those four globals
 *		directly.
 *
 *		tremblement(int amp) is kept as a free function (declared in
 *		globals.h, defined in screen_shake.cpp) forwarding to
 *		g_game_state.screen_shake() (owned by GameState, see
 *		game_state.h), because its handful of call sites (scattered
 *		across enemy/projectile .cpp files) have no reachable
 *		Game/GameState instance to call through - this keeps their
 *		call syntax unchanged. Game::updateTremblements() and
 *		Game::drawTremblements() now forward the same way.
 *		Behavior is unchanged from before this migration.
 *
 ******************************************************************/

#pragma once

namespace SDL {
class Surface;
}

class ScreenShake {
   public:
    // Starts (or restarts) a shake of the given amplitude. Equivalent to
    // the old free function tremblement(int amp).
    void Start(int amp);

    // Advances the shake by one frame. Equivalent to the old
    // Game::updateTremblements().
    void Update();

    // Draws the current shake offset onto the given surface. Equivalent to
    // the old Game::drawTremblements() (which always drew to the global
    // backSurface - callers now pass that explicitly).
    void Draw(SDL::Surface* surf);

    // Resets dy/etape/amplitude to 0. Deliberately does NOT reset ddy - the
    // original code this replaces (the level-reset block in
    // Game::joueNiveau()) didn't either; preserved here for bug-for-bug
    // compatibility.
    void Reset();

   private:
    int dy_ = 0;
    int etape_ = 0;
    int amplitude_ = 0;
    int ddy_ = 0;

    // Fix for Draw()'s self-blit-overlap bug: a reusable scratch
    // surface the shifted copy is routed through instead of blitting
    // the target surface onto itself. Lazily created on first Draw()
    // call (this class doesn't otherwise know the target surface's
    // size at construction time).
    SDL::Surface* scratch_ = nullptr;
};

// Owned by GameState (game_state.h) as g_game_state.screen_shake() - no
// standalone global instance here anymore.
