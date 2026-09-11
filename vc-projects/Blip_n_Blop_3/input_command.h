/******************************************************************
 *
 *		----------------
 *		 InputCommand.h
 *		----------------
 *
 *		A serializable snapshot of one player's intended actions for
 *		a single frame: the same 7 signals Controlor already exposes
 *		(gauche/haut/droite/bas/fire/saut/super), captured as plain
 *		data instead of read live via virtual calls into a polling
 *		Controlor (ControlP1/ControlP2, which read SDL through the
 *		global `in`).
 *
 *		This is scaffolding for the eventual Client -> InputCommand ->
 *		Server -> GameState -> Snapshot -> Client architecture (see
 *		game_state.h's own multiplayer-rationale comment) - it is NOT
 *		wired into the live single-player game loop by this change,
 *		and no multiplayer networking is implemented here. Today,
 *		Couille and friends still read directly from ctrl->gauche()/
 *		etc. (a live ControlP1/ControlP2), completely unchanged. What
 *		this adds is the ability to:
 *		  - capture what a live Controlor answers this frame as
 *		    plain, copyable data (Capture() below) instead of only
 *		    being able to ask a live Controlor "right now", and
 *		  - play a captured (or, eventually, network-received)
 *		    InputCommand back into any code that expects a Controlor,
 *		    via CommandControlor (command_controlor.h), without that
 *		    code needing to know the difference.
 *
 *		Plain bool fields, not int, even though Controlor's own
 *		methods return int: every call site in the codebase
 *		(couille.cpp and friends) only ever uses gauche()/droite()/
 *		etc. in boolean context (if/&&/||, never compared or used
 *		arithmetically) - verified via a full-codebase grep before
 *		choosing this representation. inertia()/setInertia() are
 *		deliberately not part of this: setInertia() is never called
 *		anywhere in the codebase (verified the same way), so it isn't
 *		a real per-frame input signal to capture.
 *
 ******************************************************************/

#pragma once

class Controlor;

struct InputCommand {
    bool left = false;
    bool up = false;
    bool right = false;
    bool down = false;
    bool fire = false;
    bool jump = false;
    bool super = false;

    // Reads a live Controlor's current state into a new InputCommand.
    static InputCommand Capture(const Controlor& ctrl);
};
