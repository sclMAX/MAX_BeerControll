#ifndef BOMBASMANAGER_H
#define BOMBASMANAGER_H

#include "bomba.h"
#include "config.h"

Bomba bombaR(BOMBA_RECIRCULADO_PIN);
Bomba bombaW(BOMBA_WHIRPOLL_PIN);

void bombaROn() { bombaR.on(); }

void bombaROff() { bombaR.off(); }

void prenderBombaR()
{
    if ((bombaR.timePurgaOn > 0) && (bombaR.purgas > 0))
    {
        bombaR.on();
        int timeP = 0;
        for (int i = 0; i < bombaR.purgas; i++)
        {
            timeP += bombaR.timePurgaOn;
            Alarm.timerOnce(timeP, bombaROff);
            timeP += bombaR.timePurgaOff;
            Alarm.timerOnce(timeP, bombaROn);
        }
    }
    else
    {
        bombaR.on();
    }
}

void apagarBomba(Bomba &b)
{
    b.off();
}

#endif //BOMBASMANAGER_H