# Mersenne kalanını hücre akışıyla üretme

## Ne sınar

Basamakların kaydırma konumunu üs mod p ile azaltarak Mersenne kalanını akış halinde hesaplar. Sonucu tam sayı gövdesinin doğrudan mod hesabıyla karşılaştırıp akümülatör genişliği ve katlama sayısını kaydeder.

## Nasıl çalışır

p=13,31,61,127,521 ve hücre genişliği 3,8,16 için 2,3,4,8 satırlı yapay tablolar kurulur. Haneler yılan sırasıyla okunurken Horner adımı ve Mersenne katlaması uygulanır. Tam gövdeden hesaplanan value%(2^p-1) aynı kalanla sonuçlanmalıdır. Eşitsizlik assert hatasıdır. Akümülatörün en büyük bit uzunluğu ve katlama sayısı ayrıca ölçülür.

## Neden önemli

DEX araştırmalarında temsil, kalan ve sonlu örnekler üzerinden kurulan iddialara aittir.

## Çalıştırma

```sh
cd TESTLER/HUNTER/11_DEX_ARASTIRMALARI/hunter_stream026_9dd5af2c
python3 stream026.py
```

Gerekenler: Python 3.

## Kaynak

Kaynak: [stream026.py](../../../../../TESTLER/HUNTER/11_DEX_ARASTIRMALARI/hunter_stream026_9dd5af2c/stream026.py)

Arşivdeki satır sayısı: 38.
