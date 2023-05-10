想要读懂Linux内核源码还是需要一定功力的: 
- 首先你的C语言基础一定要打牢, 如结构体, 指针, 数组, 函数指针, 指针函数, 数组指针, 指针数组等, 如果这些基础知识点你还要偷偷去翻书或者搜索, 则说明得好好补一补基础了. 
- 另外, C语言的一些GNU C扩展语法等也要熟悉, 否则在阅读Linux内核源码时就会遇到各种语法障碍. 
- 其次, 一些常用的数据结构要掌握, 如链表, 队列等. Linux内核中使用大量的动态链表和队列来维护各种设备, 管理各种事件, 不掌握这些数据的动态变化就可能在跟踪源码时遇到障碍. 
- 最后, 要理解Linux内核中大量使用的面向对象编程思想. 

面对千万行代码级的超大型工程, 如果再按照以前的函数调用流程和数据流程去分析Linux内核, 往往会让人感到捉襟见肘, 力不从心, 很容易一叶障目, 迷失在森林深处. 

Linux内核虽然是使用C语言编写的, 但处处蕴含着面向对象的设计思想. 以OOP为切入点去分析内核, 从代码复用的角度可以帮助我们从一个盘根错节的复杂系统中勾勒出一个全局的框架, 确保我们再次深入森林探险时能够手握地图, 不再迷路. 

其实C语言也可以实现面向对象编程. 面向对象编程是一种编程思想, 和使用的语言工具是没有关系的, 只不过有些语言更适合面向对象编程而已. 
- 如C++, Java新增了class关键字, 就是为了更好地支持面向对象编程, 通过类的封装和继承机制, 可以更好地实现代码复用

使用C语言我们同样可以实现面向对象编程.

# 数据结构基础

> 数据结构学过专门的课程,  这里主要是复习和进阶,  主要去看看Linux内核里的数据结构.

## 数据结构基本概念

- 什么是数据结构
	- 程序 = 数据结构 + 算法
	- 数据结构: 对客观事物的抽象
	- 数据的组织形式, 数据之间的关联
- 数据元素
	- 数据的基本单位
	-  C语言基本数据类型: 数组, 结构体, 共用体, 枚举

数据结构基本概念

- 结构类型: 顺序表,  栈,  链表,  队列,  树,  图…
- 逻辑结构: 线性, 非线性
- 存储结构: 顺序存储, 链式存储
- 基本操作: 添加, 删除, 查找, 遍历  

## 数据结构的重要性

- 编程技能
	- 程序 = 数据结构 + 算法
	- 内功: 数据结构, 算法
	- 招式: 编程语言
	- 框架分层, 代码复用, 性能优化, 复杂的业务逻辑

## 工程师层级划分
- 菜鸟
	- 遇到问题: 百度, 贴吧, QQ群, 不知如何下手…
- 新手
	- 能通过编程完成交代的任务, 代码可以运行, 为demo级别
	- 遇到极端, 边界情况会运行异常, 不稳定, 有bug, 无法解决
	- 需求改变, 功能添加导致程序结构臃肿, bug丛生, 难以维护
- 老手
	- 经过新手期锻炼, 开始重视数据结构与算法的重要性
	- 开始重视程序的健壮性, 稳定性, 可维护性
- 高手
	- 精通一门或多门语言, 根据需求选择不同语言
	- 学会使用面向对象思想去抽象, 去解构复杂的系统
	- 语言只是一个工具
- 专家
	- 设计模式: 大量项目实战和经验积累, 进一步理解面向对象思想
	- 架构设计: 代码分层, 模块耦合, 性能优化…

## 数据结构怎么学
- 链表: 设备管理
- 队列: 工作队列, 等待队列, 消息队列
- 树: 二叉树, 红黑树, B树
- 哈希表: 文件系统

# 什么是线性表

逻辑结构
- 线性结构
	- 数据元素之间是“一对一”的线性关系
	- 举例: 线性表, 栈, 队列, 数组
- 非线性结构
	- 数据元素之间是“一对多”, “多对多”树形或网络关系
	- 举例: 树, 图


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

- 链表: 链式存储的线性表
- 节点(node) : `数据域`, `指针域`
- 头指针
- 头节点
	- ![](assets/Pasted%20image%2020230508155045.png) 

链表的基本操作

- 常用的基本操作
	- 判断链表是否为空
	- 插入节点
	- 删除节点
	- 遍历

> 对于链表,  不管是单向 双向,  循环还是非循环: 
> 添加结点,  一定是先把添加的结点的指针域设好,  再去动前后节点
> 删除节点,  一定是先把前后节点设置好,  再去删那个要删的结点
> 插入,  删除都要注意链表为空的情况(只有头结点) .
> 注意不要访问空指针.

```c
下面单向链表的操作基于这个结构体: 
typedef struct list_node {
    int data; 
    struct list_node *next; 
} ListNode,  *ListLink; 
```

数组与链表

线性表
- 数组
- 链表

数组与链表比较
- 优点:  数组查找方便
- 缺点:  插入, 删除不方便;  存储空间不灵活

```c
玩具代码:  想法不一样,  实现的内容就不一样. 一般插入都是先要查找要插入的位置的.

int is_list_empty(struct list_node* head) 
{
    return (head->next == NULL) ; 
}
void list_print(struct list_node* head) 
{
    struct list_node* p; 
    p = head->next; 
    for (p;  p != NULL;  p = p->next) 
        printf("p->data = %d\n",  p->data) ; 
}
void list_free(struct list_node* head) 
{
    struct list_node *p,  *q; 
    q = head->next; 
    p = q->next; 
    while (q != NULL) 
    {
        free(q) ; 
        q = p; 
        if (p != NULL) 
            p = p->next; 
        printf("p: %p q: %p\n",  p,  q) ; 
    }; 
}
void list_add(struct list_node* head,  struct list_node* node) 
{
    node->next = head->next; 
    head->next = node; 
}
void list_add_tail(struct list_node* head,  struct list_node* node) 
{  
    struct list_node* p; 
    for (p = head->next;  p->next != NULL;  p = p->next) 
        ; 
    p->next = node; 
}
int list_delete(struct list_node* head,  struct list_node* node) 
{
    struct list_node* p; 
    if (is_list_empty(head) ) 
        return -1; 
    if (node == head->next) 
        head->next = node->next; 
    else
    {
        for (p = head->next;  p->next != node;  p = p->next) 
            ; 
        p->next = node->next; 
    }
    free(node) ; 
    return 0; 
}
struct list_node* list_foreach(struct list_node* head,  int val) 
{
    struct list_node* p; 
    p = head->next; 
    for (p;  p->data != val;  p = p->next) 
        ; 
    return p; 
}
```

## 循环链表

跟单向链表不同,  循环链表的尾结点的指针域,  不指向NULL,  指向头结点.
- ![](assets/Pasted%20image%2020230508155306.png) 

循环链表基本操作
- 创建
- 判断非空
- 添加节点
- 删除节点
- 遍历

```c
// 一般双向链表,  会有一个头指针和尾指针,  时刻记录着头结点和尾结点的实时位置.
struct headtail {
	struct list_node *head; 
	struct list_node *tail; 
} Note; 
int list_init(ListNode **head) 
{// 申请个头结点.
	struct list_node *p = (Listnode *) malloc(sizeof(ListNode) ) ; 
	if(!p) 
		return -1; 
	p->next = NULL; 
	*head = p;  // 传进来的指针 的值指向这个头结点.
	Note.head = Note.tail = p;  //目前头指针记录跟尾指针记录都是头结点地址
}
int is_list_empty(struct list_node* head) 
{
    return (head->next == head) ; 
}
void list_print(struct list_node* head) 
{
    struct list_node* p; 
    p = head->next; 
    for (p;  p != head;  p = p->next) 
        printf("p->data = %d\n",  p->data) ; 
}
void list_free(struct list_node* head) 
{
    struct list_node *p,  *q; 
    q = head->next; 
    p = q->next; 
    while (q != head) 
    {
        free(q) ; 
        q = p; 
        if (p != head) 
            p = p->next; 
        printf("p: %p q: %p\n",  p,  q) ; 
    }; 
}
void list_add(struct list_node* head,  struct list_node* node) 
{
    node->next = head->next; 
    head->next = node; 
}
void list_add_tail(struct list_node* head,  struct list_node* node) 
{
    struct list_node* p; 
    for (p = head->next;  p->next != head;  p = p->next) 
        ; 
    p->next    = node; 
    node->next = head; 
}
int list_delete(struct list_node* head,  struct list_node* node) 
{
    struct list_node* p; 
    if (head->next == head) 
    {
        printf("empty list!\n") ; 
        return -1; 
    }
    for (p = head->next;  p->next != node;  p = p->next) 
    {
        if (p == head) 
        {
            printf("find no node!\n") ; 
            return -2; 
        }
        if (p == node) 
        {
            head->next = node->next; 
            free(node) ; 
        }
    }
    p->next = node->next; 
    free(node) ; 
    return 0; 
}
struct list_node* list_foreach(struct list_node* head,  int val) 
{
    struct list_node* p; 
    p = head->next; 
    if (p == head) 
    {
        printf("empty list!\n") ; 
        return (struct list_node*) 0; 
    }
    for (;  p->data != val;  p = p->next) 
    {
        if (p == head) 
        {
            printf("find no node!\n") ; 
            return (struct list_node*) 0; 
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
- 判空,  添加,  删除,  遍历,  销毁
	- ![](assets/Pasted%20image%2020230508155445.png) 

```c
typedef struct list_node
{
    int               data; 
    struct list_node* next; 
    struct list_node* prev; 
}ListNode,  *LinkList; 
```

## 双向循环链表

基本定义
- 头结点的prev指针域指向尾结点,  尾结点的next指针域指向头结点.
	- ![](assets/Pasted%20image%2020230508161137.png) 

- 链表为空的时候跟 双向链表不同.

# Linux内核中的通用链表

## 内核链表

双向循环链表
- 在进程, 文件, 模块, 设备驱动中大量使用
- 定义: include/linux/list.h,  include/linux/types.h 中

通用在哪里?
- 定义了针对链表的一些基本操作
- 不同的数据类型都可以据此构建自己的链表

Linux4.4 内核中通用链表的头文件`list.h`
```c
#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

#define offsetof(TYPE,  MEMBER) 	((size_t) &((TYPE *) 0) ->MEMBER) 

#define container_of(ptr,  type,  member)  ({			\
	const typeof( ((type *) 0) ->member )  *__mptr = (ptr) ; 	\
	(type *) ( (char *) __mptr - offsetof(type, member)  ) ; }) 

#define LIST_POISON1  ((void *)  0x00100100) 
#define LIST_POISON2  ((void *)  0x00200200) 

struct list_head {
	struct list_head *next,  *prev; 
}; 

struct hlist_head {
	struct hlist_node *first; 
}; 

struct hlist_node {
	struct hlist_node *next,  **pprev; 
}; 

#define LIST_HEAD_INIT(name)  { &(name) ,  &(name)  }

#define LIST_HEAD(name)  \
	struct list_head name = LIST_HEAD_INIT(name) 

static inline void INIT_LIST_HEAD(struct list_head *list) 
{ //初始化
	list->next = list; 
	list->prev = list; 
}
后面还有一系列内联函数,  定义了通用链表的操作. 
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
{ // prev是前面的结点,  next是后面的结点,  在prev和next之间插入new
	next->prev = new; 
	new->next = next; 
	new->prev = prev; 
	prev->next = new; 
}

// 三个参数变两个
static inline 
void list_add(struct list_head *new,  struct list_head *head) 
{ //插在head指向结点的后面
	__list_add(new,  head,  head->next) ; 
}

static inline 
void list_add_tail(struct list_head *new,  struct list_head *head) 
{  // head指向的结点就是尾部. 然后插在他前面
	__list_add(new,  head->prev,  head) ; 
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
void __list_del(struct list_head * prev,  struct list_head * next) 
{ // 意思是已经找到要删除的结点cur了,  然后把cur->prev根cur->next传进来.
	next->prev = prev; 
//	WRITE_ONCE(prev->next,  next) ; 
	prev->next = next; 
}

#ifndef CONFIG_DEBUG_LIST
static inline void __list_del_entry(struct list_head *entry) 
{// 封装上面的函数,  直接传要删的结点的地址.
	__list_del(entry->prev,  entry->next) ; 
}

static inline void list_del(struct list_head *entry) 
{//删完后,  把该结点的指针域置到安全区.
	__list_del(entry->prev,  entry->next) ; 
	entry->next = LIST_POISON1; 
	entry->prev = LIST_POISON2; 
}
#else
```

- 遍历
```c
#define list_for_each(pos,  head)  \
	for (pos = (head) ->next;  pos != (head) ;  pos = pos->next) 

#define list_for_each_prev(pos,  head)  \
	for (pos = (head) ->prev;  pos != (head) ;  pos = pos->prev) 

#define list_for_each_safe(pos,  n,  head)  \
	for (pos = (head) ->next,  n = pos->next;  pos != (head) ;  \
		pos = n,  n = pos->next) 

#define list_for_each_prev_safe(pos,  n,  head)  \
	for (pos = (head) ->prev,  n = pos->prev;  \
	     pos != (head) ;  \
	     pos = n,  n = pos->prev) 
```

```c
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct device
{
    int              num; 
    struct list_head node; 
}; 
int main(void) 
{
    struct device*    p; 
    struct device     head;   // ¿¿¿¿¿¿¿¿¿
    struct list_head *pos,  *q; 

    INIT_LIST_HEAD(&head.node) ; 

    for (int i = 0;  i < 5;  i++) 
    {
        p = (struct device*) malloc(sizeof(struct device) ) ; 
        printf("input device num: ") ; 
        scanf("%d",  &p->num) ; 
        list_add(&(p->node) ,  &(head.node) ) ; 
    }
    puts("list_for_each: ") ; 
    list_for_each(pos,  &(head.node) ) 
    {
        p = list_entry(pos,  struct device,  node) ; 
        printf("num = %d\n",  p->num) ; 
    }
    list_for_each_safe(pos,  q,  &head.node) 
    {   // delete
        p = list_entry(pos,  struct device,  node) ; 
        printf("freeing node:  num = %d\n",  p->num) ; 
        list_del(pos) ; 
        free(p) ; 
    }
    return 0; 
}
```

# 队列:  顺序队列

## 队列基本概念

什么是队列？
- 属于线性表的一种:  queue
- FIFO:  First In First Out
- 与栈区别:  FILO(First In Last Out) 

队列的基本元素
- 队头:  front
- 队尾:  rear

哪些场合会使用队列
- 生产者—消费者
- 异步通信

队列存储
- 顺序队列
- 链式队列

队列的基本操作
- 初始化队列
- 入队
- 出队
- 队列是否为空判断
- 队列遍历

# 队列:  链式队列

链式队列
- 基本操作
	- 队列初始化
	- 入队
	- 出队
	- 队列是否为空判断
	- 队列遍历
	- 队列置空

# Linux内核中的队列:  KFIFO

基本概念
- 内核版本: Linux-4.4.x
- 定义:  `lib/kfifo.c`   `include/linux/kfifo.h`
- ![](assets/Pasted%20image%2020230509143818.png) 

KFIFO基本操作

- 入队
	- 初始化: `kfifo_init \ kfifo_alloc`
	- `Kfifo_put`
	- `Kfifo_in \ kfifo_in_spinlocked`
		- ![](assets/Pasted%20image%2020230509144345.png) 
```c
struct __kfifo {
	unsigned int	in; 
	unsigned int	out; 
	unsigned int	mask; 
	unsigned int	esize; 
	void		*data; 
}; 

int __kfifo_alloc(struct __kfifo *fifo,  unsigned int size, 
		size_t esize,  gfp_t gfp_mask) 
{
	/*
	 * round up to the next power of 2,  since our 'let the indices
	 * wrap' technique works only in this case.
	 */
	size = roundup_pow_of_two(size) ; 

	fifo->in = 0; 
	fifo->out = 0; 
	fifo->esize = esize; 

	if (size < 2)  {
		fifo->data = NULL; 
		fifo->mask = 0; 
		return -EINVAL; 
	}

	fifo->data = kmalloc_array(esize,  size,  gfp_mask) ; 

	if (!fifo->data)  {
		fifo->mask = 0; 
		return -ENOMEM; 
	}
	fifo->mask = size - 1; 

	return 0; 
}
EXPORT_SYMBOL(__kfifo_alloc) ; 

#define kfifo_alloc(fifo,  size,  gfp_mask)        \                                __kfifo_int_must_check_helper(({               \                        typeof((fifo)  + 1)  __tmp = (fifo) ;                              \
  struct __kfifo *__kfifo = &__tmp->kfifo;                        \
		__is_kfifo_ptr(__tmp)  ?                                        \
			__kfifo_alloc(__kfifo,  size,  sizeof(*__tmp->type) ,      \
			 gfp_mask)  :                               \
			-EINVAL;                                                \
	}) ) 

static void kfifo_copy_in(struct __kfifo *fifo,  const void *src, 
		unsigned int len,  unsigned int off) 
{
	unsigned int size = fifo->mask + 1; 
	unsigned int esize = fifo->esize; 
	unsigned int l; 

	off &= fifo->mask; 
	if (esize != 1)  {
		off *= esize; 
		size *= esize; 
		len *= esize; 
	}
	l = min(len,  size - off) ; 

	memcpy(fifo->data + off,  src,  l) ; 
	memcpy(fifo->data,  src + l,  len - l) ; 
	/*
	 * make sure that the data in the fifo is up to date before
	 * incrementing the fifo->in index counter
	 */
	smp_wmb() ; 
}
unsigned int __kfifo_in(struct __kfifo *fifo, 
		const void *buf,  unsigned int len) 
{
	unsigned int l; 

	l = kfifo_unused(fifo) ; 
	if (len > l) 
		len = l; 

	kfifo_copy_in(fifo,  buf,  len,  fifo->in) ; 
	fifo->in += len; 
	return len; 
}
EXPORT_SYMBOL(__kfifo_in) ; 
```

- 出队
	- Kfifo_get
	- Kfifo_out
		- ![](assets/Pasted%20image%2020230509144454.png) 

```c
static void kfifo_copy_out(struct __kfifo *fifo,  void *dst, 
		unsigned int len,  unsigned int off) 
{
	unsigned int size = fifo->mask + 1; 
	unsigned int esize = fifo->esize; 
	unsigned int l; 

	off &= fifo->mask; 
	if (esize != 1)  {
		off *= esize; 
		size *= esize; 
		len *= esize; 
	}
	l = min(len,  size - off) ; 

	memcpy(dst,  fifo->data + off,  l) ; 
	memcpy(dst + l,  fifo->data,  len - l) ; 
	/*
	 * make sure that the data is copied before
	 * incrementing the fifo->out index counter
	 */
	smp_wmb() ; 
}
unsigned int __kfifo_out_peek(struct __kfifo *fifo, 
		void *buf,  unsigned int len) 
{
	unsigned int l; 
	l = fifo->in - fifo->out; 
	if (len > l) 
		len = l; 
	kfifo_copy_out(fifo,  buf,  len,  fifo->out) ; 
	return len; 
}
EXPORT_SYMBOL(__kfifo_out_peek) ; 
unsigned int __kfifo_out(struct __kfifo *fifo, 
		void *buf,  unsigned int len) 
{
	len = __kfifo_out_peek(fifo,  buf,  len) ; 
	fifo->out += len; 
	return len; 
}
EXPORT_SYMBOL(__kfifo_out) ; 
```

> 每个版本的代码都不一样,  5.15的代码就已经变了.

# 代码复用与分层思想: 

代码复用
- 定义一个函数实现某个功能, 然后所有的程序都可以调用这个函数, 不用自己再单独实现一遍, 这就是`函数级的代码复用`.
- 用的函数打包封装成库, 并引出API供程序调用, `库级的代码复用`
- 将一些类似的应用程序抽象成应用骨架, 然后进一步慢慢迭代成框架, 如MVC, GUI系统, Django, 实现了`框架级的代码复用`
- 操作系统其实也是对任务调度, 任务间通信的功能实现并引出API供应用程序调用, 相当于实现了`操作系统级的代码复用`.

通常将要复用的具有某种特定功能的代码封装成一个模块, 各个模块之间相互独立, 使用的时候可以以模块为单位集成到系统中. 随着系统越来越复杂, 集成的模块越来越多, 模块之间有时候也会产生依赖关系. 

为了便于系统的管理和维护, 又开始出现分层思想.

分层与接口

- 基本概念
	- 按需求划分: 各层实现各自功能, 各层之间通过接口通信
	- 每一层都是对其下面一层的封装, 给上面一层提供服务
	- 每一层都会留出接口, 给上一层复用
	- 接口也不一定是固定不变的
- 分层的好处
	- 代码重用
	- 软件层次结构清晰, 易于维护
	- 兼容性: 适配不同平台, 设备
	- 扩展性: 功能易于扩展

- 计算机软硬件系统
	- 应用层, 操作系统, 硬件层
	- C库与系统调用
		- ![](assets/Pasted%20image%2020230509155642.png) 
	- Android系统框架
		- 应用层 Framework层 库 Linux内核
		- ![](assets/Pasted%20image%2020230509155714.png) 

Linux内核中的分层

系统框架
- 文件系统: VFS, EXT, YAFFS, CRAMFS
	- ![](assets/Pasted%20image%2020230509160338.png) 
- 设备驱动模型: device, driver, bus
- Input子系统: 鼠标, 键盘, 遥控器, 体感器
- MTD: 块设备的读写, 算法
- 进程调度
- 内存管理

设备驱动
- USB驱动
- 底层硬件, 控制器驱动层, USB core核心层, 各个USB class驱动层.
	- ![](assets/Pasted%20image%2020230509160410.png) 

一个系统通过分层设计, 各层实现各自的功能, 各层之间通过接口通信. 每一层都是对其下面一层的封装, 并留出API, 为上一层提供服务, 实现代码复用. 

使用分层有很多好处, 软件分层不仅实现了代码复用, 避免了重复造轮子, 同时会使软件的层次结构更加清晰, 更加易于管理和维护. 各层之间统一的接口, 可以适配不同的平台和设备, 提高了软件的跨平台和兼容性. 接口也不是固定不变的, 我们也可以根据需要通过接口来实现功能扩展. 

分层的实现
- 面向对象思想
	- 通过封装, 继承, 多态等面向对象的特性
	- 通过接口封装, 实现代码复用

# 面向对象编程基础

## 什么是OOP

面向对象编程
- Object Oriented Programming
- 对象是程序的基本单元: 包括数据成员和函数(属性和方法) 
- 类: 对客观事物的抽象, 本质是一种数据类型, 对象是类的实例化

面向过程编程
- Procedure Oriented Programming
- 函数是程序的基本单元: 解决问题的一个步骤
- 模块化编程思想: 从上至下, 以功能块为单位进行程序设计

两者比较
- 解决问题思路
	- 面向过程: 侧重解决问题的步骤过程, 细节, 模块划分
	- 面向对象: 侧重将问题抽象, 封装成类,  通过继承来实现代码复用, 软件的顶层架构设计
- 适用场合
	- 面向过程: 简单固定功能实现, 细节: 把大象装到冰箱里
	- 面向对象: 复杂软件系统的层次, 系统架构设计.

关于OOP, 还需要注意的是: 面向对象编程思想与具体的编程语言无关: 
- C++, Java实现了类机制, 增加了class关键字, 可以更好地支持面向对象编程, 
- 但C语言同样可以通过结构体, 函数指针来实现面向对象编程思想. 

我们也可以把面向对象编程作为工具, 去分析各种复杂的大型项目. 

如在Linux内核中就处处蕴含着面向对象编程思想: 
- 对于Linux内核众多的模块, 复杂的子系统, 如果我们还从C语言的角度, 用面向过程编程思想去分析一个驱动和子系统, 无非就是各种注册, 初始化, 打开, 关闭, 读写流程, 系统稍微变得复杂一点, 往往就感到力不从心. 
- 而使用面向对象编程思想, 我们可以从代码复用, 软件分层的角度去分析, 更加容易掌握整个软件的架构和层次设计. 

## 面向对象基本概念

三大特征
- 封装: 将客观事物抽象为类: 属性和方法
- 继承: 子类对象拥有父类对象的属性和方法
- 多态: `一个接口多种实现: 覆盖和重载`
	- 子类重新覆盖父类的方法
	- 子类重载父类里的方法(同名函数, 不同参数) 
- 虚函数
	- 可实现可不实现
	- 实现多态: 允许用`基类指针`来调用`子类的继承函数`
- 纯虚函数
	- 父类中不实现, 子类继承后`必须实现`
	- 实现接口
	- 抽象类

## 类的封装与实例化

C++比C语言新增了一个class关键字, 用来支持类的实现机制. 我们可以对现实存在的各种事物进行抽象, 把它`封装成一种数据类型——类`.

```c++
#include<iostream>
using namespace std; 
class Animal
{
	public: 
		int age; 
		int weight; 
		Animal(void) ; 
		~Animal(void) 
		{
			cout<<"~Animal() ..."<<endl; 
		} 
	    virtual void speak() 
	 	{
	 		cout<<"Animal speaking..."<<endl; 
	    }		
}; 
Animal::Animal(void) 
{
	cout<<"Animal() ..."<<endl; 
}
int main(void) 
{
 	Animal animal; 
 	animal.age = 1; 
 	cout<<"animal.age: "<<animal.age<<endl; 
    animal.speak() ; 		
	return 0; 
} 
```
- ![](assets/Pasted%20image%2020230509165145.png) 

一个类中, 主要包括两种基本成员: 属性和方法. 

每个类中还包括和类同名的`构造函数和析构函数`, 当我们使用类去实例化一个对象或销毁一个对象时, 会分别调用类的构造函数或析构函数. 

类的成员函数可以直接在类内部定义, 也可以先在类内部声明, 然后在类的外部定义, 在外部定义时要使用类成员运算符`::`指定该成员函数属于哪个类. 

类的本质其实就`是一种数据类型`, 与C语言的结构体类似, 
- 唯一不同的地方是类的内部可以包含类的方法, 即`成员函数`; 
- 而结构体内部只能是`数据成员`, 不能包含函数. 

一个类定义好后, 我们就可以使用这个类去`实例`化一个对象(其实就类似C语言中的使用某种数据类型定义一个变量), 然后就可以直接操作该对象了: 为该对象的属性赋值, 或者调用该对象中的方法. 

## 继承与多态

我们对自然界的相似事物进行抽象, 封装成一个类, 目的就是为了继承, 通过继承来`实现代码复用`. 

上面封装的Animal类抽象过于笼统, 我们可以把类再细分一些: 针对某种具体的动物, 如
猫, 抽象成Cat类. 

猫也属于动物, 如果在Cat类中重复定义动物的各种属性, 就达不到代码复用的目的了, 此时我们可以通过类的继承机制, 让Cat类去继承原先Animal类的属性和方法. 

```c++
#include<iostream>
using namespace std; 
class Animal
{
	public: 
		int age; 
		int weight; 
		Animal(void) ; 
		~Animal(void) 
		{
			cout<<"~Animal() ..."<<endl; 
		} 
	    virtual void speak() 
	 	{
	 		cout<<"Animal speaking..."<<endl; 
	    }		
}; 
Animal: : Animal(void) 
{
	cout<<"Animal() ..."<<endl; 
}
class Cat: public Animal
{
	public: 
		char sex; 
		Cat(void) {cout<<"Cat() ..."<<endl; }
		~Cat(void) {cout<<"~Cat() ..."<<endl; }
		void speak() 
		{
			cout<<"cat speaking...miaomiao"<<endl; 
		}
		void speak(char name[]) 
		{
			cout<<"cat speaking..."<<name<<endl; 
		}
		void eat(void) 
		{
			cout<<"cat eating..."<<endl; 
		}
}; 
int main(void) 
{
//	Animal animal; 
//	animal.age = 1; 
//	cout<<"animal.age: "<<animal.age<<endl; 
//	animal.speak() ; 	
	Cat cat; 
	Animal *p = &cat; //基类指针调用子类的继承函数
	cat.age = 2; 
	cat.sex = 'F'; 
	cout<<"cat.age: "<<cat.age<<endl; 
	cout<<"cat.sex: "<<cat.sex<<endl; 
	p->speak() ; 	
	cat.eat() ; 
 	cat.speak("xiaohua") ; 			
	return 0; 
} 
```
运行结果: 
```shell
Animal() ...
Cat() ...
cat.age: 2
cat.sex: F
cat speaking...miaomiao
cat eating...
cat speaking...xiaohua
~Cat() ...
~Animal() ...
```

在上面的C++代码中, 我们在定义Cat类过程中, 继承了Animal类中的一些属性和方法. 我们一般称Animal类为`父类或基类`, 而Cat类一般被称为`子类`. 通过继承机制, 子类不仅可以`直接复用`父类中定义的属性和方法, 还可以在父类的基础上, `扩展`自己的属性和方法, 如我们新增加的sex属性和eat() 方法. 

不同的动物, 叫声也不一样. 在Cat子类中, 我们`重新定义`了speak() 方法, 像这种`在继承过程中, 子类重新定义父类的方法`一般被称为`多态`. `一个接口多种实现`, 在不同的子类中有不同的实现, 通过`函数的重载和覆盖`, 既实现了代码复用, 又保持了实现的多样性. 

## 虚函数与纯虚函数

我们在基类Animal中使用`virtual`关键字定义了虚函数speak() , 子类Cat通过`重新定义`这个speak() 实现了`函数覆盖`. 在main() 函数中, 我们定义了一个`基类指针p`指向Cat类的实例化对象cat, 然后就可以通过这个`基类指针去调用子类`中实现的speak() 方法来实现多态. 

和虚函数类似的还有一个叫作`纯虚函数`的概念. 纯虚函数的要求比虚函数更严格一些, 它`在基类中不实现`, 但是`子类继承后必须实现`. 

含有纯虚函数的类被称为`抽象类`, 如Animal类. 如果在类中删除speak() 方法的实现, 那么我们就可以把它看作一个抽象类, 你`不能使用Animal类去实例化`一种叫作“animal”的实例对象. 

# Linux内核面向对象思想

Linux内核虽然是使用C语言实现的, 但是内核中的很多子系统, 模块在实现过程中处处体现了面向对象编程思想. 

同理, 我们在分析Linux内核驱动模块或子系统过程中, 如果能学会使用面向对象编程思想去分析, 就可以将错综复杂的模块关系条理化, 复杂的问题简单化. 

使用面向对象编程思想去分析内核是一个值得尝试的新方法, 但前提是, 我们要掌握Linux内核中是如何用C语言来实现面向对象编程思想的. 

## 类的C语言模拟实现

通过结构体来模拟一个类
- 结构体
- 函数指针
- 结构体指针

```c
struct func_pointer
{
    void (*fp1) (void) ; 
    void (*fp2) (int ,  int) ; 
    void (*fp3) (...) ; 
    void (*fp4) (...) ; 
}; 
struct animal
{
    int                  age; 
    int                  weight; 
    struct func_pointer* fp;  
//如果一个结构体中需要内嵌多个函数指针, 可以把这些函数指针进一步封装到一个结构体内. 
}; 
```
通过以上封装, 我们就可以`把一个类的属性和方法都封装在一个结构体`里了. 封装后的结构体此时就相当于一个“类”, 子类如果想使用该类的属性和方法, 该如何继承呢？
```c
struct cat
{
    struct animal *p; 
    struct animal  ani; // 如果父类实例化一个对象,这个可以没有
    char           sex; 
}; 
void speak(void) 
{
    printf("animal speaking...\n") ; 
}
int main(void) 
{
    struct animal       ani; //父类
    struct func_pointer funcp; //操作集合
    funcp.fp1  = speak;  
    ani.age    = 1;      
    ani.weight = 2; 
    ani.fp     = &funcp; 
    ani.fp->fp1() ; 
    printf("%d %d\n",  ani.age,  ani.weight) ; 

    struct cat c; //子类
    c.p = &ani;    //继承父类
    c.p->fp->fp1() ; 
    printf("%d %d\n",  c.p->age,  c.p->weight) ; 

    return 0; 
}
```
C语言可以通过在结构体中内嵌另一个结构体或结构体指针来模拟类的继承. 通过这种内嵌方式, 子类就“继承”了父类的属性和方法. 

## 链表的抽象与封装

链表是我们在编程中经常使用的一种`动态数据结构`. 一个链表(list) 由不同的`链表节点`(node) 组成, 一个链表节点往往包含两部分内容: 数据域和指针域. 
```c
struct list_node{
	int data; 
	struct list_node *next; 
	struct list_node *prev; 
}; 
```
数据域用来存储各个节点的值, 而指针域则用来指向链表的上一个或下一个节点, 各个节点通过指针域链成一个链表. 在实际编程中, 根据业务需求, 不同的链表节点可能会封装不同的数据域, 构成不同的数据格式, 进而连成不同的链表. 

不同的链表虽然数据域不同, 但是基本的操作都是相同的: 都是通过节点的指针域去添加一个节点或删除一个节点. Linux内核中`为了实现对链表操作的代码复用`, 定义了一个`通用的链表`及相关操作. 

```c
struct list_head {
	struct list_head *next,  *prev; 
}; 
void INIT_LIST_HEAD(struct list_head *list) ; 
int list_empty(const struct list_head *head) ; 
void list_add(struct list_head *new,  struct list_head *head) ; 
void list_del(struct list_head *entry) ; 
void list_replace(struct list_head *old,  struct list_head *new) ; 
void list_move(struct list_head *list,  struct list_head *head) ; 
```

我们可以`将结构类型list_head及相关的操作`看成一个`基类`, 其他子类如果想继承基类的属性和方法, 直接将`list_head`内嵌到`自己的结构体内`即可. 如我们想定义一个链表`my_list`, 如果你想`复用Linux内核中的通用链表及相关操作`, 就可以通过内嵌结构体来“继承”`list_head`的属性和方法. 

```c
struct my_list_node
{
	int data; 
	struct list_head list; 
}; 
```

## Linux内核中的数据封装

>基类: 设备管理模型 

```c
struct kobject {
	const  char *name; 
	struct list_head entry; //list基类
	struct kobject *parent; //老父亲指针
	struct kset *kset; // 指向管理自己的kset
	struct kobj_type *ktype; //封装了很多关于设备插拔,添加,删除的方法
    struct kernfs_node *sd; 
	struct kref kref; 
	unsigned int state_initialized:1; 
	unsigned int state_in_sysfs:1; 
	unsigned int state_add_uevent_sent:1; 
	unsigned int state_remove_uevent_sent:1; 
	unsigned int uevent_suppress:1; 
}; 
```

Linux使用sysfs文件系统来显示设备的信息, 在/sys目录下, 你会看到有devices的目录, 在devices目录下还有很多分类, 然后在各个分类目录下就是Linux系统下各个具体硬件设备的信息.  

/sys 这个目录是内核给用户的一个接口. 

上面的结构体就是为了管理和维护这些设备信息的.  它构成了我们所有设备在系统中的树结构雏形: `kobject结构体用来表示Linux系统中的一个设备`, 相同类型的kobject通过其内嵌的list_head链成一个`链表`, 然后使用另外一个`结构体kset来指向和管理这个列表.`
- 比如 tty类型的设备, 看做是kset, 里面的具体的各个ttyn设备, 就是kobject, 这n个ttyn设备通过链表串起来.
- windows下就好比是, 磁盘驱动器是一个kset, 里面的各个硬盘是kobject

>Kobject与sysfs的关系: 

```shell
tony in /sys at ubuntu …
➜ tree -L 1
.
├── block
├── bus
├── class
├── dev
├── devices
├── firmware
├── fs
├── hypervisor
├── kernel
├── module
└── power

tony in /sys/devices  at ubuntu …
➜ ls -sh
总用量 0
0 breakpoint  0 isa     0 LNXSYSTM: 00  0 pci0000: 00  0 pnp0   0 software  0 tracepoint  0 virtual
0 cpu         0 kprobe  0 msr          0 platform    0 power  0 system    0 uprobe

tony in /sys/devices/virtual  at ubuntu …
➜ ls -sh
总用量 0
0 bdi    0 dma_heap  0 graphics  0 mem   0 msr  0 powercap  0 sound    0 tty  0 vtconsole
0 block  0 dmi       0 input     0 misc  0 net  0 ppp       0 thermal  0 vc   0 workqueue

tony in virtual/tty/tty1 at ubuntu …
➜ tree
.
├── dev   # 记录主设备号和次设备号
├── power
│   ├── async
│   ├── autosuspend_delay_ms
│   ├── control
│   ├── runtime_active_kids
│   ├── runtime_active_time
│   ├── runtime_enabled
│   ├── runtime_status
│   ├── runtime_suspended_time
│   └── runtime_usage
├── subsystem -> ../../../../class/tty
└── uevent  # 设备插拔信息, 和其他信息

cat /sys/devices/virtual/tty/tty1/dev
4:1   # 主设备号:次设备号 

cat /sys/devices/virtual/tty/tty1/uevent
MAJOR=4
MINOR=1
DEVNAME=tty1

cat /sys/devices/virtual/tty/tty2/dev
4:2

cat /sys/devices/virtual/tty/tty2/uevent
MAJOR=4
MINOR=2
DEVNAME=tty2

cat /sys/devices/virtual/block/loop0/dev
7:0

cat /sys/devices/virtual/block/loop1/dev
7:1

cat /sys/devices/virtual/block/loop1/uevent
MAJOR=7
MINOR=1
DEVNAME=loop1
DEVTYPE=disk
DISKSEQ=2
```
主设备号是相同类型的设备共享的, 此设备号则是这种类型设备下的 具体某个设备. tty就是相同类型的设备, 主设备号是4, 而里面的tty1到ttyn 就各有各的次设备号, 从1到n. 类比windows就是 磁盘驱动器就是主设备号, 里面的各个硬盘各有各的次设备号.

>Kset: 相同类型的kobject集合

kobject结构体为什么这么重要呢, 因为它构成了我们所有设备在系统中的树结构雏形: kobject结构体用来表示Linux系统中的一个设备, 相同类型的kobject通过其内嵌的list_head链成一个链表, 然后使用另外一个结构体kset来指向和管理这个列表. 

```c
struct kset {
	struct list_head list; 
	spinlock_t list_lock; 
	struct kobject kobj; 
	struct kset_uevent_ops *uevent_ops; 
}; 
```
- ![](assets/Pasted%20image%2020230509192225.png) 

kset结构体其实就是你在Linux的/sys目录下看到的不同设备的分类目录:  
```shell
├── block
├── bus
├── class
├── dev
├── devices
├── firmware
├── fs
├── hypervisor
├── kernel
├── module
└── power
```
在这个目录下面的每一个子目录, 其实都是相同类型的kobject集合kset. 然后`不同的kset组织成树状层次的结构`, 就构成了`sysfs子系统`. `Linux内核中各个设备的组织信息`就可以`通过sysfs子系统在用户态(/sys目录) 显示出来`, 用户就可以`通过这个接口`来查看系统的设备管理信息了. 

>Kset与子系统
- ![](assets/Pasted%20image%2020230509193040.png) 

结构体`kobject`也定义了很多方法, 用来`支持设备热插拔等事件`的管理. 当用户插入一个设备或拔出一个设备时, 系统中的设备信息也会随之发生更新. 在`结构体kobject中内嵌`了一个`kobj_type结构体`, 该结构体内`封装了很多关于设备插拔, 添加, 删除的方法`. 

>基类: kobj_type

```c
struct kobj_type {
	void (*release) (struct kobject *kobj) ; 
	const struct sysfs_ops *sysfs_ops; 
	struct attribute **default_attrs; 
	const struct kobj_ns_type_operations *(*child_ns_type) (struct kobject  *kobj); 
	const void *(*namespace) (struct kobject *kobj) ; 
}; 

kobject_add() ; 
kobject_del() ; 
```

以上就是`Linux设备管理模型`中比较重要的一些`结构体和对应的函数操作集.` 
- Linux系统中不同类型的设备, 如字符设备, 块设备, USB设备, 网卡设备的插拔, 注册, 注销管理其实`都是通过这些函数接口进行维护的`. 
- 唯一的不同就是, 不同的设备在`各自的xx_register()`注册函数中对`kobject_add()`做了不同程度的封装而已. 

如果我们使用面向对象编程的思维来分析, 我们就可以`把设备管理模型中定义的这些结构体类型和函数操作集`, 看成一个`基类`. 

其他字符设备, 块设备, USB设备都是`它的子类`, 这些子类通过继承`kobject基类`的`kobject_add()`和`kobject_del`方法来完成各自设备的`注册和注销`. 

以字符设备为例, 我们可以看到字符设备结构体cdev在内核中的定义. 

```c
struct cdev {
	struct kobject kobj;  //基类kobject
	struct module *owner;  
	const struct file_operations *ops; //操作基类
	struct list_head list;  //继承了双向环链 
	dev_t dev; 
	unsigned int count; 
} __randomize_layout; 
```

在结构类型cdev中, 我们通过内嵌结构体kobject来模拟对基类kobject的继承, 字符设备的注册与注销, 都可以通过继承基类的kobject_add() /kobject_del() 方法来完成. 与此同时, 字符设备在继承基类的基础上, 也完成了自己的扩展: 实现了自己的read/write/open/close接口, 并把这些接口以函数指针的形式封装在结构体file_operations中.
- ![](assets/Pasted%20image%2020230509194543.png) 
- 不同的字符设备, 会根据自己的硬件逻辑实现各自的read(), write()函数, 并注册到系统中. 当用户程序读写这些字符设备时, 通过这些接口, 就可以找到对应设备的读写函数, 对字符设备进行打开, 读写, 关闭等各种操作. 

## 总线设备模型

>驱动级别的代码复用

- 在Linux系统中, 每一个设备都要有一个对应的驱动程序, 否则就无法对这个设备进行读写. 
- Linux系统中每一个字符设备, 都有与其对应的字符设备驱动程序; 每一个块设备, 都有对应的块设备驱动程序. 
- 而对于一些`总线型的设备`, 如鼠标, 键盘, U盘等USB设备, `设备通信是按照USB标准协议进行的`. 
- Linux系统`为了实现最大化的驱动代码复用`, 设计了`设备-总线-驱动模型`: 用`总线提供的一些方法来管理设备的插拔信息`, 所有的`设备都挂到总线上`, `总线会根据设备的类型选择合适的驱动与之匹配`. 
- 通过这种设计, `相同类型的设备`可以`共享同一个总线驱动`, 实现了`驱动级的代码复用`. 

`与总线设备模型相关的3个结构体`分别为`device,bus,driver`, 其实它们也可以看成`基类kobject的子类`. 以device为例, 其结构体定义如下. 

```c
struct device {
	struct device *parent; 
	struct device_private *p; 
	struct kobject kobj;  //kobject
	const struct device_type *type; 
	struct bus_type *bus;  //bus
	struct device_driver *driver; //device_driver
	void *platform_data; 
	void *driver_data; 
	dev_t devt; 
	u32 id; 
	struct klist_node knode_class; 
	struct class *class; 
	void (*release) (struct device *dev) ; 
}; 
```

与字符设备cdev类似, 在结构体类型device的定义里, 也通过`内嵌kobject结构体`来完成对基类kobject的继承. 但其与字符设备不同之处在于, device结构体内部还`内嵌了bus_type`和`device_driver`, 用来`表示其挂载的总线和与其匹配的设备驱动`. 

`device结构体`可以看成一个`抽象类`, 我们无法使用它去创建一个具体的设备. `其他具体的总线型设备`, 如USB设备, I2C设备等可以`通过内嵌device结构体`来完成`对device类属性和方法的继承`. 

```c
struct usb_device {
	int devnum; 
	char devpath[16]; 
	u32 route; 
	enum usb_device_state state; 
	enum usb_device_speed speed; 
	struct usb_tt *tt; 
	int ttport; 
	unsigned int toggle[2]; 
	struct usb_device *parent; 
	struct usb_bus *bus; 
	struct usb_host_endpoint ep0; 
	struct device dev; //基类
	......
}
```

各种不同类型的USB设备, 如USB串口, USB网卡, 鼠标, 键盘等, 都可以按照上面的套路, 继续一级一级地继承下去. 以USB网卡为例, 其结构体类型为usbnet. 
device -> usb_device -> usbnet
```c
struct usbnet {
/* housekeeping */
	struct usb_device *udev; //基类
	struct usb_interface *intf; 
	struct driver_info *driver_info; 
	const char *driver_name; 
	void *driver_priv; 
	wait_queue_head_t wait; 
	struct mutex phy_mutex; 
	unsigned can_dma_sg: 1; 
	unsigned in,  out; 
	struct net_device *net; 
	struct usb_host_endpoint *status; 
	unsigned maxpacket; 
	struct mii_if_info mii; 
	…
```

usb串口: 
```c
struct usb_serial {
	struct usb_device *dev; 
	struct usb_serial_driver *type; 
	struct usb_interface *interface; 
	char num_interrupt_out; 
	char num_bulk_in; 
	char num_bulk_out; 
	struct usb_serial_port *port[MAX_NUM_PORTS]; 
	struct kref kref; 
	struct mutex disc_mutex; 
	void *private; 
…
}; 
```

- 从上到下依次继承
	- ![](assets/Pasted%20image%2020230509205758.png) 

`USB网卡`比较特殊, 虽然它`实现了网卡的功能`, 但是其`底层通信是USB协议`, 底层接口是`USB接口`, 而不是普通的以太网接口, 所以这里`涉及多重继承的问题`. USB网卡是一个子类, `usb_device和net_device都是它的基类`. 

面对Linux内核中一层又一层的结构体嵌套, 面对长长的结构体定义, 如果我们仍旧使用面向过程的思维去分析, 很快你就被其错综复杂的数据结构和多层嵌套关系(大于3层) 搞得晕头转向. 

当我们使用面向对象的思维重新去分析时, 会发现整个局面开始变得豁然开朗, 整个系统层次变得清晰. 它们之间就是单纯的继承关系, 子类继承基类的各种属性和方法, 然后完成各自设备的注册, 注销, 热插拔, 不同的设备再根据自己的特性和需要去扩展各自的属性和方法.

# Linux内核中的OOP思想: 继承

在面向对象编程中, 封装和继承其实是不分开的: `封装就是为了更好地继承.` 

我们将`几个类共同的一些属性和方法抽取出来, 封装成一个父类`, 就是为了`通过继承最大化地实现代码复用`. 通过继承, `子类可以直接使用父类中的属性和方法`. 

C语言有多种方式来`模拟`类的继承. 

上一节主要通过`内嵌结构体或结构体指针`来模拟继承, 这种方法`一般适用于一级继承`, 父类和子类`差异较大`的场合, 通过结构体封装, 子类将父类嵌在自身结构体内部, 然后子类在父类的基础上扩展自己的属性和方法, 子类对象可以自由地引用父类的属性和方法. 

继承的好处
- 通过继承, 形成多层的程序结构
- 结构清晰, 层次清晰, 易于维护
- 提高代码的复用性

>继承的实现方式一
- 内嵌结构体
	- 适用于: 基类和子类差异较大的场合, 一级继承
	- 通过结构体封装: 子类将父类嵌在其结构体内部
	- 然后子类在父类基础上扩展自己的属性和方法
	- 子类对象可以自由引用父类的属性和方法

## 继承与私有指针

>继承的实现方式二: 私有指针

为了更好地使用OOP思想理解内核源码, 我们可以把继承的概念定义得更宽松一点, 除了内嵌结构体, C语言还可以有其他方法来模拟类的继承, 如`通过私有指针`.

我们可以把`使用结构体类型定义各个不同的结构体变量`, 也可以看作继承, 各个`结构体变量就是子类`, 然后`各个子类通过私有指针扩展各自的属性或方法`. 

这种继承方法主要适用于`父类和子类差别不大的场合`. 

如Linux内核中的网卡设备, 不同厂家的网卡, 不同速度的网卡, 以及相同厂家不同品牌的网卡, 它们的读写操作基本上都是一样的, 都通过标准的网络协议传输数据, 唯一不同的就是不同网卡之间存在一些差异, 如I/O寄存器, I/O内存地址, 中断号等硬件资源不相同. 

遇到这些设备, 我们完全不必给每个类型的网卡都实现一个结构体. 我们可以将各个网卡一些相同的属性抽取出来, `构建`一个`通用的结构体net_device`, 然后通过一个`私有指针`, 指向每个网卡`各自不同的属性和方法`, 通过这种设计可以`最大程度地实现代码复用`. 如Linux内核中的net_device结构体. 

```c
//bfin_can.c
struct bfin_can_priv *priv = netdev_priv(dev) ; 
struct net_device { 
	char name[IFNAMSIZ]; 
	const struct net_device_ops *netdev_ops; 
	const struct ethtool_ops *ethtool_ops; 
	/* mid-layer private */
	void *ml_priv; // 私有指针
	struct device dev; 
}; 
```

在net_device结构体定义中, 我们可以看到一个私有指针成员变量: ml_priv. 当我们使用该结构体类型`定义不同的变量`来`表示不同型号的网卡设备`时, 这个`私有指针就会指向各个网卡自身扩展的一些属性`. 如在bfin_can.c文件中, bfin_can这种类型的网卡自定义了一个结构体, 用来保存自己的I/O内存地址, 接收中断号, 发送中断号等. 

```c
struct bfin_can_priv {
	struct can_priv can; 
	struct net_device *dev; //指向struct net_device 定义的变量来继承
	void __iomem *membase; 
	int rx_irq; 
	int tx_irq; 
	int err_irq; 
	unsigned short *pin_list; 
}; 
```

每个使用`net_device类型`定义的`结构体变量`, 都可以被看作是`基类net_device的一个子类`, 各个子类可以通过自定义的结构体类型(如bfin_can_priv) 在父类的基础上扩展自己的属性或方法, 然后将`结构体变量`中的`私有指针ml_priv`指向它们即可. 

## 继承与抽象类

>继承的实现方式三
- 抽象类
	- 含有纯虚函数的类, 不能实例化, 只能被子类继承
	- 纯虚函数: 父类不实现, 留给子类实现多态
- 抽象类作用
	- 实现抽象层, 管理父类与子类的继承关系
	- 通过分层, 提高代码复用性

`含有纯虚函数的类`, 我们一般称之为`抽象类`. 抽象类不能被实例化, 实例化也没有意义, 如animal类, 它只能被子类继承. 

抽象类的作用, 主要就是实现分层: 实现抽象层. 

当父类和子类之间的`差别太大`时, 很难通过继承来实现代码复用, 如生物类和狗类, 我们可以在它们之间添加一个animal抽象类.  狗不能直接继承生物类, 因为生物又分动物, 植物, 狗跟生物的特性差别太大. 

所以 生物 -> 动物 -> 狗 逐步具体. 前两个都是抽象, 只有狗类才能实例化一只狗, 猫类实例化一只猫.

抽象类主要用来`管理父类和子类的继承关系`, 通过分层来提高代码的复用性. 如上面设备模型中的device类, 位于kobj类和usb_device类之间, 通过分层, 可以更好地实现代码复用. 

>抽象类一般在高层父类, 基类, 比较抽象的那种, 不能实例化一个对象.

举个例子:
struct cdev 这个字符设备类, 是一个抽象类; 里面的struct file_operations 也是一个抽象类, 里面全是虚函数, 继承了这个操作抽象类的子类, 都必须实现里面的操作. 

写驱动的时候, 比如键盘这个字符设备, 就是去继承struct cdev这个抽象父类, 构造一个具体的 用于键盘的这个结构体子类, 去实现 里面的各种操作. 

>这个就是驱动框架. 驱动要做的就是继承, 封装, 实现多态的接口.

## 继承与接口

通过继承, 子类可以复用父类的属性和方法, 但是也会带来一些问题: 
- 多路继承关系
	- ![](assets/Pasted%20image%2020230509211141.png) 

在上面的继承关系中, B和C作为基类A的子类, 分别继承了A的属性和方法, 这是没有问题的. 但是D又分别以B和C为父类进行多路继承, 因为B和C都继承于A, 所以这就可能带来冲突问题, 这种问题一般被称为`多继承(钻石继承)问题`. 

为了避免这个问题, Java, C#干脆就不支持多重继承, 而是通过接口的形式来实现多重继承. 

- 什么是接口
	- 一个类支持的行为, 方法
	- 对象封装后, 留出来供别的对象使用的接口
- 接口的作用
	- 对象之间的通信: 通过接口交互
	- 不需要关注内部的实现, 当实现改变, 不影响接口的使用

- 接口与抽象类比较
	- 相同点
		- 都不能实例化为对象
		- 都是为了实现多态
	- 不同点
		- 接口是一些方法的封装, 不允许有数据成员
		- 抽象类被子类继承, 接口要被类实现

什么是接口呢？一个类支持的行为和方法就是接口. 一个类封装好以后, 留出API函数供别的对象使用, 这些API就是接口. 

不同的对象之间可以通过接口进行通信, 而不需要关心各自内部的实现, 只要接口不变, 内部实现即使改变了也不会影响接口的使用. 

接口与抽象类相比, 两者有很多相似的地方. 如两者都不能实例化对象, 都是为了实现多态. 不同点在于接口是对一些方法的封装, 在类中不允许有数据成员, 而抽象类中则允许有数据成员存在. 除此之外, 抽象类一般被子类继承, 而接口一般要被类实现. 

我们可以把接口看作一个退化了的多重继承. 接口简化了继承关系, 解决了多重继承的冲突, 可以将两个不相关的类建立关联. 

- 抽象类与接口
	- ![](assets/Pasted%20image%2020230509212106.png) 
		- 动物类, 植物类都可以看作抽象类. 
		- 植物这个抽象类, 这个类中包含光合作用这个方法, 花类和树类分别继承了植物类, 并分别扩展了各自的方法: 开花, 结果. 
		- 当我们想通过多重继承实现一个桃树类时, 此时就可能产生冲突了: 花类和树类都继承了抽象类植物的光合作用方法, 并分别实现了定义, 那么当桃树类想使用光合作用这个方法时该使用哪一个呢？
		- 此时, 我们可以改变继承方式: `改多重继承为单继承, 另一个继承使用接口代替`, 这样冲突就解决了. 
		- 再来分析动物类. 狗属于动物, 因此可以通过继承动物类, 来复用动物的吃, 喝, 睡, 叫等方法. 
		- 有些狗还会看门, 具有保安的行为和方法, 但是我们不能把保安当作狗类的一个父类, 因为两者差距实在太大了, 关联性不大, 此时我们应该考虑通过接口实现. 
		- 通过接口, 我们就将两个不相关的类: 保安和狗建立了关联, 狗类可以直接调用保安类封装的一些接口. 

同理, 在我们使用面向对象编程思想分析Linux内核的过程中, 如果遇到多重继承让我们的分析变得复杂时, 我们也可以考虑化繁为简, `将多重继承简化为单继承, 另一个继承使用接口代替`. 

通过这种方法, 我们可以把复杂问题降维分析, 将复杂问题拆解简单化. 如USB网卡驱动, 既有USB子系统, 又有网络驱动模块, 放在一起分析比较复杂, 我们可以通过接口, 将多重继承改为单继承, 就能将整个驱动的架构和分层关系简单化. 

- ![](assets/Pasted%20image%2020230509212448.png) 
- 以Linux内核中的`RTL8150USB网卡驱动`源码为例: 
	- 我们把以`usb_device为基类`的这条继承分支当作一个`接口`来处理(或者反过来作为单继承都可以), USB网卡通过usb_device封装的接口可以实现USB网卡设备的插拔检测, 底层数据传输等功能. 
	- 而对于`以net_device为基类的这路继承`, 我们把它看作一个普通的`单继承关系`, USB网卡以kobject为基类, 实现多级继承, 每一级的基类都扩展了各自的方法或封装了接口, 供其子类RTL8150调用. 
	- RTL8150网卡通过调用祖父类kobject的方法kobject_add() 将设备注册到系统; 通过调用device类的probe() 完成驱动和设备的匹配及设备的suspend, shutdown等功能; 通过调用net_device类实现的open, xmit, stop等接口完成网络设备的打开, 数据发送, 数据停止发送等功能

>我们可以把struct file_operations结构体看成一个抽象类. 驱动开发,  就是去实现这个结构体下的接口.  这个抽象类自己本身不去实现,  被别的结构体继承. 然后去实现.
>比如一个字符驱动,  就是用struct cdev作为父类,  再写一个子类结构体,  封装父类,  再去实现file_operations 中的操作函数.

```c
struct rtl8150 {
	unsigned long flags;
	struct usb_device *udev; //看做接口
	struct tasklet_struct tl;
	struct net_device *netdev; //看做父类
	struct urb *rx_urb, *tx_urb, *intr_urb;
	struct sk_buff *tx_skb, *rx_skb;
	struct sk_buff *rx_skb_pool[RX_SKB_POOL_SIZE];
	spinlock_t rx_pool_lock;
	struct usb_ctrlrequest dr;
	int intr_interval;
	u8 *intr_buff;
	u8 phy;
};
typedef struct rtl8150 rtl8150_t;

static int rtl8150_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{//初始化函数. 总线驱动的初始化函数 字符设备init是初始化函数
//下面这句 拿到结构体usb_device实例化的对象的首地址 把usb_device看做是接口
	struct usb_device *udev = interface_to_usbdev(intf);
	rtl8150_t *dev;         
	struct net_device *netdev;
   //实例化一个网卡设备. 所以父类是网卡设备
	netdev = alloc_etherdev(sizeof(rtl8150_t));
	if (!netdev)
		return -ENOMEM;

	dev = netdev_priv(netdev);

	dev->intr_buff = kmalloc(INTBUFSIZE, GFP_KERNEL);
	if (!dev->intr_buff) {
		free_netdev(netdev);
		return -ENOMEM;
	}

	tasklet_setup(&dev->tl, rx_fixup);
	spin_lock_init(&dev->rx_pool_lock);

	dev->udev = udev;
	dev->netdev = netdev;
	netdev->netdev_ops = &rtl8150_netdev_ops;
	netdev->watchdog_timeo = RTL8150_TX_TIMEOUT;
	netdev->ethtool_ops = &ops;
	dev->intr_interval = 100; /* 100ms */

	if (!alloc_all_urbs(dev)) {
		dev_err(&intf->dev, "out of memory\n");
		goto out;
	}
	if (!rtl8150_reset(dev)) {
		dev_err(&intf->dev, "couldn't reset the device\n");
		goto out1;
	}
	fill_skb_pool(dev);
	set_ethernet_addr(dev);

	usb_set_intfdata(intf, dev);
	SET_NETDEV_DEV(netdev, &intf->dev);
	if (register_netdev(netdev) != 0) {
		dev_err(&intf->dev, "couldn't register the device\n");
		goto out2;
	}
	dev_info(&intf->dev, "%s: rtl8150 is detected\n", netdev->name);
	return 0;
out2:
	usb_set_intfdata(intf, NULL);
	free_skb_pool(dev);
out1:
	free_all_urbs(dev);
out:
	kfree(dev->intr_buff);
	free_netdev(netdev);
	return -EIO;
}
```
# Linux内核中的OOP思想: 多态

`编译时多态: 重载`
- Kmalloc函数

`运行时多态: 覆盖`
- 回调函数

多态是面向对象编程中非常重要的一个概念, 在前面的面向对象编程基础一节中, 我们已经知道: 在子类继承父类的过程中, 一个接口可以有多种实现, 在不同的子类中有不同的实现, 我们通过基类指针去调用子类中的不同实现, 就叫作多态. 

我们也可以使用C语言来模拟多态: 如果我们把使用同一个结构体类型定义的不同结构体变量看成这个结构体类型的各个子类, 那么在初始化各个结构体变量时, 如果基类是抽象类, 类成员中包含纯虚函数, 则我们为函数指针成员赋予不同的具体函数, 然后通过指针调用各个结构体变量的具体函数即可实现多态. 
- ![](assets/Pasted%20image%2020230509214407.png) 
- ![](assets/Pasted%20image%2020230509214616.png) 
	- 定义了一个file_system结构类型, 并把它作为基类, 使用该结构体类型定义的ext和fat变量可以看作file_system的子类. 
	- 然后, 我们定义了一个指向基类的指针fp, 并通过基类指针fp去访问各个子类中同名函数的不同实现, C语言通过这种方法“模拟”了多态. 

- 继续分析 usb网卡
	- ![](assets/Pasted%20image%2020230509214859.png) 
	- 我们也可以把net_device结构体看作一个基类, 对于每一个实例化的结构体变量, 都代表一种不同的网卡, 都把它们看作net_device基类的子类. 每一个网卡都有各自不同的read/write实现, 并保存在各个结构体变量的net_device_ops里, 当一个指向net_device结构体类型的基类指针指向不同的结构体变量时, 就可以分别去调用不同子类(具体的网卡设备) 的读写函数, 从而实现多态. 