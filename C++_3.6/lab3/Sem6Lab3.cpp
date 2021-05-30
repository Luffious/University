#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

template <class T>
class Node {
private:
	T _Key;
	Node<T>* _pleft;
	Node<T>* _pright;
	Node<T>* _pparent;
public:
	Node(T Key) : _Key(Key), _pleft(nullptr), _pright(nullptr), _pparent(nullptr) {}
	T getKey() { return _Key; }
	Node<T>* getPLeft() { return _pleft; }
	Node<T>* getPRight() { return _pright; }
	Node<T>* getPParent() { return _pparent; }
	void setKey(T Key) { _Key = Key; }
	void setPLeft(Node<T>* pnode) { _pleft = pnode; }
	void setPRight(Node<T>* pnode){ _pright = pnode; }
	void setPParent(Node<T>* pnode) { _pparent = pnode; }
};

template <class T>
void appendNode(Node<T>* proot, T value) {
	while (proot != nullptr) {
		if (value > proot->getKey()) {
			if (proot->getPRight() != nullptr) { proot = proot->getPRight(); }
			else {
				Node<T>* pright = new Node<T>(value);
				pright->setPParent(proot);
				proot->setPRight(pright);
				break;
			}
		}
		else if (value < proot->getKey()) {
			if (proot->getPLeft() != nullptr) { proot = proot->getPLeft(); }
			else {
				Node<T>* pleft = new Node<T>(value);
				pleft->setPParent(proot);
				proot->setPLeft(pleft);
				break;
			}
		}
		else if (value == proot->getKey()) { break; }
	}
}

template <class T>
Node<T>* searchNode(Node<T>* pnode, T value) {
	while (pnode != nullptr) {
		if (pnode == nullptr) {
			Node<T>* temp = nullptr;
			return temp;
		}
		if (value == pnode->getKey()) { return pnode; }
		if (value < pnode->getKey()) { pnode = pnode->getPLeft(); }
		else { pnode = pnode->getPRight(); }
	}
}

template <class T>
Node<T>* maxNode(Node<T>* pnode) {
	if (pnode->getPRight() == nullptr) { return pnode; }
	return maxNode(pnode->getPRight());
}

template <class T>
Node<T>* minNode(Node<T>* pnode) {
	while (pnode != nullptr) {
		if (pnode->getPLeft() == nullptr) { return pnode; }
		pnode = pnode->getPLeft();
	}
}

template <class T>
Node<T>* nextNode(Node<T>* pnode) {
	if (pnode->getPRight() != nullptr) { return minNode(pnode->getPRight()); }
	Node<T>* temp = pnode->getPParent();
	while (temp != nullptr && pnode == temp->getPRight()) {
		pnode = temp;
		temp = temp->getPParent();
	}
	return temp;
}

template <class T>
void deleteNode(Node<T>* proot, T value) {
	Node<T>* delete_node = searchNode(proot, value);
	if (delete_node != nullptr) {
		Node<T>* ancestor = delete_node->getPParent();
		if (delete_node->getPLeft() == nullptr && delete_node->getPRight() == nullptr) {
			if (ancestor->getPLeft() == delete_node) { ancestor->setPLeft(nullptr); }
			if (ancestor->getPRight() == delete_node) { ancestor->setPRight(nullptr); }
		}
		else if (delete_node->getPLeft() == nullptr || delete_node->getPRight() == nullptr) {
			if (delete_node->getPLeft() == nullptr) {
				if (ancestor->getPLeft() == delete_node) { ancestor->setPLeft(delete_node->getPRight()); }
				else { ancestor->setPRight(delete_node->getPRight()); }
				delete_node->getPRight()->setPParent(ancestor);
			}
			else {
				if (ancestor->getPLeft() == delete_node) { ancestor->setPLeft(delete_node->getPLeft()); }
				else { ancestor->setPRight(delete_node->getPLeft()); }
				delete_node->getPLeft()->setPParent(ancestor);
			}
		}
		else {
			Node<T>* successor = nextNode(delete_node);
			delete_node->setKey(successor->getKey());
			Node<T>* successor_parent = successor->getPParent();
			Node<T>* successor_right = successor->getPRight();
			if (successor_parent->getPLeft() == successor) {
				successor_parent->setPLeft(successor_right);
				if (successor->getPRight() != nullptr) { successor_right->setPParent(successor_parent); }
			}
			else {
				successor_parent->setPRight(successor_right);
				if (successor->getPRight() != nullptr) { successor_right->setPParent(successor_parent); }
			}
		}
	}
}

template <class T>
void deleteTree(Node<T>* pnode) {
	if (pnode != nullptr) {
		//deleteTree(pnode->getPLeft());
		//deleteTree(pnode->getPRight());
		pnode->setKey(NULL);
		pnode->setPLeft(nullptr);
		pnode->setPRight(nullptr);
		pnode->setPParent(nullptr);
	}
}

template <class T>
void printTreeOrdered(Node<T>* pnode) {
	if (pnode != nullptr) {
		printTreeOrdered(pnode->getPLeft());
		cout << pnode->getKey() << " ";
		printTreeOrdered(pnode->getPRight());
	}
}

template <class T>
void printTreeTLR(Node<T>* pnode) {
	if (pnode != nullptr) {
		cout << pnode->getKey() << " ";
		printTreeTLR(pnode->getPLeft());
		printTreeTLR(pnode->getPRight());
	}
}

template <class T>
void printTreeLRT(Node<T>* pnode) {
	if (pnode != nullptr) {
		printTreeLRT(pnode->getPLeft());
		printTreeLRT(pnode->getPRight());
		cout << pnode->getKey() << " ";
	}
}

void bubblesort(double* arr, int amount) {
	int i = 0;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int j = 0; j < amount - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				double temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = true;
			}
		}
		i += 1;
	}
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "ru");
	ofstream data;
	data.open("Sem6Lab3.txt");
	chrono::duration<double, micro> timer = std::chrono::microseconds::zero();
	for (int amount = 50000; amount <= 500000; amount += 50000) {
		cout << "N = " << amount << endl;
		data << "N = " << amount << endl;
		for (int test = 0; test < 20; test++) {
			double* a = new double[amount];
			Node<double> tree(NULL);
			if (test < 5) {
				for (int i = 0; i < amount; i++) {
					a[i] = (double)(rand()) / RAND_MAX;
				}
				bubblesort(a, amount);
				tree.setKey(a[0]);
				for (int i = 1; i < amount - 1; i++) {
					appendNode(&tree, a[i]);
				}
			}
			else {
				a[0] = (double)(rand()) / RAND_MAX;
				tree.setKey(a[0]);
				for (int i = 1; i < amount - 1; i++) {
					a[i] = (double)(rand()) / RAND_MAX;
					appendNode(&tree, a[i]);
				}
			}
			chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
			for (int i = 0; i < 100; i++) {
				searchNode(&tree, (double)(rand()) / RAND_MAX);
			}
			chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
			timer = end - start;
			if (test < 5) {
				cout << test + 1 << " Тест (с сортировкой).\tПоиск: " << timer.count() << " микро секунд.\n";
				data << test + 1 << " Тест (с сортировкой).\tПоиск: " << timer.count() << " микро секунд.\n";
			}
			else {
				cout << test + 1 << " Тест (без сортировки).\tПоиск: " << timer.count() << " микро секунд.\n";
				data << test + 1 << " Тест (без сортировки).\tПоиск: " << timer.count() << " микро секунд.\n";
			}
			start = chrono::high_resolution_clock::now();
			for (int i = 0; i < 100; i++) {
				appendNode(&tree, (double)(rand()) / RAND_MAX);
			}
			end = chrono::high_resolution_clock::now();
			timer = end - start;
			if (test < 5) {
				cout << test + 1 << " Тест (с сортировкой).\tВставка: " << timer.count() << " микро секунд.\n";
				data << test + 1 << " Тест (с сортировкой).\tВставка: " << timer.count() << " микро секунд.\n";
			}
			else {
				cout << test + 1 << " Тест (без сортировки).\tВставка: " << timer.count() << " микро секунд.\n";
				data << test + 1 << " Тест (без сортировки).\tВставка: " << timer.count() << " микро секунд.\n";
			}
			start = chrono::high_resolution_clock::now();
			for (int i = 0; i < 100; i++) {
				deleteNode(&tree, (double)(rand()) / RAND_MAX);
			}
			end = chrono::high_resolution_clock::now();
			timer = end - start;
			if (test < 5) {
				cout << test + 1 << " Тест (с сортировкой).\tУдаление: " << timer.count() << " микро секунд.\n";
				data << test + 1 << " Тест (с сортировкой).\tУдаление: " << timer.count() << " микро секунд.\n";
			}
			else {
				cout << test + 1 << " Тест (без сортировки).\tУдаление: " << timer.count() << " микро секунд.\n";
				data << test + 1 << " Тест (без сортировки).\tУдаление: " << timer.count() << " микро секунд.\n";
			}
			delete[]a;
			deleteTree(&tree);
		}
	}
	data.close();
	return 0;
}