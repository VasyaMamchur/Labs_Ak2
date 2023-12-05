#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include "hello1.h"

MODULE_AUTHOR("Vasya Mamchur <vasyamamchur089@gmail.com>");
MODULE_DESCRIPTION("'Hello, world!' within Linux Kernel tailored for Lab4");
MODULE_LICENSE("Dual BSD/GPL");


static unsigned int value = 2;
module_param(value, uint, 0444);
MODULE_PARM_DESC(hello, "How many times to display 'Hello, world!' ?");

static int __init hello2_init(void)
{
 if (value == 0 || (value >= 5 && value <= 10)) {
  pr_warn("Wrong number!\n");
 } else if (value > 10) {
  pr_err("Error! Your number is too large.\n");
  return -EINVAL;
 }

 pr_info("Hello2 module is loaded.\n");
 print_hello(value);
 return 0;
}
static void __exit hello2_exit(void)
{
 pr_info("Hello2 module is unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
