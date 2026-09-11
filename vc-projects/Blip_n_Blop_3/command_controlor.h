/******************************************************************
 *
 *		----------------
 *		 CommandControlor.h
 *		----------------
 *
 *		Plays a captured (or, eventually, network-received)
 *		InputCommand back into any code that expects a live Controlor
 *		(Couille::ctrl and friends), without that code needing to
 *		know the difference. See input_command.h for the bigger
 *		picture - this is the "replay a captured command" half of the
 *		round trip; ControlP1/ControlP2 remain the "read local SDL
 *		input" half, unchanged by this addition.
 *
 *		Not used anywhere in the live game loop yet - this is
 *		scaffolding, added so a future caller (e.g. a server replaying
 *		a client's received commands, or a local input-recording/
 *		playback tool) has somewhere to plug in without inventing a
 *		new Controlor subclass or touching Couille/ControlP1/
 *		ControlP2.
 *
 *		inertia()/setInertia() are intentionally not overridden here:
 *		they're not part of InputCommand (see input_command.h), so
 *		this class falls back to Controlor's own default (inertia_on
 *		= true, never toggled anywhere in the codebase).
 *
 ******************************************************************/

#pragma once

#include "controlor.h"
#include "input_command.h"

class CommandControlor : public Controlor {
   public:
    explicit CommandControlor(const InputCommand& cmd = InputCommand()) : cmd_(cmd) {}

    void set_command(const InputCommand& cmd) { cmd_ = cmd; }
    const InputCommand& command() const { return cmd_; }

    int gauche() const override { return cmd_.left; }
    int haut() const override { return cmd_.up; }
    int droite() const override { return cmd_.right; }
    int bas() const override { return cmd_.down; }
    int fire() const override { return cmd_.fire; }
    int saut() const override { return cmd_.jump; }
    int super() const override { return cmd_.super; }

   private:
    InputCommand cmd_;
};
