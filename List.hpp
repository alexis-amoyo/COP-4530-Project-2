/*-----const_iterator-----*/
//add protection later
// Public constructor for const_iterator.
template <typename T>
List<T>::const_iterator::const_iterator( ){
    //T & retrieve( ) const;
    current = nullptr;
}

// Return the object stored at the current position.
// For const_iterator, this is an accessor with a
// const reference return type.
template <typename T>
const T& List<T>::const_iterator::operator*( ) const{
    return retrieve();
}
	    
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++( ){
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++( int n ){
    const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--( ){
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--( int n ){
    const_iterator old = *this;
    --(*this);
    return old;
}
		
// comparison operators
template <typename T>
bool List<T>::const_iterator::operator==( const const_iterator& rhs ) const{
    if(rhs.current == current)
        return true;
    else
        return false;
}

template <typename T>
bool List<T>::const_iterator::operator!=( const const_iterator& rhs ) const{
    if(current != rhs.current)
        return true;
    else
        return false;
}

// Protected helper in const_iterator that returns the object
// stored at the current position. Can be called by all
// three versions of operator* without any type conversions.
template <typename T>
T& List<T>::const_iterator::retrieve( ) const{
    return current->data;
}

// Protected constructor for const_iterator.
// Expects a pointer that represents the current position.
template <typename T>
List<T>::const_iterator::const_iterator( Node *p ){
    current = p;
}

/*-----Nested Iterator-----*/
// Public constructor for iterator.
// Calls the base-class constructor.
// Must be provided because the private constructor
// is written; otherwise zero-parameter constructor
// would be disabled.
template <typename T>
List<T>::iterator::iterator( ){
}

template <typename T>
T& List<T>::iterator::operator*( ){
    return const_iterator::retrieve();
}

// Return the object stored at the current position.
// For iterator, there is an accessor with a
// const reference return type and a mutator with
// a reference return type. The accessor is shown first
template <typename T>
const T& List<T>::iterator::operator*( ) const{
    return const_iterator::operator*();
}

// increment/decrement operators
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++( ){
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++( int n){
    iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--( ){
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--( int ){
    iterator old = *this;
    --(*this);
    return old;
}

// Protected constructor for iterator.
// Expects the current position.
template <typename T>
List<T>::iterator::iterator( Node *p ) : const_iterator{p}{
}

/*-----List-----*/

// constructor, desctructor, copy constructor
// default zero parameter constructor
template <typename T>
List<T>::List(){
    init();
}

// copy constructor
template <typename T> 
List<T>::List(const List<T>& rhs)
: theSize(rhs.theSize), head(nullptr), tail(nullptr){
    init();
    for(auto &n : rhs)
        pushback(n);
}

// move constructor
template <typename T>
List<T>::List(List<T>&& rhs)
: theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

// copy assignment operator
template <typename T>
List<T>& List<T>::operator=( const List<T>& rhs ){
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
}

// move assignment operator
template <typename T>
List<T>& List<T>::operator=( List<T>&& rhs ){
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);

    return *this;
}

template <typename T>
List<T>::~List( ){
    clear();
    delete head;
    delete tail;
}

       
// num elements with value of val
template <typename T>
List<T>::List(int num, const T& val){
    init();
    for(int i = 0; i < num; i++){
        push_back(val);
    }
}

// constructs with elements [start, end)
template <typename T>
List<T>::List(const_iterator start, const_iterator end){
    init();
    while(start != end){
        push_back(*start);
        start++;
    }
}

// constructs with a copy of each of the elements in the initalizer_list
template <typename T>
List<T>::List(std::initializer_list<T> iList){
    init();
    for(auto &n : iList){
        push_back(n);
    }
}

// sets list to the elements of the initializer_list
template <typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList){
    List<T> list;
    for(auto &n : iList){
        list.push_back(n);
    }
    std::swap(*this, list);
    return *this;
}
	
// Accessor functions
template <typename T>
int List<T>::size() const{
    return theSize;
}       // number of elements

template <typename T>
bool List<T>::empty() const{
    if(theSize == 0){
        return true;
    }
    else{
        return false;
    }
}     // check if list is empty

template <typename T>
void List<T>::clear(){
    while(!empty()){
        pop_front();
    }
}           // delete all elements
     
// front, back, push_front, push_back, pop_front, and pop_back
// are the basic double-ended queue operations.
template <typename T>
T& List<T>::front(){
    return *begin();
}             // reference to the first element

template <typename T>
const T& List<T>::front( ) const{
    return *begin();
}

template <typename T>
T& List<T>::back(){
    return *--end();
}              // reference to the last element

template <typename T>
const T& List<T>::back( ) const{
    return *--end();
}

template <typename T>
void List<T>::push_front(const T& val){
    insert(begin(), val);
} // insert to the beginning

template <typename T>
void List<T>::push_front(T && val){
    insert(begin(), std::move(val));
}      // move version of insertvoid push_back(const T & val);  // insert to the end

template <typename T>
void cop4530::List<T>::push_back(const T& val){
    //std::cout << "hope\n";
    insert(end(), val);
}       // move version of insert

template <typename T>
void cop4530::List<T>::push_back(T && val){
    insert(end(), std::move(val));
}       // move version of insert


template <typename T>
void List<T>::pop_back(){
    erase(--end());
}                // delete last element

template <typename T>
void List<T>::pop_front(){
    erase(begin());
}               // delete first element

template <typename T>
void List<T>::remove(const T& val){ //check!!!
    iterator itr = begin();
    while(itr != end())
    {
        if(*itr == val)
            itr = erase(itr);
        else
            itr++;
    }
}      // remove all elements with value = val

template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){
    for(iterator itr = begin(); itr != end();){
        if(pred(*itr)){
            //std::cout << *itr << "\n";
            itr = erase(itr);
        }
        else{
            ++itr;
        }
    }
}// remove all elements for which Predicate pred
//  returns true. pred can take in a function object

// print out all elements. ofc is deliminitor
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const{
    for(List<T>::const_iterator itr = begin(); itr != end(); itr++){
        os << itr.current->data << ofc;
    }
}

// Return iterator representing beginning of list.
// Mutator version is first, then accessor version.
template <typename T>
typename List<T>::iterator List<T>::begin(){
    return iterator(head->next);
}               // iterator to first element

template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
    return const_iterator(head->next);
}

// Return iterator representing endmarker of list.
// Mutator version is first, then accessor version.
template <typename T>
typename List<T>::iterator List<T>::end(){
    return iterator(tail);
}                 // end marker iterator

template <typename T>
typename List<T>::const_iterator List<T>::end() const{
    return const_iterator(tail);
} 


template <typename T>
List<T> List<T>::slice(iterator start, iterator end){
    List<T> temp;
    iterator itr = start;
    while(itr != end){
        temp.push_back(*itr);
        ++itr;
    }
    return temp;
} // slice [start, end)


template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){
    //std::cout << "hi\n";
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{val, p->prev, p});
}  // insert val ahead of itr

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val){
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{std::move(val), p->prev, p});
}      // move version of insert

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr){
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;
}                 // erase one element

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){
    for(iterator itr = start; itr != end;){
        itr = erase(itr);
    }
    return end;
} // erase [start, end)

// reverse the order of all elements
template <typename T>
void List<T>::reverse(){
    int mid = theSize/2;
    iterator itrBegin = begin();
    iterator itrEnd = (--end());
    
    for(int i = 0; i < mid; ++i){
        std::swap(*itrBegin, *itrEnd);
        ++itrBegin;
        --itrEnd;
    }

}


template <typename T>
void List<T>::deduplicate(){ //???
    //std::cout << "swiss\n";
    /*iterator pos = begin();
    Node *p = pos.current; 
    for(iterator itr = begin(); itr != end();){
        while(pos != end()){    //seg faults
            std::cout << "cheddar\n";
            if(p->data == *itr){
                std::cout << "bleu\n";
                std::cout << p->data;
                std::cout << *itr;
                remove(*pos);
            }
            ++pos;
        }
        
    }*/

    for(iterator itr = begin(); itr != end(); ++itr){
        //std::cout << itr.current->data << "\n";
        auto pos = itr;
        while(++pos != end())
            if(*pos == *itr){
                erase(pos);
            }
    }

} // remove the duplicates of any element

template <typename T>
int List<T>::findSlice(const List<T> & rhs){ //check???
    int count = 0;
    if(rhs.theSize > theSize){
        //std::cout << "size bad \n";
        return count;
    }
    /*List<T> list;

    for(iterator itr = begin(); itr!= end(); itr++){
        if(itr.current->data == rhs){
            count++;
            list.push_back(rhs);
        }
    }
    return count;*/

    iterator itr = begin();

    for(int i = 0; i < theSize - rhs.size() + 1; i++){
        //std::cout << "ramen \n";
        const_iterator itr_itr = itr;
        const_iterator itrRhs = rhs.begin();

        for(int j = i; j < rhs.theSize; j++){
            if(*itr_itr != *itrRhs){
			    //std::cout << "pho \n";
                break;
            }
		    itr_itr++;
		    itrRhs++;
            //std::cout << "miso \n";
        }
        if(itrRhs == rhs.end()){
		    ++count;
            //std::cout << "tom yum \n";
        }
	    itr++;
        //std::cout << "curry \n";
    }
    //std::cout << "katsu \n";
    //std::cout << count << "\n";
    return count;
} // count the occurrence of a slice in the list

/*
		//if *itr2 != *itrRhs
			break;
		itr2++;
		itrRhs++;
	}
	if(itrRhs == rhs.end())
		counter++;
	itr++;
}
return counter;*/

template <typename T>
void List<T>::init( ){
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}


// overloading comparison operators
template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs){
    if(lhs.size() != rhs.size()){  //finish
        return false;
    }
    typename List<T>::const_iterator itrL = lhs.begin();
    typename List<T>::const_iterator itrR = rhs.begin();
    for(int i = 0; i < lhs.size(); i++){
        if(*itrL != *itrR){
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs){
    if(lhs.size() != rhs.size()){  //finish
        return true;
    }
    typename List<T>::const_iterator itrL = lhs.begin();
    typename List<T>::const_iterator itrR = rhs.begin();
    for(int i = 0; i < lhs.size(); i++){
        if(*itrL != *itrR){
            return true;
        }
    }
    return false;
}


template <typename T>
std::ostream& operator<<(std::ostream &os, const List<T> &l){
    l.print(os);
    return os;
}