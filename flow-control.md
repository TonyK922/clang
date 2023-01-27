# 流程控制

C 语言的程序是顺序执行，即先执行前面的语句，再执行后面的语句。开发者如果想要控制程序执行的流程，就必须使用流程控制的语法结构，主要是**顺序执行**, **条件执行**和**循环执行**。

## if 语句

`if语句`, `?:运算符`跟 `switch语句`都是条件选择执行.

`if`语句用于条件判断，满足条件时，就执行指定的语句。

```c
if (expression) statement
```

上面式子中，表达式`expression`为真（值不为`0`）时，就执行`statement`语句。

`if`后面的判断条件`expression`外面必须有圆括号，否则会报错。语句体部分`statement`可以是一个语句，也可以是放在大括号里面的复合语句。下面是一个例子。

```c
if (x == 10) printf("x is 10");
```

上面示例中，当变量`x`为`10`时，就会输出一行文字。对于只有一个语句的语句体，语句部分通常另起一行。

```c
if (x == 10)
  printf("x is 10\n"); //puts("x is 10");
```

如果有多条语句，就需要把它们放在大括号里面，组成一个**复合语句**。

```c
if (line_num == MAX_LINES) {
  line_num = 0;
  page_num++;
}
```

`if`语句可以带有`else`分支，指定条件不成立时（表达式`expression`的值为`0`），所要执行的代码。

```c
if (expression) statement
else statement
```

下面是一个例子。

```c
if (i > j)
  max = i;
else
  max = j;
```

如果`else`的语句部分多于一行，同样可以把它们放在大括号里面。

`else`可以与另一个`if`语句连用，构成多重判断。

```c
if (expression)
  statement
else if (expression)
  statement
...
else if (expression)
  statement
else
  statement
```

如果有多个`if`和`else`，可以记住这样一条规则，`else`总是**跟最接近**的`if`匹配。

当if else后面的大括号被省略时, else会自动和距离最近的一个if匹配.

```c
if (number > 6)
  if (number < 12)
    printf("The number is more than 6, less than 12.\n");
else
  printf("It is wrong number.\n");

//2:
int main(){
    if(0)
    if(1)
    printf("A\n");
    else // 和if(1)匹配
    printf("B\n");
    else // 和if(0)匹配, 因为if(1)已经被匹配过了
    if (1)
    printf("C\n"); // 输出C
    else // 和if(1)匹配
    printf("D\n");
}
```

上面示例中，`else`部分匹配最近的`if`（即`number < 12`），所以如果`number`等于6，就不会执行`else`的部分。

这样很容易出错，为了提供代码的可读性，建议使用大括号，明确`else`匹配哪一个`if`。

```c
if (number > 6) {
  if (number < 12) {
    printf("The number is more than 6, less than 12.\n");
  }
} else {
  printf("It is wrong number.\n");
}
```

上面示例中，使用了大括号，就可以清晰地看出`else`匹配外层的`if`。

- 如果if else省略了大括号, 那么后面不能定义变量:

```c
int main(){
    if(1)
        int number = 10; // 系统会报错
    printf("number = %i\n", number);
}


int main(){
    if(0){
        int number = 10; 
    }else
        int value = 20; // 系统会报错
    printf("value = %i\n", value);
}
```

- 但凡遇到比较一个变量等于或者不等于某一个常量的时候，把常量写在前面

```c
#include <stdio.h>
int main(){
    int a = 8;
//    if(a = 10){// 错误写法, 但不会报错
    if (10 == a){
      printf("a的值是10\n");
    }else{
     printf("a的值不是10\n");
    }
}
```



注意事项:

- 语句不一定是分号结尾, if()语句后面不能加分号
- 相同的嵌套层次采用相同的缩进, 一般4个字符
- if语句风格
- 执行概率高, 判断逻辑简单的分支, 放前面
- else匹配是 始终与同一大括号内最近的未匹配的if语句结合.

## 三元运算符 ?:

C 语言有一个三元表达式`?:`，可以用作`if...else`的简写形式。

```c
<expression1> ? <expression2> : <expression3>
```

这个操作符的含义是，表达式`expression1`如果为`true`（非0值），就执行`expression2`，否则执行`expression3`。

下面是一个例子，返回两个值之中的较大值。

```c
(i > j) ? i : j;
```

上面的代码等同于下面的`if`语句。

```c
if (i > j)
  return i;
else
  return j;
```

## switch 语句

switch 语句是一种特殊形式的 if...else 结构，用于判断条件有多个结果的情况。它把多重的`else if`改成更易用、可读性更好的形式。

```c
switch (expression) {
  case value1: statement
  case value2: statement
  default: statement
}
```

上面代码中，根据表达式`expression`不同的值，执行相应的`case`分支。如果找不到对应的值，就执行`default`分支。 `expression` 一般是整型值或字符型, 不能是浮点数.

- case的值只能是`常量` 并且还必须是`整型`, 或者可以被提升为整型的值(char、short).  

- case后面常量表达式的值不能相同. 

- case后面要想定义变量,必须给case加上大括号, 形成复合语句.

- switch中只要任意一个case匹配, 其它所有的case和default都会失效. 所以如果case和default后面没有break就会出现穿透问题
- switch中default的位置不一定要写到最后, 无论放到哪都会等到所有case都不匹配才会执行(穿透问题除外)
- switch中default可以省略

- 看上去if和switch都可以实现同样的功能, 那么在企业开发中我们什么时候使用if, 什么时候使用switch呢?

- - if else if 针对于范围的多路选择
  - switch 是针对点的多路选择

下面是一个例子。

```c
switch (grade) {
  case 0:
    printf("False");
    break;
  case 1:
    printf("True");
    break;
  default:
    printf("Illegal");
}
```

上面示例中，根据变量`grade`不同的值，会执行不同的`case`分支。如果等于`0`，执行`case 0`的部分；如果等于`1`，执行`case 1`的部分；否则，执行`default`的部分。`default`表示处理以上所有`case`都不匹配的情况。

每个`case`语句体的结尾，都应该有一个`break`语句，作用是跳出整个`switch`结构，不再往下执行。如果缺少`break`，就会导致继续执行下一个`case`或`default`分支。称为穿透.

```c
switch (grade) {
  case 0:
    printf("False");
  case 1:
    printf("True");
    break;
  default:
    printf("Illegal");
}
```

上面示例中，`case 0`的部分没有`break`语句，导致这个分支执行完以后，不会跳出`switch`结构，继续执行`case 1`分支。

利用这个特点，如果多个`case`分支对应同样的语句体，可以写成下面这样。

```c
switch (grade) {
  case 0:
  case 1:
    printf("True");
    break;
  default:
    printf("Illegal");
}
```

上面示例中，`case 0`分支没有任何语句，导致`case 0`和`case 1`都会执行同样的语句体。

`case`后面的语句体，不用放在大括号里面，这也是需要`break`的原因。

`default`分支用来处理前面的 case 都不匹配的情况，最好放在所有 case 的后面，这样就不用写`break`语句。这个分支是可选的，如果没有该分支，遇到所有的 case 都不匹配的情况，就会直接跳出整个 switch 代码块。

注意事项:

- case后面各个常量或常量表达式的值必须各不相同, 类型一般为**整型**.
- case语句中的符合语句, 视情况加break.
- 执行概率或频率高的, 放前面.
- default分支一般用于错误处理, 不要作为其中一个处理分支.

## while 语句

`while, do while, for` 三个是循环执行语句.

`while`语句用于循环结构，满足条件时，不断执行循环体。

- 构成循环结构的几个条件

- - 能够让循环条件为假的依据,否则退出循环
  - 循环的过程中重复执行的代码段
  - 循环退出的主要依据,来控制循环到底什么时候退出
  - 循环控制条件
  - 循环体
  - 能够让循环结束的语句(递增、递减、真、假等)

- while循环执行流程

- - 首先会判定"循环控制条件"是否为真, 如果为假直接跳到循环语句后面
  - 如果"循环控制条件"为真, 执行一次循环体, 然后再次判断"循环控制条件"是否为真, 为真继续执行循环体,为假跳出循环
  - 重复以上操作, 直到"循环控制条件"为假为止

```c
while (expression)
  statement
```

上面代码中，如果表达式`expression`为非零值（表示真），就会执行`statement`语句，然后再次判断`expression`是否为零；如果`expression`为零（表示伪）就跳出循环，不再执行循环体。

```c
while (i < n)
  i = i + 2;
```

上面示例中，只要`i`小于`n`，`i`就会不断增加2。

如果循环体有多个语句，就需要使用大括号将这些语句组合在一起。

```c
while (expression) {
  statement;
  statement;
}
```

下面是一个例子。

```c
i = 0;

while (i < 10) {
  printf("i is now %d!\n", i);
  i++;
}

printf("All done!\n");
```

上面代码中，循环体会执行10次，每次将`i`增加`1`，直到等于`10`才退出循环。

只要条件为真，`while`会产生无限循环。下面是一种常见的无限循环的写法。

```c
while (1) {
  // ...
}
```

上面的示例虽然是无限循环，但是循环体内部可以用`break`语句跳出循环。

## do...while 结构

`do...while`结构是`while`的变体，它会先执行一次循环体，然后再判断是否满足条件。如果满足的话，就继续执行循环体，否则跳出循环。

- do-while循环执行流程

- - 首先不管while中的条件是否成立, 都会执行一次"循环体"
  - 执行完一次循环体,接着再次判断while中的条件是否为真, 为真继续执行循环体,为假跳出循环
  - 重复以上操作, 直到"循环控制条件"为假为止

```c
do statement
while (expression);
```

上面代码中，不管条件`expression`是否成立，循环体`statement`至少会执行一次。每次`statement`执行完毕，就会判断一次`expression`，决定是否结束循环。

```c
int main()
{
    int num = -1;
    do{
        printf("请输入密码,验证您的身份\n");
        scanf("%d", &num);
    }while(123456 != num);
    printf("主人,您终于回来了\n");
}
```

上面示例中，变量`i`先减去1，再判断是否大于0。如果大于0，就继续减去1，直到`i`等于`0`为止。

如果循环部分有多条语句，就需要放在大括号里面。

```c
i = 10;

do {
  printf("i is %d\n", i);
  i++;
} while (i < 10);

printf("All done!\n");
```

上面例子中，变量`i`并不满足小于`10`的条件，但是循环体还是会执行一次。

while和do while应用场景

- 绝大多数情况下while和do while可以互换, 所以能用while就用while
- 无论如何都需要先执行一次循环体的情况, 才使用do while
- do while 曾一度提议废除，但是他在输入性检查方面还是有点用的

注意: 

`while() {}` 没有分号

`do{} while(); `有分号

## for 语句

`for`语句是最常用的循环结构，通常用于精确控制循环次数。

- for和while应用场景

- - while能做的for都能做, 所以企业开发中能用for就用for, 因为for更为灵活
  - 而且对比while来说for更节约内存空间

```c
for (initialization; continuation; action)
  statement;
```

上面代码中，`for`语句的条件部分（即圆括号里面的部分）有三个表达式。

- `initialization`：初始化表达式，用于初始化循环变量，只执行一次。
- `continuation`：判断表达式，只要为`true`，就会不断执行循环体。
- `action`：循环变量处理表达式，每轮循环结束后执行，使得循环变量发生变化。

循环体部分的`statement`可以是一条语句，也可以是放在大括号里面的复合语句。下面是一个例子。

```c
for (int i = 10; i > 0; i--)
  printf("i is %d\n", i);
```

上面示例中，循环变量`i`在`for`的第一个表达式里面声明，该变量只用于本循环体。离开循环体之后，就会失效。

条件部分的三个表达式，每一个都可以有多个语句，语句与语句之间使用逗号分隔。

```c
int i, j;
for (i = 0, j = 999; i < 10; i++, j--) {
  printf("%d, %d\n", i, j);
}
```

上面示例中，初始化部分有两个语句，分别对变量`i`和`j`进行赋值。

`for`的三个表达式都不是必需的，甚至可以全部省略，这会形成无限循环。

```c
for (;;) {
  printf("本行会无限循环地打印。\n" );
}
```

上面示例由于没有判断条件，就会形成无限循环。

注意事项:

- for( ; ; ) 的表达式是可以省略的, 单个表达式也可以扩展位多个表达式或逻辑表达式语句, 语句之间用逗号隔开.
- for语句可以多重循环, 注意效率问题, 可以将长的循环放在内层, 短的循环放外层. 循环嵌套一般不要超过三层.
- 建议for循环空间使用半开半闭区间的写法, 或者坚持同一种写法. for循环体内一般不要修改循环变量, 防止循环失控.

## break 语句

`break`语句有两种用法。一种是与`switch`语句配套使用，用来中断某个分支的执行，这种用法前面已经介绍过了。另一种用法是在循环体内部跳出循环，**不再进行后面的循环了**。

立即跳出switch语句或循环. 

在多层循环中,一个break语句只向外跳一层.

```c
for (int i = 0; i < 3; i++) {
  for (int j = 0; j < 3; j++) {
    printf("%d, %d\n", i, j); 
    break; //跳回上一层循环
  }
}
```

上面示例中，`break`语句使得循环跳到下一个`i`。

```c
while ((ch = getchar()) != EOF) {
  if (ch == '\n') break;
  putchar(ch);
}
```

上面示例中，一旦读到换行符（`\n`），`break`命令就跳出整个`while`循环，不再继续读取了。

注意，`break`命令只能跳出循环体和`switch`结构，不能跳出`if`结构。

```c
if (n > 1) {
  if (n > 2) break; // 无效
  printf("hello\n");
}
```

上面示例中，`break`语句是无效的，因为它不能跳出外层的`if`结构。

## continue 语句

`continue`语句用于在循环体内部终止本轮循环，进入下一轮循环。只要遇到`continue`语句，循环体内部后面的语句就不执行了，回到循环体的头部，开始执行下一轮循环。

```c
for (int i = 0; i < 3; i++) {
  for (int j = 0; j < 3; j++) {
    printf("%d, %d\n", i, j);
    continue; //本次循环体到此为止, 执行j++
  }
}
```

上面示例中，有没有`continue`语句，效果一样，都表示跳到下一个`j`。

```c
while ((ch = getchar()) != '\n') {
  if (ch == '\t') continue; //回while()中
  putchar(ch);
}
```

上面示例中，只要读到的字符是制表符（`\t`），就用`continue`语句跳过该字符，读取下一个字符。

## goto 语句

goto 语句用于跳到指定的标签名。这会破坏结构化编程，建议不要轻易使用，这里为了语法的完整，介绍一下它的用法。 它是汇编遗老. 

```c
char ch;

top: ch = getchar();

if (ch == 'q')
  goto top;
```

上面示例中，`top`是一个标签名，可以放在正常语句的前面，相当于为这行语句做了一个标记。程序执行到`goto`语句，就会跳转到它指定的标签名。

```c
infinite_loop:
  print("Hello, world!\n");
  goto infinite_loop;
```

上面的代码会产生无限循环。

goto 的一个主要用法是跳出多层循环。

```c
for(...) {
  for (...) {
    while (...) {
      do {
        if (some_error_condition)
          goto bail;    
      } while(...);
    }
  }
}
    
bail:
// ... ...
```

上面代码有很复杂的嵌套循环，不使用 goto 的话，想要完全跳出所有循环，写起来很麻烦。

goto 的另一个用途是提早结束多重判断。

```c
if (do_something() == ERR)
  goto error;
if (do_something2() == ERR)
  goto error;
if (do_something3() == ERR)
  goto error;
if (do_something4() == ERR)
  goto error;
```

上面示例有四个判断，只要有一个发现错误，就使用 goto 跳过后面的判断。

注意，goto 只能在同一个函数之中跳转，并不能跳转到其他函数。

## 循环嵌套

- 循环结构的循环体中存在其他的循环结构，我们称之为循环嵌套

- 注意: 一般循环嵌套不超过三层
- 外循环执行的次数 * 内循环执行的次数就是内循环总共执行的次数

- 循环优化

- 在多重循环中，如果有可能，应当将**最长的循环放在最内层**，**最短的循环放在最外层**，以减少 CPU 跨切循环层的次数

  