# CTCPU parçaları

James Augustus

## Özet

Bu işe renkten başladım: üç ışık kanalı sekiz renk, sekiz renk bir sekizlik hane eder. Hikâyesi [Hücre](Hucre/Hucre.md) belgesindedir. CTCPU'yu basit bir seçim üzerine kurdum. Toplama için sayının normal sekizlik basamaklarını tutuyorum. Sayının yapısı çarpma, bölme ya da kökte işe yarayacaksa gölgesini, yani küçük asallara göre üslerini hazırlıyorum. Bu klasör, işlemcinin parçalarını en küçüğünden başlayarak anlatır. Her parçanın kendi klasörü, kendi belgesi ve çizimleri vardır. Bu çalışmaya Hunter adıyla devam ettim. Güncel tasarımı, açık kalan işleri ve önceki tasarımlardaki parçaları ayırarak yazıyorum.

## İçindekiler

| Bölüm | Başlık |
|---|---|
| 1 | Okuma sırası |
| 2 | Güncel düzen |
| 3 | Bütün parçalar ve durumları |
| 4 | Önceki tasarımlardaki parçalar |
| 5 | Belgelerin biçimi |

## 1. Okuma sırası

| Sıra | Parça | Klasör | Ne anlatır |
|:---:|---|---|---|
| 1 | Hücre | [Hucre](Hucre/Hucre.md) | üç bit, bir sekizlik hane, sekiz renk |
| 2 | Register | [Register](Register/Register.md) | 8 satır × 8 hücre, 192 bit, satırların görevleri |
| 3 | Resolver | [Resolver](Resolver/Resolver.md) | çalışan ve sınanmış Resolver biçimleri |
| | | [Dişli modeli](Resolver/Cark.md) | Resolver'ın kadran ve çarklarla kare kare anlatımı |
| | | [Resolver deneyleri](Resolver/Deneyler/Deneyler.md) | kodda uygulanmamış Resolver biçimleri |
| 4 | ALU | [ALU](ALU/ALU.md) | iki katman: gölge ve düz |
| | Toplayıcı | [ALU/Toplayici](ALU/Toplayici/Toplayici.md) | hizalama, elde zinciri |
| | Çarpma ve bölme | [ALU/Carpma_Bolme](ALU/Carpma_Bolme/Carpma_Bolme.md) | üs aritmetiği, kesir, rough çarpım |
| | Karekök | [ALU/Karekok](ALU/Karekok/Karekok.md) | üs yarılama, sembolik kök, sürekli kesir |
| 5 | Türler | [Turler](Turler/Turler.md) | sekiz tür kodu ve durumlar |
| 6 | Çekirdek | [Cekirdek](Cekirdek/Cekirdek.md) | parçaların birleşmesi, bir komutun yolculuğu |

Komut biçimleri [ISA](../ISA.md) belgesindedir.

## 2. Güncel düzen

Tek çekirdek, tek iş parçacığı ve sekiz register kullanıyorum: $R0 \dots R7$. Her register sekiz hücreli sekiz satırdır. Bir hücre üç bittir. Bir satır 24 bit, bir register 192 bit, sekiz register birlikte 1536 bittir. Bu 192 bitin içinde sayının başka gösterimleri ve ona ait bilgiler de vardır. Register, 192 bitlik bir tamsayı tutmaz. Sayının kendisi ilk satırda, sekiz hanededir. Gölge satırlarının bir üssün sekizlik hanelerini mi yoksa merdiven katlarını mı tutacağı ve bunların birleşik kayda nasıl yerleşeceği açıktır. Gölge sistemi bir sayıyı hem $2^k \pm r$ gibi bir binom olarak tutabilir hem de çarpanlarına ayırabilir. Bu, tasarladığım işlemcilerden birinin özelliği ve taban aritmetiği de yapabiliyor. Resolver'ın biçimleri üzerinde FPGA'da deneyler yapılacak.

## 3. Bütün parçalar ve durumları

| Parça | Ne yapar | Durum |
|---|---|---|
| Hücre (xbit) | üç bitte 0..7 arası bir sekizlik hane | güncel |
| Register $R0..R7$ | sayının bütün kaydı, 192 bit | güncel |
| $rm$ | sayının sekiz hanesi | güncel |
| $rs1..rs4$ | gölge: sayaç biçiminde üssün sekizlik haneleri, merdiven biçiminde katlar ve kesilen haneler | birleşik kayıt açık, katlı merdivenin kodu açık |
| $rc$ | rough önbellek | güncel, geri okumadaki kesin rolü açık |
| $rpow$ | ölçek beyanı | güncel, hücre yerleşimi açık |
| $rtyp$ | tür ve durumlar | tür hücre 0'da, diğer hücreler açık |
| Resolver | yedi asalı sınar, üsleri sayar, artığı kat kat indirir | ilk aşama ve dişli modeli sınandı, katlı iniş kodda yok |
| Toplayıcı | toplama, çıkarma, karşılaştırma | güncel |
| Çarpma ve bölme | üs toplama ve çıkarma, kesir çifti | güncel, rough çarpım düz yolda |
| Karekök | üs yarılama, sembolik kök, hane hane kök | güncel |
| Kontrol | program sayacı, komut çözücü, saat | görevleri tanımlı, zamanlaması açık |
| ISA | işlem kodları, mod bitleri | Hunter taslağı, açıkları var |

## 4. Önceki tasarımlardaki parçalar

Aşağıdaki parçalar önceki tasarımlarda vardı. Güncel 192 bit düzende yerleri henüz belirlenmedi ya da başka bir alanın içinde düşünülüyor.

| Parça | Önceki tasarımda | Güncel 192 bit düzende |
|---|---|---|
| Durum alanı (FLAG) | sekiz durum biti ayrı bir alanda | durumlar $rtyp$ içinde düşünülüyor, hücre yerleşimi açık |
| VLINK | 137 bitlik register'da üç bitlik bağlantı alanı | yeri belirlenmedi |
| 137 bitlik register | önceki kayıt düzeni | 8 × 8 hücreli 192 bit düzen kullanılıyor |
| [Ayrı kontrolcü (PCCPU)](PCCPU/PCCPU.md) | komutları dağıtan ayrı birim | tek çekirdekli tasarımda yeri belirlenmedi |
| Taşma zinciri | komşu register'lara elde taşıma | bağlantısı ve son ucu açık |
| Küp, lider ve işçiler | birlikte çalışan birçok çekirdek | güncel tasarım tek çekirdekli, çok çekirdek açık |
| Sadeleştirme eleği | eş çarpan ve sıfır gibi sadeleşme fırsatlarını bulma | Temmuz tasarımında tanımlı, güncel yerleşimi açık |
| Açma kipleri, kesir ve karantina çifti | sembolik açılım ve istisnalar | Temmuz tasarımında tanımlı, güncel yerleşimi açık |
| Öğretim modeli (NAND, toplayıcı, IAR, IR, ACC, BUS, RAM) | komut yürütmesini görünür kılan model | ayrı bir öğretim modeli olarak duruyor |

## 5. Belgelerin biçimi

Her parça belgesi aynı düzeni izler: özet, tanımlar, mekanizma, programla hesaplanmış örnekler, kayıtlı ve yeniden çalıştırılmış ölçümler, sınırlar ve açık kalanlar. Çizimler siyah beyazdır ve örneklerdeki her değer çizimi üreten programın hesabıdır. Eski çalışmalardan gelen ölçümler "kayıtlı ölçüm" diye, yeniden çalıştırılan testler tarihiyle belirtilmiştir.
