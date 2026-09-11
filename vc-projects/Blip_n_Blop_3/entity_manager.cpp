/******************************************************************
 *
 *		--------------------
 *		 EntityManager.cpp
 *		--------------------
 *
 *		Exists solely to define ~EntityManager() out-of-line, in a
 *		translation unit that has the real definitions of every type
 *		used as std::unique_ptr<T> inside EntityManager (Event,
 *		Bulle, TirBBVache, Explosion, Vehicule, GenEnnemi, GenBonus) -
 *		see the class-level comment in entity_manager.h for why this
 *		is required, not optional, for a class holding
 *		std::list<std::unique_ptr<T>> members where T is only
 *		forward-declared in the header.
 *
 ******************************************************************/

#include "entity_manager.h"

#include "bulle.h"
#include "event.h"
#include "explosion.h"
#include "gen_bonus.h"
#include "gen_ennemi.h"
#include "tir_bb_vache.h"
#include "vehicule.h"

EntityManager::~EntityManager() noexcept = default;
