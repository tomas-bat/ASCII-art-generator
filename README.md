# ASCII-art generator (téma ASCII-art)
Autor: Tomáš Batěk

## Téma z ProgTestu

Váš program:

1. z jednoho až n obrázků běžného formátu (BMP/SVG/RAW/TGA, ...) načte data a ty validně zobrazí v ASCII (odstíny šedi)
2. ze souboru načte definovaný ASCII přechod
umožňuje alespoň dvě jednoduché operace (zesvětlení/ztmavení obrázku, vymazání, konvoluce, negativ, ...)
3. umožnuje "spuštění" animace v případě více načtených obrázků a triviální editaci animace na útovní framů (např. mazání framů, seřazení za sebou, ...)
4. Program bude umět pracovat s minimálně jedním obrázkovým formátem.

Program bude mít jednoduché možnosti přehrávání animace (zastavit, spustit, zobrazit konkrétní frame, ...).

Kde lze využít polymorfismus? (doporučené)

- Nástroje pro manipulaci a jejich efekty, sady znaků, ...
- Formáty vstupu: BMP, SVG, RAW, ...
- Různé styly ASCII vykreslení
- Přehrávač: obrázek (jen zobrazí), sekvence (přehraje více obrázků)
- Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

                                              _.oo.
                      _.u[[/;:,.         .odMMMMMM'
                   .o888UU[[[/;:-.  .o@P^    MMM^
                  oN88888UU[[[/;::-.        dP^
                 dNMMNN888UU[[[/;:--.   .o@P^
               ,MMMMMMN888UU[[/;::-. o@^
                NNMMMNN888UU[[[/~.o@P^
                888888888UU[[[/o@^-..
               oI8888UU[[[/o@P^:--..
            .@^  YUU[[[/o@^;::---..
          oMP     ^/o@P^;:::---..
       .dMMM    .o@^ ^;::---...
      dMMMMMMM@^`       `^^^^
     YMMMUP^
      ^^

## Zadání programu ASCII-art generator

### Kde mám polymorfismus?
