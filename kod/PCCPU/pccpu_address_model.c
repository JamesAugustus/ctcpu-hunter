/* Canonical source: JamesAugustus/ctcpu-hunter, kod/PCCPU/pccpu_address_model.c.
 * The Pascal repository distributes the same offline example. License: MIT.
 */
/* Logical PCCPU cell example. Sequential C software, not hardware.
 * James Augustus. MIT license (see LICENSE).
 * Addresses identify records, not bytes or a physical memory bus.
 */
#include <gmp.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { FIRST = 1000, CELLS = 6, A = 0, B = 1, ADD = 2,
       RESULT = 3, CONTROL = 4 };
typedef enum { EMPTY, WAITING, DONE, READY, RUNNING } State;
typedef struct {
    State state;
    mpz_t value;
    unsigned round, events;
    int issue_address;
} Cell;
typedef struct {
    Cell memory[CELLS];
    unsigned long n, k;
} Model;

static int address(int row, int column)
{
    return row >= 0 && row < 2 && column >= 0 && column < 3
        ? FIRST + row * 3 + column : -1;
}

/* Invalid initialization leaves the object untouched; do not clear it. */
static int init(Model *m, unsigned long n, unsigned long k)
{
    if (n == 0 || n == ULONG_MAX || k >= n) return -1;
    m->n = n;
    m->k = k;
    for (int i = 0; i < CELLS; ++i) {
        mpz_init(m->memory[i].value);
        m->memory[i].state = i < RESULT ? WAITING : EMPTY;
        m->memory[i].round = m->memory[i].events = 0;
        m->memory[i].issue_address = -1;
    }
    m->memory[CONTROL].state = RUNNING;
    return 0;
}

static void clear(Model *m)
{
    for (int i = 0; i < CELLS; ++i) mpz_clear(m->memory[i].value);
}

static int read_value(const Model *m, int addr, mpz_t out)
{
    if (addr < FIRST || addr >= FIRST + CELLS) return -1;
    int i = addr - FIRST;
    if (i > RESULT || (m->memory[i].state != DONE &&
                       m->memory[i].state != READY)) return -1;
    mpz_set(out, m->memory[i].value);
    return 0;
}

/* Evaluate against one snapshot, then commit. A round is not a clock cycle. */
static int step(Model *m, const int order[3], int trace)
{
    unsigned mask = 0;
    for (int j = 0; j < 3; ++j) {
        int addr = order[j];
        if (addr < FIRST || addr > FIRST + ADD) return -1;
        unsigned bit = 1u << (addr - FIRST);
        if (mask & bit) return -1;
        mask |= bit;
    }
    Cell *control = &m->memory[CONTROL];
    if (control->state == DONE) return 0;
    mpz_t pending[3];
    int ready[3] = {0, 0, 0}, count = 0;
    for (int i = 0; i < 3; ++i) mpz_init(pending[i]);
    for (int j = 0; j < 3; ++j) {
        int i = order[j] - FIRST;
        if (m->memory[i].state != WAITING) continue;
        if (i == A || i == B) {
            mpz_bin_uiui(pending[i], m->n, m->k + (unsigned long)i);
            ready[i] = 1;
        } else if (m->memory[A].state == DONE && m->memory[B].state == DONE) {
            mpz_add(pending[i], m->memory[A].value, m->memory[B].value);
            ready[i] = 1;
        }
        count += ready[i];
    }
    if (count) ++control->round;
    for (int j = 0; j < 3; ++j) {
        int i = order[j] - FIRST;
        if (!ready[i]) continue;
        mpz_set(m->memory[i].value, pending[i]);
        m->memory[i].state = DONE;
        int dest = i == ADD ? RESULT : i;
        if (i == ADD) {
            mpz_set(m->memory[RESULT].value, pending[i]);
            m->memory[RESULT].state = READY;
        }
        ++control->events;
        control->issue_address = FIRST + i;
        if (trace) gmp_printf("Tur %u | olay %u | isci %c | adres %d -> %d | deger %Zd\n",
            control->round, control->events, 'A' + i, FIRST + i,
            FIRST + dest, pending[i]);
    }
    for (int i = 0; i < 3; ++i) mpz_clear(pending[i]);
    if (m->memory[RESULT].state == READY) control->state = DONE;
    return count ? count : -1;
}

static int run(Model *m, const int order[3], int trace)
{
    while (m->memory[CONTROL].state != DONE)
        if (step(m, order, trace) < 0) return -1;
    return 0;
}

/* Symbolic row product, with an exact carry check. No full expansion. */
static int row_product(const mpz_t base, unsigned long r, unsigned long s)
{
    if (mpz_cmp_ui(base, 2) < 0 || r > ULONG_MAX - s) return -1;
    mpz_t middle;
    mpz_init(middle);
    unsigned long n = r + s;
    mpz_bin_uiui(middle, n, n / 2);
    int free_of_carry = mpz_cmp(middle, base) < 0;
    mpz_clear(middle);
    return free_of_carry;
}

static unsigned checks;
#define CHECK(condition) do { ++checks; if (!(condition)) { \
    fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #condition); \
    exit(EXIT_FAILURE); } } while (0)

static void tests(void)
{
    const int orders[6][3] = {
        {1000,1001,1002}, {1000,1002,1001}, {1001,1000,1002},
        {1001,1002,1000}, {1002,1000,1001}, {1002,1001,1000}
    };
    Model m;
    mpz_t value, base;
    mpz_inits(value, base, NULL);
    for (int r = 0; r < 2; ++r)
        for (int c = 0; c < 3; ++c) CHECK(address(r,c) == FIRST + 3*r + c);
    CHECK(address(-1,0) == -1 && address(0,3) == -1);
    CHECK(init(&m,0,0) == -1 && init(&m,2,2) == -1);
    CHECK(init(&m,ULONG_MAX,0) == -1);
    CHECK(init(&m,9,3) == 0);
    const int bad[3] = {1000,1000,1002};
    CHECK(step(&m,bad,0) == -1);
    CHECK(m.memory[CONTROL].events == 0 && m.memory[CONTROL].round == 0);
    CHECK(read_value(&m,1003,value) == -1);
    CHECK(read_value(&m,999,value) == -1);
    CHECK(step(&m,orders[5],0) == 2);
    CHECK(m.memory[ADD].state == WAITING);
    CHECK(read_value(&m,1003,value) == -1);
    CHECK(step(&m,orders[5],0) == 1);
    CHECK(read_value(&m,1003,value) == 0 && mpz_cmp_ui(value,210) == 0);
    CHECK(read_value(&m,1004,value) == -1);
    CHECK(step(&m,orders[0],0) == 0 && run(&m,orders[0],0) == 0);
    CHECK(m.memory[CONTROL].events == 3 && m.memory[CONTROL].round == 2);
    clear(&m);
    puts("PASS adresler, gecersiz istekler, bagimlilik ve tek sefer calisma");
    for (int p = 0; p < 6; ++p) {
        CHECK(init(&m,12,5) == 0);
        CHECK(run(&m,orders[p],0) == 0);
        CHECK(mpz_cmp_ui(m.memory[RESULT].value,1716) == 0);
        CHECK(m.memory[CONTROL].events == 3 && m.memory[CONTROL].round == 2);
        clear(&m);
    }
    puts("PASS alti farkli isci sirasi");
    /* Independent Pascal oracle uses only addition, no binomial routine. */
    mpz_t row[202];
    for (int i = 0; i < 202; ++i) mpz_init(row[i]);
    mpz_set_ui(row[0],1);
    for (unsigned long n = 0; n <= 200; ++n) {
        for (unsigned long j = n + 1; j > 0; --j)
            mpz_add(row[j],row[j],row[j-1]);
        for (unsigned long k = 0; k < n; ++k) {
            CHECK(init(&m,n,k) == 0);
            CHECK(run(&m,orders[k % 6],0) == 0);
            CHECK(mpz_cmp(m.memory[RESULT].value,row[k+1]) == 0);
            clear(&m);
        }
    }
    CHECK(mpz_sizeinbase(row[100],2) > 64);
    for (int i = 0; i < 202; ++i) mpz_clear(row[i]);
    puts("PASS 20100 Pascal toplami, yalniz toplama kullanan bagimsiz karsilastirma");
    mpz_set_ui(base,10);
    CHECK(row_product(base,2,2) == 1);
    CHECK(row_product(base,3,2) == 0);
    mpz_set_ui(base,3);
    CHECK(row_product(base,1,2) == 0);
    mpz_set_ui(base,127);
    CHECK(row_product(base,4,5) == 1 && row_product(base,5,5) == 0);
    CHECK(row_product(base,ULONG_MAX,1) == -1);
    mpz_set_ui(base,1);
    CHECK(row_product(base,2,2) == -1);
    puts("PASS eldesiz satir carpimi ve sinir kontrolleri");
    mpz_clears(value,base,NULL);
    printf("SONUC: %u kontrol gecti, 0 hata.\n",checks);
}

static int demo(void)
{
    const int order[3] = {1000,1001,1002};
    Model m;
    puts("PCCPU HUCRE MODELI - C / GMP\n"
         "Sirali yazilim modeli. Mantiksal tur, fiziksel saat cevrimi degildir.\n"
         "[1000: A] [1001: B] [1002: C]\n"
         "[1003: sonuc] [1004: PCCPU denetleyici] [1005: bos]\n"
         "A = C(9,3), B = C(9,4), C = A+B -> C(10,4)\n");
    if (init(&m,9,3) < 0) return 1;
    if (run(&m,order,1) < 0) { clear(&m); return 1; }
    gmp_printf("\nSonuc hucresi [1003] = %Zd\n",m.memory[RESULT].value);
    printf("PCCPU [1004]: %u olay, %u tur, son isci adresi %d\n",
        m.memory[CONTROL].events,m.memory[CONTROL].round,
        m.memory[CONTROL].issue_address);
    clear(&m);
    puts("\nBuyuk sayi: C(199,99) + C(199,100) = C(200,100)");
    if (init(&m,199,99) < 0) return 1;
    if (run(&m,order,1) < 0) { clear(&m); return 1; }
    gmp_printf("Sonuc = %Zd\n",m.memory[RESULT].value);
    clear(&m);
    puts("\nSatir carpimi: 121 x 121 = 14641 (eldesiz).\n"
         "1331 x 121 = 161051 (elde gerekiyor).\n"
         "Adres, degerin kendisi degildir. Degeri hesaplama isi bu C modelinde GMP ile yapilir.");
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1],"--test") == 0) { tests(); return 0; }
    if (argc == 1 || (argc == 2 && strcmp(argv[1],"--demo") == 0)) return demo();
    fprintf(stderr,"Usage: %s [--test | --demo]\n",argv[0]);
    return 2;
}
