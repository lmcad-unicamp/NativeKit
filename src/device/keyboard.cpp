#include <keyboard.h>

// Teclado ABNT
uint8_t Keyboard::shiftEnabledMap[] = {
	   KEY_NULL, KEY_NULL , '!'      , '@'      , '#'      , '$'      , '%'
	, 0 /*¨*/  , '&'      , '*'      , '('      , ')'      , '_'      , '+'
	, KEY_NULL , KEY_NULL , 'Q'      , 'W'      , 'E'      , 'R'      , 'T'
	, 'Y'      , 'U'      , 'I'      , 'O'      , 'P'      , '`'      , '{'
	, 0        , KEY_NULL , 'A'      , 'S'      , 'D'      , 'F'      , 'G'
	, 'H'      , 'J'      , 'K'      , 'L'      , 128      , '^'      , '"'
	, KEY_NULL , '}'      , 'Z'      , 'X'      , 'C'      , 'V'      , 'B'
	, 'N'      , 'M'      , '<'      , '>'      , ':'      , KEY_NULL , KEY_NULL
	, KEY_NULL , 0x20     , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
};

uint8_t Keyboard::altgrEnabledMap[] = {
	   KEY_NULL, KEY_NULL   , 251      , 253      , 252      , 0/*£*/   , 189
	, 0 /*¬*/  , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , 0/*§*/
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , 0/*ª*/
	, 0        , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , 0/*'º'*/ , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , 0x20     , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
};

uint8_t Keyboard::shiftDisabledMap[] = {
	   KEY_NULL, KEY_NULL , '1'      , '2'      , '3'      , '4'      , '5'
	, '6'      , '7'      , '8'      , '9'      , '0'      , '-'      , '='
	, KEY_NULL , KEY_NULL , 'q'      , 'w'      , 'e'      , 'r'      , 't'
	, 'y'      , 'u'      , 'i'      , 'o'      , 'p'      , 0 /*´*/  , '['
	, 0        , KEY_NULL , 'a'      , 's'      , 'd'      , 'f'      , 'g'
	, 'h'      , 'j'      , 'k'      , 'l'      , 135      , '~'      , 0x27
	, KEY_NULL , ']'      , 'z'      , 'x'      , 'c'      , 'v'      , 'b'
	, 'n'      , 'm'      , ','      , '.'      , ';'      , KEY_NULL , '#'
	, KEY_NULL , 0x20     , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL , KEY_NULL
	, KEY_NULL , KEY_NULL , KEY_NULL , '7'      , '8'      , '9'      , '-'
	, '4'      , '5'      , '6'      , '+'      , '1'      , '2'      , '3'
	, '0'      , ','      , KEY_NULL , KEY_NULL , '\\'     , KEY_NULL , KEY_NULL
};

Keyboard::Keyboard() : enabled(true), currentMap(shiftDisabledMap) {
	this->startListening( SSID::KEYBOARD );
}

Keyboard::~Keyboard() {
	this->stopListening( SSID::KEYBOARD );
}

bool Keyboard::isReady() {
	return !buffer.isEmpty();
}

void Keyboard::read( char &c ) {
	while( buffer.isEmpty() );

	c = (char) ( buffer.remove() >> 8 );
}

void Keyboard::isr( const SSID ssid, Registers &registers ) {
	assert( ssid == SSID::KEYBOARD );

	uint8_t data = inb( 0x60 );

	if ( enabled && ( data < 224 ) ) {
		uint16_t key;

		if ( data <= 128 ) { // key up event
			key = ( currentMap[data] << 8 ) | data;

			if ( key == KEY_SHIFT_L || key == KEY_SHIFT_R )
				currentMap = shiftEnabledMap;
			else if ( key == KEY_ALTGR )
				currentMap = altgrEnabledMap;
			else
				buffer.insert( key );

		} else { // key down event
			data -= 128;
			key = ( currentMap[data] << 8 ) | data;

			if ( key == KEY_SHIFT_L || key == KEY_SHIFT_R || key == KEY_ALTGR )
				currentMap = shiftDisabledMap;
		}
	}
}
