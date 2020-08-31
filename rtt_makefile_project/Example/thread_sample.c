/*
 * 程序清单：创建、初始化、脱离线程
 *
 * 这个例子会创建两个线程，一个动态线程，一个动态线程。
 * 静态线程会在运行完毕后自动被系统脱离，动态线程会一直打印计数。
 */
#include "main.h"
#include "rtthread.h"
#include "finsh_api.h"

#define THREAD_PRIORITY            25
#define THREAD_STACK_SIZE          521
#define THREAD_TMIESLICE           5

static rt_thread_t tid1 = RT_NULL;

/* 线程1的入口函数 */
static void thread1_entry(void *parameter)
{
	rt_uint32_t count = 0;

	while (1)
	{
		/* 线程1采用低优先级运行，一直打印计数值 */
		rt_kprintf("thread1 count: %d\n", count++);
		rt_thread_delay(500);
	}
}

ALIGN(RT_ALIGN_SIZE);
static char thread2_static[1024];
static struct rt_thread thread2;

/* 线程2的入口函数 */
static void thread2_entry(void *parameter)
{
	rt_uint32_t count = 0;

	/* 线程2拥有高优先级，以抢占线程1而获得执行 */
	for (count = 0; count < 10; count++)
	{
		/* 线程2打印计数值 */
		rt_kprintf("thread2 count: %d\n", count);
	}
	rt_kprintf("thread2 exit\n");

	/* 线程2运行结束后也将自动被系统脱离 */
}

/* 线程实例 */
int thread_sample(void)
{
	/* 创建线程1，名称是thread1, 入口是thread1_entry */
	tid1 = rt_thread_create("thread1",
							thread1_entry,
							RT_NULL,
							THREAD_STACK_SIZE,
							THREAD_PRIORITY,
							THREAD_TMIESLICE);
	/* 如果获得线程控制块， 启动这个线程 */
	if (tid1 != RT_NULL)
		rt_thread_startup(tid1);

	/* 创建线程2，名称是thread2, 入口是thread2_entry */
	rt_thread_init(&thread2,
					"thread2",
					thread2_entry,
					RT_NULL,
					&thread2_static[0],
					sizeof(thread2_static),
					THREAD_PRIORITY - 1,
					THREAD_TMIESLICE);
	/* 如果获得线程控制块， 启动这个线程 */
	rt_thread_startup(&thread2);

	return 0;
}

/* 导出到msh命令中 */
MSH_CMD_EXPORT(thread_sample, thread sample);
