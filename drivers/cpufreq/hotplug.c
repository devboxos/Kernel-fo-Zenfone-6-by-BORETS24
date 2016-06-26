
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cpu.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/cpufreq.h>
#include <linux/input.h>
#include <linux/math64.h>
#include <linux/kernel_stat.h>
#include <linux/tick.h>
#include <linux/earlysuspend.h>
#include <linux/wait.h>

static void hotplug_early_suspend(struct early_suspend *h) {
	unsigned int cpu;

	/* unplug online cpu cores */
	
		for_each_present_cpu(cpu)
			if (cpu && cpu_online(cpu))
				cpu_down(3);
				cpu_down(1);

	/* suspend main work thread */
		//flush_workqueue(hotplug_wq);
	//cancel_delayed_work_sync(&hotplug_work);

	pr_info( "suspended\n");
}

static void __cpuinit hotplug_late_resume(struct early_suspend *h) {
	unsigned int cpu;

	/* hotplug offline cpu cores */
		for_each_present_cpu(cpu) {
			if (num_online_cpus() >= 4)
				break;
			if (!cpu_online(cpu))
				cpu_up(1);
				cpu_up(3);
		}
	/* resume main work thread */
		//queue_delayed_work_on(0, hotplug_wq, &hotplug_work,
		//		msecs_to_jiffies(200));

	pr_info( "resumed\n");
}

static struct early_suspend __refdata hotplug_early_suspend_handler = {
	.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN,
	.suspend = hotplug_early_suspend,
	.resume = hotplug_late_resume,
};

static int msm_hotplug_probe(struct platform_device *pdev)
{
	register_early_suspend(&hotplug_early_suspend_handler);
}

