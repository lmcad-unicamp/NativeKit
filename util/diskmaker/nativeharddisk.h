#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <storage.h>
#include <assert.h>
using namespace std;

class NativeHardDisk : public Storage {
	public:
		NativeHardDisk( size_t size, const char* path ) : Storage() {
			this->size = size * STORAGE_PAGE_SIZE;
			disk.open( path, ios::trunc | ios::binary | ios::in | ios::out );
			disk.seekp( this->size - 1 );
			disk.write( "0", 1 );
		}

		virtual void write( const char src ) {
			write( &src, 1 );
		}

		virtual void read( char &dst ) {
			read( &dst, 1 );
		}

		virtual size_t read( char* dst, size_t size ) {
			disk.seekg( offset, ios::beg );
			disk.read( dst, size );
			offset += size;
			return size;
		}

		virtual size_t write( const char* src, size_t size ) {
			disk.seekp( offset, ios::beg );
			disk.write( src, size );
			offset += size;
			return size;
		}

		~NativeHardDisk() {
			disk.close();
		}
	protected:
		fstream disk;
};
