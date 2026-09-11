/******************************************************************
 *
 *		----------------
 *		 ScrollLock.cpp
 *		----------------
 *
 *		See scroll_lock.h for the Stage 2 migration note.
 *
 ******************************************************************/

#include "scroll_lock.h"

ScrollLock g_scroll_lock;

void ScrollLock::Engage(int x, int cond, int flag, int val) {
    active_ = true;
    x_ = x;
    cond_ = cond;
    flag_ = flag;
    val_ = val;
}

void ScrollLock::Release() { active_ = false; }
