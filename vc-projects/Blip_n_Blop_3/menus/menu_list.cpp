#include "menu_list.h"

#include "../game_state.h"
#include "../globals.h"
#include "../lgx_packer.h"

int MenuList::ComputeWidth() const {
    int width = 0;

    for (const std::string& s : items_) {
        int tmp = g_game_state.font_bank().menu().width(s.c_str());

        if (tmp > width) {
            width = tmp;
        }
    }

    width += 60;
    width /= 2;

    if (width < 200)
        width = 200;
    else if (width > SCREEN_W / 2)
        width = SCREEN_W / 2;
    return width;
}

void MenuList::ShadeTextBox(SDL::Surface* surf) const {
    int ys = items_.size() * 15;
    // Compute the size of the "schnuff" (= thing) to darken
    //
    int width = ComputeWidth();

    Rect rec;
    rec.top = 220 - ys;
    rec.left = SCREEN_W / 2 - width;
    rec.bottom = 260 + ys;
    rec.right = SCREEN_W / 2 + width;

    LGXpaker.halfTone(surf, &rec);
}

void MenuList::Draw(SDL::Surface* surf) const {
    ShadeTextBox(surf);

    int y = 240 - items_.size() * 15;
    for (int i = 0; i < items_.size(); ++i) {
        if (focused_ == i)
            g_game_state.font_bank().menus().printC(surf, SCREEN_W / 2, y, items_[i].c_str());
        else
            g_game_state.font_bank().menu().printC(surf, SCREEN_W / 2, y, items_[i].c_str());

        y += 30;
    }
}
