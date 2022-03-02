#include <iostream>
using namespace std;

//doulby linked list

template <typename T>
class List
{
public:
	List();
	~List();


	T push_back(T data);
	T pop_back();
	T push_front(T data);
	T pop_front();
	T insert(T value, int index);
	T deleteAt(int index);
	void clear();
	int GetSize() { return Size; }
	T& operator[](const int index);
private:
	template <typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node* pPrev;



		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};

	int Size;
	Node<T>* head;
	Node<T>* tail; // reverse to head

};

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
List<T>::~List()
{
	clear();
}

template <typename T>
T List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
		Size++;
		return head->data;
	}
	else if (tail == nullptr)
	{
		tail = new Node<T>(data); // head - tail
		tail->pPrev = head;
		head->pNext = tail;
		Size++;
		return tail->data;
	}
	else
	{
		Node<T>* newTail = new Node<T>(data);
		newTail->pPrev = tail;
		tail = newTail;
		tail->pPrev->pNext = tail;
		//it's inefficient
		/*Node<T>* lastHead = this->head;
		while (lastHead->pNext != nullptr)
		{
			lastHead = lastHead->pNext;
		}
		lastHead->pNext = tail;*/
		Size++;
		return tail->data;

	}

}

template <typename T>
T List<T>::pop_back()
{
	//because we haven't declared a tail yet
	if (Size == 1) pop_front();
	else
	{
		Node<T>* temp = tail;
		T data = tail->data;
		tail = tail->pPrev;
		tail->pNext = nullptr;
		Size--;
		delete temp;
		return data;
	}
}

template <typename T>
T List<T>::push_front(T data)
{
	//I do so bacause the logic in the push_back is the same when we add first element
	if (head == nullptr) push_back(data);
	else if (tail == nullptr)
	{
		tail = head;
		head = new Node<T>(data, tail);
		tail->pPrev = head;
		Size++;
		return tail->data;
	}
	else
	{
		Node<T>* temp = new Node<T>(data);
		temp->pNext = head;
		head = temp;
		head->pNext->pPrev = head;
		Size++;
		return head->data;

	}
}

template <typename T>
T List<T>::pop_front()
{
	Node<T>* temp = head;
	T data = head->data;
	head = head->pNext;
	if (head != nullptr)
		head->pPrev = nullptr;
	Size--;
	delete temp;
	return data;
}
/// <summary>
/// insert item on the definite index(NB: index must be less than the length of the list)
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="data"></param>
/// <param name="index"></param>
/// <returns></returns>
template <typename T>
T List<T>::insert(T value, int index)
{
	if (index == 0) push_front(value);
	else if (index == Size - 1) push_back(value);
	else if (index >= Size) cout << "You cannot insert an element to an undeclared index(try to use push_back())" << endl;
	else
	{
		//0 1 2 3 4 | 5 6 7 8 9
		//              ^

		//0 1 2 3 4 | 5 n 6 7 8 9
		//              ^

		Node<T>* temp;
		bool isFromTail;
		if (index >= Size / 2)
		{
			temp = tail;
			index = Size - index - 1;
			isFromTail = true;
		}
		else
		{
			temp = head;
			isFromTail = false;
		}

		for (int i = 0; i < Size; i++)
		{
			if (index == i)
			{
				Node<T>* newNode = new Node<T>(value, temp, temp->pPrev);

				//!!! именно в таком порядке(потому как может нарушиться логика)
				temp->pPrev->pNext = newNode;
				temp->pPrev = newNode;

				Size++;
				return newNode->data;
			}

			temp = isFromTail ? temp->pPrev : temp->pNext;//!!!
		}

	}
}

template<typename T>
T List<T>::deleteAt(int index)
{
	if (index == 0) pop_front();
	else if (index == Size - 1) pop_back();
	else if (index >= Size) cout << "Warning!!!Index is bigger than size of a list" << endl;
	else
	{
		Node<T>* temp;
		bool isFromTail;

		if (index >= Size / 2)
		{
			temp = this->tail;
			isFromTail = true;
			index = Size - index - 1;
		}
		else
		{
			temp = this->head;
			isFromTail = false;
		}
		for (int i = 0; i < Size; i++)
		{
			if (index == i)
			{
				T data = temp->data;
				temp->pPrev->pNext = temp->pNext;
				temp->pNext->pPrev = temp->pPrev;
				delete temp;
				Size--;
				return data;
			}
			temp = isFromTail ? temp->pPrev : temp->pNext;
		}
	}

}

template <typename T>
void List<T>::clear()
{
	while (Size)
		pop_front();
}

template <typename T>
T& List<T>::operator[](const int index)
{
	if (index >= Size) cout << "The index is bigger than the size of list" << endl;
	else if (Size / 2 <= index) // index = 6, size = 10 => from the tail
	{
		//  0 1 2 3 4 5 6 7 8 9 index = 6, reverseIndex = 3 => Size - index - 1
		int reverseIndex = Size - index - 1;
		Node<T>* temp = this->tail;
		for (int i = 0; i < Size; i++)
		{
			if (reverseIndex == i)
			{
				return temp->data;
			}
			temp = temp->pPrev;
		}
	}
	else
	{
		Node<T>* temp = this->head;
		for (int i = 0; i < Size; i++)
		{
			if (index == i)
			{
				return temp->data;
			}
			temp = temp->pNext;
		}
	}

}




int main()
{
	//declaring a list(in brackets you can use any type of data)
	List<int> list;
	//add item to the end
	list.push_back(5);
	//add item to the front
	list.push_front(1);
	//delete item from the end
	list.pop_back();
	//delete item from the front
	list.pop_front();
	//insert item on the definite index()
	list.insert(15, 0);
	//dele

	return 0;
}


