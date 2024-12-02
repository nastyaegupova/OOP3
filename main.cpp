#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
    explicit Node(int d) {
        data = d;
        next = nullptr;
    }
};

class List {

private:
    Node* head;
    int size;


public:
    [[nodiscard]] Node * getHead() const {
        return head;
    }


public:
    ~List() {
        delete head;
    }

    List() : head{nullptr}, size{0} {}

    List(const List& a) : head(nullptr), size(0) {
        Node * last = nullptr;
        for (Node * n = a.head; n != nullptr; n = n->next) {
            Node * item = new Node(n->data);
            if (!head) {
                head = item;
            } else {
                last->next = item;
            }
            last = item;
            ++size;
        }
    }

    List(List&& a) noexcept : size(a.size), head(a.head) {
        a.head = nullptr;
    }

    explicit List(size_t n) : head(nullptr), size(n) {
        Node* current = nullptr;
        for (size_t i = 0; i < n; i++) {
            Node* item = new Node(0);
            if (!head) {
                head = item;
                current = head;
            } else {
                current->next = item;
                current = current->next;
            }
        }
    }

    List(const int a[], size_t n) : head(nullptr), size(0) {
        for (size_t i = 0; i < n; ++i) {
            Node* newNode = new Node(a[i]);
            if (!head) {
                head = newNode;
            } else {
                Node* current = head;
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }
            ++size;
        }
    }

    void clear() {
        while (head->next && head) {
            Node * temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }

    int at(int ind) {
        if (ind < 0) {
            ind += size;
        }
        Node* current = head;
        if (ind < 0) {
            return current->data;
        } else if (ind >= size) {
            for (int i = 0; i < size && current->next != nullptr; i++) {
                current = current->next;
            }
        } else {
            for (int i = 0; i < ind; i++) {
                current = current->next;
            }
        }
        return current->data;
    }

    void resize(size_t n) {
        if (n < size) {
            Node* temp = head;
            for (size_t i = 0; i < n - 1 && temp != nullptr; i++) {
                temp = temp->next;
            }
            if (temp != nullptr) {
                Node* del = temp->next;
                temp->next = nullptr;
                while (del != nullptr) {
                    Node* nextNode = del->next;
                    delete del;
                    del = nextNode;
                }
            }
        } else if (n > size) {
            Node* temp = head;
            while (temp && temp->next != nullptr) {
                temp = temp->next;
            }
            for (size_t i = size; i < n; i++) {
                Node* newNode = new Node(0);
                if (temp) {
                    temp->next = newNode;
                } else {
                    head = newNode;
                }
                temp = newNode;
            }
        }
        size = n;
    }

    void assign(size_t count, int value) {
        if (count > size) {
            Node* current = head;
            for (size_t i = 0; i < size && current != nullptr; ++i) {
                current->data = value;
                current = current->next;
            }
            for (size_t i = size; i < count; ++i) {
                Node* newNode = new Node(value);
                if (current) {
                    current->next = newNode;
                } else {
                    head = newNode;
                }
                current = newNode;
            }
        } else if (count < size) {
            Node* current = head;
            for (size_t i = 0; i < count; ++i) {
                current->data = value;
                current = current->next;
            }
            while (current != nullptr) {
                Node* del = current;
                current = current->next;
                delete del;
            }
        } else {
            Node* current = head;
            for (size_t i = 0; i < size && current != nullptr; ++i) {
                current->data = value;
                current = current->next;
            }
        }
        size = count;
    }

    size_t length() {
        return size;
    }

    bool empty() {
        return size == 0;
    }

    void swap(List& a) {
        std::swap(a.size, size);
        std::swap(a.head, head);
    }

    List &operator=(const List& other) {// оператор присваивания с помощью копирования
        if (this != &other) {//а и б
            Node* last = nullptr;//создаем узел
            for (Node* n = other.head; n != nullptr; n = n->next) {
                Node* item = new Node(n->data);//создаем узел еще один с данными other
                if (!head) {
                    head = item;
                } else {
                    last->next = item;
                }
                last = item;
                ++size;
            }
        }
        return *this;
    }

    List &operator=( List&& other) noexcept {// присвание с перемещением
        if (this != &other) {
            head = other.head;// данные из б переносит в а и обнуляет данные б
            size = other.size;
            other.head = nullptr;
            other.size = 0;
        }
        return *this;
    }

    friend bool operator==(const List& a, const List& b) {// оператор равенства
        if (a.size != b.size) return false;// сравниваем длину
        Node* cur1 = a.head;// указатель на наш а head
        Node* cur2 = b.head;
        while (cur1 && cur2) {
            if (cur1->data != cur2->data) return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return true;
    }

    friend bool operator!=(const List& a, const List& b) {// оператор неравенства
        return !(a == b);
    }

    friend bool operator<(const List& a, const List& b) {// оператор меньше
        Node* cur1 = a.head;
        Node* cur2 = b.head;
        while (cur1 && cur2) {
            if (cur1->data < cur2->data) return true;
            if (cur1->data > cur2->data) return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return a.size < b.size;
    }

    friend bool operator>(const List& a, const List& b) {
        return b < a;
    }

    friend bool operator<=(const List& a, const List& b) {
        return !(b < a);
    }

    friend bool operator>=(const List& a, const List& b) {
        return !(a < b);
    }

    int &operator[](const size_t ind) {// оператор квадратных скобок
        Node* current = head;
        for (size_t i = 0; i < ind; ++i) {
            current = current->next;// переходим к следущему узлу
        }
        return current->data;
    }

    friend std::ostream &operator<<(std::ostream& os, const List& a) {// оператор вывода
        Node* current = a.head;
        while (current) {
            os << current->data << " ";//Берём данные из списка текущего элемента и добавляем в поток
            current = current->next;//пишем в консоль
        }
        return os;
    }

    friend std::istream &operator>>(std::istream& is, List& a) {// оператор ввода
        a.clear();
        int value;
        while (is >> value) {// берем из потока число
            Node* newNode = new Node(value);// создаем узел с этим числом
            if (!a.head) {
                a.head = newNode;
            } else {
                Node* cur = a.head;
                while (cur->next) {
                    cur= cur->next;
                }
                cur->next = newNode;
            }
            ++a.size;
        }
        return is;

    }

    [[nodiscard]] bool contains(int val) const {// содержит ли наш список какое-то значение
        Node* current = head;
        while (current) {
            if (current->data == val) return true;
            current = current->next;
        }
        return false;
    }

    [[nodiscard]] size_t count(const int val) const {// сколько раз встречается то число
        size_t cnt = 0;
        Node* current = head;
        while (current) {
            if (current->data == val) ++cnt;
            current = current->next;
        }
        return cnt;
    }
};

void print(const List& a) {
    if (a.getHead() == nullptr) {
        return;
    }
    Node* current = a.getHead();
    while (current) {
        std::cout << current->data <<" ";
        current = current->next;
    }
}


int main(int argc, char const *argv[]) {

    std::stringstream ss{"1 3 5 7 9"};
    List a(5);
    ss >> a;
    assert(5 == a.length());
    assert(1 == a[0]);
    assert(9 == a[4]);
    std::cout << a;
    List b{a};
    assert(a == b);
    assert(3 == b[1]);
    assert(7 == b[3]);
    b[4] = 0;
    assert(0 == b[4]);
    assert(!b.contains(9));
    assert(b < a);
    assert(a > b);
    std::cout << b;
    List c;
    assert(0 == c.length());
    c = b;
    assert(b == c);
    c[1] = c[2] = 7;
    assert(7 == c[1]);
    assert(7 == c[2]);
    assert(3 == c.count(7));
    std::cout << c;
}