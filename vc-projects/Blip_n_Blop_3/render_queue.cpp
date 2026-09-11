/******************************************************************
 *
 *		----------------
 *		 RenderQueue.cpp
 *		----------------
 *
 *		See render_queue.h for the design note.
 *
 ******************************************************************/

#include "render_queue.h"

void RenderQueue::Push(int x, int y, const Picture* pic) {
    commands_.push_back(RenderCommand{x, y, pic});
}

void RenderQueue::Clear() { commands_.clear(); }
