
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
std::vector<const char*>m={R"( a )",R"(√°s)",R"( me)",R"(√©s)",R"(√°l)",R"(t√°)",R"(√)",R"(z eml≈ë)",R"(≈)",R"(√°n)",R"( k√)",R"( √∂sztrog√©n)",R"(en )",R"(≈ë )",R"( tablett)",R"( sz)",R"(s√©)",R"(ek )",R"(√∂ve)",R"(sze)",R"(, a)",R"(√©r)",R"(sz√)",R"( v√)",R"( fe)",R"(mirigy)",R"(gy )",R"(tart)",R"(√ºl)",R"(√°r)",R"(t√©)",R"(hormon)",R"(bimb√≥)",R"(an )",R"(. A )",R"( nem )",R"(t, )",R"(nak)",R"(
A )",R"(ala)",R"(, m)",R"( te)",R"(√©t)",R"(n a)",R"(gy√)",R"( el)",R"(tt )",R"(k, )",R"(ele)",R"( le)",R"( al)",R"( ciklus)",R"(z√©)",R"(ont)",R"(len)",R"(agy)",R"( egy)",R"(≈ër)",R"(d≈ë)",R"(√©k)",R"(n, )",R"(l√°)",R"(k a)",R"(j√°)",R"( t√)",R"( ki)",R"(√©l)"};
char bitsToDnsChar(char c){return "ACTG"[c];}
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
std::string compressedToText(const std::string& compressed) {
    std::stringstream ss;
    for (char ch : compressed) {
        if ((unsigned char)ch > 188) {
            ss << m[(unsigned char)ch - 189];
        } else {
            ss << ch;
        }
    }
    return ss.str();
}
int main() {
    auto d=R"(A n≈ëiøll anat√≥mi√°ja - √∂nvizsg¡ata

mell anat√≥mi√°ja:

AƒΩmellkasfalon,Ω–gycsÚÃˇe ¿ azÍŸs h√≥naljvonal«∂z√∂ttÍhelyezked ÷esÃerv. Alak¸tΩv¡toz√≥ønnyiÕgb…lerak√≥doÎzs√≠rszœt ¿Ωk√∂t≈ëszœt ar∆ya ha¬rozzaøg. S√∫lya 150-300 gramm, ezÃoptatæ ‰Ît√∂bb”∂r√∂Õre nœkedhet. √âlettani jÌnÕg, hogyΩmellŒritk∆ıform√°kÂ“et√ºkÍt“ s ez azÍt“¿ÊrhesÕg u¬n fokoz√≥dhat. Aƒt‘©kony bˆ bor√≠tja,ølyΩ›udvarÊrŸe€n«ºl√∂nb√∂z fokbﬁpigment¡·iÎfagÈ∫- ¿ verej€k÷eke·ritk∆Ãˆt√ºsz≈ëket is ÿalmaz.

„›udvar«∂zep√©b≈ël emelkedikÍ≈ëΩmell›,ølynŒtetej√©n pÚ–r≈± ny√≠læsal ny√≠l‚ aƒ÷˛vezet≈ëcsœi,Ωtejcsatorn√°k. Aøll›bﬁtal¡hat√≥ sima izmok ingerl¿re √∂s–h√∫z√≥d‚ ¿Ω›t˛emelik. Ily…ingerÓhetΩcsecsem szoptatæa,Ωhideg,Ω–xu¡is izgalom.

Aøll’l√©p√≠t¿√©b…h⁄om f alkot√≥r¿z ¸tszik d√∂nt –repet:

- Mirigyszœt—mi 15-20 sugarasﬁelhelyezked lebenyb≈ël ¡l. M“ete‡terhes ¡lapotbﬁnem nÙobbÂintΩ›udvar,Ãoptatæ idej√©ËzonbﬁjÌnt≈ësenøgnÙobbodik.
- K√∂t≈ëszœti ¡lom∆y,øly aƒ ¬ma”°t adja, form√°¸t biztos√≠tja.
- Zs√≠rszœt—melyΩ÷Œ¿Ωk√∂t≈ëszœti ¡lom∆y«∂z√∂ttiÊrŸetet˝∂lti˛—z ˇetkorÍˆeh‰d¬valønnyiÕgeΩ÷Œrovæ⁄a nœkszik.
E h⁄omÔkot√≥Ìm ar∆yaÃabjaøgΩmellŒm“e€t—lak¸t,’–sÕg√©·√∂s–sÕg√©b…eÈ©ni jellemz≈ëit.
AƒnŒsa¸t izomzata nincs, csup∆Ωbˆ ÿja ¿Ωk√∂t≈ëszœti ¡lom∆y r√∂gz√≠tiΩmellkasfalon. 
Aƒk v“- ¿ nyirokel˙tæa, v‰mint beidegz¿e ig…gazdag. „nyirokelvezet¿ nÙr¿ztΩh√≥nalji nyirokcsom√≥k’l√©˝∂r€nik.

Aøll ˇettana:

Aƒ÷Œm≈±k√∂d¿eΩserdŸ≈ëkort√≥lΩv¡tozæ kor√°ig ‹¡is befolyæ ‰Î¡l. Feln≈ëÎn≈ëËƒ ¡lom∆yaΩhavi sor∆ folyamatosﬁv¡tozikΩ‹hatæ‚øgfÌl≈ëen. Ez“t fÚos pˇd√°ul, ho◊aƒ √∂nvizsg¡a¬t mindigΩciklus azonos i˜pÚ¸ban‘©gezz√ºkﬂ‹termel¿tΩk√∂zpÚi idegrend–rbenΩhipot‰musz ¿ az Ù‰pi ÷Ãab¡yozza. Aƒ ¡lom∆y⁄aΩlegfÚosabb befolyætΩpetef¿zekb…termel≈ëd ‹ok gyakorol¸k: az» (t√ºsz≈ë‹) ¿Ωprogeszteron (s⁄gatest‹).
Az»ŒserkentikΩ÷h√°m’jl≈ëd¿Á,Ω› nœked¿√©·pigmen¬ci√≥j∆ak fokoz√≥dæ√°t. HatæukraΩmelløgnÙobbodik,’–sÕ,˝∂m√∂t€ v¡ikﬂciklus mæodik’l√©b…sok n≈ënˇ panaszokat okozhat aƒ “ÒkenyÕge, duzzadæa—mi az» okozta folyad¯-visszaÿæ«∂vetkezm√©nye. „progeszteron cs√∂kkenti az»hatæ·el≈ëseg√≠tiΩtejcsatorn√°k’jl≈ëd¿√©·enyh√≠tiΩmenstru√°ci√≥val √∂s–f√ºgg folyad¯-visszaÿæt.
A«©t ‹t√≠pusımæt r¿zb…kieg¿z√≠tve, r¿zb…g√°tolvaÃab¡yozzaΩmell m≈±k√∂d¿Á.
Az Ù‰pi ÷b…termel≈ëdikΩprolactin nev≈± ‹ﬂterhesÕg ‰Î¿Ωszoptatækor vﬁjÌnt≈ëÕge,Ωtejelv¡asztæ“t’lel≈ës.

Aøll ¿Ωmenstru√°ci√≥s:
„n≈ëk na◊r¿zeÃinte naprak¿z…tudja«∂vetni∆ak ¡lapo¬tølleinŒv¡tozæaib√≥l.
Aønzesz ‰Î¿ n√©h∆y nappal u¬naΩkÁ f ‹fajta (az»Œ¿Ωprogeszteron) ‰csonyÃint…¡l‚, ilyenkorΩmellŒduzzadæaøgsz≈±nik,Ω÷Œvisszafejl≈ëdnek. Ez az i˜pÚΩlegalkalmasabbΩmellŒ√∂nvizsg¡a¬raÂivel ilyenkor aƒk j√≥l √°ttapinthat√≥akﬂciklus 10. napja«∂rŸ az»termel¿ fokoz√≥dik,ΩsejtekÃaporodæ‚ indul‚,øgkez˜dikΩmellŒduzzadæa.	„t√ºszˆeped¿ u¬n (28 napos ese€nΩ14. nap)ΩkÁ ‹fajta eÈºttes hatæ⁄aΩ÷Œfelszaporod‚,øgnÙobbod‚. Ilyenkor’”ºlΩmellÓgjobba˘ekkorΩleg“Òkenyebb. Amennyib…terhesÕg‡j√∂ÎlÁreΩciklus sor∆,ønstru√°ci√≥«∂vetkeziÏ¿Ωk√∂rforgæ kez˜dikÍ≈ëlr≈ël.
 

AøllekÃ√©pÕge:

Mint eml√≠tett√ºk,ΩmellkasfaloËƒket csup∆Ωbˆ ÿja, ¡lom∆yukat rugalmatlan«∂t≈ëszœti rostokÃ√∂vik √°t,ølyŒaz ˇet sor∆˛¬gul‚,øgereszkednek. AøllŒez¡tal -Ωgravi¬ci√≥ miaÎ- hajlamosakΩsŸlyed¿re. Ezt˛v√©deni csup∆øllÿ√≥valÓhet,ølynŒvisel¿eΩserdŸ≈ëkor‘©gÁ≈ël aj∆lott. Aøllÿ√≥t √∫◊kelløgv¡asztani, ho◊alkalmazkodj¯ΩmellŒnÙs√°g√°hoz,«©nyelmes -Óhet≈ëleg f√©mørev√≠t nˇkŸi ¿ nemÃorosÓgye˘deΩmelleket j√≥l ÿsa. KŸ√∂n√∂s…fÚosΩmellÿ√≥ visel¿e sportolæ«∂zben,ÊrhesÕg,Ãoptatæ,ønstru√°ci√≥ ¿ foÈ≥k√∫ra ‰tt. 

Aølleket’d bˆ rugalmass√°ga eg¿zÕges ˇetm√≥ddal tov√°bbøgˆizhet≈ë. Minden—miΩn≈ëiÃ√©pÕget eÈ©bk√©nt is«°ros√≠tja:Ωhelytel…¬pl¡kozæ,Ωdoh∆yzæÂ“€ktÌn«°v√©- ¿Ôkoholfogyasztæ,Ωforr√≥ f√ºr˜k,Ωt√∫lzæba viÎnapozæ,Ãol⁄iumΩbˆ rugalmass√°g√°t cs√∂kkenti, √≠◊aƒkøgereszked¿Á okozhatja.
Az √∫szæÂivel’jlesztiΩh√°t- ¿Ωmellizmoka·j√≥€kony hatæ√∫ΩmellŒform√°j⁄a.
FoÈ≥k√∫ra idej√©nΩzs√≠rszœti ¡lom∆yÊst–rte kevesebbÓsz, ¿ ez sajnos aƒb…tal¡hat√≥ zs√≠rszœtre is “v√©nyes. NÙobb m“v≈± fogyæ ese€n‘°rhat√≥, ho◊aƒ ¡lom∆ya cs√∂kkenni fog ¿ ÿæa is romlik. KŸ√∂n√∂s…fÚos ilyenkorΩmellÿ√≥ visel¿eøllettΩsportolæ ¿ az √∫szæ. 

√Årt-eΩszoptatæΩmelleknek?
„terhesÕg ¿Ωszoptatæ sor∆ aƒk m“ete rendk√≠vŸøgnœkszik,Ω÷¡lom∆y er≈ëteljesÃaporodæ‚ indul. Aøll nœked¿ÁΩbˆ sokszor‡tudja«∂vetni,’lŸe€n cs√≠kok kÌtkeznek. AÃoptatæ befejez¿e u¬nΩ÷¡lom∆y kevesebbÓsz, helyÁ zs√≠rszœt foglaljaÍ. EzekΩv¡tozæokÊljes…eÈ©niek. Megel≈ëz¿√ºkb…seg√≠thetΩmegfÌl szoptatæ ‰Îspeci¡isÃoptat√≥s-mellÿ√≥ visel¿e,Ωmell bˆ√©nŒ√°polæaΩnÙÃ√°mbﬁrendelkez¿re ¡l√≥, bˆÈ≥gyæzatilag aj∆loÎkr√©mekkel.	

AÃoptatæ sor∆˛‰kul√≥ esetleges esz€tikai h√°tr∆yo˚zonbﬁnem m“het≈ëŒaz anyatejes ¬pl¡æ semmivel‡p√≥tolhat√≥ hatæ√°hoz,øly az √∫j”ºl√∂tt’jl≈ëd¿√©hezÍengedhetetÛ—z anya-gyermŒkapcsolat˛‰kulæ√°bﬁd√∂nt jÌnt≈ëÕg≈±.

„fogamzæg√°tl√≥ tablet¬k hatæaΩmellekre:
„kombin¡t fogamzæg√°tl√≥ tablet¬k ugyanaztΩkÁ ‹t - az»t ¿ΩprogeszterÚ - ÿalmazz√°kÃintetikus form√°ban—melyŒaƒre ˇettani«∂rŸm√©nyek«∂z√∂Îis hatæt gyakorol‚. Nemøglep teh√°·hogyΩtabletta–d¿ sor∆ aƒ¡lom∆y bizonyos v¡tozæai jÌntkezhetnek. „magasabb»ÿalm√∫, vÙ»t√∫ls√∫lyos tablet¬k hatæ⁄a aƒ t“fogataøgnœksziÏtapintæra “Òkenny√©, f√°jdalmass√° v¡hatﬂjÌnÕg f≈ëlegΩtabletta–d¿Ís n√©h∆y h√≥nap¸bﬁfordulÍ≈ë, k¿≈ëbb ¡ta˙bﬁmag√°t√≥løgsz≈±nik.	„progeszteronbﬁgazdagabb tablet¬kÍÛkez hatæt v¡ta‚˛.
Amennyib…aƒpanaszok ÿ√≥san’nn¡l‚—kkor sem kellÓmondaniΩtablettæ fogamzæg√°tlær√≥l! K“d n≈ëÈ≥gyæzod seg√≠tÕg√©·mivel ilyenkor “demes ‰csonyabb»ÿalm√∫ tablet¬ra √°tt“niﬂmai kor–r≈± tablet¬k—melyekb…az»ÿalom minim¡isÂ⁄ ig…ritk∆ okozz√°k e kellemetÛøll¯hatæ·ugya‚kor fogamzæg√°tl√≥ hatæuk biztons√°ga˛v¡√≥ﬂfogamzæg√°tl√≥ tablet¬k ÿ√≥sÔkalmazæa‘©˜hatæt’jt˛ aƒ j√≥indulat√∫øgbeteged¿eivelÃemben. Ilyenøgbeteged¿Ωfibrocisztæ eml≈ëbetegÕg (masztop√°tia) ¿Ωfibroadenoma. 2-4 √©vesÀa–d¿t«∂vet≈ëenΩhatæ m⁄˛mutathat√≥.

A‘©d hatæ val√≥”≠n≈±legΩtablet¬kbﬁlev s⁄gatest‹‚ (progeszteron)«∂”∂nhet≈ë. Sajnos,‡igazol¬ÏhogyΩtablet¬‚ aƒ rosszindulat√∫ betegÕgeire is‘©d hatæaÓnne. √âvtizedekig ÿ√≥, na◊beteglÁ”°m√∫ vizsg¡atok u¬nΩk“d¿ mindm√°ig‡eld√∂nt√∂tt. JÌnlegi tudomæunkÃerintΩfogamzæg√°tl√≥tÃed n≈ëknˇ minim¡isﬁnÙobb aƒr√°k kock√°zataÂint tablet¬t nemÃed kor¬rsaikn¡ﬂfogamzæg√°tl√≥Ãed¿√©nŒabbahÙæa u¬n 10 √©v ‰ttøgsz≈±nik ezΩcsekˇy«ºl√∂nbÕg. Nem ismer·ho◊val√≥banΩk¿z√≠tm√©ny okozza-e aƒr√°k gyakoris√°g∆ak˛sm“€k≈± nœked¿Á. FigyÌmbe kell venni azt is, hogyΩtabletta–d n≈ëk gyakrabbﬁj⁄‚ n≈ëÈ≥gyæzatiÍÛˆz¿re, √≠◊eset√ºkbenΩdaganat’lfedez¿√©nŒeÕlyei is nÙobbak.

Aøll √∂nvizsg¡ata

Aøll √∂nvizsg¡a¬t«∂zvetÛŸΩmenstru√°ci√≥ u¬n cˇ–r≈±‘©gezni. Ilyenkor aƒk j√≥l √°ttapinthat√≥ak,‡“Òkenyek. FÚos, ho◊rend–resenÂind…h√≥napbﬁazonos i˜b…v√©gezz√º˚z √∂nvizsg¡atotﬂvizsg¡atøgtekint¿b≈ël ¿ tapintæb√≥lÊv≈ëdik √∂s–.
1. Aƒkøgtekint¿eΩt√ºk√∂rben:
Vetk≈ëzzÓ der¯ig, ¡lj va◊Ÿj er≈ës f√©nybenΩt√ºk√∂rÍ√©. Aøllekøgtekint¿ekor ne’ledd, ho◊aƒk sosemÊljes…egyform√°k.

Mire kell figyelni?
- L√°tsz-e v¡tozætølleid m“e€ben—lak¸ban?
- Van-e v¡tozæ aƒ›kon,Ω›udvarban?
- Van-e v“z¿ va◊v¡ad¯ozæ v‰melyik eml≈ë›b√≥l? 
- Van‚-eÃokatlﬁbˆelv¡tozæoÏbeh√∫z√≥dæoÏkiemelked¿ek
aølleiden?
- Van-e eddig‡¿zlel·esetlegÍ≈ëemelked “rajzolatΩmelleken?

A’nti«©rd¿ekreΩv¡asztΩt√ºk√∂rb…tal¡odøgΩkœtkez m√≥don:
1. L√≥gasdÓ laz∆Ωkarjaida·tekintsdøgΩmelleidet.
2. Emeld’l karjaidatΩfejed f√∂l√©Âik√∂zb…egyik oldalr√≥lΩmæikra fordulsz,«∂vesdΩmellŒkÚ√∫rj∆ak v¡tozæait«ºl√∂nb√∂z ”∂gekb≈ëløgtekintve azokat.
3. Enyh√©n pr¿eld √∂s–Ωmell›kat nincs-e v“z¿, v¡ad¯ozæ bel≈ël√ºk?

 

Aƒ √°ttapintæa:

1. Fek√ºdj«©nyelmes…hanyatt,’jed ‰Îe◊p⁄n√°valﬂvizsg¡and√≥ oldalon emeld˛ lapock√°dat e◊√∂s–hajtoÎt√∂r√∂lk√∂z≈ëvel, √≠gy«∂nnyebb…tapinthatod √°tΩmelled. AøllŒvizsg¡ata azÍÛoldali«©zzel˝∂r€njen—z √©pp…nem haszn¡t kezedÊddΩfejedÔ√°.

2. √ñs–z⁄t ujjaid eg¿zÔs√≥’lŸe€t haszn¡dΩtapintæhoz, ne csa˚z ujjbegyeketﬂtapintætΩkulcscsÚt√≥l kezdd,Ófel√© h‰dva. Ujjaid«∂rk√∂r√∂s…mozogja‚ı«©pzÌtbeli,Ã≈±kŸ spir¡øn€n,ølynek«∂ÒppÚja, ez¡talΩtapintæi m≈±vÌt‘©gpÚjaΩmell›. ViÈ°zz,ıetl…terŸet se maradjon˛Ωvizsg¡at sor∆!

3. Ha mindkÁølled √°ttapintottad, hasonl√≥ mozdulatokkal tapintsd √°tΩh√≥naljakat,Ωh√≥naljmˇyed¿t≈ël indulva,ΩmellŒir∆y√°bﬁh‰dva.„3«©p«∂zti«ºl√∂nbÕg abbﬁva˘hogyΩfel≈ël√ºnkÓv≈ëølletΩmæik keÒvel hol fogja:

 
AmennyibenΩvizsg¡at sor∆ eddig‡¿zlelt csom√≥·t√∂m√∂rŸ¿t tapintan¡—k⁄Ωmellben—k⁄Ωh√≥nalj⁄okba˘illetve b⁄mily…eÈ©bÍv¡tozæt’deznˇ’l, fordulj n≈ëÈ≥gyæz kezel≈ëorvoshoz!)";
    std::cout << textToDns(compressedToText(d));
}
