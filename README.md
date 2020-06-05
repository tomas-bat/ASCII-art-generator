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

```

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
```

## Zadání programu ASCII-art generator
Program uživatel spustí a pomocí příkazů do konzole ho bude ovládat.
- `converter` spustí podprogram pro koverzi obrázků do ASCII-artu
- `animator` spustí podprogram, který zobrazí animaci z několika obrázků v ASCII-artu
- `editor` spustí podprogram pro jednoduchou editaci ASCII-art obrázků
- `help` zobrazí nápovědu (funguje v každém podprogramu)
- `quit` ukončí program

#### V podprogramu pro konverzi obrázků do ASCII-artu:

Konvertor potřebuje pro konverzi znát umístění složky, odkud bude načítat obrázky.
Pokud uživatel složku nastaví a program z ní načte validní obrázky, je schopen konvertovat. 
Pokud uživatel nezadá žádné další parametry pro konverzi a sputí ji, program překonvertuje
načtené obrázky ze složky v původním rozlišení (jeden pixel je reprezentován dvěma znaky)
a přizpůsobené světlému terminálu do ASCII-art podoby, které uloží do podsložky converted/ v původně
zadané složce. Uživatel může před konverzí zadat maximální šířku ve znacích,
poté budou všechny ASCII-art obrázky mít maximálně takovou šířku. Dále může uživatel před konverzí
zadat, zda chce ASCII-art obrázky přizpůsobit tmavému terminálu. Uživatel také může načíst
vlastní ASCII přechod ze souboru, poté bude program využívat pro konverzi tyto znaky.

Pokud formát obrázku podporuje průhlednost, tak budou všechny zcela průhledné pixely nastaveny
na bílou nebo černou podle toho, jak je nastavena inverze.

- `howto` zobrazí nápovědu, jak konvertovat obrázky
- `folder` se dotáže na umístění složky, odkud se obrázky budou načítat
- `width <num>` nastaví maximální šířku (ve znacích) pro konvertované obrázky, 0 ponechá původní velikosti
(výchozí nastavení)
- `invert true` nastaví inverzi konvertovaných obrázků, doporučeno pro tmavý terminál
- `invert false` zruší inverzi konvertovaných obrázků (výchozí nastavení), doporučeno pro světlý terminál
- `custom` se dotáže na umístění souboru, odkud má program načíst vlastní ASCII přechod
- `reset` obnoví všechna nastevní do výchozí hodnoty
- `convert` vytvoří v zadané složce podsložku s konvertovanými obrázky 
- `back` se vrátí zpět do menu programu

V podprogramu pro zobrazení animace:
- `howto` zobrazí nápovědu, jak zobrazovat animaci
- `folder` se dotáže na umístění složky, odkud se obrázky budou načítat
- `show` zobrazí animaci
- `back` se vrátí zpět do menu programu

V podprogramu pro jednoduchou editaci ASCII-art obrázků:
- `howto` zobrazí nápovědu, jak upravovat obrázek
- `location` se dotáže na umístění obrázku
- `show` zobrazí obrázek
- `brighten` obrázek zesvětlí
- `darken` obrázek ztmaví
- `negative` udělá z obrázku negativ
- `save` uloží obrázek místo původního obrázku
- `back` se vrátí zpět do menu programu

### Kde mám polymorfismus?
Polymorfismus využívám u různých formátů obrázků. Mám abstraktní třídu `Image`, ze které
dědí `ImageJPG` a `ImagePNG`, které se každé konvertují trochu jinak. Program má
jen skupinu obrázků typu `Image` a na nich volá konverzi.

Polymorfní volání je zatím v třídě `ConverterController`, která obsahuje
vector načtených obrázků jako unique pointery. Command `convert` při konverzi
neřeší, jakého je obrázek typu.
