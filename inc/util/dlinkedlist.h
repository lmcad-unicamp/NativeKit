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

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

	template <class T> class DLinkedList {
	protected:
		struct tNode {
			tNode *next;
			tNode *previous;
			T data;

			tNode( T data ) : data(data) {
				
			}
		};

	public:
		DLinkedList() : current(0), size(0) {

		}

		const size_t pushf( T data );
		const size_t pushb( T data );
		T remove( size_t id );
		T getElement( size_t id );
		T popf();
		T popb();
		void lRotate();
		void rRotate();

		inline const size_t getSize() const;
		inline T getCurrent() const;

		~DLinkedList() {
			while ( size > 0 ) popf();
		}

	protected:
		bool isAValidNode( tNode *node );

	private:
		tNode *current;
		size_t size;
	};

	template <class T> T DLinkedList<T>::getCurrent() const {
		if ( !current )
			return 0;

		return current->data;
	}

	template <class T> const size_t DLinkedList<T>::getSize() const {
		return size;
	}

	template <class T> void DLinkedList<T>::lRotate() {
		if ( current )
			current = current->previous;
	}

	template <class T> void DLinkedList<T>::rRotate() {
		if ( current )
			current = current->next;
	}

	template <class T> bool DLinkedList<T>::isAValidNode( tNode *node ) {
		if ( size == 0 )
			return false;
		else if ( size == 1 && current != node )
			return false;

		return node == node->next->previous;
	}

	template <class T> T DLinkedList<T>::getElement( size_t id ) {
		tNode *node = (tNode*) id;

		if ( !isAValidNode( node ) )
			return 0;

		return node->data;
	}

	template <class T> T DLinkedList<T>::remove( size_t id ) {
		tNode *node = (tNode*) id;

		if ( !isAValidNode( node ) )
			return 0;

		T result = node->data;

		if ( size > 1  ) {
			tNode *next     = node->next;
			tNode *previous = node->previous;
			next->previous  = previous;
			previous->next  = next;

			if ( current == node )
				current = previous;
		} else
			current = 0;

		size--;
		delete node;
		return result;
	}

	template <class T> const size_t DLinkedList<T>::pushb( T data ) {
		tNode *node = new tNode( data );

		if ( current ) {
			tNode *next    = current->next;
			next->previous = node;
			node->next     = next;
			node->previous = current;
			current->next  = node;
		} else {
			node->next     = node;
			node->previous = node;
			current        = node;
		}

		size++;
		return (const size_t) node;
	}

	template <class T> const size_t DLinkedList<T>::pushf( T data ) {
		current = (tNode*) pushb( data );
		return (const size_t) current;
	}

	template <class T> T DLinkedList<T>::popb() {
		rRotate();
		return popf();
	}

	template <class T> T DLinkedList<T>::popf() {
		if ( !current )
			return 0;

		tNode *node = current;

		if ( size > 1  ) {
			tNode *next     = node->next;
			tNode *previous = node->previous;
			next->previous  = previous;
			previous->next  = next;

			current = previous;
		} else
			current = 0;

		size--;
		T data = node->data;
		delete node;
		return data;
	}

#endif
