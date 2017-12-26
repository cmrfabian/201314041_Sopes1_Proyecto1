//REFERENCIA: http://elixir.free-electrons.com/linux/v4.14.8/source/include/linux/sched.h

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>

#define for_each_process(p) \
	for (p = &init_task ; (p = next_task(p)) != &init_task ; )


struct task_struct *task;
static int cpu_show(struct seq_file *m, void *v){

    seq_printf(m, "201314041\n");
    seq_printf(m, "Christian Marlon Renato Fabián Natareno\n");
    seq_printf(m, "Linux Mint 18.3 Sylvia\n");
    
    for_each_process(task) {
                        
        seq_printf(m,"PID:\t%d", task->pid);
         seq_printf(m,"\tEstado: %ld", task->state);
        if(task->state == -1)
        {
            seq_printf(m,"\tEstado: %s", "No ejecutable");
        }
        else if(task->state == 0)
        {
            seq_printf(m,"\tEstado: %s", "R"); // Running
        }
        else
        {
            seq_printf(m,"\tEstado: %s", "Parado");
        }
        
        seq_printf(m,"\tNombre: %s\n", task->comm);
 
    }   
   
    return 0;
}

static int cpu_open(struct inode *inode, struct file *file){
    return single_open(file, cpu_show, NULL);
}

static const struct file_operations cpu_fops = {
    .owner = THIS_MODULE,
    .open = cpu_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init mod_cpu_init(void){    
    proc_create("cpu_201314041", 0, NULL, &cpu_fops);
    printk(KERN_INFO "Christian Marlon Renato Fabián Natareno\r\n");
    return 0;
}

static void __exit mod_cpu_exit(void){
    remove_proc_entry("cpu_201314041", NULL);
    printk(KERN_INFO "Sistemas Operativos 1.\r\n");
}

module_init(mod_cpu_init);
module_exit(mod_cpu_exit);

MODULE_AUTHOR("Christian Fabián");
MODULE_DESCRIPTION("Proyecto 1 Sistemas Operativos 1");
MODULE_LICENSE("GPL");
