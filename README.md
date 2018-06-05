To try the kernel module execute the following steps:

0. Open a terminal
1. `git clone https://github.com/BjoernDaase/vfs-FATx.git`
2. `cd module`
3. `make` (if there are any libraries missing, try installing linux kernel headers, e.g. on Debian: apt-get install linux-headers-$(uname -r)	).
4. `sudo insmod FATx-vfs.ko` (this will load the LKM)
5. Information about the module can be seen by taping `modinfo FATx-vfs.ko`
6. If step 4 was executed correctly you should see a *FATx_vfs* entry when typing `lsmod`
7. Now we can remoce the LKM again using `sudo rmmod FATx_vfs.ko`
8. If all the steps before were executed corretly using `sudo tail -f /var/log/kern.log` (or if you do not sse anything `cat /var/log/kern.log | grep LKM`) should see entries like (timestamps and metainfo could differ)

Jun  1 09:02:07 bjoerns-HP kernel: [13446.920585] Hello from the FATxvfs LKM!  
Jun  1 09:02:17 bjoerns-HP kernel: [13457.138484] Goodbye from the FATxvfs LKM!

