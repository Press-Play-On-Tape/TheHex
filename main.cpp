#include "Pokitto.h"
#include <LibAudio>
#include "src/utils/GameCookie.h"
#include "src/HexBlocks.h"
#include "src/utils/PicoMod.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookie cookie;

Audio::Sink<2, PROJ_AUD_FREQ> audio;

int main(){
    
    cookie.begin("Hex", sizeof(cookie), (char*)&cookie);

    PC::begin();
    PD::loadRGBPalette(palettePicoMod);  
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(60);
    PD::setFont(fontC64);
    PD::textWrap = false;

    PD::adjustCharStep = -1;


    // Has the cookie been initialised?

    if (cookie.initialised != COOKIE_INITIALISED) {

        cookie.initialise();

    }

    game.setup(&cookie);
    
    while( PC::isRunning() ){

        if (!PC::update()) continue;
        game.loop();

    }
    
    return 0;
}
