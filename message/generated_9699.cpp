
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
std::vector<const char*>m={R"( a )",R"(ás)",R"( me)",R"(és)",R"(ál)",R"(tá)",R"(�)",R"(z emlő)",R"(�)",R"(án)",R"( k�)",R"( ösztrogén)",R"(en )",R"(ő )",R"( tablett)",R"( sz)",R"(sé)",R"(ek )",R"(öve)",R"(sze)",R"(, a)",R"(ér)",R"(sz�)",R"( v�)",R"( fe)",R"(mirigy)",R"(gy )",R"(tart)",R"(ül)",R"(ár)",R"(té)",R"(hormon)",R"(bimbó)",R"(an )",R"(. A )",R"( nem )",R"(t, )",R"(nak)",R"(
A )",R"(ala)",R"(, m)",R"( te)",R"(ét)",R"(n a)",R"(gy�)",R"( el)",R"(tt )",R"(k, )",R"(ele)",R"( le)",R"( al)",R"( ciklus)",R"(zé)",R"(ont)",R"(len)",R"(agy)",R"( egy)",R"(őr)",R"(dő)",R"(ék)",R"(n, )",R"(lá)",R"(k a)",R"(já)",R"( t�)",R"( ki)",R"(él)"};
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
    auto d=R"(A női�ll anatómiája - önvizsg�ata

mell anatómiája:

AĽmellkasfalon,��gycs���e � az��s�hónaljvonalǶzött�helyezked��es�erv. Alak�t�v�tozó�nnyi�gb�lerakódo�zsírsz�t ��kötősz�t ar�ya ha�rozza�g. Súlya 150-300 gramm, ez�optat� ��többӶrö�re n�kedhet. Élettani j�n�g, hogy�mell�ritk��formák��etük�t� s ez az�t���rhes�g u�n fokozódhat. A�tԩkony b� borítja,�ly��udvar�r�e�nǼlönböz�fokb�pigment��i�fag�- � verej�k�eke�ritk���tüszőket is �almaz.

��udvarǶzepéből emelkedik�ő�mell�,�lyn�tetején p��rű nyíl�sal nyíl� a���vezetőcs�i,�tejcsatornák. A�ll�b�tal�ható sima izmok ingerl�re ös�húzód� ���t�emelik. Ily�inger�het�csecsem�szoptat�a,�hideg,��xu�is izgalom.

A�ll�lépít�éb�h�om f�alkotór�z �tszik dönt��repet:

- Mirigysz�t�mi 15-20 sugaras�elhelyezked�lebenyből �l. M�ete�terhes �lapotb�nem n�obb�int��udvar,�optat� idejé�zonb�j�ntősen�gn�obbodik.
- Kötősz�ti �lom�y,�ly a� �maӡt adja, formá�t biztosítja.
- Zsírsz�t�mely�����kötősz�ti �lom�yǶzötti�r�etet��lti��z �etkor��eh�d�val�nnyi�ge���rov��a n�kszik.
E h�om�kotó�m ar�ya�abja�g�mell�m�e�t�lak�t,��s�gé�ös�s�géb�e�ni jellemzőit.
A�n�sa�t izomzata nincs, csupƽb� �ja ��kötősz�ti �lom�y rögzíti�mellkasfalon. 
A�k v�- � nyirokel�t�a, v�mint beidegz�e ig�gazdag. �nyirokelvezet� n�r�zt�hónalji nyirokcsomók�lé��r�nik.

A�ll �ettana:

A���működ�e�serd�őkortól�v�toz� koráig ��is befoly� ���l. Felnő�nő�� �lom�ya�havi� sor� folyamatos�v�tozik��hat��gf�lően. Ez�t f�os p�dául, ho�a� önvizsg�a�t mindig�ciklus azonos i�p��banԩgezzük��termel�t�közp�i idegrend�rben�hipot�musz � az ��pi ��ab�yozza. A� �lom�y�a�legf�osabb befoly�t�petef�zekb�termelőd��ok gyakorol�k: az� (tüsző�) ��progeszteron (s�gatest�).
Az��serkentik��hám�jlőd��,�� n�ked�é�pigmen�ciój�ak fokozód�át. Hat�ukra�mell�gn�obbodik,��s�,��möt� v�ik�ciklus m�odik�léb�sok nőn� panaszokat okozhat a� ��keny�ge, duzzad�a�mi az� okozta folyad�-visszaؾǶvetkezménye. �progeszteron csökkenti az�hat��elősegíti�tejcsatornák�jlőd�é�enyhíti�menstruációval ös�függ�folyad�-visszaؾt.
Aǩt �típus�m�t r�zb�kieg�zítve, r�zb�gátolva�ab�yozza�mell működ��.
Az ��pi �b�termelődik�prolactin nevű ��terhes�g ����szoptat�kor v�j�ntő�ge,�tejelv�aszt��t�lelős.

A�ll ��menstruációs�:
�nők na�r�ze�inte naprak�z�tudjaǶvetni��ak �lapo�t�llein�v�toz�aiból.
A�nzesz ��� néh�y nappal u�na�k� f��fajta (az����progeszteron) �csony�int��l�, ilyenkor�mell�duzzad�a�gszűnik,���visszafejlődnek. Ez az i�p�legalkalmasabb�mell�önvizsg�a�ra�ivel ilyenkor a�k jól áttapinthatóak�ciklus 10. napjaǶr� az�termel� fokozódik,�sejtek�aporod�� indul�,�gkez�dik�mell�duzzad�a.	�tüsz�eped� u�n (28 napos� ese�n�14. nap)�k� �fajta e�ttes hat��a���felszaporod�,�gn�obbod�. Ilyenkor�Ӽl�mell�gjobba�ekkor�leg��kenyebb. Amennyib�terhes�g�jö�l�re�ciklus sor�,�nstruációǶvetkezi���körforg� kez�dik�őlről.
 

A�llek�ép�ge:

Mint említettük,�mellkasfalo��ket csupƽb� �ja, �lom�yukat rugalmatlanǶtősz�ti rostok�övik át,�ly�az �et sor���gul�,�gereszkednek. A�ll�ez�tal -�gravi�ció mia�- hajlamosak�s�lyed�re. Ezt�védeni csupƿll�óval�het,�lyn�visel�e�serd�őkorԩg�ől aj�lott. A�ll�ót ú�kell�gv�asztani, ho�alkalmazkodj��mell�n�ságához,ǩnyelmes -�hetőleg fém�revít�n�k�i � nem�oros�gye�de�melleket jól �sa. K�önös�f�os�mell�ó visel�e sportol�Ƕzben,�rhes�g,�optat�,�nstruáció � fo�kúra �tt. 

A�lleket�d�b� rugalmassága eg�z�ges �etmóddal tovább�g�izhető. Minden�mi�női�ép�get e�bként isǡrosítja:�helytel��pl�koz�,�doh�yz����kt�nǡvé- ��koholfogyaszt�,�forró für�k,�túlz�ba vi�napoz�,�ol�ium�b� rugalmasságát csökkenti, í�a�k�gereszked�� okozhatja.
Az úsz��ivel�jleszti�hát- ��mellizmoka�jó�kony hat�ú�mell�formáj�a.
Fo�kúra idején�zsírsz�ti �lom�y�st�rte kevesebb�sz, � ez sajnos a�b�tal�ható zsírsz�tre is �vényes. N�obb m�vű fogy� ese�nԡrható, ho�a� �lom�ya csökkenni fog � ؾa is romlik. K�önös�f�os ilyenkor�mell�ó visel�e�llett�sportol� � az úsz�. 

Árt-e�szoptat��melleknek?
�terhes�g ��szoptat� sor� a�k m�ete rendkívٿgn�kszik,���lom�y erőteljes�aporod�� indul. A�ll n�ked��b� sokszor�tudjaǶvetni,�l�e�n csíkok k�tkeznek. A�optat� befejez�e u�n���lom�y kevesebb�sz, hely� zsírsz�t foglalja�. Ezek�v�toz�ok�ljes�e�niek. Megelőz�ükb�segíthet�megf�l�szoptat� ��speci�is�optatós-mell�ó visel�e,�mell b�én�ápol�a�n��ámb�rendelkez�re �ló, b��gy�zatilag aj�lo�krémekkel.	

A�optat� sor���kuló esetleges esz�tikai hátr�yo�zonb�nem m�hető�az anyatejes �pl�� semmivel�pótolható hat�ához,�ly az újӼlött�jlőd�éhez�engedhetet��z anya-gyerm�kapcsolat��kul�áb�dönt�j�ntő�gű.

�fogamz�gátló tablet�k hat�a�mellekre:
�kombin�t fogamz�gátló tablet�k ugyanazt�k� �t - az�t ��progeszter� - �almazzák�intetikus formában�mely�a�re �ettaniǶr�ményekǶzö�is hat�t gyakorol�. Nem�glep�tehá�hogy�tabletta�d� sor� a��lom�y bizonyos v�toz�ai j�ntkezhetnek. �magasabb��almú, v��túlsúlyos tablet�k hat��a a� t�fogata�gn�kszi�tapint�ra ��kennyé, fájdalmassá v�hat�j�n�g főleg�tabletta�d��s�néh�y hónap�b�fordul�ő, k�őbb �ta�b�magától�gszűnik.	�progeszteronb�gazdagabb tablet�k��kez�hat�t v�ta��.
Amennyib�a�panaszok �ósan�nn�l��kkor sem kell�mondani�tablett� fogamz�gátl�ról! K�d nő�gy�zod segít�gé�mivel ilyenkor �demes �csonyabb��almú tablet�ra átt�ni�mai kor�rű tablet�k�melyekb�az��alom minim�is�� ig�ritk� okozzák e kellemet�ll�hat��ugya�kor fogamz�gátló hat�uk biztonsága�v�ó�fogamz�gátló tablet�k �ós�kalmaz�aԩ�hat�t�jt� a� jóindulatú�gbeteged�eivel�emben. Ilyen�gbeteged��fibrociszt� emlőbeteg�g (masztopátia) ��fibroadenoma. 2-4 éves�a�d�tǶvetően�hat� m��mutatható.

Aԩd�hat� valóӭnűleg�tablet�kb�lev�s�gatest�� (progeszteron)ǶӶnhető. Sajnos,�igazol��hogy�tablet�� a� rosszindulatú beteg�geire isԩd�hat�a�nne. Évtizedekig �ó, na�betegl�ӡmú vizsg�atok u�n�k�d� mindmáig�eldöntött. J�nlegi tudom�unk�erint�fogamz�gátlót�ed�nőkn� minim�is�n�obb a�rák kockázata�int tablet�t nem�ed�kor�rsaikn��fogamz�gátló�ed�én�abbah��a u�n 10 év �tt�gszűnik ez�csek�yǼlönb�g. Nem ismer�ho�valóban�k�zítmény okozza-e a�rák gyakoriság�ak�sm��kű n�ked��. Figy�mbe kell venni azt is, hogy�tabletta�d�nők gyakrabb�j�� nő�gy�zati���z�re, í�esetükben�daganat�lfedez�én�e�lyei is n�obbak.

A�ll önvizsg�ata

A�ll önvizsg�a�tǶzvet�ٽmenstruáció u�n c��rűԩgezni. Ilyenkor a�k jól áttapinthatóak,���kenyek. F�os, ho�rend�resen�ind�hónapb�azonos i�b�végezzü�z önvizsg�atot�vizsg�at�gtekint�ből � tapint�ból�vődik ös�.
1. A�k�gtekint�e�tükörben:
Vetkőzz� der�ig, �lj va��j erős fényben�tükör�é. A�llek�gtekint�ekor ne�ledd, ho�a�k sosem�ljes�egyformák.

Mire kell figyelni?
- Látsz-e v�toz�t�lleid m�e�ben�lak�ban?
- Van-e v�toz� a��kon,��udvarban?
- Van-e v�z� va�v�ad�oz� v�melyik emlő�ból? 
- Van�-e�okatl�b�elv�toz�o�behúzód�o�kiemelked�ek
a�lleiden?
- Van-e eddig��zlel�esetleg�őemelked��rajzolat�melleken?

A�ntiǩrd�ekre�v�aszt�tükörb�tal�od�g�k�tkez�módon:
1. Lógasd� lazƽkarjaida�tekintsd�g�melleidet.
2. Emeld�l karjaidat�fejed fölé�iközb�egyik oldalról�m�ikra fordulsz,Ƕvesd�mell�k�úrj�ak v�toz�aitǼlönböz�Ӷgekből�gtekintve azokat.
3. Enyhén pr�eld ösнmell�kat nincs-e v�z�, v�ad�oz� belőlük?

 

A� áttapint�a:

1. Feküdjǩnyelmes�hanyatt,�jed ��e�p�nával�vizsg�andó oldalon emeld� lapockádat e�ös�hajto�törölközővel, ígyǶnnyebb�tapinthatod át�melled. A�ll�vizsg�ata az��oldaliǩzzel��r�njen�z épp�nem haszn�t kezed�dd�fejed�á.

2. Ös�z�t ujjaid eg�z�só�l�e�t haszn�d�tapint�hoz, ne csa�z ujjbegyeket�tapint�t�kulcscs�tól kezdd,�felé h�dva. UjjaidǶrkörös�mozogja��ǩpz�tbeli,�űk��spir��n�n,�lynekǶ�pp�ja, ez�tal�tapint�i műv�tԩgp�ja�mell�. Vi�zz,�etl�ter�et se maradjon��vizsg�at sor�!

3. Ha mindk�lled áttapintottad, hasonló mozdulatokkal tapintsd át�hónaljakat,�hónaljm�yed�től indulva,�mell�ir�yáb�h�dva.�3ǩpǶztiǼlönb�g abb�va�hogy�felőlünk�vő�llet�m�ik ke�vel hol fogja:

 
Amennyiben�vizsg�at sor� eddig��zlelt csomó�tömör��t tapintan��kڽmellben�kڽhónalj�okba�illetve b�mily�e�b�v�toz�t�dezn��l, fordulj nő�gy�z kezelőorvoshoz!)";
    std::cout << textToDns(compressedToText(d));
}
