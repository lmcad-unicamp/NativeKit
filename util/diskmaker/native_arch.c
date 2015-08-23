#include <stdint.h>
#include <types.h>

char _multiboot;
char _kernel_base;
char _kernel_top;
char _stack_base;
char _stack_top;
char _heap_base;
char _heap_top;
char _storage_base;
char _storage_top;

extern "C" void _reboot() {}
extern "C" void _sstate( void* buffer ) {}
extern "C" void _lstate( void* buffer ) {} 
extern "C" bool _pdupdate( void* pDir, uintptr_t vAddr, uintptr_t pAddr, uint8_t permission, size_t size = 1 ) {}
extern "C" void _pdprotect( void* pDir, void* vAddr, uint8_t permission, size_t size = 1 ) {}
extern "C" void _pdcreate( void* vAddr ) {}
extern "C" void _pdload( void* pDir ) {}
extern "C" void _pdsave( void* &pDir ) {}
extern "C" void _ptcreate( void* pTable, void* pDir, uintptr_t base ) {}
