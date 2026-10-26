from models import hunter_channel_fold as m
results = [(n, getattr(m, n)()) for n in ['gate_y']]
for name, result in results:
 print(name, result)
assert all(r[0] in ('PASS', 'OK') for n,r in results), results
print('Kapı denetimleri tamamlandı')
