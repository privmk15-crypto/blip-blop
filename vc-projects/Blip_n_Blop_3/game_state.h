/******************************************************************
 *
 *		----------------
 *		 GameState.h
 *		----------------
 *
 *		Composition root for the Stage 2 ownership migration and the
 *		SOLE owner of ScreenShake, ScrollLock, Level, Weather,
 *		RpgTrigger, HoldFire, PlayerToggles, EntityManager, DebugStats,
 *		PhaseClock, EnemyStats, FontBank, GameFlags, PictureBankSet
 *		and (as of the sound-bank migration) SoundBankSet - the types
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

#include "debug_stats.h"
#include "enemy_stats.h"
#include "entity_manager.h"
#include "font_bank.h"
#include "game_flags.h"
#include "hold_fire.h"
#include "level.h"
#include "phase_clock.h"
#include "picture_bank_set.h"
#include "player_toggles.h"
#include "rpg_trigger.h"
#include "screen_shake.h"
#include "scroll_lock.h"
#include "sound_bank_set.h"
#include "weather.h"

class GameState {
   public:
    // Declared here, defined (noexcept = default) in game_state.cpp,
    // which pulls in the real headers for everything EntityManager holds
    // via unique_ptr - belt-and-suspenders alongside EntityManager's own
    // out-of-line destructor (entity_manager.h/.cpp): two attempts at
    // deferring just EntityManager's own destructor still failed CI with
    // the same incomplete-type error pointing at game_state.cpp, so this
    // makes GameState's destruction explicit too rather than relying on
    // an implicit one being generated correctly in this TU.
    ~GameState() noexcept;

    ScreenShake& screen_shake() { return screen_shake_; }
    ScrollLock& scroll_lock() { return scroll_lock_; }
    Level& level() { return level_; }
    Weather& weather() { return weather_; }
    RpgTrigger& rpg_trigger() { return rpg_trigger_; }
    HoldFire& hold_fire() { return hold_fire_; }
    PlayerToggles& player_toggles() { return player_toggles_; }
    EntityManager& entities() { return entities_; }
    DebugStats& debug_stats() { return debug_stats_; }
    PhaseClock& phase_clock() { return phase_clock_; }
    EnemyStats& enemy_stats() { return enemy_stats_; }
    FontBank& font_bank() { return font_bank_; }
    GameFlags& game_flags() { return game_flags_; }
    PictureBankSet& picture_banks() { return picture_banks_; }
    SoundBankSet& sound_banks() { return sound_banks_; }

   private:
    ScreenShake screen_shake_;
    ScrollLock scroll_lock_;
    Level level_;
    Weather weather_;
    RpgTrigger rpg_trigger_;
    HoldFire hold_fire_;
    PlayerToggles player_toggles_;
    EntityManager entities_;
    DebugStats debug_stats_;
    PhaseClock phase_clock_;
    EnemyStats enemy_stats_;
    FontBank font_bank_;
    GameFlags game_flags_;
    PictureBankSet picture_banks_;
    SoundBankSet sound_banks_;
};

// The single GameState for the current game session - the sole owner of
// all 7 aggregated types. A plain global with default-constructed value
// members: nothing else needs to run before it (its members are POD-like,
// default member initializers only), so there is no cross-translation-unit
// static-initialization-order concern.
extern GameState g_game_state;
