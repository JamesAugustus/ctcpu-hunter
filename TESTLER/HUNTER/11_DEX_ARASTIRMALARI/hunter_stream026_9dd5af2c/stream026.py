from pathlib import Path
import random,json
HERE=Path(__file__).resolve().parent

def stream(limbs,p,w):
    m=(1<<p)-1;acc=0; maxacc=0; wraps=0;steps=0
    for i,a in enumerate(limbs):
        pos=(i*w)%p
        acc+=a<<pos
        maxacc=max(maxacc,acc.bit_length())
        while acc>>p:
            acc=(acc&m)+(acc>>p);wraps+=1
        if acc==m:acc=0
        steps+=1
    return acc,{'limbs':steps,'fold_passes':wraps,'max_accumulator_bits':maxacc}

def main():
 rng=random.Random(26026);count=0;cases=[]
 for p in (13,31,61,127,521):
  for w in (3,8,16):
   for rows in (2,3,4,8):
    maxbits=0;maxacc=0;folds=0
    n=(rows*p+w-1)//w
    for j in range(40):
     limbs=[rng.randrange(1<<w) for _ in range(n)]
     if j==0:limbs=[(1<<w)-1]*n
     if j==1:limbs=[0]*n
     value=sum(a<<(i*w) for i,a in enumerate(limbs))
     result,metrics=stream(limbs,p,w)
     assert result==value%((1<<p)-1)
     maxbits=max(maxbits,value.bit_length());maxacc=max(maxacc,metrics['max_accumulator_bits']);folds+=metrics['fold_passes'];count+=1
    cases.append({'P':p,'limb_bits':w,'nominal_rows':rows,'inputs':40,'input_limbs':n,'max_full_input_bits':maxbits,'max_accumulator_bits':maxacc,'fold_passes_total':folds})
 result={'status':'PASS','comparisons':count,'cases':cases,'scope':'Small streaming reduction only; full integer reference built only up to4176bits; no LL/square benchmark',
 'memory_meaning':'Logical accumulator size only; Python RSS and stored input/reference excluded. Stream can consume iterator.',
 'identity':'sum a_i*2^(i*w) = sum a_i*2^((i*w) mod P) modulo2^P-1'}
 (HERE/'SONUC_026.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'status':'PASS','comparisons':count,'examples':[c for c in cases if c['P']==521 and c['limb_bits']==8]},indent=2))
if __name__=='__main__':main()
