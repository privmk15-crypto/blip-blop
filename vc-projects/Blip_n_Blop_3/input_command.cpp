/******************************************************************
 *
 *		----------------
 *		 InputCommand.cpp
 *		----------------
 *
 *		See input_command.h for the design note.
 *
 ******************************************************************/

#include "input_command.h"

#include "controlor.h"

InputCommand InputCommand::Capture(const Controlor& ctrl) {
    InputCommand cmd;
    cmd.left = ctrl.gauche();
    cmd.up = ctrl.haut();
    cmd.right = ctrl.droite();
    cmd.down = ctrl.bas();
    cmd.fire = ctrl.fire();
    cmd.jump = ctrl.saut();
    cmd.super = ctrl.super();
    return cmd;
}
