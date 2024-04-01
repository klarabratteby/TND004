#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

/*
 *  Default constructor :create an empty Set
 */
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/*
 *  Default constructor :create an empty Set, O(1)
 */
Set::Set() : counter{0} {
    head= new Node;
    tail= new Node;
    
    head->next=tail;
    tail->prev = head;
}

/*
 *  Conversion constructor: convert val into a singleton {val}, O(1)
 */
Set::Set(int val) : Set{} {  // create an empty list
    insert_node(tail,val);
}

/*
 * Constructor to create a Set from a sorted vector of ints
 * Create a Set with all ints in sorted vector list_of_values, O(n)
 */
Set::Set(const std::vector<int>& v) : Set{} {  // create an empty list
    for (size_t i=0; i < v.size(); i++) {
        insert_node(tail, v[i]);
        
    }
}
/*
 * Copy constructor: create a new Set as a copy of Set S, O(n)
 * \param S Set to copied
 * Function does not modify Set S in any way
 */
Set::Set(const Set& S) : Set{} {  // create an empty list, call by refernce
    Node* ptr1 = S.head->next;
    
    while (ptr1 != S.tail) {
        
        insert_node(tail, ptr1->value);
        ptr1 = ptr1->next;
    }

}

/*
 * Transform the Set into an empty set
 * Remove all nodes from the list, except the dummy nodes, O(n)
 */
void Set::make_empty() {
    Node* dummy = head->next;
    while (dummy != tail) {
        remove_node(dummy); // "remove" dummy from first place but move it further down the list
        dummy = head->next;
    }
    
}

/*
 * Destructor: deallocate all memory (Nodes) allocated for the list, O(n)
 */
Set::~Set() {
    make_empty(); // O(n)
    delete head;
    delete tail;
    
    // avoid memory leaks
    head = nullptr; // O(1)
    tail = nullptr; // O(1)
}

/*
 * Assignment operator: assign new contents to the *this Set, replacing its current content
 * \param S Set to be copied into Set *this
 * Call by valued is used
 */
// copy-and-swap idiom, calling for copy constructor and destructor, O(1), only points on head. Call by value.
Set& Set::operator=(Set S) {

    std::swap(head, S.head);
    std::swap(tail, S.tail);
    std::swap(counter, S.counter);
    
    return *this;
}

/*
 * Test whether val belongs to the Set
 * Return true if val belongs to the set, otherwise false
 * This function does not modify the Set in any way, O(n)
 */
bool Set::is_member(int val) const {
    Node* ptr2 = head->next;
    while (ptr2 != tail && val != ptr2->value) {
        ptr2 = ptr2->next;
    }
    
    if(ptr2 == tail) {
        return false;
    }
    else {
        return true;
        
    }
        
}

/*
 * Test whether Set *this and S represent the same set
 * Return true, if *this has same elemnts as set S
 * Return false, otherwise, O(n)
 */
bool Set::operator==(const Set& S) const {
   
    // If not similar in size -> return false
    if (counter != S.counter) {
              return false;
    }
    
    Node* ptr1 = head->next; // *this
    Node* ptr2 = S.head->next; // S
    
    while ((ptr1 != tail) && (ptr2 != S.tail)) {
        if (ptr1->value != ptr2->value){
            return false;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return true;
}
    
     
/*
* Three-way comparison operator: to test whether *this == S, *this < S, *this > S
* Return std::partial_ordering::equivalent, if *this == S
* Return std::partial_ordering::less, if *this < S
* Return std::partial_ordering::greater, if *this > S
* Return std::partial_ordering::unordered, otherwise, O(n)
*/

std::partial_ordering Set::operator<=>(const Set& S) const {
    
    // Calling on operator==
    if (*this == S) {
        return std::partial_ordering::equivalent;
    }
    
    bool subset = true;
    Node* ptr1 = head->next; // *this
    Node* ptr2 = S.head->next; // S
    
    // Check if *this is a subset of S
    while ( ptr1 != tail) {
        
        // If less = subset, ptr1 cannot be a subset of ptr2.
        if (ptr2 == S.tail || ptr1->value < ptr2->value) {
            subset = false;
            break;
        }
        else if (ptr1->value == ptr2->value) {
            ptr1= ptr1->next;
            ptr2= ptr2->next;
            
        }
        else {
            ptr2 = ptr2->next;
        }
            
    }
    
    // Check if *this is a superset of S
    bool superset= true;
    while (ptr2 != S.tail) {
        if (ptr1 == tail || ptr1->value > ptr2->value) {
            superset = false;
            break;
            
        } else if (ptr1->value == ptr2->value) {
            ptr1= ptr1->next;
            ptr2= ptr2->next;
            
        } else {
            ptr1 = ptr1->next;
        }
        
    }
    
    // Check for superset/subset
   if (subset == true) {
        return std::partial_ordering::less;
    }
    else if (superset == true) {
        return std::partial_ordering::greater;
    }
    else {
        return std::partial_ordering::unordered;
            
    }
    
}
    
        
/*
* Modify Set *this such that it becomes the union of *this with Set S
* Set *this is modified and then returned, O(n)
*/
Set& Set::operator+=(const Set& S) {
        
    Node* ptr1 = head->next;;
    Node* ptr2 = S.head->next;
        
    // Union = combining the elements of two sets
    while (ptr1 != tail && ptr2 != S.tail ) {
        if (ptr1->value < ptr2->value) {
            ptr1 = ptr1->next;
        }
        else if (ptr1->value > ptr2->value) {
            insert_node(ptr1, ptr2->value);
            ptr2 = ptr2->next;
                
        }
        else {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    while (ptr2 != S.tail) {
        // if ptr1 finished -> add the rest of the values in ptr2
        insert_node(tail,ptr2->value);
        ptr2=ptr2->next;
            
    }
    return *this;
}
    
    /*
     * Modify Set *this such that it becomes the intersection of *this with Set S
     * Set *this is modified and then returned, O(n)
     */
Set& Set::operator*=(const Set& S) {
    Node* ptr1 = head->next;
    Node* ptr2 = S.head->next;
        
    while (ptr1 != tail && ptr2 != S.tail) {
        if (ptr1->value < ptr2->value) {
            ptr1 = ptr1->next;
            remove_node(ptr1->prev); // remove if ptr2 does not exist in ptr1
        }
        else if (ptr2->value < ptr1->value) {
            ptr2 = ptr2->next;
        }
        else {
            ptr1 = ptr1->next; // if both exist -> proceed
            ptr2 = ptr2->next;
        }
    }
        
    while (ptr1 != tail) {
        ptr1 = ptr1->next;
        remove_node(ptr1->prev);
    }
        
    return *this;
}
    
/*
* Modify Set *this such that it becomes the Set difference between Set *this and Set S
* Set *this is modified and then returned, O(n)
*/
Set& Set::operator-=(const Set& S) {
    Node* ptr1 = head->next;
    Node* ptr2 = S.head->next;
        
    while (ptr1 != tail && ptr2 != S.tail) {
        if (ptr1->value > ptr2->value) {
            ptr2 = ptr2->next;
        }
        else if (ptr1->value < ptr2->value) {
            ptr1 = ptr1->next;
        }
        else {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            remove_node(ptr1->prev); // remove if similar value
        }
    }
        
    return *this;
}
    

    /* ******************************************** *
     * Private Member Functions -- Implementation   *
     * ******************************************** */
    
    /*
     * Insert a new Node storing val after the Node pointed by p
     * \param p pointer to a Node
     * \param val value to be inserted  after position p, O(1)
     */
    void Set::insert_node(Node* p, int val) {
        Node* newNode = new Node(val, p, p->prev);
        p->prev = p->prev->next = newNode;
        ++counter;
    }
    
    /*
     * Remove the Node pointed by p
     * \param p pointer to a Node, O(1)
     */
    void Set::remove_node(Node* p) {
        p->next->prev = p->prev;
        p->prev->next = p->next;

        delete p;
        counter--;
        
    }
    
    /*
     * Write Set *this to stream os
     */
    void Set::write_to_stream(std::ostream& os) const {
        if (is_empty()) {
            os << "Set is empty!";
        } else {
            Set::Node* ptr{head->next};
            
            os << "{ ";
            while (ptr != tail) {
                os << ptr->value << " ";
                ptr = ptr->next;
            }
            os << "}";
        }
    }
    

