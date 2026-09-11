/******************************************************************
 *
 *		----------------
 *		 FontBank.h
 *		----------------
 *
 *		Owns the 8 Fonte instances (fnt_score_blip/fnt_score_blop/
 *		fnt_ammo/fnt_ammo_used/fnt_cool/fnt_rpg/fnt_menu/fnt_menus,
 *		globals.h/.cpp before this migration): loaded once at startup
 *		(Game::loadFonts()/blip_n_blop_3.cpp's WinMain) and used
 *		throughout HUD, menu and cutscene rendering to print text to
 *		a surface.
 *
 *		Owned by GameState (game_state.h) as g_game_state.font_bank()
 *		as part of the Stage 2 ownership migration. Fonte itself is
 *		move-only (holds std::vector<std::unique_ptr<Picture>>), which
 *		is fine here - FontBank is never copied, only its 8 Fonte
 *		members are read/written in place via the accessors below.
 *
 ******************************************************************/

#pragma once

#include "fonte.h"

class FontBank {
   public:
    Fonte& score_blip() { return score_blip_; }
    Fonte& score_blop() { return score_blop_; }
    Fonte& ammo() { return ammo_; }
    Fonte& ammo_used() { return ammo_used_; }
    Fonte& cool() { return cool_; }
    Fonte& rpg() { return rpg_; }
    Fonte& menu() { return menu_; }
    Fonte& menus() { return menus_; }

   private:
    Fonte score_blip_;
    Fonte score_blop_;
    Fonte ammo_;
    Fonte ammo_used_;
    Fonte cool_;
    Fonte rpg_;
    Fonte menu_;
    Fonte menus_;
};

// Owned by GameState (game_state.h) as g_game_state.font_bank() - no
// standalone global instances here anymore.
