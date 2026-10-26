# Hunter'a giden yol

Bu günlüğü kendi cümlelerimden ve memo kayıtlarımdan derledim. Çoğu o an aldığım ani notlardı. Sohbet sırasında verdiğim yönergeleri ve parçalı ifadeleri, anlamlarını koruyarak birinci tekil şahısla yeniden anlattım. Bu bölümler birebir alıntı değildir. Tırnak içinde bıraktığım ifadeler kayıtlı sözlerimdir. Özgün kayıtları arşivimde koruyorum.

---

## 1. Tek sayfa özet

Bu bir kanıt defteri değil. Kafamın adım adım nereye yürüdüğünün kaydı: bir şeye takıldım, kendime sordum, bir şey denedim, sonuç beni başka bir yere götürdü. Tarih ve saatler bu yürüyüşün sırasını gösteriyor. Kısa matematiksel gerekçeler 3. bölümde, sonlu hesap kontrolleri 4. bölümde. Testin geçmesi tek başına genel kanıt değildir.

Makinenin adı başta CT-CPU'ydu. 30 Ağustos 2026'da onu baştan yazmaya karar verdim. Hunter adıyla devam etti. Bu belgede ikisi aynı projenin farklı dönemleridir. CT-CPU tamamlanmış bir işlemci olarak sunulmuyor. Hunter onun devamıdır.

Gölge, bir sayının asal çarpanlarını ve üslerini tuttuğum ikinci gösterim. Bu gösterimde çarpma üsleri toplamaya, bölme üsleri çıkarmaya dönüşüyor. RS, shadow register demek. `RS1[e3=7]`, birinci gölge register’ında 3 asalının üssünün 7 olduğunu gösteriyor. LOG 020’de bu yazımla 3^11’i iki gölge register’ına ayırmayı önerdim.

Tam bir yıldır iki şeyle uğraşıyorum: kendi işlemcimi tasarlamak ve Mersenne sayılarıyla oynamak. Burada "buldum" demeyeceğim. Buradakilerin çoğu "acaba bu böyle midir" diye kendime sorup sonra denediğim şeyler. Bir kısmı tuttu. Bir kısmı yanlış çıktı. Bir kısmının yüzyıllardır bilindiğini de sonradan öğrendim. Hepsini kendi cümlelerimle, sırasıyla yazıyorum.

[D]101: sayının ikilikte 101 ile bittiğini, önündeki kısmın D olduğunu gösteren yazım, yani sayı = 8D + 5. p ≥ 3 ve k ≥ 0 tam sayıları için (3+8k)·M_p sayılarının hepsi böyle biter.

*"Galiba Pascal benim işlemcimi benden önce yapmış sanırım, ve cevap zaten onda."*

Hangi fikir hangisini tetikledi, kısaca şöyle. Tarihlerin hepsi 2026.

| Tarih | Ne oldu | Neyi tetikledi |
|---|---|---|
| 21 Nisan | CT-CPU tarifi: renk etiketli xbit ve sekizlik, Mersenne üsleri 3'e göre R ve Y | Sekizlik dil, 1-3-7'nin içerik kökü |
| 23 Nisan | LOG modu: çarpma indeks toplamı | Gölgenin ilkesi |
| 13 Mayıs | Bir xbit alanı sekiz türü seçer | Bugünkü TÜR hücresi |
| 8 Haziran | Doom isteğinden CT-CPU'ya, 1 xbit = 3 bit = 1 renk, "Karar: KESİN" | Bütün makine dili |
| 9 Haziran | Gölge: çarpma üs toplama, bölme üs çıkarma | Resolver, rough, tembel gölge |
| 16-19 Haziran | Mersenne xbit deseni: W, RW, YW | Oktal Mersenne desenleri |
| 20-22 Haziran | Tek merkezi gölge çözücü, mod 7 hane toplamı | Hane akıtma |
| 18 Temmuz | Manifesto: iki yüz, 3,75 bit sınırı, Tanrı zar atmaz | Kabul ölçütleri |
| 26 Temmuz | M_p = baş hane + 7'ler, q = 2kp + 1 yazılı | Elek kapıları |
| 26 Temmuz ile 2 Ağustos arası | Sayan makine, KATLA = mod M_p (sonraki derlemeden) | Vida ve tur |
| 29 Temmuz | Motor temsile bağlanır, Mersenne test yatağı, 8 opcode | Hunter'ın sade ISA'sı |
| 2 Ağustos gecesi | R, Y, W yerine 1, 3, 7 | 1-3-7 evreni |
| 5 Ağustos | 1-3-7 çetele evreni | Üç baş, paket |
| 21 Ağustos | "dünyada var mı?", Euler ve Fermat eşleşmesi | Bilinenleri ayırma alışkanlığı |
| 30 Ağustos | Horner zinciri "235", taşmalı hane sorusu | C/T/A, [D]101 |
| 31 Ağustos | "121 = 11 kere 11", gölge LL'e yardım etmiyor, p = 3q + r, taban 8 onayı | Pascal, paket |
| 1 Eylül gecesi | 1331 her tabanda, eldesiz evren, "en önemli sayı 3" | 11 formülü, Taban^0 |
| 2 Eylül | Pascal gecesi, eşik C(n, ⌊n/2⌋) + 1 | Merdiven |
| 2-3 Eylül | Teori derlemesi: C/T/A, üç baş, çarpan yasası, vida, kutu | Testler |
| 7 Eylül sabahı | İmza süzgeci 51. ve 52. üste bozuldu, paketli elek, 11 ölçeği | Elek turu |
| 15 Eylül | Ters Mersenne P, [D]101 ailesi, Taban^0 adı | Özgüllük testi |
| 25 Eylül | Scott kitabından HunterCPU | Saf CPU kitabı (1 Ekim) |
| 1 Ekim gecesi | İkilik katlama ile 13, 31, 127, "p >= 2" itirazı | Açık sezgiler |
| 10 Ekim | 182 teori, testli liste, [D]101 ispatı | Bu belge |
| 11-12 Ekim | Merdiven adımı: a_(n+1) = a_n + kom_n, flip-flop | Toplayıcı devre |
| 12 Ekim | Taban 3'te zincir, 121'de beşli dönüş | 11'in izi |
| 13-14 Ekim | Mersenne tabanında 2'nin kuvveti: temiz Pascal satırı, 52 üs | Vardığım yer |

---

## Nasıl çalışıyorum

Python dili benim için hâlâ çok iyi değil, hâlâ algılamaya çalışıyorum. C'de bile iyi değilim. Bazen o bile bana yüksek seviye geliyor. Büyük sayılar için GMP kütüphanesine ihtiyacım olduğunu da biraz geç fark ettim. Tabii ki yapay zekâdan yardım aldım. Python ile bir LLM modeli bana pek farklı gelmiyor: ikisinde de yazıyorsun, o hallediyor.

Ben daha çok dişlilere, çarklara, tork gibi şeylere yakınım. Fizikçiyim, ama klasik mekanik bana daha kuantize geliyor, kuantum fiziği ise daha analog, daha hassas ve belirsiz.

Adım adım, kesin ilerlemeyi seviyorum. İnsanların ne dediklerini de çoğu zaman tam anlayamam. Kesinliği ve netliği sevdiğim için yüksek seviyeli her şey bana soru işaretleriyle geliyor. Çocukken bir hevesle QBasic öğreniyordum. Bu kesin konuşma takıntısı belki oradan başladı. "Eğer bu buysa şu da şudur, o zaman buraya git" komutları bana hep daha basit geldi. Sanırım daha az sorumluluk taşıdıkları için.

İronik olan şu: 1 ve 0'da rahatım, ama 0 ile 7 arasında bir cebir kurmaya uğraşıyorum. Bu belgedeki testlerin ana hali bu yüzden C ile yazıldı.

## 2. ADHD günlüğü

Her kayıt aynı kalıpta: ne sezdim, kendime ne sordum, neye baktım ve ne denedim, sonuç ne, beni nereye götürdü, ne öğrendim. Kaydetmediğim alanı boş bırakmadım, hiç yazmadım. Mersenne kolunun Haziran ile Ağustos arasındaki özgün kayıtlarını bu yayına dahil etmedim. O dönem yalnız sonraki derlemelerdeki izlerle duruyor.

Elimdeki en eski yazılı kayıt Nisan 2026'dan. Ondan önceki aylar bu günlükte yok. O dönemin yazılı kaydı elimde değil.

LOG 048-061 bu derlemeye alınmadı.

### LOG 001, 21 Nisan 2026, Renkli yardımcı işlemci

**Araştırma ve test:** CT-CPU (bugünkü Hunter) makinesini renk etiketli register’ları ve sekizlik gösterimi olan bir yardımcı işlemci diye tarif ettim. Mersenne asal üslerini 3'e göre sınıflarına ayırıp R ve Y renkleriyle işaretledim. Mersenne sayılarını her hanesi bir renk harfi olan sekizlik bir tabloya dizdim. Ardışık asalların 3'e göre geçişlerini saydım. Son hane yanlılığını Lemke Oliver ve Soundararajan 2016'da yayımlamış. Makaleyi sonradan öğrendim. Bu beni motive etti. Kendimi daha çok eğitmeliyim, çünkü kâğıt kalemle buralara gelebildim. Beni motive eden bir şey daha var: düşündüğüm şeyleri birilerinin daha önce bulmamış olmasını düşünmek aslında çok saçma olurdu. Amerika ben keşfetmeden önce de zaten oradaydı. Kâğıt kalemle hızlıca buralara kadar gelebilmem ise beni çok ama çok ayrıca motive ediyordu. Fizik okurken öğrendiklerimi gerçekten anladım. Bir şeylerde başarılı olmak onları anladığımız anlamına gelmiyor. Buradan çıkardığım asıl ders buydu.\

**Sonuç:** LİTERATÜRDE. 52 Mersenne üssündeki sayımım yanlılık göstermedi. İstatistik olduğu için hüküm saymadım.\

**Götürdüğü yer:** → LOG 004 (xbit), → LOG 006 (Mersenne xbit deseni)

### LOG 002, 23 Nisan 2026, LOG modu

**Araştırma ve test:** Çarpmayı log indekslerinin toplamı, bölmeyi farkı olarak yapan bir "LOG modu" yazdım.\

**Sonuç:** AÇIK. Ertesi gün tek xbit çarpma ve bölme testi yazıldı, koşum çıktısı yok.\

**Götürdüğü yer:** → LOG 005 (gölge)

### LOG 003, 13 Mayıs 2026, Sekiz tür

**Araştırma ve test:** Bir xbit alanının sekiz türü seçmesine karar verdim.\

**Götürdüğü yer:** → bugünkü TÜR hücresi (3. bölüm)

### LOG 004, 8 Haziran 2026, Doom'dan işlemciye: xbit

**Araştırma ve test:** Doom'u assembly ile yazmak istiyordum. Önce işlemcinin nasıl çalıştığını anlamam, sonra kendi işlemcimi tasarlamam gerekiyordu. Işıkla hesap: üç ışık kanalı sekiz renk verir, sekiz renk bir sekizlik hane eder. 1 xbit = 3 bit = 1 oktal hane = 1 renk. Günlüğe "Karar: KESİN" yazdım.\

**Götürdüğü yer:** → LOG 005, bütün makine dili buradan

### LOG 005, 9 Haziran 2026, Gölge

**Araştırma ve test:** LOG modunun ilkesini log yerine asal üslerle kurdum. Her sayının yazısının yanında bir de gölgesi var. Gölgede çarpma üs toplama, bölme üs çıkarma. 13 Haziran'da önceki çalışmaları taradım: Gödel numaralaması (1931), logaritmik sayı sistemi (1971).\

**Sonuç:** LİTERATÜRDE. Gölgenin kuralı aritmetiğin temel teoremi (T13_shadow_vector).\

**Öğrendiğim:** Barmenken bunları epey yapıyormuşum, bunu fark ettim. Haziran'da kendime şunu yazmışım: "Kendim buluyor, sonra literatürde görüyorum (convergent insight)"\

**Götürdüğü yer:** → LOG 007, → LOG 008\


### LOG 006, 16-19 Haziran 2026, Mersenne xbit deseni

**Araştırma ve test:** 2^p − 1'i p'nin 3'e göre sınıfına göre W, RW ya da YW diye yazdım.\

**Sonuç:** TUTTU. Temmuz'da p = 5..127 arasındaki 10 örnekte istisna çıkmadı. Genel hali T05_137_octal_head.\

**Götürdüğü yer:** → LOG 010, → LOG 013

### LOG 007, 20-22 Haziran 2026, Gölge çözücü ve hane akıtma

**Araştırma ve test:** Tek merkezi bir gölge çözücü kurdum. 7'ye göre kalanın sekizlik hanelerin toplamının 7'ye göre kalanı olduğunu yazdım. Bölücüsüz kalan yürüyüşüne hane akıtma dedim.\

**Sonuç:** LİTERATÜRDE. Bu, Horner'ın 1819 şeması. Kendi notumda "Horner gibi bir yazılım bu sanki." demişim (T12_digit_flow).\

**Götürdüğü yer:** → LOG 011

### LOG 008, 18 Temmuz 2026, Manifesto

**Araştırma ve test:** Manifestomu yazdım: her sayı iki yüzle yaşıyor, gölgenin 3,75 bit sınırı, sonra eklediğim "Tanrı zar atmaz".\

**Götürdüğü yer:** → 7. bölüm, manifesto, makinenin kabul ölçütleri

### LOG 009, 18-19 Temmuz 2026, Kenarı tut

**Araştırma ve test:** Karekökü hesaplamak yerine kenarı tutma fikrini yazdım.\

**Sonuç:** LİTERATÜRDE. Wildberger'in rasyonel trigonometrisine benziyor, bunu sonradan gördüm.

### LOG 010, 26 Temmuz 2026, Baş hane, 7'ler, çarpan yasası

**Araştırma ve test:** M_p'yi bir baş hane ve ardından 7'ler diye yazdım. Bir görev dosyasında q = 2kp + 1 yazılı.\

**Sonuç:** LİTERATÜRDE. Bölenlerin q = 2kp + 1 biçimini Fermat 1640'ta biliyormuş, q ≡ ±1 (mod 8) koşulunu Euler 1750'de eklemiş (T03_factor_law). Araştırınca bunun bilinen bir sonuç olduğunu gördüm.\

**Götürdüğü yer:** → LOG 031

### LOG 011, 26 Temmuz-2 Ağustos 2026, Sayan makine ve KATLA

**Sezgi:** Mod sözcüğüne alışamamıştım. Bir sayıyı bölüp kalanı yazmak bana yabancı geliyordu. Aynı işlemi başka bir hareket üzerinden anlamak istiyordum.\

**Araştırma ve test:** 2^p ≡ 1 (mod 2^p − 1) olduğu için yüksek bitleri alçak bitlere ekleyip bölmeden kalan buldum. Buna KATLA dedim. Ona sayan bir makinenin turu diyordum.\

**Sonuç:** LİTERATÜRDE. Mersenne modunda bilinen uç uca elde yöntemi. Vidanın altındaki hesap çarpımsal mertebe. Eylül sonunda 45.056 kimlikte doğrulandı.\

**Götürdüğü yer:** → LOG 019, → LOG 078\

**Öğrendiğim:** "Katla" dediğim şey mod hesabının ta kendisiymiş.

### LOG 012, 29 Temmuz 2026, Temsil kararı

**Araştırma ve test:** Kararım: Motor matematiğe değil temsile bağlanır, Mersenne test yatağıdır. Komut kümesini sekiz opcode'a indirdim.\

**Götürdüğü yer:** → Hunter'ın sade komut kümesi (3. bölüm)

### LOG 013, 2 Ağustos 2026 gecesi, R, Y, W yerine 1, 3, 7

**Sezgi:** 734 tane 7 yazmak yerine bu tekrarın sayısını tutabileceğimi düşündüm. O sayı da çok büyüdüğünde 2^p biçimindeki bir gösterime başvurmayı düşünüyordum.\

**Araştırma ve test:** Renk harfleri yerine 1, 3, 7 yazmaya başladım.\

**Götürdüğü yer:** → LOG 014

### LOG 014, 5 Ağustos 2026, 1-3-7 çetele evreni

**Sezgi:** "21. elma 2. kutuya girdi diye 2. kutu '20' demek değildir, ortada 20+1 elma vardır."\

**Araştırma ve test:** 1, 3, 7'yi birer işaret saydım. Adet sayıyorlar. Buna bir sayı evreni dedim.\

**Götürdüğü yer:** → LOG 028, → LOG 031

### LOG 015, 21 Ağustos 2026, Dünyada var mı?

**Soru:** Yaptığım projeye benzeyen başka projeler olup olmadığını merak ettim.\

**Araştırma ve test:** Dönen araştırma dört Mersenne bulgumun Euler'de ve Fermat'ta bilindiğini gösterdi.\

**Sonuç:** LİTERATÜRDE. p ≡ 3 (mod 4) ve 2p + 1 asal ise 2p + 1'in M_p'yi bölmesi Euler'in (T04_euler_2p_plus1).\

**Öğrendiğim:** Bilineni ayırmayı alışkanlık edindim.

### LOG 016, 25 Ağustos 2026, Sağdan bölme

**Araştırma ve test:** Sayıyı en düşük haneden başlayarak bölen bir yürüyüş kaydettim.\

**Sonuç:** LİTERATÜRDE. Montgomery'nin 1985'teki modüler çarpma yöntemine yakın.

### LOG 017, 30 Ağustos 2026, Taşmalı hane

**Soru:** 10^7 olan bir sayıyla 10^3 çarpanı olan başka bir sayıyı toplarken, 10^3 parantezine alıp 10^4 ile 10^0 üzerinden çalışıp çalışamayacağımı sordum.\

**Araştırma ve test:** Horner zincirini "235" üstünde yürüttüm.\

**Götürdüğü yer:** → LOG 025, → LOG 036

### LOG 018, 31 Ağustos 2026, İki kol birleşti

**Sezgi:** Mersenne çalışmasıyla işlemci fikrimin aynı noktada buluştuğunu düşündüm.\

**Araştırma ve test:** Mersenne çalışması ile Hunter'ı aynı yerde topladım. Kafamda onluk düşünüp sekizlik yazıyordum. Hesabın yapıldığı tabanla sonucun yazıldığı tabanı birbirine karıştırmamaya çalıştım. Elle yazdığım liste 1'den 12'ye üslerin sekizlik karşılığıydı: 1, 3, 7, 17, 37, 77, 177, 377, 777, 1777, 3777, 7777.\

**Götürdüğü yer:** → LOG 019, → LOG 028

### LOG 019, 31 Ağustos 2026, 21:54, Gölge Lucas-Lehmer'e yardım etmiyor

**Araştırma ve test:** Lucas-Lehmer kalanında bit düzeyinde katlama ile sekizlik hane katlamasını karşılaştırdım. Kaçış için üssü p = 3q + r diye ayırdım. Kararım: önce işlemci bitecek, LL sonra.\

**Sonuç:** TUTMADI. Bit katlama 500 denemenin 500'ünde doğru, sekizlik hane katlaması p = 7'de 500'de 22, p = 13, 17, 31'de hiç. 8^k − 1 ancak p 3'ün katıysa M_p'ye denk geliyor. Kayıt başlığı: "Oktal ve gölge LL'e yardım etmiyor".\

**Götürdüğü yer:** → LOG 031 (p = 3q + r ayrıştırması paketin temeli oldu)

### LOG 020, 31 Ağustos 2026, 3^11 ve 121

**Sezgi:** Sekizlik tabanda 2·5·8+1 ifadesinin 121 yazılmasına takıldım, bunu 11 kere 11 ile ilişkilendiriyordum. 2·5 onlukta 10 ediyordu, 10·8+1 sayısını 10 ve 1 diye, yani on bir gibi okuyordum. (2·5·8+1)·3^7 ifadesinden 121x3^7 sonucuna gidiyordum. 121 ile kare arasındaki ilişkiyi henüz kanıtlayamıyordum. Bu aşamada yalnız bir sezgiydi.\

**Araştırma ve test:** 3^11'i gölgede kademe kademe indirdim: 8v + a = 81, v = 10, yani 2 × 5. 3^11'i iki gölge satırına "RS1 [e3=7] RS2 [e3=1]" diye bölmeyi önerdim. RS, shadow register, yani gölge register’ı. Bir hücre en çok 7 tutar. Bu yüzden 3^11 = 3^7 · 81 diye bölünür ve RS1[e3=7] olur. Kalan 81, sekizlikte 121₈. 1 çıkınca 120₈, 8'e bölününce 12₈ kalır. Sekizlikte 12₈ = 2 · 5 (2² · 3 değil, o 14₈ eder). Yani doğru ikinci satır RS2[e2=1, e5=1 | a=1]:

```
rs1 = [e3 = 7]                   3^7 = 4213₈
rs2 = [e2 = 1, e5 = 1 | a = 1]   12₈ = 2·5,  a = 1  →  121₈
(12₈ · 10₈ + 1) · 4213₈ = 121₈ · 4213₈ = 531773₈ = 3^11   ✓
```

2·5·8+1 ifadesini 121 olarak okumamın karşılığı tam buydu: 2 · 5 · 10₈ + 1 = 121₈.

**Sonuç:** TUTMADI. 3^7 × 24 = 52488 çıktı, 177147 değil. Ama hata bana 121'i gösterdi.\

**Götürdüğü yer:** → LOG 021, → LOG 022

### LOG 021, 31 Ağustos 2026, Kareler ve taban 11

**Sezgi:** 121_2’den 121_16’ya uzanan yazımlar arasında 9, 64, 81, 121, 289 gibi sayılara bakıyordum. Bunlar bana kurmaya çalıştığım sayı evreninin asalları gibi geliyordu.\

**Soru:** 11 tabanının daha uygun olup olmayacağını ve Hunter için 11 tabanlı paralel bir sayı evreni kurup kuramayacağımı düşündüm.\

**Araştırma ve test:** 11 neden özel? Elimde "çünkü 11 güzel simetrik en küçük asal. cevap buralarda." vardı. sekizlikteki 11'in onlukta 9 olduğunu görünce düzelttim: "simetrik olan en küçüğü dedim. başka simetrik yok zaten çünkü bir unicorn." Kararım: "onaylandı taban 8".\

**Sonuç:** TUTMADI. Karelerin sekizlikte palindrom olduğunu düşünmüştüm, 1 ile 200 arasındaki karelerin yalnız yüzde 6,5'i palindrom.\

**Götürdüğü yer:** → LOG 022

### LOG 022, 1 Eylül 2026 gecesi, 1331 her tabanda

**Sezgi:** 10 tabanında 11’in kübünün 1331, 11 tabanında 12’nin kübünün 1331, 12 tabanında 13’ün kübünün yine 1331 yazılmasına baktım. Pascal’ın benim işlemcimi benden önce yapmış olabileceğini, aradığım cevabın orada durduğunu düşünüyordum.\

**Araştırma ve test:** Taban bir artınca sayıyı da bir artırdım, yazı aynı kaldı. b tabanında (b + 1)^3 = 1331.\

**Sonuç:** LİTERATÜRDE. 11'in kuvvetleri Pascal satırları, binom teoremi (T07_pascal_11).\

**Götürdüğü yer:** → LOG 023, → LOG 024, → 3. bölüm, eşik yasası\

**Öğrendiğim:** Bu fikre sonradan "11 bir formüldür" adını verdim.

### LOG 023, 1 Eylül 2026 gecesi, Carrysiz evren

**Sezgi:** Notumdaki parçalı 121 x 11 = 11 ifadesinin ardından hesabı 121x10 + 121 üzerinden anlatmaya çalışıyordum. İlk ifade doğru bir eşitlik değil, o anki tamamlanmamış notumdu. Ardından 14641*11 = 14641x10 + 14641 yazıp katsayıları elde taşımadan 15101051 diye yan yana koydum. Bunu eldesiz bir sayı evreni olarak düşünüyordum. Normal onluk hane yazımıyla aynı şey değildi.\

**Soru:** 11’e bölünebilme kuralını sekizlikte 9 üzerinden okuyup okuyamayacağımı ve Horner açılımının burada ne göstereceğini merak ettim. Bütün binomların 11’in katı olup olmadığını da sordum.\

**Araştırma ve test:** 11'i her tabanda b + 1 diye okudum. 11 ile çarpmak, 10 ile çarpıp yüzde 10 eklemektir. Bu yalnız onluk sistemde böyle görünür.\

**Sonuç:** LİTERATÜRDE. 11_b = b + 1 yazının tanımı (T09_11_base_value).\

**Götürdüğü yer:** → LOG 076, → LOG 036

### LOG 024, 2 Eylül 2026, 04:07, Merdiven ve Pascal gecesi

**Sezgi:** 1010001 gibi yazımlar ortaya çıktığında palindromun kaydığını düşünüyordum. Tam o noktada 11’in 12 olmasını, değişenin taban değil sayı olması üzerinden anlamaya çalıştım.\

**Soru:** Pascal açılımına bakarken tabanı neden daha önce 11, 12, 13, 14 diye artırmadığımı kendime sordum.\

**Araştırma ve test:** Eldenin ne zaman başladığına baktım. Kırılmayı n değil, orta katsayı belirliyor.\

**Sonuç:** TUTTU. 11^n'i eldesiz yazmak için en küçük taban C(n, ⌊n/2⌋) + 1 (T08_threshold_law). Pascal gecesi bu saatte Hunter arşivine girdi.

[Pascigon: −15 ile +15 satırları (PDF)](../pdf/Pascigon.pdf)

**Götürdüğü yer:** → 3. bölüm, eşik yasası, → LOG 032\

**Öğrendiğim:** Sayı büyüdükçe taban bir basamak çıkıyor. Buna evren merdiveni dedim. Derlemedeki cümlem: "n=11'de içindeki evrende yeniden başlıyor... hedef o evrenin 11'ine ulaşmak gibidir belki."

### LOG 025, 2-3 Eylül 2026, C/T/A imzası

**Sezgi:** Altı haneli oktal sayıları Horner açılımıyla çift, tek ve asal diye işaretleyen bir şablon düşündüm. Başı C ile başlayıp sonucu A çıkan 15 örneğe bakıyordum.\

**Araştırma ve test:** Altı haneli sekizlik sayıları Horner açılımıyla adım adım okudum. Her ara değere C (çift), T (tek) ya da A (asal) koydum.\

**Sonuç:** TUTMADI. 242 imzanın 242'sinde hem asal hem bileşik var. 500021₈ ile 500023₈ aynı imzayı taşıyor. Elle yaptığım tablodaki bir "A" da yanlıştı: 400037₈ = 131103 = 3 × 43701.\

**Götürdüğü yer:** → gölgenin bugünkü kademeli hali ve CLIMB (3. bölüm)\

**Öğrendiğim:** Horner okumasını buradan öğrendim.

### LOG 026, 2-3 Eylül 2026, Teori derlemesi

**Sezgi:** Kurduğum sayı evreninin, 1’den 12’ye üslerin Mersenne hallerindeki oktal karşılıklarıyla ilişkisini fark ettim. 23’ün bir eksiği 22 = 11x2, 89’un bir eksiği 88 = 11x8 ediyordu. İkisini de 11’e bölündüğünde 1 kalanını veren sayılar olarak okuyordum.\

**Araştırma ve test:** C/T/A, üç baş, çarpan yasası, vida ve kutuyu tek derlemede topladım.\

**Sonuç:** LİTERATÜRDE. 23 ve 89'da gördüğüm, Fermat ve Euler'in çarpan yasası (T03_factor_law).\

**Götürdüğü yer:** → LOG 029

### LOG 027, 2-3 Eylül 2026, Lucas-Lehmer'in sonundaki kare

**Sezgi:** Sayıları küp olmaya çalışırken parça bulamayınca 1 azalan cisimler gibi düşünüyordum. Sonunda bir kare oluşması gerektiği sezgisine kapıldım.\

**Sonuç:** Genel bir modüler karenin varlığı asallığı ayırmıyor. Bu, Lucas-Lehmer dizisinin son adımıyla aynı ölçüt değildir. Tanımlanmamış “kare mührü” T10’da SINANAMADI olarak kalıyor. Kare her tek p'de var: (2^((p+1)/2))² = 2^(p+1) ≡ 2 (mod M_p). Bileşik M_11'de de 64² mod 2047 = 2 (T10_square_seal).\

**Öğrendiğim:** Bir eşitliğin her yerde doğru olması onu ayırıcı yapmıyor.

### LOG 028, 4 Eylül 2026 gecesi, Baş hane ve renk kapısı

**Sezgi:** Sekizlikteki Mersenne asal yazımlarında başta 1 ya da 3, devamında 7’ler görüyordum. R ya da Y’den sonra White gelen bu yazıyla renklerden bir kapı kurmak istedim. O notta 3 ve 3 tane 7 üzerinden baktığım iki sayıdan söz ediyordum. 23 ve 89’un, 11’in katının bir fazlası oluşunu da aynı örneklerde izliyordum: k*11+1. 1, 3, 7, 17, 37, 77 dizisini Mersenne sayıları için bir gösterim olarak düşünüyordum. 3777, p = 11’e karşılık geliyordu. R’ye G eklendiğinde Yellow, blue da eklendiğinde White oluşmasıyla bir bağ kuruyordum. CT-CPU assembly’sinde 63! ifadesini açmadan, paket olarak donanımda taşıyabilmeyi istedim.\

**Sonuç:** TUTTU. Baş hane p'nin 3'e göre kalanına bağlı: p = 3t + 1 ise 1, p = 3t + 2 ise 3 (T05_137_octal_head). Nedenini ben bulmadım, sonradan öğrendim.\

**Götürdüğü yer:** → LOG 031 (açmadan paketle)\

**Öğrendiğim:** Baş hane asallığı ayırmıyor: M_5 asal, M_11 bileşik, ikisinin de başı 3 (T06_head_digit_primality, tutmadı).

### LOG 029, 5 Eylül 2026, 00:48, p = 37 ve ilk büyük tur

**Soru:** p = 37’nin 1-3-7 gösteriminde nasıl yazıldığını görmek istedim.\

**Araştırma ve test:** 323 iddiayı iki ayrı yoldan denedim.\

**Sonuç:** AÇIK. 302 geçti, 3 kaldı, 18 kararsız. Kuadratik üreteç M² + 10M + k tutmadı: M = 3, k = 3 için 42 (T14_quadratic_generator).\

**Götürdüğü yer:** → LOG 080 (kalan üç iddia)

### LOG 030, 7 Eylül 2026, 03:55, İmza süzgeci bozuldu

**Soru:** Tek tek sayılarda çalışan örnekler yerine hepsini kapsayan bir algoritma veya yöntem arıyordum.\

**Araştırma ve test:** İlk 50 Mersenne üssünden 44 imzalık sabit bir küme kurmuştum.\

**Sonuç:** TUTMADI. 51. üs (82.589.933) ve 52. üs (136.279.841) kümenin dışında kaldı. 649 bileşik kontrolünün 116'sı süzgeçten geçti. İmza aslında p'nin belli bir sayıya göre kalan sınıfıymış (T17_signature_filter).\

**Götürdüğü yer:** → LOG 031

### LOG 031, 7 Eylül 2026, 04:12, Paketli elek

**Soru:** Mersenne asalları için kurduğum eleğin işe yarayıp yaramadığını sorguladım. 04:37’de Lucas-Lehmer adımlarını yalnız gidişatını yazarak hızlandırıp hızlandıramayacağımı da düşündüm.\

**Araştırma ve test:** Kararım: M_P'yi açmadan bir paket olarak tutmak. 04:07'de yazdığım iki dosyanın üstüne: M_P = (h + 1) · 8^t − 1, t = ⌊(P − 1)/3⌋, h = 2^s − 1. Bölen adayları q = 2kP + 1 ve q ≡ ±1 (mod 8). M_P'nin q'ya göre kalanı paketten. 04:22'de eleği sade bir metin olarak yazdırdım. Aday araması GIMPS'in küçük bölen aramasıyla aynı aileden.\

**Sonuç:** TUTMADI, hüküm olarak. Elek bir süzgeç: M_41'in böleni 13367 (k = 163), ilk 64 adayda yok (T11_packed_sieve). Paket yazımının kendisi tuttu (T05_137_octal_head).\

**Götürdüğü yer:** → LOG 032, → 3. bölüm, paket yazımı

### LOG 032, 7 Eylül 2026, 05:18, 11 ölçeği

**Araştırma ve test:** Paketi 2^11 tabanında okuyan bir ölçek modeli ekledim. Paket ile 11 ölçeğinin birleşimi için bir kaynak bulamadım.\

**Sonuç:** AÇIK.

### LOG 033, 7 Eylül 2026, Sıfırsız taban

**Sezgi:** Sayıyı içinde 0 bulunmayan bir tabanda yazmak istedim. Her şeyi 11 yazımı üzerinden düşünüyordum: unaryde 1 ve 1, yani 11. 2’yi bu nedenle ilk çift olarak okuyordum.\

**Sonuç:** TUTMADI. P = 23 ve P = 67 sıfırsız yazılabiliyor, ama M_P bileşik.\

**Götürdüğü yer:** → LOG 040

### LOG 034, 7 Eylül 2026, Elde sayısı

**Araştırma ve test:** Toplamada kaç kez elde doğduğunu saydım. Buna elde sayısı dedim.\

**Sonuç:** LİTERATÜRDE. Kummer'in 1852 teoremi: asal tabanda toplamadaki elde sayısı, binom katsayısındaki asal üssünü veriyor.

### LOG 035, 8 Eylül 2026, 18:22, Sekizlikte p = 35

**Sezgi:** Baştaki 7’yi bir istisna olarak görmüyordum. 0 kullanmadan 1, 11, 111 diye ilerleyen yazımla 7, 77 sonrasında 1 ve 3’ün belirmesi arasında ilişki kuruyordum. 67’yi 11’in doyumu gibi düşünüyor, 6x11+1 sıçramasını bu doyuma bağlıyordum.\

**Soru:** Hunter sekizlik çalıştığında bu gösterimden bir kazanç çıkıp çıkmayacağını merak ettim.

**Götürdüğü yer:** → LOG 037

### LOG 036, 10 Eylül 2026, Araya bir şey sıkıştırmak

**Sezgi:** 11’in içine iki 0 koyup 1001 elde etmeyi, 101’in karesini ve 11001 gibi yazımları düşünüyordum. Arayı açıp içine bir şey yerleştiren özel bir toplama biçimi arıyordum.\

**Soru:** 13’ü 1 11 veya 01 11 diye yazmayı düşündüm. 17’yi 10001 diye yazmak yerine 1 111 gibi paketleyip onu yorumlayan bir okuyucu bırakıp bırakamayacağımı sordum.\

**Araştırma ve test:** Sayıyı [D1, D0, B] diye taban etiketiyle yazdım.\

**Sonuç:** TUTMADI. En iyi kod 11 bit, düz ikili 8 bit. Bit kazandırmıyor.\

**Götürdüğü yer:** → LOG 039

### LOG 037, 12 Eylül 2026, p ile 11

**Sezgi:** p’nin 11 ile ilişkili olduğu durumda q’nun bileşik, bu ilişki olmadığında ise kesin asal olabileceğini düşündüm.\

**Sonuç:** AÇIK. Nedenini açıklayamadım, "garanti" kısmını sınamadım.

### LOG 038, 15 Eylül 2026, 08:02, Ters Mersenne P

**Araştırma ve test:** Elime geçen notta bir desen vardı: P = 20996011 için ters(P) = 11069902, √356798503 = 18889,11069902... ve 18889 = 13 × 1453. Not bir konuşma çıktısıydı. Desene nasıl vardığımın kaydını bu yayına dahil etmedim. Yapay zekâ modeline formüllerimi yazdım, ne istediğimi yazdım, çünkü beynim sürekli daldan dala atlıyordu, hesaplayacak vaktim yoktu. Ben Ramanujan değilim. Notu bırakıp yalnız Mersenne ve Hunter açısından araştırılmasını istemişim.\

**Sonuç:** TUTMADI. Aritmetik doğru ama Mersenne'e özgü değil: aynı kural Mersenne olmayan 23, 29, 101, 1000 ve 4567 için de asal q buldu. "Her ters P özel bir asal yapı verir" iddiası P = 2, 3, 5, 7'de bozuldu. ters(p) asal üretmiyor: 19 → 91 = 7 × 13, 61 → 16, 127 → 721 = 7 × 103. Tur: 40 iddiada 27 geçti, 9 kaldı, 4 kararsız (T15_reverse_p_general).\

**Götürdüğü yer:** → LOG 039, → LOG 040, → LOG 085\

**Öğrendiğim:** İstatistik hüküm dayanağı değil. Kesin bilinenden geriye doğru gideceğim.

### LOG 039, 15 Eylül 2026, [D]101 ailesi

**Sezgi:** Eldeyi hemen taşımadan çalışmak istedim. Bunu unaryye benzer biçimde 10’ların dizildiği başka bir sayı evreni olarak hayal ediyordum.\

**Araştırma ve test:** Notta [11]101 yazısı vardı: ikilik bir yazının üst hanesine 11, değeri 11 · 8 + 5 = 93 = 3 × 31. Bunun bir ailenin p = 5 üyesi olduğu çıktı: D = 3 · 2^(p−3) − 1 + k · M_p için [D]101 = (3 + 8k) · M_p. Altındaki fikir, bir haneye tabandan büyük değer yazıp eldeyi geciktirmek, Avizienis'in 1961'deki fazlalıklı sayı sistemlerinde ve carry-save toplayıcıda var. Ailenin kendisini başka yerde görmedim.\

**Sonuç:** TUTTU. İspatı 10 Ekim'de yazıldı (T01_d101_family).\

**Götürdüğü yer:** → 3. bölüm, [D]101 ailesi

### LOG 040, 15 Eylül 2026, 14:19, Taban^0

**Sezgi:** İlk 2 ya da ilk 2 hane için istisna konmasına itiraz ediyordum. Bunun, pozisyonel yazımda gözden kaçırdığımı düşündüğüm Taban^0 ile ilgili olabileceğini sezdim. Unaryde 2’yi 1 ve 1, yani 11 olarak okuyup ilk ikiz diye düşünüyordum.\

**Soru:** Unaryde, 1 tabanında asallığın ne anlama geldiğini kendime sordum.\

**Sonuç:** LİTERATÜRDE. Sınanabilen kısmı bir son hane kuralı: taban bir asala bölünüyorsa, sayının o asala bölünüp bölünmediğini son hane söyler. Onluk tabanda 2 ve 5 için okulda öğrendiğimiz kural bu.\

**Götürdüğü yer:** → LOG 046, → LOG 084

### LOG 041, 15 Eylül 2026, Fibonacci

**Sezgi:** Önce Fibonacci formülünün yanlış olabileceğini düşündüm. Ardından yalnız bir önceki sayının toplanmasından farklı olarak, artışların da arttığı bir düzen görmeye çalıştım. Bunu ivme, sonra ivmenin ivmesi benzetmesiyle, artışların artışlara taşınması olarak tarif ediyordum.\

**Sonuç:** TUTMADI. "Yanlış formül" hükmü düştü. Artışın artışa taşındığı doğru çıktı: ardışık Fibonacci terimlerinin farkı yine Fibonacci.

### LOG 042, 16 Eylül 2026, Scott cpu

**Araştırma ve test:** Notuma "Scott cpu" yazdım. J. Clark Scott'un "But How Do It Know" kitabı, bir fikri önceden tetikleyen tek kaynak.\

**Götürdüğü yer:** → LOG 044

### LOG 043, 19 Eylül 2026, Ulam bandı

**Araştırma ve test:** Köşegeni sabit bir üç hanenin artan tabanda okunması olarak yazdım, iki kaydırma kuralı çıkardım. Ulam spirali 1963'ten beri literatürde. Ona nasıl geldiğim kayıtta yok.\

**Sonuç:** TUTMADI. Biri k = 5'te kırıldı: `4k² + 10k + 5 − 10⌊k/2⌋` kuralı 155 − 20 = 135 = 5 × 27 verdi, öbürü 299'da (13 × 23). "n, n − 10, n − 20'den biri asaldır" kuralı denenen 36 sayının 36'sında doğruydu, yani hiçbir şeyi ayırmıyordu.

### LOG 044, 25 Eylül 2026, HunterCPU

**Araştırma ve test:** Scott'un kitabındaki gibi sade bir Hunter görmek istedim. NAND kapılarından sade bir Hunter modeli kurdum.\

**Sonuç:** TUTTU. 6 × 7 = 42'yi 268 adımda hesaplıyor. 268 tik modelin saat adımıdır, hız ölçüsü değil, programın doğru bittiğini gösterir.\

**Götürdüğü yer:** → saf CPU kitabı (1 Ekim)

### LOG 045, 1 Ekim 2026, 00:57, İkilik katlama

**Sezgi:** 11, 1011 ve 9’un 1001 yazımını bölünme ve katlanma üzerinden karşılaştırıyordum, 1001 için iki kez katlanma gerektiğini düşünüyordum. 13’ün 1101 yazımında Mersenne asallığıyla bir ilişki gördüğümü sandım, 17’de aynı iz çıkmadı. 31’in 11111 yazımını üst üste katlayıp tek 1’e indirmeye çalıştım. 127’nin 1111111 yazımında 111 1 111, 101 1 101 ve 101 101 101 gibi bölümlere bakıyor, 121’in 3 katıyla bir bağ kuruyordum. 101, 111 ve 0 01 11 111 101 yazımlarında asallıkla ilgili bir düzen arıyordum.\

**Soru:** 11111 1 11111 yazımının Mersenne olup olmadığını sordum.\

**Araştırma ve test:** p'leri ikilikte yazıp ortadan katladım. Yazı tek bir 1'e iniyorsa ona "eşit katlanır" dedim.\

**Sonuç:** AÇIK. 13'te, 31'de ve 127'de M_p asallığıyla örtüştü. 17'de örtüşmedi: "olmuyor" demişim, oysa M_17 = 131071 asal. Neden bazı p'lerde tutuyor, 17'de neden tutmuyor? Açıklayamadım.\

**Götürdüğü yer:** → LOG 046

### LOG 046, 1 Ekim 2026, "p >= 2" itirazı

**Sezgi:** Mersenne kurallarındaki p >= 2 koşuluna itiraz ettim. 2’nin çiftliğini, belirli bir kapsamda 1 ve 1 olarak okunmasına bağlamaya çalışıyordum.\

**Sonuç:** AÇIK.

### LOG 047, 10 Ekim 2026, 182 teori

**Araştırma ve test:** Her şeyi 182 teorilik, testli bir listede topladım. [D]101 ailesinin ispatını yazdım.\

**Sonuç:** TUTTU. 40 kartlık testte 39 kartta karttaki hüküm doğrulandı, birinin testi yok.\

**Götürdüğü yer:** → bu belge: 3. bölüm (tutanlar) ve 4. bölüm (testler)

### LOG 062, 11 Ekim 2026, Merdiven üstel biçimde

**Sezgi:** 121’i 11’in yakınlaştırılmış hali gibi görüyordum. Aynı düşünceyle 1331’i 4 tabanında, 14641’i 7 tabanında okuyordum.\

**Soru:** 1, 3, 4^2, 5^3, 8^4, 12^5, 22^6 dizisini, tabanı her seferinde en büyük katsayının 1 fazlası seçerek ne kadar sürdürebileceğimi merak ettim.\

**Araştırma ve test:** Her satırı atomun üssü olarak yazdım. Atom ortadaki sayının 2 fazlası, taban 1 fazlası. n'inci satırda sayı atom^n. 0'dan 40'a kadar her satır kendi tabanında temiz yazıldı. Bir alt tabanda ise hepsi bozuldu.\

**Sonuç:** TUTTU. Ortaların dizisi literatürde var (OEIS A001405).\

**Götürdüğü yer:** → LOG 063\

**Öğrendiğim:** 22^6 sayısının 21 tabanında 1 6 15 20 15 6 1 yazıldığını gördüm. Bu katsayıları doğrudan okuyabiliyordum.

### LOG 063, 12 Ekim 2026, gece, +n kuralı kırıldı, Katalan çıktı

**Soru:** 5^3 sonrasında 5+3=8 ile 8^4’e, sonra 8+4=12 ile 12^5’e gidiyordum. Ama 12+5=17 beklerken 22^6 çıkmıştı. Bu değişimin kuralını arıyordum.\

**Sezgi:** Bir yerde unary bir adım veya faz farkı ekleniyormuş gibi düşünüyordum.\

**Araştırma ve test:** Her basamaktaki artışı satırdaki sayılarla yan yana koydum. "+n" yalnız n = 0, 1, 3, 4'te tutuyordu, çünkü n satırın ikinci sayısı. Gerçek artış ortadaki sayı ya da ortanın komşusu. Hepsini tek formülde toplayabildim:
```
a_(n+1) = 2·a_n − 2 − (1 − d_n)·Cat_(n/2)
```
Eksik kalan parça bir Katalan sayısı çıktı: orta eksi komşu. Lucas-Lehmer'e benziyor mu diye baktım. Benzemiyor, o karesel, bu doğrusal.

**Sonuç:** TUTTU, bu yazım benim. Altındaki binom LİTERATÜRDE.\

**Götürdüğü yer:** → LOG 065, sonra Katalan'sız yazdım (3. bölüm, Merdiven adımı)

### LOG 064, 12 Ekim 2026, 03:30-03:55, İki üçgen, 3^−1

**Sezgi:** n=0 durumundaki 3^0 ile bir önceki adımda düşündüğüm 3^-1 = 1/3 arasında ilişki aradım. 010, 0110, 01210 diye yukarı uzanan ikinci bir Pascal üçgeni hayal ediyordum. −1’in içe gömülüp tekrar çıkmasını astar benzetmesiyle düşünüyordum.\

**Araştırma ve test:** Pascal'ı negatif satırlara uzattım, −15'ten +15'e kadar çizdim. Satır −1, 1 −1 1 −1 diye sonsuza uzanıyor, katsayıların mutlak büyüklüğü 1 ile sınırlı. Burada “sınırlı”, satırın sonlu uzunlukta olduğu anlamına gelmiyor. Oradan taban 2, atom 3 yorumuna gittim, yani 3^−1 = 1/3. Negatif satırın formal kuvvet serisini x = 2’de sayısal toplam diye kullanamam: 1 − x + x² − … serisi yalnız |x| < 1’de yakınsar. x = 2’de 1/(1+x) = 1/3 değeri rasyonel ifadenin değerlendirmesidir, bu sonsuz serinin toplamı değildir. Pascal ile eksi Pascal toplanınca sıfır kalıyor. 00'dan 010'a geçiş kuralla gelmiyor. 1, sıfırdan doğan bir tohum gibi.\

**Sonuç:** TUTTU. Negatif satırların kendisi LİTERATÜRDE (genişletilmiş Pascal).\

**Götürdüğü yer:** → çizim Pascigon.pdf

### LOG 065, 12 Ekim 2026, 04:01-04:23, Fark formülü ve flip-flop

**Soru:** b.n(x) - b.n(x-1) farkını, b sayısından bir önceki seviyenin a veya b sayısını çıkararak incelemek istedim.\

**Sezgi:** Çift ve tek diye adlandırmak yerine durumu 1 ve 0 ile tutmak istedim. Bunu flip-flop gibi çalışan bir sayaç olarak düşünüyordum.\

**Araştırma ve test:** 1'den 30'a kadar farkları çıkardım. Çift ve tek yerine 0 ve 1 diye dönen bir sayaç koydum. Daha önce bulamadığım yineleme formülü buymuş:
```
d_0 = 0,  d_(n+1) = 1 − d_n
mid_n = C(n, (n − d_n)/2)
b_n − b_(n−1) = C(n − 1, (n − 2 − d_n)/2)
```
30 satırın 30'unda tuttu. Ortaya "M" demedim, "mid" dedim, M Mersenne'in harfi.

**Sonuç:** TUTTU.\

**Götürdüğü yer:** → LOG 066

### LOG 066, 12 Ekim 2026, 06:00, 254^10'u okumak

**Sezgi:** 254’ten 2 çıkarınca 252’nin orta katsayı olduğunu gördüm. Ortadan 5 hane sonra 1, 4 hane sonra 10 geleceğini düşünüyordum. Üçüncü hane için n·(n−1)/2 formülüne ulaşmıştım. Dördüncüyü henüz bulamamıştım. Önceki katsayıdan yardım alarak, toplamayla ilerleme fikrine de bakıyordum.\

**Araştırma ve test:** Ortadan uca adım adım gittim. Her sayı bir öncekinin (n − k)/(k + 1) katı. Bulamadığım 4. haneyi de buldum: n(n−1)(n−2)/6 = 120. 254^10, 253 tabanında 1 10 45 120 210 252 210 120 45 10 1 diye yazılıyor. Ayrıca satır 0'dan 30'a yalnız toplamayla gittim: yarısını hesaplayıp aynalayınca 225 toplama, hiç çarpma yok.\

**Sonuç:** TUTTU. Kuralın kendisi LİTERATÜRDE (binom). Ben ona satırı ortadan okuyarak vardım.\

**Götürdüğü yer:** → LOG 067

### LOG 067, 12 Ekim 2026, 06:09-06:20, Parçala, taban umrumda değil

**Sezgi:** Katsayıların 1 6 15 20 15 6 1 olduğundan emindim. Katsayı dizisini tabandan ayrı tutup taban değerini sonradan seçmek istedim.\

**Araştırma ve test:** 336^25'i 335 tabanında 10 + 10 + 5 diye parçaladım. Satırları çarptım, eldeyi en sonda taşıdım. Doğrudan hesapla karşılaştırınca 26 hanenin hepsi aynı çıktı. Değer kuralı her tabanda doğru: Σ C(n,k)·b^(n−k) = (b+1)^n. Sayıyı (b, n) çifti olarak tutuyorum. Çarpma da üsleri toplamaya dönüyor.\

**Sonuç:** TUTTU. Altındaki parçalar LİTERATÜRDE: Kronecker yerine koyması, carry-save, LNS/Zech (toplamayı çarpıma çevirme).\

**Götürdüğü yer:** → LOG 068

### LOG 068, 12 Ekim 2026, 06:27-06:33, Verilen sayı

**Soru:** 26321361382 gibi verilen bir sayıyı, bir tabanda Pascal biçimiyle nasıl ilişkilendirebileceğimi araştırdım.\

**Sezgi:** Verilen sayıyı mid olarak ele alabileceğimi düşündüm.\

**Araştırma ve test:** Sayıyı ortanın sınırı yaptım: taban N + 1, atom N + 2. Taban, satırın en büyük orta sayısından büyük kaldıkça satır temiz yazılıyor. Hangi satırın geleceği de belli oluyor: ortası N'yi geçmeyen en büyük satır. Bu sayı için o satır 37. satır:
```
1 37 666 7770 66045 435897 2324784 10295472 38608020 124403620
348330136 854992152 1852482996 3562467300 6107086800 9364199760
12875774670 15905368710 [17672631900] [17672631900] ... ayna
```
Yani (N + 2)^37, N + 1 tabanında tam bu. Çarpma yok: uçlar 1, satır aynalı, aradakiler toplamayla geliyor. 38. satırın ortası 35345263800, N'yi geçiyor, orada haneler taşıyor (T20_middle_by_addition).

**Sonuç:** TUTTU, 37. satıra kadar. Tabanı 11'den her sayıya genellemek LİTERATÜRDE (Jiu ve Vignat 2016, Islam ve arkadaşları 2020).\

**Götürdüğü yer:** → LOG 069

### LOG 069, 12 Ekim 2026, 06:34, Dünyada var mı (2)

**Soru:** Bu yol daha önce bulunmuş mu, ne kadar niş?\

**Araştırma ve test:** Kendi formülümü yazmadan, yalnız genel terimlerle aradım. Islam ve arkadaşları 2020'de (arXiv 2005.14490) tabanı orta katsayıdan seçmiş, ama 10'un kuvveti olarak. En küçük taban A051920'de, atom üssü merdiveni A193242'de, adım kuralı A001405'te kayıtlıymış.\

**Sonuç:** LİTERATÜRDE. T08 de kısmen literatürde. Bana kalan d sayacı ve (b, n) veri düzeni, yani bunu işlemciye dökmek.\

**Öğrendiğim:** Ben aynı zamanda bir işlemci yapmaya çalışıyorum. Benim için fark matematikte değil, mimaride.

### LOG 070, 12 Ekim 2026, 06:46-06:51, Swap ve Mersenne tabanları

**Sezgi:** 2^7 içindeki üssü 7 = 3x2+1 diye ayırıp 2^(3x2+1) yazımına baktım.\

**Araştırma ve test:** 128^9 = 2^63'ü üsleri yer değiştirerek okudum. `(2^7)^9`, `(2^9)^7` ve `(2^21)^3`'ün hepsi temiz satır veriyor. Tabanlar 2^k − 1, yani Mersenne sayıları: 127 asal, 511 ve 2097151 değil. 2000'e kadar atomu 2'nin kuvveti olan satır yalnız üç tane: n = 2, 4, 9 (üsler 2, 3, 7). 2 → 3 → 7 zinciri Catalan-Mersenne dizisinin başına benziyor, ama 15 ve 127 ile devam etmiyor. 7 + 2 = 9 da tesadüf.\

**Sonuç:** TUTTU. Zincirin sonlu olup olmadığı AÇIK.\

**Götürdüğü yer:** → LOG 072

### LOG 071, 12 Ekim 2026, Taban 3'te zincir

**Soru:** Bir kuvvetten altındaki kuvvetleri zincir halinde çıkarınca ne kalıyor?\

**Araştırma ve test:** Tepeden b^n'yi aldım, altından b^(n−1)'den b^m'ye kadar zinciri, en sonda da c tane 1'i çıkardım:
```
değer = b^n − (b^(n−1) + … + b^m) − c = b^n − (b^n − b^m)/(b − 1) − c
b = 2 :  değer = 2^m − c             tepe tamamen yok oluyor
b = 3 :  değer = (3^n + 3^m)/2 − c   tepe yarıya iniyor
```
3 tabanında m = 1 ile:
```
                         c = 0    c = 1
3² − 3                       6        5
3³ − 3² − 3                 15       14
3⁴ − 3³ − 3² − 3            42       41
3⁵ − 3⁴ − … − 3            123      122
3⁶ − 3⁵ − … − 3            366      365
3⁷ − 3⁶ − … − 3           1095     1094
3⁸ − 3⁷ − … − 3           3282     3281
3⁹ − 3⁸ − … − 3           9843     9842
3^10 − 3⁹ − … − 3        29526    29525
```
c = 0 sütunu (3^n + 3)/2, c = 1 sütunu (3^n + 1)/2. Son 1'i çıkarmak zinciri 3^0'a kadar indirmekle aynı. Sade dizi bu: a(n) = (3^n + 1)/2 → 1, 2, 5, 14, 41, 122, 365, 1094. 3 tabanında 11…12 diye yazılıyor. Bir sonrakine tek adımla geçiliyor: a(n+1) = 3·a(n) − 1. 3^5 = 243 = 2·121 + 1 olduğu için a(n), 121'e bölününce 1, 2, 5, 14, 41 diye beşte bir dönüyor, a(5) = 122 = 121 + 1 başa dönüş. Bu yüzden a(n) hiçbir zaman 11'e bölünmüyor. 14 ile 41'in ters yazılması tesadüf, 300'e kadar yalnız orada.

**Sonuç:** TUTTU (T22_base3_chain). Dizi LİTERATÜRDE (OEIS A007051). 3^10'un 121'e bölününce 1 kalması, yani 11'in taban 3 Wieferich asalı olması da LİTERATÜRDE, ötekisi 1006003, ikisini de koşturdum.\

**Götürdüğü yer:** → LOG 020'deki 121'e geri bağlanıyor

### LOG 072, 13 Ekim 2026, Mersenne tabanında 2'nin kuvveti

**Araştırma ve test:** LOG 070'teki 128^9'u genelledim. M_p = 2^p − 1 tabanında 2^p "11" diye yazılıyor, o yüzden 2^(p(p+2)) bu tabanda Pascal'ın p+2. satırı. Haneleri birbirinden üretip Horner'la geri topladım:
```
int n = p + 2;                     /* satir no              */
uint64_t b = (1ULL << p) - 1;      /* taban = M_p           */
uint64_t R = 1, v = 0;             /* en soldaki 1, deger   */
for (int k = 0; k <= n; k++) {
    v = v * b + R;                 /* v = v*taban + hane    */
    R = R * (n - k) / (k + 1);     /* sonraki hane          */
}
/* p = 7:  1 9 36 84 126 126 84 36 9 1,  v = 2^63 */
```
Bu uint64_t örneği yalnız p = 7 için verilmiştir. Daha büyük üslerde tam Horner değeri 64 bite sığmaz. Genel hesap için çok hassasiyetli tamsayı gerekir.

p = 5'te orta tabanı geçiyor, satır taşıyor, p ≥ 7'de hep temiz. p = 7'den 37'ye kadar p+2, ortası tabanın altında kalan en büyük satır, 38'den sonra p+3 de sığıyor. İlk 30 Mersenne üssünde denedim. Otuzuncusu p = 132049'da 132052 hanenin hepsi tabandan küçük çıktı, değer üç asal modülde 2^(p(p+2)) ile aynı (GMP ile 2,4 saniye). Asallık rol oynamıyor: p = 8'de taban 255 asal değil, satır yine temiz.

**Sonuç:** TUTTU (T21_mersenne_row). Altındaki binom ve 11'in kuvvetlerini her tabana genellemek LİTERATÜRDE (Jiu ve Vignat 2016). Mersenne asallarını ötekilerden ayırmıyor.\

**Götürdüğü yer:** → LOG 073

Bu bölümdeki kanıt tek p ≥ 7 içindir. Çift üsler bu pakette T21 ile p = 7..61 aralığında sınanır. Bütün tam sayı p ≥ 7 için genişletilmiş kanıt, [Pascal Mersenne Rows](https://github.com/JamesAugustus/pascal-mersenne-rows) deposundadır.

### LOG 073, 14 Ekim 2026, Mersenne tabanında 2'nin kuvvetleri: temiz Pascal satırı

**Soru:** Bu satır büyük Mersenne asallarında da temiz kalıyor mu, ve neden?\

**Araştırma ve test:** Üç şeyi kanıtladım. n = p + 2, x = (p + 1)/2 olsun.
```
T1 (değer)    Σ C(n,k)·M_p^(n−k) = (M_p + 1)^n = 2^(p(p+2))
T2 (temizlik) p ≥ 7 tek ise orta < M_p, hiçbir hane taşmaz
T3 (orta)     orta = C(2x+1, x) = (p + 2)·Cat_x
```
T1 binom teoremi. T2'yi tümevarımla gösterdim: n = 9'da 126 < 127. İki satır ilerleyince orta 2(2x+3)/(x+2) katına çıkıyor, bu 4'ten küçük, taban ise 4 katından fazla büyüyor (M_(p+2) = 4·M_p + 3). Yani orta tabanı hiç yakalayamıyor. p = 3 ve 5'te tutmuyor (10 > 7, 35 > 31). T3'te satırın 2. hanesi ortayı bölüyor: p = 7'de 126 = 9·14, p = 13'te 6435 = 15·429.

Ortanın çarpanlarını büyük sayıya dokunmadan, yalnız küçük bölmelerle bulabiliyorum (Legendre). (p+3)/2'den büyük, n'ye kadar her asal ortada bir kez var. (p+3)/2'nin kendisi asalsa hiç yok: p = 7'de 5, 126'da yok.

13-14 Ekim çalışma listemdeki 52 Mersenne üssünün hepsinde hesapladım. Bu, o deney listesinin kapsamıdır, güncel bir rekor listesi iddiası değildir. Büyük tablo hesapları bu paketin journal_tests.c dosyasında tekrarlanmıyor. En büyüğü p = 136279841'de orta hane 136 milyon bit ve tabanın 11 bit altında. Orta hanelerin onluk ve oktal yazımlarını, çarpanlarını, ilk yedi asalın üslerini tabloya döktüm. Hepsi ikinci bir hesapla da tuttu.

**Sonuç:** TUTTU, yukarıdaki kanıt her tek p ≥ 7 içindir (T21_mersenne_row ayrıca p = 7..61 aralığındaki çift ve tek üsleri sınar). Kullandığım araçlar LİTERATÜRDE: binom teoremi, Legendre formülü, C(2x+1, x) = (2x+1)·Cat_x. Tabanı M_p, satırı p + 2 seçmek ve bunun her tek p ≥ 7 için taşmadığını göstermek benim yaptığım. Asallığı ayırmıyor: M_11 = 23·89 da aynı sonucu veriyor.\

**Götürdüğü yer:** → LOG 074\

**Öğrendiğim:** Dev bir 2 kuvvetini Mersenne tabanında yazmak için hesap gerekmiyor, hanesi baştan belli.

### LOG 074, 14 Ekim 2026, Üslerin kendi yazımı

**Soru:** Mersenne üslerinin kendisi ikilikte nasıl duruyor?\

**Araştırma ve test:** 52 üssü ikilik, oktal ve işaretli ikilik (NAF) yazdım, 28 sütunlu bir ızgarada alt alta dizdim. İkilikteki her 1 bloğu bir Mersenne farkı: 2^(a−1) + … + 2^b = M_a − M_b = 2^b·M_(a−b). Böylece her üs Mersenne sayılarının toplamı oluyor. Örneğin 521 = (M_10 − M_9) + (M_4 − M_3) + M_1. İkilik yazımı yalnız 1'lerden oluşan, yani kendisi Mersenne olan üsler yalnız dört tane: 3 = M_2, 7 = M_3, 31 = M_5, 127 = M_7. Ardışık üslerin farklarını da aynı yolla açtım.\

**Sonuç:** TUTTU, yazım olarak. İkilik yazımı yalnız 1'lerden oluşan dört üs çift Mersenne asalları (M_M_2, M_M_3, M_M_5, M_M_7), LİTERATÜRDE. 2 → 3 → 7 → 127 zinciri Catalan-Mersenne dizisi. LOG 070'teki 2 → 3 → 7 buraya bağlanıyor. Desenden bir sonraki üssü tahmin eden bir kural bulmadım.

### Zincirin haritası

Soy ağacını da çizdim. Düz ok (->) yazılı bir kanıtı olan bağ. Noktalı ok (..>) ise içerik olarak aynı olduğu halde arada yazılı bir bağ cümlesi bulamadığım, olası bağ.

```
[KÖK 1] Renk ve ışıkla hesap (21 Nis taslak, 8 Haz kesin)
  +-> xbit: 3 bit = 1 oktal hane = 1 renk (8 Haz)
       +-> sekizlik taban (8 Haz, 31 Ağu "onaylandı taban 8")
       +-> sekiz tür etiketi (13 May) -> TÜR hücresi
       +-> Mersenne xbit deseni W/RW/YW (16-19 Haz)
            +-> oktal Mersenne desenleri, M_p = baş + 7'ler (26 Tem)
                 +-> {1,3,7} dili (2 Ağu)
                      +-> 1-3-7 çetele evreni (5 Ağu)
                           +-> üç baş (31 Ağu)
                           +-> paket M_P = (h+1)·8^t-1 -> PAKETLİ ELEK (7 Eyl)
                           +-> [D]101 ailesi (15 Eyl, ispat 10 Eki)

[KÖK 2] R/Y: Mersenne üssü mod 3 (21 Nis) ..> Mersenne xbit deseni (16-19 Haz)

[KÖK 3] LOG modu: çarpma = indeks toplamı (23 Nis) ..> GÖLGE

[KÖK 4] GÖLGE: çarpma = üs toplama (9 Haz)
  +-> resolver (20 Haz) -> hane akıtma (22 Haz) -> katlamalı kanallar (4 Eyl)
  +-> tembel gölge (1-2 Tem), RR rough sayıyı tutan register’dı (Ağustos başına kadar), 2 Ağustos’ta ayrı alana dönüştü
  +-> "gölge LL'e yardım etmiyor" (31 Ağu) -> p = 3q + r ..> paket (h, t)
  +-> eldesiz evren (1 Eyl) ..> taşmalı hane, [D]101 (15 Eyl)

[KÖK 5] Mersenne ve Lucas-Lehmer (ayrı depolar, Haziran-Ağustos)
  +-> sayan makine, KATLA (26 Tem ile 2 Ağu arası)
  |    +-> bit katlama kazanır (31 Ağu) -> vida ve tur (2-3 Eyl)
  +-> çarpan yasası q = 2kp+1 (26 Tem, sözüm 2-4 Eyl) -> PAKETLİ ELEK
  +-> 2p+1 kapısı (29 Tem) -> PAKETLİ ELEK
  +-> imza süzgeci bozuldu (7 Eyl) -> PAKETLİ ELEK

[KÖK 6] 121 ve Pascal
  +-> 121 = 11 kere 11 (31 Ağu) -> 1331 her tabanda (1 Eyl)
  |    -> 11 BİR FORMÜLDÜR (2 Eyl)
  |         +-> merdiven, eşik C(n,n/2)+1 (2 Eyl)
  |         |    -> merdiven adımı, flip-flop (11-12 Eki)
  |         |    -> Mersenne tabanında 2'nin kuvveti (13 Eki) -> temiz satır, 52 üs (14 Eki)
  |         +-> unary, "en önemli sayı 3" (1 Eyl) -> Taban^0 (15 Eyl)
  |         +-> 11 ölçeği (7 Eyl) -> PAKETLİ ELEK
  +-> Horner zinciri "235" (30 Ağu) -> C/T/A imzası (2-3 Eyl, tutmadı)
  +-> taban 3 zinciri, 121'de beşli dönüş (12 Eki)
  +-> komşu tabanda okuma (1-10 Eyl) -> TERS MERSENNE P (15 Eyl) -> [D]101

[KÖK 7] J. Clark Scott, "But How Do It Know" (16 Eyl)
  -> HunterCPU (25 Eyl) -> saf CPU kitabı (1 Eki)
```

Ağaca bakınca en çok fikir doğuran üç düğüm görünüyor: 121 ve Pascal, gölge, 1-3-7 evreni. Kolların en çok buluştuğu yer ise paketli elek. 1-3-7, çarpan yasası, 2p + 1 kapısı, katlama, imza süzgecinin yenilgisi ve 11 ölçeği. Hepsi oraya akıyor.


---

## 3. Tutanlar: net çıktığım formüller

Bu bölümde yalnız tutanlar var. Tutmayanlar ve zaten bilinenler günlükte TUTMADI ve LİTERATÜRDE diye işaretli, 4. bölümde de ayrı ayrı yazıyor. Net derken şunu kastediyorum: testi geçti ve neden doğru olduğunu kısa bir hesapla gösterebiliyorum. Her birinin testteki adını da yazdım. Aynı adlar journal_tests.c'de de var.

Formüllerin başı LOG 022'deki not. Taban bir artınca sayı da bir artıyor, yazı aynı kalıyor: b tabanında (b + 1)^3 = 1331. Bu b = 4'ten başlayarak doğru. 3 tabanında 3 bir hane olamadığı için 1331 yazılamaz. Aşağıdaki eşik yasası bu notun genel hali.

### Merdiven adımı

Merdivenin bir basamaktan ötekine nasıl çıktığını uzun süre bulamadım. Sonunda tek bir toplamaya indi:

**a_(n+1) = a_n + kom_n,   a_0 = 3**

Burada n, Pascal üçgeninin satır numarası. a_n o satırın atomu: ortadaki en büyük sayının 2 fazlası. kom_n ortanın solundaki komşu. Satırın ortasında iki eş sayı varsa komşu ortanın kendisi oluyor. Satırın tek ortalı mı çift ortalı mı olduğunu bir sayaç tutuyor. 0, 1, 0, 1 diye dönüyor, flip-flop gibi.

Katalan'sız genel hali, hepsi tek sayaçla (satırın dışındaki C(n,k) değerini 0 kabul ediyorum, örneğin C(0,−1) = 0):
```
d_0 = 0,   d_(n+1) = 1 − d_n          (sayaç: 0, 1, 0, 1, ...)
mid_n = C(n, (n − d_n)/2)             (orta)
kom_n = C(n, (n − 2 + d_n)/2)         (komşu)
a_n   = mid_n + 2                     (atom)
a_(n+1) = a_n + kom_n,   a_0 = 3
```
LOG 063'teki Katalanlı yazımla aynı şeyi söylüyor, ama çıkarma yerine toplamayla. Nedeni Pascal kuralı: bir alt satırın ortası, bu satırın ortasıyla komşusunun toplamı.

Satır 6'da 1 6 15 [20] 15 6 1 var. Orta 20, atom 22, komşu 15. Bir sonraki atom 22 + 15 = 37. Satır 7'de iki tane 35 var, komşu 35'in kendisi. Atom 37, sonraki 37 + 35 = 72. Böyle 1000. satıra kadar gittim, hep tuttu (arşiv kaydı, bu paketteki T18 yalnız n ≤ 60 aralığını sınar). Çarpma hiç gerekmiyor, yalnız toplama.

Sonra araştırdım. Adım kuralı OEIS'te A001405 kaydında (Hanusa 2003) aynen yazılıymış. En küçük taban A051920'de (Sloane 1999), atom üssü merdiveni de A193242'de (Povolotsky 2013) duruyor. Yani matematiği literatürde. Benim istediğim bu adımı bir toplayıcı ve bir flip-flop ile devreye dökmek. O devreyi henüz yapmadım. Komşu katsayının üretilmesi veya saklanması da gerekir. Tek toplamayı saymak bütün devrenin bellek ve hesap maliyetini açıklamaz.

### Eşik yasası ve merdiven

**eşik(n) = C(n, ⌊n/2⌋) + 1**

11^n'e bakıyordum, yani (b + 1)^n'e. Bu sayı b tabanında eldesiz yazılabiliyorsa yazısı tam Pascal üçgeninin n'inci satırı oluyor. Bunun için tabanın en az eşik(n) olması gerekiyor, yetiyor da. n = 4'te satır 1 4 6 4 1, en büyük katsayı 6, eşik 7. Onluk taban 7'den büyük, o yüzden 11^4 = 14641, satırın kendisi. n = 5'te satır 1 5 10 10 5 1, ortadaki 10 onluk tabanda tek hane olamaz, eşik 11. Onlukta 11^5 = 161051 çıkıyor, satır bozuluyor. 11 tabanında ise 12^5 yine 1 5 10 10 5 1 diye yazılıyor, her katsayı tek hane. Merdiven buradan çıkıyor. n = 1'den 6'ya eşikler 2, 3, 4, 7, 11, 21. n büyüdükçe sayı kendi evrenine sığmıyor, bir üst tabana çıkmak zorunda kalıyor.

Neden doğru? Binom açılımı (b + 1)^n = Σ C(n, k) · b^k. Bütün katsayılar b'den küçükse her biri geçerli bir hane olur. Bir sayının b tabanındaki yazısı tek olduğu için yazı tam satırın kendisidir. Satırın en büyük katsayısı ortadaki C(n, ⌊n/2⌋). b bundan büyükse yazı satırdır. b ona eşit ya da ondan küçükse ortadaki katsayı hane olamaz, elde doğar ve yazı satırdan ayrılır. Ortadaki katsayıların dizisi bilinen bir dizi (OEIS A001405), eşiği ben bu yoldan okudum.

Testteki adı T08_threshold_law. n = 1..15 için eşikte ve bir üstünde, n = 2..15 için bir altında 44 taban kontrolü, tuttu.

### [D]101 ailesi

**[D]101 = (3 + 8k) · M_p, burada D = 3 · 2^(p−3) − 1 + k · M_p, p ≥ 3 ve k ≥ 0 tam sayıdır.**

[D]101 yazısı, ikilikteki 101'in, yani 5'in üstündeki haneye D koymak demek, değeri 8D + 5. D'yi böyle seçince çıkan sayı her zaman M_p'nin katı oluyor. p = 5, k = 0 için D = 3 · 4 − 1 = 11 ve [11]101 = 11 · 8 + 5 = 93 = 3 × 31.

Neden doğru? 8D + 5 = 3 · 2^p − 8 + 8k · M_p + 5 = 3 · (2^p − 1) + 8k · M_p = (3 + 8k) · M_p. Ters yönü de var: 8D + 5 = t · M_p ise t ≡ 3 (mod 8) olmak zorunda. Çünkü M_p ≡ −1 (mod 8) ve 8D + 5 ≡ 5 (mod 8), demek ki −t ≡ 5, yani t ≡ 3. Bu biçimdeki bütün katlar ailenin içinde. Aile asallık söylemiyor, çarpanı ben koyuyorum.

Testteki adı T01_d101_family. Asal p = 3..31 ve k = 0..3 için 40 eşitlik, tuttu.

### 1-3-7 baş hane ve paket yazımı

**M_P = (h + 1) · 8^t − 1, burada P = 3t + s, s ∈ {1, 2, 3} ve h = 2^s − 1**

M_P sekizlikte bir baş hane h ve ardından t tane 7. h, P'nin 3'e göre kalanına göre 1, 3 ya da 7. P = 11 için 11 = 3 · 3 + 2, yani t = 3, s = 2, h = 3. M_11 = 3777₈ = 2047. "3777 mesela 11 e tekabül ediyor" dediğim şey buydu. Paketli elek M_P'yi bu yazıyla, açmadan tutuyor.

Neden doğru? 2^P = 2^s · 8^t, o halde M_P = 2^s · 8^t − 1 = (2^s − 1) · 8^t + (8^t − 1). 8^t − 1 sekizlikte t tane 7 ve 2^s − 1 de 1, 3 ya da 7 olan tek bir hane. P asal ve 3'ten büyükse 3'e bölünmez, s 3 olamaz, baş hane 1 ya da 3 kalır.

Testteki adı T05_137_octal_head. p = 3..300 için 298/298, tuttu.

### M_p ≡ −1 (mod 8)

**M_p ≡ 7 (mod 8), p ≥ 3**

p 3 ya da daha büyükse M_p'nin sekizlikteki son hanesi hep 7. M_5 = 31 = 3 · 8 + 7. Neden doğru? p ≥ 3 için 2^p 8'e bölünür, 2^p − 1 ≡ −1 ≡ 7 (mod 8). Formüllerin en basiti bu. [D]101 ailesinin ters yönü de buna dayanıyor.

Testteki adı T02_mersenne_mod8. p = 3..79 için 77 üs, tuttu.

### Makine: Hunter'ın bu derlemedeki hali

Bu bölüm, Ekim 2026 derlemesindeki tasarım ve arşiv kayıtlarını anlatır. Aşağıdaki alan, hız, saat çevrimi ve büyük test sayıları journal_tests.c tarafından yeniden üretilmiyor. Bunlar tarihsel model/deney kayıtlarıdır, bu paket için yeni doğrulanmış benchmark veya FPGA/silikon sonucu değildir.

Makine zamanla sadeleşti. 30 Ağustos'ta CT-CPU'yu baştan yazmaya karar verdim. Hunter adıyla devam etti. Eski düzen, yani 4096 thread, MIMD, renkli kapılar, bugün yalnız tarih olarak duruyor. Hunter'ın o tarihteki halini tek bir makine belgesinde tutuyorum.

Hunter tek çekirdekli, tek thread'li, 8 register'lı bir makine. Bir sayı sekiz oktal haneden oluşuyor. En büyüğü 77777777₈, yani 16.777.215. Her register'ın içinde sekiz küçük alt register var: düz yazı (rm), dört gölge satırı (rs1..rs4), rough önbellek (rc), ölçek (rpow) ve tür (rtyp). Her biri sekiz hücre, her hücre üç bit. Bir register'ın tamamı 192 bit ediyor.

Gölge de ilk halinden farklı artık. İlk gölge sayıyı düpedüz asal çarpanlarına ayırıyordu. Hunter'daki gölge sayıyı sekizlik tabanda kademe kademe indiriyor: val = smooth × (8 × alt + a). Her satırda yedi küçük asalın (2, 3, 5, 7, 11, 13, 17) üsleri ve bir kalan hane duruyor. Bu, Horner şemasının genelleşmiş hali. smooth her kademede 1 olsaydı elimde düz oktal sayı kalırdı.

Komut kümesi sekiz opcode: LOAD, MOV, ADD ailesi (ADD, SUB, CMP), MUL ailesi (gölgede çarpma ve bölme, karekök, kare, kaydırma), J (koşullu atlama), LD, ST ve SYS. Bir komut dört xbit, yani 12 bit. Tasarım hedefim mikrokod kullanmadan opcode’ları doğrudan kontrol yollarına bağlamak. Bu tarif, komutu ayıran veya kontrol üreten mantığın maliyetsiz olduğunu göstermez. Burada sentezlenmiş bir devre sunmuyorum.

Ölçtüklerimi değiştirmeden yazıyorum. 24 bitlik bir dizi çarpıcıda klasik devre 576 tam toplayıcı istiyor, gölge 30. Bu modelde yalnız sayılan toplayıcı adedi yaklaşık 19 kat küçük, bu oran tüm işlemcinin alan oranı değildir. Rastgele 24 bitlik sayı çiftlerinde ortalama tam toplayıcı maliyeti klasik yolda 529, gölgede 1026 çıktı. Çünkü rastgele bir sayının büyük kısmı rough kalıyor ve o kısım klasik çarpılıyor (bkz. 3,75 bit). Gölgenin yararlı olmasını yapısı belli sayılarda bekliyorum. Kazanç işlem türüne, temsil dönüşümüne ve karşılaştırılan uygulamaya bağlıdır. Gölgeyi kuran resolver bu sayının dışında, tasarımda tipik 3 saat çevrimi sürüyor, hane akıtmayla bölme yapmadan çalışıyor. Arşivdeki bölme karşılaştırması yaklaşık üç kat hız bildirmişti, karşılaştırma bu pakette tekrarlanmadı. 2^24 sayının hepsinde gölgeye gidip geri dönmek 0 hata verdi. Silikon yok. İşlem ve kapı sayıları da kullanılan modelin kapsamıyla sınırlı. Gerçek saat frekansı, güç ve tüm sistem alanı için donanım uygulaması ve ölçüm gerekir.

### Makinede tutanlar

Bunlar arşivdeki simülasyon sonuçlarıdır, bu günlüğün 22 kartı söz konusu makine testlerini içermez.

Formül olmayan ama makinede tutan iki ölçüm de var. 2^24 sayının hepsinde gölgeye gidip yazıya geri dönmek 0 hata verdi (yukarıdaki ölçüm). NAND kapılarından kurduğum sade Hunter modeli 6 × 7 = 42'yi 268 adımda doğru hesapladı. 268 tik modelin saat adımıdır, hız ölçüsü değil, programın doğru bittiğini gösterir. Bunlar simülasyonda ölçüldü, çipte henüz denenmedi (Tang Nano 9K ile denenecek).


---

### Resolver: sayı akarken ölçmek

Gölgeyi kurmak için sayının içinde kaç tane 2, 3, 5, 7, 11, 13, 17 olduğunu bilmem gerekiyordu. Bölme devresi istemiyordum. Sayının sekizlik hanelerini soldan akıttım. Her hane geldiğinde yedi kanal kendi kalanını güncelledi: kalan ← (8 · kalan + hane) mod q. Son hane girdiğinde cevap hazırdı. Bölünen kanalda bölüm de akarak çıktı ve bir sonraki aşamaya girdi. Her bölünmede o kanalın sayacı bir tık attı, 7'yi geçince elde bir üst satıra geçti.

3¹⁴'ü akıttığımda bir şey gördüm: aşamalar arasında 14641, 1331, 121, 11 belirdi. 3² = 9, sekizlikte 11 yazılıyor, yani 3^(2n) = 9^n = (8+1)^n açılımının katsayıları Pascal satırıdır. Sekizlikte bu katsayılar ancak 8'den küçükken doğrudan hane olur: n = 0..4 temizdir, n = 5'te orta katsayı 10 olduğu için elde başlar. 3^14 için n = 7'dir, katsayıları doğrudan sekizlik haneler sayamam. Pascal yine oradaydı.

Literatürde: kalan akışı Horner (1819), bölüm akışı uzun bölme. Benim olan, bunları yedi paralel kanal, zincirlenen aşamalar ve elde atan sekizlik sayaçlarla tek bir akışta birleştirmek.

### Gölgenin sınırı: 3,75 bit

Rastgele bir sayı aldığımda, içinde gölgenin tuttuğu yedi asaldan (2, 3, 5, 7, 11, 13, 17) gelen kısım ortalama ne kadar büyük? Örnek: 744 = 2³ · 3 · 31. Gölgeye düşen kısım 2³ · 3 = 24, geriye kalan 31 rough, rc'ye gider.

Her asal gölgeye ortalama log₂(p) / (p − 1) bit getirir. Sayıların yarısı 2'ye bölünür, dörtte biri iki kez bölünür, sekizde biri üç kez, bunların toplamı ortalama bir tane 2 eder, yani 1 bit. 3 için ortalama yarım tane 3 düşer, o da ½ · log₂ 3 ≈ 0,79 bit eder.

| Asal | Ortalama katkı (bit) |
|---|---|
| 2 | 1,000 |
| 3 | 0,792 |
| 5 | 0,580 |
| 7 | 0,468 |
| 11 | 0,346 |
| 13 | 0,308 |
| 17 | 0,255 |
| Toplam | 3,75 |

Bu toplam, pozitif tamsayıları 1..N aralığından eşit olasılıkla seçip N büyütürken elde edilen ortalama logaritmik katkıdır. Sıfır için bu asal üs modeli kullanılmaz. Arşivdeki 200.000 rastgele sayılık deneyde ölçüldü: ortalama 3,755 bit, formülle aynı. 2^3,75 ≈ 13,5. Bu, gölgeye düşen kısmın yaklaşık geometrik ortalamasıdır, sayı değerlerinin aritmetik ortalaması değildir. Sayının büyük kısmı rough'ta kalır.

Bu yüzden gölge rastgele veride uçmaz. Gücü yapısı belli sayılarda çıkar: faktöriyeller, kuvvetler, Mersenne biçimli sayılar, çarpanları önceden bilinen hesaplar.

## 4. Testler

"İstatistik kısmına inancım ve ilgim çoktur ama sebeplerini bilmediğimiz şeylerden ilerlemesi bana simya gibi geliyor."

Bu yüzden burada denediklerimi sırasıyla, eskiden yeniye yazıyorum. Her satırda ne denediğim, hangi dosyayla denediğim, sonucu ve bu yayındaki karşılığı var. Dosyaları arşiv adıyla anıyorum. Eski dosyaların hepsi yerinde, bu yayın için ise günlük iddialarının testlerini baştan, tek dosyada yazdım. Testleri C ile yazdım:

```
cc -std=c99 -O2 -o journal_tests journal_tests.c -lm && ./journal_tests
```

Sonuçları dört sözle yazıyorum. Tuttu: kendi yolumla kurduğum şey doğrulandı. Tutmadı: karşı örneği var. Literatürde: doğru çıktı, araştırmalarım sonucunda bu yöntemin daha önce bulunduğunu, üzerinde çalışıldığını gördüm. Sınanamadı: bu yayında testi yazılamayan iddia. İstatistik sonuçlarını hüküm saymadım. Onları ayrıca işaretledim.

### Denediklerim, sırasıyla

Aşağıdaki tablo eski deney defterinin özetidir. Yalnız arşiv adlarına bağlı tarihsel ölçümler bu paket için yeniden çalıştırılmadı. Seçili emülatör kaynakları, Nihai Form’da kaydedildiği gibi, TESTLER/HUNTER/ altındaki 30 arşiv testi arasında yeniden çalıştırıldı. Süre, enerji, alan, yüzde ve büyük kontrol adetleri ilgili eski koşumun kaydıdır, farklı makinelere veya algoritmalara genel hız garantisi vermez. Aşağıdaki 22 kart günlük iddialarını kapsar. Pakette ayrıca iki NIHAI_EK doğrulama programı bulunur.

| Tarih ve deney | Arşiv kaydı | Sonuç | Bu yayındaki karşılığı (günlük testi) |
|---|---|---|---|
| **Nisan.** Mersenne üslerinin 3'e göre dağılımı ve R/Y şeridi | Nisan-Temmuz CT-CPU arşivi, mod3_distribution.py ve visualize_ry_strip.py | istatistik: 52 üste yanlılık çıkmadı, hüküm sayılmadı | denendi. |
| **Nisan.** LOG modunda tek xbit çarpma ve bölme | aynı arşiv, log_mode_test.py | kararsız: 17 çarpma ve 14 bölme durumu yazılı, koşum çıktısı yok | denendi. |
| **Haziran.** Gölgenin ilk C simülasyonu: çevirici ve gölgede çarpma | CT-CPU yedek arşivi, ctcpu_golge.c ve ctcpu_cekirdek_test.c | tuttu: 5 milyon gölge çarpması 4,2 ms (bilgisayar üstünde ölçüm) | T13_shadow_vector (literatürde). |
| **Haziran.** Gölge emülatörü, 2^24 sayının hepsi: gidiş-dönüş, 7, 11 ve 13 kalanları, rough | CT-CPU arşivi, test_nihai.c, test_ek.c ve test_roughflag.c | tuttu: 18/18 | denendi (3. bölümde makinede tutanlar). |
| **Temmuz.** Çeyrek-kare ile binom çarpımı | CT-CPU git arşivi, CEYREK_KARE_DENEY.c | tuttu: 3 milyon çiftte 0 hata, küçük sayılarda binom kazandı | denendi. |
| **Temmuz.** Yapısal kare, m = 8n + r | CT-CPU git arşivi, YAPISAL_KARE_DENEY.c | tuttu: 0 hata, kare yüzde 42-44 daha ucuz | denendi. |
| **Temmuz.** Sekizlik Mersenne deseni, p = 5..127 | CT-CPU arşivi, GECE_ARASTIRMASI.html (hesap satırı raporun içinde) | tuttu: 10 örnek, istisna yok | T05_137_octal_head (tuttu). |
| **Temmuz.** Hane akıtma ve gölge gidiş-dönüşü | CT-CPU arşivi, resolver_emulator.c, golge_nihai.c ve TUM_TESTLERI_KOSTUR.sh | 117 milyon kontrolde 0 hata | T12_digit_flow (literatürde: Horner). |
| **Temmuz.** Uyarlanır hassasiyet: render ve matris çarpımı | CT-CPU arşivi, render_adaptif.c ve matmul_adaptif.c | karışık: render 1,3 kat hızlı, ALU ağır işte 0,81 kata düştü | denendi. |
| **Ağustos.** Gölge birleşik denetimi, 2^24 | CT-CPU arşivi, CEM_MODELI, golge_nihai.c | tuttu: 60.436.967 geçişte çift rough 0 | denendi. |
| **Ağustos.** Mersenne tezgahının görsel simülasyonu | Mersenne tezgahı deposu, CTCPU_SIMULASYON.html | iki hata buldu (VEYA ayrıştırıcısı ve RR çözümü), ikisi düzeltildi | denendi. |
| **Ağustos.** Küp kimliği 8^p − 1 = M_3p ve 2p + 1 kapısı | Hunter arşivi, EVREN_137.html içindeki test dizisi | literatürde: kapıdan geçen p ≤ 200 için 2p + 1, M_p'yi böldü, bu Euler'in yasası | T04_euler_2p_plus1 (literatürde). |
| **Ağustos sonu.** Gölgenin canlı akışı | CT-CPU git arşivi, 29_AGUSTOS_2026, GOLGE_AKIS_CANLI.html | tuttu: 9/9, 300 rastgele gidiş-dönüşte 0 hata | denendi. |
| **Eylül başı.** 323 iddialık ilk büyük tur | TEST_001 deneme arşivi, test_battery.py | 302 geçti, 3 kaldı, 18 kararsız | aşağıdaki dört satır bu turun parçaları. |
| **Eylül başı.** Kuadratik üreteç M² + 10M + k | TEST_001 deneme arşivi, k4_A_bolum29.py | tutmadı: M = 3, k = 3 için 42 | T14_quadratic_generator (tutmadı). |
| **Eylül başı.** C/T/A imzası | TEST_001 deneme arşivi, k5_A_orta1.py | tutmadı: imza tek başına asallığı ayırmıyor | denendi. |
| **Eylül başı.** Pascal eşiği, n ≤ 60 | TEST_001 deneme arşivi, k3_B_bolum13.py | o aralıkta doğru, sonlu deneme | T08_threshold_law (tuttu). |
| **Eylül başı.** Tornavida ve katlama sayısı | TEST_001 deneme arşivi, f1_tornavida.py | tutmadı: turun kalan 3 iddiası bunlar | denendi. |
| **Eylül başı.** Lucas-Lehmer'siz Hunter Mersenne hattı | Hunter arşivi, test_hunter_pipeline.py | 38 geçti, 4 kaldı, 7 açık, 35.936.789 kontrol | parçaları aşağıda. |
| **Eylül başı.** Baş hane, p = 1..1000 | aynı dosya | tuttu: 1997 kontrol, 0 ihlal | T05_137_octal_head (tuttu). |
| **Eylül başı.** Çarpan yasası q = 2kP + 1 ve q ≡ ±1 (mod 8) | aynı dosya | literatürde: 313.714 kontrol | T03_factor_law (literatürde). |
| **Eylül başı.** Pascal eşiği, n ≤ 200 | aynı dosya | tuttu | T08_threshold_law (tuttu). |
| **Eylül başı.** Sabit imza süzgeci | aynı dosya | tutmadı: 51. ve 52. üs kümeye girmedi | T17_signature_filter (bu yayında sınanamadı: tarihsel imza fonksiyonu ve sabit imza kümesi bu pakette yok). |
| **Eylül başı.** İmza özelliğinin ayırıcılığı | aynı dosya | istatistik: hüküm sayılmadı | denendi. |
| **Eylül başı.** Paketli elek, ikinci sürüm | Hunter arşivi, test_paketli_elek_v2.py | eleğin kaçırdığı bileşikler bu dosyada değil, Ekim'deki teori testinde görüldü | T11_packed_sieve (tutmadı). |
| **Eylül başı.** 11_b = b + 1 ve unary ölçek | Hunter arşivi, test_11_olcek_modeli.py | literatürde | T09_11_base_value (literatürde). |
| **Eylül ortası.** Ters Mersenne P, 40 iddia | TEST_003 deneme arşivi, geri_muhendislik.py | 27 geçti, 9 kaldı, 4 kararsız, Mersenne'e özgülük tutmadı | T15_reverse_p_general (yalnız ters yazımın her zaman asal verdiği iddiası için karşı örnek, geniş tarihsel mekanizmanın tamamı sınanmadı). |
| **Eylül.** Ulam bandı | Hunter arşivi, ARASTIRMA_20260919, HUNTER_BANT_TABAN_DENETIM.py | sayımlar k ≤ 200'de tuttu, kaydırma kuralı k = 5'te kırıldı | denendi. |
| **Eylül sonu.** HunterCPU'nun NAND toplayıcısı | Hunter arşivi, cpu.test.mjs | tuttu: 65.536 girdi çifti | denendi. |
| **Eylül sonu.** Katlama ve vida, 45.056 kimlik | Hunter arşivi, NIHAI_FORM_300926, kesin_kontrol.py | literatürde: altındaki hesap çarpımsal mertebe | denendi. |
| **Ekim başı.** HunterCPU ile 6 × 7 = 42 | Hunter arşivi, HUNTERCPU_6X7_021026, kontrol.py | tuttu: 268 adım | denendi. |
| **Ekim.** 40 kartlık teori testi | Hunter teorileri, testler.c | 39 kartta karttaki hüküm doğrulandı, birinin testi yok | kare mührü, 242/242 C/T/A sonucu ve M_41 kaçağı ilk burada çıktı: T10_square_seal (ölçüt tanımsız, sınanamadı) ve T11_packed_sieve (tutmadı). |
| **Ekim.** Bu günlüğün testleri | journal_tests.c | 22 test: 15 tuttu (7’si literatürde), 4 tutmadı, 3 sınanamadı | aşağıdaki tablo. |

Kare mührü için eski bir kod dosyası yok, o ilk kez Ekim'deki teori testinde sınandı.

### Bu günlüğün 22 testi

| Günlük testi adı | Neyi sınıyor | Durum | Sonuç | Aralık |
|---|---|---|---|---|
| T01_d101_family | [D]101 = (3 + 8k) · M_p | TUTTU | 40 eşitlik doğru | asal p = 3..31, k = 0..3 |
| T02_mersenne_mod8 | M_p ≡ 7 (mod 8) | TUTTU | 77 üs için doğru | p = 3..79 |
| T03_factor_law | Bölenler q = 2kp + 1 ve q ≡ ±1 (mod 8), Fermat, Euler | TUTTU, LİTERATÜRDE | 14 asal çarpan koşulu sağladı | asal p = 3..31 |
| T04_euler_2p_plus1 | p ≡ 3 (mod 4) ve 2p + 1 asal ise M_p'yi böler, Euler 1750 | TUTTU, LİTERATÜRDE | 3 uygun q böldü, p = 3 istisnası dışarıda | asal p < 100 |
| T05_137_octal_head | M_p sekizlikte 1, 3 ya da 7 ile başlar, 7'lerle biter | TUTTU | 298/298 doğru | p = 3..300 |
| T06_head_digit_primality | Baş hane asallığı ayırır mı | TUTMADI | M_11 = 2047 bileşik, başı 3 | p = 5, 11 |
| T07_pascal_11 | 11'in kuvvetleri Pascal satırıdır, binom teoremi | TUTTU, LİTERATÜRDE | 65 hane kontrolü doğru | n = 0..4, n = 1..30, taban en büyük katsayı + 1 ve + 2 |
| T08_threshold_law | Eldesiz yazım için eşik taban C(n, ⌊n/2⌋) + 1 | TUTTU | 44 taban kontrolü doğru | n = 1..15 eşikte ve bir üstünde, n = 2..15 bir altında |
| T09_11_base_value | 11_b = b + 1 | TUTTU, LİTERATÜRDE | 99 taban ve 98 kare doğru | b = 2..100, kareler b = 3..100 |
| T10_square_seal | LL sonundaki kare asallık imzası mı | SINANAMADI | ölçüt tanımsız | küçük p = 3, 5, 7, 11, 13 |
| T11_packed_sieve | Elek k ≤ 64 ile bütün bileşikleri yakalar mı | TUTMADI | M_41 bileşik, böleni 13367 (k = 163), k ≤ 64 kaçırır | p = 41 |
| T12_digit_flow | Sekizlik Horner kalan akışı doğru kalanı verir, Horner | TUTTU, LİTERATÜRDE | 491.520 kalan eşitliği doğru | n < 32768, p = 3..17 |
| T13_shadow_vector | Gölgede çarpmanın üsleri topladığını sınar | TUTTU, LİTERATÜRDE | 4096 çarpım doğru | a, b = 1..64 |
| T14_quadratic_generator | M² + 10M + k asal üretir mi | TUTMADI | M = 3, k = 3 için 42 = 2 × 21 | M = 3, k = 3 |
| T15_reverse_p_general | Bir asalın onluk ters yazımı her zaman asal mıdır? | TUTMADI | 19→91=7×13 karşı örneği | p = 19 |
| T16_mersenne_infinitude | Mersenne asallarının sonsuzluğu bu mekanizmadan çıkar | SINANAMADI | test yazılmadı | açık problem |
| T17_signature_filter | Sabit imza kümesi bütün sonraki üsleri tutar | SINANAMADI | İmza fonksiyonu ve sabit imza kümesi pakette yok, ham üs üyeliği imza testi değildir | tarihsel #51 ve #52 iddiası |
| T18_ladder_step | a_(n+1)=a_n+kom_n | TUTTU | formül ve Pascal satırı aynı | n=0..60, uint64_t |
| T19_base_difference | b_n-b_(n-1)=kom_(n-1) | TUTTU | fark ve komşu katsayı aynı | n=1..60, uint64_t |
| T20_middle_by_addition | verilen sayı orta: taban N+1, uçtan toplama + ayna | TUTTU | 0-37 temiz, 38'de orta N'yi geçiyor | N = 26321361382 |
| T21_mersenne_row | 2^(p(p+2)), 2^p − 1 tabanında p+2. satır | TUTTU | p = 5 taşar, p = 7..37'de en büyük temiz satır p+2 | p = 7..61, 3 asal modül |
| T22_base3_chain | b^n − zincir − c, a(n) = (3^n+1)/2 | TUTTU, LİTERATÜRDE | 6156 eşitlik, mod 121 beşte döner, Wieferich 3: 11, 1006003 | b = 2..10, n < 2000, q < 2·10^6 |

Toplam 22 test: 15 tuttu, 4 tutmadı, 3 sınanamadı. Tutan 15 testin 7'sinin literatürde bilinen sonuçlarla ilgili olduğunu sonradan öğrendim. Çıktının tamamı TEST_OUTPUT.txt dosyasında. Kod ve çıktı İngilizce: HOLDS = tuttu, FAILS = tutmadı, UNTESTED = sınanamadı, ERROR = kod hatası. Kod yalnız hesapladığını söylüyor. Literatür bilgisi bu tabloda. T11 bana eleğin bir hüküm değil, bir süzgeç olduğunu gösterdi. M_41'in böleni 13367 = 2 · 163 · 41 + 1. Elek k'yı 163'e kadar götürseydi bulurdu, ilk 64 adayda bulamıyor.


---

## 5. Uçuk olanlar

Burada "acaba böyle midir" deyip bıraktıklarım var: tutmayanlar, sınanamayanlar. Kalıp günlükle aynı, numaralar günlükten devam ediyor.

### LOG 075, 20 Ocak 2026, Kara delik

**Sezgi:** Kara deliğin içindeki perspektif ve yeni zaman üzerine bir başlık not ettim.\

**Sonuç:** AÇIK. Notta yalnız başlık var. Denklem yok, ölçüm yok, sınanacak bir şey yok.

### LOG 076, 1 Eylül 2026 gecesi, En önemli sayı

**Sezgi:** 1’lik tabana kadar düşündüğümde en önemli sayının 2 yerine 3 olabileceğini sezdim. 2’yi bu bakışta 0 gibi düşünüyordum.\

**Sonuç:** AÇIK. "Önemli"nin ölçüsünü tanımlamadım, sınanamaz.\

**Götürdüğü yer:** → LOG 040 (Taban^0'ın tohumu)

### LOG 077, 2-3 Eylül 2026, Sayılar canlı

**Soru:** Sayıları sabit değerlerden çok canlı ve akışkan, ivmeye benzeyen şeyler gibi düşünüyordum. Bir türev makinesi yapıp yapmadığımı kendime sordum.\

**Sonuç:** AÇIK. Felsefi kısmı sınanamaz. Sınanabilen kısmı, ardışık Fibonacci terimlerinin farkının yine Fibonacci olması, doğru çıktı.\

**Götürdüğü yer:** → LOG 041

### LOG 078, 2-3 Eylül 2026, Vida ve yay

**Sezgi:** Yay fabrikasında bir demir iğnenin dokunuşuyla eksen boyunca uzayan ve dönen yayı gözümün önüne getiriyordum. Böyle bir hareketin sayıların davranışını anlatıp anlatamayacağını düşündüm.\

**Soru:** Dönen şeyin bir vida olması, ilerledikçe yükselmesi ve modların vidanın yönüyle ilişkili olması ihtimallerini düşündüm.\

**Sonuç:** AÇIK. Benzetmenin ölçülebilir bir karşılığı yok. Altındaki muhasebe, yani atılan turların bölümü vermesi, kanıtlı ve bilinen bir şey.

### LOG 079, 2-3 Eylül 2026, Repunit şifreleme

**Sezgi:** Mersenne asallarının önemini kaybedip yeni şifreleme yöntemlerinin repunit asallarına yönelebileceğini düşünüyordum.\

**Sonuç:** AÇIK. Bir güvenlik analizi yok. Sınanabilen tek şey, bileşik a için R_a(b)'nin bileşik olması, o doğru.

### LOG 080, 3 Eylül 2026, Yay sezgisi ve vida sorusu

**Sezgi:** Buradaki ilk sezgim tornavida değil, yayı andıran bir hareketti: bir noktadan başlayıp uzayan ve dönen bir çizgi. Ardından kendime “bu bir tornavida değil mi?” diye sordum, çünkü dönen çizgi ilerledikçe yükseliyorsa vida gibi düşünülebilir.\

**Araştırma ve test:** Vida düşüncesini mod işlemiyle ilişkilendirdim. Bir sayıyı 2^p−1’e bölerken x = q(2^p−1)+r yazımı, q tam turu ve r kalanı gösterir. 2^p ≡ 1 (mod 2^p−1) olduğundan 2’nin p basamaklık blokları Mersenne modunda aynı kalana sarılır. Bölüm tur sayısını, kalan ise çevrimdeki konumu taşır. KATLA adımı N=(N>>p)+(N&M_p) biçiminde yüksek ve düşük parçaları toplar. Bu aritmetik ilişki test edildi. Vida benzetmesinin fiziksel veya geometrik bir teorem olduğu gösterilmedi.\

**Sonuç:** AÇIK. Katlama tuttu, üç boyutlu yay fikri henüz formüle dökülmedi.

### LOG 081, 7 Eylül 2026, Zoom

**Sezgi:** Her şeyi 11 yazımları üzerinden düşünüyordum. Bu bakışta 0’a yer vermiyordum. Sayıların büyümesinden çok, yakınlaştırma veya katlanma gibi bir hareket hayal ediyordum.\

**Sonuç:** AÇIK. Bu bir bakış açısı, çürütülebilir bir iddia değil.

### LOG 082, 8 Eylül 2026, Kâğıt katlama

**Soru:** Katlanma sayısını, kâğıdın özkütlesini ve ağırlığını bildiğim bir benzetme kurdum. En-boy oranının korunması veya değişmesi üzerinden asallık hakkında bir şey söyleyip söyleyemeyeceğimi merak ettim.\

**Sonuç:** TUTMADI. "Katlanma sayısı"nı hiç tanımlamadım. Tanımlanınca her sayının sonunda 1'e indiği görüldü.

### LOG 083, 15 Eylül 2026, Bütün Mersenne'ler aynı sayı

**Sezgi:** Bütün Mersenne sayılarını farklı komutlarla yazılmış aynı sayı gibi düşünüyordum. [2,1,0]_3 yazımını 3x2+1 üzerinden okuyor, 0 olduğunda kaydırmayı 3 ile çarpma komutu olarak yorumluyordum.\

**Sonuç:** AÇIK. Aynı sayı derken yazıyı mı, değeri mi kastettiğimi tanımlamadım. Rakamı komut olarak okumak bir sözleşme, doğrulanacak bir iddia çıkarmıyor.

### LOG 084, 15 Eylül 2026, Tek ve çift

**Sezgi:** Çiftliği, bulunduğum sayı evreninin en küçük asalına bölünmek üzerinden yeniden tanımlamayı düşünüyordum. Tek ve çift ayrımının baştan verilmiş olmasına itiraz ettim. 22’yi yalnız 2x11 diye değil, 2, 22, 222, 2222 diye ilerleyen bir evren içinde okuyordum. O bakışta 22’nin de en küçük asal olabileceğini düşünüyordum.\

**Sonuç:** AÇIK. "Evren" kelimesini tanımlamadım. Taban olarak tanımlanırsa her evrenin en küçük asalı yine 2 çıkıyor.

### LOG 085, 15 Eylül 2026, Sonsuzluk

**Sezgi:** Mersenne asallarının sonsuzluğunun bu mekanizmadan çıkabileceğini düşündüm.

**Not:** Buradaki “mekanizma” sözcüğüyle hangi işlem veya teorem zincirini kastettiğimi kayda geçirmemişim.

**Sonuç:** AÇIK. Mersenne asallarının sonsuz olup olmadığı açık bir soru, sonlu bir testle sınanamaz (T16_mersenne_infinitude).

### LOG 086, 21 Eylül 2026, Rubik

**Sezgi:** Bu yapıların bir kesişim veya Venn şemasına, hatta Rubik küpü yöntemine dönüşebileceğini hayal ediyordum.\

**Sonuç:** AÇIK. Güzel bir benzetme. Kuralları henüz yazılmadı, bu yüzden işlemciye nasıl gireceği denenmedi.




---

## 6. Kaynaklar

### Kendi arşivim

Tarihler dosyaların içindeki ya da değişme tarihleri. Dosya adları arşivimdeki adlarıdır, o günün kaydı olarak duruyorlar.

| Tarih | Arşiv kaydı |
|---|---|
| **20 Ocak 2026** | Fikir defterim (kara delik notu) |
| **21 Nisan 2026** | CT-CPU arşivi: CTCPU_BIBLE.txt, MERSENNE klasörü, mersenne_ctcpu_64xbit.txt |
| **23 Nisan 2026** | CT-CPU arşivi: journal_001_log_modu_k_karari.txt |
| **Nisan-Temmuz 2026** | CT-CPU arşivi: LEMKE_OLIVER_BIAS_DETAYLI.txt |
| **8 Haziran 2026** | CT-CPU yolculuk özeti, CT-CPU ARGE günlüğü, LOG-001 ve LOG-002 |
| **9 Haziran 2026** | CT-CPU arşivi: 02_golge_kesif_2026-06-09 |
| **Haziran 2026** | CT-CPU arşivi: KISISEL_IFADE.txt |
| **18 Temmuz 2026** | Manifestom |
| **29 Temmuz 2026** | Hunter arşivi: EMULATOR_YOL_HARITASI.md |
| **2 Ağustos 2026** | Fikir defterim |
| **5 Ağustos 2026** | Hunter arşivi: ARASTIRMA_050826_137_SAYI_EVRENI.txt |
| **21 Ağustos 2026** | Hunter arşivi: ARASTIRMA_210826_DUNYA_VE_CTCPU.txt |
| **30-31 Ağustos 2026** | Özel günlüğüm: CEVAPLAR 3, 4, 5 ve 6 |
| **1-3 Eylül 2026** | Fikir defterim (01.09, 03.09), konuşma kaydı (1-2 Eylül gecesi), 2-3 Eylül oturum derlemesi |
| **4-5 Eylül 2026** | Konuşma kayıtları (4 Eylül 23:02, 5 Eylül 00:48), TEST_001 deneme raporu |
| **7 Eylül 2026** | DEXMERSENNE arşivi: dm.txt, SAYI_TEST_ALGORITMASI_001.txt (04:07), PAKETLI MERSENNE ELEGI.txt (04:22), konuşma kayıtları (03:55, 04:37), Hunter arşivi: HUNTER_PIPELINE_SONUCLARI_001.txt, fikir defterim |
| **8-12 Eylül 2026** | Konuşma kaydı (8 Eylül 18:22), fikir defterim (08.09, 10.09, 12.09) |
| **15 Eylül 2026** | CxCPUMath arşivi: Ters Mersenne P (08:02), fikir defterim, F39 (14:19), TEST_003 deneme raporu |
| **19 Eylül 2026** | Hunter arşivi: ARASTIRMA_20260919 (Ulam bandı), fikir defterim |
| **21 ve 30 Eylül 2026** | Hunter arşivi: nihai form (Rubik) |
| **1-2 Ekim 2026** | Hunter arşivi: CEM_11_ILK_CIFT_011026.txt (1 Ekim 00:57), HUNTERCPU_6X7_021026, fikir defterim (01.10) |
| **10-11 Ekim 2026** | Hunter teorileri (ayrı kayıt), Hunter fikirlerinin kronolojisi, test defteri ve Ek A |
| **11-12 Ekim 2026** | Merdiven çalışma notları ve Pascal −15…+15 çizimi |
| **13-14 Ekim 2026** | Mersenne satırı tabloları (ayrı depo: pascal-mersenne-rows) |
| **Tarihsiz** | Hunter arşivi: HUNTER.txt (makinenin bugünkü hali), CEM_OKUMA_001_US_SAYACI.txt |

Bu depodaki günlük iddialarının testleri journal_tests.c dosyasında, çıktısı TEST_OUTPUT.txt dosyasında. TESTLER/HUNTER/ altında günlük testleri dahil 30 arşiv testi, TESTLER/NIHAI_EK/ altında iki ek doğrulama programı bulunur.

### Literatür

R. J. Lemke Oliver, K. Soundararajan, Unexpected biases in the distribution of consecutive primes, PNAS 113 (2016). <https://doi.org/10.1073/pnas.1605366113>

J. Clark Scott, But How Do It Know? The Basic Principles of Computers for Everyone (2009).

Gödel numaralaması. <https://en.wikipedia.org/wiki/G%C3%B6del_numbering>

Logaritmik sayı sistemi. <https://en.wikipedia.org/wiki/Logarithmic_number_system>

Asal çarpanlara ayırma. <https://mathworld.wolfram.com/PrimeFactorization.html>

Mersenne sayıları, Fermat ve Euler. <https://mathworld.wolfram.com/MersenneNumber.html>

GIMPS, Mersenne asallarının matematiği. <https://www.mersenne.org/various/math.php>

Jerome A. Solinas, Generalized Mersenne Numbers, CACR teknik raporu CORR 99-39 (1999). <https://cacr.uwaterloo.ca/techreports/1999/corr99-39.pdf>

Çarpımsal mertebe. <https://mathworld.wolfram.com/MultiplicativeOrder.html>

P. L. Montgomery, Modular multiplication without trial division, Math. Comp. 44 (1985). Wikipedia özeti: <https://en.wikipedia.org/wiki/Montgomery_modular_multiplication>

Horner yöntemi. <https://mathworld.wolfram.com/HornersMethod.html>

A. Avizienis, Signed-digit number representations for fast parallel arithmetic, IRE Trans. Electronic Computers (1961). <https://doi.org/10.1109/TEC.1961.5219227>

Carry-save toplayıcı. <https://en.wikipedia.org/wiki/Carry-save_adder>

Taban. <https://mathworld.wolfram.com/Base.html>

Binom teoremi. <https://mathworld.wolfram.com/BinomialTheorem.html>

OEIS A001405, orta binom katsayıları (adım kuralı: C. Hanusa, 2003). <https://oeis.org/A001405>

OEIS A051920 (N. J. A. Sloane, 1999). <https://oeis.org/A051920>

OEIS A193242 (A. Povolotsky, 2013). <https://oeis.org/A193242>

OEIS A000108, Katalan sayıları. <https://oeis.org/A000108>

OEIS A007051, (3^n + 1)/2. <https://oeis.org/A007051>

L. Jiu, C. Vignat, On binomial identities in arbitrary bases, J. Integer Sequences 19 (2016). <https://arxiv.org/abs/1602.04149>

M. S. Islam ve arkadaşları, Generating binomial coefficients in a row of Pascal's triangle from extensions of powers of eleven, Heliyon (2022). <https://arxiv.org/abs/2005.14490>

Legendre formülü. <https://en.wikipedia.org/wiki/Legendre%27s_formula>

Çift Mersenne sayıları. <https://mathworld.wolfram.com/DoubleMersenneNumber.html>


## 7. Manifesto

Kişisel mesajım ayrı dosyada: [Küçük Mesaj](KUCUK_MESAJ.md).
