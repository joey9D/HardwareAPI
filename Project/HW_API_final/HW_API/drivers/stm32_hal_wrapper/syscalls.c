// Minimal system calls for STM32 bare metal
// These are required by newlib

#include <sys/stat.h>
#include <errno.h>

#undef errno
extern int errno;

// Environment pointer
char *__env[1] = { 0 };
char **environ = __env;

// Exit program
void _exit(int status) {
    (void)status;
    while(1); // Infinite loop on embedded system
}

// Get process ID
int _getpid(void) {
    return 1;
}

// Kill process
int _kill(int pid, int sig) {
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

// Write to file/console
int _write(int file, char *ptr, int len) {
    (void)file;
    (void)ptr;
    return len; // Pretend we wrote everything
}

// Read from file/console
int _read(int file, char *ptr, int len) {
    (void)file;
    (void)ptr;
    (void)len;
    return 0; // No input available
}

// File status
int _fstat(int file, struct stat *st) {
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

// Check if file is terminal
int _isatty(int file) {
    (void)file;
    return 1; // Assume yes for simplicity
}

// Seek in file
int _lseek(int file, int ptr, int dir) {
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

// Close file
int _close(int file) {
    (void)file;
    return -1;
}

// Increase heap
void *_sbrk(int incr) {
    extern char _end;
    static char *heap_end = &_end;
    char *prev_heap_end = heap_end;
    
    heap_end += incr;
    return (void*)prev_heap_end;
}
