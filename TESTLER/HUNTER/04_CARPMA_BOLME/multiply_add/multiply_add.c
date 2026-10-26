// 8, 16 ve 24 bit işaretsiz çarpımı koşullu toplama ve kaydırmayla kuran C11 öğretim referansı.
#include <stdint.h> // uint32_t ve uint64_t tam genişlikli işaretsiz türlerini ve UINT sabitlerini bildirir.
#include <stdbool.h> // bool, true ve false ile başarı durumunu açıkça yazmayı sağlar.
#include <stdio.h> // Standart giriş/çıkış bildirimleri: stdin giriş, stdout çıktı, stderr hata akışı; printf ve fprintf de burada bildirilir.
#include <inttypes.h> // PRIu32 ve PRIu64, tam genişlikli işaretsiz tamsayılar için taşınabilir printf biçimlerini sağlar.

// Girişler W bit, tam sonuç en çok 2W bittir; W en fazla 24 olduğundan uint64_t içinde en çok 48 bit kullanılır.
// Durum: ACC kısmi sonuç, M kaydırılan A, Q kalan B, COUNT işlenecek bit sayısıdır.
// Başlangıç ACC=0, M=A, Q=B, COUNT=W; değişmez ACC + M×Q = A×B biçimindedir.
// Her STEP bir Q biti tüketir; Q erken sıfır olsa bile COUNT sıfıra ulaşana kadar W STEP tamamlanır.
// Son STEP'teki M kaydırması sonucu etkilemez ve M<2^48 olduğundan bu genişlikte güvenlidir.
// += C düzeyinde toplama sözleşmesidir; bu örnek ripple devresi veya modern MUL komutunun iç işleyişi ya da hız ölçümü değildir.
bool multiply_add(uint32_t a, uint32_t b, unsigned width, uint64_t *out) { // a ve b girdilerinden tam sonucu out adresine yazar; başarıyı bool ile döndürür.
    if (out == NULL || (width != 8u && width != 16u && width != 24u)) { // Geçersiz adresi veya desteklenmeyen genişliği herhangi bir kaydırma yapmadan reddeder.
        return false; // Hata durumunda çıkış adresine yazmadan çağırana döner.
    } // Genişlik ve adres kontrolü burada biter.
    const uint32_t limit = (UINT32_C(1) << width) - UINT32_C(1); // W bit içinde taşınabilecek en büyük işaretsiz değeri üretir.
    if (a > limit || b > limit) { // Her iki girdinin de seçilen W bitlik aralığa sığmasını ister.
        return false; // Aralık hatasında çağıranın önceki çıkış değerini korur.
    } // Girdi aralık denetimi burada biter.
    uint64_t acc = UINT64_C(0); // Başlangıçta hiçbir seçili kısmi toplam yoktur.
    uint64_t m = a; // A'yı 64 bite genişletir; her STEP'te sıradaki basamağın ağırlığına kaydırılır.
    uint32_t q = b; // B'nin henüz işlenmemiş bitleri bu register benzetiminde tutulur.
    unsigned count = width; // W bitlik B'nin bütün bitlerini saymak için sayaç W ile başlar.
    while (count != 0u) { // W kez RUN gövdesi ve sonunda bir kez bitiş kontrolü yapılır.
        if ((q & UINT32_C(1)) != 0u) { // Q'nun en sağdaki biti birse o basamağın ağırlığı sonuca katılacaktır.
            acc += m; // Seçilmiş ağırlığı ACC'ye ekler; toplam sayısı B'nin bir bitlerinin sayısıdır.
        } // Sıfır bit için toplama atlanır, diğer STEP işleri yine yapılır.
        m <<= 1u; // Sonraki basamak için ağırlığı iki katına çıkaran bir sola kaydırma yapar.
        q >>= 1u; // İşlenen en sağ biti atar; sıradaki bit karar yerine gelir.
        --count; // Bir giriş biti işlendiği için kalan bit sayısını tam bir azaltır.
    } // COUNT sıfırdır; W bit tüketildiği için Q da sıfırdır ve değişmez ACC'nin sonucu verdiğini gösterir.
    *out = acc; // Doğrulanmış tam sonucu çağıranın gösterdiği uint64_t nesnesine yazar.
    return true; // İşlemin geçerli girdilerle tamamlandığını bildirir.
} // Çarpma çekirdeği biter; burada çarpma işleci kullanılmaz.

static uint32_t next_sample(uint32_t *state) { // Sabit tohumdan tekrarlanabilir örnekler üretir; bu test üreteci kriptografik değildir.
    uint32_t x = *state; // Önceki 32 bitlik test üreteci durumunu yerel değişkene alır.
    x ^= x << 13u; // Sola kaydırılmış bitleri XOR ile karıştırır; işaretsiz taşma modülerdir.
    x ^= x >> 17u; // Sağa kaydırılmış bitleri XOR ile karıştırır.
    x ^= x << 5u; // Son XOR ve kaydırma karışımını uygular.
    *state = x; // Yeni durumu sonraki örnek için saklar.
    return x; // Üretilen 32 bitlik deterministik örneği döndürür.
} // Test örneği üreteci biter.

static bool check_case(uint32_t a, uint32_t b, unsigned width, uint64_t *cases) { // Bir geçerli çağrıyı bağımsız aritmetik beklentiyle karşılaştırır.
    uint64_t actual = UINT64_MAX; // Fonksiyonun yazdığını görebilmek için sonuç aralığının dışında bir başlangıç değeri seçer.
    const uint64_t expected = (uint64_t)a * (uint64_t)b; // Kaynaktaki tek aritmetik çarpma bağımsız test oracle'ıdır; her iki operand önce 64 bite genişletilir.
    const bool ok = multiply_add(a, b, width, &actual); // &actual sonuç nesnesinin adresidir; çekirdek bu adrese tam sonucu yazmalıdır.
    ++*cases; // Bu geçerli test çağrısını sayar; örnek kümeleri arasında tekrarlar olabilir.
    if (!ok || actual != expected) { // Başarı bildirimi veya tam sayısal sonuç yanlışsa hata üretir.
        fprintf(stderr, "FAIL width=%u a=%" PRIu32 " b=%" PRIu32 " expected=%" PRIu64 " actual=%" PRIu64 "\n", width, a, b, expected, actual); // %u unsigned genişliği, PRIu biçimleri tam genişlikli değerleri, \n satır sonunu yazar.
        return false; // İlk yanlış örnekte testi başarısız bildirir.
    } // Sonuç karşılaştırması biter.
    return true; // Bu örnekte tam sonuç ve başarı durumu doğrudur.
} // Geçerli örnek kontrolü biter.

static bool check_reject(uint32_t a, uint32_t b, unsigned width, uint64_t *cases) { // Geçersiz çağrının çıkış nesnesine dokunmamasını sınar.
    uint64_t actual = UINT64_MAX; // Değişmeden kalması gereken izleme değerini kurar.
    const bool ok = multiply_add(a, b, width, &actual); // Geçersiz girdileri gerçek çekirdeğe gönderir.
    ++*cases; // Reddedilmesi beklenen çağrı sayısını artırır.
    if (ok || actual != UINT64_MAX) { // Başarı dönmesi veya çıkışın değişmesi sözleşme ihlalidir.
        fprintf(stderr, "FAIL rejection width=%u a=%" PRIu32 " b=%" PRIu32 "\n", width, a, b); // Hatalı reddetmenin genişliğini ve girdilerini standart hata akışına yazar.
        return false; // Bu geçersiz çağrının doğru ele alınmadığını bildirir.
    } // Çıkış koruma denetimi biter.
    return true; // Çağrı reddedilmiş ve önceki çıkış değeri korunmuştur.
} // Geçersiz örnek kontrolü biter.

int main(void) { // Parametresiz test programının giriş noktasıdır; sıfır dönüş kodu tüm kontrollerin geçtiğini bildirir.
    uint64_t byte_cases = 0u, boundary_cases = 0u, sample_cases = 0u, rejected_cases = 0u; // Dört kapsamın gerçek çağrı sayılarını ayrı tutar.
    for (uint32_t a = 0u; a < 256u; ++a) { // A'nın bütün 256 bayt değerini sırayla seçer.
        for (uint32_t b = 0u; b < 256u; ++b) { // Her A için B'nin bütün 256 değerini sınar: toplam 65.536 çift.
            if (!check_case(a, b, 8u, &byte_cases)) { // 8 bitlik çarpımı bağımsız uint64_t sonuçla karşılaştırır.
                return 1; // İlk başarısız karşılaştırmada hata koduyla çıkar.
            } // Bu bayt çiftinin kontrolü biter.
        } // Bir A için bütün B değerleri tüketilmiştir.
    } // Eksiksiz bayt çifti taraması biter.
    const unsigned wide_widths[] = {16u, 24u}; // Daha geniş girdiler için sınır ve örnek taraması yapılacak iki genişliği tutar.
    uint32_t seed = UINT32_C(0xA5A5F00D); // Tekrarlanabilir xorshift örnek dizisinin sıfır olmayan sabit başlangıç durumudur.
    for (unsigned wi = 0u; wi < 2u; ++wi) { // 16 bit ve 24 bit kapsamlarını birer kez kurar.
        const unsigned width = wide_widths[wi]; // Bu turda test edilecek W genişliğini seçer.
        const uint32_t limit = (UINT32_C(1) << width) - UINT32_C(1); // Bu genişliğin en büyük geçerli girdisini hesaplar.
        const uint32_t edges[] = {0u, 1u, 2u, 3u, limit >> 1u, UINT32_C(1) << (width - 1u), limit - 1u, limit}; // Sıfır, bir, küçük sayılar, üst bit sınırı ve en büyük iki değeri seçer.
        for (unsigned ai = 0u; ai < 8u; ++ai) { // Sekiz A sınır değerini gezer.
            for (unsigned bi = 0u; bi < 8u; ++bi) { // Sekiz B sınır değerini gezer; genişlik başına 64 çift üretir.
                if (!check_case(edges[ai], edges[bi], width, &boundary_cases)) { // Sınır çarpımının bütün 2W bitini doğrular.
                    return 1; // Hatalı sınır örneğinde programı başarısız bitirir.
                } // Bu sınır çiftinin kontrolü biter.
            } // Bir A sınırı için B sınırları bitmiştir.
        } // Bu genişliğin 64 sınır çifti tamamlanmıştır.
        for (unsigned i = 0u; i < 2000u; ++i) { // Genişlik başına tam 2.000 deterministik örnek çağrısı yapar.
            const uint32_t a = next_sample(&seed) & limit; // Üreteç değerini W bitlik geçerli A aralığına maskeler.
            const uint32_t b = next_sample(&seed) & limit; // Sonraki üreteç değerini W bitlik geçerli B aralığına maskeler.
            if (!check_case(a, b, width, &sample_cases)) { // Örnek çiftinin sonucunu bağımsız çarpma ile karşılaştırır.
                return 1; // İlk yanlış örnekte hata koduyla çıkar.
            } // Bu deterministik örneğin kontrolü biter.
        } // Bu genişliğin örnek çağrıları tamamlanmıştır.
    } // Her iki genişliğin sınır ve örnek taraması biter.
    const unsigned valid_widths[] = {8u, 16u, 24u}; // Aralık ve NULL çıkış hatalarını üç geçerli genişlikte de denetler.
    for (unsigned wi = 0u; wi < 3u; ++wi) { // Üç genişliğin her biri için beş geçersiz çağrı hazırlar.
        const unsigned width = valid_widths[wi]; // Bu turun geçerli genişliğini alır.
        const uint32_t limit = (UINT32_C(1) << width) - UINT32_C(1); // Aralığın hemen dışındaki değeri kurmak için üst sınırı hesaplar.
        if (!check_reject(limit + 1u, 0u, width, &rejected_cases) || !check_reject(0u, limit + 1u, width, &rejected_cases)) { // A ve B aralık hatalarını ayrı çağrılarla sınar; diğer operand sıfır olsa da hata reddedilmelidir.
            return 1; // Herhangi bir aralık hatası kabul edildiyse program başarısızdır.
        } // Aralığın hemen üstündeki iki kontrol biter.
        if (!check_reject((uint32_t)-1, 1u, width, &rejected_cases) || !check_reject(1u, (uint32_t)-2, width, &rejected_cases)) { // Bu iki negatif sabit unsigned dönüşümden sonra büyük değer olur; W sınırını aştıkları için reddedilmelidir.
            return 1; // Negatif kaynaklı bu iki aralık dışı değer kabul edilirse hata bildirir.
        } // Dönüşmüş değer kontrolleri biter; unsigned API önceki işaret bilgisini genel olarak saklamaz.
        ++rejected_cases; // Bir sonraki NULL çıkış çağrısını geçersiz test sayısına ekler.
        if (multiply_add(0u, 0u, width, NULL)) { // Geçerli sayılarla bile boş sonuç adresinin reddedilmesini ister.
            fprintf(stderr, "FAIL null output width=%u\n", width); // Hatalı NULL kabulünün genişliğini hata akışına yazar.
            return 1; // Geçersiz çıkış adresi kabul edildiği için başarısız döner.
        } // NULL çıkış denetimi biter.
    } // Üç genişlikte toplam 15 geçersiz çağrı tamamlanmıştır.
    const unsigned invalid_widths[] = {0u, 1u, 7u, 9u, 15u, 17u, 23u, 25u, 31u, 32u, 64u}; // Desteklenen genişliklerin altı, arası ve kaydırma açısından tehlikeli üst değerleri seçer.
    for (unsigned i = 0u; i < sizeof invalid_widths / sizeof invalid_widths[0]; ++i) { // Dizi eleman sayısı kadar ilerler; sizeof nesnenin bayt boyutunu verir.
        if (!check_reject(1u, 1u, invalid_widths[i], &rejected_cases)) { // Geçersiz genişliğin hiçbir çıkış yazmadan reddedilmesini denetler.
            return 1; // Genişlik sözleşmesi bozulursa test programını durdurur.
        } // Bu geçersiz genişlik kontrolü biter.
    } // On bir geçersiz genişlik denetimi tamamlanmıştır.
    const uint64_t valid_cases = byte_cases + boundary_cases + sample_cases; // Geçerli çağrı kapsamlarını toplar; bu sayı benzersiz çift sayısı iddiası değildir.
    printf("PASS C11 multiply_add widths=8/16/24 byte_pairs=%" PRIu64 " wide_boundary_pairs=%" PRIu64 " deterministic_pairs=%" PRIu64 " valid_calls=%" PRIu64 " rejected_calls=%" PRIu64 " total_calls=%" PRIu64 "\n", byte_cases, boundary_cases, sample_cases, valid_cases, rejected_cases, valid_cases + rejected_cases); // PRIu64 sayaçları taşınabilir ondalık biçimde, \n son satır sonuyla stdout'a yazar.
    return 0; // Bütün geçerli sonuçlar ve hata sözleşmeleri doğrulanmıştır.
} // Bağımsız test programı biter.
