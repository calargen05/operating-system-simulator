#ifndef LIST_HPP
#define LIST_HPP

#include "List.h"

// CONST OPERATIOR CLASS

using namespace cop4530;

	template <typename T>
	List<T>::const_iterator::const_iterator() {
		current = nullptr;
	}

	template <typename T>
	const T & List<T>::const_iterator::operator*() const {
		return retrieve();
	}

	template <typename T>
	const T * List<T>::const_iterator::operator->() const {
		return current;
	}

	template <typename T>
	typename List<T>::const_iterator & List<T>::const_iterator::operator++() {
		current = current->next;
		return *this;
	}

	template <typename T>
	typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
		const_iterator old = *this;
		++(*this);
		return old;
	}

	template <typename T>
	typename List<T>::const_iterator & List<T>::const_iterator::operator--() {
		current = current->prev;
		return *this;
	}

	template <typename T>
	typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
		const_iterator old = *this;
		++(*this);
		return old;
	}

	template <typename T>
	bool List<T>::const_iterator::operator==(const const_iterator &rhs) const {
		return current == rhs.current;
	}

	template <typename T>
	bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const {
		return !(*this==rhs);
	}

	template <typename T>
	T& List<T>::const_iterator::retrieve() const {
		return current->data;
	}

	template <typename T>
	List<T>::const_iterator::const_iterator(Node * p) {
		current = p;
	}



	// ITERATOR CLASS


	// ask a question about what I'm supposed to put in the iterator constructor
	template <typename T>
	List<T>::iterator::iterator() {}

	template <typename T>
	T& List<T>::iterator::operator*() {
		return const_iterator::retrieve();
	}

	template <typename T>
	const T& List<T>::iterator::operator*() const {
		return const_iterator::operator*();
	}

	template <typename T>
	T* List<T>::iterator::operator->() {
		return &(this->current->data);
		//returns the data from the node the iterator is referring to
	}

	template <typename T>
	const T* List<T>::iterator::operator->() const {
		return const_iterator::operator->();
		// since this one is constant, the const itr pointer operator can be used here
	}

	template <typename T>
	typename List<T>::iterator& List<T>::iterator::operator++() {
		this->current = this->current->next;
		return *this;
	}

	template <typename T>
	typename List<T>::iterator List<T>::iterator::operator++(int) {
		iterator old = *this;
		++(*this);
		return old;
	}

	template <typename T>
	typename List<T>::iterator& List<T>::iterator::operator--() {
		this->current = this->current->prev;
		return *this;
	}

	template <typename T>
	typename List<T>::iterator List<T>::iterator::operator--(int) {
		iterator old = *this;
		++(*this);
		return old;
	}

	template <typename T>
	List<T>::iterator::iterator(Node* p) {
		const_iterator::current = p;
	}



	// LIST CLASS

	template <typename T>
	List<T>::List() {
		init();
	}

	template <typename T>
	List<T>::~List() {
		clear();
		delete head;
		delete tail;
	}

	template <typename T>
	List<T>::List(const List &rhs) {
		List copy = rhs;
		std::swap(*this, copy);
	}

	template <typename T>
	List<T>::List(List && rhs)
		: theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
	{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}

	// DONT FORGET TO ADD THE FUNCTION DEFINTIONS FOR THE 3 FUNCTIONS BELOW!

	// 10/18/24 3:52 pm : I know these 3 functions below aren't all the way correct
	
	// this one puts in the value "val" in the list "num" times

	template <typename T>
	List<T>::List(int num, const T& val)	{
		init();
		for(int i=0; i<num; i++)
			push_back(val);
	}
	
	// this one uses the const itr to put the values of the nodes the const itrs are pointing to in the list.

	template <typename T>
	List<T>::List(const_iterator start, const_iterator end) {
		init();
		while(start!= end) {
			push_back(*start);
			start++;
		}
	}

	template <typename T>
	const List<T>& List<T>::operator=(const List &rhs) {
		clear();
		// using the range-based for loop to add itr of any datatype
		for (const auto& i : rhs)
			push_back(i);
		return *this;
	}

	template <typename T>
	List<T> & List<T>::operator=(List && rhs) {
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);

		return *this;
	}

	template <typename T>
	void List<T>::init() {
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}

	template <typename T>
	int List<T>::size() const {
		return theSize;
	}

	template <typename T>
	bool List<T>::empty() const {
		return size() == 0;
	}

	template <typename T>
	void List<T>::clear() {
		while (!empty())
			pop_front();
	}

	template <typename T>
	void List<T>::reverse() {
		if(empty())
			return;
		else {
			// temp node to switch the pointers;
			Node* tempNode;
			// current node to traverse the list
			Node* curr = head;
			
			// instead of reversing the values of the list, the for loop reverses the pointers themselves in the list to reverse it
			for ( ; curr != nullptr; ) {
				tempNode = curr->prev;
				curr->prev = curr->next;
				curr->next = tempNode;
				curr = curr->prev;
			}
			
			tempNode = head;
			head = tail;
			tail = tempNode;
		}
	}

	template <typename T>
	T& List<T>::front() {
		return *begin();
	}

	template <typename T>
	const T& List<T>::front() const {
		return *begin();
	}

	template <typename T>
	T& List<T>::back() {
		return *--end();
	}

	template <typename T>
	const T& List<T>::back() const {
		return *--end();
	}

	template <typename T>
	void List<T>::push_front(const T& val) {
		insert(begin(), val);
	}

	template <typename T>
	void List<T>::push_front(T && val) {
		insert(begin(), std::move(val));
	}

	template <typename T>
	void List<T>::push_back(const T& val) {
		insert(end(), val);
	}

	template <typename T>
	void List<T>::push_back(T && val) {
		insert(end(), std::move(val));
	}

	template <typename T>
	void List<T>::pop_front() {
		erase(begin());
	}

	template <typename T>
	void List<T>::pop_back() {
		erase(--end());
	}
	
	// this function is simple, i use the itr class to iterate from the beginning of the list to the end 
	// and remove the node data values that are equal to "val"
	template <typename T>
	void List<T>::remove(const T& val) {
		auto itr = begin();
		while (itr != end()) {
			if (*itr == val)
				itr = erase(itr);
			else
				itr++;
		}
	}

	// prints out the values of each node in the list and spaces them out
	// really only used for the output operator
	template <typename T>
	void List<T>::print(std::ostream& os, char ofc) const {
		for (const_iterator itr = begin(); itr != end(); itr++)
			os << *itr << ofc;
	}

	template <typename T>
	typename List<T>::iterator List<T>::begin() {
		return head->next;
	}

	template <typename T>
	typename List<T>::const_iterator List<T>::begin() const {
		return head->next;
	}

	template <typename T>
	typename List<T>::iterator List<T>::end() {
		return tail;
	}

	template <typename T>
	typename List<T>::const_iterator List<T>::end() const {
		return tail;
	}

	template <typename T>
	typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
		Node *p = itr.current;
		theSize++;
		return {p->prev = p->prev->next = new Node{val, p->prev, p}};
	}

	template <typename T>
	typename List<T>::iterator List<T>::insert(iterator itr, T && val) {
		Node *p = itr.current;
		theSize++;
		return {p->prev = p->prev->next = new Node{std::move(val), p->prev, p}};
	}

	template <typename T>
	typename List<T>::iterator List<T>::erase(iterator itr) {
		Node* p = itr.current;
		iterator retVal {p->next};
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		theSize--;

		return retVal;
	}

	template <typename T>
	typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
		for (iterator itr = start; itr != end;)
			itr = erase(itr);

		return end;
	}

	// overloading comparison operators
	
	// checks the size for equality, then checks each node 1 by 1 in each list to see if any node values are inequal
	template <typename T>
	bool operator==(const List<T> & lhs, const List<T> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		auto lhs_i = lhs.begin();
		auto rhs_i = rhs.begin();
	
		for ( ;lhs_i!=lhs.end(), rhs_i!=rhs.end(); lhs_i++, rhs_i++) {
			if (*lhs_i != *rhs_i)
				return false;
		}
		return true;
	}

	// uses the comparison equal operator to check for inequality because the "==" operator overload was already done
	template <typename T>
	bool operator!=(const List<T> & lhs, const List<T> &rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const List<T> &l) {
		l.print(os);
		return os;
	}

#endif
