/******************************************************************
 *
 *		----------------
 *		 SoundBankSet.h
 *		----------------
 *
 *		Owns the sound/music bank globals (globals.h/.cpp before this
 *		migration): 4 SoundBankBB instances (sbk_bb/sbk_rpg/sbk_misc/
 *		sbk_niveau), 3 MusicBank instances (mbk_niveau/mbk_inter/
 *		mbk_interl), 4 fixed-size "currently loaded bank" name
 *		buffers (current_sbk/current_sbk_misc/current_sbk_niveau/
 *		current_mbk - kept as char[200], same as before, since
 *		strcpy()/strlen() are used directly on them at the call
 *		sites), and current_zik (currently-playing music track
 *		index).
 *
 *		current_sbk/current_sbk_misc/current_sbk_niveau are dead
 *		(verified via full-codebase grep: never read anywhere,
 *		written nowhere but their own zero-initialization) - migrated
 *		anyway for completeness/consistency with the rest of this
 *		cluster, not removed, per the "migrate ownership, not
 *		semantics" rule used throughout Stage 2.
 *
 *		Owned by GameState (game_state.h) as
 *		g_game_state.sound_banks().
 *
 ******************************************************************/

#pragma once

#include "music_bank.h"
#include "sound_bank_bb.h"

class SoundBankSet {
   public:
    SoundBankBB& sbk_bb() { return sbk_bb_; }
    SoundBankBB& sbk_rpg() { return sbk_rpg_; }
    SoundBankBB& sbk_misc() { return sbk_misc_; }
    SoundBankBB& sbk_niveau() { return sbk_niveau_; }

    MusicBank& mbk_niveau() { return mbk_niveau_; }
    MusicBank& mbk_inter() { return mbk_inter_; }
    MusicBank& mbk_interl() { return mbk_interl_; }

    char* current_sbk() { return current_sbk_; }
    char* current_sbk_misc() { return current_sbk_misc_; }
    char* current_sbk_niveau() { return current_sbk_niveau_; }
    char* current_mbk() { return current_mbk_; }
    int& current_zik() { return current_zik_; }

   private:
    SoundBankBB sbk_bb_;
    SoundBankBB sbk_rpg_;
    SoundBankBB sbk_misc_;
    SoundBankBB sbk_niveau_;

    MusicBank mbk_niveau_;
    MusicBank mbk_inter_;
    MusicBank mbk_interl_;

    char current_sbk_[200] = {};
    char current_sbk_misc_[200] = {};
    char current_sbk_niveau_[200] = {};
    char current_mbk_[200] = {};
    int current_zik_ = 0;
};

// Owned by GameState (game_state.h) as g_game_state.sound_banks() - no
// standalone global instances here anymore.
