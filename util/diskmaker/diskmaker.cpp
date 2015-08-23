#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <cstring>

#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

#include <nfsii.h>
#include <storage.h>
#include "nativeharddisk.h"

using namespace std;

void createFileAt( FileSystem &fs, string dst, string src ) {
	ifstream srcFile( src.c_str(), ifstream::binary );
	char data;

	if ( !srcFile )
		return;

	srcFile.seekg( 0, srcFile.end );
	int fileSize = srcFile.tellg();
	srcFile.seekg( 0, srcFile.beg );

	printf( "  > copying srcFile at: %s [%d]", src.c_str(), fileSize );

	if ( fs.touch( dst.c_str(), ( fileSize / STORAGE_PAGE_SIZE ) + 1 ) ) {
		fid_t fd = fs.open( dst.c_str() );
		fs.seek( fd, 0 );
		
		for ( int i = 0; i < fileSize; i++ ) {
			srcFile.read( &data, 1 );
			fs.write( fd, &data, 1 );
		}

		fs.close( fd );
		printf( " - done\n" );
	} else {
		printf( " - error\n" );
	}

	srcFile.close();
}

void createFolderAt( FileSystem &fs, string dst, string src ) {
	// struct stat st;
	// stat( src.c_str(), &st );
	// size_t fileSize = st.st_size;

	// printf( "%s %d\n", dst.c_str(), st.st_size );

	printf( "  > creating folder: %s", dst.c_str());

	if( fs.mkdir( dst.c_str() ) ) {
		printf( " - done\n" );
	} else {
		printf( " - error\n" );
	}
}

void cloneDirectory( FileSystem &fs, string dst, string src ) {
	struct stat fInfo;
	DIR *directory;

	directory = opendir( src.c_str() );

	while ( dirent *ep = readdir( directory ) ) {
		string dstPath = dst + "/" + ep->d_name;
		string srcPath = src + "/" + ep->d_name;
		stat( srcPath.c_str(), &fInfo );

		if( S_ISDIR( fInfo.st_mode ) ) {
			if (( strcmp( ep->d_name, "..") != 0 ) && ( strcmp( ep->d_name, ".") != 0 )) {
				createFolderAt( fs, dstPath, srcPath );
				cloneDirectory( fs, dstPath, srcPath );
			}
		} else {
			createFileAt( fs, dstPath, srcPath );
		}
	}

	closedir( directory );
}

int main( int argc, char* argv[] ) {
	if ( argc != 3 ) {
		cout << "Invalid input. See the documentation for more information." << endl;
		return 0;
	}

	NativeHardDisk hd( 3000, argv[2] );
	NFSII fs(hd);
	cloneDirectory( fs, "", argv[1] );
	return 0;
}

