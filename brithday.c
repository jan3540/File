#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/init.h>
//声明一个list_head对象
 static LIST_HEAD(brithday_list);
//定义插入链表的结构
struct brithday { int day; int month; int year; struct list_head list;
};
//brithday()将实例添加到链表中，(通过list_add_tail()函数)，通过引用函数避免代码重复
void brithday(int day, int month, int year, struct brithday *person)
{ person->day=day; person->month=month; person->year=year; INIT_LIST_HEAD(&person->list); list_add_tail(&person->list, &brithday_list);
}
//内核模块入口函数
int brithday_init(void){
//创建并初始化struct brithday的实例 struct brithday *person; struct brithday *ptr;
 char n[5]={'a','b','c','d','e'}; int i=0;
//设置五个人的名字，便于区分 person = kmalloc(sizeof(*person)*5, GFP_KERNEL); brithday(1,10,2020,person); person=person+1; brithday(2,9,2021,person); person=person+1; brithday(3,8,2022,person); person=person+1; brithday(4,7,2023,person); person=person+1; brithday(5,6,2024,person); //遍历链表并循环输出五个人的出生日期到缓冲区 list_for_each_entry(ptr, &brithday_list, list) { printk(KERN_INFO "%c 的出生日期是： %d 年 %d月 %d 日.\n",n[i],ptr->year,ptr->month,ptr->day); i=i+1; }
printk(KERN_INFO "Loading Module\n"); return 0;
}
//内核注册模块的退出函数
void brithday_exit(void)
{ struct brithday *ptr, *next; list_for_each_entry_safe(ptr, next, &brithday_list, list){ list_del(&ptr->list); kfree(ptr); } printk(KERN_INFO "Removing Moudle\n");
}
module_init(brithday_init);
module_exit(brithday_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Module");
MODULE_AUTHOR("SGG");
