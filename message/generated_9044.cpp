
#include <iostream>
#include <string>
#include <sstream>
char*m[]={" a ","√°s"," me","√©s","√°l","t√°","z eml≈ë","â","√°n"," k√","en "," √∂sztrog√©n","≈ë "," sz"," tablett","ë","s√©","√°t","ek ","√∂ve","ñ","z√°","sze",", a","√©r","sz√"," v√"," fe","gy ","√ºl","√°r","°","t√©","tart","mirigy","int","an ",". A ","t√≥","©","t, ","nak","hormon","≠","bimb√≥"," mi"," nem ","±","ala","≥",", m"," te","∂",R"(
A )","√©t","n a","∫","gy√","º","kor"," el","t≈ë","tt ","k, ","ele","√"," le","≈"," al","z√©","rt√","ont","len","agy"," ciklus","≈ër","l√©","lye","k√©","d≈ë"," egy","√©k","n, ","l√°","k a","j√°"," t√"," ki","√©l","s√°","nek","et ","ely","k. ","ik ","asz"," na","√∂r","√≠t","y√°","kez"," n≈ë"," m√"," ke"," h√≥na","≈ël","s, ","m√©","at ","a a","alma","t f","sza","nt ","leg","koz","ked","i a","ete","ese","ent","bb "," cs","√ºk","z≈ë","t. "};
std::string charToDnsSequence(char ch) {
    std::string s(4, '\0');
    for (unsigned j = 0; j < 4; ++j) {
        s[j] = "ACTG"[(ch >> 2*j) & 0x03];
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
        if ((unsigned char)ch > 129) {
            ss << m[(unsigned char)ch - 130];
        } else {
            ss << ch;
        }
    }
    return ss.str();
}
int main() {
    auto d=R"(AÁiÑll ana®mi√°ja - √∂nvizsgÜata

mell ana®mi√°ja:

AàÇmellkasfalon,Çògycs…è⁄e Ö azæüséh√≥naljvonalã∂z√∂ttæheœzˆé§esèerv. AlakjìÇvÜtoz√≥Ñnnyiígbålerak√≥do¿zs√≠rszït ÖÇk√∂øszït aräya haározzaÑg. S√∫lya 150-300 gramm, ezèoptatÉ ≤¿t√∂bbõ∂r√∂íre nïˆheˇ√âlettani j¬níg, hogyÇmellîritkä“form√°k¥öet˝ætö s ez azætöÖµrhesíg uán foı√≥dhaˇAàtú©kony bÕ bor‰ja,ÑlyÇÆudvarµrüe¢nãºl√∂nb√∂zéfokb¶pigm˙Ü™i¿fagª∫- Ö verej¢k§eke™ritkäè≈ë»ºs˛k›is £z.

∑Æudvarã∂zep√©bÎ emelˆikæ≈ëÇmellÆ,Ñlynît¯j√©n p…òr≈± ny√≠lÉsal ny√≠l´ aàmiriûkivezeøcsïi,Çtejcsatorn√°ﬂAÑllÆb¶talÜha® sima izmok ingerlÖre √∂sòh√∫z√≥d´ ÖÇÆtŸemeliﬂIlyåingerƒhetÇcsecsemészoptatÉa,Çhideg,ÇòxuÜis izgalom.

AÑllùŒp‰Ö√©båh†om féalko®rÖz jìsz‡d√∂ntéòrepet:

- Mirigyszïtômi 15-20 sugaras¶elheœzˆélebenybÎ Ül. Mö¯∞terhes Ülapotb¶nem nÀobb¥•ÇÆudvar,èoptatÉ idej√©πzonb¶j¬nøsenÑgnÀobbodik.
- K√∂øszïti Ülomäy,Ñly aà ám·ì adja, form√°jì biztos‰ja.
- Zs√≠rszïtômﬁÇ§îÖÇk√∂øszïti Ülomäyã∂z√∂ttiµrü¯tÿ∂ltiŸôz ⁄etΩæÕeh≤dávalÑnnyiígeÇ§îrovÉ†a nïkszik.
E h†om∆ko®¬m aräyaèabjaÑgÇmellîmöe¢tôlakjì,ùòsíg√©™√∂sòsíg√©båeª©ni jellem˛it.
Aànîsajì izomzata nincÏcsupäÇbÕ £ja ÖÇk√∂øszïti Ülomäy r√∂gz‰iÇmellkasfalon. 
Aàk vö- Ö nyirokellìÉa, v≤m• beidegzÖe igågazdag. ∑nyirokelvezetÖ nÀrÖztÇh√≥nalji nyirokcsom√≥kùŒÿ∂r¢nik.

AÑll ⁄ettana:

Aà§îm≈±k√∂dÖeÇserdü≈ëΩ®lÇvÜtozÉ Ω√°ig ¨Üis befolyÉ ≤¿Ül. Feln≈ë¿n≈ëπà ÜlomäyaÇhaviÃ sorä folyamatos¶vÜtozikÇ¨hatÉ´Ñgf¬l≈ëen. EzöÒ…os p⁄d√°ul, hoûaà √∂nvizsgÜaátØndigÇciklus azonos i—p…◊banú©gezz˝ß¨termelÖtÇk√∂zp…i idegrendòrbenÇhipot≤musz Ö az À≤pi §èabÜyozza. Aà Ülomäy†aÇÙf…osa˚befolyÉtÇp¯fÖzekbåtermel≈ëdé¨ok gyaΩol◊k: azç (t√ºs˛¨) ÖÇprogeszteron (s†gatest¨).
Azçîserk˙ikÇ§h√°mùjl≈ëdÖ∏,ÇÆ nïˆÖ√©™pigmenáci√≥jäak foı√≥dÉì. HatÉukraÇmellÑgnÀobbodik,ùòsí,ÿ∂m√∂t¢ vÜikßciklus mÉodikùŒbåsokÁn⁄ pan·okÓoıhÓaà ö«kenyíge, duzzadÉaôm˜zç oıta folyad”-visÚ£Éã∂vetÊÌnye. ∑progeszteron¸√∂kk˙˜zçhatÉ™el≈ëseg‰iÇtejcsatorn√°kùjl≈ëdÖ√©™enyh‰iÇmenstru√°ci√≥val √∂sòf√ºggéfolyad”-visÚ£Ét.
Aã©t ¨t√≠pus“mÉt rÖzbåkiegÖz‰ve, rÖzbågìolvaèabÜyozzaÇmell m≈±k√∂dÖ∏.
Az À≤pi §båtermel≈ëdikÇprolactin nev≈± ¨ßterhesíg ≤¿ÖÇszoptatÉΩ v¶j¬nøíge,ÇtejelvÜ·tÉötùlel≈ës.

AÑll ÖÇmenstru√°ci√≥sÃ:
∑n≈ëk‚ûrÖzeè•e‚prakÖzåtudjaã∂vetniÃäak ÜlapoátÑlleinîvÜtozÉaib√≥l.
AÑnzesz ≤¿Ö n√©häy‚ppal uánaÇk∏ fé¨fajta (azçîÖÇprogeszteron) ≤csonyè•åÜl´, iœnΩÇmellîduzzadÉaÑgsz≈±nik,Ç§îvisÚfejl≈ëd‹. Ez az i—p…ÇÙalksabbÇmellî√∂nvizsgÜaára,Øvel iœnΩ aàk j√≥l ìtap•ha®akßciklus 10.‚pjaã∂rü azçtermelÖ foı√≥dik,ÇsejtekèaporodÉ´ indul´,ÑgÊ—dikÇmellîduzzadÉa.	∑t√ºszÕepedÖ uán (28‚posÃ ˘¢nÇ14.‚p)Çk∏ ¨fajta eªºttes hatÉ†aÇ§îfelÚporod´,ÑgnÀobbod´. IœnΩùõºlÇmellƒgjobba‘ekΩÇÙö«kenyebb. Amennyibåterhesíg∞j√∂¿l∏reÇciklus sorä,Ñnstru√°ci√≥ã∂vetÊi¡ÖÇk„forgÉ Ê—dikæÎrÎ.
 

AÑllekè√©píge:

M• eml‰ett˝,Çmellkasfaloπàk›csupäÇbÕ £ja, ÜlomäyukÓrugtlanã∂øszïti rostokè√∂v‡ì,Ñlyîaz ⁄›soräŸágul´,Ñgereszˆ‹. AÑllîezÜtal -Çgraviáci√≥Øa¿- hajlamosakÇsüœdÖre. EztŸv√©deni¸upäÑll£√≥valƒhet,ÑlynîviselÖeÇserdü≈ëΩú©g∏Î ajälotˇAÑll£√≥t √∫ûkellÑgvÜ·tani, hoûalkzkodj”ÇmellînÀ€g√°hoz,ã©nyelmes -ƒheøÙ f√©mÑrev‰én⁄küi Ö nemèorosƒgye‘deÇmellek›j√≥l £sa. Kü√∂n√∂såf…osÇmell£√≥ viselÖe sportolÉã∂zben,µrhesíg,èoptatÉ,Ñnstru√°ci√≥ Ö foª≥k√∫ra ≤tˇ

AÑlleketùdébÕ rugs€ga egÖzíges ⁄etm√≥ddal tov√°bbÑgÕizheø. MindenômiÇn≈ëiè√©píg›eª©b–Ûisã°ros‰ja:ÇhﬁtelåáplÜıÉ,ÇdohäyzÉ¥ö¢kt¬nã°v√©- Ö∆koholfogy·tÉ,Çforr√≥ f√ºr—k,Çt√∫lzÉba vi¿napozÉ,èol†iumÇbÕ rugs€gì¸√∂kk˙i, √≠ûaàkÑgereszˆÖ∏ oıhatja.
Az √∫szÉ,ØvelùjlesztiÇhì- ÖÇmellizmoka™j√≥¢kony hatÉ√∫Çmellîform√°j†a.
Foª≥k√∫ra idej√©nÇzs√≠rszïti ÜlomäyµstòrteÈv˘bbƒsz, Ö ez sajnos aàbåtalÜha® zs√≠rszïtre is öv√©nyes. NÀo˚möv≈± fogyÉ ˘¢nú°rha®, hoûaà Ülomäya¸√∂kkenni fog Ö £Éa is romliﬂKü√∂n√∂såf…os iœnΩÇmell£√≥ viselÖeÑllettÇsportolÉ Ö az √∫szÉ. 

√Årt-eÇszoptatÉÇmellek‹?

Aµrhesíg ÖÇszoptatÉ sorä aàk mö¯ rendk√≠vüÑgnïkszik,Ç§Ülomäy er≈ëteljesèaporodÉ´ indul. AÑll nïˆÖ∏ÇbÕ sokszor∞tudjaã∂vetni,ùlüe¢n¸√≠kok k¬tÊ‹. AèoptatÉ befejezÖe uánÇ§ÜlomäyÈv˘bbƒsz, hﬁ∏ zs√≠rszïÒoglaljaæ. EzekÇvÜtozÉokµljesåeª©nieﬂMegel≈ëzÖ˝båseg‰hetÇmegf¬lészoptatÉ ≤¿speciÜisèopta®s-mell£√≥ viselÖe,Çmell bÕ√©nî√°polÉaÇnÀè√°mb¶rendelÊÖre Ül√≥, bÕª≥gyÉzatilag ajälo¿kr√©mekkel.	

AèoptatÉ soräŸ≤kul√≥ ˘tÙes esz¢tikai hìräyo÷zonb¶nem möheøîaz anyatejes áplÜÉ semmivel∞p√≥tolha® hatÉ√°hoz,Ñly az √∫jõºl√∂ttùjl≈ëdÖ√©hezæengedh¯t ôz anya-gyermîkapcsolatŸ≤kulÉ√°b¶d√∂ntéj¬nøíg≈±.

∑fogamzÉgìl√≥ tableták hatÉaÇmellekre:
∑kombinÜÒogamzÉgìl√≥ tableták ugyanaztÇk∏ ¨t - azçt ÖÇprogeszter… - £zókè•etikus form√°banômﬁîaàre ⁄ettaniã∂rüÌnyekã∂z√∂¿is hatÉt gyaΩol´. NemÑglepétehì, hogyÇtablettaòdÖ sorä aàÜlomäy bizonyos vÜtozÉai j¬ntÊhet‹. ∑magasabbç£alm√∫, vÀçt√∫ls√∫lyos tableták hatÉ†Ôà töfogataÑgnïkszi¡tap•Éra ö«kenny√©, f√°jds€ vÜhatßj¬níg fÎegÇtablettaòdÖæsén√©häyÍp◊b¶fordulæ≈ë, kÖ≈ë˚Üta’b¶magì√≥lÑgsz≈±nik.	∑progeszteronb¶gazdaga˚tabletákæ ÊéhatÉt vÜta´Ÿ.
Amennyibåaàpan·ok £√≥sanùnnÜl´ôkΩ semÈllƒmondaniÇtablettÉ fogamzÉgìlÉr√≥l! KödÁª≥gyÉzod seg‰íg√©™mivel iœnΩ ödemes ≤csonyabbç£alm√∫ tabletára ìtönißmai Ωòr≈± tabletákômeœkbåazç£alomØnimÜis¥† igåritkä oıók eÈllemet ÑlŒkhatÉ™ugya´Ω fogamzÉgìl√≥ hatÉuk bizton€gaŸvÜ√≥ßfogamzÉgìl√≥ tableták £√≥s∆kzÉaú©—hatÉtùjtŸ aà j√≥indulat√∫Ñgb¯gedÖeivelèemben. IœnÑgb¯gedÖÇfibrocisztÉ eml≈ëb¯gíg (m·topìia) ÖÇfibroadenoma. 2-4 √©vesêaòdÖtã∂veøenÇhatÉ m†Ÿmutatha®.

Aú©déhatÉ val√≥õ≠n≈±ÙÇtabletákb¶levés†gatest¨´ (progeszteron)ã∂õ∂nheø. Sajnos,∞igazolá¡hogyÇtabletá´ aà rosszindulat√∫ b¯gígeire isú©déhatÉaƒnne. √âvtizedekig £√≥,‚ûb¯gl∏sóm√∫ vizsgÜatok uánÇködÖØndm√°ig∞eld√∂nt√∂tˇJ¬nÙi tudomÉunkèer•ÇfogamzÉgìl√≥tèedén≈ëkn⁄ØnimÜis¶nÀo˚aàr√°k kock√°zata¥• tabletát nemèedéΩársaiknÜßfogamzÉgìl√≥èedÖ√©nîabbahÀÉa uán 10 √©v ≤ttÑgsz≈±n‡ezÇcse–lyãºl√∂nbíg. Nem ismer™hoûval√≥banÇkÖz‰Ìny oıza-e aàr√°k gyaΩi€gäakŸsmö¢k≈± nïˆÖ∏. Figy¬mbeÈll venn˜zt iÏhogyÇtablettaòdén≈ëk gyakrabb¶j†´Áª≥gyÉzatiæ ÕzÖre, √≠û˘t˝benÇdaganatùlfedezÖ√©nîeíœi is nÀobbak.

AÑll √∂nvizsgÜata

AÑll √∂nvizsgÜaátã∂zvet üÇmenstru√°ci√≥ uán c⁄òr≈±ú©gezni. IœnΩ aàk j√≥l ìtap•ha®ak,∞ö«kenyeﬂF…oÏhoûrendòr˘n,Øndåh√≥napb¶azonos i—båv√©gezz√º÷z √∂nvizsgÜatotßvizsgÜatÑgtek•ÖbÎ Ö tap•Éb√≥lµv≈ëd‡√∂sò.
1. AàkÑgtek•ÖeÇt˝„ben:
Vetk≈ëzzƒ der”ig, Ülj vaûüj er≈ës f√©nybenÇt˝„æ√©. AÑllekÑgtek•ÖeΩ neùledd, hoûaàk sosemµljesåegyform√°k.

MireÈll figyelni?
- Lìsz-e vÜtozÉtÑlleid möe¢benôlak◊ban?
- Van-e vÜtozÉ aàÆkon,ÇÆudvarban?
- Van-e vözÖ vaûvÜad”ozÉ v≤mﬁ‡eml≈ëÆb√≥l? 
- Van´-eèokatl¶bÕelvÜtozÉo¡beh√∫z√≥dÉo¡kiemelˆÖek
aÑlleiden?
- Van-e eddig∞Özlel™˘tÙæ≈ëemelˆéörajzolatÇmelleken?

Aùntiã©rdÖekreÇvÜ·tÇt˝„båtalÜodÑgÇkïtÊém√≥don:
1. L√≥gasdƒ lazäÇkarjaida™tek•sdÑgÇmelleidet.
2. Emeldùl karjaidatÇfejed f√∂Œ,Øk√∂zbåegy‡oldalr√≥lÇmÉikra fordulsz,ã∂vesdÇmellîk…√∫rjäak vÜtozÉaitãºl√∂nb√∂zéõ∂gekbÎÑgtek•ve azokat.
3. Enyh√©n prÖeld √∂sòÇmellÆkÓnincs-e vözÖ, vÜad”ozÉ belÎ˝?

 

Aà ìtap•Éa:

1. Fek√ºdjã©nyelmesåhanyatt,ùjed ≤¿eûp†n√°valßvizsgÜand√≥ oldalon emeldŸ lapock√°dÓeû√∂sòhajto¿t„√∂lk√∂˛vel, √≠gyã∂nnyebbåtap•hatod ìÇmelled. AÑllîvizsgÜatÔzæ oldaliã©zzelÿ∂r¢njenôz √©ppånem h·nÜt ÊedµddÇfejed∆√°.

2. √ñsòórt ujjaid egÖz∆s√≥ùlüe¢t h·nÜdÇtap•Éhoz, ne¸a÷z ujjbegyeketßtap•ÉtÇkulcscs…®l Êdd,ƒfeŒ h≤dva. Ujjaidã∂rk„√∂såmozogja´“ã©pz¬tbeli,è≈±küéspirÜÑn¢n,Ñly‹ã∂«pp…ja, ezÜtalÇtap•Éi m≈±v¬tú©gp…jaÇmellÆ. Viª°zz,“etlåterü›se maradjonŸÇvizsgÜÓsorä!

3. HaØndk∏Ñlled ìtap•ottad, hasonl√≥ mozdulatokkal tap•sd ìÇh√≥naljakat,Çh√≥naljÌœdÖøl indulva,ÇmellîiräÂb¶h≤dva.∑3ã©pã∂ztiãºl√∂nbíg abb¶va‘hogyÇfelÎ√ºnkƒv≈ëÑlletÇmÉ‡ke«vel hol fogja:

 
AmennyibenÇvizsgÜÓsorä eddig∞Özlelt¸om√≥™t√∂m„üÖt tap•anÜôk†Çmellbenôk†Çh√≥nalj†okba‘illetve b†milyåeª©bævÜtozÉtùdezn⁄ùl, forduljÁª≥gyÉz Êel≈ëorvoshoz!)";
    std::cout << textToDns(compressedToText(d));
}
