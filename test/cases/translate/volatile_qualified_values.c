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
// pub var v1: __helpers.Volatile(c_uint) = .{
//     .value = 0,
// };
// pub var v2: vuint = .{
//     .value = 0,
// };
// pub const struct_hw = extern struct {
//     x: c_int = 0,
// };
// pub const union_uhw = extern union {
//     x: c_int,
// };
// pub var hw: __helpers.Volatile(struct_hw) = .{
//     .value = struct_hw{
//         .x = 0,
//     },
// };
// pub var uhw: __helpers.Volatile(union_uhw) = .{
//     .value = union_uhw{
//         .x = 0,
//     },
// };
// pub extern fn bar(a: c_uint, b: c_uint) void;
// pub export fn foo() void {
//     var x: c_uint = __helpers.addVolatile(&v1).*;
//     _ = &x;
//     x = __helpers.addVolatile(&v2).*;
//     x +%= __helpers.addVolatile(&v2).*;
//     __helpers.addVolatile(&v2).* = 3;
//     __helpers.addVolatile(&v2).* +%= 1;
//     var z: c_uint = blk: {
//         const ref = __helpers.addVolatile(&v2);
//         __helpers.addVolatile(&ref.*).* +%= 1;
//         break :blk ref.*;
//     };
//     _ = &z;
//     var y: c_uint = @as([*c]volatile c_uint, @ptrCast(&v1)).*;
//     _ = &y;
//     var yy: c_int = __helpers.addVolatile(&hw).*.x;
//     _ = &yy;
// }
// pub var varr: [3]vuint = [3]vuint{
//     0,
//     0,
//     0,
// };
// pub export fn baz() void {
//     var x: c_uint = __helpers.addVolatile(&varr[@as(c_int, 2)]).*;
//     _ = &x;
//     __helpers.addVolatile(&varr[@as(c_int, 2)]).* = x;
// }
