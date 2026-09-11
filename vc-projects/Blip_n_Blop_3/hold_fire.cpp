/******************************************************************
 *
 *		----------------
 *		  HoldFire.cpp
 *		----------------
 *
 *		See hold_fire.h for the Stage 2 migration note.
 *
 ******************************************************************/

#include "hold_fire.h"

void HoldFire::Engage(int flag, int val) {
    active_ = true;
    flag_ = flag;
    val_ = val;
}

void HoldFire::Activate() { active_ = true; }

void HoldFire::Release() { active_ = false; }
