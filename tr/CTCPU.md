# CTCPU

CTCPU, sayıları iki gösterimle işlemek için tasarladığım bir işlemci. Sayının normal basamaklı yazımını ve gölge dediğim ikinci gösterimini kullanıyor. Hunter bu çalışmanın devamı.

## Renklerle başla

Normal bir işlemci bitlerle çalışır: 0 ya da 1. CTCPU'da en küçük birim daha büyük: **xbit**, yani üç bit, yani sekiz değer. Bu sekiz değeri sekiz renkle gösteriyorum, çünkü üç ışık kanalı (kırmızı, yeşil, mavi) karışınca sekiz renk verir. Her rengin bir numarası ve bir harfi var.

| Sayı | Renk       | Harf | Üç bit |
|------|------------|------|--------|
| 0    | Siyah      | K    | 000    |
| 1    | Kırmızı    | R    | 001    |
| 2    | Yeşil      | G    | 010    |
| 3    | Sarı       | Y    | 011    |
| 4    | Mavi       | B    | 100    |
| 5    | Macenta    | M    | 101    |
| 6    | Camgöbeği  | C    | 110    |
| 7    | Beyaz      | W    | 111    |

Renkler ışık gibi karışır: kırmızı (1) + yeşil (2) = sarı (3), kırmızı (1) + mavi (4) = macenta (5), yeşil (2) + mavi (4) = camgöbeği (6), kırmızı + yeşil + mavi = beyaz (7).

Bir sayı, bu renklerden oluşan bir dizidir. 137 sekizlik tabanda 211 yazılır, renkle G R R olur. Mersenne sayısı 31 sekizlikte 37, renkle Y W. 127 sekizlikte 177, renkle R W W. Günlükteki 1, 3, 7 örüntülerini renk olarak görebilmemin sebebi bu.

## Sayılar nasıl tutuluyor?

Bir xbit üç bitten oluşuyor ve bir sekizlik haneyi gösteriyor. Sekiz xbit, 24 bitlik bir değer tutuyor. Renkler bu haneleri görselleştirmek için kullanılıyor.

Normal gösterimde sayı basamaklarıyla tutuluyor. Gölge gösteriminde seçilmiş asal çarpanların üsleri ve geriye kalan çarpan saklanıyor.

## Parçalar

| Parça                 | Ne yapıyor?                                                                                            |
|-----------------------|--------------------------------------------------------------------------------------------------------|
| Kontrol birimi        | Sıradaki komutu seçiyor ve parçaların hangi işi yapacağını yönetiyor.                                  |
| Register’lar          | İşlenen sayıları, ara sonuçları ve kontrol bilgilerini tutuyor.                                        |
| ALU                   | Toplama, çıkarma, karşılaştırma ve diğer aritmetik işlemleri yürütüyor.                                |
| Resolver              | Sayıyı gölge gösterimine hazırlıyor. Seçilmiş asal çarpanların üslerini ve kalan çarpanı çıkarıyor.    |
| Gölge alanları        | Resolver’ın ürettiği gösterimi saklıyor. Uygun çarpımsal işlemler bu gösterim üzerinden yapılabiliyor. |
| Bayraklar             | Sıfır veya taşma gibi durumları kaydediyor.                                                            |
| Komutlar ve atlamalar | Yapılacak işlemi belirliyor. Atlama komutları programın nereden devam edeceğini değiştiriyor.          |

ISA, bu komutların biçimini ve ne yapacağını tanımlayan sözleşme.

## Parçalar nasıl birlikte çalışıyor?

Başlangıçta program ve üzerinde çalışılacak değerler hazır bulunuyor. Çalıştırma başlayınca kontrol birimi sıradaki komutu alıyor. Gerekli değerler register’lardan okunuyor ve ilgili birime gönderiliyor.

Toplama gibi işlemler normal gösterimi kullanıyor. Bir işlem gölgeye ihtiyaç duyuyorsa ve o gölge henüz hazır değilse resolver onu oluşturuyor. Sonuç register’a yazılıyor. İlgili bayraklar güncelleniyor.

Program bir atlama komutuyla önceki bir adıma dönebiliyor. Döngünün ne zaman biteceğini programdaki koşul veya sayaç belirliyor. Durma komutuna ulaşıldığında yürütme bitiyor.

Bu sayfa tasarımın genel akışını anlatıyor. Parçaların kesin bağlantıları ve komut davranışları kendi belgelerinde ayrıntılandırılacak.

[Parça açıklamaları](CTCPU_PARCALAR/README.md) · [Resolver’ın çalışma örneği](CTCPU_PARCALAR/Resolver.md) · [English](../CTCPU.md)
