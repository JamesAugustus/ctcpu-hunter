# CTMemTensor

James Augustus

Düşünülen bellek ve adresleme sistemleri

## Öz

CTMemTensor, sayı değerlerini, bu değerlerin matematiksel konumlarını ve simetri ilişkilerini ortak bir bellek kaydında ifade etmek için kullanılan çalışma adıdır. Bir kayıt tek bir değeri, simetrik iki konumu, bir matematiksel tarifi veya bunlara bağlı hesaplanmış değerleri taşıyabilir. Bu belge, düşünülen adresleme ve saklama biçimlerini tanımlar. Seçeneklerden biri henüz kesin bir komut kümesi veya fiziksel RAM düzeni olarak kabul edilmemiştir.

Ana örnekte adresler satırın ortasından başlar. [1,4,6,4,1] satırında 6 değeri 0, soldaki 4 değeri -1, sağdaki 4 değeri +1 adresindedir. İki orta elemanı bulunan satırlarda ortak merkez değeri ile iki ayrı konumun nasıl temsil edilebileceği ayrıca ele alınır. Merkezden uzaklık ve yön, kenardan başlayan sütun numarası ve geometrik koordinat ayrı adresleme seçenekleri olarak korunur.

PCCPU görevlerin başlatılması ve tamamlanmasının yönetimiyle ilişkilidir. CTMemTensor ise verinin, konumun ve simetri ilişkisinin gösterimiyle ilgilidir. Pascal katsayıları bu düzenin matematiksel örnek ailesidir. N(p) işlevi, seçilen Mersenne tabanında katsayıların doğrudan hane olarak kullanılabildiği satır sınırını verir. Fiziksel bellek, çok çekirdekli yürütme veya performans üstünlüğü henüz uygulanmış değildir.

## 1. Tanımlar ve kapsam

Bu belgede n, Pascal satırının numarasıdır. En üstteki tek 1, n = 0 satırıdır. Bir satırda n + 1 eleman vardır. Örneğin 1331 gösterimi dört eleman içerir, fakat karşılık gelen Pascal satırı n = 3'tür. Hane sayısı ile satır numarası aynı parametre değildir.

| Gösterim | Anlam |
|---|---|
| C(n,j) | Soldan, sıfırdan sayılan j sütunundaki klasik binom katsayısı |
| N(n,z) | Bu belgede incelenen, merkezden başlayan katsayı okuması |
| d | Merkezden veya merkez çiftinden uzaklık, negatif değildir |
| a | Seçilen taraf, örnek kodlama 0 = sol ve 1 = sağ |
| j_L, j_R | Sol ve sağ konumların klasik sütun numaraları |
| x | İşlemde kullanılan taban veya kuvvet değişkeni |
| N(p) | Tek parametreli, en büyük eldesiz satır işlevi |

N(n,z) ve N(p) burada farklı görevler için kullanılan gösterimlerdir. İlki bir satırdaki değeri okumaya, ikincisi bir tabanda geçerli satır aralığını belirlemeye yarar. Son komut biçiminde bunlar ayrı işlem adlarıyla da gösterilebilir. Parametre sayısının farklı olması, tür ve anlam ayrımının ayrıca tanımlanması gereğini ortadan kaldırmaz.

Klasik C(9,4) = 126 ifadesi matematiksel olarak doğrudur. Merkezden başlayan gösterimde aynı katsayı N(9,0) = 126 olarak okunur. Bu iki ifadedeki 4 ve 0 aynı koordinat sisteminin adresleri değildir. İç hesapta C(n,j) kullanılması, dış adreslemenin de sütun sırasını izlemesini gerektirmez.

CTMemTensor adı çok eksenli kayıt fikrini belirtir. Bu belge genel tensör çarpımı veya tensör cebiri gerçekleştiren bir donanım tanımlamaz. Satır, merkezden uzaklık, taraf, taban ve işlem türü ayrı eksenler veya kayıt alanları olarak ele alınabilir.

## 2. Merkezden başlayan işaretli adresleme

Tek orta elemanlı n = 4 satırı için merkezden başlayan adresler şöyledir:

| Katsayı | 1 | 4 | 6 | 4 | 1 |
|---|---|---|---|---|---|
| İşaretli adres z | -2 | -1 | 0 | +1 | +2 |
| Uzaklık d = abs(z) | 2 | 1 | 0 | 1 | 2 |
| Taraf | Sol | Sol | Merkez | Sağ | Sağ |

Bu düzende N(4,0) = 6, N(4,-1) = N(4,+1) = 4 ve N(4,-2) = N(4,+2) = 1 olur. İşaret yönü, mutlak değer uzaklığı belirtir. -1 ile +1 aynı konum değildir. İkisinin de uzaklığı 1'dir ve bu satırda katsayıları eşittir.

Merkezden dışarı doğru yalnız farklı katsayılar okunacaksa sıra 6, 4, 1 olur. Soldan sağa bütün konumlar okunacaksa sıra 1, 4, 6, 4, 1 olarak kalır. Okuma sırası ile satırın matematiksel yapısı ayrı kavramlardır.

Tek orta eleman bulunan n = 2m satırlarında klasik sütuna dönüşüm j = m + z'dir. Geçerli adres aralığı -m ≤ z ≤ m olur. Katsayı C(n,m+z) ile hesaplanabilir. Buradaki dönüşüm, yeni adres sisteminin mevcut binom hesabıyla birlikte kullanılmasını sağlar.

## 3. Uzaklık ve yön biti

İşareti ayrı bir alan olarak saklamak da mümkündür. Bu seçenekte kayıt (n,d,a) biçiminde düşünülür. Örnek yön kodlaması a = 0 için sol, a = 1 için sağdır. Bit değerlerinin hangi yöne karşılık geleceği henüz kesin bir mimari karar değildir.

m = floor(n/2) olsun. 0 ≤ d ≤ m için merkezden dışarı doğru iki sütun

`j_L = m - d`

`j_R = n - m + d`

ile bulunur. Ortak katsayı C(n,j_L) = C(n,j_R)'dir. Bu eşitlik j_R = n - j_L olmasından kaynaklanır.

N(n,d)[a] biçimi, bu seçeneği yazmak için kullanılabilir. Bu durumda ikinci parametre işaretli z değil, negatif olmayan d uzaklığıdır. Aynı yazılım arayüzünde hangi kipin kullanıldığı açık olmalıdır. Bu metin olası gösterimleri karşılaştırır, aynı ifadeye sessizce iki anlam yüklemez.

### İki orta elemanlı satırlar

n = 9 satırının katsayıları [1,9,36,84,126,126,84,36,9,1]'dir. m = 4 olur. d = 0 için j_L = 4 ve j_R = 5 elde edilir. İki katsayı da 126'dır. Dolayısıyla N(9,0) = 126 merkez değerini verir, fakat tek başına hangi orta konumun seçildiğini belirtmez.

| Uzaklık d | Sol sütun | Sağ sütun | Ortak katsayı |
|---|---|---|---|
| 0 | 4 | 5 | 126 |
| 1 | 3 | 6 | 84 |
| 2 | 2 | 7 | 36 |
| 3 | 1 | 8 | 9 |
| 4 | 0 | 9 | 1 |

Konum da gerekli olduğunda taraf alanı korunur: N(9,0)[0] sol orta konumu, N(9,0)[1] sağ orta konumu seçebilir. -0 ile +0 farklı tamsayı adresleri değildir. Bu nedenle sıfırdaki iki konumu yalnız işaretle ayırmak yeterli olmaz.

n = 4 ve d = 0 için ise j_L = j_R = 2'dir. İki taraf tek merkez konumuna yönelir. Değer toplamaya bir kez katılır. n = 9 ve d = 0'da iki farklı konum bulunduğundan, eşit katsayıya rağmen iki ağırlıklı katkı vardır.

## 4. Diğer düşünülen adresleme sistemleri

### 4.1. Kenardan başlayan sistem

Klasik sütun numarası j, soldan 0 ile n arasında ilerler. n = 4 için adresler 0,1,2,3,4 ve katsayılar 1,4,6,4,1'dir. Bu sistemde C(9,4) = 126 yazılır. Simetrik eş j ile n-j arasındadır.

Önceki PCCPU çift-konum örneğinde uçları birlikte tutan thread_no_1 kaydı bu tür bir seçeneği gösterir. Kenardan başlayan bu seçenek korunur. Merkezden başlayan N(n,z) ile aynı adres sistemi olarak okunmamalıdır.

### 4.2. Geometrik merkez sistemi

Satırın geometrik merkezi n/2 alınabilir. u = j - n/2 koordinatı, n = 4 için -2,-1,0,+1,+2 değerlerini verir. n = 9 için ortadaki iki koordinat -1/2 ve +1/2 olur. Bu seçenekte her konum ayrı koordinata sahiptir, ancak çift merkezli satırda 0 adresinde eleman yoktur.

Kesirli koordinattan kaçınmak için q = 2j - n kullanılabilir. n = 4 adresleri -4,-2,0,+2,+4 olur. n = 9'un iki orta adresi -1 ve +1'dir. Bu q, merkez çiftinden uzaklık d ile aynı ölçeğe sahip değildir. Geometrik sistem, N(9,0) = 126 merkez okumasına alternatif bir koordinat sözleşmesidir.

### 4.3. Ortadaki elemanlardan birini başlangıç alma

Çift merkezli satırda sol orta eleman başlangıç seçilirse t = j - floor(n/2) kullanılabilir. n = 9 için iki orta elemanın adresleri 0 ve 1 olur. Bütün adresler tamsayıdır, fakat simetrik eş t ile -t arasında değildir. Bu satırda eşleme t ile 1-t arasındadır. Simetri kuralı adresleme kipine göre değişir.

### 4.4. Seçeneklerin özeti

| Sistem | n = 4 merkez adresi | n = 9 orta adresleri |
|---|---|---|
| Merkez çifti ve taraf | 0, tek konum | 0 ve ayrı sol/sağ alanı |
| Geometrik u | 0 | -1/2 ve +1/2 |
| İki kat geometrik q | 0 | -1 ve +1 |
| Sol orta başlangıcı t | 0 | 0 ve 1 |
| Soldan sütun j | 2 | 4 ve 5 |

Merkezden değer okuma, bu belgenin ana örneğidir. Diğer sistemler düşünülen alternatiflerdir. Uygulama, seçtiği adresleme kipini kayıtla birlikte taşımalı veya arayüzün tamamında sabit tutmalıdır.

## 5. Konum seçimi ve aritmetik işlemi

Bir konumu seçmek, o konumdan hangi büyüklüğün okunacağını tek başına belirlemez. Aynı kayıttan katsayı, kuvvet veya basamak katkısı istenebilir. Katsayının kendisini bir kuvvete yükseltmek de ayrı bir işlem olarak düşünülebilir.

| İşlem | Tanım | n = 4, sol 4, x = 10 için |
|---|---|---|
| Katsayı okuma | c = C(n,j) | 4 |
| Taban kuvveti | x^(n-j) | 1000 |
| Basamak katkısı | c × x^(n-j) | 4000 |
| Katsayı kuvveti | c^j, bu seçenekte üs soldan sütun j | 4 |

Sağdaki 4 için j = 3 olur. Katsayı yine 4, basamak katkısı 40 ve katsayı kuvveti 4³ = 64'tür. 1331 örneğinde sol 3 için j = 1 ve 3¹ = 3, sağ 3 için j = 2 ve 3² = 9 elde edilir. Bu, katsayının konum kuvvetine yükseltildiği seçeneğin somut karşılığıdır. Üs olarak uzaklık d seçilirse farklı bir işlem elde edilir. Hangi üs kuralının kullanılacağı işlem tanımında belirtilmelidir.

14641 sayısını onluk yazıyla girmek, hesapta kullanılacak x değerini kendiliğinden belirlemez. Girdi yazım tabanı ile matematiksel işlem tabanı ayrı alanlar olabilir. İki alanın da 10 seçildiği örnekte basamak katkıları 10000,4000,600,40,1 olur ve toplam 14641'dir.

## 6. Düşünülen bellek kayıtları

CTMemTensor için üç saklama biçimi ele alınmaktadır. Birincisi simetrik iki değerin tamamen hesaplanıp ayrı alanlarda tutulmasıdır. İkincisi n, konum, taraf, taban ve işlem türünün saklanarak değerin gerektiğinde üretilmesidir. Üçüncüsü bu matematiksel tarife ek olarak daha önce hesaplanmış değerlerin önbellekte tutulmasıdır.

| Alan grubu | İçerik |
|---|---|
| Adresleme | Kip, satır, konum veya uzaklık, taraf |
| Matematiksel veri | Ortak katsayı, işlem tabanı veya başvurusu |
| İşlem | Katsayı, kuvvet, basamak katkısı veya katsayı kuvveti |
| Değerler | Gerekirse sol ve sağ için ayrı tam sayılar |
| Durum | Tarafların hazır olma ve geçerlilik bilgileri |
| Sahiplik | Mantıksal thread veya görevlendirilen çekirdek kimliği |

Thread kimliği, matematiksel koordinat ve fiziksel bellek adresi farklı alanlardır. thread_no_1'in d = 0 veya j = 0 konumuna denk gelmesi zorunlu değildir. Örneğin aynı thread, n = 4 satırındaki iki ucu, yani d = 2 çiftini ve x^4 ile x^0 değerlerini sahiplenebilir. Merkezden adresleme bu sahipliği engellemez.

Tek merkezli satırda iki taraf aynı konuma yönelirse bir kez sayılır. Çift merkezli satırda katsayı aynı olsa da iki basamak ağırlığı ayrı tutulur. Satır, taban, konum veya işlem türü değiştiğinde ilişkili önbellek değerleri geçersizleştirilmelidir. Bir tarafın katsayısı bağımsız değiştirilirse ortak katsayı ilişkisi ayrılmalıdır.

Bir çekirdek veya görev de hücre kaydında temsil edilebilir. Bu, fiziksel işlemcinin bir RAM hücresinin içine yerleştirildiği anlamına gelmez. Yazılımla tutulan kayıt düzeni ile hesaplama yapabilen özel bellek donanımı ayrı geliştirme aşamalarıdır. Kayıt alanlarının bit genişliği, RAM erişim yolları ve eşzamanlı yazma kuralları açıktır.

## 7. Pascal simetrisi ve N(p) sınırı

Pascal katsayıları C(n,j) = C(n,n-j) eşitliğini sağlar. Bütün satırın değeri, b ≥ 2 tamsayı tabanı için

`(b+1)^n = Σ C(n,j) b^(n-j),  j = 0,...,n`

olarak yazılır. Katsayıların doğrudan hane olabilmesi için C(n,floor(n/2)) < b gerekir. b = 2^p - 1 ve p ≥ 2 olduğunda

`N(p) = max { n ≥ 0 : C(n,floor(n/2)) < 2^p - 1 }`

bu koşulu sağlayan son satırı verir. n ≤ N(p) aralığında katsayı simetrisi, doğrudan hane simetrisi olarak okunabilir. Sınır aşıldığında katsayılar simetrik kalır, fakat elde taşınmış haneler aynı simetriyi taşımayabilir.

Örneğin N(3) = 4'tür. Yedi tabanında n = 4 satırı [1,4,6,4,1] ve değer 4096'dır. n = 5 katsayıları [1,5,10,10,5,1] iken normalleştirilmiş haneler [1,6,4,3,5,1] olur. Bu nedenle simetrik katsayı saklama ile normalleştirilmiş hane saklama ayrı kiplerdir.

Matematiksel çalışma [pascal-mersenne-rows](https://github.com/JamesAugustus/pascal-mersenne-rows) deposundadır. Yayımdaki [önceki Türkçe not](https://github.com/JamesAugustus/pascal-mersenne-rows/blob/main/tr/note.md) taban gösterimini ve eldesiz koşulu açıklar. N(p) eki sabit tabandaki son geçerli satırı inceler. CTMemTensor, N(p)'yi bellek hızını kanıtlayan bir sonuç olarak kullanmaz.

## 8. Uygulama durumu ve açık kararlar

[PCCPU C örneği](../../../../kod/PCCPU/pccpu_address_model.c), üretici ve toplayıcı görevlerinin bağımlılığını sınar. İç hesapta klasik C(n,j) katsayıları kullanılır. 60.353 kontrol bu mevcut programa aittir. CTMemTensor'ın merkez adres çözücüsü, seçilebilir adresleme kipleri veya RAM protokolü bu C programında henüz uygulanmamıştır.

HTML rehberindeki sayısal gösterim, adres dönüşümlerini ve simetrik katsayı çiftlerini açıklayan bir tarayıcı hesabıdır. Gerçek bir thread zamanlayıcısı veya RAM gerçekleştirmesi değildir. [Test sonuçları](../PCCPU/TEST_SONUCLARI.md), mevcut C testinin kapsamını belirtir.

Açık kararlar adresleme kipinin seçimi, çift merkez durumunun gösterimi, yön bitinin kodlanması, işlem türleri, tam değer veya tarif saklama, önbellek geçerliliği, çekirdek sahipliği ve fiziksel bellek yerleşimidir. Bu belge bunları düşünülen sistemler olarak kayda geçirir. CTMemTensor çalışma adıdır. Yeni bir işlemci standardı, bitmiş donanım veya kanıtlanmış performans üstünlüğü iddiası yoktur.

## Kaynak ve ilgili belgeler

[PCCPU](../PCCPU/PCCPU.md), [C modeli açıklaması](../PCCPU/PCCPU_C_TESTI_ACIKLAMA.md), [English](../../../../md/CTCPU_PARTS/CTMemTensor/CTMemTensor.md).

Metin CC BY 4.0. Telif hakkı © 2026 James Augustus.
