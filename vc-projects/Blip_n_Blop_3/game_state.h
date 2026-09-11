/******************************************************************
 *
 *		----------------
 *		 GameState.h
 *		----------------
 *
 *		Composition root for the Stage 2 ownership migration:
 *		aggregates the small owned types extracted from globals.h so
 *		far (ScreenShake, ScrollLock, Level, Weather, RpgTrigger,
 *		HoldFire, PlayerToggles) into one addressable "state of the
 *		simulated world" surface.
 *
 *		Why now: this exists specifically to prepare for future
 *		multiplayer work via server-authoritative state sync (not
 *		lockstep - this codebase's scattered, unseeded rand() calls
 *		make full determinism impractical to retrofit, but state sync
 *		doesn't need determinism, only a serializable/diffable state
 *		surface). A dedicated server needs exactly one thing it can
 *		construct, update, and eventually serialize/diff - without
 *		ever touching rendering/audio/input (a future GameContext,
 *		not built yet, and deliberately never referenced from here).
 *
 *		IMPORTANT - this does NOT change ownership of any aggregated
 *		type. Each keeps its own invariants and its own free-standing
 *		g_* global instance, because the ~150 leaf entity files that
 *		read/write them have no reachable Game (or GameState)
 *		reference and go through those globals/free-function shims
 *		directly - see each type's own header for why. GameState
 *		holds references to those SAME instances (bound in
 *		game_state.cpp), not new copies - it's an additional access
 *		path for future consumers (networking, save state) that want
 *		"the whole state" as one object, not a new source of truth.
 *		None of the ~40 existing call sites across game.cpp/
 *		couille.cpp/enemy.cpp/event_*.h etc. need to change, or have
 *		been changed, because of this file.
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
    GameState(ScreenShake& screen_shake, ScrollLock& scroll_lock,
              Level& level, Weather& weather, RpgTrigger& rpg_trigger,
              HoldFire& hold_fire, PlayerToggles& player_toggles)
        : screen_shake_(screen_shake),
          scroll_lock_(scroll_lock),
          level_(level),
          weather_(weather),
          rpg_trigger_(rpg_trigger),
          hold_fire_(hold_fire),
          player_toggles_(player_toggles) {}

    ScreenShake& screen_shake() { return screen_shake_; }
    ScrollLock& scroll_lock() { return scroll_lock_; }
    Level& level() { return level_; }
    Weather& weather() { return weather_; }
    RpgTrigger& rpg_trigger() { return rpg_trigger_; }
    HoldFire& hold_fire() { return hold_fire_; }
    PlayerToggles& player_toggles() { return player_toggles_; }

   private:
    ScreenShake& screen_shake_;
    ScrollLock& scroll_lock_;
    Level& level_;
    Weather& weather_;
    RpgTrigger& rpg_trigger_;
    HoldFire& hold_fire_;
    PlayerToggles& player_toggles_;
};

// The single GameState for the current game session, aggregating the
// existing g_screen_shake/g_scroll_lock/g_level/g_weather/g_rpg_trigger/
// g_hold_fire/g_player_toggles singletons (see game_state.cpp). Binding
// references here does not read those objects' contents, only their
// addresses, so this is safe regardless of static-initialization order
// across translation units.
extern GameState g_game_state;
