#include <iostream>
using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node<T>* next;
    Node(T data = T(),Node<T>* next = NULL) : data(data),next(next){}
};

template <typename T>
class Stack{
    Node<T>* root;
    int length;
    void makeEmpty(){
        while(!isEmpty()) pop();
    }
public:
    Stack() : root(NULL) , length(0){}
    ~Stack() {makeEmpty();}
    Stack(Stack& r_stack) : Stack(){
        assign(r_stack);
    }
    void operator =(Stack& r_stack){
        assign(r_stack);
    }
    void assign(Stack& r_stack){
        if (r_stack.isEmpty()) throw invalid_argument("Referans alinan liste bos!!!");
        makeEmpty();
        Node<T>* temp = r_stack.begin();
        root = new Node<T>(temp->data);
        Node<T>* loc = begin();
        temp = temp->next;
        while(temp != r_stack.end()){
            loc->next = new Node<T>(temp->data);
            loc = loc->next;
            temp=temp->next;
        }
    }
    Node<T>* begin() const{return root;}
    Node<T>* end() const{return NULL;}
    bool isEmpty() const{return begin() == end();}
    void push(const T& val){
        Node <T>* newData = new Node<T>(val,root);
        root = newData;
        length++;
    }
    void print() const{
        Node<T>* temp = begin();
        while (temp != end()){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void pop(){
        if (isEmpty()) throw invalid_argument("Listede silinebilecek bir eleman yok!");
        else{
            Node<T>* temp = begin();
            root = root->next;
            delete [] temp;
        }
        length--;
    }
    T top() const{
        if (isEmpty()){
            cout << "Liste bos!!!" << endl;
            return T();
        }
        else{
            return begin()->data;
        }
    }
    int size() { return length ; }
};

int main(){
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.print();
    Stack<int> s2;
    s2 = s;
    s2.print();
    s2.pop();
    s.print();
    s2.print();
    return 0;
}