想要读懂Linux内核源码还是需要一定功力的:
- 首先你的C语言基础一定要打牢，如结构体、指针、数组、函数指针、指针函数、数组指针、指针数组等，如果这些基础知识点你还要偷偷去翻书或者搜索，则说明得好好补一补基础了。
- 另外，C语言的一些GNU C扩展语法等也要熟悉，否则在阅读Linux内核源码时就会遇到各种语法障碍。
- 其次，一些常用的数据结构要掌握，如链表、队列等。Linux内核中使用大量的动态链表和队列来维护各种设备，管理各种事件，不掌握这些数据的动态变化就可能在跟踪源码时遇到障碍。
- 最后，要理解Linux内核中大量使用的面向对象编程思想。

面对千万行代码级的超大型工程，如果再按照以前的函数调用流程和数据流程去分析Linux内核，往往会让人感到捉襟见肘、力不从心，很容易一叶障目，迷失在森林深处。

Linux内核虽然是使用C语言编写的，但处处蕴含着面向对象的设计思想。以OOP为切入点去分析内核，从代码复用的角度可以帮助我们从一个盘根错节的复杂系统中勾勒出一个全局的框架，确保我们再次深入森林探险时能够手握地图，不再迷路。

其实C语言也可以实现面向对象编程。面向对象编程是一种编程思想，和使用的语言工具是没有关系的，只不过有些语言更适合面向对象编程而已。
- 如C++、Java新增了class关键字，就是为了更好地支持面向对象编程，通过类的封装和继承机制，可以更好地实现代码复用

使用C语言我们同样可以实现面向对象编程.

# 数据结构基础

> 数据结构学过专门的课程, 这里主要是复习和进阶, 主要去看看Linux内核里的数据结构.

## 数据结构基本概念

- 什么是数据结构
	- 程序 = 数据结构 + 算法
	- 数据结构：对客观事物的抽象
	- 数据的组织形式、数据之间的关联
- 数据元素
	- 数据的基本单位
	-  C语言基本数据类型：数组、结构体、共用体、枚举

数据结构基本概念

- 结构类型：顺序表, 栈, 链表, 队列, 树, 图…
- 逻辑结构：线性、非线性
- 存储结构：顺序存储、链式存储
- 基本操作：添加、删除、查找、遍历  

## 数据结构的重要性

- 编程技能
	- 程序 = 数据结构 + 算法
	- 内功：数据结构、算法
	- 招式：编程语言
	- 框架分层、代码复用、性能优化、复杂的业务逻辑

## 工程师层级划分
- 菜鸟
	- 遇到问题：百度、贴吧、QQ群，不知如何下手…
- 新手
	- 能通过编程完成交代的任务，代码可以运行，为demo级别
	- 遇到极端、边界情况会运行异常、不稳定、有bug，无法解决
	- 需求改变、功能添加导致程序结构臃肿、bug丛生、难以维护
- 老手
	- 经过新手期锻炼，开始重视数据结构与算法的重要性
	- 开始重视程序的健壮性、稳定性、可维护性
- 高手
	- 精通一门或多门语言，根据需求选择不同语言
	- 学会使用面向对象思想去抽象、去解构复杂的系统
	- 语言只是一个工具
- 专家
	- 设计模式：大量项目实战和经验积累、进一步理解面向对象思想
	- 架构设计：代码分层、模块耦合、性能优化…

## 数据结构怎么学
- 链表：设备管理
- 队列：工作队列、等待队列、消息队列
- 树：二叉树、红黑树、B树
- 哈希表：文件系统

# 什么是线性表

逻辑结构
- 线性结构
	- 数据元素之间是“一对一”的线性关系
	- 举例：线性表、栈、队列、数组
- 非线性结构
	- 数据元素之间是“一对多”、“多对多”树形或网络关系
	- 举例：树、图


线性表
- 相同数据类型的N个元素的序列
- 每个元素有且仅有一个前趋和后继

## 线性表分类

- 顺序存储
	- 顺序表
	- 数组
- 链式存储
	- 单链表
	- 双链表
	- 循环链表
	- 静态链表

## 单向链表

链表的定义

- 链表：链式存储的线性表
- 节点(node)：`数据域`、`指针域`
- 头指针
- 头节点
	- ![](assets/Pasted%20image%2020230508155045.png)

链表的基本操作

- 常用的基本操作
	- 判断链表是否为空
	- 插入节点
	- 删除节点
	- 遍历

> 对于链表, 不管是单向 双向, 循环还是非循环:
> 添加结点, 一定是先把添加的结点的指针域设好, 再去动前后节点
> 删除节点, 一定是先把前后节点设置好, 再去删那个要删的结点
> 插入, 删除都要注意链表为空的情况(只有头结点).
> 注意不要访问空指针.

```c
下面单向链表的操作基于这个结构体:
typedef struct list_node {
    int data;
    struct list_node *next;
} ListNode, *ListLink;
```

数组与链表

线性表
- 数组
- 链表

数组与链表比较
- 优点: 数组查找方便
- 缺点: 插入、删除不方便; 存储空间不灵活

```c
玩具代码: 想法不一样, 实现的内容就不一样. 一般插入都是先要查找要插入的位置的.

int is_list_empty(struct list_node* head)
{
    return (head->next == NULL);
}
void list_print(struct list_node* head)
{
    struct list_node* p;
    p = head->next;
    for (p; p != NULL; p = p->next)
        printf("p->data = %d\n", p->data);
}
void list_free(struct list_node* head)
{
    struct list_node *p, *q;
    q = head->next;
    p = q->next;
    while (q != NULL)
    {
        free(q);
        q = p;
        if (p != NULL)
            p = p->next;
        printf("p:%p q:%p\n", p, q);
    };
}
void list_add(struct list_node* head, struct list_node* node)
{
    node->next = head->next;
    head->next = node;
}
void list_add_tail(struct list_node* head, struct list_node* node)
{  
    struct list_node* p;
    for (p = head->next; p->next != NULL; p = p->next)
        ;
    p->next = node;
}
int list_delete(struct list_node* head, struct list_node* node)
{
    struct list_node* p;
    if (is_list_empty(head))
        return -1;
    if (node == head->next)
        head->next = node->next;
    else
    {
        for (p = head->next; p->next != node; p = p->next)
            ;
        p->next = node->next;
    }
    free(node);
    return 0;
}
struct list_node* list_foreach(struct list_node* head, int val)
{
    struct list_node* p;
    p = head->next;
    for (p; p->data != val; p = p->next)
        ;
    return p;
}
```

## 循环链表

跟单向链表不同, 循环链表的尾结点的指针域, 不指向NULL, 指向头结点.
- ![](assets/Pasted%20image%2020230508155306.png)

循环链表基本操作
- 创建
- 判断非空
- 添加节点
- 删除节点
- 遍历

```c
// 一般双向链表, 会有一个头指针和尾指针, 时刻记录着头结点和尾结点的实时位置.
struct headtail {
	struct list_node *head;
	struct list_node *tail;
} Note;
int list_init(ListNode **head)
{// 申请个头结点.
	struct list_node *p = (Listnode *)malloc(sizeof(ListNode));
	if(!p)
		return -1;
	p->next = NULL;
	*head = p; // 传进来的指针 的值指向这个头结点.
	Note.head = Note.tail = p; //目前头指针记录跟尾指针记录都是头结点地址
}
int is_list_empty(struct list_node* head)
{
    return (head->next == head);
}
void list_print(struct list_node* head)
{
    struct list_node* p;
    p = head->next;
    for (p; p != head; p = p->next)
        printf("p->data = %d\n", p->data);
}
void list_free(struct list_node* head)
{
    struct list_node *p, *q;
    q = head->next;
    p = q->next;
    while (q != head)
    {
        free(q);
        q = p;
        if (p != head)
            p = p->next;
        printf("p:%p q:%p\n", p, q);
    };
}
void list_add(struct list_node* head, struct list_node* node)
{
    node->next = head->next;
    head->next = node;
}
void list_add_tail(struct list_node* head, struct list_node* node)
{
    struct list_node* p;
    for (p = head->next; p->next != head; p = p->next)
        ;
    p->next    = node;
    node->next = head;
}
int list_delete(struct list_node* head, struct list_node* node)
{
    struct list_node* p;
    if (head->next == head)
    {
        printf("empty list!\n");
        return -1;
    }
    for (p = head->next; p->next != node; p = p->next)
    {
        if (p == head)
        {
            printf("find no node!\n");
            return -2;
        }
        if (p == node)
        {
            head->next = node->next;
            free(node);
        }
    }
    p->next = node->next;
    free(node);
    return 0;
}
struct list_node* list_foreach(struct list_node* head, int val)
{
    struct list_node* p;
    p = head->next;
    if (p == head)
    {
        printf("empty list!\n");
        return (struct list_node*)0;
    }
    for (; p->data != val; p = p->next)
    {
        if (p == head)
        {
            printf("find no node!\n");
            return (struct list_node*)0;
        }
    }
    return p;
}
```

## 双向链表

基本概念
- 数据域
- 前趋指针
- 后继指针

基本操作
- 判空, 添加, 删除, 遍历, 销毁
	- ![](assets/Pasted%20image%2020230508155445.png)

```c
typedef struct list_node
{
    int               data;
    struct list_node* next;
    struct list_node* prev;
}ListNode, *LinkList;
```

## 双向循环链表

基本定义
- 头结点的prev指针域指向尾结点, 尾结点的next指针域指向头结点.
	- ![](assets/Pasted%20image%2020230508161137.png)

- 链表为空的时候跟 双向链表不同.

# Linux内核中的通用链表

## 内核链表

双向循环链表
- 在进程、文件、模块、设备驱动中大量使用
- 定义：include/linux/list.h、 include/linux/types.h 中

通用在哪里?
- 定义了针对链表的一些基本操作
- 不同的数据类型都可以据此构建自己的链表

Linux4.4 内核中通用链表的头文件`list.h`
```c
#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

struct list_head {
	struct list_head *next, *prev;
};

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{ //初始化
	list->next = list;
	list->prev = list;
}
后面还有一系列内联函数, 定义了通用链表的操作. 
.......
```

## 链表的基本操作

基本操作
- 基于内核Linux4.4.x版本.
- 初始化
- 添加节点
- 删除节点
- 遍历

- 添加
```c
static inline 
void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{ // prev是前面的结点, next是后面的结点, 在prev和next之间插入new
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

// 三个参数变两个
static inline 
void list_add(struct list_head *new, struct list_head *head)
{ //插在head指向结点的后面
	__list_add(new, head, head->next);
}

static inline 
void list_add_tail(struct list_head *new, struct list_head *head)
{  // head指向的结点就是尾部. 然后插在他前面
	__list_add(new, head->prev, head);
}

```

- 删除:
```c
/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline 
void __list_del(struct list_head * prev, struct list_head * next)
{ // 意思是已经找到要删除的结点cur了, 然后把cur->prev根cur->next传进来.
	next->prev = prev;
//	WRITE_ONCE(prev->next, next);
	prev->next = next;
}

#ifndef CONFIG_DEBUG_LIST
static inline void __list_del_entry(struct list_head *entry)
{// 封装上面的函数, 直接传要删的结点的地址.
	__list_del(entry->prev, entry->next);
}

static inline void list_del(struct list_head *entry)
{//删完后, 把该结点的指针域置到安全区.
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}
#else

```