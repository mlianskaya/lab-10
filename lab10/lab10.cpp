#include <iostream>;
#include <string>;
using namespace std;

template <class T>
class MyPriorityQueue
{
private:
	struct Node //структура - элемент списка
	{
		T data; //данные
		int priority; //приоритет
		Node *next; //указатель на следующий элемент
	};
	Node *head; //указатель на первый элемент списка
public:
	MyPriorityQueue() //конструктор (создание пустого списка)
	{
		head = nullptr;
	}
	~MyPriorityQueue()
	{
		while (head) //до тех пор, пока головной элемент не равен NULL
		{
			//удаление элементов с начала
			Node *temp = head;
			head = head->next; //определяем новый головной элемент
			delete temp; //удаляем старый головной элемент
		}
	}
	void push(T value, int priority) //функция добавляет элемент в очередь с учетом приоритета
	{
		Node *newNode = new Node;//создаем новый элемент
		newNode->data = value;
		newNode->priority = priority;

		if (!head || priority < head->priority) 
		{
			newNode->next = head; //головной элемент сдвигаем на 1 позицию
			head = newNode; //делаем первым элементом в очереди новый элемент
		}
		else //ищем, куда поставить новый элемент в список, учитывая его приоритетность
		{
			Node *current = head; //задаем значение текущему элементу
			while (current->next && priority >= current->next->priority) 
			//пока не дошли до конца списка, и значение приоритетности текущего элемента меньше значение приоритетности нового элемента
			{
				current = current->next; //делаем текущим элементом следующий
			}
			newNode->next = current->next; //меняем позцию следующего элемента, ставим его вслед за новым
			current->next = newNode; //новый элемент ставим за текущим
		}
	}
	T pop() //функция берёт элемент из очереди с учетом приоритета и удаляет его
	{
		if (!head)
		{
			throw out_of_range("Queue is empty");
		}
		T value = head->data;
		Node *temp = head;
		head = head->next; //определяем новый головной элемент
		delete temp; //удаляем старый головной элемент
		return value;
	}
	T peek() //функция берёт элемент из очереди с учетом приоритета без удаления
	{
		return head->data;
	}
	int size()
	{
		int count = 0;
		Node *current = head;
		while (current) //пока текущий элемент не равен 0
		{
			count++; //увеличиваем счетчик
			current = current->next; //переходим к следующему элементу
		}
		return count;
	}
	friend ostream& operator<<(ostream& os, const MyPriorityQueue<T>& queue) //переопределение оператора вывода в поток
/*cтандартный выходной поток cout имеет тип std::ostream. первый параметр представляет ссылку на неконстантный объект ostream.
 второй параметр оператора определяется как ссылка на константный объекта класса, который надо вывести в поток.*/
	{
		Node* current = queue.head;
		while (current)
		{
			os << current->data << " ";
			current = current->next;
		}
		return os; //для совместимости с другими операторами переопределяемый оператор должен возвращать значение параметра std::ostream.
	}
	
};



int main()
{
	MyPriorityQueue <int> intQueue;
	intQueue.push(5, 2);
	intQueue.push(10, 1);
	intQueue.push(3, 3);
	intQueue.push(7, 4);
	cout << "First queue: " << intQueue << endl;
	cout << "Size: " << intQueue.size() << endl;
	cout << "Peek: " << intQueue.peek() << endl;

	cout << "----------------------------------------------\n";

	MyPriorityQueue <string> stringQueue;
	stringQueue.push("banana", 2);
	stringQueue.push("apple", 1);
	stringQueue.push("cherry", 3);
	cout << "Second queue: " << stringQueue << endl;
	cout << "Size: " << stringQueue.size() << endl;
	cout << "Peek: " << stringQueue.peek() << endl;

	stringQueue.pop();
	cout << "New queue: " << stringQueue << endl;
	cout << "Size: " << stringQueue.size() << endl;
	cout << "Peek: " << stringQueue.peek() << endl;

	return 0;
}