/******************************************************************
 *
 *		--------------------
 *		 EntityManager.h
 *		--------------------
 *
 *		Owns ALL 21 entity containers migrated out of globals.h -
 *		groups #1-#7 of the Stage 2 EntityManager analysis, now
 *		complete: list_joueurs, list_event, list_event_endormis,
 *		list_meteo, list_bulles, list_tirs_bb, list_cow, list_impacts,
 *		list_vehicules, list_gen_ennemis, list_gen_bonus (groups
 *		#1-#3), list_fonds_statiques, list_premiers_plans,
 *		list_plateformes_mobiles, list_txt_cool (group #4),
 *		list_ennemis, list_gore, list_bonus, list_fonds_animes (group
 *		#5), list_giclures (group #6), list_tirs_ennemis (group #7,
 *		the largest spawn-site footprint of the 21).
 *
 *		Update/draw/cleanup logic for all entity lists already lives
 *		centrally in Game
 *		(UpdateCollection<T>()/DrawCollection<T>()/RemoveDestroyed<T>(),
 *		game.cpp) - this class does not duplicate or move that, it
 *		only owns the storage, exactly like every other Stage 2
 *		migration so far (ScreenShake, ScrollLock, Level, Weather,
 *		RpgTrigger, HoldFire, PlayerToggles).
 *
 *		Needs an out-of-line destructor (entity_manager.cpp), even
 *		though every accessor here is trivial: several members are
 *		std::list<std::unique_ptr<T>> where T (Event, Bulle,
 *		TirBBVache, Explosion, Vehicule, GenEnnemi, GenBonus, Ennemi,
 *		Tir, Bonus, Sprite, TexteCool) is only forward-declared here.
 *		An implicitly-generated (inline) destructor would need those
 *		types complete wherever it's first instantiated - which,
 *		since GameState's single instance is defined in
 *		game_state.cpp, would be game_state.cpp, which doesn't
 *		include the real headers. Declaring ~EntityManager() here and
 *		defining it (= default is enough) in entity_manager.cpp,
 *		which does include them, defers that instantiation to a
 *		translation unit where it can succeed.
 *
 *		Second gotcha, also confirmed the hard way while migrating
 *		groups #1-#3: the declaration below must specify `noexcept`
 *		explicitly. A destructor with NO exception-specification is -
 *		even when it's user-declared and not defaulted right here -
 *		still implicitly considered to have the SAME exception
 *		specification it would get if it were implicitly-declared,
 *		which means the compiler tries to inspect every member's
 *		destructor (including the unique_ptr<T> ones) right here at
 *		the declaration to compute it, reintroducing the exact same
 *		incomplete-type error this destructor exists to avoid. An
 *		explicit `noexcept` skips that computation.
 *
 *		Third gotcha, also confirmed the hard way: the above two were
 *		STILL not sufficient for game_state.cpp to build - something
 *		about GameState's own (fully implicit) destruction of its
 *		EntityManager member kept re-triggering the same error there
 *		regardless. game_state.cpp now includes the real headers
 *		directly too and gives GameState its own explicit
 *		`~GameState() noexcept` (see game_state.h/.cpp) - belt and
 *		suspenders alongside this class's own out-of-line destructor,
 *		since the exact precise rule GCC 13 was applying was never
 *		fully pinned down.
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
class Ennemi;
class Tir;
class Bonus;
class TexteCool;

class EntityManager {
   public:
    // Declared here, defined (= default) in entity_manager.cpp - see the
    // class-level comment for why this can't just be implicit/inline, and
    // why `noexcept` must be spelled out explicitly.
    ~EntityManager() noexcept;

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

    std::list<std::unique_ptr<Ennemi>>& list_ennemis() {
        return list_ennemis_;
    }
    std::list<std::unique_ptr<Tir>>& list_tirs_ennemis() {
        return list_tirs_ennemis_;
    }
    std::list<std::unique_ptr<Bonus>>& list_bonus() { return list_bonus_; }

    std::list<std::unique_ptr<Sprite>>& list_fonds_animes() {
        return list_fonds_animes_;
    }
    std::list<std::unique_ptr<Sprite>>& list_fonds_statiques() {
        return list_fonds_statiques_;
    }
    std::list<std::unique_ptr<Sprite>>& list_premiers_plans() {
        return list_premiers_plans_;
    }
    std::list<std::unique_ptr<Sprite>>& list_plateformes_mobiles() {
        return list_plateformes_mobiles_;
    }

    std::list<std::unique_ptr<TexteCool>>& list_txt_cool() {
        return list_txt_cool_;
    }

    // FIXME (carried over from globals.h): should prolly be a list of
    // Giclure, but GoreGiclure doesn't inherit Giclure.
    std::list<std::unique_ptr<Sprite>>& list_giclures() {
        return list_giclures_;
    }
    // FIXME (carried over from globals.h): all things put inside list_gore
    // don't have a common base aside from Sprite.
    std::list<std::unique_ptr<Sprite>>& list_gore() { return list_gore_; }

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
    std::list<std::unique_ptr<Ennemi>> list_ennemis_;
    std::list<std::unique_ptr<Tir>> list_tirs_ennemis_;
    std::list<std::unique_ptr<Bonus>> list_bonus_;
    std::list<std::unique_ptr<Sprite>> list_fonds_animes_;
    std::list<std::unique_ptr<Sprite>> list_fonds_statiques_;
    std::list<std::unique_ptr<Sprite>> list_premiers_plans_;
    std::list<std::unique_ptr<Sprite>> list_plateformes_mobiles_;
    std::list<std::unique_ptr<TexteCool>> list_txt_cool_;
    std::list<std::unique_ptr<Sprite>> list_giclures_;
    std::list<std::unique_ptr<Sprite>> list_gore_;
};
