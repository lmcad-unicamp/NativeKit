/* ---------------------------------------------------------------------------- *
 * Copyright (C) 2014-2015 Alisson Linhares de Carvalho.                        *
 * All rights reserved.                                                         *
 *                                                                              *
 * This file is part of the Native Kit.                                         *
 *                                                                              *
 * The Native Kit is free software: you can redistribute it and/or modify it    *
 * under the terms of the GNU Lesser General Public License as published by     *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * The Native Kit is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY   *
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  *
 * more details.                                                                *
 *                                                                              *
 * You should have received a copy of the GNU General Public License along with *
 * the Native Kit. If not, see <http://www.gnu.org/licenses/>.                  *
 * ---------------------------------------------------------------------------- */

#include <syscalls.h>

bool SysCalls::enabled = true;
System *SysCalls::sys = 0;

SysCalls::tSysCall SysCalls::syscalls[] = {
	sys_default, // sys_restart_syscall
	sys_exit,
	sys_fork,
	sys_read,
	sys_write,
	sys_open,
	sys_close,
	sys_wait,
	sys_default, // sys_creat
	sys_link,
	sys_unlink,
	sys_execve,
	sys_default, // sys_chdir
	sys_default, // sys_time
	sys_default, // sys_mknod
	sys_default, // sys_chmod
	sys_default, // sys_lchown16
	sys_default, // reserved
	sys_stat,
	sys_lseek,
	sys_getpid,
	sys_default, // sys_mount
	sys_default, // sys_oldumount
	sys_default, // sys_setuid16
	sys_default, // sys_getuid16
	sys_default, // sys_stime
	sys_default, // sys_ptrace
	sys_default, // sys_alarm
	sys_fstat,
	sys_default, // sys_pause
	sys_default, // sys_utime
	sys_default, // reserved
	sys_default, // reserved
	sys_default, // sys_access
	sys_default, // sys_nice
	sys_default, // reserved
	sys_default, // sys_sync
	sys_kill,
	sys_default, // sys_rename
	sys_default, // sys_mkdir
	sys_default, // sys_rmdir
	sys_default, // sys_dup
	sys_default, // sys_pipe
	sys_times,
	sys_default, // reserved
	sys_brk,
	sys_default, // sys_setgid16
	sys_default, // sys_getgid16
	sys_default, // sys_signal
	sys_default, // sys_geteuid16
	sys_default, // sys_getegid16
	sys_default, // sys_acct
	sys_default, // sys_umount
	sys_default, // reserved
	sys_default, // sys_ioctl
	sys_default, // sys_fcntl
	sys_default, // reserved
	sys_default, // sys_setpgid
	sys_default, // reserved
	sys_default, // sys_olduname
	sys_default, // sys_umask
	sys_default, // sys_chroot
	sys_default, // sys_ustat
	sys_default, // sys_dup2
	sys_default, // sys_getppid
	sys_default, // sys_getpgrp
	sys_default, // sys_setsid
	sys_default, // sys_sigaction
	sys_default, // sys_sgetmask
	sys_default, // sys_ssetmask
	sys_default, // sys_setreuid16
	sys_default, // sys_setregid16
	sys_default, // sys_sigsuspend
	sys_default, // sys_sigpending
	sys_default, // sys_sethostname
	sys_default, // sys_setrlimit
	sys_default, // sys_old_getrlimit
	sys_default, // sys_getrusage
	sys_gettimeofday,
	sys_default, // sys_settimeofday
	sys_default, // sys_getgroups16
	sys_default, // sys_setgroups16
	sys_default, // sys_old_select
	sys_default, // sys_symlink
	sys_default, // sys_lstat
	sys_default, // sys_readlink
	sys_default, // sys_uselib
	sys_default, // sys_swapon
	sys_reboot,
	sys_default,
	sys_default, // sys_old_mmap
	sys_default, // sys_munmap
	sys_default, // sys_truncate
	sys_default, // sys_ftruncate
	sys_default, // sys_fchmod
	sys_default, // sys_fchown16
	sys_default, // sys_getpriority
	sys_default, // sys_setpriority
	sys_default, // reserved
	sys_default, // sys_statfs
	sys_default, // sys_fstatfs
	sys_default, // sys_ioperm
	sys_default, // sys_socketcall
	sys_default, // sys_syslog
	sys_default, // sys_setitimer
	sys_default, // sys_getitimer
	sys_default, // sys_newstat
	sys_default, // sys_newlstat
	sys_default, // sys_newfstat
	sys_default, // sys_uname
	sys_default, // sys_iopl
	sys_default, // sys_vhangup
	sys_default, // reserved
	sys_default, // sys_vm86old
	sys_default, // sys_wait4
	sys_default, // sys_swapoff
	sys_default, // sys_sysinfo
	sys_default, // sys_ipc
	sys_default, // sys_fsync
	sys_default, // sys_sigreturn
	sys_default, // sys_clone
	sys_default, // sys_setdomainname
	sys_newuname,
	sys_default, // sys_modify_ldt
	sys_default, // sys_adjtimex
	sys_default, // sys_mprotect
	sys_default, // sys_sigprocmask
	sys_default, // reserved
	sys_default, // sys_init_module
	sys_default, // sys_delete_module
	sys_default, // reserved
	sys_default, // sys_quotactl
	sys_default, // sys_getpgid
	sys_default, // sys_fchdir
	sys_default, // sys_bdflush
	sys_default, // sys_sysfs
	sys_default, // sys_personality
	sys_default, // reserved
	sys_default, // sys_setfsuid16
	sys_default, // sys_setfsgid16
	sys_default, // sys_llseek
	sys_default, // sys_getdents
	sys_default, // sys_select
	sys_default, // sys_flock
	sys_default, // sys_msync
	sys_default, // sys_readv
	sys_default, // sys_writev
	sys_default, // sys_getsid
	sys_default, // sys_fdatasync
	sys_default, // sys_sysctl
	sys_default, // sys_mlock
	sys_default, // sys_munlock
	sys_default, // sys_mlockall
	sys_default, // sys_munlockall
	sys_default, // sys_sched_setparam
	sys_default, // sys_sched_getparam
	sys_default, // sys_sched_setschedule
	sys_default, // sys_sched_getschedule
	sys_default, // sys_sched_yield
	sys_default, // sys_sched_get_priorit
	sys_default, // sys_sched_get_priorit
	sys_default, // sys_sched_rr_get_inte
	sys_default, // sys_nanosleep
	sys_default, // sys_mremap
	sys_default, // sys_setresuid16
	sys_default, // sys_getresuid16
	sys_default, // sys_vm86
	sys_default, // reserved
	sys_default, // sys_poll
	sys_default, // sys_nfsservctl
	sys_default, // sys_setresgid16
	sys_default, // sys_getresgid16
	sys_default, // sys_prctl
	sys_default, // sys_rt_sigreturn
	sys_default, // sys_rt_sigaction
	sys_default, // sys_rt_sigprocmask
	sys_default, // sys_rt_sigpending
	sys_default, // sys_rt_sigtimedwait
	sys_default, // sys_rt_sigqueueinfo
	sys_default, // sys_rt_sigsuspend
	sys_default, // sys_pread64
	sys_default, // sys_pwrite64
	sys_default, // sys_chown16
	sys_default, // sys_getcwd
	sys_default, // sys_capget
	sys_default, // sys_capset
	sys_default, // sys_sigaltstack
	sys_default, // sys_sendfile
	sys_default, // reserved
	sys_default, // reserved
	sys_default, // sys_vfork
	sys_default, // sys_getrlimit
	sys_default, // sys_mmap_pgoff
	sys_default, // sys_truncate64
	sys_default, // sys_ftruncate64
	sys_default, // sys_stat64
	sys_default, // sys_lstat64
	sys_default, // sys_fstat64
	sys_default, // sys_lchown
	sys_default, // sys_getuid
	sys_default, // sys_getgid
	sys_default, // sys_geteuid
	sys_default, // sys_getegid
	sys_default, // sys_setreuid
	sys_default, // sys_setregid
	sys_default, // sys_getgroups
	sys_default, // sys_setgroups
	sys_default, // sys_fchown
	sys_default, // sys_setresuid
	sys_default, // sys_getresuid
	sys_default, // sys_setresgid
	sys_default, // sys_getresgid
	sys_default, // sys_chown
	sys_default, // sys_setuid
	sys_default, // sys_setgid
	sys_default, // sys_setfsuid
	sys_default, // sys_setfsgid
	sys_default, // sys_pivot_root
	sys_default, // sys_mincore
	sys_default, // sys_madvise
	sys_default, // sys_getdents64
	sys_default, // sys_fcntl64
	sys_default, // reserved
	sys_default, // reserved
	sys_default, // sys_gettid
	sys_default, // sys_readahead
	sys_default, // sys_setxattr
	sys_default, // sys_lsetxattr
	sys_default, // sys_fsetxattr
	sys_default, // sys_getxattr
	sys_default, // sys_lgetxattr
	sys_default, // sys_fgetxattr
	sys_default, // sys_listxattr
	sys_default, // sys_llistxattr
	sys_default, // sys_flistxattr
	sys_default, // sys_removexattr
	sys_default, // sys_lremovexattr
	sys_default, // sys_fremovexattr
	sys_default, // sys_tkill
	sys_default, // sys_sendfile64
	sys_default, // sys_futex
	sys_default, // sys_sched_setaffinity
	sys_default, // sys_sched_getaffinity
	sys_default, // sys_set_thread_area
	sys_default, // sys_get_thread_area
	sys_default, // sys_io_setup
	sys_default, // sys_io_destroy
	sys_default, // sys_io_getevents
	sys_default, // sys_io_submit
	sys_default, // sys_io_cancel
	sys_default, // sys_fadvise64
	sys_default, // reserved
	sys_default, // sys_exit_group
	sys_default, // sys_lookup_dcookie
	sys_default, // sys_epoll_create
	sys_default, // sys_epoll_ctl
	sys_default, // sys_epoll_wait
	sys_default, // sys_remap_file_pages
	sys_default, // sys_set_tid_address
	sys_default, // sys_timer_create
	sys_default, // sys_timer_settime
	sys_default, // sys_timer_gettime
	sys_default, // sys_timer_getoverrun
	sys_default, // sys_timer_delete
	sys_default, // sys_clock_settime
	sys_default, // sys_clock_gettime
	sys_default, // sys_clock_getres
	sys_default, // sys_clock_nanosleep
	sys_default, // sys_statfs64
	sys_default, // sys_fstatfs64
	sys_default, // sys_tgkill
	sys_default, // sys_utimes
	sys_default, // sys_fadvise64_64
	sys_default, // reserved
	sys_default, // sys_mbind
	sys_default, // sys_get_mempolicy
	sys_default, // sys_set_mempolicy
	sys_default, // sys_mq_open
	sys_default, // sys_mq_unlink
	sys_default, // sys_mq_timedsend
	sys_default, // sys_mq_timedreceive
	sys_default, // sys_mq_notify
	sys_default, // sys_mq_getsetattr
	sys_default, // sys_kexec_load
	sys_default, // sys_waitid
	sys_default, // reserved
	sys_default, // sys_add_key
	sys_default, // sys_request_key
	sys_default, // sys_keyctl
	sys_default, // sys_ioprio_set
	sys_default, // sys_ioprio_get
	sys_default, // sys_inotify_init
	sys_default, // sys_inotify_add_watch
	sys_default, // sys_inotify_rm_watch
	sys_default, // sys_migrate_pages
	sys_default, // sys_openat
	sys_default, // sys_mkdirat
	sys_default, // sys_mknodat
	sys_default, // sys_fchownat
	sys_default, // sys_futimesat
	sys_default, // sys_fstatat64
	sys_default, // sys_unlinkat
	sys_default, // sys_renameat
	sys_default, // sys_linkat
	sys_default, // sys_symlinkat
	sys_default, // sys_readlinkat
	sys_default, // sys_fchmodat
	sys_default, // sys_faccessat
	sys_default, // sys_pselect6
	sys_default, // sys_ppoll
	sys_default, // sys_unshare
	sys_default, // sys_set_robust_list
	sys_default, // sys_get_robust_list
	sys_default, // sys_splice
	sys_default, // sys_sync_file_range
	sys_default, // sys_tee
	sys_default, // sys_vmsplice
	sys_default, // sys_move_pages
	sys_default, // sys_getcpu
	sys_default, // sys_epoll_pwait
	sys_default, // sys_utimensat
	sys_default, // sys_signalfd
	sys_default, // sys_timerfd_create
	sys_default, // sys_eventfd
	sys_default, // sys_fallocate
	sys_default, // sys_timerfd_settime
	sys_default, // sys_timerfd_gettime
	sys_default, // sys_signalfd4
	sys_default, // sys_eventfd2
	sys_default, // sys_epoll_create1
	sys_default, // sys_dup3
	sys_default, // sys_pipe2
	sys_default, // sys_inotify_init1
	sys_default, // sys_preadv
	sys_default, // sys_pwritev
	sys_default, // sys_rt_tgsigqueueinfo
	sys_default, // sys_perf_event_open
	sys_default  // sys_recvmmsg
};

SysCalls::SysCalls() {

}

void SysCalls::init( System *sys ) {
	SysCalls::sys = sys;
}

void SysCalls::enable() {
	this->enabled = true;
}

void SysCalls::disable() {
	this->enabled = false;
}

void SysCalls::call( Registers &registers ) {
	uintr_t r0 = registers.r0;

	if ( r0 < (sizeof(syscalls) / sizeof(tSysCall)) )
		syscalls[r0]( sys, registers );
}
