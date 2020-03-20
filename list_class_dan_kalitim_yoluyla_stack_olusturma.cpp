#include <iostream>
using namespace std;

template<typename T>
class Node{
public:
    T data;
    Node<T>* next;
    Node(T data = T()) : data(data) , next(NULL){}
};

template<typename T>
class List{
    Node<T> * root;
    Node<T> * tail;
    int _size;
    void clear(){
        if (isEmpty()){}
        else{
            while(size()!=0){
                pop_front();
            }
        }
    }
    Node<T>* findPrev(Node<T>* search){
        Node<T> *temp = root;
        while(temp->next != search && temp != NULL){
            temp = temp->next;
        }
        return temp;
    }
    Node<T>* find(T data){
        Node<T> *temp = root;
        while(temp->data != data && temp != NULL){
            temp = temp->next;
        }
        return temp;
    }
public:
    List() : root(NULL),tail(NULL),_size(0){}
    ~List(){
        clear();
    }
    List(Node<T>* first,Node<T>* last) : List(){
        insert(begin(),first,last);
    }
    List(List& rClass): List(rClass.begin(),rClass.end()){ }
    void operator = (List& rClass){
        root = NULL; tail=root; _size=0;
        insert(begin(),rClass.begin(),rClass.end());
    }
    Node<T>* begin() const{return root;}
    Node<T>* end() const{return tail;}
    virtual bool isEmpty() const{return root == NULL;}
    virtual int size() const{return _size;}
    virtual void print() const{
        if (isEmpty()) {cout << "Listede yazdirilabilecek eleman yok!!!" << endl;return;}
        Node <T>* temp = root;
        while(temp != NULL){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void push_back(T val){
        if (isEmpty()){
            root = new Node<T>(val);
            tail = root;
        }
        else{
            Node<T>* newData = new Node<T>(val);
            tail->next = newData;
            tail = newData;
        }
        _size++;
    }
    void push_front(T val){
        if (isEmpty()){ push_back(val);}
        else
        {
            Node<T>* newData = new Node<T>(val);
            newData->next = root;
            if (size()==1)tail = root;
            root = newData;
            _size++;
        }
    }
    T front() const{
        if (size() == 0) throw invalid_argument("Listede eleman yok!!!");
        else {return root->data;}
    }
    T back() const{
        if (size() == 0) throw invalid_argument("Listede eleman yok!!!");
        else return tail->data;
    }
    void pop_front(){
        if (size() == 0) throw invalid_argument("Silinebilecek bir eleman yok!!!");
        else{
            Node<T>* temp = root;
            root = root->next;
            delete [] temp;
        }
        _size--;
    }
    void pop_back(){
        if (size() == 0) throw invalid_argument("Silinebilecek bir eleman yok!!!");
        else if (size() == 1) pop_front();
        else{
            Node<T>* temp = findPrev(tail);
            tail = temp;
            temp = temp->next;
            delete [] temp;
            tail->next = NULL;
        }
        _size--;
    }
    void insert(Node<T> * pos,Node<T>* first,Node<T> *last){
        insert(pos,first->data);
        int val = first->data;
        while(first != last){
            first = first->next;
            pos = find(val);
            if (pos->next == NULL) {push_back(first->data);}
            else{
                insert(pos->next,first->data);
            }
        }
    }
    void insert(Node<T>* pos,T val){
        if (pos == begin()) push_front(val);
        else if (pos == end()) push_back(val);
        else{
            insert(pos->data,val);
        }
    }
    void insert(T ref,T val){
        if (size() == 0) push_back(val);
        else if(ref == root->data) push_front(val);
        else{
            Node<T> * temp = root;
            while(temp->next->data != ref && temp->next != NULL){
                temp = temp->next;
            }
            if (temp->next == NULL){
                throw invalid_argument("Hata : Referans listede bulunmuyor!");
            }
            else {
                Node<T> * newData = new Node<T>(val);
                newData->next = temp->next;
                temp->next = newData;
            }
        }
        _size++;
    }
    void insert(Node<T>* pos,int n,T val){
        insert(pos,val);
        for (int i=1; i<n; i++) insert(val,val);
    }
    void insert(T ref,int n,T val){
        insert(ref,val);
        for(int i=1; i<n; i++ ) insert(val,val);
    }
    void erase(T val){
        if (size() == 0) throw invalid_argument("Listede silinebilecek bir eleman yok");
        Node<T> *temp = root;
        while(temp->next != NULL){
            if(temp->next->data == val){
                Node<T>* remove = temp->next;
                temp->next = temp->next->next;
                delete[](remove);
                _size--;
            }
            else temp = temp->next;
        }
        if (root->data == val){
            pop_front();
            _size--;
        }
    }
    void erase(Node<T>* pos){
        if (size() == 0) throw invalid_argument("Listede silinebilecek bir eleman yok");
        if (pos == begin()) pop_front();
        else if (pos == end()) pop_back();
        else{
            Node<T>* temp = findPrev(pos);
            temp->next = temp->next->next;
            delete[](pos);
            _size--;
        }
    }
};
template <typename T>
class Stack:private List<T>{
public:
    Stack() : List<T>(){}
    Stack(Stack& r_stack) : List<T>(r_stack){}
    void operator = (Stack& r_stack){
        List<T>::insert(this->begin(),r_stack.begin(),r_stack.end());
    }
    bool isEmpty() const{
        return List<T>::isEmpty();
    }
    void push(T data){
        List<T>::push_front(data);
    }
    void pop(){
        List<T>::pop_front();
    }
    T top(){
        return List<T>::front();
    }
    int size(){
        return List<T>::size();
    }
    void print(){List<T>::print();}
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