/******************************************************************
 *
 *		--------------------
 *		 EntityManager.h
 *		--------------------
 *
 *		Owns entity containers migrated out of globals.h. This is
 *		groups #1-#3 of the Stage 2 EntityManager analysis (11 of 21
 *		total lists) - specifically the ones with the smallest
 *		spawn-site footprint (0 to 1 external writer file each, per
 *		that analysis): list_joueurs, list_event, list_event_endormis,
 *		list_meteo, list_bulles, list_tirs_bb, list_cow, list_impacts,
 *		list_vehicules, list_gen_ennemis, list_gen_bonus.
 *
 *		The remaining 10 lists (list_ennemis, list_tirs_ennemis,
 *		list_bonus, list_fonds_animes, list_fonds_statiques,
 *		list_premiers_plans, list_plateformes_mobiles, list_txt_cool,
 *		list_giclures, list_gore) stay in globals.h for now - larger
 *		spawn-site footprint, planned as later groups.
 *
 *		Update/draw/cleanup logic for ALL entity lists (migrated or
 *		not) already lives centrally in Game
 *		(UpdateCollection<T>()/DrawCollection<T>()/RemoveDestroyed<T>(),
 *		game.cpp) - this class does not duplicate or move that, it
 *		only owns the storage, exactly like every other Stage 2
 *		migration so far (ScreenShake, ScrollLock, Level, Weather,
 *		RpgTrigger, HoldFire, PlayerToggles).
 *
 *		Needs an out-of-line destructor (entity_manager.cpp), even
 *		though every accessor here is trivial: several members are
 *		std::list<std::unique_ptr<T>> where T (Event, Bulle,
 *		TirBBVache, Explosion, Vehicule, GenEnnemi, GenBonus) is only
 *		forward-declared here. An implicitly-generated (inline)
 *		destructor would need those types complete wherever it's
 *		first instantiated - which, since GameState's single instance
 *		is defined in game_state.cpp, would be game_state.cpp, which
 *		doesn't include the real headers. Declaring ~EntityManager()
 *		here and defining it (= default is enough) in
 *		entity_manager.cpp, which does include them, defers that
 *		instantiation to a translation unit where it can succeed.
 *		(Confirmed the hard way: this exact shape failed CI with
 *		"invalid application of 'sizeof' to incomplete type" for
 *		every unique_ptr<T> member, pointing at game_state.cpp.)
 *
 *		Owned by GameState (game_state.h) as g_game_state.entities().
 *		Most writers of these lists are Event subclasses
 *		(EventGenEnnemi, EventGenBonus, EventVehicule, etc.) or other
 *		leaf entity files with no reachable Game/GameState reference
 *		of their own - same reasoning as every prior Stage 2 type.
 *
 ******************************************************************/

#pragma once

#include <list>
#include <memory>
#include <vector>

class Couille;
class Event;
class Sprite;
class Bulle;
class TirBB;
class TirBBVache;
class Explosion;
class Vehicule;
class GenEnnemi;
class GenBonus;

class EntityManager {
   public:
    // Declared here, defined (= default) in entity_manager.cpp - see the
    // class-level comment for why this can't just be implicit/inline.
    ~EntityManager();

    // FIXME (carried over from globals.h): vector instead of an owning
    // container because Couille* isn't owned here - see the original
    // "FIXME: make it owning?" note this replaces.
    std::vector<Couille*>& list_joueurs() { return list_joueurs_; }

    std::list<std::unique_ptr<Event>>& list_event() { return list_event_; }
    std::list<std::unique_ptr<Event>>& list_event_endormis() {
        return list_event_endormis_;
    }

    std::list<Sprite*>& list_meteo() { return list_meteo_; }
    std::list<std::unique_ptr<Bulle>>& list_bulles() { return list_bulles_; }

    std::list<TirBB*>& list_tirs_bb() { return list_tirs_bb_; }
    std::list<std::unique_ptr<TirBBVache>>& list_cow() { return list_cow_; }
    // FIXME (carried over from globals.h): should be owning by value but
    // can't, because of circular deps.
    std::list<std::unique_ptr<Explosion>>& list_impacts() {
        return list_impacts_;
    }
    std::list<std::unique_ptr<Vehicule>>& list_vehicules() {
        return list_vehicules_;
    }
    std::list<std::unique_ptr<GenEnnemi>>& list_gen_ennemis() {
        return list_gen_ennemis_;
    }
    std::list<std::unique_ptr<GenBonus>>& list_gen_bonus() {
        return list_gen_bonus_;
    }

   private:
    std::vector<Couille*> list_joueurs_;
    std::list<std::unique_ptr<Event>> list_event_;
    std::list<std::unique_ptr<Event>> list_event_endormis_;
    std::list<Sprite*> list_meteo_;
    std::list<std::unique_ptr<Bulle>> list_bulles_;
    std::list<TirBB*> list_tirs_bb_;
    std::list<std::unique_ptr<TirBBVache>> list_cow_;
    std::list<std::unique_ptr<Explosion>> list_impacts_;
    std::list<std::unique_ptr<Vehicule>> list_vehicules_;
    std::list<std::unique_ptr<GenEnnemi>> list_gen_ennemis_;
    std::list<std::unique_ptr<GenBonus>> list_gen_bonus_;
};
