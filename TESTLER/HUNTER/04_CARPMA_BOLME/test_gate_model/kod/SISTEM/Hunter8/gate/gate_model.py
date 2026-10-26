"""Hunter8: araya bit yerleştirme, ham katsayı ve taban okuma referans modeli."""

import json  # Örnekleri okunabilir metin olarak terminale verir; dosya açmaz.


def _integer(value, name, minimum=0):  # Sabit genişlik varsaymadan tamsayı doğrular.
    if type(value) is not int or value < minimum:  # bool, float ve negatifleri reddeder.
        raise ValueError(f"{name}: en az {minimum} olan bir tamsayı gerekir")  # Açık hata üretir.
    return value  # Doğrulanmış değeri döndürür.


def _coefficients(coeffs_lsb):  # Çağıranın dizisini değiştirmeden katsayıları alır.
    if not isinstance(coeffs_lsb, (list, tuple)) or not coeffs_lsb:  # Boş bant tanımsızdır.
        raise ValueError("Katsayılar boş olmayan list veya tuple olmalı")  # Biçimi denetler.
    return [_integer(c, "katsayı") for c in coeffs_lsb]  # Her katsayı negatif olmayan tamsayıdır.


def _bits(word, name, allow_empty=False):  # Yazı MSB solda; baştaki sıfırlar genişliği korur.
    minimum = 0 if allow_empty else 1  # Sadece eklenen blok boş olabilir.
    if not isinstance(word, str) or not minimum <= len(word) <= 8:  # Baytlık giriş sınırıdır.
        raise ValueError(f"{name}: {minimum}..8 bitlik yazı gerekir")  # Genişlik hatasını bildirir.
    if any(bit not in "01" for bit in word):  # İkilik dışındaki karakterleri kabul etmez.
        raise ValueError(f"{name}: yalnız 0 ve 1 kullanılabilir")  # Sessiz dönüşüm yapmaz.
    return word  # Sıfırları da içeren asıl yazıyı döndürür.


def evaluate(coeffs_lsb, base):  # Ham katsayı bandını seçilen tabanda sayıya okur.
    coeffs = _coefficients(coeffs_lsb)  # Dizinin ilk elemanı en düşük ağırlıktadır.
    _integer(base, "taban", 2)  # Unary, konumsal taban 1 gibi ele alınmaz.
    acc = 0  # Henüz hiçbir yüksek basamak okunmadı.
    for coefficient in reversed(coeffs):  # En yüksek katsayıdan en düşüğe ilerler.
        acc = acc * base + coefficient  # Horner: eski öneki bir basamak açar, yenisini ekler.
    return acc  # Bütün katsayıların ağırlıklı toplamını verir.


def append_prefix(prefix, digit, base):  # Sayısal öneke bir geçerli basamak ekler.
    _integer(prefix, "önek")  # Önek tek bir rakam değildir; 24 gibi bir değer olabilir.
    _integer(base, "taban", 2)  # Konumsal taban en az ikidir.
    _integer(digit, "son basamak")  # Son basamak negatif olamaz.
    if digit >= base:  # Tek hanelik son parçanın tabana sığması gerekir.
        raise ValueError("Son basamak tabandan küçük olmalı")  # Ham katsayı ile rakamı ayırır.
    return prefix * base + digit  # [24]1,2 önerisinin değeri 49 olur.


def insert_bits(word, payload, cut):  # Sağda cut bitini tutar, sol parçanın önünü açar.
    _bits(word, "giriş")  # Bir ila sekiz bit; yazının genişliği açık kalır.
    _bits(payload, "eklenen blok", allow_empty=True)  # Sıfır ila sekiz yeni bit eklenir.
    _integer(cut, "kesim")  # Kesim en düşük bitten sayılır.
    if cut > len(word):  # Kaynağın dışına kesim yapılamaz.
        raise ValueError("Kesim giriş genişliğini aşamaz")  # Sonuç üretmeden reddeder.
    value = int(word, 2)  # Kaynağın sayısal değerini alır.
    right = value & ((1 << cut) - 1)  # Sağdaki cut bit yerinde tutulur; cut=0 maskesi sıfırdır.
    left = value >> cut  # Kalan üst parçayı ayrı değere indirir.
    payload_width = len(payload)  # 00 değeri sıfır olsa da iki yeni yer açar.
    inserted = int(payload, 2) if payload else 0  # Boş blok sıfır genişlikte etkisizdir.
    result = (((left << payload_width) | inserted) << cut) | right  # Ayrık alanları birleştirir.
    result_word = format(result, f"0{len(word) + payload_width}b")  # Baştaki sıfırları korur.
    return dict(word=result_word, value=result, left=left, right=right, cut=cut,
                payload_width=payload_width)  # En fazla 16 bit döner; byte'a sessizce kırpmaz.


def normalize(coeffs_lsb, base):  # Geniş katsayıları geçerli basamaklara carry ile indirger.
    coeffs = _coefficients(coeffs_lsb)  # Giriş dizisini kopyalar; katsayılar tabanı aşabilir.
    _integer(base, "taban", 2)  # Bölüm ve kalan için geçerli taban gerekir.
    index, carry = 0, 0  # INDEX işlenen sütun sayısı; başlangıçta gelen elde yoktur.
    digits, steps = [], []  # Çıkış önce boştur; adım kayıtları ayrı öğretim verisidir.
    while index < len(coeffs) or carry:  # Katsayılar ve son carry tükenince biter.
        coefficient = coeffs[index] if index < len(coeffs) else 0  # Son elde için sıfır sütunu açar.
        total = coefficient + carry  # Bu sütundaki bütün katkıları toplar.
        next_carry, digit = divmod(total, base)  # TOTAL = digit + base * next_carry.
        steps.append(dict(index=index, coefficient=coefficient, carry_in=carry,
                          total=total, digit=digit, carry_out=next_carry))  # Önce ve sonra görünür.
        digits.append(digit)  # Bu basamak artık değişmez; en düşük basamak önce yazılır.
        carry = next_carry  # Çoklu katkılarda bu değer 1'den büyük olabilir.
        index += 1  # Bir sonraki taban ağırlığına geçer; tek başına CPU cycle değildir.
    while len(digits) > 1 and digits[-1] == 0:  # Gereksiz yüksek sıfırları sadece sonuç yazısından atar.
        digits.pop()  # Sıfırın temsili daima [0] olarak kalır; STEP izi korunur.
    return dict(digits_lsb=digits, value=evaluate(digits, base), steps=steps)  # Tam değer taşma olmadan döner.


def square_bits(word):  # En fazla bir baytın karesini ham katsayılarla kurar.
    _bits(word, "giriş")  # MSB solda yazılmış ve genişliği belli ikilik girişi doğrular.
    bits = [int(bit) for bit in reversed(word)]  # Katsayı indeksini bit ağırlığıyla eşler.
    coefficients = [0] * (2 * len(bits) - 1)  # i+j sütunları 0..2m-2 arasında olabilir.
    products = 0  # Mantıksal bit çarpımı sayacı; donanım tick sayacı değildir.
    for i, a in enumerate(bits):  # İlk çarpanın m bitini sırayla seçer.
        for j, b in enumerate(bits):  # Her seçilen bit için ikinci çarpanın m bitini dolaşır.
            coefficients[i + j] += a * b  # Aynı ağırlığa gelen katkıları aynı sütunda toplar.
            products += 1  # Sıfır katkılar dahil toplam m*m çift ziyaret edilir.
    result = normalize(coefficients, 2)  # Ham bant ikilik basamaklara carry ile çevrilir.
    result.update(coefficients_lsb=coefficients, bit_pair_products=products)  # Oluşum maliyetini ayrı gösterir.
    return result  # En büyük sonuç 255²=65025, yani 16 bite sığar.


def demo():  # Yalnız stdout üretir; örnek çalıştırmak hiçbir dosya değiştirmez.
    examples = dict(insert_11=insert_bits("11", "00", 1), square_101=square_bits("101"),
                    square_111=square_bits("111"), prefix_48=append_prefix(24, 0, 2),
                    prefix_49=append_prefix(24, 1, 2),
                    same_pattern={str(b): evaluate([1, 2, 1], b) for b in (2, 3, 4)})  # Tabanı değişen aynı banttır.
    print(json.dumps(examples, ensure_ascii=False, indent=2))  # STEP alanlarını da okunabilir gösterir.


if __name__ == "__main__":  # İçe aktarma sırasında örnekler kendiliğinden çalışmaz.
    demo()  # Terminalden doğrudan çağrıda küçük deneyleri çalıştırır.
