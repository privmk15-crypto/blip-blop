/******************************************************************
 *
 *		----------------
 *		 RenderQueue.h
 *		----------------
 *
 *		Collects RenderCommands during a frame's gameplay-side draw
 *		pass (once Sprite::affiche() and friends are migrated to push
 *		into one of these instead of calling SDL directly), for
 *		RenderSystem to execute afterward. A thin, ordered container -
 *		nothing more: Push() appends, Clear() empties it back out for
 *		reuse, commands() exposes the sequence to RenderSystem in the
 *		exact order it was built, which matters (painter's-algorithm
 *		draw order must be preserved - see the RenderSystem design
 *		analysis, point 1).
 *
 *		Deliberately SDL-free, same reasoning as render_command.h:
 *		only forward-declares Picture. Gameplay code that will
 *		eventually hold a RenderQueue& (passed down through
 *		affiche(RenderQueue&), per the migration plan - NOT done yet)
 *		never needs to see SDL to call Push().
 *
 *		Not wired into anything yet: no call site constructs, passes,
 *		or reads a RenderQueue anywhere in the codebase. This is step
 *		1 of the RenderSystem migration plan - an isolated, inert
 *		foundation, matching render_command.h/render_system.h.
 *
 ******************************************************************/

#pragma once

#include <vector>

#include "render_command.h"

class Picture;

class RenderQueue {
   public:
    void Push(int x, int y, const Picture* pic);
    void Clear();

    const std::vector<RenderCommand>& commands() const { return commands_; }

   private:
    std::vector<RenderCommand> commands_;
};
