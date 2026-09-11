/******************************************************************
 *
 *		----------------
 *		 PictureBankSet.h
 *		----------------
 *
 *		Owns the 10 PictureBank instances (pbk_decor/pbk_blip/
 *		pbk_blop/pbk_bb/pbk_misc/pbk_ennemis/pbk_niveau/pbk_rpg/
 *		pbk_rpg_bb/pbk_inter, globals.h/.cpp before this migration):
 *		loaded once per level/menu context (Game::loadPbk() and
 *		friends) and indexed everywhere sprites pick their Picture
 *		(pbk_ennemis[N], pbk_niveau[N], ...).
 *
 *		Owned by GameState (game_state.h) as
 *		g_game_state.picture_banks() as part of the Stage 2 ownership
 *		migration. PictureBank itself is move-only (holds
 *		std::vector<std::unique_ptr<Picture>>), same as Fonte/
 *		FontBank - fine here since PictureBankSet is never copied.
 *
 ******************************************************************/

#pragma once

#include "picture_bank.h"

class PictureBankSet {
   public:
    PictureBank& decor() { return decor_; }
    PictureBank& blip() { return blip_; }
    PictureBank& blop() { return blop_; }
    PictureBank& bb() { return bb_; }
    PictureBank& misc() { return misc_; }
    PictureBank& ennemis() { return ennemis_; }
    PictureBank& niveau() { return niveau_; }
    PictureBank& rpg() { return rpg_; }
    PictureBank& rpg_bb() { return rpg_bb_; }
    PictureBank& inter() { return inter_; }

   private:
    PictureBank decor_;
    PictureBank blip_;
    PictureBank blop_;
    PictureBank bb_;
    PictureBank misc_;
    PictureBank ennemis_;
    PictureBank niveau_;
    PictureBank rpg_;
    PictureBank rpg_bb_;
    PictureBank inter_;
};

// Owned by GameState (game_state.h) as g_game_state.picture_banks() - no
// standalone global instances here anymore.
