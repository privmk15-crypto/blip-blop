/******************************************************************
 *
 *		----------------
 *		 GameState.cpp
 *		----------------
 *
 *		See game_state.h for the Stage 2 migration note.
 *
 *		Includes the real headers for everything EntityManager holds
 *		via std::unique_ptr<T> (only forward-declared in
 *		entity_manager.h), even though EntityManager already has its
 *		own out-of-line destructor for exactly this reason. Two
 *		rounds of trying to keep those types forward-declared-only
 *		everywhere (an out-of-line ~EntityManager(), then an explicit
 *		noexcept on it) both still failed CI with an identical
 *		incomplete-type error pointing at this file, building
 *		g_game_state's own (implicit) destruction. Including them
 *		here directly - the one TU that actually owns the single
 *		GameState instance - sidesteps needing to pin down the exact
 *		rule that kept pulling them in.
 *
 ******************************************************************/

#include "game_state.h"

#include "bulle.h"
#include "event.h"
#include "explosion.h"
#include "gen_bonus.h"
#include "gen_ennemi.h"
#include "tir_bb_vache.h"
#include "vehicule.h"

GameState g_game_state;

GameState::~GameState() noexcept = default;
