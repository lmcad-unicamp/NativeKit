#include <ktest.h>

TEST( DLinkedList_PushAndPop )
	DLinkedList <int>list;
	REQUIRE( list.getSize() == 0 )
	size_t id1 = list.pushf(1); // 1
	size_t id2 = list.pushb(2); // 12
	size_t id3 = list.pushf(3); // 312
	size_t id4 = list.pushf(4); // 4312
	size_t id5 = list.pushb(5); // 43125

	REQUIRE( list.getElement(id1) == 1 )
	REQUIRE( list.getElement(id2) == 2 )
	REQUIRE( list.getElement(id3) == 3 )
	REQUIRE( list.getElement(id4) == 4 )
	REQUIRE( list.getElement(id5) == 5 )
	REQUIRE( list.popb() == 5 )
	REQUIRE( list.popb() == 2 )
	REQUIRE( list.popf() == 4 )
	REQUIRE( list.getSize() == 2 )
	REQUIRE( list.popf() == 3 )
	REQUIRE( list.popf() == 1 )
	REQUIRE( list.popf() == 0 )

	id5 = list.pushb(5); // 5
	id1 = list.pushf(1); // 15
	id2 = list.pushb(2); // 152
	id3 = list.pushf(3); // 3152
	id4 = list.pushb(4); // 31524

	REQUIRE( list.getCurrent() == 3 )
	REQUIRE( list.remove(id5))
	REQUIRE( list.getSize() == 4 )
	REQUIRE( list.remove(id3))
	REQUIRE( list.remove(id4))
	REQUIRE( !list.remove(id3))
	REQUIRE( list.getCurrent() == 1 )
	REQUIRE( !list.remove(id4))
	REQUIRE( !list.remove(id5))

	id3 = list.pushb(3);

	REQUIRE( list.popf() == 1 )
	REQUIRE( list.popf() == 2 )
	REQUIRE( list.getSize() == 1 )
	REQUIRE( list.getElement(id3) == 3 )
	REQUIRE( list.remove(id3) )
	REQUIRE( list.getSize() == 0 )
	REQUIRE( list.getElement(id3) == 0 )

	id1 = list.pushb(1);
	id2 = list.pushb(2);
	id3 = list.pushb(3);
	id4 = list.pushb(4);
	id5 = list.pushb(5);

	REQUIRE( list.getCurrent() == 1 )
	REQUIRE( list.remove(id1) )
	REQUIRE( list.getCurrent() == 2 )
	list.rRotate();
	REQUIRE( list.getCurrent() == 5 )
	REQUIRE( list.remove(id5) )
	REQUIRE( list.getCurrent() == 2 )
	REQUIRE( list.remove(id4) )
	list.lRotate();
	REQUIRE( list.getCurrent() == 3 )
	REQUIRE( list.popf() == 3 )
	REQUIRE( list.popf() == 2 )
	REQUIRE( list.popb() == 0 )
	REQUIRE( list.getSize() == 0 )
	REQUIRE( list.getCurrent() == 0 )
END
