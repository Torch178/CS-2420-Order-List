#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>

template <class Type>
struct Node
{
	Type data{};
	Node* next{nullptr};
};

template <class Type>
class OrderedLinkedList;

template <class Type>
std::ostream& operator<<(std::ostream&, const OrderedLinkedList<Type>& list);


template <class Type>
class OrderedLinkedList
{
public:
	OrderedLinkedList();
	OrderedLinkedList(const OrderedLinkedList& other);
	OrderedLinkedList<Type>& operator=(const OrderedLinkedList<Type>& other);
	~OrderedLinkedList();

        int size() const;
        bool empty() const;
	Type get(int) const;
	Type getFirst() const;
	Type getLast() const;
	void insert(const Type&);
	int find(const Type&) const;
	void remove(const Type&);
        void clear();
        OrderedLinkedList<Type> everyOtherOdd();
        OrderedLinkedList<Type> everyOtherEven();
        friend std::ostream& operator<< <>(std::ostream&, const OrderedLinkedList<Type>& list);

protected:
	Node<Type>* head{ nullptr };
	Node<Type>* tail{ nullptr };
	int listSize = 0;
};

template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList()
{
}

template <class Type>
OrderedLinkedList<Type>::OrderedLinkedList(const OrderedLinkedList<Type>& other)
{
	//initialize values in case of an empty list
	if (other.head == nullptr) {
		this->head = nullptr;
		this->tail = nullptr;
		
	}
	this->listSize = 0;

	//copy values using currNode pointer
	Node<Type>* currNode = other.head;
	while (currNode != nullptr) {
		insert(currNode->data);
		currNode = currNode->next;
	}
	
}

template <class Type>
OrderedLinkedList<Type>& OrderedLinkedList<Type>::operator=(const OrderedLinkedList& other)
{
	if (this != &other) {
		//deallocate memory for linked list
		while (this->head != nullptr) {
			Node<Type>* NodeToDelete = this->head;
			this->head = head->next;
			delete NodeToDelete;
		}
		//copy over values from other
		this->listSize = 0;
		Node<Type>* currNode = other.head;
		while (currNode != nullptr) {
			insert(currNode->data);
			currNode = currNode->next;
		}

	}

return *this;
}

template <class Type>
OrderedLinkedList<Type>::~OrderedLinkedList()
{
	Node<Type>* NodeToDelete = head;
	while (head != nullptr) {
		NodeToDelete = head;
		head = head->next;
		delete NodeToDelete;
	}
	
}

template <class Type>
int OrderedLinkedList<Type>::size() const
{
return listSize;
}

template <class Type>
bool OrderedLinkedList<Type>::empty() const
{
	if (listSize == 0) { return true; }
	else { return false; }
}

template <class Type>
Type OrderedLinkedList<Type>::get(int pos) const
{
	if (pos > (listSize - 1) || pos < 0) {
		throw std::out_of_range("Error, index position out of bounds");
	}
	Node<Type>* currNode = head;
	int i = 0;
	while (currNode != nullptr) {
		if (i == pos) { return currNode->data; }
		i++;
		currNode = currNode->next;
	}
}

template <class Type>
Type OrderedLinkedList<Type>::getFirst() const
{
	if (head == nullptr) { throw std::out_of_range("Empty list"); }
	else {
		return head->data;
	}
   
}

template <class Type>
Type OrderedLinkedList<Type>::getLast() const
{
	if (tail == nullptr) { throw std::out_of_range("Empty list"); }
	else {
		return tail->data;
	}
   
}

template <class Type>
void OrderedLinkedList<Type>::insert(const Type& item)
{
	Node<Type>* newNode = new Node<Type>;
	newNode->data = item;
	newNode->next = nullptr;
	//empty list
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		Node<Type>* currNode = head;
		Node<Type>* prevNode;
		while (currNode != nullptr) {
			prevNode = currNode;
			//if current node is less than or equal the new node data then we need to move to next position in list or insert new node after current node if we're at the end of the list
			if (currNode->data <= item) {
				if (tail == currNode) {
					currNode->next = newNode;
					tail = newNode;
					newNode->next = nullptr;
					break;
				}
				else {
				
					currNode = currNode->next;
				}

			}
			//if the current node is greater than the new node data, then we need to insert the new node here and shift the current node over.
			if ((currNode->data > item) && (head != currNode)) {
				prevNode->next = newNode;
				newNode->next = currNode;
				break;
			}
			if((currNode->data > item) && (head == currNode)) {
				newNode->next = currNode;
				head = newNode;
				break;
			}
		}//end of while loop
		
	}

	listSize++;

}

template <class Type>
int OrderedLinkedList<Type>::find(const Type& item) const
{
	int i = 0;
	Node<Type>* currNode = head;
	while (currNode != nullptr && listSize > 0) {
		if (currNode->data == item) { 
			return i; }
		else {
			i++;
			currNode = currNode->next;
		}
		
	}
	return -1;
}

template <class Type>
void OrderedLinkedList<Type>::remove(const Type& item)
{
	Node<Type>* currNode = head;
	Node<Type>* prevNode = head;
	while (currNode != nullptr) {
		//check to see if you're at the correct node to remove
		if (currNode->data == item) {
			if (head == currNode) {
				head = currNode->next;
				delete currNode;
				listSize--;
				break;
			}
			else {
				prevNode->next = currNode->next;
				if (currNode == tail) {
					tail = prevNode;
				}
				delete currNode;
				listSize--;
				break;
			}
		}//end of item check
		prevNode = currNode;
		currNode = currNode->next;
	}//end of while loop
}

template <class Type>
void OrderedLinkedList<Type>::clear()
{
	Node<Type>* currNode = head;
	Node<Type>* nodeToDelete;
	while (currNode != nullptr) {
		nodeToDelete = currNode;
		currNode = currNode->next;
		delete nodeToDelete;
		listSize--;
	}
	head = nullptr;
	tail = nullptr;
}


template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherOdd(){
	OrderedLinkedList<Type> retVal;
	int i = 0;
	Node<Type>* currNode = this->head;

	while (currNode != nullptr) {
		if (i % 2 == 0) { retVal.insert(currNode->data); }

		currNode = currNode->next;
		i++;
	}

return retVal;
}

template <class Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherEven(){
	OrderedLinkedList<Type> retVal;
	int i = 0;
	Node<Type>* currNode = this->head;

	while (currNode != nullptr) {
		if (i % 2 == 1) { retVal.insert(currNode->data); }

		currNode = currNode->next;
		i++;
	}
return retVal;
}

template <class Type>
std::ostream& operator<<(std::ostream& out, const OrderedLinkedList<Type>& list)
{
	Node<Type>* currNode = list.head;
	while (currNode != nullptr) {
		if (currNode->next != nullptr) {
			out << currNode->data << "->";
		}
		else {
			out << currNode->data;
		}

		currNode = currNode->next;
	}

	return out;
}
#endif
