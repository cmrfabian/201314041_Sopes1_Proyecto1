//REFERENCIA: http://elixir.free-electrons.com/linux/latest/source/fs/proc/meminfo.c


#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/hugetlb.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/quicklist.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>
#include <asm/uaccess.h>
#include <asm/page.h>
#include <asm/pgtable.h>


struct sysinfo i;
unsigned long pages[NR_LRU_LISTS];
int lru;


static int memo_show(struct seq_file *m, void *v){
    long utilizada;
    long porcentaje;

    seq_printf(m, "201314041\n");
    seq_printf(m, "Christian Marlon Renato Fabián Natareno\n");
    seq_printf(m, "Linux Mint 18.3 Sylvia\n");

    #define K(x) ((x) << (PAGE_SHIFT - 10))
    si_meminfo(&i);

    for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
    pages[lru] = global_node_page_state(NR_LRU_BASE + lru);

    seq_printf(m,"Memoria Total: %8lu kB\n",K(i.totalram));
    seq_printf(m,"Memoria Libre: %8lu kB\n",K(i.freeram));

    
    utilizada = K(i.totalram) - K(i.freeram);
    porcentaje =  (utilizada * 100) / K(i.totalram);
    seq_printf(m,"Porcentaje de memoria utilizada: %8lu %%\n",porcentaje);

    #undef K
    return 0;
}

static int memo_open(struct inode *inode, struct file *file){
    return single_open(file, memo_show, NULL);
}

static const struct file_operations memo_fops = {
    .owner = THIS_MODULE,
    .open = memo_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init memo_init(void){    
    proc_create("memo_201314041", 0, NULL, &memo_fops);
    printk(KERN_INFO "201314041.\r\n");
    return 0;
}

static void __exit memo_exit(void){
    remove_proc_entry("memo_201314041", NULL);
    printk(KERN_INFO "Sistemas Operativos 1.\r\n");
}

module_init(memo_init);
module_exit(memo_exit);

MODULE_AUTHOR("Christian Fabián");
MODULE_DESCRIPTION("Proyecto 1 Sistemas Operativos 1");
MODULE_LICENSE("GPL");
