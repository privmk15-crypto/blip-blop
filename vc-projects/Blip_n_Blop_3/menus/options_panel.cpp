#include "options_panel.h"

#include <algorithm>

#include "../config.h"
#include "../control_alias.h"
#include "../input.h"
#include "../txt_data.h"
#include "txt_defines.h"

#include "../dd_gfx.h"

OptionsPanel::OptionsPanel() {
    vsync_on_txt_ = txt_data[TXT_VSYNC] + " " + txt_data[TXT_ON];
    vsync_off_txt_ = txt_data[TXT_VSYNC] + " " + txt_data[TXT_OFF];

    items_.AddEntry("VSYNC");
    items_.AddEntry(txt_data[TXT_FULLSCREEN]);
    // txt_data[TXT_MUSICVOL]/[TXT_SOUNDVOL] (812/813) exist in
    // data/uk.dat but are blank entries - nothing was ever written
    // there. Hardcoded here instead, same as "VSYNC" just above (for
    // the same reason: no usable localized string to pull from).
    items_.AddEntry("MUSIC VOLUME");
    items_.AddEntry("SFX VOLUME");
    items_.AddEntry(txt_data[TXT_P1KEYS]);
    items_.AddEntry(txt_data[TXT_P2KEYS]);
    items_.AddEntry(txt_data[TXT_RETURN]);
    RefreshVsync();
    RefreshMusicVolume();
    RefreshSfxVolume();
}

void OptionsPanel::RefreshVsync() {
    items_.ChangeEntry(0, vSyncOn ? vsync_on_txt_ : vsync_off_txt_);
}

// 0-255 internally (matches FMOD's own volume range), shown as 0-100%
// and stepped in the menu by roughly 10% per LEFT/RIGHT press.
static const int kVolumeStep = 26;

void OptionsPanel::RefreshMusicVolume() {
    items_.ChangeEntry(2, "MUSIC VOLUME " +
                               std::to_string(music_volume * 100 / 255) + "%");
}

void OptionsPanel::RefreshSfxVolume() {
    items_.ChangeEntry(3, "SFX VOLUME " +
                               std::to_string(sfx_volume * 100 / 255) + "%");
}

int OptionsPanel::ProcessEvent() {
    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        items_.MoveUp();
    } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        items_.MoveDown();
    }

    bool left = in.scanKey(DIK_LEFT) || in.scanAlias(ALIAS_P1_LEFT);
    bool right = in.scanKey(DIK_RIGHT) || in.scanAlias(ALIAS_P1_RIGHT);

    // Fix: this used to toggle VSYNC on LEFT/RIGHT unconditionally, no
    // matter which item was focused - pressing LEFT/RIGHT while on
    // Fullscreen or P1/P2 Keys silently flipped VSYNC in the
    // background. Needed fixing anyway to add volume (LEFT/RIGHT on
    // those items must adjust volume, not touch VSYNC).
    if (left || right) {
        switch (items_.focused()) {
            case 0:
                vSyncOn = !vSyncOn;
                RefreshVsync();
                break;
            case 1:
                fullscreen = !fullscreen;
                DDToggleFullscreen();
                break;
            case 2:
                music_volume = right ? std::min(255, music_volume + kVolumeStep)
                                      : std::max(0, music_volume - kVolumeStep);
                apply_volume_settings();
                RefreshMusicVolume();
                break;
            case 3:
                sfx_volume = right ? std::min(255, sfx_volume + kVolumeStep)
                                    : std::max(0, sfx_volume - kVolumeStep);
                apply_volume_settings();
                RefreshSfxVolume();
                break;
        }
    }

    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        switch (items_.focused()) {
            case 0:
                vSyncOn = !vSyncOn;
                RefreshVsync();
                break;
            case 1:
                fullscreen = !fullscreen;
                DDToggleFullscreen();
                break;
            case 4:
                return MenuType::Keys_1;
            case 5:
                return MenuType::Keys_2;
            case 6:
                return MenuType::Main;
        }
    }
    return MenuType::Options;
}
