#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/init_task.h>


/**
 * Performs a DFS on a given task's children.
 *
 * @void
 */
void DFS(struct task_struct *task)
{  
    struct task_struct *child;
    struct list_head *list;

    printk("name: %s, pid: [%d], state: %li\
", task->comm, task->pid, task->state);
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        DFS(child);
    }
}

/**
 * This function is called when the module is loaded.
 *
 * @return 0  upon success
 */
int task_lister_init(void)
{
    printk(KERN_INFO"Loading Task Lister Module...\
");
    DFS(&init_task);

    return 0;
}

/**
 * This function is called when the module is removed.
 *
 * @void
 */
void task_lister_exit(void)
{
    printk(KERN_INFO"Removing Task Lister Module...\
");
}

// Macros for registering module entry and exit points.
module_init(task_lister_init);
module_exit(task_lister_exit);