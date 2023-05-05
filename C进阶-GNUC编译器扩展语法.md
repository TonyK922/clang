先看一些Linux内核代码:
- ![](assets/Pasted%20image%2020230504175525.png)
- ![](assets/Pasted%20image%2020230504175603.png)
- ![](assets/Pasted%20image%2020230504175613.png)

这些就是GNU C的扩展语法.  这篇内容主要是为了看懂linux 内核代码.

# C语言标准和编译器

## C语言标准

主要内容:
- 定义各种关键字、定义各种数据类型、运算规则
- 数据类型转换
- 变量的作用域
- 运算符的优先级和结合性
- 函数原型、函数嵌套层数、参数个数限制
- 标准库函数接口

目的是为了 全球人类写c语言的时候, 能知道对方的意思. 不然不同编译器, 各玩各的. 同一套代码不同编译器编译出来结果不同. 那就不好了. 太混乱.

C语言标准发布后，大家都遵守这个标准开展工作：程序员开发程序时，按照这种标准规定的语法规则编写程序；编译器厂商开发编译器工具时，也按照这种标准去解析、翻译程序。不同的编译器厂商支持统一的C语言标准，我们编写的同一个程序使用不同的编译器都可以正常编译和运行.

C标准版本:
- K&R C
- ANSI C
- C99
- C11

## C标准和编译器

c99标准

C99标准是ANSI在1999年基于C89标准发布的一个新标准。该标准对ANSI C标准做了一些扩充，如新增了一些关键字，支持新的数据类型。
- 布尔型：`_Bool`.
- 复数：`_Complex`.
- 虚数：`_Imaginary`。
- 内联：inline.
- 指针修饰符: `restrict`.
- 支持long long、long double数据类型。
- 支持变长数组。
- 允许对结构体特定成员赋值。
- 支持十六进制浮点数, float_Complex等数据类型.

C99标准也会借鉴其他编程语言的一些优点，对自身的语法和标准做一系列改进，例如：
- 变量声明可以放在代码块的任何地方。ANSI C标准规定变量的声明要全部写在函数语句的最前面，否则就会报编译错误。现在不需要这样写了，哪里需要使用变量，直接在哪里声明即可。
- 源程序每行最大支持4095字节。这个貌似足够用了，没有什么程序能复杂到一行程序有4000多个字符。
- 支持`//`单行注释。早期的ANSI C标准使用`/**/`注释，不如C++的//注释方便，所以C99标准就把这种注释吸收过来了，从C99标准开始也支持这种注释方式。
- 标准库新增了一些头文件，如stdbool.h、complex.h、stdarg.h、fenv.h等。大家在C语言中经常返回的true、false，其实这是C++里面的定义的bool类型，早期的C语言是没有bool类型的。那为什么我们经常这样写，而编译器编译程序时没有报错呢？这是因为早期大家编程使用的都是VC++6.0系列，使用的是C++编译器，C++编译器是兼容ANSI C标准的。当然还有一种可能就是有些IDE对这种数据类型做了封装。

C11标准

C11标准是ANSI在2011年发布的最新C语言标准，C11标准修改了C
语言标准的一些bug，增加了一些新特性。
- 增加_Noreturn，声明函数无返回值。
- 增加_Generic，支持泛型编程。
- 修改了标准库函数的一些bug，如gets()函数被gets_s()函数代替。
- 新增文件锁功能。
- 支持多线程。

从C11标准的新增内容，我们可以观察到C语言未来的发展趋势。C语言现在也在借鉴现代编程语言的优点，不断添加到自己的标准里。如现代编程语言的多线程、字符串、泛型编程等，C语言最新的标准都支持。但是这样下去，C语言会不会变得越来越臃肿？是不是还能保持它“简单就是美”的初心呢？这一切只能交给时间了，至少目前我们不用担心这些，因为新发布的C11标准，目前绝大多数编译器还不支持，我们暂时还用不到。

C标准是一套规则, 而编译器支不支持还另说. 目前对C99标准支持最好的是GNU C编译器，据说可以支持C99标准99%的新增特性。

嵌入式开发常用的编译器
- GCC编译器
- ARM编译器
- C51编译器

不同编译器对C标准的支持
- VC系列
- GCC系列

编译器对C标准的扩展

不同编译器，出于开发环境、硬件平台、性能优化的需要，除了支持C语言标准，还会自己做一些扩展。

在51单片机上用C语言开发程序，我们经常使用Keil for C51集成开发环境。你会发现Keil for C51或者其他IDE里的C编译器会对C语言做很多扩展，如增加了各种关键字。
- data：RAM的低128B空间，单周期直接寻址。
- code：表示程序存储区。
- bit：位变量，常用来定义51单片机的P0～P3管脚。
- sbit：特殊功能位变量。
- sfr：特殊功能寄存器。
- reentrant：重入函数声明。

如果你在程序中使用以上这些关键字，那么你的程序只能使用51编译器来编译运行；如果你使用其他编译器，如VC++6.0，则编译是通不过的。

同样的道理，GCC编译器也对C语言标准做了很多扩展:
- 零长度数组
- 语句表达式
- 内建函数
- `__attribute__`特殊属性声明
- 标号元素
- case范围

- ![](assets/Pasted%20image%2020230504181419.png)
- ![](assets/Pasted%20image%2020230504181426.png)

## 新增特性

预定义标识符:
`__DATA__`  `__FILE__`  `__FUNCTION__` `__LINE__` `__STDC__` `__TIME__` `__func__` 
include   define   printf/ scanf
- 编译器预定义的标识符
- 标准库函数名
- 预处理命令名

特点:
- 代表特定的含义
- 用户不要再将其当作普通标识符使用
- 用作普通标识符时, 会失去其原义

GNU C extentions:
- ![](assets/Pasted%20image%2020230504182049.png)

# 指定初始化

## 数组元素的指定初始化

```c
int a[100] = {[10]=1, [20 ... 30] = 2, [50] = 3}; //注意 ... 的空格
```

`...`  的switch-case: 
```c
switch(a)
{
	case 1: break;
	case 2 ... 8: break; // 看这里
	case 9 : break;
	default:
	  break;
}
```
`...`和其两端的数据范围2和8之间也要有`空格`, 不能写成`2...8`的形式, 否则会报编译错误。

## 指定初始化结构体成员

```c
struct student{
	char name[20];
	int age;
};
typedef struct student stu;

int main(){
	stu s1 = { .name = "tony", .age = 18 };
}
```
上面代码中, 我们采用GNU C的初始化方式, 通过结构域名.name和.age, 就可以给结构体变量的某一个指定成员直接赋值. 
当然也可以采用C语言标准的初始化方式，即按照固定顺序直接初始化.

## Linux内核驱动注册

在Linux内核驱动中，大量使用GNU C的这种指定初始化方式，通过结构体成员来初始化结构体变量。如在字符驱动程序中，我们经常见到下面这样的初始化。

```c
static const struct file_operations 
ab3100_opt_operations = 
{
.open = ab3100_otp_open,
.read = seq_read,
.llseek = seq_lseek,
.release = single_release,
};
```

在驱动程序中，我们经常使用file_operations这个结构体来注册我们开发的驱动，然后系统会以回调的方式来执行驱动实现的具体功能。结构体file_operations在Linux内核中的定义如下:
- ![](assets/Pasted%20image%2020230504185610.png)
	- 结构体file_operations里定义了很多结构体成员, 而在这个驱动中, 我们只初始化了部分成员变量. 通过访问结构体的各个成员域来指定初始化, 当结构体成员很多时优势就体现出来了, 初始化会更加方便. 

指定初始化不仅使用灵活，而且还有一个好处，就是代码易于维护。

尤其是在Linux内核这种大型项目中，有几万个文件、几千万行的代码，当成百上千个文件都使用file_operations这个结构体类型来定义变量并初始化时，那么一个很大的问题就来了：如果采用C标准按照固定顺序赋值，当file_operations结构体类型发生变化时，如添加了一个成员、删除了一个成员、调整了成员顺序，那么使用该结构体类型定义变量的大量C文件都需要重新调整初始化顺序，牵一发而动全身，想想这有多可怕！

我们通过指定初始化方式，就可以避免这个问题。无论file_operations结构体类型如何变化，添加成员也好、删除成员也好、调整成员顺序也好，都不会影响其他文件的使用。

# 语句表达式

## 定义

表达式 = 操作符 + 操作数
语句 = 表达式 + `;`
代码块 = 语句 + `{}`

- GNU C对C语言标准作了扩展, 允许在一个表达式里内嵌语句, 允许在表达式内部使用局部变量, for循环和goto跳转语句. 这种类型的表达式，我们称为`语句表达式`. 
	- 语句表达式的格式如下:
	- `({表达式1; 表达式2; 表达式3;});`

- 注意: 语句表达式最外面使用`小括号()`括起来, 里面一对`大括号{}`包起来的是代码块, 最后要加`;`分号, 因为`语句表达式本质还是语句`.
- 代码块里允许内嵌各种语句. 语句的格式可以是一般表达式, 也可以是循环, 跳转语句. 

- 语句表达式的值为内嵌语句中`最后一个表达式的值.` 
	- 上面的语句表达式的值就是表达式3的值.

栗子:
```c
int main(void)
{
	int sum = 0;
	sum = 
	({
		int s = 0;   //表达式1  声明
		for (int i = 0; i < 10; i++)   
			s += i;    //表达式2 for()
			s;   //表达式3 
	});
	printf("sum = %d\n", sum);
	return 0;
}
```

在上面的程序中, 通过语句表达式实现了从1到10的累加求和, 因为语句表达式的值等于最后一个表达式的值, 所以在for循环的后面, 我们要`添加一个s`; 语句表示整个语句表达式的值. 如果不加这一句, 你会发现sum = 0. 或者你将这一行语句改为`100; `, 你会发现最后sum的值就变成了100, 这是因为语句表达式的值总等于最后一个表达式的值. 

在上面的程序中，我们在语句表达式内定义了局部变量，使用了for循环语句。在语句表达式内，我们同样可以使用goto进行跳转。

```c
int main(void)
{
	int sum = 0;
	sum = 
	({
		int s = 0;   //表达式1  声明
		for (int i = 0; i < 10; i++)   
			s += i;    //表达式2 for()
			goto here;
			s;   //表达式3 
	});
	printf("sum = %d\n", sum);
here:
	puts("here:");
	printf("sum = %d\n", sum);
	return 0;
}
```
上面代码会打印
here:
sum = 0

## 宏定义中的语句表达式

语句表达式的主要用途在于定义功能复杂的宏. 使用语句表达式来定义宏, 不仅可以实现复杂的功能, 还能避免宏定义带来的歧义和漏洞. 

简单的宏: 两个数取较大的那个:
一般选手:
```c
#define MAX(x,y) ((x)>(y)?(x):(y))
```
上面的写法基本可以:

现在:
```c
#define MAX(x,y) ((x)>(y)?(x):(y))

int main(void)
{
	int x = 2;
	int y = 6;
	printf("max = %d\n", MAX(x++,y++));
	return 0;
}
```

上面结果会打印max = 7, 而不是 我们想要的6; 所以上面那种写法还是有问题.

在C语言编程规范里, 使用宏时一般是不允许参数变化的. 万一碰到这种情况, 该怎么办呢? 这时候, 语句表达式就该上场了. 我们可以使用语句表达式来定义这个宏, 在语句表达式中定义两个临时变量, 分别来暂时存储i和j的值, 然后使用临时变量进行比较, 这样就避免了两次自增, 自减问题.

```c
#define MAX(type,x,y)({  \
    type _x = (x);       \
    type _y = (y);       \
    _x > _y ? _x : _y;   \
})

// 优化版:
#define MAX(x,y)({      \
    typeof(x) _x = (x); \
    typeof(y) _y = (y); \
    (void)(&_x == &_y); \
    _x > _y ? _x : _y;  \
})
```

在优化版宏定义中, 我们使用了typeof关键字来自动获取宏的两个参数类型. 比较难理解的是`(void)(&x == &y);`这句话, 看起来很多余, 仔细分析一下, 你会发现这条语句很有意思。

它的作用有两个: 
- 一是用来给用户提示一个警告, 对于不同类型的指针比较, 编译器会发出一个警告, 提示两种数据的类型不同. 
	- ![](assets/Pasted%20image%2020230504194611.png)
- 二是两个数进行比较运算, 运算的结果却没有用到, 有些编译器可能会给出一个warning, 加一个(void)后, 就可以消除这个警告. 

内核的函数调用本来就很深, 所以栈的消耗往往很大. 为了节约开销, 就会用大量的语句表达式的宏, 和inline函数.

语句表达式，作为GNU C对C标准的一个扩展，在内核中，尤其在内核的宏定义中被大量使用。使用语句表达式定义宏，不仅可以实现复杂的功能，还可以避免宏定义带来的一些歧义和漏洞。

## typeof与container_of宏

>typeof关键字

- ANSI C定义了sizeof关键字, 用来获取一个变量或数据类型在内存中所占的字节数. 
- GNU C扩展了一个关键字typeof, 用来获取一个变量或表达式的类型. 
	- 这里使用关键字可能不太合适, 因为毕竟typeof现在还没有被纳入C标准, 是GCC扩展的一个关键字.  姑且把它叫作关键字.

- 使用typeof可以获取一个变量或表达式的类型
	- typeof的参数有两种形式: 表达式或类型. 

```c
int i;
typeof(i) j = 20;  //typeof(i)就等于int , int j=20
typeof(int *) a; // int *a;
int f();   
typeof(f()) k;  // int k;
```

使用示例:
```c
int f();

int main(void)
{
	int i = 2;
	typeof(i) k = 6;

	int *p = &k;
	typeof(p) q = &i;
	printf("k = %d\n", k);
	printf("*p = %d\n", *p);
	printf("i = %d\n", i);
	printf("*q = %d\n", *q);

	typeof(f()) m = 100;
}
```
打印如下:
- ![](assets/Pasted%20image%2020230504200341.png)

基本用法:
- `typeof (int *) y;`     把y定义为指向int类型的指针
- `typeof (int) *y;`       把y定义为指向int类型的指针
- `typeof (*x) y;`          把y定义为指针x指向的数据类型
- `typeof (int) y[4];`     相当于定义一个：int y[4]
- `typeof (*x) y[4];`     把y定义为指针x指向的数据类型的数组
- `typeof (typeof (char *)[4]) y;`  定义一个字符指针数组：`char *y[4];`
- `typeof(int x[4]) y; ` 相当于定义：int y[4]

在内核中的使用
- 主要用途
	- 主要用在宏定义中
	- 使用typeof来获取宏参数类型
- 内核代码示例
	- 宏定义：交换两个数
	- 可以交换多种类型的变量

```c
#define SWAP(a, b) { \
	typeof(a) _t=a; \
			   a=b; \
		       b=_t;}
```

>container_of

这个宏在Linux内核中应用甚广, 会不会用这个宏, 看不看得懂这个宏, 也逐渐成为考察一个内核驱动开发者的C语言功底的不成文标准. 

container_of功能
- 根据结构体某一成员的地址, 获取这个结构体的首地址
	- 结构体类型
	- 结构体成员
	- 结构体成员地址

```c
struct student{
	int age;
	int num;
	int math;
} stu;

p = container_of ( &stu.num, struct student, num);
```

宏定义:
```c
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of( ptr, type, member) ({   \
  const typeof( ((type *)0)->member ) *__mptr = (ptr);  \
  (type *) ( (char *)__mptr - offsetof(type, member) );})
```

type：结构体类型
member：结构体成员变量
ptr：结构体成员变量的地址

这个宏在内核中非常重要, Linux内核中有大量的结构体类型数据, 为了抽象, 对结构体进行了多次封装, 往往在一个结构体里嵌套多层结构体. 内核中不同层次的子系统或模块, 使用的就是对应的不同封装程度的结构体, 这也是C语言的面向对象编程思想在Linux内核中的实现. 通过分层, 抽象和封装, 可以让我们的程序兼容性更好, 能适配更多的设备, 程序的逻辑也更容易理解. 

在内核中, 我们经常会遇到这种情况: 我们传给某个函数的参数是某个结构体的成员变量, 在这个函数中, 可能还会用到此结构体的其他成员变量, 那么该怎么操作呢? container_of就是干这个的, 通过它, 我们可以首先找到结构体的首地址, 然后通过结构体的成员访问就可以访问其他成员变量了. 

container_of宏实现分析:
- 注意结构体对齐
- 因为它用到了offsetof这个宏, 所以先看它.

```c
typedef struct student{
	int age;
	int num;
	int math;
} STU;

int main(void)
{
	STU stu = {20, 1001, 99};
	printf("&stu = %p\n", &stu);
	printf("&stu.age = %p\n", &stu.age);
	printf("&stu.num = %p\n", &stu.num);
	printf("&stu.math = %p\n", &stu.math);

	return 0;
}
```
程序运行结果如下:
- ![](assets/Pasted%20image%2020230504205835.png)

从运行结果可以看到，结构体中的每个成员变量，从结构体首地址开始依次存放，每个成员变量相对于结构体首地址，都有一个固定偏移。如num相对于结构体首地址偏移了4字节。math的存储地址相对于结构体首地址偏移了8字节.

一个结构体数据类型, 在同一个编译环境下, 各个成员相对于结构体首地址的偏移是固定不变的. 我们可以修改一下上面的程序: 当结构体的首地址为0时, 结构体中各个成员的地址在数值上等于结构体各成员相对于结构体首地址的偏移. 

```c
typedef struct student{
	int age;
	int num;
	int math;
} STU;
int main(void)
{
	printf("&age = %p\n", &((struct student *)0)->age);
	printf("&num = %p\n", &((struct student *)0)->num);
	printf("&math = %p\n", &((struct student *)0)->math);

	return 0;
}
```
在上面的程序中, 我们没有直接定义结构体变量, 而是将数字0通过强制类型转换, 转换为一个指向结构体类型为student的常量指针, 然后分别打印这个常量指针指向的各成员地址:
- ![](assets/Pasted%20image%2020230504210137.png)

因为常量指针的值为0，即可以看作结构体首地址为0，所以结构体中每个成员变量的地址即该成员相对于结构体首地址的偏移. container_of宏的实现就是使用这个技巧来实现的. 
offsetof 的原理搞明白了就继续 container_of吧.

```c
#define offsetof (TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of( ptr, type, member) ({   \
  const typeof( ((type *)0)->member ) *__mptr = (ptr);  \
  (type *) ( (char *)__mptr - offsetof(type, member) );})
```

从语法角度来看, container_of宏的实现由一个语句表达式构成. 语句表达式的值即最后一个表达式的值. `(type *) ( (char *)__mptr - offsetof(type, member) );`

container_of的原理概括一句话:
- 成员变量的实际地址, 减去该成员的偏移量, 就是结构体变量的实际首地址了.

然后这个宏的值 是`(type *)`类型的. 就把结构体变量的首地址返回了.

offsetof宏 将0强制转换为一个指向TYPE类型的结构体常量指针, 然后通过这个常量指针访问成员, 获取成员MEMBER的地址, 其大小在数值上等于MEMBER成员在结构体TYPE中的偏移量. 

结构体的成员数据类型可以是任意数据类型, 为了让这个宏兼容各种数据类型, 我们定义了一个临时指针变量`__mptr`, 该变量用来存储结构体成员MEMBER的实际地址, 即存储宏中的参数ptr的值.
`const typeof( ((type *)0)->member ) *__mptr = (ptr);`

最后`__mptr`的值, 结构体变量的成员实际地址, 减去 offsetof 的结果. 注意, offsetof的结果, 已经是偏移量了, 几偏移了几个字节, 所以需要强转成 `char *` , 因为如果__mptr是`(int *)`, 减去一个值, 偏移就是 4 * 偏移量了, 因为是按4字节寻址的. 只有是char类型的指针, 寻址才是按1字节.

结束.

# 零长度数组

零长度数组, 变长数组都是GNU C编译器支持的数组类型.  顾名思义, 零长度数组就是长度为0的数组.

ANSI C标准规定: 定义一个数组时, 数组的长度必须是一个常数, 即数组的长度在编译的时候是确定的. 

C99标准规定: 可以定义一个变长数组. 
```c
int len;
int a[len];
```
数组的长度在编译时是未确定的, 在程序运行的时候才确定, 甚至可以由用户指定大小. 

零长度数组特点, 就是它不占用内存存储空间. 只表示地址.
举个例子: 
```c
int main (int argc, char *argv[])
{
    char a[0];

    printf("%zd %p\n", sizeof(a), &a);
    return 0;
}
```
输出结果:
```shell
0  0x7ffd44fb7887
```
没长度, 但有地址.

零长度数组一般单独使用的机会很少, 它常常作为结构体的一个成员, 构成一个变长结构体. 

```c
struct buffer{
	int len;
	char arr[0];
};
```

零长度数组在结构体中同样不占用存储空间, 所以buffer结构体的大小为4. 

零长度数组使用示例:

零长度数组经常以变长结构体的形式, 在某些特殊的应用场合使用. 在一个变长结构体中, 零长度数组不占用结构体的存储空间, 但是我们可以通过使用结构体的成员arr去访问内存, 非常方便. 变长结构体的使用示例如下:
```c
struct buffer{
	int len;
	char arr[0];
};

int main()
{
	struct buffer *buff;
	buff = (struct buffer *)malloc(sizeof(struct buffer) + 20);
	if(!buff) exit(-1);

	buff->len = 20;
	strncpy(buff->arr, "hello world", strlen("hello world")+1);
	puts(buff->arr);

	free(buff);
	return 0;
}
```

### 内核中的零长度数组

零长度数组在内核中一般以变长结构体的形式出现. 我们就分析一下变长结构体内核USB驱动中的应用. 在网卡驱动中, 大家可能都比较熟悉一个名字: 套接字缓冲区, 即Socket Buffer, 用来传输网络数据包. 同样, 在USB驱动中, 也有一个类似的东西, 叫作URB, 其全名为`USB Request Block`, 即USB请求块, 用来传输USB数据包. 
- include/linux/usb.h:
```c
struct urb {
	/* private: usb core and host controller only fields in the urb */
	struct kref kref;		/* reference count of the URB */
	void *hcpriv;			/* private data for host controller */
	atomic_t use_count;		/* concurrent submissions counter */
	atomic_t reject;		/* submissions will fail */
	int unlinked;			/* unlink error code */

	/* public: documented fields in the urb that can be used by drivers */
	struct list_head urb_list;	/* list head for use by the urb's
					 * current owner */
	struct list_head anchor_list;	/* the URB may be anchored */
	struct usb_anchor *anchor;
	struct usb_device *dev;		/* (in) pointer to associated device */
	struct usb_host_endpoint *ep;	/* (internal) pointer to endpoint */
	unsigned int pipe;		/* (in) pipe information */
	unsigned int stream_id;		/* (in) stream ID */
	int status;			/* (return) non-ISO status */
	unsigned int transfer_flags;	/* (in) URB_SHORT_NOT_OK | ...*/
	void *transfer_buffer;		/* (in) associated data buffer */
	dma_addr_t transfer_dma;	/* (in) dma addr for transfer_buffer */
	struct scatterlist *sg;		/* (in) scatter gather buffer list */
	int num_mapped_sgs;		/* (internal) mapped sg entries */
	int num_sgs;			/* (in) number of entries in the sg list */
	u32 transfer_buffer_length;	/* (in) data buffer length */
	u32 actual_length;		/* (return) actual transfer length */
	unsigned char *setup_packet;	/* (in) setup packet (control only) */
	dma_addr_t setup_dma;		/* (in) dma addr for setup_packet */
	int start_frame;		/* (modify) start frame (ISO) */
	int number_of_packets;		/* (in) number of ISO packets */
	int interval;			/* (modify) transfer interval
					 * (INT/ISO) */
	int error_count;		/* (return) number of ISO errors */
	void *context;			/* (in) context for completion */
	usb_complete_t complete;	/* (in) completion routine */
	struct usb_iso_packet_descriptor iso_frame_desc[0];
					/* (in) ISO ONLY */
};
```

这个结构体内定义了USB数据包的传输方向, 传输地址, 传输大小, 传输模式等. 这些细节我们不深究, 只看最后一个成员. 

在URB结构体的最后定义一个零长度数组, 主要用于USB的同步传输. USB有4种传输模式: 中断传输, 控制传输, 批量传输和同步传输. 不同的USB设备对传输速度, 传输数据安全性的要求不同, 所采用的传输模式也不同. USB摄像头对视频或图像的传输实时性要求较高, 对数据的丢帧不是很在意, 丢一帧无所谓, 接着往下传就可以了. 所以USB摄像头采用的是USB同步传输模式.

USB摄像头一般会支持多种分辨率, 从`16*16`到高清720P多种格式. 不同分辨率的视频传输, 一帧图像数据的大小是不一样的, 对USB传输数据包的大小和个数需求是不一样的. 那么USB到底该如何设计, 才能在不影响USB其他传输模式的前提下, 适配这种不同大小的数据传输需求呢? 答案就在结构体内的这个零长度数组上. 

当用户设置不同分辨率的视频格式时, USB就使用不同大小和个数的数据包来传输一帧视频数据. 通过零长度数组构成的这个变长结构体就可以满足这个要求. USB驱动可以根据一帧图像数据的大小, 灵活地申请内存空间, 以满足不同大小的数据传输. 而且这个零长度数组又不占用结构体的存储空间. 当USB使用其他模式传输时, 不受任何影响, 完全可以当这个零长度数组不存在. 所以不得不说, 这个设计还是很巧妙的. 

看看内核是如何使用这个零长数组的呢?
```c
struct urb *usb_alloc_urb(int iso_packets, gfp_t mem_flags)
{
	struct urb *urb;

	urb = kmalloc(sizeof(struct urb) +
		iso_packets * sizeof(struct usb_iso_packet_descriptor),
		mem_flags);
	if (!urb)
		return NULL;
	usb_init_urb(urb);
	return urb;
}
EXPORT_SYMBOL_GPL(usb_alloc_urb);
```
kmalloc是内核中的内存申请接口.

为何使用零长数组, 而不是用一个指针?
- 定义指针要占用空间.
- 数组名不是指针
	- 数组名是地址常量, 它作为参数传递的时候, 传的就是这个地址常量. 也就是被常说 弱化成指针.
	- 数组名用来表征一块连续内存空间, 而指针是一个变量, 编译器要给它单独分配一个内存空间. 
	- 而对于数组名, 编译器不会再给它分配一个单独的存储空间, 它仅仅是一个符号, 和函数名一样, 用来表示一个地址.

- 看个例子:
	- ![](assets/Pasted%20image%2020230504222649.png)
	- 使用ARM交叉编译器进行编译，并进行反汇编:
	- ![](assets/Pasted%20image%2020230504222749.png)
	- 从汇编代码中, 可以看到, 对于长度为10的数组`array1[10]`, 编译器给它分配了从0x21024～0x21048共40字节的存储空间, 但并没有给`数组名array1`单独分配存储空间, 数组名array1仅仅表示这40个连续存储空间的首地址, 即数组元素`array1[0]`的地址。
	- 对于指针变量p, 编译器给它分配了0x2104c这个存储空间, 在这个存储空间上存储的是数组元素`array1[5]`的地址: 0x21038. 
	- 对于指针变量p, 编译器给它分配了0x2104c这个存储空间, 在这个存储空间上存储的是数组元素`array1[5]`的地址: 0x21038,
	- 而对于`array2[0]`这个零长度数组, 编译器并没有为它分配存储空间, 此时的array2仅仅是一个符号, 用来表示内存中的某个地址, 我们可以通过查看可执行文件a.out的符号表来找到这个地址值. 
		- ![](assets/Pasted%20image%2020230504223120.png)
	- 看符号表就可以知道, array2 长度0, 但是有地址0x21054. 在BSS段的后面. array2符号表示的默认地址是一片未使用的内存空间, 仅此而已, 编译器绝不会单独再给其分配一个存储空间来存储数组名. 


# 属性声明: section

>GNU C编译器扩展关键字：`__attribute__`

主要用途: 
- GNU C增加了一个`__attribute__`关键字用来声明一个函数, 变量或类型的特殊属性. 
- 主要用途就是指导编译器在编译程序时进行特定方面的优化或代码检查. 
	- 例如, 我们可以通过属性声明来指定某个变量的数据对齐方式. 

使用方法
- `__attribute__`的使用非常简单, 当我们定义一个函数, 变量或类型时, 直接在它们名字旁边添加下面的属性声明即可. 
- 在声明后面添加：`__attribute__((ATTRIBUTE))`
- 例：`int global_val __attribute__((section(“.data”)));`.
- 注意属性声明的` section("")` 中的双引号.

需要注意的是, `__attribute__`后面是两对小括号, 不能图方便只写一对, 否则编译就会报错. 括号里面的ATTRIBUTE表示要声明的属性. 目前`__attribute__`支持十几种属性声明:
- section
- aligned
- packed.
- format.
- weak.
- alias.
- noinline.
- always_inline.

aligned和packed用来显式指定一个变量的存储对齐方式。在正常情况下，当我们定义一个变量时，编译器会根据变量类型给这个变量分配合适大小的存储空间，按照默认的边界对齐方式分配一个地址。而使用__atttribute__这个属性声明，就相当于告诉编译器：按照我们指定的边界对齐方式去给这个变量分配存储空间:
- ![](assets/Pasted%20image%2020230504225259.png)
- 有些属性可能还有自己的参数。如aligned(8)表示这个变量按8字节地址对齐，属性的参数也要使用小括号括起来，如果属性的参数是一个字符串，则小括号里的参数还要用双引号引起来。

我们也可以对一个变量同时添加多个属性说明。在定义变量时，各个属性之间用逗号隔开。
- ![](assets/Pasted%20image%2020230504225349.png)
- 对一个变量添加两个属性声明, 这两个属性都放在`__attribute__(())`的两对小括号里面, 属性之间用逗号隔开. 
- 如果属性有自己的参数，则属性的参数同样要用小括号括起来。
- 这里还有一个细节，就是属性声明要紧挨着变量，上面的三种声明方式都是没有问题的，但下面的声明方式在编译的时候可能就通不过。
	- ![](assets/Pasted%20image%2020230504225515.png)

## 属性声明：section

我们可以使用`__attribute__`来声明一个`section属性`, section属性的主要作用是: 在程序编译时，将一个函数或变量放到指定的段, 即放到指定的section中. 

一个可执行文件主要由代码段, 数据段, BSS段构成. 代码段主要存放编译生成的可执行指令代码, 数据段和BSS段用来存放全局变量, 未初始化的全局变量. 代码段, 数据段和BSS段构成了一个可执行文件的主要部分. 

除了这三个段, 可执行文件中还包含其他一些段. 用编译器的专业术语讲, 还包含其他一些section, 如只读数据段, 符号表等. 我们可以使用下面的readelf命令, 去查看一个可执行文件中各个section的信息. 

栗子:
```c
#include <stdio.h>

__attribute__((section(".data"))) int global;

int main (int argc, char *argv[])
{
    return 0;
}
```
以前我们就知道, 如果不加`__attribute__((section(".data")))`,  int global必然被扔到.bss段中去的. 现在我们来看看:
```shell
readelf -s  attribute |grep global

29: 00000000000010e0     0 FUNC    LOCAL  DEFAULT   14 __do_global_dtors_aux
31: 0000000000003df8     0 OBJECT  LOCAL  DEFAULT   20 __do_global_dtors_aux_fin
49: 0000000000004010     4 OBJECT  GLOBAL DEFAULT   23 global

readelf -S  attribute | grep 23
[23] .data             PROGBITS         0000000000004000  00003000
```
结果的确是放到.data段了. 就是这样.

你也可以把.data换成随便一个名字 比如test, 结果就是他被放到test段中.
```shell
readelf -s  section | grep global

50: 0000000000004010     4 OBJECT  GLOBAL DEFAULT   24 global


➜ readelf -S  section | grep 24

[24] test              PROGBITS         0000000000004010  00003010

```

我们给函数也放到指定的section.
```c
#include <stdio.h>

__attribute__((section("test"))) int global;

__attribute__((section("test"))) int fun()
{
	return 0;
}

int main (int argc, char *argv[])
{
    return 0;
}
```

上面代码有个有趣的报错:
```shell
section.c: In function ‘fun’:
section.c:5:38: error: ‘fun’ causes a section type conflict with ‘global’
    5 | __attribute__((section("test"))) int fun()
      |                                      ^~~
section.c:3:38: note: ‘global’ was declared here
    3 | __attribute__((section("test"))) int global;
      |                                      ^~~~~~
make: *** [<内置>：section] 错误 1
```

数据跟函数不能放在同一个section中. 想想肯定是的, 因为数据是可读写的, 而函数代码是只读的. 所以放在一个段里, 这个段的权限怎么规定? 

所以我们把fun()函数的 section改成test2 , 编译 查看:
```shell
readelf -s  section | grep fun

52: 00000000000011b5    15 FUNC    GLOBAL DEFAULT   15 fun

readelf -S  section | grep 15

[15] test2             PROGBITS         00000000000011b5  000011b5
```

## Linux内核驱动中的`__init`宏

linux 内核中有些函数, 只需要在初始化的时候执行一次, 后面基本就不用了. 如果不做特殊处理, 这些函数就浪费资源. 只用一次, 就不用了, 还占用资源的话就不合适. 

宏定义:
```c
#define __init __section(.init.text) __cold notrace
```

被`__init` 宏修饰的函数, 在系统启动完成, 就会被清理掉.  在 `start_kernel` 里有大量的初始化函数. 在这个函数的最后一行会调用 `rest_init()`; 
```c
static noinline void __ref rest_init(void)
{
	struct task_struct *tsk;
	int pid;

	rcu_scheduler_starting();

	pid = kernel_thread(kernel_init, NULL, CLONE_FS);
  ........
	/*
	 * The boot idle thread must execute schedule()
	 * at least once to get things moving:
	 */
	schedule_preempt_disabled();
	/* Call into cpu_idle with preempt disabled */
	cpu_startup_entry(CPUHP_ONLINE);
}
```
kernel_thread()中 调用 kernel_init()函数, kernel_init函数里又调用free_initmem(); 它接着调用一个内联函数 free_initmem_default(); 接着又调用`free_reserved_area()`函数. 
```c
/*
 * Default method to free all the __init memory into the buddy system.
 * The freed pages will be poisoned with pattern "poison" if it's within
 * range [0, UCHAR_MAX].
 * Return pages freed into the buddy system.
 */
static inline unsigned long free_initmem_default(int poison)
{
	extern char __init_begin[], __init_end[];

	return free_reserved_area(&__init_begin, &__init_end,
				  poison, "unused kernel");
}
```

vmlinux.lds linux elf的链接脚本:
- ![](assets/Pasted%20image%2020230504233204.png)
- `__init_begin` 和 `__init_end` 中间, 是所有`.init.xx` 段的集合. 

`free_reserved_area` 会把这中间的内容全清了.
```c
unsigned long free_reserved_area(void *start, void *end, int poison, char *s)
{
	void *pos;
	unsigned long pages = 0;

	start = (void *)PAGE_ALIGN((unsigned long)start);
	end = (void *)((unsigned long)end & PAGE_MASK);
	for (pos = start; pos < end; pos += PAGE_SIZE, pages++) {
		struct page *page = virt_to_page(pos);
		void *direct_map_addr;
		/*
		 * 'direct_map_addr' might be different from 'pos'
		 * because some architectures' virt_to_page()
		 * work with aliases.  Getting the direct map
		 * address ensures that we get a _writeable_
		 * alias for the memset().
		 */
		direct_map_addr = page_address(page);
		if ((unsigned int)poison <= 0xFF)
			memset(direct_map_addr, poison, PAGE_SIZE);

		free_reserved_page(page);
	}
	if (pages && s)
		pr_info("Freeing %s memory: %ldK\n",
			s, pages << (PAGE_SHIFT - 10));

	return pages;
}
EXPORT_SYMBOL(free_reserved_area);
```

## U-boot镜像自复制分析

U-boot一般存储在NOR Flash或NAND Flash上. 无论从NOR Flash还是从NAND Flash启动, U-boot其本身在启动过程中, 都会从Flash存储介质上加载自身代码到内存, 然后进行重定位, 跳到内存RAM中去执行. U-boot是怎么完成代码自复制的呢? 或者说它是怎样将自身代码从Flash复制到内存的呢? 

在复制自身代码的过程中, 一个主要的疑问就是: U-boot是如何识别自身代码的? 是如何知道从哪里开始复制代码的? 是如何知道复制到哪里停止的? 这个时候我们不得不说起U-boot源码中的一个零长度数组. 

```c
#define __section(S)      __attribute__((__section__(S)))
//sections.c
char __image_copy_start[0] __section(".__image_copy_start");
char __image_copy_end[0] __section(".__image_copy_end");
```
这两行代码的作用是分别定义一个零长度数组，并指示编译器要分别放在`.__image_copy_start`和`.__image_copy_end`这两个section中。

其实就分别代表了U-boot镜像要复制自身镜像的起始地址和结束地址. 无论U-boot自身镜像存储在NOR Flash, 还是存储在NAND Flash上, 只要知道了这两个地址, 我们就可以直接调用相关代码复制. 

链接器在链接各个目标文件时, 会按照链接脚本里各个section的排列顺序, 将各个section组装成一个可执行文件. U-boot的链接脚本U-boot.lds在U-boot源码的根目录下面: 
uboot的链接脚本: 
```shell
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
 . = 0x00000000;
 . = ALIGN(4);
 .text :
 {
  *(.__image_copy_start)
  *(.vectors)
  arch/arm/cpu/armv7/start.o (.text*)
 }
 .__efi_runtime_start : {
  *(.__efi_runtime_start)
 }

 .text_rest :
 {
  *(.text*)
 }
 . = ALIGN(4);
 .rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }
 . = ALIGN(4);
 .data : {
  *(.data*)
 }
 . = ALIGN(4);
 . = .;
 . = ALIGN(4);
 __u_boot_list : {
  KEEP(*(SORT(__u_boot_list*)));
 }
 . = ALIGN(4);
 .efi_runtime_rel_start :
 {
  *(.__efi_runtime_rel_start)
 }
 .efi_runtime_rel : {
  *(.rel*.efi_runtime)
  *(.rel*.efi_runtime.*)
 }
 .efi_runtime_rel_stop :
 {
  *(.__efi_runtime_rel_stop)
 }
 . = ALIGN(4);
 .image_copy_end :
 {
  *(.__image_copy_end)
 }
 .rel_dyn_start :
 {
  *(.__rel_dyn_start)
 }
 .rel.dyn : {
  *(.rel*)
 }
 .rel_dyn_end :
 {
  *(.__rel_dyn_end)
 }
 .end :
 {
  *(.__end)
 }
 _image_binary_end = .;
 . = ALIGN(4096);
 .mmutable : {
  *(.mmutable)
 }
 .bss_start __rel_dyn_start (OVERLAY) : {
  KEEP(*(.__bss_start));
  __bss_base = .;
 }
 .bss __bss_base (OVERLAY) : {
  *(.bss*)
   . = ALIGN(4);
   __bss_limit = .;
 }
 .bss_end __bss_limit (OVERLAY) : {
  KEEP(*(.__bss_end));
 }
}
```

通过链接脚本我们可以看到, `__image_copy_start`和`__image_copy_end`这两个section, 在链接的时候分别放在了代码段.text的前面, 数据段.data的后面, 作为U-boot复制自身代码的起始地址和结束地址. 而在这两个section中, 我们除了放两个零长度数组, 并没有放其他变量. 

在arch/arm/lib/relocate.S中, ENTRY(relocate_code)汇编代码主要完成代码复制的功能.
- ![](assets/Pasted%20image%2020230504235725.png)
- 在这段汇编代码中, 寄存器R1, R2分别表示要复制镜像的起始地址和结束地址, R0表示要复制到RAM中的地址, R4存放的是源地址和目的地址之间的偏移, 在后面重定位过程中会用到这个偏移值. 在汇编代码中: `ldr r1, =__image_copy_start`
- 通过ARM的LDR伪指令, 直接获取要复制镜像的首地址, 并保存在R1寄存器中. 数组名本身其实就代表一个地址, 通过这种方式, U-boot在嵌入式启动的初始阶段, 就完成了自身代码的复制工作: 从Flash复制自身镜像到内存中, 然后进行重定位, 最后跳到内存中执行. 

# 属性声明: aligned

## 地址对齐: aligned

GNU C通过`__attribute__`来声明aligned和packed属性, 指定一个变量或类型的对齐方式. 

这两个属性用来告诉编译器: 
在给变量分配存储空间时, 要按指定的地址对齐方式给变量分配地址. 如果你想定义一个变量, 在内存中以8字节地址对齐, 就可以这样定义:
- `__attribute__((aligned(8))) int a;`
- `int a __attribute__((aligned(8)));`
- `int a __attribute__((aligned(8))) = 1;`
- 错误示范: `int a = 1 __attribute__((aligned(8)));`
	- 通过aligned属性, 可以显式地指定变量a在内存中的地址对齐方式. aligned有一个参数, 表示要按几字节对齐, 使用时要注意, 地址对齐的字节数`必须是2的幂次方`, 否则编译就会出错.

一般情况下, 当我们定义一个变量时, 编译器会按照默认的地址对齐方式, 来给该变量分配一个存储空间地址. 如果该变量是一个int型数据, 那么编译器就会按4字节或4字节的整数倍地址对齐; 如果该变量是一个short型数据, 那么编译器就会按2字节或2字节的整数倍地址对齐; 如果是一个char类型的变量, 那么编译器就会按照1字节地址对齐. 
```c
#include <stdio.h>

int a = 1, b = 2;
char c1 = 3, c2 = 4;

int main (int argc, char *argv[])
{
    printf("a: %p\n",&a); 
    printf("b: %p\n",&b); 
    printf("c1: %p\n",&c1); 
    printf("c2: %p\n",&c2); 
    return 0;
}
```
运行打印如下:
```shell
./aligned
a: 0x559f1a3fe010
b: 0x559f1a3fe014
c1: 0x559f1a3fe018
c2: 0x559f1a3fe019
```

接下来，我们修改一下程序，指定变量c2按4字节对齐:
```c
int a = 1, b = 2;
char c1 = 3;
__attribute__((aligned(4))) char c2 = 4;

int main (int argc, char *argv[])
{
    printf("a: %p\n",&a); 
    printf("b: %p\n",&b); 
    printf("c1: %p\n",&c1); 
    printf("c2: %p\n",&c2); 
    return 0;
}
```
打印:
```shell
a: 0x55e8e3ad9010
b: 0x55e8e3ad9014
c1: 0x55e8e3ad9018
c2: 0x55e8e3ad901c
```
c1, c2 间隔了4个字节, c2的地址为1c, 能被4整除. 
编译器不再分配019结尾的地址, 而是空了3个字节. 在01c结尾的地址分配.

通过aligned属性声明, 虽然可以显式地指定变量的地址对齐方式, 但是也会因边界对齐造成一定的内存空置, 浪费内存资源.

既然地址对齐会造成一定的内存空洞，那么我们为什么还要按照这种对齐方式去存储数据呢？
- 一个主要原因就是：这种对齐设置可以简化CPU和内存RAM之间的接口和硬件设计
- 减少访存次数.

一个32位的计算机系统, 在CPU读取内存时, 硬件设计上可能只支持4字节或4字节倍数对齐的地址访问, CPU每次向内存RAM读写数据时, 一个周期可以读写4字节. 如果我们把一个int型数据放在4字节对齐的地址上, 那么CPU一次就可以把数据读写完毕; 如果我们把一个int型数据放在一个非4字节对齐的地址上, 那么CPU可能就要分两次才能把这个4字节大小的数据读写完毕. 

为了配合计算机的硬件设计, 编译器在编译程序时, 对于一些基本数据类型, 如int, char, short, float等, 会按照其数据类型的大小进行地址对齐, 按照这种地址对齐方式分配的存储地址, CPU一次就可以读写完毕. 虽然边界对齐会造成一些内存空洞, 浪费一些内存单元, 但是在硬件上的设计却大大简化了. 这也是编译器给我们定义的变量分配地址时, 不同类型的变量按照不同字节数地址对齐的主要原因. 

除了int, char, short, float这些基本类型数据, 对于一些复合类型数据, 也要满足地址对齐要求. 

## 结构体的对齐

结构体作为一种复合数据类型, 编译器在给一个结构体变量分配存储空间时, 不仅要考虑结构体内各个基本成员的地址对齐, 还要考虑结构体整体的对齐. 

为了结构体内各个成员地址对齐, 编译器可能会在结构体内填充一些空间; 为了结构体整体对齐, 编译器可能会在结构体的末尾填充一些空间. 

```c
typedef struct st{
    char a;
    int b;
    short c;
}data;
int main (int argc, char *argv[])
{
    data s;
    printf("size: %zd\n",sizeof(s)); 
    printf("a: %p\n",&s.a); 
    printf("b: %p\n",&s.b); 
    printf("c: %p\n",&s.c); 
    return 0;
}
```
```shell
打印如下:
size: 12
a: 0x7ffcd94d25dc
b: 0x7ffcd94d25e0
c: 0x7ffcd94d25e4
```
成员b 为4字节对齐, 编译器给a分配完地址, 空3个字节, 给b分配.

根据结构体的对齐规则, 结构体的整体对齐要按结构体所有成员中最大对齐字节数或其整数倍对齐, 或者说结构体的整体长度要为其最大成员字节数的整数倍, 如果不是整数倍则要补齐. 

该结构体中, 成员最大对齐字节是4字节. 所以 short型后面要补2个字节. 一共是12个字节.

结构体成员按不同的顺序排放, 可能会导致结构体的整体长度不一样, 我们修改一下上面的程序. 
```c
typedef struct st{
    char a;
    short b;
    int c;
}data;
```
打印:
```shell
size: 8
a: 0x7ffed1a00150
b: 0x7ffed1a00152
c: 0x7ffed1a00154
```
short b按2字节对齐, 所以分配到的地址是152结尾. int c是4字节对齐, 地址是154结尾.
整体是2+2+4是8个字节.

现在我们手动修改, 让short b按4字节对齐.
```c
typedef struct st{
    char a;
    short b __attribute__((aligned(4)));
    int c;
}data;
```

打印:
```shell
size: 12
a: 0x7ffe4cd4501c
b: 0x7ffe4cd45020
c: 0x7ffe4cd45024
```
结果很明显了, 不解释了.

我们不仅可以显式指定结构体内某个成员的地址对齐, 也可以显式指定整个结构体的对齐方式. 
```c
typedef struct st{
    char a;
    short b;
    int c;
}__attribute__((aligned(16))) data;
```

打印:
```shell
size: 16
a: 0x7ffcd7fe79b0
b: 0x7ffcd7fe79b2
c: 0x7ffcd7fe79b4
```
a占了2个字节, b 也是2个字节, 剩下的都是c开始的字节. 结构体自身是占8个字节, 而指定结构体整体是16个字节对齐之后, 那么还要补8个字节, 到达16个字节.

## 思考

编译器一定会按照aligned指定的方式对齐吗?

通过这个属性声明, 其实只是建议编译器按照这种大小地址对齐, 但`不能超过编译器允许的最大值`. 

一个编译器, 对每个基本数据类型都有默认的最大边界对齐字节数. 如果超过了, 则编译器只能按照它规定的最大对齐字节数来给变量分配地址. 
```c
char c1 = 3;
__attribute__((aligned(16))) char c2 = 4;

int main (int argc, char *argv[])
{
    printf("c1: %p\n",&c1); 
    printf("c2: %p\n",&c2); 
    return 0;
}
```
指定char型的变量c2以16字节对齐，编译运行结果如下。

```shell
c1: 0x55e8e3ad9010
c2: 0x55e8e3ad9020
```

如果我们继续修改c2变量按`32字节`对齐, 你会发现程序的运行结果`不再有变化`, 编译器仍然分配一个16字节对齐的地址, 这是因为32字节的对齐方式已经超过编译器允许的最大值了.

## 属性声明: packed

aligned属性一般用来增大变量的地址对齐, 元素之间因为地址对齐会造成一定的内存空洞. 而`packed属性则与之相反`, 一般`用来减少地址对齐`, 指定变量或类型使用最可能小的地址对齐方式:

```c
typedef struct st{
    char a;
    short b __attribute__((packed)); 
    int c __attribute__((packed));
} data;

int main (int argc, char *argv[])
{
    data s;
    printf("size: %zd\n",sizeof(s)); 
    printf("a: %p\n",&s.a); 
    printf("b: %p\n",&s.b); 
    printf("c: %p\n",&s.c); 
    return 0;
}
```
我们将结构体的成员b和c使用packed属性声明，就是告诉编译器，尽量使用最可能小的地址对齐给它们分配地址，尽可能地减少内存空洞: 
```shell
./aligned
size: 7
a: 0x7ffda1312ae1
b: 0x7ffda1312ae2
c: 0x7ffda1312ae4
```

通过结果我们看到，结构体内各个成员地址的分配，使用最小1字节的对齐方式，没有任何内存空间的浪费，导致整个结构体的大小只有7字节。

这个特性在底层驱动开发中还是非常有用的:

例如，你想定义一个结构体，封装一个IP控制器的各种寄存器，在ARM芯片中，每一个控制器的寄存器地址空间一般都是连续存在的。如果考虑数据对齐，则结构体内就可能有空洞，就和实际连续的寄存器地址不一致。使用packed可以避免这个问题，结构体的每个成员都紧挨着，依次分配存储地址，这样就避免了各个成员因地址对齐而造成的内存空洞。
```c
typedef struct st{
    char a;
    short b; 
    int c; 
} __attribute__((packed)) data;

```

我们也可以对整个结构体添加packed属性，这和分别对每个成员添加packed属性效果是一样的。修改结构体后，重新编译程序，运行结果和上面程序的运行结果相同：结构体的大小为7，结构体内各成员地址相同。

## 内核中的aligned、packed声明

在Linux内核源码中, 我们经常看到aligned和packed一起使用, 即对一个变量或类型同时使用aligned和packed属性声明.

这样做的好处是: 既避免了结构体内各成员因地址对齐产生内存空, 又指定了整个结构体的对齐方式. 
```c
typedef struct st{
    char a;
    short b; 
    int c; 
} __attribute__((packed,aligned(8))) data;
int main (int argc, char *argv[])
{
    data s;
    printf("size: %zd\n",sizeof(s)); 
    printf("a: %p\n",&s.a); 
    printf("b: %p\n",&s.b); 
    printf("c: %p\n",&s.c); 
    return 0;
}
```
程序运行结果如下。
```shell
size: 8
a: 0x7ffde3b37320
b: 0x7ffde3b37321
c: 0x7ffde3b37323
成员都是1字节对齐, 但整个结构体是8字节对齐.
```


在上面的程序, 结构体data虽然使用了packed属性声明, 结构体内所有成员所占的存储空间为7字节, 但是我们同时使用了aligned(8)指定结构体按8字节地址对齐, 所以编译器要在结构体后面填充1字节，这样整个结构体的大小就变为8字节, 按8字节地址对齐. 

# 属性声明: format

## 变参函数的格式检查

GNU通过`__attribute__`扩展的format属性, 来指定`变参函数的参数格式检查`.

使用方法:
- `__attribute__(( format(archetype, string-index, first-to-check))); 
- `void LOG(const char *fmt, ...) __attribute__((format(printf,1,2))); 

在一些商业项目中, 我们经常会实现一些自定义的打印调试函数, 甚至实现一个独立的日志打印模块. 

这些自定义的打印函数往往是变参函数, 用户在调用这些接口函数时参数往往不固定, 那么编译器在编译程序时, 怎么知道我们的参数格式对不对呢? 如何对我们传进去的实参做格式检查呢?

因为我们实现的是变参函数, 参数的个数和格式都不确定, 所以编译器表示压力很大, 不知道该如何处理. 

`__attribute__`的`format属性`这时候就派上用场了. 

在上面的示例代码中, 我们定义一个`LOG()`变参函数, 用来实现日志打印功能. 编译器在编译程序时, 如何检查LOG()函数的参数格式是否正确呢? 方法其实很简单, 通过给`LOG()`函数添加`__attribute__((format(printf,1,2)))`属性声明就可以了. 

这个属性声明告诉编译器: 你知道printf()函数不? 你怎么对printf()函数进行参数格式检查的, 就按照同样的方法, 对LOG()函数进行检查. 

属性`format(printf, 1, 2)`有3个参数: 
- 第1个参数printf是告诉编译器, 按照printf()函数的标准来检查;
- 第2个参数表示在LOG()函数`所有的参数列表中格式字符串`的位置索引;
- 第3个参数是告诉编译器`要检查的参数的起始位置`.

通过format(printf, 1, 2) 属性声明, 告诉编译器: LOG()函数的参数, 其格式字符串的位置在所有参数列表中的索引是1, 即第一个参数; 要编译器帮忙检查的参数, 在所有的参数列表里索引是2. 知道了LOG()参数列表中格式字符串的位置和要检查的参数位置, 编译器就会按照检查printf的格式打印一样, 对LOG()函数进行参数检查了. 

举例:
`printf("size = %d %d %d \n", a,b,c);`
- printf中, 第一个参数是格式字符串, 对应的是`format(printf, 1, 2)`中的`1`.
- printf中, %d代表的占位符, 其实际参数, 是第二个参数a, 即参数的起始位置是2. 对应`format(printf, 1, 2)`中的2.

格式字符串:
- 如果一个字符串中含有格式匹配符, 那么这个字符串就是格式字符串. 
- 如格式字符串`"I have %d apple \n"`里面含有格式匹配符%d, 我们也可以叫它占位符. 打印的时候, 后面变参的值会代替这个占位符, 在屏幕上显示出来. 

`void LOG(const char *fmt, ...) __attribute__((format(printf,1,2)));`

- `LOG("I have %d apple %d banana \n", 5, 6);`
- 上面的声明就是, 按照printf的参数检查方式来检查LOG里的参数就行了.
	- LOG里的第1个参数, 就是字符串格式
	- 第2个参数, 就是实际参数的起始位置.

- `LOG("I have %d apple \n", 5);`
	- 在这个LOG()函数中有2个参数, 第1个参数是格式字符串，
	- 第2个参数是要打印的一个常量值5, 用来匹配格式字符串中的占位符. 

我们也可以把LOG函数定义为以下形式:
- `void LOG(int n, char *fmt, ...) __attribute__((format(printf,2,3)));`
- 在这个函数定义中, 多了一个参数n, 格式字符串在参数列表中的位置发生了变化(在所有的参数列表中, 索引由1变成了2), 要检查的第一个变参的位置也发生了变化(索引从原来的2变成了3). 那么我们使用format属性声明时. 就要写成format(printf, 2, 3)的形式了. 

## 变参函数的设计与实现

对于变参函数，编译器或操作系统一般会提供一些宏给程序员使用，用来解析函数的参数列表，这样程序员就不用自己解析了，直接调用封装好的宏即可获取参数列表。编译器提供的宏有以下3种。
- va_list: 定义在编译器头文件stdarg.h中, 如`typedef char *va_list;`
- va_start(fmt, args): 根据参数args的地址, 获取args后面参数的地址, 并保存在fmt指针变量中. 
- va_end(args): 释放args指针, 将其赋值为NULL. 

```c
看一下linux 4.4内核 中的定义:
#ifndef _VALIST
#define _VALIST
typedef char *va_list;
#endif

typedef int s32;
typedef s32 acpi_native_int;

#define _AUPBND  (sizeof(acpi_native_int) - 1)
#define _ADNBND  (sizeof(acpi_native_int) - 1)

#define  _bnd(x, bnd)   (((sizeof(x))+(bnd)) & (~(bnd)))
#define  va_arg(ap, T)  (*(T *)(( (ap) += (_bnd(T, _ADNBND) )))
#define  va_end(ap)     (ap = (va_list) NULL)
#define  va_start(ap,A) (void)((ap)= (char *)&(A) + (_bnd (A,_AUPBND))))
复杂的宏都是为了保证安全, 不出叉子. 保证偏移量总是对的.
```

上面使用编译器提供的三个宏，省去了解析参数的麻烦。但打印的时候，我们还必须自己实现。

我们继续改进，使用vprintf()函数完成打印功能。vprintf()函数的声明在stdio.h头文件中:
```c
CRTIMP int __cdecl __MINGW_NOTHROW \
	vprintf(const char*, __VALIST);
```

vprintf()函数有两个参数：一个是格式字符串指针，一个是变参列表。
```c
#include<stdio.h>
#include<stdarg.h>

void my_print(char *fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	vprintf(fmt, args);
	va_end(args);
}

int main (int argc, char *argv[])
{
    my_print("%d %d %d %d\n", 1,2,3,4);
    return 0;
}
```
结果就打印: 1 2 3 4 了.

上面的myprintf()函数基本上实现了和printf()函数相同的功能：支持变参，支持多种格式的数据打印。接下来，我们需要对其添加format属性声明，让编译器在编译时，像检查printf()一样，检查myprintf()函数的参数格式。

```c
void __attribute__((format(printf,1,2))) my_print(char *fmt,...)
{
    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
}
```

然后我们就可以搞一个log函数:
```c
#define DEBUG
void __attribute__((format(printf,2,3))) LOG(int k,char *fmt,...)
{
#if DEBUG
    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
#endif
}
```

Linux内核里也有:
```c
__attribute__((format(printf,1,2))) void mpsslog(char *format, ...);
```
不同子系统用的log接口都不一样.

```c
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#define DBG_INFO 1
#define DBG_MAP  2
#define DBG_REG  4
#define DBG_ADV  8
#define DBG_CAL  16

__attribute__((format(printf, 4, 5)))
void _tda_printk(struct tda18271_priv *state, const char *level,
		 const char *func, const char *fmt, ...);

#define tda_printk(st, lvl, fmt, arg...)			\
	_tda_printk(st, lvl, __func__, fmt, ##arg)

#define tda_dprintk(st, lvl, fmt, arg...)			\
do {								\
	if (tda18271_debug & lvl)				\
		tda_printk(st, KERN_DEBUG, fmt, ##arg);		\
} while (0)

#define tda_info(fmt, arg...)	pr_info(fmt, ##arg)
#define tda_warn(fmt, arg...)	tda_printk(priv, KERN_WARNING, fmt, ##arg)
#define tda_err(fmt, arg...)	tda_printk(priv, KERN_ERR,     fmt, ##arg)
#define tda_dbg(fmt, arg...)	tda_dprintk(priv, DBG_INFO,    fmt, ##arg)
#define tda_map(fmt, arg...)	tda_dprintk(priv, DBG_MAP,     fmt, ##arg)
#define tda_reg(fmt, arg...)	tda_dprintk(priv, DBG_REG,     fmt, ##arg)
#define tda_cal(fmt, arg...)	tda_dprintk(priv, DBG_CAL,     fmt, ##arg)

#define tda_fail(ret)							     \
({									     \
	int __ret;							     \
	__ret = (ret < 0);						     \
	if (__ret)							     \
		tda_printk(priv, KERN_ERR,				     \
			   "error %d on line %d\n", ret, __LINE__);	     \
	__ret;								     \
})
```

```c
#include  <stdio.h>
#include  <stdarg.h>

#define ERR_LEVEL 1
#define WARN_LEVEL 2
#define INFO_LEVEL 3

#define DEBUG_LEVEL 3
/*
 * 0 关闭打印
 * 1 只打印错误信息
 * 2 打印警告和错误
 * 3 打印所有信息
 */

void __attribute__((format(printf,1,2))) INFO(char *fmt, ...)
{
	#if (DEBUG_LEVEL >= INFO_LEVEL)
	va_list args;
	va_start(args, fmt);
	vprintf(fmt,args);
	va_end(args);
	#endif
}

void __attribute__((format(printf,1,2))) WARN(char *fmt, ...)
{
	#if (DEBUG_LEVEL >= WARN_LEVEL)
	va_list args;
	va_start(args, fmt);
	vprintf(fmt,args);
	va_end(args);
	#endif
}

void __attribute__((format(printf,1,2))) ERR(char *fmt, ...)
{
	#if (DEBUG_LEVEL >= ERR_LEVEL)
	va_list args;
	va_start(args, fmt);
	vprintf(fmt,args);
	va_end(args);
	#endif
}

```
在上面的程序中，我们封装了3个打印函数：INFO()、WARN()和ERR()，分别打印不同优先级的日志信息。在实际调试中，我们可以根据自己需要的打印信息，设置合适的打印等级，就可以分级控制这些打印信息了.

# 属性声明: const

使用方法
- `int func( int a) __attribute__((const));`

作用:
- 优化程序
- 编译的时候需要配合优化选项.

```c
int __attribute__((const)) square(int n)
{
    printf("square:\n");
    return n*n;
}

int main(void)
{
    int sum=0;
    for(int i=0;i<10;i++)
        sum +=square(4);
    printf("sum = %d\n",sum);
    return 0;
}
```
优化过之后: 
square 只执行一次.

用的不多. 知道就行. 内核也有用到, 见到知道就行了.

# 属性声明: weak

## 强符号和弱符号

之前说过的编译 链接过程.

GNU C通过weak属性声明, 可以将一个强符号转换为弱符号. 使用方法如下. 
```c
void __attribute__((weak)) func(void);
int num __attribute__((weak));
```

- 强符号：函数名，初始化的全局变量名。
- 弱符号：未初始化的全局变量名。

在一个工程项目中，对于相同的全局变量名、函数名，我们一般可以归结为下面3种场景。
- 强符号+强符号 -> 冲突报错
- 强符号+弱符号 -> 强
- 弱符号+弱符号 -> 选size大的

一般来讲，不建议在一个工程中定义多个不同类型的同名弱符号，编译的时候可能会出现各种各样的问题. 也不能同时定义两个同名的强符号，否则就会报重定义错误。我们可以使用GNU C扩展的weak属性，将一个强符号转换为弱符号。

这部分之前学编译的时候已经挺细的了.

```c
//func.c
int a = 1;
int b;
void func()
{
	printf("func: a = %d\n", a);
	printf("func: b = %d\n", b);
}

// main.c
int a;
int b = 2;
void func();
int main()
{
	printf("main: a = %d\n", a);
	printf("main: b = %d\n", b);
	func();
	return 0;
}
结果打印:
main: a = 1
main: b = 2
func: a = 1
func: b = 2
```

然后就可以对不同源文件的 a b 和 func函数 的符号强弱进行改变.

## 强引用与弱引用

链接处理:
- 强引用: 未找到定义时, 会报未定义错误
- 弱引用: 未找到定义时, 不会报错, 会默认设置为0或者一个特殊值  
	- 运行时会报错, 函数地址是0 就segmentfault了.
	- 所以对于弱符号, 先判断函数地址是不是0, 应该就安全了.

## 函数的强符号与弱符号

链接器对于同名函数冲突，同样遵循相同的规则。函数名本身就是一个强符号，在一个工程中定义两个同名的函数，编译时肯定会报重定义错误。但我们可以通过weak属性声明，将其中一个函数名转换为弱符号。

## 弱符号的用途

在一个源文件中引用一个变量或函数, 当编译器只看到其声明, 而没有看到其定义时, 编译器一般编译不会报错: 编译器会认为这个符号可能在其他文件中定义. 在链接阶段, 链接器会到其他文件中找这些符号的定义, 若未找到, 则报未定义错误. 

当函数被声明为一个弱符号时, 会有一个奇特的地方: 当链接器找不到这个函数的定义时, 也不会报错. 编译器会将这个函数名, 即弱符号, 设置为0或一个特殊的值. 只有当程序运行时, 调用到这个函数, 跳转到零地址或一个特殊的地址才会报错, 产生一个内存错误.
- ![](assets/Pasted%20image%2020230505200036.png)
	- ![](assets/Pasted%20image%2020230505200046.png)

为了防止函数运行出错，我们可以在运行这个函数之前，先进行判断，看这个函数名的地址是不是0，然后决定是否调用和运行，这样就可以避免段错误了。
- ![](assets/Pasted%20image%2020230505200124.png)

函数名的本质就是一个地址，在调用func()之前，我们先判断其是否为0，如果为0，则不调用，直接跳过。你会发现，通过这样的设计，即使func()函数没有定义，整个工程也能正常编译、链接和运行！

弱符号的这个特性，在库函数中应用得很广泛。如你在开发一个库时，基础功能已经实现，有些高级功能还没实现，那么你可以将这些函数通过weak属性声明转换为一个弱符号。通过这样设置，即使还没有定义函数，我们在应用程序中只要在调用之前做一个非零的判断就可以
了，并不影响程序的正常运行。等以后发布新的库版本，实现了这些高级功能，应用程序也不需要进行任何修改，直接运行就可以调用这些高级功能。

# 属性声明: alias

GNU C扩展了一个alias属性, 这个属性很简单, 主要用来给函数定义一个别名. 
- ![](assets/Pasted%20image%2020230505200331.png)

- 用法:
	- `函数声明 __attribute__((alias("别名")));`
	- 然后调用别名跟调用原名是一样的.

通过alias属性声明, 我们可以给__f()函数定义一个别名f(), 以后如果想调用__f()函数, 则直接通过f()调用即可. 

在Linux内核中, 你会发现alias有时会和weak属性一起使用. 如有些函数随着内核版本升级, 函数接口发生了变化, 我们可以通过alias属性对这个旧的接口名字进行封装, 重新起一个接口名字. 

# 属性声明: constructor & destructor

这东西类似C++的构造函数和析构函数, gnu c扩展借鉴了这个机制, 扩充了C标准.

使用方法:
- `__attribute__((constructor)) int init_func(void);`
- `__attribute__((destructor)) int exit_func(void);`

用的话, 也不知道哪里真正会用到. 但是知道 有个印象就行. 见到能认识就好了.

当一个函数被属性声明为 这俩属性的时候, 其运行与之前就不同了.
- 属性声明为constructor时, 即使你不显式调用, 进入main函数之前, 也会自动调用它. 
- 属性声明为destructor时, 即使你不显式调用, 在再出main函数后, 也会自动执行它.

```c
#include <stdio.h>

__attribute__((constructor)) void init_func()
{
    puts("init_func");
}

__attribute__((destructor)) void exit_func()
{
    puts("exit_func");
}

int main (int argc, char *argv[])
{
    puts("hello world");
    return 0;
}

打印如下:
./constructor
init_func
hello world
exit_func
```

回忆:
- 程序的真正入口是`_start` 
- 跳到main之前, 需要初始化C语言的运行环境.
- 退出main之后, 会把main 的返回值 交给exit()函数.

# 内联函数

## 属性声明: noinline

与内联函数相关的两个属性: noinline和always_inline. 这两个属性的用途是告诉编译器, 在编译时, 对我们指定的函数内联展开或不展开. 使用方法:
- `static inline __attribute__((noinline)) int func();`
- `static inline __attribute__((always_inline)) int func();`

- 一个使用inline声明的函数被称为内联函数, 内联函数一般前面会有static和extern修饰. 
- 使用inline声明一个内联函数, 和使用关键字register声明一个寄存器变量一样, 只是`建议`编译器在编译时内联展开. 
- 使用关键字register修饰一个变量, 只是建议编译器在为变量分配存储空间时, 将这个变量放到寄存器里, 这会使程序的运行效率更高.
- 编译器会不会放, 这得视具体情况而定, 编译器要根据寄存器资源是否紧张, 这个变量的类型及是否频繁使用来做权衡. 
- 同样, 当一个函数使用inline关键字修饰时, 编译器在编译时也`不一定会`内联展开. 编译器也会根据实际情况, 如函数体大小, 函数体内是否有循环结构, 是否有指针, 是否有递归, 函数调用是否频繁来做决定. 
	- 如GCC编译器, 一般是不会对函数做内联展开的, 只有当编译优化等级开到-O2以上时, 才会考虑是否内联展开. 
- 但是在我们使用noinline和always_inline对一个内联函数作显式属性声明后, 编译器的编译行为就变得确定了: 使用noinline声明, 就是告诉编译器不要展开; 使用always_inline属性声明, 就是告诉编译器要内联展开. 

## 什么是内联函数

说起内联函数, 又不得不说函数`调用开销`. 一个函数在执行过程中, 如果需要调用其他函数, 则一般会执行下面的过程. 
- 保存当前函数现场
- 跳到调用函数执行
- 恢复当前函数现场
- 继续执行当前函数

如有一个ARM程序, 在main()函数中对一些数据进行处理, 运算结果暂时保存在R0寄存器中. 接着调用另外一个func()函数, 调用结束后, 返回main()函数继续处理数据. 如果我们在func ()函数中要使用R0这个寄存器(用于保存函数的返回值), 就会改变R0寄存器中的值, 那么就篡改了main ()函数中的暂存运算结果. 当我们返回main ()函数继续进行数据处理时, 最后的结果肯定不正确. 

那么怎么办呢? 很简单, 在跳到func()函数执行之前, 先把R0寄存器的值保存到堆栈中, func()函数执行结束后, 再将堆栈中的值恢复到R0寄存器, 这样main()函数就可以继续执行了, 就像什么事情都没有发生过一样. 

现在的计算机系统, 无论什么架构和指令集, 一般都采用这种方法. 这种方法虽然麻烦了点, 但至少能解决问题, 无非就是需要不断地保存现场, 恢复现场, 这就是函数调用带来的开销. 

对于一般的函数调用, 这种方法是没有问题的. 但对于一些极端情况, 例如, 一个函数短小精悍, 函数体内只有一行代码, 在程序中被大量频繁地调用. 如果每次调用, 都不断地保存现场, 执行时却发现函数只有一行代码, 接着又要恢复现场, 则来回折腾的开销比较大, 性价比不高. 

函数调用也是如此:
- 有些函数短小精悍, 而且调用频繁, 调用开销大, 算下来性价比不高, 这时候我们就可以将这个函数声明为内联函数. 
- 编译器在编译过程中遇到内联函数, 像宏一样, 将内联函数直接在调用处展开, 这样做就减少了函数调用的开销: 直接执行内联函数展开的代码, 不用再保存现场和恢复现场. 

## 内联函数与宏

那我为什么不直接定义一个宏, 非要用一个内联函数呢?

与宏相比, 内联函数有以下优势:
- 参数类型检查: 内联函数虽然具有宏的展开特性, 但其`本质仍是函数`, 在`编译过程`中, 编译器仍可以`对其进行参数检查`, 而宏不具备这个功能.  (宏展开太无脑)
- 便于调试: 函数支持的调试功能有断点, 单步等, 内联函数同样支持.
- 返回值: 内联函数有返回值, 返回一个结果给调用者. 这个优势是`相对于ANSI C`说的, 因为现在宏也可以有返回值和类型了, 如前面使用语句表达式定义的宏.
- 接口封装: 有些内联函数可以用来封装一个接口, 而宏不具备这个特性.

## 编译器对内联函数的处理

前面提到, 编译器不一定会对这个函数做内联展开。编译器也要根据实际情况进行评估，权衡展开和不展开的利弊，并最终决定要不要展开。

内联函数并也有一些缺点.
- 降低cache命中率, 取指效率可能会降低, 执行速度慢
- 内联函数会增大程序的体积
	- 如果在一个文件中多次调用内联函数, 多次展开, 那么整个程序的体积就会变大, 在一定程度上会降低程序的执行效率. 
- 函数的作用之一就是提高代码的复用性. 我们将常用的一些代码或代码块封装成函数，进行模块化编程，可以减轻软件开发工作量。
- 内联函数往往又降低了函数的复用性。
	- 编译器在对内联函数做展开时，除了检测用户定义的内联函数内部是否有指针、循环、递归，还会在函数执行效率和函数调用开销之间进行权衡。
- 一般来讲, 判断对一个内联函数是否做展开, 从程序员的角度出发, 主要考虑如下因素: 
	- 函数体积小
	- 函数体内无指针赋值、递归、循环等语句
	- 调用频繁

当我们认为一个函数体积小，而且被大量频繁调用，应该做内联展开时，就可以使用static inline关键字修饰它。但编译器不一定会做内联展开，如果你想明确告诉编译器一定要展开，或者不展开，就可以使用noinline或always_inline对函数做一个属性声明。

```c
static inline __attribute__((always_inline)) int func(int a)
{
	return a+1;
}
static inline void print_num(int a)
{
	printf("%d \n", a);	
}
int main()
{
	int i;
	i = func(3);
	print_num(10);
	return 0;
}
```

在这个程序中, 我们分别定义两个内联函数: func()和print_num(), 然后使用always_inline对func()函数进行属性声明. 编译这个源文件, 并对生成的可执行文件a.out做反汇编处理, 其汇编代码如下. 
- ![](assets/Pasted%20image%2020230505220642.png)
	- 通过反汇编代码可以看到, 因为我们对func()函数作了always_inline属性声明, 所以在编译过程中, 在调用func()函数的地方. 编译器会将func()函数在调用处直接展开. 
		- 在`<main>`中, 从`mov r3,#3` 到 `str r3, [fp, #-12]` 这一部分.

而对于print_num()函数, 虽然我们对其做了内联声明, 但编译器并没有对其做内联展开, 而是把它当作一个普通函数对待. 

- 还有一个需要注意的细节是:
当编译器对内联函数做展开处理时, 会直接在调用处展开内联函数的代码, 不再给func()函数本身生成单独的汇编代码. 因为编译器在所有调用该函数的地方都做了内联展开, 没必要再去生成单独的函数汇编指令. 

在这个例子中, 我们发现编译器就没有给func()函数本身生成单独的汇编代码, 编译器只给print_num()函数生成了独立的汇编代码. 

## 内联函数为什么定义在头文件中

在Linux内核中, 你会看到大量的内联函数被定义在头文件中, 而且常常使用static修饰. 

为什么inline函数经常使用static修饰呢? 这个问题在网上也讨论了很久, 听起来各有道理, 从C语言到C++, 甚至有人还拿出了Linux内核作者Linus关于static inline的解释.
- ![](assets/Pasted%20image%2020230505221313.png)

我们可以这样理解: 内联函数为什么要定义在头文件中呢? 因为它是一个内联函数, 可以像宏一样使用, 任何想使用这个内联函数的源文件, 都不必亲自再去定义一遍, 直接包含这个头文件, 即可`像宏一样使用`. 

那么为什么还要用static修饰呢? 因为我们使用inline定义的内联函数, 编译器不一定会内联展开, 那么当一个工程中多个文件都包含这个内联函数的定义时, 编译时就有可能报重定义错误. 而使用static关键字修饰，则可以将这个函数的作用域限制在各自的文件内, 避免重定义错误的发生.

# 属性声明: mode

作用: 
- 显式声明一个数据类型的大小

使用示例:
- `typedef int s8 __attribute__((mode(QI)));`
- `typedef unsigned int us8 __attribute__((mode(QI)));`

不同平台的编译器, 对于同一个数据类型, 分配的内存空间可能不一样. 依赖具体的硬件平台和编译器环境.

我们就可以定义一个新的数据类型, 同时用mode属性来确定它的大小.

mode属性参数:
- ![](assets/Pasted%20image%2020230505221935.png)

那么`typedef int s8 __attribute__((mode(QI)));`  s8就相当于是有符号数的8比特 数据类型.
us8 就是无符号的8比特 数据类型.

```c
typedef int s8 __attribute__((mode(QI)));
typedef int s16 __attribute__((mode(HI)));
typedef int s32 __attribute__((mode(SI)));
typedef int s64 __attribute__((mode(DI)));
  
typedef unsigned int us8 __attribute__((mode(QI)));
typedef unsigned int us16 __attribute__((mode(HI)));
typedef unsigned int us32 __attribute__((mode(SI)));
typedef unsigned int us64 __attribute__((mode(DI)));
  
typedef float f32 __attribute__((mode(SF)));
typedef float f64 __attribute__((mode(DF)));

int main(void)
{
	s8 i;
	printf("i: %d\n",sizeof(i));
	printf("%d\n",sizeof(s8));
    printf("%d\n",sizeof(s16));
    printf("%d\n",sizeof(s32));
    printf("%d\n",sizeof(s64));
  
    printf("%d\n",sizeof(us8));
    printf("%d\n",sizeof(us16));
    printf("%d\n",sizeof(us32));
    printf("%d\n",sizeof(us64));
    printf("%d\n",sizeof(f32));
    printf("%d\n",sizeof(f64));
    return 0;
}
```

# 属性声明: noreturn

作用:
- 修饰一个函数, 没有返回值, 以消除warning.

使用示例
- `void func( int ) __attribute__((noreturn));`

exit 和 return 的区别:
- exit 退出当前所在进程.
	- os加载器会fork一个子进程, 把父进程的内容 cow写时复制到子进程. 如果是从子进程的main函数return退出的, 那么os会调用exit来收拾残局.
- return  退出当前函数.

有时候在分支处理的时候, 遇到错误直接关掉进程, 而不是从main函数退出. 如果是在一个有返回值的函数里直接退出进程, 那就会报warning. 看个例子:

```c
#include<stdio.h>
#include<stdlib.h>
void __attribute__((noreturn)) cac_exit()
{
    exit(1);
}
int cac(int num)
{
    if(num < 0)
        cac_exit();
    else
        return 5 * num;
} 

int main(void)
{
    int money = 0;
    money = cac(10);
    printf("Money = %d\n",money);
    return 0;
}
```
不加属性声明的看warning:
```shell
gcc -Wall noreturn.c -o noreturn

noreturn.c: In function ‘cac’:
noreturn.c:13:1: warning: control reaches end of non-void function [-Wreturn-type]
   13 | }
      | ^
```
- ![](assets/Pasted%20image%2020230505224442.png)
	- 装的插件也会提醒会有warning 虽然是clang 但跟gcc差别不大.

加上上面的`__attribute__((noreturn)) ` warning就没了.
- ![](assets/Pasted%20image%2020230505224544.png)

# 属性声明: used & unused

作用: 
- 消除warning
- 修饰变量和函数

你定义了一个变量, 但是你没有使用过它, 就会报warning说你定义变量, 但没用它.

使用示例:
- `register int reg asm(“r0”) __attribute__((used));`
- `static void func(void) __attribute__((used, section(".text")));`
	- 告诉编译器, 我的func函数一定用的到, 你务必给我把这个函数放到目标文件的.text段.

- `static __attribute__((unused)) int a;`
	- 告诉编译器, a可能用不到, 你不要报warning了.
- `static int func(void) __attribute__((unused));`
	- 这个函数可能用不到, 别报warning.
- `int fun(__attribute__((unused)) int a, int b);` 
	- 参数 a 可能用不到, 你别警告.

