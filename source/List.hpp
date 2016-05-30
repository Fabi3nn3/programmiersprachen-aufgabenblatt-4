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

	friend class List<T>; //friend darf auf Member zugreifen 
	//not implemented yet

 private:
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

		for(int i = 0; i <= m_size; ++i){
			
		}

	}

 private:
	std::size_t m_size = 0;
	ListNode<T>* m_first = nullptr;
	ListNode<T>* m_last = nullptr;
};

#endif 
//#define BUW_LIST_HPP