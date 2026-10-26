#!/usr/bin/env python3
"""Yayın parçalarında kullanılan sayıları bağımsız kesin aritmetikle denetler."""
from decimal import Decimal, localcontext
from fractions import Fraction
from math import prod, isqrt
from pathlib import Path
import json
import time

started = time.monotonic()
Q = (2, 3, 5, 7, 11, 13, 17)
checks = 0
def check(condition):
    global checks
    checks += 1
    assert condition, checks

def factors(n):
    es = []
    for q in Q:
        e = 0
        while n % q == 0:
            e += 1
            n //= q
        es.append(e)
    return es, n

def smooth_set(limit):
    values = {1}
    for q in Q:
        expanded = set(values)
        for n in values:
            n *= q
            while n <= limit:
                expanded.add(n)
                n *= q
        values = expanded
    return values

check(3 * 8 * 8 == 192)
check(8 * 192 == 1536)
check(8**8-1 == 16777215)
check(7 * 4 == 28)
check(sum(7 * 8**j for j in range(4)) == 4095)
check(3**14 == 4782969 == int('22175571', 8))
check(6 + 8 == 14 == int('16', 8))
for n, octal in [(744, '1350'), (738, '1342'), (2124, '4114'), (360, '550'), (59, '73')]:
    check(n == int(octal, 8))
check(59 == 8*7+3)
check(738 == 2*3**2*(8*5+1))
check(2124 == 2**2*3**2*(8*7+3))
check(3**10 == 3**7*(8*3+3) == 59049)
check(2**11 == 2**7*2**4 == 2048)
check(12*15 == 2**2*3**2*5 == 180)
check(360//12 == 2*3*5 == 30)
check(Fraction(12,8) == Fraction(3,2) == 12*Fraction(1,8))
check(Fraction(3,7)**3 == Fraction(27,343))
check(19*23 == 256+160+21 == 437)
check(60**2 == 2**4*3**2*5**2 == 3600)
check(6**2*2 == 72)
check(12*15+15 == 195 == 3*5*13)
check(6*1365613 == 8193678)
check(prod(Q) == 510510)
check(tuple(360%q for q in Q) == (0,0,0,3,8,9,3))
check(tuple(510870%q for q in Q) == tuple(360%q for q in Q))
M = prod(Q)
def crt(residues):
    return sum(r * (M//q) * pow(M//q, -1, q) for r,q in zip(residues,Q)) % M
for n in range(10000):
    check(crt([n%q for q in Q]) == n)
check(crt([510870%q for q in Q]) == 360)
for q in Q:
    for n in range(4096):
        digits = [int(d) for d in oct(n)[2:]]
        r = 0
        for d in digits:
            r = (8*r+d)%q
        weighted = sum(d * pow(8,k,q) for k,d in enumerate(reversed(digits)))%q
        check(r == weighted == n%q)
check(37634 == 4*2**13+4866)
check(37634%8191 == 4+4866 == 4870)
check(738%7 == 3 and 738%11 == 1)
for p in [3,5,7,11,13,17,83]:
    n = 2**p-1
    tail, head = divmod(p,3)
    digits = (str((1<<head)-1) if head else '') + '7'*tail
    check(n == int(digits,8))
check(2**11-1 == 23*89 == 2047)
check(2**5-1 == 31)
check((2**41-1)%13367 == 0)
check(13367 == 2*163*41+1)
check(91 == 7*13)
check(42 == 2*21)
check((2**83-1)%167 == 0)
check(len(str(2**83-1)) == 25 and len(oct(2**83-1)[2:]) == 28)
check(all(16777213%d for d in range(2,isqrt(16777213)+1)))
check(oct(16777213)[2:] == '77777775')
limit = 2**24-1
smooth = len(smooth_set(limit))
check(smooth == 15748)
check(limit-smooth == 16761467)
print('24 bit pozitif alanda smooth:', smooth, 'rough:', limit-smooth)
print('Rough yüzdesi:', Decimal(limit-smooth)*100/Decimal(limit))
print('20M çiftte rough×rough yüzdesi:', Decimal(19327807)*100/20000000)
print('CRT modül çarpımı:', M, '360 ile 510870 aynı kalan vektörünü verir')
for x in range(8):
    for y in range(8):
        a={i for i in range(3) if x&(1<<i)}
        b={i for i in range(3) if y&(1<<i)}
        encode=lambda s: sum(1<<i for i in s)
        check(encode(a&b)==x&y)
        check(encode(a|b)==x|y)
        check(encode(a^b)==x^y)
        check(encode(set(range(3))-(a&b))==7^(x&y))
        check(encode(set(range(3))-(a|b))==7^(x|y))
with localcontext() as ctx:
    ctx.prec=60
    root=Decimal(59).sqrt()
    x=Fraction(0)
    print('Karekök 59 sürekli kesir yaklaşıkları:')
    for i in range(1,8):
        x=Fraction(10,14+x)
        value=Decimal(7)+Decimal(x.numerator)/Decimal(x.denominator)
        print(i, value, 'mutlak hata', abs(value-root))
    check(abs(value-root)<Decimal('3.4e-10'))
    # Sonlu yakınsak kesin rasyoneldir, irrasyonel köke eşit değildir.
    check((7+x)**2 != 59)
print('GECTI, bağımsız eşitlik kontrolü:', checks)
print('Sabit arşiv tarihi: 25 Ekim 2026')
print('Süre:', round(time.monotonic()-started,6), 's')
