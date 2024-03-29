这部分主要是针对c语言运行时的. 之前的编译, 链接, 安装, 执行是c语言的编译时. 

程序在运行过程中，其实还有一些细节值得我们继续研究：我们在函数内定义的局部变量是存储在哪里的？如何访问它们？可以像全局变量一样通过变量名访问吗？我们使用malloc/free申请的内存，又是在内存的什么地方？

内存中有专门的堆栈空间, 函数的局部变量是保存在栈中的, 而我们使用malloc申请的动态内存则是在堆空间中分配的. 它们是程序运行时比较特殊的两块内存区域: 一块由系统维护, 一块由用户自己申请和释放. 
- ![](assets/Pasted%20image%2020230502184553.png)

# 程序运行的抽象: 进程

在Shell终端下编译运行上面的程序，并使用pstree命令查看进程树:
- ![](assets/Pasted%20image%2020230502184656.png)
	- Shell虚拟终端bash本身也是以进程的形式运行的, 进程PID为11527. 当我们在Shell交互环境下运行./hello时, bash会解析我们的命令和参数, 调用fork创建一个子进程, 接着调用exec()函数将hello可执行文件的代码段, 数据段加载到内存, 替换掉子进程的代码段和数据段. 然后bash会解析我们在交互环境下输入的参数, 将解析的参数列表argv传递给main, 最后跳到main()函数执行. 
	- 当我们使用pstree命令查看bash的进程树时也是如此, pstree本身也变成了bash的一个子进程.

在Linux系统中, 每个进程都使用一个task_struct结构体表示, 各个task_struct构成一个链表, 由操作系统的调度器管理和维护, 每一个进程都会接受操作系统的任务调度, 轮流占用CPU去运行. 只要轮换的速度足够快, 就会让你有种错觉: 感觉所有的程序在同时运行. 在Linux环境下, 一个可执行文件的加载执行过程如图.
- ![](assets/Pasted%20image%2020230502184930.png)
	- 程序是安装在磁盘上某个路径下的二进制文件，而进程则是一个程序运行的实例：操作系统会从磁盘上加载这个程序到内存，分配相应的资源、初始化相关的环境，然后调度运行。
	- 一个进程实例不仅包括汇编指令代码, 数据, 还包括进程上下文环境, CPU寄存器状态, 打开的文件描述符、信号、分配的物理内存等相关资源。

在一个进程的地址空间中, 代码段, 数据段, BSS段在程序加载运行后, 地址就已经固定了, 在整个程序运行期间不再发生变化, 这部分内存一般也称为静态内存. 
而在程序中使用malloc申请的内存, 函数调用过程中的栈在程序运行期间则是不断变化的, 这部分内存一般也称为动态内存. 用户使用malloc申请的内存一般被称为堆内存(heap), 函数调用过程中使用的内存一般被称为栈内存(stack). 

# Linux环境下的内存管理

堆栈内存不是仅靠程序本身来维护的, 而是由操作系统, 编译器, CPU, 物理内存相互配合实现的.

## Linux进程内存映像

虚拟地址空间:
- 在Linux环境下运行的程序, 在编译时`链接的起始地址都是相同的`, 而且是一个`虚拟地址`. 
- Linux操作系统需要`CPU内存管理单元`的支持才能运行, Linux内核通过`页表和MMU硬件`来管理内存, 完成虚拟地址到物理地址的转换, 内存读写`权限管理`等功能. 
- 可执行文件在运行时, 加载器将可执行文件中的不同section加载到内存中读写权限不同的区域, 如代码段, 数据段, .bss段, .rodata段等. 
	- ![](assets/Pasted%20image%2020230502190228.png)
	- MMAP区域, 动态共享库就是使用这片地址空间的.

## Linux进程内存空间

- 在非裸机的计算机上运行的程序主要分为两种: 操作系统(内核)和应用程序. 
- 每一个应用程序进程都有4GB大小的虚拟地址空间. 为了系统的安全稳定, 0到4GB的虚拟地址空间一般分为两部分: 用户空间和内核空间. 
- 到3GB地址空间给应用程序使用, 而操作系统一般运行在3到4GB内核空间. 
- 通过内存权限管理, 应用程序没有权限访问内核空间, 只能通过中断或系统调用来访问内核空间, 这在一定程度上保障了操作系统核心代码的稳定运行. 
- 随着硬件发展, 导致Linux内核镜像运行时需要的地址空间也越来越大. 在很多处理器平台下, 0到2G的地址空间给用户, 2G到4G的空间给内核.
- 所有用户进程共享内核地址空间, 但独享各自的用户地址空间. 
	- ![](assets/Pasted%20image%2020230502191058.png)
	- ![](assets/Pasted%20image%2020230502191107.png)

## Linux进程内存映像

在Linux环境下, 虽然所有的程序编译时使用相同的链接地址, 但在程序运行时, 相同的虚拟地址会通过MMU转换, 映射到不同的物理内存区域, 各个可执行文件被加载到内存不同的物理页上. 

每个进程都有各自的页表, 用来记录各自进程中虚拟地址到物理地址的映射关系.

地址映射
- 虚拟地址通过页表/TLB映射到物理内存
- 页表由OS维护, 记录虚拟地址到物理地址的映射关系
- 通过页表还设置内存权限: 读, 写, 可执行
	- ![](assets/Pasted%20image%2020230502191220.png)
		- 通过这种地址管理, 每个进程都可以独享一份独立的, 私有的3GB用户空间.
		- 编译器在编译程序时，不用考虑每个程序在实际物理内存中的地址分配问题。
		- 通过内存读写权限管理，可以保护每个进程的空间不被其他进程破坏，从而保障系统的安全运行。

- 地址转换:
	- ![](assets/Pasted%20image%2020230502191904.png)

内存管理:
为什么要使用虚拟内存?
- 避免使用物理内存带来的弊端
- 为每个进程提供一个独立的, 私有的地址空间
- 保护每个进程的空间不被其它进程破坏
- 内存读写权限管理, 保障系统的安全运行

# 栈的管理

## 栈的作用

栈是C语言运行的基础, 离开了栈, C语言就无法运行: 
- 函数参数
- 局部变量
- 函数返回值
- 编译器生成的临时变量
	- ![](assets/Pasted%20image%2020230502192225.png)

在很多嵌入式系统的启动代码中, 你会看到: 系统一上电开始运行的都是汇编代码, 在跳到第一个C语言函数运行之前, 都要先初始化栈空间. 

## 栈的初始化

栈初始化
- DDR/SDRAM/SRAM初始化
- 初始化栈指针

不同处理器的栈指针
- ARM：SP寄存器(R13)、FP(R11)
- X86：ESP(栈顶指针)、EBP(栈底指针)

栈的初始化其实就是`栈指针SP的初始化`. 在系统启动过程中, 内存初始化后, 将栈指针指向内存中的一段空间, 就完成了栈的初始化, 栈指针指向的这片内存空间被称为栈空间. 不同的处理器一般都会使用专门的寄存器来保存栈的起始地址, X86处理器一般使用ESP(栈顶指针)和EBP(栈底指针)来管理堆栈, 而ARM处理器则使用R13寄存器(SP)和R11寄存器(FP)来管理堆栈.

## 栈的起始地址

在栈的初始化过程中, 栈在内存中的起始地址还是有点讲究的. ARM处理器使用的是`满递减栈`, 在Linux环境下, 栈的起始地址一般就是进程用户空间的最高地址, 紧挨着内核空间, 栈指针从高地址往低地址增长. 

为了防止黑客栈溢出攻击, 新版本的Linux内核一般会将栈的起始地址设置成随机的, 每次程序运行, 栈的初始化起始地址都会基于用户空间的最高地址有一个随机的偏移, 每次栈的起始地址都不一样. 
- ![](assets/Pasted%20image%2020230502192922.png)
	- 栈初始化后, 栈指针就指向了这片栈空间的栈顶, 当需要入栈, 出栈操作时, 栈指针SP就会随着栈顶的变化上下移动. 在一个满递减栈中, 栈指针SP总是指向栈顶元素. 

在栈的初始化过程中, 除了指定栈的起始地址, 我们还需要指定栈空间的大小. 在Linux环境下, 我们可以通过下面的命令来查看和设置栈的大小. 

Linux的进程栈大小
- 查看堆栈大小：$ ulimit -s
- 设置堆栈大小：$ ulimit -s size
- 调高堆栈容量会增加内存开销和启动时间
	- Linux默认给每一个用户进程栈分配8MB大小的空间.
- 栈容量太小, 则程序超出栈设置的内存空间又容易发生栈溢出(Stack Overflow), 产生段错误
- 在最大值内，栈会动态增长

在设置栈大小时, 我们要根据程序中的变量, 数组对栈空间的实际需求, 设置合理的栈大小. 用户在编写程序时, 为了防止栈溢出, 可以参考下面的一些原则:
- 尽量不要在函数内使用大数组, 如果确实需要大块内存, 则可以使用malloc申请动态内存. 
- 函数的嵌套层数不宜过深.
- 递归的层数不宜太深

# 函数调用

每一个函数都会有自己专门的栈空间来保存这些数据，每个函数的栈空间都被称为栈帧(Stack Frame, SF). 
每一个栈帧都使用两个寄存器FP和SP来维护, FP指向栈帧的底部, SP指向栈帧的顶部. 

函数的栈帧除了保存局部变量和实参, 还用来保存函数的上下文. 

什么是栈帧?
- 一个程序中往往存在多级函数调用, 每一级调用都会运行不同的函数, 每个函数都有自己的栈帧空间, 每一个栈帧都有栈底和栈顶, 无论函数调用运行到哪一级, SP总是指向当前正在运行函数栈帧的栈顶, 而FP总是指向当前运行函数的栈底.

在每一个函数栈帧中, 除了要保存`局部变量`, `函数实参`, 函数调用者的`返回地址`, 有时候编译过程中的一些临时变量也会保存到函数的栈帧中. 

除此之外, `上一级函数栈帧的起始地址`, 即`栈底`也会保存到当前函数的栈帧中, 多个栈帧`通过FP`构成一个链, 这个链就是某个进程的`函数调用栈`. 很多调试器支持回溯功能, 其实就是基于这个调用链来分析函数的调用关系的. 

- 函数调用栈帧:
	- ![](assets/Pasted%20image%2020230502200925.png)
		- main()函数中调用了f()函数, main()函数的栈帧基址FP, main()函数中的返回地址LR, 都需要保存在f()函数的栈帧中. 当f()函数运行结束退出时就可以根据栈中保存的地址返回函数的上一级继续执行. 

ARM汇编指令:
- 寄存器间接寻址
	- `LDR R0, [R1,#4];    R0<-[R1+4]`
	- `LDR R0, [R1,#4]!;`     `R0<-[R1+4], R1=R1+4`
	- `LDR R0, [R1], #4;`      `R0<-[R1], R1=R1+4`
	- `LDR R0, [R1,R2];`      `R0<-[R1+R2]`
- 入栈出栈
	- `PUSH {FP,LR};`        `FP/LR->STACK, SP->LR`
	- `POP {FP,PC};`          `[SP]->PC, [SP+4]->FP`

- 函数调用
	- 栈帧基址, 返回地址保存
	- 函数返回: 栈帧释放
- 局部变量
	- 初始化的局部变量
	- 未初始化的局部变量
	- 压入该函数的栈帧内

对汇编代码进行分析, 我们可以看到, 在函数内定义的局部变量都分别保存在每个函数各自的栈帧空间里, 对这些局部变量的访问是通过FP/SP这对栈指针加上相对偏移来实现的, 这和通过变量名对全局变量访问有所不同. 

每个函数栈帧中都保存着上一级函数的返回地址LR和它的栈帧空间起始地址FP，当函数运行结束时，可根据这些信息返回上一级函数继续运行。

FP和SP总是指向当前正在运行的函数的栈帧空间，分别指向栈帧的底部和顶部，通过相对偏移寻址来访问栈帧内的局部变量。

函数运行结束后, 当前函数的栈帧空间就会释放, SP/FP指向上一级函数栈帧, 函数内定义的局部变量也就随着栈帧的销毁而失效, 无法再继续引用. 

```c
int g()
{
	int x =1;
	int y =2;
	return 3;
}

int f()
{
	int l = 20;
	int m = 30;
	int n = 40;
	g();
	return 50;
}

int main()
{
	int i =2, j =3, k =4;
	f();
	return 0;
}
```
- ![](assets/Pasted%20image%2020230502211913.png)

为什么在g()函数的反汇编代码中没有将LR压栈？
- 当f()函数跳转到g()函数时, 因为g()函数中没有使用BL指令调用其他函数, 因此在整个g()函数运行期间, LR寄存器的值是不变的, 一直保存的是上一级函数f()的返回地址. 
- 为了节省内存资源, 减少压栈带来的时间和空间开销, 所以LR并没有压入栈中. 当g()函数运行结束时, 将LR寄存器中的返回地址赋值给PC指针, 就可以直接返回到上一级f()函数中继续运行了.

# 参数传递

函数调用过程中的参数传递, 一般都是通过栈来完成的. 
ARM处理器为了提高程序运行效率, 会使用寄存器来传参. 

根据ATPCS规则:
- 在函数调用过程中, 当要传递的参数个数小于4时, 直接使用R0到R3寄存器.
- 当要传递的参数个数大于4时, 前4个参数使用寄存器传递压入被调函数栈帧, 剩余的参数则压入主调函数栈帧保存. 
- 返回值, 小于4个字节, 直接用R0返回. 8个字节, 用R0跟R1来返回. 大于8个字节, 如结构体之类, 则在栈内临时分配一块区域.

函数参数入栈
- 被调用函数将寄存器R0~R3传来的参数压栈保存

```c
int f(int ag1, int ag2, int ag3, int ag4, int ag5, int ag6, int ag7)
{
	int s=0;
	s = ar1+ar2+ar3+ar4+ar5+ar6+ag7;
	return s;
}

int main()
{
	int sum = 0;
	sum = f(1,2,3,4,5,6,7);
	printf("sum = %d\n", sum);
	return 0;
}
```

在参数传递过程中，各个参数压栈、出栈的顺序也要有一个约定，如上面的7个参数，是从左往右依次压入堆栈的呢？还是从右往左呢？我们一般把不同的约定方式称为调用惯例。

## 调用惯例

- ![](assets/Pasted%20image%2020230502213639.png)
- 函数调用双方的约定
	- 参数压栈方式
	- 栈清理
- 默认的调用惯例
	- C语言默认使用cdecl
		- 参数传递：按从右至左压入堆栈
		- 栈清理方：由caller管理
	- 好处
		- 预先知道参数、返回值大小
		- 支持变参函数的调用，如printf

上面的代码, 参数7 6 5先压到main的栈帧中. 然后把 4 3 2 1 分别给R3 R2 R1 R0四个寄存器. 然后跳到f函数. 接着压fp, fp sp到新栈帧. 然后把R0到R4的参数压到f的栈帧中. 7 6 5通过fp寄存器来相对寻址访问.
FP寄存器不仅可以向前偏移访问本函数栈帧的内存单元，还可以向后偏移，到上一级函数的栈帧中获取要传递的实参。sp也可以被用来放问栈帧内的数据.
- ![](assets/Pasted%20image%2020230502215248.png)
	- 随后f运行结束. fp sp返回:
	- ![](assets/Pasted%20image%2020230502215349.png)

# 形参与实参

函数的参数传递是值传递, 形参保存的是实参的副本, 改变形参并不会改变实参. 
从栈帧的运行就知道了.

函数参数
- 形参：函数定义时使用的参数，用来接收传来的实参
- 实参：常量、变量、表达式、函数等
- 特点：形参值的改变并不能改变实参

为什么形参的改变不能改变实参:
- 形参只有被调用时才给分配内存单元, 调用结束后随着栈帧的销毁而被释放
- 变量作为实参传递时，只是将其值拷贝到形参的内存空间。
- 即实参和形参位于不同的内存存储单元

理解了形参在栈中的动态变化, 我们就可以更好地理解局部变量的生命周期和作用域. 

# 栈与作用域

## 变量的作用域

全局变量
- 该变量定义在函数外
- 作用域: 从声明处到文件结尾
- 其它文件使用extern声明即可引用
- 生命周期: 整个程序运行期间
局部变量
- 变量定义在函数体内、存储在栈内
- 作用域：只能在函数内使用
- 生命周期：函数运行期间

为什么程序不能访问其它函数里的局部变量
- 局部变量只有函数被调用时才会在栈内分配内存空间
- 局部变量的作用域和生命周期只在函数运行期间
- 函数运行结束，栈帧释放，变量“消失”

## 作用域管理

编译器栈管理
- 编译器根据`{}`代码块做压栈出栈操作
- 根据`{}`代码块来限定一个变量的作用域

如果我们在代码块中定义一个`静态变量k`, 则编译器在编译时会把变量k放置在`数据段`中, k的生命周期也随之改变, 但是其`作用域不变`. 
static关键字虽然改变了局部变量的存储属性(生命周期, 但是其作用域仍是由`{}代码块`决定的. 
我们查看符号表, 可以看到经过static修饰的局部变量k, 其存储位置已经由栈转移到了数据段中, 但是作用域仍局限在由{}限定的代码块内. 
- ![](assets/Pasted%20image%2020230502221840.png)

小结
全局变量的作用域
- 全局变量的作用域由文件来限定
- 可使用extern进行扩展，被其它文件引用
- 可以使用static进行限制，只能在本文件被引用
局部变量的作用域
- 局部变量的作用域由{}限定
- 可使用static修改局部变量的存储属性(生存周期)
- 但不能改变其作用域

# 栈溢出攻击原理

Linux进程的栈空间是有固定大小的, 一般是8MB. 如果我们在函数内定义了一个数组, 系统就会在栈上给这个数组分配存储空间. 由于C语言对边界检查的宽松性, 即使程序对超出数组的内存单元进行数据篡改, 编译器一般也不会报错. 如下面的数组越界访问程序. 

C语言的哲学思想除了简单就是美. 还有另外一个特点: 对语法检查的宽松性, 默认所有的编程者都是高手, 在操作内存时永不犯错. 

然而正是这种编程的灵活性给了黑客可乘之机, 可以利用C语言的语法检查宽松性, 利用栈溢出植入自己的指令代码, 夺取程序的控制权, 然后就可以进行恶意攻击. 

函数运行结束时就会根据返回地址LR跳到上一级函数继续执行, 黑客如果发现你实现的某个函数有漏洞, 就可以利用漏洞修改栈的返回地址LR, 植入自己的指令代码. 

```c
#include <stdio.h>

void shellcode()
{
	while(1);
}

void f()
{
	int a[4];
    a[8] = shellcode;
}
int main()
{
	f();
	return 0;
}
```
在上面的栈溢出程序中, main()函数调用了f()函数, 正常情况下, f()运行结束后会返回到main()中继续执行. 但是由于f()函数内的数组越界访问破坏了f()函数的栈帧结构: 将f()函数栈帧内的main()函数的返回地址给覆盖掉了, 替换为自己的病毒代码shellcode的入口地址. 所以当f()函数运行结束后并不会返回到main(), 而是跳到shellcode()执行了. 由于C语言对边界检查的宽松性, 我们在程序中访问数组元素`a[8]`编译器并不报错, 黑客利用数组的溢出夺取了程序的控制权, 攻击成功. 
- ![](assets/Pasted%20image%2020230502223956.png)
- 虽然C语言标准并没有规定数组的越界访问会报错，但是大多数编译器为了安全考虑，会对数组的边界进行自行检查：当发现数组越界访问时，会产生一个错误信息来提醒开发者。

GCC编译器为了防止数组越界访问, 一般会在用户定义的数组末尾放入一个保护变量, 并根据此变量是否被修改来判断数组是否越界访问. 若发现这个变量值被覆盖, 就会给当前进程发送一个SIGABRT信号, 终止当前进程的运行. 这种检测手段简单有效, 但是也会存在漏洞: 如果用户绕过这个检测点, 如对数组元素`a[5]`进行越界访问, GCC可能就检测不到了. 

# 堆内存管理

我们使用`malloc()/free()`函数申请/释放的动态内存就属于堆内存, 堆是Linux进程空间中一片`可动态扩展或缩减的内存区域`, 一般位于BSS段的后面. 

堆与栈的区别:
- 堆内内容是匿名的，不能按名字直接访问，通过指针间接访问
- 栈上的数据、变量在函数返回时会被释放，无法继续使用
- 堆内存由程序员自己申请和释放(malloc/free), 函数退出时, 如果程序员不释放，会一直存在

堆内存申请与释放
-  C语言：malloc, calloc, realloc/free
-  C++语言：new/delete

当用户使用malloc()函数申请一片内存时, 要到哪里去申请呢? 当用户使用free()函数释放一片内存时, 将这片内存归还到哪里呢? 堆内存自身也需要专门的管理和维护, 以应对用户的内存申请和释放请求. 关于堆内存管理, 不同的嵌入式开发环境, 不同的操作系统实现也不完全相同. 

## 裸机环境下的堆内存管理

嵌入式一般使用集成开发环境来开发裸机程序, 如ADS1.2, Keil, RVDS, Keil MDK等. 以Keil为例, Keil自带的启动文件startxx.s会初始化堆内存, 并设置堆的大小, 然后由main()函数调用`__user_initial_stackheap`来获取堆栈地址. 

堆空间地址的设置一般由编译器默认获取, 将堆地址设置在`ARM ZI区`的后面, 或者使用scatter文件来设置, 在汇编启动代码中初始化这段堆空间. 
- 以STM32平台的启动代码示例, 看看堆是如何初始化的: 
	- ![](assets/Pasted%20image%2020230503114628.png)

在嵌入式裸机程序开发中, 一般很少使用C标准库. 如Keil编译器, 根本就没有完全实现一个C标准库, 并且C标准库也没有默认链接使用. 

Keil编译器只是实现了一个简化版的C标准库, 叫作MicroLIB库, 如图:
- ![](assets/Pasted%20image%2020230503115306.png)
	- 该函数库实现了C标准规定的大部分函数功能, 并针对嵌入式平台做了很多优化, 使其体积更小, 更适合存储资源有限的嵌入式系统. 
	- 如果你在开发ARM裸机程序时想使用该库, 则可以在Keil集成开发环境的Target配置选项中选中该库, 然后就可以直接使用库中的malloc()函数来申请内存了. 

内存碎片

- 内存碎片的产生
	- 大量频繁地申请/释放内存
	- 到最后可能申请内存失败、系统宕机
	- ![](assets/Pasted%20image%2020230503115602.png)

编程忠告:
- 在裸机环境中尽量不用malloc/free
- 使用数组代替

heap问题解决之道:
- 根据需求
	- 自己实现堆内存管理如 内存池：将堆内存空间划分为固定大小的内存块，自己管理与维护内存的申请和释放来避免内存碎片的产生。
	- 将堆内存划分成不同大小的内存块, 根据用户申请内存的大小选择合适的内存块, 进一步提高内存利用率. 节省内存资源.
- 关于堆内存的管理, 不同的系统和平台有不同的解决方案. 
	- 在有操作系统的环境下, 一般会让操作系统介入堆内存管理, 以减少开发者的工作量, 减轻工作负担. 
	- 裸机就自己实现

![](assets/Pasted%20image%2020230503122428.png)

## uC/OS的堆内存管理

在裸机环境下, 由于缺少堆内存管理, 我们已经知道了使用malloc()/free()的弊端, 即堆内存经过多次申请和释放后会引起内存碎片化, 当内存碎片过多时, 再去申请一片连续的大块内存就会失败. 让操作系统介入堆内存管理, 目的就是改善这一状况. 

uc/os堆内存管理
- 基本策略
	- 将堆内存分成若干区
	- 每个区分为若干大小相等的内存块
	- 程序以内存块为单位对内存进行申请/释放
- ![](assets/Pasted%20image%2020230503123005.png)

uC/OS内核源码中有一个单独的源文件: os_mem.c, 该源文件实现了对堆内存的管理. 

内存控制块

在uC/OS的堆内存管理中, 内存分区是操作系统管理堆内存的基本单元, 每个内存分区使用一个结构体来表示, 我们称之为`内存控制块`. 
```c
typedef struct os_mem { /* MEMORY CONTROL BLOCK */
void *OSMemAddr; /* 内存分区指针*/
void *OSMemFreeList; /* 空闲内存控制块链表指针*/
INT32U OSMemBlkSize; /* 每个内存快长度*/
INT32U OSMemNBlks; /* 分区内总的内存块数目*/
INT32U OSMemNFree; /* 分区内空闲内存块个数 */

#if OS_MEM_NAME_EN > 0u
INT8U *OSMemName; /* 分区名字*/
#endif
} OS_MEM;
```

内存控制块空闲链表
- 每个分区由大小相同的内存块构成, `内存块总数量和空闲的内存块数量`都保存在任务控制块内
- 各个内存块构成一个`链表`, 通过`内存控制块结构体`中的`OSMemFreeList`成员可获取指向该链表的指针.
- 每个内存控制块代表堆内存中的一个内存分区.
- 各个内存控制块用指针链成链表
- uC/OS可以通过`OS_CFG.H\OS_MAX_MEM_PART宏`来配置内核支持的最大分区数
- 该链表由`osmem.c\OS_MemInit()`函数创建并初始化
	- ![](assets/Pasted%20image%2020230503123747.png)

源代码:
- ![](assets/Pasted%20image%2020230503124214.png)
- ![](assets/Pasted%20image%2020230503124218.png)
	- 在uC/OS初始化过程中, 会调用`OS_MemInit()`函数, 在内存中创建一个节点数为`OS_MAX_MEM_PART`的`链表`. 链表中的每个节点为一个`OS_MEM类型的结构体`, 每个结构体表示一个内存分区, 用户可以使用该结构体来创建自己的堆内存. `OSMemFreeList`是一个全局指针变量, 指向该链表的第一个节点, `OS_MemInit()`运行结束后, 链表在内存中的分布如图.
		- ![](assets/Pasted%20image%2020230503152633.png)

用户在开发程序时, 如果想使用堆内存, 则可以使用`uC/OS`提供的接口函数去创建一个堆内存, 从堆内存中申请一个内存块或释放一个内存块. 这3个API的函数原型如下:
代码分析:
- 初始化动态堆内存：OSMemCeate
- 申请一个内存块：OS_MemGet
- 释放一个内存块：OS_MemPut
	- ![](assets/Pasted%20image%2020230503152805.png)

在uC/OS下开发应用程序, 可以按照下面的流程去创建一个内存分区, 去申请和释放一片堆内存:
- ![](assets/Pasted%20image%2020230503152836.png)

接下来我们就研究一下uC/OS的堆内存是如何实现的。首先我们要调用OSMemCreate()函数去创建一个内存分区，并将该分区划分为指定大小的内存块。OSMemCreate()函数的核心源码如下。
- ![](assets/Pasted%20image%2020230503152911.png)
	- OSMemCreate()函数的主要功能是基于某个内存地址创建一个内存分区, 并将该内存分区划分成用户指定大小的若干内存块. 该函数首先会从全局指针OSMemFreeList指向的内存控制块链表中摘取一个节点, 使用这个OS_MEM结构体变量来表示我们当前创建的分区. 接下来的核心一步就是划分内存块: 每个内存块的前4字节存放的是下一个内存块的地址. 各个内存块通过这种地址指向关系构成一个内存块链表，便于管理和维护.
	- 这部分代码的实现很有意思, 使用一个二级指针plink完成链表的构建. 在上面的for循环中可以看到, `*plink=(void*)pblk;`这句代码占用了当前内存块的4字节来存放下一个内存块的地址, `plink=(void**)pblk;`这句代码则移动plink指针, 使其指向下一个内存块, 不断循环初始化每个内存块的前4字节, 就可以在一片连续的内存中构建一个如图:
		- ![](assets/Pasted%20image%2020230503165113.png)

## Linux堆内存管理

Linux环境下的堆内存管理比uC/OS复杂多了, 不仅包含堆内存管理, 还包括读写权限管理, 地址映射等. 
Linux内核中的`内存管理子系统`负责整个`Linux虚拟空间`的权限管理和地址转换. 

### Linux堆地址空间和大小

- 堆的空间
	- Linux2.4从0x4000 0000给共享库分配空间, 将程序载入此空间
	- Linux2.6+ 将共享库地址往上移到栈附近, 0xBFxxxxxx附近
- 堆的大小
	- 理论上大约2.9G的虚拟地址空间
	- ![](assets/Pasted%20image%2020230503171739.png)

每一个Linux用户进程都有各自的4GB的虚拟空间, 除去3GB到4GB的内核空间, 还有0到3GB的用户空间可用. 在这3GB的地址空间上, 除了代码段, 数据段, BSS段, MMAP区域, 默认的8MB进程栈空间占用一部分地址空间, 还有大量可用的地址空间, 理论上都可以给堆内存使用. 

一个用户进程也, 想申请一块内存使用, 需要向内核申请, 内核批准后才能使用. 如果你跳过申请, 直接对未申请的内存空间进行读写, 系统一般会报内存段错误. 

### 堆管理策略

- 系统调用
	- Linux由内核负责整个虚拟地址空间的权限管理和地址转换
	- malloc/free底层的实现: 通过系统调用向内核申请内存
	- 大量的系统调用会降低性能

`malloc()/free()`函数的底层实现, 其实就是通过`系统调用brk`向内核的内存管理系统申请内存. 内核批准后, 就会在BSS段的后面留出一片内存空间, 允许用户进行读写操作. 申请的内存使用完毕后要通过free()函数释放, free()函数的底层实现也是通过系统调用来归还这块内存的. 

### Glibc堆内存管理

当用户要申请的内存比较大时, 如大于128KB, 一般会通过mmap系统调用直接映射一片内存, 使用结束后再通过ummap系统调用归还这块内存. 

mmap区域是Linux进程中比较特殊的一块区域, 主要用于程序运行时动态共享库的加载和mmap文件映射. 

内存分配器
- Glibc使用`ptmalloc2`作为默认的内存分配器对堆内存进行管理
- 留出malloc/free等API用于用户动态内存的申请分配
- 通过系统调用brk/mmap向内核“批发”内存
- 管理用户程序释放的空闲内存

两种动态内存
- 堆内存：通过算法管理、回收不同大小的内存块
- MMAP内存：通过系统调用向系统申请/释放内存(>128K)

![](assets/Pasted%20image%2020230503182710.png)

为了验证上面的理论是否正确, 我们可以编写一个程序, 使用malloc()函数申请不同大小的内存块, 观察它们在进程空间的地址变化: 
```c
#include <stdio.h>
#include <stdlib.h>

int global_val;

int main(void)
{
	int *p =NULL;
	printf("&global_val = %p\n", &global_val);

	p = (int *) malloc(100);
	printf("&mem_100 = %p\n", p);

	p = (int *) malloc(1024*256);
	printf("&mem_256k = %p\n", p);

	free(p);

	while(1);
	return 0;
}
```
编译运行看结果:
- ![](assets/Pasted%20image%2020230503175543.png)
	- 对于用户申请的小块内存, Linux内存管理子系统会在BSS段的后面批准一块内存给用户使用. 当用户申请的内存大于128KB时, Linux系统则通过mmap系统调用, 映射一片内存给用户使用, 映射区域在用户进程栈附近. 两次申请的不同大小的内存, 其地址分别位于内存中两个不同的区域：heap区和mmap区。
- 我们让a.out进程先不退出, 一直死循环运行, 以方便我们通过cat命令查看a.out进程的内存布局.
	- ![](assets/Pasted%20image%2020230503175836.png)
	- 在32位X86平台下我们可以看到, heap区域在.bss段的后面, 而mmap区域则紧挨着stack, mmap区域包括进程动态链接时加载到内存的动态链接器`ld-2.23.so`, 动态共享库, 使用mmap申请的动态内存.
	- 使用kill命令杀掉a.out进程再重新运行, 你会发现`&mem_100`和`&mem_256K`的地址打印值发生了变化, 每次程序运行的地址可能都不相同. 这是因为`heap区`和`mmap区`的`起始地址`和stack一样, 也不是固定不变的. 
	- 为了防止黑客攻击, 每次程序运行时, 它们都会以一个`随机偏移`作为起始地址. 

- a.out 内存布局:
	- ![](assets/Pasted%20image%2020230503182805.png)
		- 栈的起始地址并不紧挨着内核空间0xc000 0000, 而是从0xbf9a2000作为起始地址, 中间有一个大约6MB的偏移. heap区也不紧挨着.bss段, 它们之间也有一个offset; mmap区也是如此, 它和stack区之间也有一个offset. 
		- 这些随机偏移由内核支持的可选配置选项`randomize_va_space`控制，当然你也可以关闭这个功能。
			- ![](assets/Pasted%20image%2020230503183005.png)
		- 将`randomize_va_space`赋值为0, 可以关掉这个随机偏移功能. 关闭这个功能后再去运行a.out, 你会看到, a.out进程栈的起始地址就紧挨着内核空间0xc0000000存放, heap区和mmap区也是如此. 

对于用户创建的每一个Linux用户进程, Linux内核都会使用一个`task_struct`结构体来描述它. `task_struct`结构体中`内嵌一个mm_struct`结构体, 用来描述`该进程代码段, 数据段, 堆栈的起始地址`.   
- ![](assets/Pasted%20image%2020230503184217.png)
	- `mm_struct`结构体中的`start_brk成员`表示堆区的起始地址, 当我们将`randomize_va_space`设置为0, 关闭随机地址的偏移功能时, 这个地址就是数据段(包括.data和.bss)的结束地址end_data. 
	- `mm_struct`结构体中的`brk`成员表示`堆区的结束边界地址`. 当用户使用`malloc()`申请的内存大小大于当前的堆区时, `malloc()`就会通过`brk()系统调用`, 修改`mm_struct`中的成员变量`brk`来`扩展堆区`的大小. 
	- brk()系统调用的`核心操作`其实就是通过`扩展数据段的边界`来改变数据段的大小的. 
		- ![](assets/Pasted%20image%2020230503184450.png)
	- 当程序`加载到内存运行时`, 加载器会根据可执行文件的代码段, 数据段(.data和.bss)的`size大小`在内存中`开辟同等大小的地址空间`。
	- 代码段和数据段的大小在编译时就已经确定, 代码段具有只读和执行的权限, 而数据段则有读写的权限. 代码段和栈之间的一片茫茫内存虽然都是空闲的, 但是要先申请才能使用。
	- `brk()系统调用通过扩展数据段的终止边界来扩大进程中可读写内存的空间, 并把扩展的这部分内存作为堆区, 使用start_brk和brk来标注堆区的起始和终止地址`.
	- 在程序运行期间, 随着`用户申请的动态内存不断变化`, brk的`终止地址也随之不断地变化`, 堆区的大小也会随之不断地变化. 

### 堆内存申请与释放底层实现

`大量的系统调用`会让处理器和操作系统在不同的工作模式之间来回切换: 操作系统要在用户态和内核态之间来回切换, CPU要在普通模式和特权模式之间来回切换, 每一次切换都意味着各种上下文环境的保存和恢复, 频繁地系统调用会`降低系统的性能`. 

`系统调用`还有一个不人性化的地方是`不支持任意大小的内存分配`, 有的平台甚至只支持一个或数倍`物理页大小的内存申请`, 这在一定程度上会造成内存的浪费.

为了提高内存申请效率, 减少系统调用带来的开销, 我们可以在`用户空间`层面对堆内存介入管理. 如在`glibc中`实现的`内存分配器(allocator)`可以直接对堆内存进行维护和管理. 

- 如图所示, `内存分配器`通过系统调用`brk()/mmap()`向Linux内存管理子系统“批发”内存, 同时实现了`malloc()/free()`等API函数给用户使用, 满足用户动态内存的申请与释放请求. 
	- ![](assets/Pasted%20image%2020230503184916.png)
	- 当用户使用`free()`释放(小于128K)内存时, `释放的内存并不会立即返回给内核`, 而是被`内存分配器接收`, `缓存在用户空间`. `内存分配器`将这些内存块通过`链表`收集起来, 等下次有用户再去申请内存时, 可以直接从链表上查找合适大小的内存块给用户使用, 如果`缓存的内存不够用`再通过`brk()系统调用`去内核“批发”内存. 
	- `内存分配器`相当于一个`内存池缓存`, 通过这种操作方式, 大大`减少了系统调用`的次数, 从而提升了程序申请内存的效率, 提高了系统的整体性能. 

### chunk

Linux环境下的C标准库glibc使用`ptmalloc/ptmalloc2`作为默认的内存分配器, 具体的实现源码在`glibc-2.xx/malloc`目录下. 为了方便对内存块进行跟踪和管理, 对于`每一个用户申请的内存块`, ptmalloc都`使用一个malloc_chunk结构体来表示`, 每一个内存块`被称为chunk`. malloc_chunk结构体定义在`glibc-2.xx/malloc/malloc.c`文件中.
- ![](assets/Pasted%20image%2020230503193957.png)

- 已分配的chunk
	- ![](assets/Pasted%20image%2020230503195008.png)
	- 标志位: 
		- A: =0 表示从`主分配区`分配内存; =1 是从`非主分配区`分配内存
			- 主线程就是主分配区, 子线程就是子分配区
		- M: =0 表示从Heap分配内存; =1表示从MMAP映射区分配内存
		- P: =0 表示前一个chunk空闲

- 空闲的chunk
	- ![](assets/Pasted%20image%2020230503195304.png)
		- 使用free释放掉的内存块并不会立即归还给操作系统
		- 添加到一个链表中
		- 下次内存申请, 从这个链表中找出合适的空闲内存块, 分配给用户

### bin

- Chunk容器
	- 被用户free掉的chunk通过fd和bk指针连成链表
	- 不同大小的chunk分别连成不同的链表, 这个链表叫做bin
	- Ptmalloc一共有`128个bin`, 用数组保存这些bin的起始地址
- Bin分类
	- Fast bins: 被free的小于`max_fast`的chunk首先放到这里
	- Unsorted bins: 大于max_fast的chunk或fast bins中合并的chunk
	- Small bins: 小于512字节的chunk
	- Large bins: 512B < SIZE <128K

用户程序调用`free()`释放掉的内存块并`不会立即归还给操作系统`, 而是被`用户空间的ptmalloc`接收并添加到`一个空闲链表`中. 

malloc_chunk结构体中的`fd`和`bk指针成员`将每个空闲内存块链成一个`双链表`, `不同大小的内存块链接在不同的链表上`, `每个链表`都被我们称作`bin`, ptmalloc内存分配器共有`128个bin`, 使用一个数组来保存这些bin的起始地址. 

- 每一个bin都是由不同大小的内存块链接而成的链表, 根据内存块大小的不同, 我们可以对这些bins进行分类. 每个bin在数组中的地址索引和bin链表中内存块大小之间的对应关系:
	- ![](assets/Pasted%20image%2020230503200137.png)
	- 用户释放掉的内存块不会立即放到bins中, 而是先放到`unsorted bin`中. 等用户下次申请内存时, 会首先到`unsorted bin`中查看有没有合适的内存块, 若没有找到, 则再到`small bins`或`large bins`中查找. 
	- small bins中一共包括`62个bin`, 相邻两个bin上的内存块大小`相差8字节`, 内存数据块的大小范围为`[16，504]`, 大于504字节的大内存块要放到large bins对应的链表中. 
	- 每个bin在数组中的索引和内存块大小之间的关系如表:
		- ![](assets/Pasted%20image%2020230503200928.png)
- bins数组:
	- ![](assets/Pasted%20image%2020230503201106.png)
		- 因为用的是双向环链, 127x2

除了数组中的这些bins, 还有一些`特殊的bins`, 如`fast bins`. 
用户释放掉的小于`M_MXFAST`(32位系统下默认是`64字节`)的内存块会`首先被放到fast bins`中. 

- 如图所示, fast bins由`单链表`构成, `FILO栈式操作`, 运行效率高, 相当于`small bins的缓存`. 
	- ![](assets/Pasted%20image%2020230503201653.png)

### 堆内存的分配流程

- 分配顺序: 
Fast bins-> Small bins -> Unsorted bin-> Larger bins -> Top chunk-> Mmap chunk

- 当用户申请一块内存时, 内存分配器就根据申请的内存大小从bins查找合适的内存块. 
- 当申请的内存块小于`M_MXFAST`时, ptmalloc分配器会首先到`fast bins`中去看看有没有合适的内存块, 如果没有找到, 则再到`small bins`中查找.
- 如果要申请的内存块`大于512字节`, 则直接跳过small bins, 直接到`unsorted bin`中查找.

- 在适当的时机, `fast bins`会将`物理相邻的空闲内存块合并`, 存放到`unsorted bin`中. 
- 内存分配器如果`在unsorted bin`中`没有找到合适大小的内存块`, 则会`将unsorted bin中物理相邻的内存块合并`, 根据`合并后的内存块大小`再迁移到`small bins`或`large bins`中. 
	- ![](assets/Pasted%20image%2020230503211927.png)

	- 如图所示, unsorted bin中两个大小分别为16字节和24字节的内存块在物理内存上是相邻的, 因此我们可以把它们合并成一个40字节大小的内存块, 并迁移到small bins中对应的链表上. 
		- ![](assets/Pasted%20image%2020230503202100.png)
	- 合并后的内存块如图
		- ![](assets/Pasted%20image%2020230503202145.png)

### 特殊的chunk

- Last remainder chunk
- ptmalloc接着会到`large bins`中寻找合适大小的内存块. 假设没有找到大小正好合适的内存块, 一些`大的内存块`将会`被分割成两部分`: 一部分返回给用户使用, 剩余部分则放到unsorted bin中. 
- 此剩余块 就是新的 last remainder chunk.

如果在`large bins`中还没有找到合适的内存块, 这时候就要到`top chunk`上去分配内存了.

- top chunk:
	- top chunk是`堆内存区顶部`的一个独立chunk, 它比较特殊, 不属于任何bins. 
	- 若用户申请的内存小于top chunk, 则top chunk会被分割成两部分: 一部分返回给用户使用, 剩余部分则作为新的top chunk. 
	- 若用户申请的内存大于top chunk, 则内存分配器会通过`系统调用sbrk()/mmap()`扩展top chunk的大小. 
	- `用户第一次调用malloc()申请内存时, ptmalloc会申请一块比较大的内存, 切割一部分给用户使用, 剩下部分作为top chunk. `

- mmap chunk: 
- 当`用户申请的内存`大于`M_MMAP_THRESHOLD(默认128KB)`时, `内存分配器`会通过系统调用`mmap()申请内存`. 
- 使用`mmap映射的内存区域`是一种`特殊的chunk`, 这种chunk叫作`mmap chunk`. 
- 当用户通过`free()`函数释放掉这块内存时, 内存分配器再`通过munmap()系统调用`将其归`还给操作系统`, 而不是将其放到bin中. 
- 注意: 该chunk不会放入bin 而是直接还给OS. 

![](assets/Pasted%20image%2020230503210122.png)

### arena

为了适应多进程, 多线程并发而出现的概念. 
- 分配区的
	- 通过`sbrk()和mmap()`为线程分配的堆区
	- main arena：给主线程分配的arena
	- thread arena：给子线程分配的arena

> chunk -> bins -> arena

用户调用glibc标准库stdlib.h中的malloc(), 其实是调用glibc/malloc.c下的`__libc_malloc()`函数. 该函数会调用`_int_malloc()`函数, 在此函数中, 根据申请的内存大小, 归类到不同的bin中.

内存释放与合并:
- free的内存大小 小于64字节, 先放到fast bins. 大于64字节且小于128K, 会先放到unsorted bin, 以待物理相邻合并 再放到small 或者 large bins里去.
- 大于128K 的直接还给os. 因为是mmap申请的, munmap来释放.

### 内存申请释放示例

```c
#include<stdio.h>
#include<stdlib.h>

int main()
{
// 申请
    char *p1,*p2,*p3,*p4,*p5,*p6;
    p1 = malloc(32*1024);
    p2 = malloc(64*1024);
    p3 = malloc(120*1024);
    p4 = malloc(132*1024);
    printf("p1: %p\n",p1);
    printf("p2: %p\n",p2);
    printf("p3: %p\n",p3);
    printf("p4: %p\n",p4);

//释放再申请
    free(p1);
    p5 = malloc(12*1024);
    printf("p5: %p\n",p5);
    free(p2);
    p6 = malloc(80*1024);
    printf("P6: %p\n",p6);
//  free(p1);
//  free(p2);
    free(p3);
    free(p4);
    free(p5);
    free(p6);
    return 0;
}
```

```shell
p1: 0x8172008
p2: 0x817a010
p3: 0x818a018
p4: 0xb75b7008

p5: 0x8172008
p6: 0x8175010
```
- 堆内存申请
	- ![](assets/Pasted%20image%2020230503213437.png)
		- 可以看到，对于小于128KB的内存申请, ptmalloc会直接在堆区域分配内存; 对于大于128KB的内存申请, ptmalloc内存分配器则直接在靠近进程栈(0xbxxxxxxx)的地方映射一片内存区域返给用户使用.
		- 用户释放的内存并不会立即归还给操作系统，而是由ptmalloc接管，等下次用户申请内存时就可以将接管的这块内存继续分配给用户使用。
		- 对于120KB的大内存申请，如果没有在large bins中找到合适的内存块，则ptmalloc就会到top chunk区域分配内存。
- 内存释放再申请
	- 这个实验是指 free p1后, 再连续申请内存.没有free p2.
	- ![](assets/Pasted%20image%2020230503214059.png)
		- 程序新申请的12KB内存就是从刚刚释放的32KB大小的内存块中直接分割一块返给用户的，所以p1的地址跟p5一样.
- 内存合并
	- free p1, 申请, free p2, 申请.
	- ![](assets/Pasted%20image%2020230503215856.png)
		- 当堆内存中相邻的两个内存块都被释放且处于空闲状态时, ptmalloc在合适的时机, 会将这两块内存合并成一块大内存, 并在bins上更新它们的维护信息. 
		- 释放64KB内存时, 它就会和相邻的20KB大小的空闲内存块合并, 生成一个84KB大小的新内存块. 
		- 当用户申请一个80KB大小的内存时, 就可以将这块内存分配给用户, 并将剩下的4KB内存块放到unsorted bin中, 等待用户新的内存申请或将它移动到large bins中. 
- 大于128K的内存申请与释放
	- ![](assets/Pasted%20image%2020230503220230.png)
		- 如果申请的内存大于128KB, 则ptmalloc直接通过`mmap()`映射一片内存返给用户, 这部分映射内存释放时也不会添加到bins, 而是直接通过`munmap()`直接还给操作系统.

### mmap映射区域探秘

当用户使用malloc申请大于128KB的堆内存时, 内存分配器会通过mmap系统调用, 在Linux进程虚拟空间中直接映射一片内存给用户使用. 

这片使用mmap映射的内存区域比较神秘, 目前我们还不是很熟悉, 无论是动态链接器, 动态共享库的加载, 还是大于128KB的堆内存申请, 都和这个区域息息相关. 

既然已经有堆区和栈区了, 为什么还要使用这片映射区域? 这片映射区域的内存有什么特点? 怎么使用它? 操作系统是如何管理和维护的?

想要搞清楚这部分区域, 我们还得从文件的读写说起。

当我们运行一个程序时, 需要从磁盘上将该可执行文件加载到内存. 将文件加载到内存有两种常用的操作方法:
- 一种是通过常规的文件I/O操作, 如read/write等系统调用接口；
- 一种是使用mmap系统调用将文件映射到进程的虚拟空间, 然后直接对这片映射区域读写即可. 

>文件I/O:

- 文件I/O操作使用文件的API函数(open, read, write, close)对文件进行打开和读写操作. 文件存储于磁盘中, 我们通过`指定的文件名`打开一个文件, 就会得到一个`文件描述符`, 通过该文件描述符就可以找到该文件的`索引节点inode`, 根据inode就可以`找到`该文件在`磁盘上的存储位置`. 然后我们就可以直接调用read()/write()函数到磁盘指定的位置读写数据了. 
	- ![](assets/Pasted%20image%2020230515164658.png)
- 磁盘属于机械设备, 程序每次读写磁盘都要经过转动磁盘, 磁头定位等操作, `读写速度较慢`. 为了提高读写效率, 减少I/O读盘次数以保护磁盘, Linux内核基于`程序的局部原理`提供了一种`磁盘缓冲机制`
	- ![](assets/Pasted%20image%2020230515164642.png)
- 在内存中以`物理页`为单位`缓存磁盘上的普通文件或块设备文件`. 当应用程序读磁盘文件时, 会先到缓存中看数据是否存在, 若数据存在就直接读取并复制到用户空间; 若不存在, 则`先将磁盘数据读取到页缓存(page cache)中`, 然后从页缓存中复制数据到用户空间的buf中. 
- 当应用程序写数据到磁盘文件时, 会先将用户空间buf中的数据写入`page cache`, 当`page cache`中缓存的数据`达到设定的阈值`或者`刷新时间超时`, Linux`内核`会将这些数据`回写到磁盘`中. 
- `不同的进程`可能会`读写多个文件`, 不同的文件可能都要缓存到`page cache物理页`中. 如图所示, Linux`内核`通过一个叫作`radix tree的树结构`来管理这些`页缓存对象`. 一个物理页上可以是文件页缓存, 也可以是交换缓存, 甚至是普通内存. 
	- 以文件页缓存为例, 它通过一个叫作address_space的结构体让磁盘文件和内存产生关联. 我们通过文件名可以找到该文件对应的inode, inode->imapping成员指向address_space对象, 物理页中的page->mapping指向页缓存owner的address_space, 这样文件名和其对应的物理页缓存就产生了关联. 
	- 当我们读写指定的磁盘文件时, 通过文件描述符就可以找到该文件的address_space, 通过传进去的文件位置偏移参数就可以到页缓存中查找对应的物理页, 若查找到则读取该物理页上的数据到用户空间; 若没有查找到, 则Linux内核会新建一个物理页添加到页缓存, 从磁盘读取数据到该物理页, 最后从该物理页将数据复制到用户空间. 
- Linux内核中的页缓存机制在一定程度上提高了磁盘读写效率, 但是程序通过read()/write()频繁地系统调用还是会带来一定的性能开销. 系统调用会不停地切换CPU和操作系统的工作模式, 数据也在用户空间和内核空间之间不停地复制. 为了`减少系统调用`的次数, 尝到了缓存“甜头”的glibc决定进一步优化: 
	- ![](assets/Pasted%20image%2020230503222444.png)
	- 如图所示, 在`用户空间`开辟一个`I/O缓冲区`, 并`将系统调用read()/write()` 进一步`封装成fread()/fwrite()库函数`. 
	- 在用户空间, C标准库会`为每个打开的文件`分配一个`I/O缓冲区`和一个`文件描述符fd`. `I/O缓冲区信息和文件描述符fd`一起封装在`FILE结构体`中.
		- ![](assets/Pasted%20image%2020230503222617.png)
		- 用户可以通过这个`FILE类型`的文件指针, 调用`fread()/fwrite()` C标准库函数来读写文件.
		- 当`应用程序`通过`fread()函数读磁盘文件`时, 数据从`内核的页缓存`复制到`I/O缓冲区`, 然后复制到`用户的buf2`中, 当`fread`第二次读写磁盘文件时会`先到I/O缓冲区`里查看是否有要读写的数据, 如果有就直接读取, 如果没有就重复上面的流程, 重新缓存; 
		- 当程序通过`fwrite()`函数写文件时, 数据会先从`用户的buf1缓冲区`复制到`I/O缓冲区`, 当`I/O缓冲区满`时再`一次性复制到内核的页缓存`中, Linux内核在`适当的时机`再把页缓存中的数据回写到磁盘中. 
		- I/O缓冲区通过`减少系统调用的次数`来降低系统调用的开销, 但也增加了数据在不同缓冲区复制的次数: 一次读写流程要完成两次数据的复制操作. 当程序要读写的数据很大时, 这种文件I/O的开销也是很大的, 得不偿失. 


- 那么能不能通过进一步优化来`减少数据的复制次数`呢? 答案是能, 可以`将文件直接映射到进程虚拟空间`. 进程的虚拟地址空间与文件之间的映射关系如图:
	- ![](assets/Pasted%20image%2020230503223141.png)
- 我们可以通过`mmap系统调用`将文件直接映射到进程的虚拟地址空间中, 地址与文件数据一一对应, 对`这片内存映射区域`进行读写操作`相当于对磁盘上的文件进行读写操作`. 这种映射方式减少了内存复制和系统调用的次数, 可以进一步提高系统性能. 

>将文件映射到内存

- 将文件映射到内存主要由`mmap()/munmap()`函数来完成. mmap()的函数原型如下:
	- `void *mmap(void *addr, size_t length,int prot, int flags, int fd, off_t offset);`
	相关的参数:
- addr: 进程中要映射的虚拟内存起始地址, 一般为NULL. 
	- addr表示你要将文件映射到进程虚拟空间的地址, 可以显示指定, 也可以设置为NULL, 由系统自动分配.
	- mmap()映射成功会返给用户一个地址, 这个地址就是文件映射到进程虚拟空间的起始地址. 
	- 通过这个地址我们就与要读写的文件建立了关联, 用户对这片映射内存区域进行读写就相当于对文件进行读写.
- length: 要映射的内存区域大小。
- prot: 内存保护标志有PROT_EXEC, PROT_READ, PROT_WRITE.
- flags: 映射对象类型有MAP_FIXED, MAP_SHARED, MAP_PRIVATE.
- fd: 要映射文件的文件描述符.
- offset: 文件位置偏移.
- mmap以`页为单位`进行操作: `参数addr和offset必须按页对齐`.

接下来我们编写一个程序, 不通过文件I/O对文件进行读写, 而是通过mmap映射的内存进行读写. 通过映射内存往一个磁盘文件写数据的示例程序如下:
```c
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, i;
	char *p_map;
	fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, 0666);
	write(fd, "", 1);
	p_map = (char *) mmap(NULL, 20, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p_map == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	close(fd);
	if(fd == -1)
	{
		perror("close");
		return -1;
	}
	memcpy(p_map, "hello\n", 7);
	sleep(5);
	if(munmap(p_map,20) == -1)
	{
		perror("munmap");
		return -1;
	}
	return 0;
}
```

编译上面的程序并运行，通过指定的文件名创建一个文本文件data.txt，然后在程序中向这片映射内存写入字符串“hello world”，就可以直接将这个字符串写入文本文件data.txt。

通过映射内存从一个文件数据读取数据的程序示例如下:
```c
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, i;
	char *p_map;
	fd = open(argv[1], O_CREAT|O_RDWR, 0666);
	p_map = (char *) mmap(NULL, 20, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p_map == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	close(fd);
	if(fd == -1)
	{
		perror("close");
		return -1;
	}
	printf("%s",p_map);
	if(munmap(p_map,20) == -1)
	{
		perror("munmap");
		return -1;
	}
	return 0;
}
```
编译上面的程序并运行，通过指定的文件名打开文本文件data.txt，将该文件映射到进程的虚拟空间，映射成功后，读取这片映射内存空间的数据就相当于读取data.txt文件中的数据。

>mmap映射实现机制分析

Linux下的每一个进程在内核中统一使用`task_struct`结构体表示. task_struct结构体的`mm_struct`成员用来描述`当前进程的内存布局信息`. 一个进程的虚拟地址空间分为不同的区域, 如代码段, 数据段, mmap区域等, 每一个区域都使用`vm_area_struct`结构体对象来描述. 

![](assets/Pasted%20image%2020230503225844.png)

各个`vm_area_struct`通过成员`vm_next, vm_prev`指针链成一个链表, 内嵌在vm_struct结构体中. 一个进程创建以后, 链表中的各个vm_area_struct结构体对象和进程虚拟空间中不同区域之间的对应关系如图:
- ![](assets/Pasted%20image%2020230503225909.png)

- 通过mmap()函数虽然完成了文件和进程虚拟空间的映射, 但是需要注意的是, 现在`文件还在磁盘上`. 当用户程序开始读写进程虚拟空间中的这片映射区域时, 发现这片映射区域`还没有分配物理内存`, 就会产生一个`缺页异常`, Linux`内存管理子系统`就会`给该片映射内存分配物理内存`, 将要读写的文件内容读取到这片内存, 最后将虚拟地址和物理地址之间的映射关系写入该进程的页表. 
- 文件映射的这片空间分配物理内存成功后, 我们再去读写文件时就不用使用文件的I/O接口函数了, 直接对进程空间中的这片映射区域读写即可. 
	- ![](assets/Pasted%20image%2020230504124406.png)
- 在实际编程中, 我们使用malloc()函数申请的动态内存一般被当作缓冲区使用, 免不了有大量的数据被搬来搬去, 
- 通过mmap()函数将文件直接映射到内存, 就可以`减少数据搬运的次数`. 
- 按照Linux信奉的“一切皆文件”的哲学思想, 我们也可以将映射的文件范围扩大, 一块普通的内存, 显卡, Frambuffer都是一个文件, 都可以映射到内存, `既减少了系统调用的次数`, 又`减少了数据复制的次数`, `性能相比文件I/O显著提高`. 
- 这也是我们使用malloc()函数申请大于128KB的内存时, malloc()函数底层采用mmap映射的原因.

>把设备映射到内存

Linux的设计思想是“一切皆文件”, 即无论是磁盘上的普通数据文件, 还是/dev目录下的设备文件, 甚至是一块普通的内存, 我们都可以把它看作一个文件, 并通过文件I/O接口函数read()/write()去读写它们. 

那当然, 我们也可以通过mmap()函数将一个设备文件映射到内存, 对映射内存进行读写同样也能达到对设备文件进行读写的目的. 

以LCD屏幕的显示为例，如图所示，无论是计算机的显示器还是手机的显示屏，其主要部件一般包括LCD屏幕、LCD驱动器、LCD控制器和显示内存。

LCD屏幕有和它配套的显示内存，LCD屏幕上的每一个像素都和显示内存中的数据一一对应，通过配置LCD控制器可以让LCD驱动器工作，将显示内存上的数据一一对应地在屏幕上显示。
- ![](assets/Pasted%20image%2020230504124732.png)

和51单片机经常搭配使用的LCD1602液晶屏显示模块. 
LCD1602不仅包括液晶屏幕, 背面还有驱动控制电路, 里面集成的还有`显示内存`, 直接在显存里写入数据就可以在液晶屏上显示指定的字符了. 

X86环境下的显示控制模块通常以显卡的形式直接插到主板上, 显卡又分为集成显卡和独立显卡, 独立显卡模块有自己单独的显示内存, 而集成显卡则没有自己独立的显示内存, 要占用内存的一片地址空间作为显存使用. 

在嵌入式ARM平台上, LCD控制器通常以IP的形式集成到SoC芯片上, 和X86的集成显卡类似, 也要占用一部分`内存空间作为显示内存`, 因此我们可以看到ARM平台上外接的LCD屏通常很薄, 就是一个包含驱动电路的屏幕, 通过引出的几根引线接口可以直接插到嵌入式开发板上. 

不同的嵌入式平台, 外接的屏幕大小, 尺寸, 分辨率都不一样. 为了更好地适配不同的显示屏, Linux内核在驱动层对不同的LCD硬件设备进行抽象, 屏蔽底层的各种硬件差异和操作细节, 抽象出一个`帧缓存设备`——Framebuffer. 

`Framebuffer是Linux对显存抽象的一种虚拟设备`, 对应的设备文件为`/dev/fb`, 它为Linux的显示提供了统一的接口. 用户不用关心硬件层到底是怎么实现显示的, 直接往帧缓存写入数据就可以在对应的屏幕上显示自己想要的字符或图像. 

以ARM vexpress仿真平台为例, 帧缓存设备对应的设备文件节点为/dev/fb0. 向设备文件/dev/fb0写入数据有`两种方式`, 如图所示: 
- 第一种是使用open/read/write接口像普通文件一样对设备进行读写, 这种操作方式容易理解, 但是当要显示的数据很大时, 大块数据在用户空间的缓冲区和内核的缓存之间来回复制会影响系统的性能. 
	- ![](assets/Pasted%20image%2020230504125732.png)
- 我们一般采用第二种mmap映射的方式, 把设备文件像磁盘上的普通文件一样直接映射到进程的虚拟地址空间, 应用程序在用户空间直接对映射内存进行读写就可以实时地在屏幕上显示出来.

```c
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	int i= 100;
	unsigned char *fb_mem;
	fd = open("/dev/fb0", O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	fb_mem = mmap(NULL, 800*600, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p_map == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	while(1)
	{
		memset(fb_mem, i++, 800*600);
		sleep(1);
	}
	close(fd);
	return 0;
}
```
在上面的程序中, 我们将Framebuffer的设备文件/dev/fb0通过mmap()直接映射到了进程的虚拟空间中. 通过mmap()返回的指针fb_mem, 我们就可以直接对这片映射区域写入数据, 不断地向屏幕`800*600`大小的显存区域写入随机数据.

编译上面的程序并在ARM vexpress仿真开发板上运行，在LCD屏幕上可以看到`800*600`大小的显示区域内，屏幕显示的颜色一直在不断变化，运行效果如图:
- ![](assets/Pasted%20image%2020230504131444.png)

>多进程共享动态库

通过之前的学习, 我们对动态库的动态链接和重定位过程已经很熟悉了, 再加上本章对mmap映射的理解, 我们就可以接着分析一个被加载到内存的动态库是`如何被多个进程共享的`. 

当动态库第一次被链接器加载到内存参与动态链接时, 如图所示, 动态库映射到了当前进程虚拟空间的mmap区域, 动态链接和重定位结束后, 程序就开始运行. 
- ![](assets/Pasted%20image%2020230504131802.png)

当程序访问mmap映射区域, 去调用动态库的一些函数时, 发现此时还没有为这片虚拟空间分配物理内存, 就会产生一个缺页异常. 内核接着会为这片映射内存区域分配物理内存, 将动态库文件`libtest.so`加载到物理内存, 并将虚拟地址和物理地址之间的映射关系更新到进程的页表项, 此时动态库才真正加载到物理内存, 程序才可以正常运行. 

对于`已经加载到物理内存的文件`, Linux内核会通过一个`radix tree的树结构`来管理这些页缓存对象. 在下图中, 当进程B运行也`需要加载`动态库`libtest.so`时, `动态链接器`会将库文件libtest.so映射到`进程B的一片虚拟内存空间`上, 链接重定位完成后进程B开始运行. 

当通过映射内存地址访问libtest.so时也会触发一个缺页异常, Linux内核在分配物理内存之前会`先从radix tree树中查询libtest.so是否已经加载到物理内存`, 当内核发现libtest.so库文件已经加载到内存后就不会给进程B分配新的物理内存, 而是`直接修改进程B的页表项`, 将进程B中的这片映射区域直接映射到libtest.so所在的物理内存上. 
- ![](assets/Pasted%20image%2020230504132017.png)

通过上面的分析我们可以看到, `动态库libtest.so只加载到物理内存一次`, 后面的进程如果需要链接这个动态库, 直接将该库文件`映射到自身进程的虚拟空间即可`, 同一个动态库虽然被映射到了多个进程的不同虚拟地址空间, 但是通过MMU地址转换, `都指向了物理内存中的同一块区域`. 此时动态库libtest.so也被多个进程共享使用, 因此动态库也被称作`动态共享库`. 

### 内存泄露与防范

内存泄漏是很多初学者在软件开发中经常遇到的一个问题, 要想编写一个可以长期稳定运行的程序, 预防内存泄漏是必不可少的一环. 要想快速定位内存泄漏, 掌握一些常用的调试手段和工具, 了解内存泄漏背后的原理也是很有必要的. 

>一个内存泄露的例子

```c
#include <stdlib.h>
int main(void)
{
	char *p;
	p = (char *) malloc (32);
	strcpy(p, “hello”);
	puts(p);
	return 0;
}
```

上面代码malloc()申请的内存在使用结束后没有及时被释放, 则C标准库中的内存分配器ptmalloc和内核中的内存管理子系统都失去了对这块内存的追踪和管理.

失去管理和追踪的这块内存, 一直孤零零地躺在内存的某片区域, 用户, 内存分配器和内存管理子系统都不知道它的存在, 它就像内存中的一块漏洞, 我们称这种现象为`内存泄漏`.  memory leak.

函数运行结束退出后, 随着函数栈帧的销毁, 指针局部变量p也就随之释放掉了, 用户再也无法通过指针变量p来访问这片内存, 也就失去了对这块内存的控制权. 

在函数退出之前, 如果我们没有使用free()函数及时地将这块内存归还给内存分配器ptmalloc或内存管理子系统, ptmalloc和内存管理子系统就失去了对这块内存的控制权, 它们可能认为用户还在使用这片内存. 等下次去申请内存时, 内存分配器和内存管理子系统都没有这块内存的信息, 所以不可能把这块内存再分配给用户使用. 

- 下图中有大小为548 Byte和504 Byte的两个内存块, 一开始这两个内存块是在空闲链表中的, 当用户使用malloc()申请内存时, 内存分配器ptmalloc将这两个内存块节点从空闲链表中摘除, 并把内存块的地址返给用户使用. 如果用户使用后忘了归还, 那么空闲链表中就没有了这两个内存块的信息, 这两块内存也就无法继续使用了, 在内存中就产生了两个“漏洞”, 即发生了内存泄漏. 
	- ![](assets/Pasted%20image%2020230504152533.png)

>预防内存泄漏

预防方法:
- malloc后及时地free
- 代码review
- 使用相关工具检测

预防内存泄漏最好的方法就是: 内存申请后及时地释放, 两者要配对使用, 内存释放后要及时将指针设置为NULL, 使用内存指针前要进行非空判断.

如果在一个函数内部, 我们使用malloc()申请完内存后没有及时释放, 则很容易通过代码审查找到漏洞并及时修复. 随着程序的逻辑越来越复杂, 函数嵌套的层数越来越深, 当内存的申请与释放由不同的函数实现时, 估计这个漏洞就很难被发现了. 
```c
#include <stdlib.h>

int main(void)
{
	char *p;
	p = (char *) malloc(32);
	strcpy(p, "hello");

	if(cond1)
		return -1;
	puts(p);

	if(cond2)
		goto quit;

	free(p);
quit:
	return 0;
}
```
上面就是另一个内存泄露的例子.

为了预防这种情况发生，在程序的各个异常分支出口，要注意检查内存资源是否已经释放，检查通过后再退出。

一般情况下，本着“谁污染谁治理”的原则，在一个函数内申请的内存，在函数退出之前要自己释放掉。但有时候我们在一个函数内申请的内存，可能保存到了一个全局队列或链表中进行管理和维护，或者需要在其他函数里释放，当函数的调用关系变得复杂时，就很容易产生内存泄漏。为了预防这种错误的发生，在编程时，如果我们在一个函数内申请了内存，则要在申请处添加注释，说明这块内存应该在哪里释放。

>内存泄露检测

内存检测工具:
- Mtrace
- Valgrind
- Dmalloc
- Purify
- Kcachegrind
- MallocDebug

>内存泄漏检测：MTrace

MTrace是Linux系统自带的一个工具，它通过跟踪内存的使用记录来动态定位用户代码中内存泄漏的位置。使用MTrace很简单，在代码中添加下面的接口函数就可以了。
```c
#include <mcheck.h>
void mtrace();
void muntrace();
```

mtrace()函数用来开启内存使用的记录跟踪功能，muntrace()函数用来关闭内存使用的记录跟踪功能。如果想检测一段代码是否有内存泄漏，则可以把这两个函数添加到要检测的程序代码中。
- ![](assets/Pasted%20image%2020230504153544.png)
	- 开启跟踪功能后，MTrace会跟踪程序代码中使用动态内存的记录，并把跟踪记录保存在一个文件里，这个文件可以由用户通过MALLOC_TRACE来指定。接下来我们编译、运行这个程序，并使用MTrace来定位内存泄漏的位置.
		- ![](assets/Pasted%20image%2020230504153605.png)
		- 通过生成的日志文件mtrace.log来定位内存泄漏在程序中的位置。
		- ![](assets/Pasted%20image%2020230504153616.png)
		- 根据动态内存的使用记录，我们可以很快定位到内存泄漏发生在mcheck.c文件中的第11行代码。

广义上的内存泄露:
- 狭义上的内存泄漏
	- 申请了内存，没有释放，无法对这块内存进行管理
- 广义上的内存泄漏
	- 系统频繁地进行内存申请和释放，导致内存碎片越来越多、无法申请大片连续的内存
	- Fast bins：提高内存分配速度的同时，也会带来大量内存碎片


不同的计算机和服务器系统，不同的业务需求，对堆内存的使用频率和内存大小需求也不相同。为了最大化地提高系统性能，我们可以通过一些参数对glibc的内存分配器进行调整，使之与我们的实际业务需求达到更大的匹配度，更高效地应对实际业务的需求。

glibc底层实现了一个mallopt()函数，可以通过这个函数对上面的各种参数进行调整。
```c
#include <malloc.h>
int mallopt(int param, int value);
```
对参数的说明如下:
- M_ARENA_MAX: 可创建的最大内存分区数, 在多线程环境下经常创建多个分区. 
- M_MMAP_MAX: 可以申请映射分区的个数, 设置为0则表示关闭mmap映射功能. 
- M_MMAP_THRESHOLD: 当申请的内存大于此阈值时, 使用mmap分配内存, 默认此阈值大小是128KB.
- M_MXFAST: fast bins中内存块的大小阈值, 最大`80*sizeof(size_t)/4`, 设置为0则表示关闭fast bins功能. 
-  M_TOP_PAD: 调用sbrk()每次向系统申请/释放的内存大小。
- M_TRIM_THRESHOLD: 当top chunk大小大于该阈值时, 会释放bins中的一部分内存以节省内存. 
- 这些参数的默认值及可以配置的范围值如图所示:
	- ![](assets/Pasted%20image%2020230504154144.png)
	- ![](assets/Pasted%20image%2020230504154120.png)

为了避免fast bins带来的内存碎片化, 用户可根据自己的实际业务需求, 将参数M_MXFAST设置为0, 关闭fast bins功能. 不同的业务逻辑对内存的需求不同, 在使用频率和大小上都不一样, 大家可根据实际业务场景, 对多个参数进行调优, 进一步提高内存分配的效率, 确保系统更加高效稳定地运行. 

### 常见内存错误及检测

现在的处理器引入MMU后, 操作系统接管了内存管理的工作, 负责虚拟空间和物理空间的地址映射和权限管理. 如图所示, 内存管理子系统将一个进程的虚拟空间划分为不同的区域, 如代码段, 数据段, BSS段, 堆, 栈, mmap映射区域, 内核空间等, 每个区域都有不同的读, 写, 执行权限. 
- ![](assets/Pasted%20image%2020230504154639.png)

通过内存管理, 每个区域都有具体的访问权限, 如只读, 读写, 禁止访问等. 数据段, BSS段, 堆栈区域都属于读写区, 而代码段则属于只读区, 如果你往代码段的地址空间上写数据, 就会发生一个段错误. 

在Linux用户进程的4GB虚拟空间上, 除了上面我们熟悉的区域, 还剩下很多区域, 如代码段之前的区域, 堆和mmap区域之间的进程空间, 内核空间等. 这部分内存空间是禁止用户程序访问的. 当一个用户进程试图访问这部分空间时, 就会被系统检测到, 在Linux下系统会向当前进程发送一个信号SIGSEGV, 终止该进程的运行. 

当一个进程试图非法访问内存时, 通过内存管理机制可以及时检测到并制止该进程的进一步破坏行为, 以免造成系统崩溃. 发生段错误的进程被终止运行后, 不会影响系统中其他进程的运行, 系统依旧照常运行. 

所以说, 一个程序发生内存错误未必是一件坏事情, 当计算机蓝屏或内核崩溃发生了OOPS时, 那么问题可能就比较麻烦了. 

对于应用程序来说, 常见的内存错误:
- 内存越界
- 内存踩踏
- 多次释放
- 非法指针

发生段错误的根本原因在于非法访问内存，即访问了权限未许可的内存空间。

引发段错误的行为:
- 访问内存禁区
	- 内核空间, 零地址, 堆和mmap区域之间的内存空间
		- ![](assets/Pasted%20image%2020230504155043.png)
	- 当我们往一个只读区域的地址空间执行写操作时, 或者访问一个禁止访问的地址(如零地址)时, 都会发生段错误. 在实际编程中, 总会因为各种各样的疏忽不小心触碰到这些“红线”, 导致段错误.
		- ![](assets/Pasted%20image%2020230504155121.png)
		- 编译运行上面的程序，可能正常运行，也可能会发生段错误。
- 栈溢出
- 数组越界访问
- 多次free()

>第三方工具内存检测

- 使用core dump调试段错误:

- 在Linux环境下运行的应用程序, 由于各种异常或Bug, 会导致程序退出或被终止运行. 
- 此时系统会将该程序运行时的内存, 寄存器状态, 堆栈指针, 内存管理信息, 各种函数的堆栈调用信息保存到一个core文件中. 在嵌入式系统中, 这些信息有时也会通过串口打印出来. 
- 我们可以根据这些信息来定位问题到底出在了哪里, 以上面的doublefree为例, 编译程序并运行, 开启core dump功能.
	- ![](assets/Pasted%20image%2020230504155612.png)
	- ![](assets/Pasted%20image%2020230504155618.png)
	- core dump功能开启后运行a.out, 发生段错误后就会在当前目录下生成一个core文件, 然后我们就可以使用gdb来解析这个core文件, 来定位程序到底出错在哪里. 
		- ![](assets/Pasted%20image%2020230504155711.png)
		- ![](assets/Pasted%20image%2020230504155716.png)
		- 在GDB交互环境下, 我们通过bt查看调用栈信息, 就可以很快将段错误定位到double_free.c的第8行. 
		- ![](assets/Pasted%20image%2020230504155730.png)

>什么是内存踩踏

内存踩踏如幽灵一般, 比段错误更加隐蔽, 更加难以定位, 因为有时候内存踩踏并不会报错, 然而你的程序却出现各种莫名其妙地运行错误. 当你把代码看了一遍又一遍, 找不出任何问题, 甚至开始怀疑人生时, 就要考虑内存踩踏了. 

- 举个栗子:
	- ![](assets/Pasted%20image%2020230504155853.png)
	- 在上面的程序中, 我们申请了两块动态内存, 对其中的一块内存写数据时产生了溢出, 就会把溢出的数据写到另一块缓冲区里. 在缓冲区释放之前, 系统是不会发现任何错误的, 也不会报任何提示信息, 但是程序却可能因为误操作, 覆盖了另一块缓冲区的数据, 造成程序莫名其妙的错误. 编译运行上面的程序, 分别打印两个内存中的数据. 
		- ![](assets/Pasted%20image%2020230504155929.png)
		- 我们申请的q指针指向的内存已经被踩踏了，如果这个程序在系统运行期间一直运行，在这块内存被free之前，这个错误可能一直不会被检测到。

如果一个进程中有多个线程, 多个线程都申请堆内存, 这些堆内存就可能彼此相邻, 使用时需要谨慎, 提防越界. 

在内核驱动开发中, 驱动代码运行在特权状态, 对内存访问比较自由, 多个驱动程序申请的物理内存也可能彼此相邻. 如果你的程序代码经常莫名其妙地崩溃, 而且每次出错的地方也不一样, 在确保自己的代码没问题后, 也可以大胆地去怀疑一下是不是内存踩踏的问题. 

当然，我们也可以使用一些工具或Linux系统提供的API函数去检测内存踩踏。

>内存踩踏监测：mprotect

mprotect()是Linux环境下一个用来保护内存非法写入的函数, 它会监测要保护的内存的使用情况, 一旦遇到非法访问就立即终止当前进程的运行, 并产生一个core dump. mprotect()函数的原型如下:
```c
#include <sys/mman.h>
int mprotect(void *addr, size_t len, int prot);
```

mprotect()函数的第一个参数为`要保护的内存的起始地址`, len表示内存的长度, 第三个参数prot表示要设置的内存访问权限. 
- PROT_NONE：这块内存禁止访问，禁止读、写、执行。
- PROT_READ：这块内存只允许读。
- PROT_WRITE：这块内存可以读、写。
- PROT_EXEC：这块内存可以读、写、执行。

页(page)是Linux内存管理的基本单元, 在32位系统中, 一个页通常是4096字节, mprotect()要保护的内存单元通常要以页地址对齐, 我们可以使用`memalign()`函数申请一个以页地址对齐的一片内存:
- ![](assets/Pasted%20image%2020230504160333.png)
	- 在上面的程序中, 我们使用memalign() 函数`申请了一块以页大小对齐的512字节的内存`, 然后将这片内存`设置为只读`, 接下来我们往这片内存写入数据, 看看会发生什么. 
	- ![](assets/Pasted%20image%2020230504160423.png)
	- 在内存设置为只读之前，我们往这片内存写数据是正常的。将这块内存设置为只读后，再往这块内存写数据，当前进程就会终止运行，并产生一个core dump。根据这个core dump文件，我们就可以使用gdb很方便地定位内存踩踏的位置。
	- ![](assets/Pasted%20image%2020230504160512.png)
	- ![](assets/Pasted%20image%2020230504160516.png)

> 内存检测神器：Valgrind

除了使用系统提供的各种API函数, 我们还可以使用内存工具检测不同类型的内存错误. 以Valgrind为例, 不仅可以检测内存泄漏, 还可以对程序进行各种性能分析, 代码覆盖测试, 堆栈分析及CPU的Cache命中率, 丢失率分析等. 这么好的工具, 此时不用, 更待何时?

- 使用valgrind内存检测
	- Memcheck:内存检测
	- Callgrind：程序性能分析、代码覆盖检测
	- Massif:堆栈分析器
	- Cachegrind：分析CPU的cache命中率、丢失率，用于代码优化

- Valgrind包含一套工具集, 其中一个内存检测工具Memcheck可以对我们的内存进行`内存覆盖`, `内存泄漏`, `内存越界检测`. Valgrind的安装及使用步骤如下:
	- ![](assets/Pasted%20image%2020230504160633.png)
	- 接下来我们写一个内存泄漏的示例程序, 看看使用Valgrind工具能否检测出来. 
	- ![](assets/Pasted%20image%2020230504160648.png)
	- 编译运行上面的程序，并使用Valgrind工具集的Memcheck工具检测:
	- ![](assets/Pasted%20image%2020230504160701.png)
	- 根据检测的打印信息我们可以看到, 当前程序一共申请了3块堆内存, 释放了2次, 还有一块32字节的内存在程序退出时没有释放. 如果想看更详细的堆内存信息, 则在编译时多加一个参数--leak-check=full即可, 工具会把程序中内存泄漏的源码位置打印出来. 如下所示, 内存泄漏发生在源码的第7行(mem_leak.c:7).
	- ![](assets/Pasted%20image%2020230504160752.png)
	- ![](assets/Pasted%20image%2020230504160759.png)

- Memcheck工具不仅能检测内存泄漏, 还能检测内存越界. 下面我们写一个内存越界的例子, 看看Valgrind能否检测出来:
	- ![](assets/Pasted%20image%2020230504160821.png)
	- 编译上面的程序，并使用Valgrind进行内存踩踏检测。
	- ![](assets/Pasted%20image%2020230504160829.png)
	- ![](assets/Pasted%20image%2020230504160836.png)
	- 通过打印信息, 我们可以很容易地看到在mem_overwrite.c文件的第11行发生了非法写操作, 根据这些提示信息就可以去修改自己的程序了. 

把上面的代码中的while(1)去掉, 还有一个错误, 就是q内存区域的 数据头 区域, 被写入p的字符串给踩踏了. 导致free(q)的时候, q的数据头没了, glibc没有办法依据数据头来管理这段内存了. 所以会报错.