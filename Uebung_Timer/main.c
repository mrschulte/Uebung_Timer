/**
 Ersteller:          Marc-Rafael Schulte
 Beschreibung:       Übung_Timer
 Letzte Änderung :   Montag, 22.02.2021
**/

#include <avr/io.h>
#include "../Library/myLib.h"
#include "../Library/USART_SerielleSchnittstelle.h"

int main(void)
{

    /// 16Mhz/1024 = 15625 -> 1/15625 = 0.000064s = 0.064ms (so lange braucht ein Zählvorgang)
    /// 500ms / 0.064ms = 7812.5 ( Anzahl der Zählvorgänge )
    /// 7812.5 / 256 = 30.5 ( Da das 8-Bit Register nur bis 256 zählen kann, muss es mehrere Durchgänge machen - 30.5 )
    /// 30.5 geht nicht, deswegen nur 30 mit kleinem Fehler


    char str[]="Hallo";
    TCCR0B |= 0x05;
    uint8_t zaehler = 0;
    init_usart();

    while(1)
    {
        TCNT0 = 0;
        while(!(TIFR0 & (1<<TOV0)));
        TIFR0 |= 1<<TOV0;
        zaehler++;

        if(zaehler == 30)  ///Müsste 30.5 sein -> ein kleiner Fehler ist vorhanden
        {
            _puts(str);
            _putch(10);
            zaehler = 0;
        }

    }

    return 0;
}
