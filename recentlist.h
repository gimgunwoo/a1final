template <class T>
class RecentList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr){
			data_ = data;
			next_ = next;
			prev_ = prev; 
		}
	};
	Node* first_;
	Node* last_;
public:
	class const_iterator{
		friend class RecentList;
		Node* curr_;
		const RecentList* myList_;
	protected:
		const_iterator(Node* curr, const RecentList* list){
			curr_ = curr;
			myList_ = list;
		}
	public:
		bool operator==(const_iterator right){
			return (curr_ == right.curr_);
		}

		bool operator!=(const_iterator right){
			return (curr_ != right.curr_);
		}

		const_iterator(){}

		const_iterator operator++(){
			//prefix operator returns iterator to current node
			curr_ = curr_->next_;
			return *this;
		}

		const_iterator operator--(){
			//prefix operator returns iterator to current node
			curr_ = curr_->prev_;
			return *this;
		}

		const_iterator operator++(int){
			//postfix operator returns iterator to node before the increment
			const_iterator temp = *this;
			curr_ = curr_->next_;
			return temp;
		}

		const_iterator operator--(int){
			//postfix operator returns iterator to node before the decrement.
			const_iterator temp = *this;
			curr_ = curr_->prev_;
			return temp;
		}

		const T& operator*() const{
			//returns a const reference to data in the node referred to by the iterator.
			T rc = T{};
			if (curr_){
				return curr_->data_;
			}
			return rc;
		}
	};
	class iterator : public const_iterator{
		friend class RecentList;
		iterator(Node* curr, const RecentList* list) : const_iterator(curr, list){
		}

	public:
		iterator(){}

		iterator operator++(){
			//prefix operator returns iterator to current node
			const_iterator::curr_ = const_iterator::curr_->next_;
			return *this;
		}

		iterator operator--(){
			//prefix operator returns iterator to current node
			const_iterator::curr_ = const_iterator::curr_->prev_;
			return *this;
		}

		iterator operator++(int){
			//postfix operator returns iterator to node before the increment
			iterator temp = *this;
			const_iterator::curr_ = const_iterator::curr_->next_;
			return temp;
		}

		iterator operator--(int){
			//postfix operator returns iterator to node before the decrement.
			iterator temp = *this;
			const_iterator::curr_ = const_iterator::curr_->prev_;
			return temp;
		}

		const T& operator*() const{
			//returns a const reference to data in the node referred to by the iterator.
			if (const_iterator::curr_){
				return const_iterator::curr_->data_;
			}
		}

		T& operator*(){
			//returns a reference to data in the node referred to by the iterator.
			if (const_iterator::curr_){
				return const_iterator::curr_->data_;
			}
		}
	};

	RecentList(){
		//create empty RecentList
		init();
	}

	void init(){
		//initializes RecentList
		first_ = new Node();
		last_ = new Node();
		first_->next_ = last_;
		last_->prev_ = first_;
	}

	iterator begin(){
		//returns the appropriate iterator to first node in list
		iterator itr(first_, this);
		return ++itr;
		//return iterator(first_, this);
	}

	const_iterator begin() const{
		//returns the appropriate iterator to first node in list
		const_iterator citr(first_, this);
		return ++citr;
		//return const_iterator(first_, this);
	}

	iterator end(){
		//returns the appropriate iterator to the node after the last node in the list
		return iterator(last_, this);
	}

	const_iterator end() const{
		//returns the appropriate iterator to the node after the last node in the list
		return const_iterator(last_, this);
	}
	
	iterator insert(iterator itr, const T& data){
		//creates a new node at the end of the linked list
		Node* curr = itr.curr_;
		curr->prev_->next_ = new Node(data, curr, curr->prev_);
		curr->prev_ = curr->prev_->next_;
		return iterator(curr->prev_, this);
	}

	void insert(const T& data){
		//creates new node holding data at the front of the linked list
		Node* newData = new Node(data, first_->next_, first_);
		first_->next_->prev_ = newData;
		first_->next_ = newData;
	}

	void remove(const T& data){
		//This function removes a node that matches data
		iterator searching = search(data);
		if (searching != end()){
			Node* rmv = searching.curr_;
			rmv->prev_->next_ = rmv->next_;
			rmv->next_->prev_ = rmv->prev_;
			delete rmv;
		}
	}

	void remove(Node* rmv){
		//accepts a node to remove
		Node* pr = rmv->prev_;
		Node* nx = rmv->next_;
		pr->next_ = nx;
		nx->prev_ = pr;
		delete rmv;
	}
	/*
	const_iterator search(const T& key){
		//search accepts as arguments a key of the unknown data type T.
		//The function finds and returns the address of the node containing a matching key.
		//It will also adjust the linked list such that the node is moved to the front of the linked list. 
		//function returns an iterator to the node if found, end() if it is not.
		Node* result = first_->next_;
		do{
			if (result->data_ == key){
				result->next_->prev_ = result->prev_;
				result->prev_->next_ = result->next_;
				result->next_ = first_->next_;
				first_->next_ = result;
				result->next_->prev_ = result;
				first_->next_->prev_ = first_;

				return const_iterator(result , this);
			}
			result = result->next_;
		} while (result->next_ != nullptr);

		return end();
	}*/
	
	iterator search(const T& key){
		//search accepts as arguments a key of the unknown data type T.
		//The function finds and returns the address of the node containing a matching key.
		//It will also adjust the linked list such that the node is moved to the front of the linked list. 
		//function returns an iterator to the node if found, end() if it is not.
		Node* result = first_->next_;
		do{
			if (result->data_ == key){
				result->next_->prev_ = result->prev_;
				result->prev_->next_ = result->next_;
				result->next_ = first_->next_;
				first_->next_ = result;
				result->next_->prev_ = result;
				first_->next_->prev_ = first_;
			
				return iterator(result , this);
			}
			result = result->next_;
		} while (result->next_ != nullptr);
		
		return end();
	}

	~RecentList(){
		//destructor
		if (!isEmpty()){
			while (!isEmpty()){
				remove(first_->next_);
			}
		}
		delete first_;
		delete last_;
	}

	RecentList(const RecentList& rhs){
		//copy constructor
		init();
		*this = rhs;
	}

	RecentList(RecentList&& rhs){
		//move constructor
		first_ = rhs.first_;
		last_ = rhs.last_;
		rhs.first_ = nullptr;
		rhs.last_ = nullptr;
	}

	RecentList& operator=(const RecentList& rhs){
		//assignment operator.
		if (this == &rhs)
			return *this;

		while (!isEmpty()){
			remove(first_->next_);
		}

		const_iterator cst_itr = rhs.begin();

		while (cst_itr != rhs.end()){
			insert(end(), *cst_itr++);
		}

		return *this;
	}

	RecentList& operator=(RecentList&& rhs){
		//move operator
		if (this != rhs){
			while (!isEmpty()){
				remove(first_->next_);
			}
		}

		first_ = rhs.first_;
		last_ = rhs.last_;
		rhs.first_ = nullptr;
		rhs.last_ = nullptr;
	}

	bool isEmpty() const{
		//checks a linked list if the next node of the first node is the last one
		//returns true if the first node is pointing to last one
		return (first_->next_ == last_);
	}
};