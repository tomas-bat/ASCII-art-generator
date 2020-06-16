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
#### Program uživatel spustí a pomocí příkazů do konzole ho bude ovládat.

Obrazovka aplikace může vypadat například takto (dolar značí vstup uživatele):

```
Enter command:
$ width 100
Maximum ASCII image width will now be 100 characters.
Enter command:
$ load
Found: example.jpeg
Loaded 1 image(s) in total.
Enter command:
$ convert
Converting example.jpeg...
Converted to /lorem/ipsum/converted/example.jpeg.ascii
```

V hlavním menu aplikace uživatel může nastavit umístění složky, odkud se budou
načítat obrázky. To je jediná nutná informace pro konverzi obrázků. Volitelně poté
uživatel může specifikovat, zda chce vzhled ASCII obrázku přizpůsobit tmavému terminálu,
výchozí nastavení je totiž pro světlý. Dále také může načíst ze souboru vlastní ASCII
přechod, pokud nechce použít výchozí - stačí specifikovat cestu k souboru, ze kterého program
přečte první řádku. Všechna tato nastavení budou mít vliv na všechny podprogramy a zůstanou
uložena po celou dobu běhu aplikace.
- `folder` se dotáže na umístění složky, odkud se obrázky budou načítat
- `invert true` nastaví inverzi obrázků, doporučeno pro tmavý terminál
- `invert false` zruší inverzi obrázků (výchozí nastavení), doporučeno pro světlý terminál
- `custom` se dotáže na umístění souboru, odkud má program načíst vlastní ASCII přechod
- `converter` spustí podprogram pro koverzi obrázků do ASCII-artu
- `animator` spustí podprogram, který zobrazí animaci z několika obrázků v ASCII-artu
- `editor` spustí podprogram pro jednoduchou editaci ASCII-art obrázků
- `help` zobrazí nápovědu (funguje v každém podprogramu)
- `quit` ukončí program

#### V podprogramu pro konverzi obrázků do ASCII-artu:

Pokud uživatel specifikoval složku, odkud má program načítat obrázky, může si je nyní
nechat načíst, program poté zobrazí, které obrázky se mu podařilo načíst. Volitelně
může uživatel specifikovat maximální šířku (ve znacích) pro konvertované obrázky, či
si nechat maximální šířku nastavit podle šířky okna terminálu. Pokud uživatel maximální
šířku nezadá, nebo ji nastaví na 0, tak konvertované obrázky zachovají svojí původní
velikost (jeden pixel je reprezentován dvěma znaky). Nyní si uživatel může nechat
načtené obrázky překonvertovat. Obrázky se budou ukládat do složky "converted/", která
se vytvoří v původně zadané složce. Pokud chce uživatel resetovat všechna nastavení,
může tak v tomto podprogramu učinit, resetuje tím však i nastavení z hlavního menu
aplikace. Jakmile uživatel tento podprogram opustí, nastavení učiněná v tomto podprogramu
se zapomenou.

Pokud formát obrázku podporuje průhlednost, tak budou všechny zcela průhledné pixely nastaveny
na bílou nebo černou podle toho, jak je nastavena inverze.

- `howto` zobrazí nápovědu, jak konvertovat obrázky
- `load` načte obrázky ze zadané složky
- `match` nastaví maximální šířku (ve znacích) pro konvertované obrázky podle šířky terminálu
- `width <num>` nastaví maximální šířku (ve znacích) pro konvertované obrázky, 0 ponechá původní velikosti
(výchozí nastavení)
- `reset` obnoví všechna nastevní do výchozí hodnoty
- `convert` vytvoří v zadané složce podsložku s konvertovanými obrázky 
- `back` se vrátí zpět do menu programu

#### V podprogramu pro zobrazení animace:

Aby mohl uživatel pracovat s tímto podprogramem, musí nejdříve alespoň 1 obrázek pomocí
konverteru vytvořit. Poté uživatel může obrázky načíst a program řekne, které obrázky
se mu podařilo načíst. Volitelně může uživatel nastavit počet snímku za sekundu při
zobrazovaní animace (výchozí nastavení je 30 FPS), dále může volitelně prohazovat
pořadí snímků. Pokud chce zjistit, který snímek ja na kterém místě, může si to nechat
zobrazit. Poté si může nechat animaci zobrazit. Jakmile uživatel tento podprogram
opustí, nastavení učiněná v tomto podprogramu se zapomenou.

- `howto` zobrazí nápovědu, jak zobrazovat animaci
- `load` načte obrázky ze složky converted/
- `positions` zobrazí současnou pozici obrázků v animaci
- `swap <num> <num>` prohodí pořadí dvou zadaných obrázků v animaci
- `fps <num>` nastaví framerate animace
- `show` zobrazí animaci
- `back` se vrátí zpět do menu programu

#### V podprogramu pro jednoduchou editaci ASCII-art obrázků:

Aby mohl uživatel pracovat s tímto podprogramem, musí nejdříve alespoň 1 obrázek pomocí
konverteru vytvořit. Poté si může nechat vypsat, které obrázky může načíst. Jeden z nich
si uživatel vybere a nechá si ho načíst. Tento obrázek si může nechat zobrazit a upravovat,
konkrétně má možnost obrázek zesvětlit, ztmavit a udělat negativ.
- `howto` zobrazí nápovědu, jak upravovat obrázek
- `images` zobrazí obrázky, které jdou načíst
- `load <filename>` načte daný obrázek
- `show` zobrazí obrázek
- `brighten` obrázek zesvětlí
- `darken` obrázek ztmaví
- `negative` udělá z obrázku negativ
- `back` se vrátí zpět do menu programu


### Kde mám polymorfismus?

Polymorfismus využívám u různých formátů obrázků. Mám abstraktní třídu `Image`, ze které
dědí `ImageJPG` a `ImagePNG`, které se každé převádí do RGB trochu jinak. Program má
jen skupinu obrázků typu `Image` a na nich volá konverzi.

Polymorfní volání je v třídě `ConverterController`, která obsahuje
vector načtených obrázků jako unique pointery. Command `convert` při konverzi
neřeší, jakého je obrázek typu, protože u každého obrázku zavolá abstraktní metodu
`extract`.

Kdybych se rozhodl přidat podporu pro další typy obrázků, vytvořil bych jen
dalšího potomka třídy `Image` a definoval mu, jak se má převést do RGB.
