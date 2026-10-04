#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/string.h>

#define BUF_SIZE 128

static char mood_buffer[BUF_SIZE] = "MindBridge ready";

static DEFINE_MUTEX(mood_lock);


/* READ FROM DEVICE */
static ssize_t mb_read(
    struct file *file,
    char __user *buffer,
    size_t length,
    loff_t *offset)
{
    ssize_t result;

    mutex_lock(&mood_lock);

    result = simple_read_from_buffer(
        buffer,
        length,
        offset,
        mood_buffer,
        strlen(mood_buffer)
    );

    mutex_unlock(&mood_lock);

    return result;
}


/* WRITE TO DEVICE */
static ssize_t mb_write(
    struct file *file,
    const char __user *buffer,
    size_t length,
    loff_t *offset)
{
    char temp[BUF_SIZE];
    size_t count;

    count = length < BUF_SIZE - 1
                ? length
                : BUF_SIZE - 1;

    if (copy_from_user(temp, buffer, count))
    {
        return -EFAULT;
    }

    temp[count] = '\0';

    mutex_lock(&mood_lock);

    strscpy(
        mood_buffer,
        temp,
        sizeof(mood_buffer)
    );

    mutex_unlock(&mood_lock);

    return count;
}


/* FILE OPERATIONS */
static const struct file_operations mb_fops =
{
    .owner = THIS_MODULE,
    .read = mb_read,
    .write = mb_write,
    .llseek = default_llseek,
};


/* DEVICE */
static struct miscdevice mb_device =
{
    .minor = MISC_DYNAMIC_MINOR,
    .name = "mindbridge",
    .fops = &mb_fops,
    .mode = 0600,
};


/* MODULE LOAD */
static int __init mb_init(void)
{
    int result;

    result = misc_register(&mb_device);

    if (result == 0)
    {
        pr_info("MindBridge device registered\n");
    }

    return result;
}


/* MODULE UNLOAD */
static void __exit mb_exit(void)
{
    misc_deregister(&mb_device);

    pr_info("MindBridge device removed\n");
}


module_init(mb_init);
module_exit(mb_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(
    "MindBridge virtual Linux character device"
);
MODULE_AUTHOR("MindBridge Project");
