
#include <iostream>
#include <string>
#include <sstream>
char bitsToDnsChar(char ch) {
    switch (ch) {
        case 0: return 'A';
        case 1: return 'C';
        case 2: return 'T';
        case 3: return 'G';
    }
}
std::string charToDnsSequence(char ch) {
    std::string s(4, '\0');
    for (unsigned j = 0; j < 4; ++j) {
        s[j] = bitsToDnsChar((ch >> 2*j) & 0x03);
    }
    return s;
}
std::string textToDns(const std::string& text) {
    std::stringstream ss;
    for (char ch : text) {
        ss << charToDnsSequence(ch);
    }
    return ss.str();
}
int main() {
    auto d=R"(A női mell anatómiája - önvizsgálata

mell anatómiája:

Az emlő a mellkasfalon, a szegycsont széle és az elülső hónaljvonal között elhelyezkedő mirigyes szerv. Alakját a változó mennyiségben lerakódott zsírszövet és a kötőszövet aránya határozza meg. Súlya 150-300 gramm, ez szoptatás alatt többszörösére növekedhet. Élettani jelenség, hogy a mellek ritkán egyformák, méretük eltér s ez az eltérés terhesség után fokozódhat. Az emlőt vékony bőr borítja, mely a bimbóudvar területén különböző fokban pigmentált, itt faggyú- és verejtékmirigyeket, ritkán szőrtüszőket is tartalmaz.


A bimbóudvar közepéből emelkedik elő a mellbimbó, melynek tetején pontszerű nyílással nyílnak az emlőmirigy kivezetőcsövei, a tejcsatornák. A mellbimbóban található sima izmok ingerlésre összehúzódnak és a bimbót kiemelik. Ilyen inger lehet a csecsemő szoptatása, a hideg, a szexuális izgalom.

A mell felépítésében három fő alkotórész játszik döntő szerepet:

- Mirigyszövet, ami 15-20 sugarasan elhelyezkedő lebenyből áll. Mérete nem terhes állapotban nem nagyobb, mint a bimbóudvar, szoptatás idején azonban jelentősen megnagyobbodik.
- Kötőszöveti állomány, mely az emlő támaszát adja, formáját biztosítja.
- Zsírszövet, amely a mirigyek és a kötőszöveti állomány közötti területet tölti ki, az életkor előrehaladtával mennyisége a mirigyek rovására növekszik.
E három alkotóelem aránya szabja meg a mellek méretét, alakját, feszességét, összességében egyéni jellemzőit.
Az emlőnek saját izomzata nincs, csupán a bőr tartja és a kötőszöveti állomány rögzíti a mellkasfalon. 
Az emlők vér- és nyirokellátása, valamint beidegzése igen gazdag. 
A nyirokelvezetés nagyrészt a hónalji nyirokcsomók felé történik.

A mell élettana:

Az emlőmirigyek működése a serdülőkortól a változás koráig hormonális befolyás alatt áll. Felnőtt nőn az emlő állománya a havi ciklus során folyamatosan változik a hormonhatásnak megfelelően. Ezért fontos például, hogy az emlő önvizsgálatát mindig a ciklus azonos időpontjában végezzük. A hormontermelést a központi idegrendszerben a hipotalamusz és az agyalapi mirigy szabályozza. Az emlő állományára a legfontosabb befolyást a petefészekben termelődő hormonok gyakorolják: az ösztrogén (tüszőhormon) és a progeszteron (sárgatesthormon).
Az ösztrogének serkentik a mirigyhám fejlődését, a bimbó növekedését, pigmentációjának fokozódását. Hatásukra a mell megnagyobbodik, feszessé, tömötté válik. A ciklus második felében sok nőnél panaszokat okozhat az emlő érzékenysége, duzzadása, ami az ösztrogén okozta folyadék-visszatartás következménye. 
A progeszteron csökkenti az ösztrogénhatást, elősegíti a tejcsatornák fejlődését, enyhíti a menstruációval összefüggő folyadék-visszatartást.
A két hormontípus egymást részben kiegészítve, részben gátolva szabályozza a mell működését.
Az agyalapi mirigyben termelődik a prolactin nevű hormon. A terhesség alatt és a szoptatáskor van jelentősége, a tejelválasztásért felelős.

A mell és a menstruációs ciklus:

A nők nagy része szinte naprakészen tudja követni ciklusának állapotát melleinek változásaiból.
A menzesz alatt és néhány nappal utána a két fő hormonfajta (az ösztrogének és a progeszteron) alacsony szinten állnak, ilyenkor a mellek duzzadása megszűnik, a mirigyek visszafejlődnek. Ez az időpont a legalkalmasabb a mellek önvizsgálatára, mivel ilyenkor az emlők jól áttapinthatóak. A ciklus 10. napja körül az ösztrogéntermelés fokozódik, a sejtek szaporodásnak indulnak, megkezdődik a mellek duzzadása.	
A tüszőrepedés után (28 napos ciklus esetén a 14. nap) a két hormonfajta együttes hatására a mirigyek felszaporodnak, megnagyobbodnak. Ilyenkor feszül a mell legjobban, ekkor a legérzékenyebb. Amennyiben terhesség nem jött létre a ciklus során, menstruáció következik, és a körforgás kezdődik előlről.
 

A mellek szépsége:

Mint említettük, a mellkasfalon az emlőket csupán a bőr tartja, állományukat rugalmatlan kötőszöveti rostok szövik át, melyek az élet során kitágulnak, megereszkednek. A mellek ezáltal - a gravitáció miatt - hajlamosak a süllyedésre. Ezt kivédeni csupán melltartóval lehet, melynek viselése a serdülőkor végétől ajánlott. A melltartót úgy kell megválasztani, hogy alkalmazkodjék a mellek nagyságához, kényelmes - lehetőleg fém merevítő nélküli és nem szoros legyen, de a melleket jól tartsa. Különösen fontos a melltartó viselése sportolás közben, terhesség, szoptatás, menstruáció és fogyókúra alatt. 

A melleket fedő bőr rugalmassága egészséges életmóddal tovább megőrizhető. Minden, ami a női szépséget egyébként is károsítja: a helytelen táplálkozás, a dohányzás, mértéktelen kávé- és alkoholfogyasztás, a forró fürdők, a túlzásba vitt napozás, szolárium a bőr rugalmasságát csökkenti, így az emlők megereszkedését okozhatja.
Az úszás, mivel fejleszti a hát- és a mellizmokat, jótékony hatású a mellek formájára.
Fogyókúra idején a zsírszöveti állomány testszerte kevesebb lesz, és ez sajnos az emlőben található zsírszövetre is érvényes. Nagyobb mérvű fogyás esetén várható, hogy az emlő állománya csökkenni fog és tartása is romlik. Különösen fontos ilyenkor a melltartó viselése mellett a sportolás és az úszás. 

Árt-e a szoptatás a melleknek?

A terhesség és a szoptatás során az emlők mérete rendkívül megnövekszik, a mirigyállomány erőteljes szaporodásnak indul. A mell növekedését a bőr sokszor nem tudja követni, felületén csíkok keletkeznek. A szoptatás befejezése után a mirigyállomány kevesebb lesz, helyét zsírszövet foglalja el. Ezek a változások teljesen egyéniek. Megelőzésükben segíthet a megfelelő szoptatás alatt speciális szoptatós-melltartó viselése, a mell bőrének ápolása a nagy számban rendelkezésre álló, bőrgyógyászatilag ajánlott krémekkel.	

A szoptatás során kialakuló esetleges esztétikai hátrányok azonban nem mérhetőek az anyatejes táplálás semmivel nem pótolható hatásához, mely az újszülött fejlődéséhez elengedhetetlen, az anya-gyermek kapcsolat kialakulásában döntő jelentőségű.


A fogamzásgátló tabletták hatása a mellekre:

A kombinált fogamzásgátló tabletták ugyanazt a két hormont - az ösztrogént és a progeszteront - tartalmazzák szintetikus formában, amelyek az emlőre élettani körülmények között is hatást gyakorolnak. Nem meglepő tehát, hogy a tablettaszedés során az emlőállomány bizonyos változásai jelentkezhetnek. 
A magasabb ösztrogéntartalmú, vagy ösztrogéntúlsúlyos tabletták hatására az emlő térfogata megnövekszik, tapintásra érzékennyé, fájdalmassá válhat. A jelenség főleg a tablettaszedés első néhány hónapjában fordul elő, később általában magától megszűnik.	
A progeszteronban gazdagabb tabletták ellenkező hatást váltanak ki.
Amennyiben az emlőpanaszok tartósan fennállnak, akkor sem kell lemondani a tablettás fogamzásgátlásról! Kérd nőgyógyászod segítségét, mivel ilyenkor érdemes alacsonyabb ösztrogéntartalmú tablettára áttérni. A mai korszerű tabletták, amelyekben az ösztrogéntartalom minimális, már igen ritkán okozzák e kellemetlen mellékhatást, ugyanakkor fogamzásgátló hatásuk biztonsága kiváló. A fogamzásgátló tabletták tartós alkalmazása védőhatást fejt ki az emlő jóindulatú megbetegedéseivel szemben. Ilyen megbetegedés a fibrocisztás emlőbetegség (masztopátia) és a fibroadenoma. 2-4 éves tablettaszedést követően a hatás már kimutatható.

A védő hatás valószínűleg a tablettákban levő sárgatesthormonnak (progeszteron) köszönhető. Sajnos, nem igazolták, hogy a tablettának az emlő rosszindulatú betegségeire is védő hatása lenne. Évtizedekig tartó, nagy beteglétszámú vizsgálatok után a kérdés mindmáig nem eldöntött. Jelenlegi tudomásunk szerint a fogamzásgátlót szedő nőknél minimálisan nagyobb az emlőrák kockázata, mint tablettát nem szedő kortársaiknál. A fogamzásgátló szedésének abbahagyása után 10 év alatt megszűnik ez a csekély különbség. Nem ismert, hogy valóban a készítmény okozza-e az emlőrák gyakoriságának kismértékű növekedését. Figyelembe kell venni azt is, hogy a tablettaszedő nők gyakrabban járnak nőgyógyászati ellenőrzésre, így esetükben a daganat felfedezésének esélyei is nagyobbak.

A mell önvizsgálata

A mell önvizsgálatát közvetlenül a menstruáció után célszerű végezni. Ilyenkor az emlők jól áttapinthatóak, nem érzékenyek. Fontos, hogy rendszeresen, minden hónapban azonos időben végezzük az önvizsgálatot. A vizsgálat megtekintésből és tapintásból tevődik össze.
1. Az emlők megtekintése a tükörben:
Vetkőzz le derékig, állj vagy ülj erős fényben a tükör elé. A mellek megtekintésekor ne feledd, hogy az emlők sosem teljesen egyformák.

Mire kell figyelni?
- Látsz-e változást melleid méretében, alakjában?
- Van-e változás az emlőbimbókon, a bimbóudvarban?
- Van-e vérzés vagy váladékozás valamelyik emlőbimbóból? 
- Vannak-e szokatlan bőrelváltozások, behúzódások, kiemelkedések
a melleiden?
- Van-e eddig nem észlelt, esetleg előemelkedő érrajzolat a melleken?

A fenti kérdésekre a választ a tükörben találod meg a következő módon:
1. Lógasd le lazán a karjaidat, tekintsd meg a melleidet.
2. Emeld fel karjaidat a fejed fölé, miközben egyik oldalról a másikra fordulsz, kövesd a mellek kontúrjának változásait különböző szögekből megtekintve azokat.
3. Enyhén préseld össze a mellbimbókat nincs-e vérzés, váladékozás belőlük?

 

Az emlő áttapintása:

1. Feküdj kényelmesen hanyatt, fejed alatt egy párnával. A vizsgálandó oldalon emeld ki lapockádat egy összehajtott törölközővel, így könnyebben tapinthatod át a melled. A mellek vizsgálata az ellenoldali kézzel történjen, az éppen nem használt kezed tedd a fejed alá.

2. Összezárt ujjaid egész alsó felületét használd a tapintáshoz, ne csak az ujjbegyeket. A tapintást a kulcscsonttól kezdd, lefelé haladva. Ujjaid körkörösen mozogjanak egy képzeletbeli, szűkülő spirál mentén, melynek középpontja, ezáltal a tapintási művelet végpontja a mellbimbó. Vigyázz, egyetlen terület se maradjon ki a vizsgálat során!

3. Ha mindkét melled áttapintottad, hasonló mozdulatokkal tapintsd át a hónaljakat, a hónaljmélyedéstől indulva, a mellek irányában haladva.
A 3 kép közti különbség abban van, hogy a felőlünk levő mellet a másik kezével hol fogja:

 
Amennyiben a vizsgálat során eddig nem észlelt csomót, tömörülést tapintanál, akár a mellben, akár a hónaljárokban, illetve bármilyen egyéb elváltozást fedeznél fel, fordulj nőgyógyász kezelőorvoshoz!)";
    std::cout << textToDns(d);
}
