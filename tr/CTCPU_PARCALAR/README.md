# CTCPU parçaları

CTCPU, sekizlik haneler ve sayının iki gösterimi üzerine kurulan bir işlemci tasarımıdır. Pozisyonel gösterim, alışılmış toplama ve çıkarma işlemleri için kullanılır. Gölge gösterimi ise seçilmiş asal üslerini ve kalan çarpanı tutar. Böylece uygun çarpımsal işlemler üsler üzerinden yürütülebilir.

CTCPU, Hunter olarak devam eden çalışmanın önceki adıdır. Bu sayfalar parçaları ve görevlerini anlatır. Arşivdeki bütün bileşenlerin aynı sürümde, birlikte sınanmış tek bir makine oluşturduğu anlamına gelmez.

## Sayı ve gösterim

Bir xbit, bir sekizlik hane olarak okunan üç ikilik bittir. Sekiz xbit, 24 bitlik işaretsiz bir değer tutar. Renk bu hanenin etiketi olabilir ama üç bitin ötesinde ek bilgi taşımaz.

Örneğin 360 = 2³ × 3² × 5. İlk gölge ayrıştırması, [2, 3, 5, 7, 11, 13, 17] asalları için [3, 2, 1, 0, 0, 0, 0] üslerini ve 1 artığını içerir. Bu ayrıştırmayı [resolver](Resolver.md) üretir. Sonraki gölge katmanları bu giriş örneğinin dışında kalır.

## Parçalar ve görevleri

| Parça | Görevi | Buradaki kapsam |
|---|---|---|
| Kontrol ve register’lar | Değerleri tutmak, komutları seçmek ve veri akışını yönetmek | Genel tanıtım |
| ISA | Komut biçimlerini ve davranışlarını tanımlamak | Araştırma günlüğünde özet |
| ALU | Aritmetik ve karşılaştırma yapmak | Genel tanıtım |
| Gölge | Sayının alternatif gösterimini tutmak | İlk katman örneği |
| Resolver | Pozitif pozisyonel tamsayıyı seçilmiş asal üslerine ve kalan çarpana ayırmak | [Açıklama ve adım adım örnek](Resolver.md) |
| Bayraklar | Kontrolün kullanacağı durumları işaretlemek | Genel tanıtım |

Aritmetik bedelsiz değildir. Üs işlemleri, kalan çarpanlar, gösterim dönüşümü ve taşma maliyet taşır. Temsil edilen sayıların toplamı tanımlıdır ama genel olarak asal üslerini toplayarak hesaplanamaz.

## Yürütme mantığı

Başlangıçta register’da pozisyonel değer bulunur. Bir işlem, henüz geçerli gölgesi olmayan bu sayının gölgesine ihtiyaç duyduğunda kontrol birimi dönüşüm ister. Resolver değeri okur, seçilmiş asal kuvvetlerini ayırır ve üslerle artığı döndürür. İşlem, ihtiyaç duyduğu gösterimi kullanır. Pozisyonel değer değiştirildiğinde ilgili gölge de güncellenmeli veya geçersiz sayılmalıdır.

Tembel dönüşüm kuralı budur: bir sayıyı yüklemek, tek başına gölge kurmayı gerektirmez. Kesin zamanlama, register arayüzü ve maliyet, uygulama eklendiğinde onunla karşılaştırılmalıdır.

## Yayının kapsamı

Bu klasörde şimdilik açıklamalar var. Emülatör kaynakları veya tam ISA sözleşmesi burada değil. Assembly dili, assembler, derleyici ve emülatör daha sonra aynı repoya eklenebilir. Burada ölçülmüş bir donanım hızı veya enerji kazancı iddiası yok.

Anlatım, arşivdeki CTCPU sistem tanımına ve parça kartlarına dayanır. Repodaki 22 test, günlükteki matematiksel iddiaları sınar. Resolver’ın veya CPU arayüzünün tamamını sınamaz.

[Araştırma günlüğü](../YOL.md) · [English](../../CTCPU_PARTS/README.md) · [Repo tanıtımı](../README.md)
