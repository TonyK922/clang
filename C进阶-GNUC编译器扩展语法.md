先看一些Linux内核代码:
- ![](assets/Pasted%20image%2020230504175525.png)
- ![](assets/Pasted%20image%2020230504175603.png)
- ![](assets/Pasted%20image%2020230504175613.png)

这些就是GNU C的扩展语法.

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

## 零长度数组

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

内核中的零长度数组

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


## 属性声明: section

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

>属性声明：section

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

我们给函数
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

>Linux内核驱动中的`__init`宏

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