# Resolver

James Augustus

Resolver, sayının normal biçimini gölgeye çeviren birimdir: yedi küçük asalın (2, 3, 5, 7, 11, 13, 17) üslerini ve bunlara bölünmeyen artığı bulur. Gölge sistemi bir sayıyı hem binom olarak, örneğin $19 = 2^4 + 3$ gibi $2^k \pm r$ biçiminde tutabiliyor, hem de çarpanlarına ayırabiliyor. Bu, tasarladığım işlemcilerden birinin özelliği ve bu işlemci taban aritmetiği de yapabiliyor. Bu belgede kodu yazılmış ve sınanmış biçimleri en yeniden en eskiye doğru anlatıyorum. Kodda uygulanmamış ya da yalnız örnek düzeyinde kalan biçimler [Resolver deneyleri](Deneyler/Deneyler.md) belgesindedir. Her biçimde tarih ve kaynak, fikir, mekanizma, programla doğrulanmış bir örnek, kodun ve sınamanın durumu ve bir önceki biçimden farkı yazılıdır. Sayılar, $_8$ ile işaretlenmedikçe onluktur.

| Sıra | Biçim | Tarih | Sınama |
|:---:|---|---|---|
| 1 | Akan sayaç | 12-13 Ekim 2026 | C çekirdeği, $2^{24}$'e kadar her sayı |
| 2 | Akış katlaması, $2^p - 1$'e göre | 13 Eylül 2026 | altı farklı $p$ ile kalan hesabı |
| 3 | Katlama kapısı ve üs-pozisyonel gölge | 9 Eylül 2026 | 393.216 sonuç |
| 4 | Hane ağırlıkları ve kesme | 20 Temmuz 2026 | ağırlıklar $2^{24}$'e kadar |
| 5 | İlk sürüm: iki vuruşluk boru | 30 Haziran 2026 | yaklaşık 117 milyon kontrol |

## İçindekiler

| Bölüm | Başlık |
|---|---|
| 1 | Akan sayaç |
| 1.1 | Tarih ve kaynak |
| 1.2 | Fikir |
| 1.3 | Mekanizma |
| 1.3.1 | Kalan akışı |
| 1.3.2 | Bölüm akışı |
| 1.3.3 | Sekizlik üs sayacı |
| 1.4 | Örnek |
| 1.5 | Kod ve sınama |
| 1.6 | Farkı |
| 2 | Akış katlaması, $2^p - 1$'e göre |
| 2.1 | Tarih ve kaynak |
| 2.2 | Fikir |
| 2.3 | Mekanizma |
| 2.4 | Örnek |
| 2.5 | Kod ve sınama |
| 2.6 | Farkı |
| 3 | Katlama kapısı ve üs-pozisyonel gölge |
| 3.1 | Tarih ve kaynak |
| 3.2 | Fikir |
| 3.3 | Mekanizma |
| 3.4 | Örnek |
| 3.5 | Kod ve sınama |
| 3.6 | Üs-pozisyonel gölge |
| 3.7 | Farkı |
| 4 | Hane ağırlıkları ve kesme |
| 4.1 | Tarih ve kaynak |
| 4.2 | Fikir |
| 4.3 | Mekanizma |
| 4.3.1 | Kesme |
| 4.4 | Örnek |
| 4.5 | Kod ve sınama |
| 4.6 | Farkı |
| 5 | İlk sürüm: iki vuruşluk boru |
| 5.1 | Tarih ve kaynak |
| 5.2 | Fikir |
| 5.3 | Mekanizma |
| 5.3.1 | Birinci vuruş, bölünebilirlik |
| 5.3.2 | İkinci vuruş, üs bulma |
| 5.4 | Örnek |
| 5.5 | Kod ve sınama |
| 5.6 | Farkı |
| 6 | Açık kalanlar |

## 1. Akan sayaç

### 1.1 Tarih ve kaynak

12-13 Ekim 2026. Tarif: "Sayı geldi ve parçalara ayrıldı: Horner olarak ve farklı taban olarak. Bir data olarak tutuluyor ve çözülmesi basit." Bu tarif tek dosyalık bir C çekirdeğine dönüştü.

### 1.2 Fikir

Sayı makineye girerken bölünmeye başlar. Haneler soldan sağa akarken hem kalan hem bölüm aynı akıştan çıkar. Bölüm bir sonraki aşamaya akar ve orada yeniden bölünür. Üsler sekizlik bir kilometre sayacında birikir.

### 1.3 Mekanizma

Üç parça vardır.

#### 1.3.1 Kalan akışı

Her hane $d$ geldiğinde yedi kanal aynı anda $r_q \leftarrow (8\,r_q + d) \bmod q$ günceller. Son hane girdiği an yedi kalan hazırdır. $q = 7$ için $8 \equiv 1$ olduğundan kalan, sekizlik haneler toplamının 7'ye göre kalanıdır, $q = 3$ için $8 \equiv -1$ olduğundan haneler sırayla eklenip çıkarılır, $q = 2$ için yalnız son haneye bakılır.

#### 1.3.2 Bölüm akışı

Aynı akışta bölümün haneleri de çıkar: $t = 8\,r + d$, bölüm hanesi $\lfloor t / q \rfloor$, yeni kalan $t \bmod q$. Bölüm haneleri konveyör gibi bir sonraki aşamaya girer.

#### 1.3.3 Sekizlik üs sayacı

Her bölünmede kanalın sayacı bir artar. Dört satır bir üssün sekizlik haneleridir: $e = rs1 + 8\,rs2 + 64\,rs3 + 512\,rs4$, en fazla $4095$. Bir satır 7'den 0'a dönerse elde üst satıra geçer.

### 1.4 Örnek

$3^{14} = 4\,782\,969 = 22175571_8$. Kalan akışında yalnız 3 kanalı 0'a iner. Bölüm akışında değer her aşamada 3'e bölünerek akar. Sekizinci bölünmede sayaç 7'den 0'a döner ve elde ikinci satıra geçer. On dördüncü bölünmede değer 1 olur. Okunan üs $e_3 = 6 + 8 \cdot 1 = 14 = 16_8$. Aynı mekanizmayı başka sayılarla hane hane ve kare kare [dişli modeli](Cark.md) belgesinde gösteriyorum.

### 1.5 Kod ve sınama

C99 çekirdeği. 25 Ekim 2026'da yeniden çalıştırıldı: $1 \le N \le 2^{24}$ aralığındaki her sayı için çevirme ve geri kurma 0 hata, 100.000 rastgele çiftte 200 sekizlik haneye kadar toplama, çıkarma, çarpma ve bölme 0 hata. Bilerek bozulmuş üç kopyanın üçünde de hata yakalandı.

### 1.6 Farkı

[Resolver deneylerindeki](Deneyler/Deneyler.md) katlı merdivende gölge satırları merdivenin katlarıydı ve bir üs hücresi en fazla 7 tutuyordu. Burada aynı dört satır tek bir üssün sekizlik haneleridir. Aşağı taşınan şey kalan değer değil, üssün hanesidir.

## 2. Akış katlaması, $2^p - 1$'e göre

### 2.1 Tarih ve kaynak

13 Eylül 2026. Mersenne araştırma hattının 24. ve 26. çalışmaları.

### 2.2 Fikir

$M = 2^p - 1$'e göre kalan, bölme yapmadan bulunur. $2^p \equiv 1 \pmod M$ olduğundan sayının $p$. bitten yukarısı, aşağı katlanıp alt kısma eklenebilir. Çok uzun bir sayı birden çok parça (limb) halinde akarken her parça doğru konuma kaydırılıp aynı halkaya eklenir.

### 2.3 Mekanizma

$$V \leftarrow (V \gg p) + (V \,\&\, M), \qquad V = M \text{ ise } V \leftarrow 0$$

Değer $p$ bite sığana kadar tekrarlanır. Bu bir halkadır: en üstten taşan bit en alta sarar. Akış sürümünde $i$. parça $(i \cdot w) \bmod p$ konumuna kaydırılarak toplayıcıya eklenir.

### 2.4 Örnek

$p = 13$, $M = 8191$, $V = 37634$:

$$37634 = 4 \cdot 2^{13} + 4866 \quad\Rightarrow\quad 4 + 4866 = 4870$$

Gerçekten $37634 \bmod 8191 = 4870$.

### 2.5 Kod ve sınama

Python. $p = 13, 31, 61, 127, 521$ ve $4096$ ile, farklı parça genişlikleriyle sınandı. [Paketlenen test komutu](../../../../TESTLER/HUNTER/11_DEX_ARASTIRMALARI/hunter_stream026_9dd5af2c/TEST_TR.md) ilk beş değeri kapsar. Ek $p = 4096$ kontrolü bu paketin dışındaki tarihsel bir denetimdir. Bu çalışma yalnız kalanı hesaplar, sayının asal olup olmadığına karar vermez.

### 2.6 Farkı

Yedi küçük asal yerine tek ve büyük bir modül, $2^p - 1$, için çalışır. Kadranının diş sayısı $2^p - 1$ olan tek bir halka gibidir.

## 3. Katlama kapısı ve üs-pozisyonel gölge

### 3.1 Tarih ve kaynak

9 Eylül 2026. Mersenne araştırma hattının kanal modeli ve register modeli.

### 3.2 Fikir

Küçük bir asala göre kalan, sekizlik hane akışı yerine ikilik katlamayla da bulunabilir. Her kanal için öyle bir $w$ seçilir ki $2^w \equiv \pm 1 \pmod q$ olsun. O zaman sayının alt $w$ biti ile üstü toplanır ya da çıkarılır ve kalan değişmez.

### 3.3 Mekanizma

| $q$ | $w$ | Özdeşlik | Katlama |
|---:|---:|---|---|
| 3 | 2 | $2^2 \equiv +1$ | $LOW + HIGH$ |
| 7 | 3 | $2^3 \equiv +1$ | $LOW + HIGH$ |
| 5 | 2 | $2^2 \equiv -1$ | $LOW - HIGH$ |
| 17 | 4 | $2^4 \equiv -1$ | $LOW - HIGH$ |
| 11 | 5 | $2^5 \equiv -1$ | $LOW - HIGH$ |
| 13 | 6 | $2^6 \equiv -1$ | $LOW - HIGH$ |

Değer $w$ bite sığana kadar katlanır, sonra en fazla birkaç $q$ ekleme ya da çıkarmayla $0 \le r < q$ aralığına getirilir. 2 kanalı katlama istemez: kalan son bittir, üs sondaki sıfır bitlerinin sayısıdır.

### 3.4 Örnek

$738$, 7 kanalında: $738 \to 2 + 92 = 94 \to 6 + 11 = 17 \to 1 + 2 = 3$. 11 kanalında: alt 5 bit $2$, üst kısım $23$, $2 - 23 = -21$, iki kez 11 eklenince $1$. Gerçekten $738 \bmod 7 = 3$, $738 \bmod 11 = 1$.

### 3.5 Kod ve sınama

Python kalan kapısı. Altı kanal ve $0..65535$ aralığındaki her giriş için 393.216 sonuç sınandı, hata yok. Bu belge için aynı katlamayı ayrıca yazıp aynı aralıkta denedim, bütün sonuçlar doğru çıktı.

### 3.6 Üs-pozisyonel gölge

Aynı çalışmada, büyük bir üssün sekizlik hanelerini satırlara dağıtan bir gölge adayı da tanımlandı: $E(q) = e_1(q) + 8\,e_2(q) + 64\,e_3(q) + 512\,e_4(q)$. Örneğin $3^{14}$ için $E_3 = 16_8$, yani $e_1 = 6$, $e_2 = 1$. Akan sayaç bu adayın çalışan hali oldu.

### 3.7 Farkı

Kalanı bulmak için sekizlik hane akışı yerine ikilik katlama kullanılır.

## 4. Hane ağırlıkları ve kesme

### 4.1 Tarih ve kaynak

20 Temmuz 2026, 2 Ağustos 2026'da güncellendi. Gölge mekanizması şeması ve sade iniş kartı.

### 4.2 Fikir

Bir sayının bir asala göre kalanı, sekizlik hanelerinin sabit ağırlıklarla toplamının o asala göre kalanıdır. Ağırlıklar $8^k \bmod q$ dizisidir ve her asal için kısa bir döngü oluşturur. Rough değerin inişi ise bir çıkarma ve bölme değil, alt üç biti kesip gerisini almaktır.

### 4.3 Mekanizma

Ağırlıklar, en düşük haneden başlayarak:

| $q$ | Ağırlıklar ($8^k \bmod q$) |
|---:|---|
| 3 | 1, 2 |
| 5 | 1, 3, 4, 2 |
| 7 | 1 (hane toplamı) |
| 11 | 1, 8, 9, 6, 4, 10, 3, 2, 5, 7 |
| 13 | 1, 8, 12, 5 |
| 17 | 1, 8, 13, 2, 16, 9, 4, 15 |

2 kanalı kaydırmadır ve tabloya girmez. Kalan $r_q = \sum_k d_k \cdot w_k \bmod q$ olur.

#### 4.3.1 Kesme

$\text{rough} - (\text{rough} \,\&\, 7)$ ve ardından $/8$, alt üç biti kesip gerisini almaktır. Çıkarıcı da bölücü de gerekmez, devrede yalnız tel bağlantısıdır. Kesilen üç bit bir sonraki satırın $a$ hücresine olduğu gibi yazılır. Kalan rough, her adımda üzerine yazılan bir yuvarlanan rough register'ında taşınır.

### 4.4 Örnek

$360 = 550_8$, haneler en düşükten $0, 5, 5$. 11 kanalında $0 \cdot 1 + 5 \cdot 8 + 5 \cdot 9 = 85$ ve $85 \bmod 11 = 8$. 13 kanalında $0 + 40 + 60 = 100$ ve $100 \bmod 13 = 9$. Gerçekten $360 \bmod 11 = 8$, $360 \bmod 13 = 9$. Kesme: $59 = 73_8$, alt üç bit $3$, gerisi $7$.

### 4.5 Kod ve sınama

Ağırlıklar kayıtlı ölçüme göre $2^{24}$'e kadar bütün sayılarda doğrulandı, hata yok. Bu belge için 360'ın altı kanalı ayrıca hesaplandı ve hepsi doğru çıktı.

### 4.6 Farkı

Sonraki biçimlerde aynı kalan, haneler soldan sağa akarken Horner biçimiyle bulundu. Burada haneler sabit ağırlıklarla aynı anda toplanır.

## 5. İlk sürüm: iki vuruşluk boru

### 5.1 Tarih ve kaynak

30 Haziran 2026. Resolver biriminin ilk tam analizi. Özeti 3 Ağustos ve 1 Eylül 2026'da yeniden yazıldı.

### 5.2 Fikir

Genel bir bölücü yoktur ama Resolver hep aynı yedi sabit asala böler. Sabit bir sayıya bölmek kaydırma ve toplamayla yapılabilir. Bölünebilirlik testi bundan da ucuzdur.

### 5.3 Mekanizma

İki vuruş vardır.

#### 5.3.1 Birinci vuruş, bölünebilirlik

Sekiz sekizlik hane soldan sağa akar, yedi kanalın kalanı her hanede aynı anda güncellenir: $r_q \leftarrow (8\,r_q + d) \bmod q$. Ara değer en fazla $8q - 1$'dir ve kalan, $q$ karşılaştırılıp çıkarılarak bulunur. Son hane tek başına yalnız 2, 4 ve 8 ile bölünebilirliği söyler. Tek asallar için bütün haneler gerekir.

#### 5.3.2 İkinci vuruş, üs bulma

Sayıyı bölen asallarda sabit $q$ bölme ağı ve bir sayaç ile üs bulunur: sayı bölünmez olana kadar bölünür, sayaç üssü verir. 2'nin üssü, sondaki sıfır bitlerinin sayısı olarak tek adımda okunur.

Yedi asala bölünmeyen artık $rc$'ye düz yazılır ve açılmaz. Bu sürümde Resolver her yüklemede çalışıyordu. Sonraki sürümlerde gölge, ilk çarpımsal işlemde kurulan tembel bir gölge oldu.

### 5.4 Örnek

$510510 = 2 \cdot 3 \cdot 5 \cdot 7 \cdot 11 \cdot 13 \cdot 17 = 01745056_8$. Sekiz hane aktıktan sonra yedi kanalın hepsinin kalanı 0'dır. $360$: 2'ye üç, 3'e iki, 5'e bir kez bölünür, gölge $[3, 2, 1, 0, 0, 0, 0]$, artık 1.

### 5.5 Kod ve sınama

Eski emülatörde kayıtlı ölçüm: 24 bitlik bütün sayılar ve yedi asal için yaklaşık 117 milyon bölünebilirlik kontrolü ve 16,7 milyon çevirme ve geri çevirme, hata yok. Üs bulmada ortalama 1,66 adım, en kötü 15 adım ($3^{15}$). [Emülatör kaynağındaki](../../../../TESTLER/HUNTER/01_RESOLVER/resolver_emulator/resolver_emulator.c) Test 7, $1 \le N \le 2^{24}-1$ aralığını kapsar. Tek asal kanallarındaki her başarılı bölme bir adım sayılır, 2 çarpanları varsa tamamı birlikte bir adım sayılır. Sekizlik hane akışı ve başarısız bölünebilirlik kontrolleri bu sayıya dahil değildir. Bu emülatörü 25 Ekim 2026'da yeniden çalıştırdım ve bu sayımları yeniden ürettim. Bunlar yazılım modelinin adımlarıdır, ölçülmüş saat çevrimleri değildir.

### 5.6 Farkı

Bu ilk sürüm artığı düz taşır. Artığı sekize bölerek indirme fikri bu belgede anlatıldı ama kodda uygulanmadı. Sonraki bütün biçimler bu iki vuruşun üzerine kuruldu.

## 6. Açık kalanlar

Gölge satırlarının akan sayaçtaki gibi bir üssün sekizlik haneleri mi, yoksa [katlı merdivendeki](Deneyler/Deneyler.md) gibi merdivenin katları mı olacağı kesinleşmedi. $rc$'nin ilk rough çarpanı mı yoksa son işlenmemiş artığı mı tuttuğu açıktır. Sıfır, negatif ve kesirli girdiler ayrıca tanımlanmalıdır.

Bu biçimler üzerinde FPGA'da deneyler yapılacak. Sonuçları ayrıca paylaşacağım.

İlgili belgeler: [Resolver deneyleri](Deneyler/Deneyler.md), [Dişli modeli](Cark.md), [Register](../Register/Register.md) ve [Parçalar](../README.md).
