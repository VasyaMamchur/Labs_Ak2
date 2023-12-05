#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>


MODULE_AUTHOR("Vasya Mamchur <vasyamamchur089@gmail.com>");
MODULE_DESCRIPTION("'Hello, world!' within Linux Kernel tailored for Lab3");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int value = 1;
module_param(value, uint, 0444);
MODULE_PARM_DESC(hello, "How many times to display 'Hello, world!' ?");

struct array_node {
	struct list_head list_node;
	ktime_t timemarker;
};

static LIST_HEAD(Head_Node);

static int __init hello_init(void)
{

	int count;

	if (value == 0 || (value >= 5 && value <= 10)) {
		pr_warn("Wrong number!\n");
	} else if (value > 10) {
		pr_err("Error! Your number is too large.\n");
		return -EINVAL;
	}

	for (count = 0; count < value; count++) {
		struct array_node *md = kmalloc(sizeof(*md), GFP_KERNEL);

		md->timemarker = ktime_get();
		list_add(&md->list_node, &Head_Node);
		printk(KERN_EMERG "Hello, world!\n");
	}
	return 0;
}

static void __exit hello_exit(void)
{
	struct array_node *md, *tmp;

	list_for_each_entry_safe(md, tmp, &Head_Node, list_node) {
		ktime_t duration = ktime_sub(ktime_get(), md->timemarker);

		pr_info("Event time: %lld ns\n", ktime_to_ns(duration));
		list_del(&md->list_node);
		kfree(md);
	}
}

module_init(hello_init);
module_exit(hello_exit);
