
#include <iostream>
#include <string>
#include <sstream>
char*m[]={" a ","ás"," me","és","ál","tá","z emlő","�","án"," k�","en "," ösztrogén","ő "," sz"," tablett","�","sé","át","ek ","öve","�","zá","sze",", a","ér","sz�"," v�"," fe","gy ","ül","ár","�","té","tart","mirigy","int","an ",". A ","tó","�","t, ","nak","hormon","�","bimbó"," mi"," nem ","�","ala","�",", m"," te","�",R"(
A )","ét","n a","�","gy�","�","kor"," el","tő","tt ","k, ","ele","�"," le","�"," al","zé","rt�","ont","len","agy"," ciklus","őr","lé","lye","ké","dő"," egy","ék","n, ","lá","k a","já"," t�"," ki","él","sá","nek","et ","ely","k. ","ik ","asz"," na","ör","ít","yá","kez"," nő"," m�"," ke"," hóna","ől","s, ","mé","at ","a a","alma","t f","sza","nt ","leg","koz","ked","i a","ete","ese","ent","bb "," cs","ük","ző","t. "};
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
    auto d=R"(A�i�ll ana�miája - önvizsg�ata

mell ana�miája:

A��mellkasfalon,��gycsɏ�e � az��s�hónaljvonal��zött�he�z���es�erv. Alakj��v�tozó�nnyi�gb�lerakódo�zsírsz�t ��kö�sz�t ar�ya ha�rozza�g. Súlya 150-300 gramm, ez�optat� ��több��rö�re n��he�Élettani j�n�g, hogy�mell�ritk��formák��et��t� s ez az�t���rhes�g u�n fo�ódha�A�t��kony b� bor�ja,�ly��udvar�r�e�n��lönböz�fokb�pigm���i�fag��- � verej�k�eke�ritk��őȼs�k�is ��z.

��udvar��zepéb� emel�ik�ő�mell�,�lyn�t�jén pɘrű nyíl�sal nyíl� a�miri�kiveze�cs�i,�tejcsatorná�A�ll�b�tal�ha� sima izmok ingerl�re ös�húzód� ���t�emeli�Ily�inger�het�csecsem�szoptat�a,�hideg,��xu�is izgalom.

A�ll��p�éb�h�om f�alko�r�z j�sz�dönt��repet:

- Mirigysz�t�mi 15-20 sugaras�elhe�z��lebenyb� �l. M���terhes �lapotb�nem n�obb����udvar,�optat� idejé�zonb�j�n�sen�gn�obbodik.
- Kö�sz�ti �lom�y,�ly a� �m� adja, formáj� biztos�ja.
- Zsírsz�t�mނ����kö�sz�ti �lom�y��zötti�r��tضltiٙz �et���eh�d�val�nnyi�ge���rov��a n�kszik.
E h�om�ko��m ar�ya�abja�g�mell�m�e�t�lakj�,��s�gé�ös�s�géb�e��ni jellem�it.
A�n�saj� izomzata ninc�csup��b� �ja ��kö�sz�ti �lom�y rögz�i�mellkasfalon. 
A�k v�- � nyirokell��a, v�m� beidegz�e ig�gazdag. �nyirokelvezet� n�r�zt�hónalji nyirokcsomók��ضr�nik.

A�ll �ettana:

A���működ�e�serd�ő��l�v�toz� �áig ��is befoly� ���l. Felnő�nő�� �lom�ya�havi� sor� folyamatos�v�tozik��hat���gf�lően. Ez���os p�dául, ho�a� önvizsg�a�t�ndig�ciklus azonos i�p��ban��gezz���termel�t�közp�i idegrend�rben�hipot�musz � az ˲pi ��ab�yozza. A� �lom�y�a��f�osa�befoly�t�p�f�zekb�termelőd��ok gya�ol�k: az� (tüs��) ��progeszteron (s�gatest�).
Az��serk�ik��hám�jlőd��,�� n���é�pigmen�ciój�ak fo�ód��. Hat�ukra�mell�gn�obbodik,��s�,ضmöt� v�ik�ciklus m�odik��b�sok�n� pan�ok�o�h�a� ��keny�ge, duzzad�a�m�z� o�ta folyad�-vis򣃋�vet��nye. �progeszteron�ökk��z�hat��előseg�i�tejcsatornák�jlőd�é�enyh�i�menstruációval ös�függ�folyad�-vis�t.
A��t �típus�m�t r�zb�kieg�z�ve, r�zb�g�olva�ab�yozza�mell működ��.
Az ˲pi �b�termelődik�prolactin nevű ��terhes�g ����szoptat�� v�j�n��ge,�tejelv��t��t�lelős.

A�ll ��menstruációs�:
�nők�r�ze��e�prak�z�tudja��vetni̊ak �lapo�t�llein�v�toz�aiból.
A�nzesz ��� néh�y�ppal u�na�k� f��fajta (az����progeszteron) �csony����l�, i�n��mell�duzzad�a�gszűnik,���vis�fejlőd�. Ez az i�pɂ�alk�sabb�mell�önvizsg�a�ra,�vel i�n� a�k jól �tap�ha�ak�ciklus 10.�pja��r� az�termel� fo�ódik,�sejtek�aporod�� indul�,�g��dik�mell�duzzad�a.	�tüsz�eped� u�n (28�pos� ��n�14.�p)�k� �fajta e��ttes hat��a���fel�porod�,�gn�obbod�. I�n����l�mell�gjobba�ek�����kenyebb. Amennyib�terhes�g�jö�l�re�ciklus sor�,�nstruáció��vet�i���k�forg� ��dik��r�.
 

A�llek�ép�ge:

M� eml�ett�,�mellkasfalo��k�csup��b� �ja, �lom�yuk�rug�tlan���sz�ti rostok�öv��,�ly�az ��sor�هgul�,�geresz��. A�ll�ez�tal -�gravi�ció�a�- hajlamosak�s��d�re. Ezt�védeni�up��ll�óval�het,�lyn�visel�e�serd�ő���g�� aj�lot�A�ll�ót ú�kell�gv��tani, ho�alk�zkodjӂmell�n��gához,��nyelmes -�he�� fém�rev�n�k�i � nem�oros�gye�de�mellek�jól �sa. K�önös�f�os�mell�ó visel�e sportol���zben,�rhes�g,�optat�,�nstruáció � fo��kúra �t�

A�lleket�d�b� rug�s�ga eg�z�ges �etmóddal tovább�g�izhe�. Minden�mi�női�ép�g�e��b��is��ros�ja:�h�tel��pl���,�doh�yz����kt�n��vé- ��koholfogy�t�,�forró für�k,�túlz�ba vi�napoz�,�ol�ium�b� rug�s�g��ökk�i, í�a�k�geresz��� o�hatja.
Az úsz�,�vel�jleszti�h�- ��mellizmoka�jó�kony hat�ú�mell�formáj�a.
Fo��kúra idején�zsírsz�ti �lom�y�st�rte�v�bb�sz, � ez sajnos a�b�tal�ha� zsírsz�tre is �vényes. N�o�m�vű fogy� ��n��rha�, ho�a� �lom�ya�ökkenni fog � ��a is romli�K�önös�f�os i�n��mell�ó visel�e�llett�sportol� � az úsz�. 

Árt-e�szoptat��mellek�?

A�rhes�g ��szoptat� sor� a�k m�� rendkív��gn�kszik,���lom�y erőteljes�aporod�� indul. A�ll n�����b� sokszor�tudja��vetni,�l�e�n�íkok k�t��. A�optat� befejez�e u�n���lom�y�v�bb�sz, h޸ zsírsz��oglalja�. Ezek�v�toz�ok�ljes�e��nie�Megelőz��b�seg�het�megf�l�szoptat� ��speci�is�opta�s-mell�ó visel�e,�mell b�én�ápol�a�nˏámb�rendel�re �ló, bͻ�gy�zatilag aj�lo�krémekkel.	

A�optat� sor�ٲkuló �t�es esz�tikai h�r�yo�zonb�nem m�he��az anyatejes �pl�� semmivel�pótolha� hat�ához,�ly az új��lött�jlőd�éhez�engedh�tʙz anya-gyerm�kapcsolatٲkul�áb�dönt�j�n��gű.

�fogamz�g�ló tablet�k hat�a�mellekre:
�kombin��ogamz�g�ló tablet�k ugyanazt�k� �t - az�t ��progeszter� - ��z�k��etikus formában�mޔa�re �ettani��r��nyek��zö�is hat�t gya�ol�. Nem�glep�teh�, hogy�tabletta�d� sor� a��lom�y bizonyos v�toz�ai j�nt�het�. �magasabb��almú, vˍtúlsúlyos tablet�k hat��� t�fogata�gn�kszi�tap��ra ��kennyé, fájd�s� v�hat�j�n�g f�eg�tabletta�d��s�néh�y�p�b�fordul�ő, k�ő��ta�b�mag�ól�gszűnik.	�progeszteronb�gazdaga�tablet�k���hat�t v�ta��.
Amennyib�a�pan�ok �ósan�nn�l��k� sem�ll�mondani�tablett� fogamz�g�l�ról! K�d绳gy�zod seg�gé�mivel i�n� �demes �csonyabb��almú tablet�ra �t�ni�mai ��rű tablet�k�me�kb�az��alom�nim�is�� ig�ritk� o��k e�llemetʄl�khat��ugya�� fogamz�g�ló hat�uk bizton�ga�v�ó�fogamz�g�ló tablet�k �ós�k�z�a���hat�t�jt� a� jóindulatú�gb�ged�eivel�emben. I�n�gb�ged��fibrociszt� emlőb�g�g (m�top�ia) ��fibroadenoma. 2-4 éves�a�d�t��ve�en�hat� m��mutatha�.

A��d�hat� való��nű�tablet�kb�lev�s�gatest�� (progeszteron)����nhe�. Sajnos,�igazol��hogy�tablet�� a� rosszindulatú b�g�geire is��d�hat�a�nne. Évtizedekig �ó,�b�gl�s�mú vizsg�atok u�n�k�d��ndmáig�eldöntöt�J�n�i tudom�unk�er��fogamz�g�lót�ed�nőknگnim�is�n�o�a�rák kockázata�� tablet�t nem�ed���rsaikn��fogamz�g�ló�ed�én�abbah˃a u�n 10 év �tt�gszűn�ez�cse�ly��lönb�g. Nem ismer�ho�valóban�k�z��ny o�za-e a�rák gya�i�g�ak�sm��kű n����. Figy�mbe�ll venn�zt i�hogy�tabletta�d�nők gyakrabb�j��绳gy�zati���z�re, í��t�ben�daganat�lfedez�én�e��i is n�obbak.

A�ll önvizsg�ata

A�ll önvizsg�a�t��zvetʟ�menstruáció u�n cژrű��gezni. I�n� a�k jól �tap�ha�ak,���kenye�F�o�ho�rend�r�n,�nd�hónapb�azonos i�b�végezzü�z önvizsg�atot�vizsg�at�gtek��b� � tap��ból�vőd�ös�.
1. A�k�gtek��e�t��ben:
Vetkőzz� der�ig, �lj va��j erős fényben�t��é. A�llek�gtek��e� ne�ledd, ho�a�k sosem�ljes�egyformák.

Mire�ll figyelni?
- L�sz-e v�toz�t�lleid m�e�ben�lak�ban?
- Van-e v�toz� a��kon,��udvarban?
- Van-e v�z� va�v�ad�oz� v�m��emlő�ból? 
- Van�-e�okatl�b�elv�toz�o�behúzód�o�kiemel��ek
a�lleiden?
- Van-e eddig��zlel��t��őemel���rajzolat�melleken?

A�nti��rd�ekre�v��t�t��b�tal�od�g�k�t�módon:
1. Lógasd� laz��karjaida�tek�sd�g�melleidet.
2. Emeld�l karjaidat�fejed fö�,�közb�egy�oldalról�m�ikra fordulsz,��vesd�mell�k�úrj�ak v�toz�ait��lönböz���gekb�gtek�ve azokat.
3. Enyhén pr�eld ös��mell�k�nincs-e v�z�, v�ad�oz� bel��?

 

A� �tap��a:

1. Feküdj��nyelmes�hanyatt,�jed ��e�p�nával�vizsg�andó oldalon emeld� lapockád�e�ös�hajto�t�ölkö�vel, így��nnyebb�tap�hatod ��melled. A�ll�vizsg�at�z��oldali��zzelضr�njen�z épp�nem h�n�t �ed�dd�fejed�á.

2. Ös��rt ujjaid eg�z�só�l�e�t h�n�d�tap��hoz, ne�a�z ujjbegyeket�tap��t�kulcscsɨl �dd,�fe� h�dva. Ujjaid��rk�ös�mozogja�ҋ�pz�tbeli,�űk��spir��n�n,�ly܋��pp�ja, ez�tal�tap��i műv�t��gp�ja�mell�. Vi��zz,�etl�ter��se maradjonقvizsg��sor�!

3. Ha�ndk��lled �tap�ottad, hasonló mozdulatokkal tap�sd ��hónaljakat,�hónalj��d��l indulva,�mell�ir��b�h�dva.�3��p��zti��lönb�g abb�va�hogy�fel�ünk�vő�llet�m��ke�vel hol fogja:

 
Amennyiben�vizsg��sor� eddig��zlelt�omó�töm㟅t tap�an��k��mellben�k��hónalj�okba�illetve b�mily�e��b�v�toz�t�deznڝl, fordulj绳gy�z �előorvoshoz!)";
    std::cout << textToDns(compressedToText(d));
}
