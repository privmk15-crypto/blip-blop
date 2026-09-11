/******************************************************************
 *
 *		----------------
 *		 GameState.h
 *		----------------
 *
 *		Composition root for the Stage 2 ownership migration and the
 *		SOLE owner of ScreenShake, ScrollLock, Level, Weather,
 *		RpgTrigger, HoldFire, and PlayerToggles - the small types
 *		extracted from globals.h so far.
 *
 *		Why one true owner rather than 7 independent globals: this
 *		exists to prepare for future multiplayer work via
 *		server-authoritative state sync (not lockstep - this
 *		codebase's scattered, unseeded rand() calls make full
 *		determinism impractical to retrofit, but state sync doesn't
 *		need determinism, only a serializable/diffable state
 *		surface). Real single ownership - not 7 globals plus a
 *		reference-holding facade - is what actually enables later
 *		work like multiple independent GameState instances (a server
 *		hosting several lobbies, client-side rollback/prediction),
 *		which a set of process-wide singletons could never support.
 *
 *		How the ~150 leaf entity files that have no reachable Game/
 *		GameState reference still reach this state: they go through
 *		the single global g_game_state below (or, for
 *		screen-shake specifically, the tremblement() free-function
 *		shim in screen_shake.cpp, which itself now forwards through
 *		g_game_state). There is deliberately no per-type global
 *		anymore (no g_screen_shake, g_level, etc.) - g_game_state is
 *		the only source of truth, reached via
 *		g_game_state.level()/.weather()/etc.
 *
 *		Deliberately excludes anything render/audio/input-related
 *		(a future GameContext, not built yet) - a dedicated server
 *		constructs a GameState and never needs a GameContext at all.
 *
 ******************************************************************/

#pragma once

#include "hold_fire.h"
#include "level.h"
#include "player_toggles.h"
#include "rpg_trigger.h"
#include "screen_shake.h"
#include "scroll_lock.h"
#include "weather.h"

class GameState {
   public:
    ScreenShake& screen_shake() { return screen_shake_; }
    ScrollLock& scroll_lock() { return scroll_lock_; }
    Level& level() { return level_; }
    Weather& weather() { return weather_; }
    RpgTrigger& rpg_trigger() { return rpg_trigger_; }
    HoldFire& hold_fire() { return hold_fire_; }
    PlayerToggles& player_toggles() { return player_toggles_; }

   private:
    ScreenShake screen_shake_;
    ScrollLock scroll_lock_;
    Level level_;
    Weather weather_;
    RpgTrigger rpg_trigger_;
    HoldFire hold_fire_;
    PlayerToggles player_toggles_;
};

// The single GameState for the current game session - the sole owner of
// all 7 aggregated types. A plain global with default-constructed value
// members: nothing else needs to run before it (its members are POD-like,
// default member initializers only), so there is no cross-translation-unit
// static-initialization-order concern.
extern GameState g_game_state;
