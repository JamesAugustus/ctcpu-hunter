# Resolver

Resolver, pozitif bir tamsayının ilk gölge ayrıştırmasını oluşturur. Sabit 2, 3, 5, 7, 11, 13 ve 17 asallarının kuvvetlerini ayırır, geriye kalan çarpanı saklar. Bu artığın asal olması gerekmez.

Burada anlatılan girdi aralığı 1 ≤ N ≤ 2²⁴ − 1. Örneklerde tabanı belirtilmeyen sayılar onluktur. Çıktı şu eşitliği sağlar:

```text
N = 2^e2 × 3^e3 × 5^e5 × 7^e7 × 11^e11 × 13^e13 × 17^e17 × R
```

## Yürütme mantığı

Aşağıdaki akış aritmetiğin basit, sıralı anlatımıdır. Adımlar ölçülmüş donanım çevrimleri veya kesin register yerleşimi değildir.

- `N` değişmeden saklanan girdidir.
- `V` işlenecek kalan değerdir. Başlangıçta N’ye eşittir.
- `E[0..6]` yedi asalın üslerini tutar. Başlangıçta hepsi sıfırdır.
- `i`, `P = [2, 3, 5, 7, 11, 13, 17]` listesinden asalı seçer. Başlangıç değeri 0’dır.
- İşlem bittiğinde V, `R` çıktısına yazılır.

```text
gölge isteği → N'yi doğrula → V=N, E=0, i=0
                             ↓
                   V=1 veya i=7? ──evet──→ R=V, E ve R'yi döndür
                             │ hayır
                             ↓
                   V, P[i]'ye bölünüyor mu?
                      │ evet              │ hayır
                      ↓                   ↓
                V=V/P[i], E[i]++         i++
                      └────── durma kontrolüne dön ──────┘
```

N = 360 için:

| Adım | Önce | İşlem | Sonra |
|---|---|---|---|
| Başlangıç | — | İlk değerleri yerleştir | V=360, E=0, i=0 |
| 1 | V=360, asal=2 | Böl, e2’yi artır | V=180, e2=1 |
| 2 | V=180, asal=2 | Böl, e2’yi artır | V=90, e2=2 |
| 3 | V=90, asal=2 | Böl, e2’yi artır | V=45, e2=3 |
| 4 | V=45, asal=2 | Bölünmüyor, ilerle | i=1, asal=3 |
| 5 | V=45, asal=3 | Böl, e3’ü artır | V=15, e3=1 |
| 6 | V=15, asal=3 | Böl, e3’ü artır | V=5, e3=2 |
| 7 | V=5, asal=3 | Bölünmüyor, ilerle | i=2, asal=5 |
| 8 | V=5, asal=5 | Böl, e5’i artır | V=1, e5=1 |
| Bitiş | V=1 | Dur, artığı yaz | E=[3,2,1,0,0,0,0], R=1 |

Bu döngüde 8 bölünebilirlik kontrolü, 6 tam bölme, 6 üs artırma ve 2 asal indeksi artırma vardır. Durma koşulu 9 kez değerlendirilir. Fiziksel uygulama farklı bir zamanlama kullanabilir.

Döngü değişmezi `N = V × product(P[j]^E[j])` eşitliğidir. Başarılı bölme V’den bir asal çarpanı çıkarır ve E’ye ekler. Böylece N korunur. Başarılı bölmede V küçülür, diğer durumda i artar. İşlem bu yüzden sonlu sayıda adımda biter. Bittiğinde R, seçilmiş yedi asaldan hiçbirini çarpan olarak içermez.

## Sekizlik hane akıtma

Bölünebilirlik eleği, sekizlik haneleri soldan sağa okuyabilir. Her asal kanalının kalanı sıfırdan başlar ve şöyle güncellenir:

```text
kalan = (8 × kalan + hane) mod asal
```

Hane sayacı okunacak haneleri sayar. 24 bitlik biçimde, baştaki sıfırlar dahil sekiz sekizlik hane vardır. Her hanede bir tarama adımı yapılır, sekiz adımdan sonra elek durur. Kalan, o ana kadar okunan önekin ilgili asala göre kalanıdır. Yedi kanal paralel hesaplanabilir.

Son kalanın sıfır olması bölünebilirliği gösterir. Tek başına bölümü üretmez veya asalın kaç kez bulunduğunu saymaz. Bölüm çıkarma ve üs sayma ayrı işlerdir. Tam açılmış bir elek ile sıralı taramanın alan ve zamanlama maliyetleri farklıdır.

## Sınırlar ve maliyet

- N=1 için bütün üsler sıfır, R=1 olur.
- N=59 için bütün üsler sıfır, R=59 olur.
- N=437 için R=437=19×23 olur. Artık, asallık belgesi değildir.
- N=2124 için e2=2, e3=2 ve R=59 olur.
- Bu model sıfırı reddeder. Sıfırı tekrar tekrar bölmek bitmeyen döngüye yol açar.
- Negatif, kesirli ve daha geniş girdiler ayrı arayüz gerektirir. Sessizce bit kesilmemelidir.
- Üs alanları desteklenen aralığı tutabilmelidir. Örneğin N=2²³ için e2=23 gerekir. Bu sayfa paketlenmiş gölge kodlamasını tanımlamaz.

Arşivdeki tasarım, paylaşımlı resolver birimleri ve çarpımsal işlem geçerli bir gölge istediğinde tembel dönüşüm kullanır. Yerleşim, iş hacmi ve kapı maliyeti uygulama üzerinden sınanmalıdır. Bu sayfada yeni donanım ölçümü yoktur. Günlük testleri, resolver’ın bütününü sınayan bir test paketi değildir.

[Parçalar](README.md) · [English](../../CTCPU_PARTS/Resolver.md) · [Repo tanıtımı](../README.md)
