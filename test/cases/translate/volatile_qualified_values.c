typedef volatile unsigned int vuint;

static volatile unsigned int v1 = 0u;
static vuint v2 = 0u;

struct hw {
    int x;
};

union uhw {
    int x;
};

static volatile struct hw hw = {0};
static volatile union uhw uhw = {0};

extern void bar(vuint a, volatile unsigned int b);

void foo() {
    unsigned int x = v1;
    x = v2;
    x += v2;
    v2 = 3u;
    v2 += 1u;
    unsigned int z = v2 += 1u;
    unsigned int y = *(&v1);
    int yy = hw.x;
}

static vuint varr[3] = {0,0,0};

void baz() {
    unsigned int x = varr[2];
    varr[2] = x;
}

// translate
//
// pub const vuint = __helpers.Volatile(c_uint);
//
// pub export fn foo() void {
//     (void)0;
// }
