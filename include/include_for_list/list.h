#ifndef __ASD_LIST__
#define __ASD_LIST__

#include <iostream>
#include <string>
#include <map>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

using namespace std;

template <typename DataType>
struct Node
{
	DataType data;
	Node* next;

	Node(DataType d = 0, Node* n = nullptr) : data(d), next(n)
	{
	}
	Node(const Node& node2) : data(node2.data), next(node2.next)
	{
	}
	bool operator==(const Node& node2) const
	{
		return (data == node2.data);
	}
	bool operator!=(const Node& node2) const
	{
		if ((data != node2.data))
		{
			return true;
		}
	}
};

// example
// https://internalpointers.com/post/writing-custom-iterators-modern-cpp 

template <typename DataType>
class listIterator : public std::iterator<std::forward_iterator_tag, DataType>
{
public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = DataType;
	using pointer = Node<DataType>*;
	using reference = DataType&;

	listIterator(pointer tmp = nullptr) : p(tmp) {};
	reference operator*()
	{
		return p->data;
	}
	pointer  operator->()
	{
		return p;
	}

	listIterator& operator++()
	{
		if (p != nullptr)
		{
			p = p->next;
		}
		return *this;
	}
	listIterator operator++(int)
	{
		listIterator tmp(*this);
		++(*this);
		return tmp;
	}
	bool operator==(const listIterator& it2) const
	{
		return (p == it2.p);
	}
	bool operator!=(const listIterator& it2) const
	{
		return (p != it2.p);
	}

private:
	pointer p;
};

template <typename DataType>
class List
{
private:
	Node<DataType>* head;
	//Node<DataType>* last;
public:

	List(Node<DataType>* n = nullptr) : head(n)
	{
	}

	List(const DataType& d)
	{
		Node<DataType>* newNode = new Node<DataType>(d, nullptr);
		head = newNode;
	}

	bool isEmpty() const
	{
		return head == nullptr;
	}

	void InsertToHead(const DataType& d)
	{
		Node<DataType>* newNode = new Node<DataType>(d, head);
		head = newNode;
	}

	DataType ViewHead() const
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}
		return head->data;
	}

	void InsertToTail(const DataType& d)
	{
		Node<DataType>* newNode = new Node<DataType>(d, nullptr);

		if (isEmpty())
		{
			head = newNode;
		}
		else
		{
			Node<DataType>* current = head;

			while (current->next != nullptr)
			{
				current = current->next;
			}

			current->next = newNode;
		}
	}

	DataType ViewTail()
	{
		if (head == nullptr)
		{
			throw std::runtime_error("List is empty");
		}

		Node<DataType>* current = head;

		while (current->next != nullptr)
		{
			current = current->next;
		}

		return current->data;
	}

	void Delete(const DataType& d)
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		Node<DataType>* current = head;
		Node<DataType>* previous = nullptr;

		if (head->data == d)
		{
			head = head->next;
			delete current;
		}
		else
		{
			while ((current->data != d) && (current->next != nullptr))
			{
				previous = current;
				current = current->next;
			}
			if (current->data == d) {
				previous->next = current->next;
				delete current;
			}
		}
	}

	listIterator<DataType> begin() const
	{
		return listIterator<DataType>(head);
	}

	listIterator<DataType> tail() const
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		Node<DataType>* current = head;

		while (current->next != nullptr)
		{
			current = current->next;
		}

		return listIterator<DataType>(current);
	}

	listIterator<DataType> end() const
	{

		return listIterator<DataType>(nullptr);
	}

	~List()
	{
		Node<DataType>* current = head;
		map<Node<DataType>*, bool> visited; // дл€ цикла

		while (current != nullptr)
		{
			if (visited[current])
			{
				break;
			}

			visited[current] = true;
			Node<DataType>* tmp = current;
			current = current->next;

			delete tmp;
		}
	}

	List(const List& list2) : head(nullptr)
	{
		if (list2.head == nullptr)
		{
			return;
		}

		head = new Node<DataType>(list2.head->data);

		Node<DataType>* current = head;
		for (Node<DataType>* src = list2.head->next; src != nullptr; src = src->next)
		{
			current->next = new Node<DataType>(src->data);
			current = current->next;
		}


	}

	List& operator=(const List& list2)
	{
		if (this == &list2)
		{
			return *this;
		}

		Node<DataType>* current = list2.head;
		for (listIterator<DataType> iter = list2.begin(); iter != list2.end(); ++iter)
		{
			this->InsertToTail(*iter);
		}

		return *this;
	}

	void Clean()
	{
		while (!isEmpty())
		{
			Node<DataType>* tmp = head;
			head = head->next;

			delete tmp;
		}
	}

	void InsertAfter(const listIterator<DataType>& it, const DataType& d)
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		listIterator<DataType> iter = it;
		Node<DataType>* NewNode = new Node<DataType>(d, iter->next);

		iter->next = NewNode;
	}

	listIterator<DataType> Search(const DataType& d)
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		for (listIterator<DataType> iter = this->begin(); iter != this->end(); ++iter)
		{
			if (*iter == d)
			{
				return iter;
			}
		}
		throw std::runtime_error("undefined");

	}

	void Delete(const listIterator<DataType>& it)
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		Node<DataType>* current = head;
		Node<DataType>* previous = nullptr;

		listIterator<DataType> copy_start = it;

		if (copy_start == this->begin()) // ++
		{
			this->Clean();
		}
		else
		{
			listIterator<DataType> iter = this->begin();

			while (iter != copy_start)
			{
				previous = current;
				current = current->next;
				++iter;
			}

			while (current != nullptr)
			{
				Node<DataType>* tmp = current;
				current = current->next;
				delete tmp;
			}

			previous->next = nullptr;
		}
	}


	void Delete(const listIterator<DataType>& start, const listIterator<DataType>& finish)
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		Node<DataType>* current = head;

		listIterator<DataType> copy_start = start;
		listIterator<DataType> copy_finish = finish;

		if (copy_start == this->begin() && copy_finish != this->end()) //++
		{
			++copy_finish;
			while (copy_start != copy_finish)
			{
				Node<DataType>* tmp = current;
				current = current->next;
				++copy_start;
				delete tmp;
			}
			head = current;
		}
		else if (copy_start == this->begin() && copy_finish == this->end()) // ++
		{
			this->Clean();
		}
		else //if (copy_start != this->begin() && copy_finish != this->end())
		{
			++copy_finish;
			listIterator<DataType> iter = this->begin();
			Node<DataType>* previous = nullptr;

			while (iter != copy_start)
			{
				previous = current;
				current = current->next;
				++iter;
			}

			while (copy_start != copy_finish)
			{
				Node<DataType>* tmp = current;
				current = current->next;
				++copy_start;
				delete tmp;
			}

			previous->next = current;
		}


	}

	void DeleteAll(const DataType& d)
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		Node<DataType>* current = head;
		Node<DataType>* previous = nullptr;

		while (current != nullptr)
		{
			if (current->data == d)
			{
				Node<DataType>* current_to_delete = current;

				if (current == head)
				{
					head = head->next;
				}
				else
				{
					previous->next = current->next;
				}

				current = current->next;

				delete current_to_delete;
			}
			else
			{
				previous = current;
				current = current->next;
			}
		}
	}

	void Inverse()
	{
		Node<DataType>* prev = nullptr;
		Node<DataType>* current = head;
		Node<DataType>* next = nullptr;

		while (current != nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		head = prev;
	}

	List Merge(const listIterator<DataType>& start, const List& list2)
	{
		if (isEmpty())
		{
			return list2;
		}

		List<DataType> list_merged;

		listIterator<DataType> copy_start = start;
		listIterator<DataType> iter = this->begin();

		while (iter != copy_start)
		{
			list_merged.InsertToTail(*iter);
			++iter;
		}
		list_merged.InsertToTail(*copy_start);

		Node<DataType>* current_2 = list2.head;
		while (current_2 != nullptr)
		{
			list_merged.InsertToTail(current_2->data);
			current_2 = current_2->next;
		}

		++copy_start;


		while (copy_start != this->end())
		{
			list_merged.InsertToTail(*copy_start);
			++copy_start;
		}


		return list_merged;
	}

	void MergeWith(const listIterator<DataType>& start, const List& list2)
	{
		listIterator<DataType> copy_start = start;

		Node<DataType>* current_2 = list2.head;

		while (current_2 != nullptr)
		{
			this->InsertAfter(copy_start, current_2->data);
			current_2 = current_2->next;
			++copy_start;
		}
	}

	friend ostream& operator<<(ostream& os, const List<DataType>& l)
	{
		if (l.isEmpty())
		{
			os << "Empty list";
			return os;
		}

		for (listIterator<DataType> iter = l.begin(); iter != l.end(); ++iter)
		{
			os << *iter;
			os << " ";
		}

		return os;
	}

	friend istream& operator>>(istream& is, const List<DataType>& l)
	{
		DataType value = 0;
		while (is >> value)
		{
			l.InsertToTail(value);
		}

		return is;
	}

	void MadeUnique()
	{
		map<DataType, bool> data_seen;
		Node<DataType>* current = head;
		Node<DataType>* previous = nullptr;

		while (current != nullptr)
		{
			if (data_seen[current->data] == true)
			{
				Node<DataType>* tmp = current;
				current = current->next;

				if (previous != nullptr)
				{
					previous->next = current;
				}
				else
				{
					head = current;
				}

				delete tmp;
			}
			else
			{
				data_seen[current->data] = true;
				previous = current;
				current = current->next;
			}
		}

	}

	bool Cycle()
	{
		listIterator<DataType> fast = this->begin();
		listIterator<DataType> slow = this->begin();

		while (fast != this->end() && (++fast) != this->end())
		{
			++slow;
			++fast;

			if (slow == fast)
			{
				return true;
			}
		}

		return false;
	}

	void BreakCycle()
	{
		listIterator<DataType> fast = this->begin();
		listIterator<DataType> slow = this->begin();

		while (fast != this->end() && ++fast != this->end())
		{
			++slow;
			++fast;

			if (slow == fast)
			{
				slow = this->begin();

				while (slow != fast)
				{
					++slow;
					++fast;
				}

				listIterator<DataType> cycle_start = slow;

				listIterator<DataType> cycle_end = cycle_start;
				while (cycle_end != cycle_start)
				{
					++cycle_end;
				}

				Node<DataType>* node = cycle_end.operator->();
				node->next = nullptr;

				return;
			}
		}
	}

	string ToString()
	{
		string list_string = "";
		listIterator<DataType> iter = this->begin();

		for (iter; iter != this->end(); ++iter)
		{
			list_string += to_string(*iter);
			list_string += " > ";
		}

		list_string.pop_back();
		list_string.pop_back();
		list_string.pop_back();

		return list_string;
	}

	int GetSize() const
	{
		int size = 0;

		if (isEmpty())
		{
			return size;
		}

		Node<DataType>* current = head;

		while (current != nullptr)
		{
			size++;
			current = current->next;
		}

		return size;
	}

	List Merge(const List& list2)
	{
		List<DataType> list_merged;

		listIterator<DataType> iter1 = this->begin();
		listIterator<DataType> iter2 = list2.begin();

		for (; iter1 != this->end(); ++iter1)
		{
			list_merged.InsertToTail(*iter1);
		}

		for (; iter2 != list2.end(); ++iter2)
		{
			list_merged.InsertToTail(*iter2);
		}


		return list_merged;
	}

	bool operator==(const List& list2) const
	{
		if (this->GetSize() != list2.GetSize())
		{
			return false;
		}

		Node<DataType>* current1 = this->head;
		Node<DataType>* current2 = list2.head;

		while ((current1 != nullptr) && (current2 != nullptr))
		{
			if (current1->data != current2->data)
			{
				return false;
			}

			current1 = current1->next;
			current2 = current2->next;
		}

		return true;
	}

	DataType min() const
	{
		if (isEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		Node<DataType>* current = head;
		DataType min = head->data;

		while (current != nullptr)
		{
			if (current->data < min)
			{
				min = current->data;
			}

			current = current->next;
		}

		return min;

	}

	void Print()
	{
		Node<DataType>* p = head;
		while (p->next != nullptr) { //пока список не кончитс€
			cout << p->data << " ";
			p = p->next;
		}
		cout << p->data; //печать послед.
	}

	Node<DataType>* GetFirst()
	{
		return head;
	}

	void InsertCurr(Node<DataType>* prev, Node<DataType>* curr, DataType value)
	{
		Node<DataType>* p = new Node<DataType>(value, nullptr);

		
		if (head == nullptr) {
			head = p;
			return;
		}

		// ¬ставка в начало (перед head)
		if (prev == nullptr) {
			p->next = head;
			head = p;
			return;
		}

		// ¬ставка в конец (если curr == nullptr и prev->next == nullptr)
		if (curr == nullptr) {
			if (prev->next == nullptr) {
				prev->next = p;
			}
			else {
				delete p; // ќсвобождаем пам€ть, если вставка невозможна
				throw std::invalid_argument("Invalid prev node for insertion at the end");
			}
			return;
		}

		// ¬ставка между prev и curr
		prev->next = p;
		p->next = curr;
	}
};

#endif