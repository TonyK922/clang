// do while(0)
#define fun(x)                                                                 \
    do                                                                         \
    {                                                                          \
        fun1(x);                                                               \
        fun2(x);                                                               \
    } while (0)

// 获取数组元素个数
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))

// 求两个数中最大值的宏MAX
#define MAX(x, y)                                                              \
    ({                                                                         \
        typeof(x) _max1 = (x);                                                 \
        typeof(y) _max2 = (y);                                                 \
        (void)(&_max1 == &_max2);                                              \
        _max1 > _max2 ? _max1 : _max2;                                         \
    })
// 语句表达式的值为内部最后一个表达式的值

// 通过成员获取结构体地址的宏container_of
// 我们传给某个函数的参数是某个结构体的成员，但是在函数中要用到此结构体的其它成员变量，这时就需要使用这个宏
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE*)0)->MEMBER)
#define container_of(ptr, type, member)                                        \
    ({                                                                         \
        const typeof(((type*)0)->member)* __mptr = (ptr);                      \
        (type*)((char*)__mptr - offsetof(type, member));                       \
    })

// #与变参宏  #和##
// #运算符，可以把宏参数转换为字符串
// ##运算符,可以把两个参数组合成一个

// 变参宏

// 我们都知道printf接受可变参数，C99后宏定义也可以使用可变参数。C99标准新增加的一个
// __VA_ARGS__ 预定义标识符来表示变参列表
#define DEBUG(...) printf(__VA_ARGS__)
#define _DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
