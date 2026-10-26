# Küçük Mesaj

Bu metinde eski hedeflerim ve sonradan yaptığım değerlendirmeler bir arada. Buradaki emülatör, ISA, skorboard, cycle ve performans ifadeleri bu pakette yeniden sınanmamıştır. Aşağıdaki 18 Temmuz tarihi bütün cümlelerin o gün yazıldığı anlamına gelmez. Burada anlattığım eski CT-CPU tasarımı ile araştırma günlüğündeki Hunter, projenin farklı dönemlerine ait.

### İstediklerim, amaçlarım, yapmak istediklerim (18 Temmuz 2026)

#### Ben kimim, nereden geliyorum

Hayatım boyunca data paketlemeyi, pratik iletişimi ve optimizasyonu sevdim. İşlerin etkileşimli ve dolaylı yoldan paralel yapılması için kafa yormak hoşuma gider. Bir düşüncenin karşısındaki gerekçeyi de aramayı severim. Çoğu zaman başka insanların neden sonuç ilişkilerini bile kafamda tartmışımdır. Bir ızgaraya düz ve çapraz bakarak farklı anlamlarla bağlam kurmaya çalışırım (Scrabble/bulmaca ilkem). Data aktarmaya, yani insanlar arası ve öteki canlılarla iletişime bile takıntılıyım. Birinin konuşurkenki içtenliğini hissederim. Algım bütüncül çalışır. Son zamanlarda insanlarla iletişimim pek iyi değil, çünkü ben de sabırsızlaşıyorum. Samimiyetsiz, niyetini çok acemice gizleyen, ani dürtüyle gelişen ve ilgiliymiş izlenimi vermeye çalışan iletişim biçimleriyle karşılaşınca ilgimi kaybediyorum.

Bir sistemin nasıl işlediğini çözmeyi seviyorum. Format dönüşümü ve tersine mühendislik kendimi yakın hissettiğim alanlar. x64/ARM assembly, dosya formatları, binary okuma. Ben buradan geliyorum. Yeni projelerim bu birikimin devamı.

Kurulu düzenin her zaman en iyi tasarım olmadığını çocukken öğrendim. F klavyeyi denedim, müthiş bir deneyimdi. Türkçe için tasarlanmıştı zaten. Ama dünya Q’ya alışmıştı ve üstüne bir endüstri kurulmuştu. Ben de alışmak zorundaydım ve Türkçe Q klavyeye başladım. İngilizce Q’nun şu anki işlerimde daha hızlı olduğunu ve uğraştığım alanın bu klavye üzerine kurulduğunu fark edince, yakın zamanda İngilizce Q klavyeye alıştım.

Buna QWERTY etkisi diyorum. Bir düzen yaygınlaşınca herkes ona alışır, araçlar ona göre yapılır. Daha iyi tasarım, geçiş maliyetini yenemezse kaybeder.

#### Büyük hayalim, derin nefes alan bilgisayar

Amacım hızıyla değil sakinliğiyle kazanan bir makine. Bunu şöyle hayal ediyorum: 3 GHz’lik bir işlemcinin kapasitesinin üçte biri planlamaya ve işi düzenlemeye, kalan üçte ikisi daha büyük problemleri çözmeye ayrılsın. Daha fazla iş yapsın ama ne yapacağını da sakin sakin planlasın. Buradaki 1 GHz / 2 GHz paylaşımı bir benzetme. GHz enerji birimi değil ve bu oran ölçülmüş bir sonuç değil. Buna derin nefes politikası diyorum.

Metaforum şu. Hızlı ve manik oynayan bir profesyonel oyuncu iyi olabilir. Deneyimli ama sakin ve mekanik olarak temiz oynayan oyuncu her zaman daha da iyi oynayacaktır. Ben sakin oyuncuyu tasarlıyorum. İlgilenen, Dfalt_ adlı FPS oyuncusuna bakabilir.

Aynı soruyu sormak, aynı düşünme mekanizmasını çalıştırmak demek değil. İki sisteme “Bir sayı söyle” dediğimde, kullandıkları algoritmalar seçimlerini şekillendirir. İnsanlarda da kültürün, alışkanlıkların ve yaşanmışlıkların benzer bir etkisi olduğunu düşünüyorum. Aynı paydada buluşan insanlar, birbirlerinden habersizken bile benzer seçimlere ve keşif yollarına yönelebilir. Benim mekaniklikten kastım biraz da bu.

Bu makine kesin matematik yapacak, float hatası sıfır. Sayıları sembolleştirdim. Her sayı aynı anda iki formda yaşıyor. Pozisyonel form (toplama için) ve gölge form, yani asal çarpanlarına ayrılmış üsler (çarpma = üs toplama, bölme = üs çıkarma, kök = üs yarılama). Ayrıca √x, i√x, 1/x, Σx, x! gibi şeyleri işlem olarak değil TİP olarak taşıyorum. Sembolik olarak taşınır, gerektiğinde açılır. Gösterimi saklamanın, yorumlamanın ve açmanın maliyeti vardır.

Makinenin kısa tanımı: [CTCPU](CTCPU.md).

Silikon yok. Tüm MHz/watt/cycle sayıları model tahminidir. Yalnız emülatör ölçümleri gerçektir ve öyle etiketlenir. Bu cümleyi saklamayacağım. README'nin en tepesine koyacağım.

Sınırlarımı da biliyorum ve söylüyorum. Gölge toplayamaz, ama üzerinde çalıştığım bazı şeyler var. Rastgele veride uçmaz (bunu kendim hesapladım, rastgele bir sayının ilk yedi asaldan gelen kısmının ortalama logaritmik büyüklüğü yaklaşık 3,75 bit), 120 KB bellek genel amaçlı iş için azdır. Ben yapılandırılmış sayılarla ve kesin aritmetikle çalışmaya odaklanıyorum. Gröbner hesapları, kesin rasyonel aritmetik ve monom motorları bunun olası kullanım alanları. Hedefim sıfır yuvarlama hatası. Bu hedefin maliyeti ve sınırları, seçilen veri türleri ve karşılaştırılan hesaplarla birlikte ölçülmelidir. Tek başına başka hesaplama birimlerine üstünlük kanıtı değildir.

Tasarladığım şey, ana bilgisayardan iş alan ve belirli hesaplara odaklanan sakin bir yardımcı işlemci. Kurulu devlerle aynı masada yarışmayacağım. Onların klavyesinde tuşu olmayan harflerle oynayacağım.

#### Stratejim, işlemci değil emülasyon

İnsanlara önce emülatörümle ulaşmak istiyorum. Kimseden donanım almasını, alışkanlık değiştirmesini istemiyorum. Emülatörüm herkesin elindeki makinede koşacak. Kurulu taban düşmanım değil, taşıyıcım olacak (JVM/WASM/PICO-8 yolu).

İddiam bahanesiz ve ölçülebilir olacak. Emülatörümü aynı makinede GMP/FLINT'in uygun yöntemleriyle karşılaştırmak, hem süreyi hem de tüketilen enerjiyi ölçmek istiyorum. "Silikon yok" mazereti yok.

Bir FPGA kartı aldım (Tang Nano 9K). Emülasyonun yanında FPGA'da da deneyler yapacağım, ama önce oturtulması gereken şeyler var. İlk adım basit olacak, küçük adımlarla ilerleyeceğim.

#### Yapacaklarım (araç zinciri)

CT-CPU'ya kendi assembly dilimi yazmakla uğraşıyorum. Bunun için metin sözdizimi ve programı emülatöre aktaracak bir assembler üzerinde çalışıyorum. Elimde ISA opcode'ları, komut formatı ve ARM/x64 temsil dosyaları var.

Programcılar bildikleri dilden başlayabilsin diye C karşılıklarını da hazırlayacağım.

ARM ve x64 assembly eşlemelerini bile yapacağım, çeviri tabloları ve köprülerle.

Emülatörü ISA'yla bire bir hizalayacağım (bilinen 11.1 tutarsızlığı, emülatörün 22 opcode'luk enum'u kilitli 8 opcode haritasına çekilecek). Yayında sözleşme ile kod birbirini doğrulayacak.

#### Yayın ve topluluk hayalim

ISA belgesi dahil hazır olan her şeyi GitHub'da açık paylaşacağım, çünkü insanların da geliştirmesini istiyorum.

Benim için değer yalnız ortaya koyduğum üründe değil, onu üretebilmemde. Ben bunun çok daha iyisini, bambaşka mimarileri de yapabilirim.

Hayalim, programcıların ve optimizasyonla uğraşanların açık kodu ve assembly’yi alıp değiştirmesi. Benim düşünmediğim şeyler denemeleri, yeni işler çıkarmaları. Demoscene'in, Chip-8'in, uxn'in başına gelen benim makinemin de başına gelsin istiyorum.

Ve bu süreç şunu gösterecek: Yazılım dili bilmek ve AI kullanmak tek başına birini programcı yapmaz. İstek ve problem çözmek birini yazılım mühendisi / bilgisayar bilimci yapar. Benim araçlarla yaptığım işler bunun kanıtı olacak.

#### Tanrı zar atmaz

“Tanrı zar atmaz,” demişti Einstein. Ben bunu makinemde istediğim deterministik davranış için bir benzetme olarak kullanıyorum. Arşiv kaydına göre kat12 dört koşumda bayt bayt aynı. Bu paket o deneyi yeniden üretmiyor. Kaydedilen koşumlarda yuvarlama hatası sıfır, determinizm sapması sıfır. Zar atmayan makine. Kişisel olarak kuantumda da zar atılmadığına inanıyorum. Sicim teorisine de inanıyorum.

Bütün bunların yanında kişisel bir amacım da var: akademik hedeflerimle ilerlerken geçim dertlerini düşünmemek. Ailemin geçim sorunu olduğunu düşünmeden kendi kafamı kâğıda dökebilmek. Eğitimime devam etmek ve daha düzenli bir ortamda kendimi geliştirmek istiyorum. İş, staj, kendimi geliştirecek şeyler arıyorum. Bu yazılardan da anlaşılıyor ki kafam çok dağılıyor. Heyecanım ve disiplinsizliğim, sezgilerime ve hedeflerime giden yolda bir engel oluyor.

---

Bu belgeyi derlerken yapay zekâ kullandım. Çünkü tonlarca dosyam, sayfalarca fiziksel kâğıdım var ama yanımda kimse yok.

James Augustus
