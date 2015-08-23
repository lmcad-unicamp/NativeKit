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

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#undef errno

extern int errno;
char *__env[1] = { 0 };
char **environ = __env;

#define SYS_RESTART 0
#define SYS_EXIT    1
#define SYS_FORK    2
#define SYS_READ    3
#define SYS_WRITE   4
#define SYS_OPEN    5
#define SYS_CLOSE   6
#define SYS_WAIT    7
#define SYS_CREAT   8
#define SYS_LINK    9
#define SYS_UNLINK  10
#define SYS_EXECVE  11
#define SYS_CHDIR   12
#define SYS_MKNOD   14
#define SYS_CHMOD   15
#define SYS_LCHOW   16
#define SYS_STAT    18
#define SYS_LSEEK   19
#define SYS_GETPID  20
#define SYS_ALARM   27
#define SYS_FSTAT   28
#define SYS_KILL    37
#define SYS_TIMES   43
#define SYS_BRK     45
#define SYS_GETTIMEOFDAY 78
#define SYS_SLEEP 162
#define SYS_ACCESS  33

// Terminate a process.
extern "C" int _exit( int status ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_EXIT), "b"(status) : );
	return ret;
}

// Creates a new process by duplicating the calling process.
extern "C" int fork() {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_FORK) : );
	return ret;
}

// Read from a file descriptor.
extern "C" int read( int fd, char *buffer, int len ) {
	__asm__ __volatile__( "int $0x80" : "=a"(len) : "a"(SYS_READ), "b"(fd), "c"(buffer), "d"(len) : );
	return len;
}

// Write to a file descriptor.
extern "C" int write( int fd, char *buffer, int len ) {
	__asm__ __volatile__( "int $0x80" : "=a"(len) : "a"(SYS_WRITE), "b"(fd), "c"(buffer), "d"(len) : );
	return len;
}

// Open a file.
extern "C" int open( const char *path, int flags, int mode ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_OPEN), "b"(path), "c"(flags + 64 ), "d"(mode) : );
	return ret;
}

// Close a file descriptor.
extern "C" int close( int fd ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_CLOSE), "b"(fd) : );
	return ret;
}

// Wait for a child process.
extern "C" int wait( int *status ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_WAIT), "c"(status) : );
	return ret;
}

// Create a new link (directory entry) for the existing file, oldname.
extern "C" int link( const char *oldPath, const char *newPath ){
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_LINK), "b"(oldPath), "c"(newPath) : );
	return ret;
}

// Delete a name and possibly the file it refers to.
extern "C" int unlink( char *path ){
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_UNLINK), "b"(path) : );
	return ret;
}

// Executes the program pointed to by filename.
extern "C" int execve( char *path, char **argv, char **env ){
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_EXECVE), "b"(path), "c"(argv), "d"(env) : );
	return ret;
}

// Obtain information about the named file and write it to the area pointed to by the buf argument.
extern "C" int stat( const char *path, struct stat *st ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_STAT), "b"(path), "c"(st) : );
	return ret;
}

// Repositions the offset of the open file associated with the file descriptor fd to the argument offset.
extern "C" int lseek( int fd, int offset, int whence ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_LSEEK), "b"(fd), "c"(offset), "d"(whence) : );
	return ret;
}

// Shall return the process ID of the calling process.
extern "C" int getpid() {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_GETPID) : );
	return ret;
}

// Obtain information about the named file and write it to the area pointed to by the buf argument.
extern "C" int fstat( int fd, struct stat *st ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_FSTAT), "b"(fd), "c"(st) : );
	return ret;
}

// Send signal to a process 
extern "C" int kill( int pid, int sig ){
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_KILL), "b"(pid), "c"(sig) : );
	return ret;
}

// Stores the current process times in the struct tms.
extern "C" clock_t times( struct tms *buffer ){
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_TIMES), "b"(buffer) : );
	return ret;
}

extern "C" caddr_t brk( void *addr ) {
	register caddr_t ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_BRK), "b"(addr) : );
	return ret;
}

extern "C" caddr_t sbrk( int incr ) {
	static caddr_t heapPtr = 0;

	if ( (heapPtr == 0) && (( heapPtr = brk( 0 )) == (caddr_t) -1 ))
		_exit(1);

	caddr_t addr = heapPtr;
	heapPtr += incr;

	if ( brk( heapPtr ) == (caddr_t) -1 ) {
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	return addr;
}

// Returns the time of a day.
extern "C" int gettimeofday( struct timeval *p, struct timezone *z ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_GETTIMEOFDAY), "b"(p), "c"(z) : );
	return ret;
}

// The isatty() function tests whether fd is an open file descriptor referring to a terminal.
// obs.: isatty isn't a syscall!
extern "C" int isatty( int file ) {
	if ( file < 3 )
		return 1;

	errno = EINVAL;
	return 0;
}

// Generate a SIGALRM signal for the process after the number of realtime seconds specified.
extern "C" unsigned alarm( unsigned seconds ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_ALARM), "b"(seconds) : );
	return ret;
}

// Suspends the execution of the calling thread until the time specified in seconds has elapsed.
extern "C" int sleep( unsigned int seconds ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_SLEEP), "b"(seconds) : );
	return ret;
}

// Check user's permissions for a file.
extern "C" int access( const char *pathname, int mode ) {
	register int ret;
	__asm__ __volatile__( "int $0x80" : "=a"(ret) : "a"(SYS_ACCESS) : );
	return ret;
}
