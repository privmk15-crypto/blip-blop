/******************************************************************
 *
 *		----------------
 *		 RenderSystem.cpp
 *		----------------
 *
 *		See render_system.h for the design note. This is the sole
 *		translation unit in the RenderSystem step-1 foundation that
 *		needs the real Picture/SDL types - render_command.h and
 *		render_queue.h/.cpp stay SDL-free.
 *
 ******************************************************************/

#include "render_system.h"

#include "picture.h"
#include "render_queue.h"

void RenderSystem::Execute(const RenderQueue& queue, SDL::Surface* target, int offset) {
    for (const RenderCommand& cmd : queue.commands()) {
        if (cmd.pic != nullptr) {
            cmd.pic->BlitTo(target, cmd.x - offset, cmd.y);
        }
    }
}
