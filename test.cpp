// Name: Megan Kim
// rec13: Doubly linked list implementation

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& myList) {
        const List::Node* currPtr = myList.header->next;
        while (currPtr != myList.trailer) {
            os << currPtr->data << ' ';
            currPtr = currPtr->next;
        }
        return os;
    }

    // Nested Node class: only can be accessed by List
    class Node {
    public:
        Node(int data, Node* prior = nullptr, Node* next = nullptr)
            : data(data), prior(prior), next(next) {}

        int data;
        Node* prior;
        Node* next;
    };

public:
    class iterator {
        friend List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return (lhs.curr == rhs.curr);
        }
    public:
        iterator(Node* curr) : curr(curr) {}
        int operator* () {
            return curr->data;
        }
        iterator& operator++ () {
            curr = curr->next;
            return *this;
        }
        iterator& operator-- () {
            curr = curr->prior;
            return *this;
        }
    private:
        Node* curr;
    };
    class const_iterator {
        friend List;
        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
            return (lhs.curr == rhs.curr);
        }
    public:
        const_iterator(Node* curr) : curr(curr) {}
        int operator* () {
            return curr->data;
        }
        const_iterator& operator++ () {
            curr = curr->next;
            return *this;
        }
        const_iterator& operator-- () {
            curr = curr->prior;
            return *this;
        }
    private:
        const Node* curr;
    };
    iterator begin() {
        iterator iter(header->next);
        return iter;
    }
    iterator end() {
        iterator iter(trailer);
        return iter;
    }
    const_iterator begin() const {
        const_iterator iter(header->next);
        return iter;
    }
    const_iterator end() const {
        const_iterator iter(trailer);
        return iter;
    }

    // LIST CLASS ====================
    // Default constructor
    List() : header(new Node(0)), trailer(new Node(0)), listSize(0) {
        header->next = trailer;
        trailer->prior = header;
    }

    // List methods
    void push_back(int data) {
        Node* lastNode = trailer->prior;
        lastNode->next = new Node(data, trailer->prior, trailer);
        trailer->prior = lastNode->next;
        listSize++;
    }

    int pop_back() {
        // Checks if List is empty first
        if (trailer->prior == header) {
            cerr << "List is empty!" << endl;
            return 0;
        }
        else {
            int data = trailer->prior->data; // Storing data
            Node* newLast = trailer->prior->prior;
            newLast->next = trailer;
            delete trailer->prior;
            trailer->prior = newLast;
            // Updating size
            listSize--;
            // Returning removed data
            return data;
        }
    }

    void push_front(int data) {
        Node* frontNode = header->next;
        header->next = new Node(data, header, frontNode);
        frontNode->prior = header->next;
        listSize++;
    }

    int pop_front() {
        // Checks if List is empty first
        if (trailer->prior == header) {
            cerr << "List is empty!" << endl;
            return 0;
        }
        else {
            int data = header->next->data;
            Node* newFront = header->next->next;
            newFront->prior = header;
            delete header->next;
            header->next = newFront;
            // Updating size
            listSize--;
            // Returning removed data
            return data;
        }
    }

    void clear() {
        while (0 < listSize) {
            pop_back();
        }
    }

    // Index operators
    int& operator[](size_t ind) { // Modifiable
        Node* curr = header->next;
        while (0 < ind) {
            curr = curr->next;
            ind--;
        }
        return curr->data;
    }
    int operator[](size_t ind) const { // For const
        const Node* curr = header->next;
        while (0 < ind) {
            curr = curr->next;
            ind--;
        }
        return curr->data;
    }
    iterator insert(const iterator& iter, int data) {
        Node* old_prior = iter.curr->prior;
        old_prior->next = new Node(data, old_prior, iter.curr);
        iter.curr->prior = old_prior->next;
        iterator new_iter(old_prior->next);
        ++listSize;
        return new_iter;
    }
    iterator erase(const iterator& iter) {
        iter.curr->prior->next = iter.curr->next;
        iter.curr->next->prior = iter.curr->prior;
        iterator new_iter(iter.curr->next);
        delete iter.curr;
        --listSize;
        return new_iter;
    }

    List& operator=(const List& rhs) {
        if (this != &rhs) {
            clear();
            Node* rhs_curr = rhs.header->next;
            while (rhs_curr != rhs.trailer) {
                push_back(rhs_curr->data);
                rhs_curr = rhs_curr->next;
            }
        }
        return *this;
    }
    // Getters
    int& front() { // Can modify front value
        return header->next->data;
    }
    int front() const { // Returning const reference
        return header->next->data;
    }

    int& back() { // Can modify back value
        return trailer->prior->data;
    }
    int back() const { // Returning const reference
        return trailer->prior->data;
    }

    size_t size() const { return listSize; }
private:
    Node* header;
    Node* trailer;
    size_t listSize;
};

// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
        << ", front: " << myList.front()
        << ", back(): " << myList.back()
        << ", list: " << myList << endl;
}

//The following should not compile. Check that it does not.
//void changeFrontAndBackConst(const List& theList){
//    theList.front() = 17;
//    theList.back() = 42;
//}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

bool operator!= (const List::iterator& lhs, const List::iterator& rhs) {
    return !(lhs == rhs);
}
bool operator!= (const List::const_iterator& lhs, const List::const_iterator& rhs) {
    return !(lhs == rhs);
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i * i << ");\n";
        myList.push_back(i * i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i * i << ");\n";
        myList.push_front(i * i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i * i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
        << "the data in the third item in the list\n"
        << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // task 5
    cout << "\n------task five------\n";
    cout << "fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
    printListInfo(myList);
    cout << "now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "and again using the iterator type directly:\n";
    // note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = mylist.begin(); iter != mylist.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "wow!!! (i thought it was cool.)\n";

    // task 6
    cout << "\n------task six------\n";
    cout << "filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
    printListInfo(myList);
    cout << "filling an empty list with insert at begin(): "
        << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i * i);
    printListInfo(myList);
    // ***need test for insert other than begin/end***
    cout << "===================\n";

    // task 7
    cout << "\n------task seven------\n";
    cout << "filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
    cout << "erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***need test for erase other than begin/end***
    cout << "===================\n";

    // task 8
    
}
