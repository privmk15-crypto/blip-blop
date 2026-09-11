#pragma once

#define APPAR_BLIP 0
#define FINI_BLIP 1
#define APPAR_BLOP 2
#define FINI_BLOP 3

class CharacterSelection {
    int et_phase_;
    int phase_;
    // Etap 4 (Full HD prep, fix): single scroll phase for the tiled
    // background (inter()[6]/[7], each a native-640-wide image). Used
    // to be two independently-tracked positions (x_back1_/x_back2_),
    // which was exactly right for a 640-wide screen (two 640-wide
    // tiles placed 640 apart give perfect, gapless coverage of a
    // 640-wide viewport) but leaves a periodically-visible gap on an
    // 854-wide one (2*640=1280 is wide enough in total, but the two
    // tiles' phase doesn't always align to cover [0, SCREEN_W)). See
    // draw() - now renders 3 tiles derived from this single phase,
    // which is enough to guarantee full coverage regardless of phase.
    int x_back1_;
    int y_select_;
    int x_name_;
    int y_name_;
    int step_;
    int pic_select_;
    int x_charac_;
    int y_charac_;

   public:
    enum class Output : int {
        Blip = 0,
        Blop = 1,
        Continue = 2,
    };
    CharacterSelection();
    Output update();
    void draw();
};
