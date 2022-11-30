#include "LCD.h"

using namespace drivers;

void drivers::setup_LCD(tContext* pContext){
    cfaf128x128x16Init();

    GrContextInit(pContext, &g_sCfaf128x128x16);
    
    GrFlush(pContext);
    GrContextFontSet(pContext, g_psFontFixed6x8);

}
