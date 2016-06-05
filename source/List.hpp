#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP

#include <cstddef>

//List.BUW_LIST_HPP

template <typename T>
class List;

template <typename T>
struct ListNode{

	ListNode() :
	m_value(),
	m_prev(nullptr), 
	m_next(nullptr) {}

	ListNode(T const& v, ListNode* prev, ListNode* next): 
	m_value(v), 
	m_prev(prev), 
	m_next(next)
	{}

	T m_value;
	ListNode* m_prev;
	ListNode* m_next;	

};

template <typename T>
struct ListIterator{

	typedef ListIterator<T> Self;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	friend class List<T>; //friend darf auf Member zugreifen 
	
	ListIterator() : m_node(nullptr){} 
	ListIterator(ListNode<T>* n) : m_node(n){} 

	reference operator*() const {
		
		return m_node -> m_value;
	} 

	pointer operator->() const {
		
		return &(m_node ->m_value); //gibt die Afresse von m_value zurueck
	}

	Self& operator++() {

		if(m_node){
		m_node = m_node -> m_next;
		}

		return *this;

	} 

	Self operator++(int) {

		ListIterator tmp(*this); //gibt aktuellen Wert zurueck vor erhoehen
		if(m_node){
		m_node = m_node -> m_next;
		}

		return tmp;
	}

	bool operator==(const Self& x) const {

		return m_node == x.m_node;
	}

	bool operator!=(const Self& x) const {

		return m_node != x.m_node;

	} 

	Self next () const{
		if(m_node)
			return ListIterator(m_node -> m_next);
		else
			return ListIterator(nullptr);
	}

	Self prev() const{
		if(m_node)
			return ListIterator(m_node -> m_prev);
		else
			return ListIterator(nullptr);
	}

 private:
 	//The Node the iterator is pointing to
	ListNode<T>* m_node = nullptr;
};

template <typename T>
struct ListConstIterator{

	friend class List<T>;

 public:
	ListNode<T>* m_node = nullptr;

};

template <typename T>
class List{

 public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef ListIterator<T> iterator;
	typedef ListConstIterator<T> const_iterator;

	friend class ListIterator<T>;
	friend class ListConstIterator<T>;

	List(): //Default Constructor
	m_size{0},
	m_first{nullptr},
	m_last{nullptr} {} 

	List(List<T> const& copy): 
	m_size{0},
	m_first{nullptr},
	m_last{nullptr}{

		for(auto i = copy.begin(); i != copy.end(); i++){

			push_back(*i);
		}
	}

	List(List&& mvlst):
	m_first{mvlst.m_first},m_last{mvlst.m_last},m_size{mvlst.m_size}{

		mvlst.m_first = nullptr;
		mvlst.m_last = nullptr;
		mvlst.m_size = 0;
	}

	~List(){
		clear();
	}

	bool empty() const{

		return m_size == 0;
	}

	std::size_t size() const{
		return m_size;
	}

	T const& front() const{
		return m_first->m_value; //m_first beinhaltet Adresse, Zeiger auf Wert (value) 
	}

	T& front(){       			 //Ruckgabe bei Reference aber kann verandert werden
		return m_first->m_value; 
	}

	T const& back() const{
		return m_last->m_value;
	}

	T& back(){
		return m_last->m_value;
	}

	void insert(T const& a, iterator const& p){

		iterator i = begin();
		while(i != p) i++;

		T temp = *i;
		*i = a;
		i++;

		while(i!=end()){

			T temp2 = *i;
			*i = temp;
			temp = temp2;
			i++;

		}

		push_back(temp);
	}

	void reverse(){

		List<T> rev{*this}; //copy der liste
		clear(); //macht ganze Liste leer 
		for(iterator i = rev.begin(); i!=rev.end(); ++i){
			push_front(*i);
		}
	}

	void push_front(T const& p){

		if(m_size == 0){
			m_first = new ListNode<T>{p, nullptr, nullptr}; //ListeNode des Types T, gibt Pointer auf ListNode Element zurück  
			m_last = m_first;
		}

		else if(m_size >= 1){
			m_first = new ListNode<T>{p, nullptr, m_first};
			m_first -> m_next -> m_prev = m_first;
		}

		++m_size;

	}

	void push_back(T const& a){

		if(m_size == 0){
			m_last = new ListNode<T>{a, nullptr, nullptr};
			m_first = m_last;
		}

		else if(m_size >= 1){
			m_last = new ListNode<T>{a, m_last, nullptr};
			m_last -> m_prev -> m_next = m_last;
		}

		++m_size;

	}

	void pop_front(){

		if(m_size == 1){
			assert(m_first != nullptr);
			delete m_first;
			m_first = nullptr;
			m_size = 0;

		}

		else if(m_size >= 1){
			assert(m_first != nullptr);
			delete m_first;
			m_first = m_first-> m_next;
			-- m_size;

		}
	}

	void pop_back(){

		if(m_size == 1){
			assert(m_last != nullptr);
			delete m_last;
			m_last = nullptr;
			m_size = 0;
		}

		else if(m_size >= 1){
			assert(m_last != nullptr);
			delete m_last;
			m_last = m_last-> m_prev;
			--m_size;
		}
	}

	void clear(){

		while(m_size > 0){
			pop_front();
		}

	}

	iterator begin() const{

		iterator begi{m_first};
		return begi; 
	}

	iterator end() const{

		return ListIterator<T>{};
	}

 private:
	std::size_t m_size = 0;
	ListNode<T>* m_first = nullptr;
	ListNode<T>* m_last = nullptr;
};

template<typename T>
bool operator == (List<T> const& xs, List<T> const& ys){
	
	if(xs.size() != ys.size()){ //ueberprueft ob gleich groß
		return false;
	}

	else{

		ListIterator<T> x = xs.begin(); 
		ListIterator<T> y = ys.begin();

		while(x != xs.end() and y!=ys.end()){

			if(*x != *y){
				return false;
			}

			x++;
			y++;
		}

	return true;
	}
}

template<typename T>
bool operator != (List<T> const& xs, List<T> const& ys){

	return !(xs == ys);
}

#endif 
//#define BUW_LIST_HPP