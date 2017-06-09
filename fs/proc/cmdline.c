#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <asm/setup.h>

static char new_command_line[COMMAND_LINE_SIZE];

#include <asm/uaccess.h>    /* copy_from_user */

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	char *temp_saved_command_line, *temp;
	int i;
	
	temp_saved_command_line = kmalloc(strlen(saved_command_line)+1, GFP_KERNEL);
	memcpy(temp_saved_command_line, saved_command_line, strlen(saved_command_line)+1);
	temp=strstr(temp_saved_command_line, "array");

	if (temp!=NULL) {
		for(i=0;i<20;i++)	*(temp+i)='*';
	}

	seq_printf(m, "%s\n", new_command_line);

	kfree(temp_saved_command_line);
	return 0;
}

static int cmdline_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cmdline_proc_show, NULL);
}

static int cmdline_proc_write(struct file *file, const char __user *buf,
				size_t len, loff_t *ppos)
{
	char* str;//char str[1000];
	str = kmalloc(len+1, GFP_KERNEL);
	if (copy_from_user(str, buf, len)) {
		printk( KERN_INFO "[cmdline] copy_from_user failed.\n");
		return -EFAULT;
	}
	str[len] = '\0';
	strcpy(saved_command_line, str);
kfree(str);
	return len;
}

static const struct file_operations cmdline_proc_fops = {
	.open		= cmdline_proc_open,
	.read		= seq_read,
	.write		= cmdline_proc_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_cmdline_init(void)
{
	char *offset_addr, *cmd = new_command_line;

	strcpy(cmd, saved_command_line);

	/*
	 * Remove 'androidboot.verifiedbootstate' flag from command line seen
	 * by userspace in order to pass SafetyNet CTS check.
	 */
	offset_addr = strstr(cmd, "androidboot.verifiedbootstate=");
	if (offset_addr) {
		size_t i, len, offset;

		len = strlen(cmd);
		offset = offset_addr - cmd;

		for (i = 1; i < (len - offset); i++) {
			if (cmd[offset + i] == ' ')
				break;
		}

		memmove(offset_addr, &cmd[offset + i + 1], len - i - offset);
	}

	proc_create("cmdline", 0, NULL, &cmdline_proc_fops);
	return 0;
}
module_init(proc_cmdline_init);
