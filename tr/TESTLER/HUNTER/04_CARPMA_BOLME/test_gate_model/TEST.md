# Python katsayı ve çarpım denetimi

## Ne sınar

Seçili dört yöntem 256 byte değerinin karesini ve ham çarpım katsayılarını bağımsız ağırlıklı toplamla karşılaştırır. Çok operandlı elde zincirinde her adımın değer korunumunu ve geçersiz aritmetik türlerinin reddini sınar.

## Nasıl çalışır

Komuttaki dört GateModelTests yöntemi sırayla çağrılır. 0..255 değerlerinin kareleri 64 bit çifti çarpımından oluşan 15 ham katsayıyla kurulur ve değer² ile karşılaştırılır. 2..7 tabanlarında çok operandlı elde adımlarının ağırlıklı toplamı korunmalıdır. Geçersiz tür, taban ve basamak kabul edilirse veya katsayı normalizasyonu değeri değiştirirse unittest hatası oluşur.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/test_gate_model/kod/SISTEM/Hunter8/gate
python3 test_gate_model.py GateModelTests.test_all_256_byte_squares_and_raw_coefficients GateModelTests.test_two_square_traces_and_multioperand_carry GateModelTests.test_raw_coefficients_keep_value_at_every_normalization_step GateModelTests.test_invalid_arithmetic_types_bases_and_digits_raise_value_error
```

Gerekenler: Python 3.

kod/ dizini kaynakta kullanılan göreli hiyerarşiyi korur.

## Kaynak

Kaynak: [test_gate_model.py](../../../../../TESTLER/HUNTER/04_CARPMA_BOLME/test_gate_model/kod/SISTEM/Hunter8/gate/test_gate_model.py)

Arşivdeki satır sayısı: 197.
