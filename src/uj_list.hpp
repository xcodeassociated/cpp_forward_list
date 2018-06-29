//
//  uj_list.hpp
//  
//
//  Created by Janusz Majchrzak on 08/06/16.
//  Copyright © 2016 Janusz Majchrzak. All rights reserved.
//

#ifndef list_h
#define list_h

#include <memory>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <typeinfo>
#include <type_traits>
#include <limits>

namespace uj{
    
    /**
     * \brief Forward List
     */
    template<typename T>
    class list {
        
        template <typename TT> struct node;
        
    public:
        
        template<typename TT> class ForwardIterator;
        template<typename TT> class ConstForwardIterator;
        
        typedef T value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef ForwardIterator<T> iterator;
        typedef ConstForwardIterator<T> const_iterator;
        
    public:
        
        /**
         * \brief Forward Iterator
         * \details uj::list::iterator
         */
        template <class UnqualifiedType = typename std::remove_cv<T>::type>
        class ForwardIterator : public std::iterator<std::forward_iterator_tag, UnqualifiedType, std::ptrdiff_t, T*, T&> {
            friend class list;
            node <UnqualifiedType>* itr = nullptr; /**< \brief Pointer to node before actual element */
            
            /** \brief Returns true if there is a next node */
            bool hasNext() {
                return itr->next != nullptr;
            }
            
            /** \brief If possiblle advances iterator by one */
            void increment() noexcept {
                if(this->itr->next != nullptr)
                    this->itr = this->itr->next;
            }
            
            /** \brief Returns pointer to node before the element */
            node<UnqualifiedType>* get() {
                return this->itr;
            }
            
            /** \brief Constructs iterator with nd as internal pointer */
            ForwardIterator(node<UnqualifiedType>* nd) noexcept : itr(nd) {
                ;
            }
            
        public:
            
            /** \brief Constructs invalid default iterator */
            ForwardIterator() noexcept : itr(nullptr) {
                ;
            }
            
            /** \brief Constructs iterator as copy of other */
            ForwardIterator(const ForwardIterator& other) noexcept : itr(other.itr) {
                ;
            }
            
            /** \brief Destructs iterator */
            ~ForwardIterator() {
                ;
            };
            
            /** \brief Swaps internal pointer of iterator with other */
            void swap(ForwardIterator& other) noexcept {
                using std::swap;
                swap(itr, other.iter);
            }
            
            /** \brief Assigns internal pointer of it to this */
            ForwardIterator& operator=(const ForwardIterator& it) {
                this->itr = it.itr;
                
                return *this;
            }
            
            /** \brief Advances this iterator by number */
            ForwardIterator& operator+(int number) {
                for(int i = 0; i < number; i++) {
                    this->increment();
                }
                
                return *this;
            }
            
            /** \brief Advances iterator by one */
            ForwardIterator& operator++() noexcept {
                if(this->itr->next != nullptr)
                    this->increment();
                    
                    return *this;
            }
            
            /** \brief Advances iterator by one while returning iterator with previous state */
            ForwardIterator operator++(int) noexcept {
                auto ret = *this;
                
                if(this->itr->next != nullptr)
                    this->increment();
                    
                    return ret;
            }
            
            /** \brief Returns true if internal pointers compare equal */
            template<class LLType>
            bool operator==(const ForwardIterator<LLType>& rhs) const noexcept {
                return itr == rhs.itr;
            }
            
            /** \brief Returns false if internal pointers compare equal */
            template<class LLType>
            bool operator!=(const ForwardIterator<LLType>& rhs) const noexcept {
                return itr != rhs.itr;
            }
            
            /** \brief Returns reference to iterator's element */
            typename ForwardIterator::reference operator*() noexcept {
                return itr->next->data;
            }
            
            /** \brief Returns pointer to iterator's element */
            typename ForwardIterator::pointer operator->() noexcept {
                return &(itr->next->data);
            }
        };
        
        /**
         * \brief Const Forward Iterator
         * \details uj::list::const_iterator
         */
        template <class UnqualifiedType = typename std::remove_cv<T>::type>
        class ConstForwardIterator : public std::iterator<std::forward_iterator_tag, UnqualifiedType, std::ptrdiff_t, const T*, const T&> {
            friend class list;
            node <UnqualifiedType>* itr = nullptr; /**< \brief Pointer to node before actual element */
            
            /** \brief Returns true if there is a next node */
            bool hasNext(){
                return itr->next != nullptr;
            }
            
            /** \brief If possiblle advances iterator by one */
            void increment() noexcept {
                if(this->itr->next != nullptr)
                    this->itr = this->itr->next;
            }
            
            /** \brief Returns pointer to node before the element */
            node<UnqualifiedType>* get() {
                return this->itr;
            }
            
            /** \brief Constructs iterator with nd as internal pointer */
            ConstForwardIterator(node<UnqualifiedType>* nd) : itr(nd) {
                ;
            }
            
        public:
            
            /** \brief Constructs invalid default iterator */
            ConstForwardIterator() : itr(nullptr) {
                ;
            }
            
            /** \brief Converts other to const iterator */
            ConstForwardIterator(const ForwardIterator<UnqualifiedType>& other) : itr(other.itr) {
                ;
            }
            
            /** \brief Constructs iterator as copy of other */
            ConstForwardIterator(const ConstForwardIterator& other) : itr(other.itr) {
                ;
            }
            
            /** \brief Destructs iterator */
            ~ConstForwardIterator() {
                ;
            };
            
            /** \brief Swaps internal pointer of iterator with other */
            void swap(ConstForwardIterator& LL) noexcept {
                using std::swap;
                swap(itr, LL.iter);
            }
            
            /** \brief Assigns internal pointer of it to this */
            ConstForwardIterator& operator=(const ConstForwardIterator& it) {
                this->itr = it.itr;
                
                return *this;
            }
            
            /** \brief Assigns internal pointer of it to this */
            ConstForwardIterator& operator=(const ForwardIterator<T>& it) {
                this->itr = it.itr;
                
                return *this;
            }
            
            /** \brief Advances this iterator by number */
            ConstForwardIterator& operator+(int number) {
                for(int i = 0; i < number; i++){
                    this->increment();
                }
                
                return *this;
            }
            
            /** \brief Advances iterator by one */
            ConstForwardIterator& operator++() noexcept {
                if(this->itr->next != nullptr)
                    this->increment();
                    
                    return *this;
            }
            
            /** \brief Advances iterator by one while returning iterator with previous state */
            ConstForwardIterator operator++(int) noexcept {
                auto ret = *this;
                if(this->itr->next != nullptr)
                    this->increment();
                    
                    return ret;
            }
            
            /** \brief Returns true if internal pointers compare equal */
            template<class LLType>
            bool operator==(const ConstForwardIterator<LLType>& rhs) const noexcept {
                return itr == rhs.itr;
            }
            
            /** \brief Returns false if internal pointers compare equal */
            template<class LLType>
            bool operator!=(const ConstForwardIterator<LLType>& rhs) const noexcept {
                return itr != rhs.itr;
            }
            
            /** \brief Returns reference to iterator's element */
            typename ConstForwardIterator::reference operator*() noexcept {
                return itr->next->data;
            }
            
            /** \brief Returns pointer to iterator's element */
            typename ConstForwardIterator::pointer operator->() noexcept {
                return &(itr->next->data);
            }
        };
        
    private:
        
        /**
         * \brief Used internally by uj::list
         */
        template <typename TT = T>
        struct node{
            T data; /**< Value of element in node */
            node<TT>* next = nullptr; /**< Pointer to next node */
            
            /** \brief Constructs empty node */
            node<TT>(void) {
                ;
            }
            
            /** \brief Constructs node with d */
            node<TT>(const TT& d) : data(d), next() {
                ;
            }
            
            /** \brief Consttructs node with copy of data, but without next */
            node<TT>(const node<T>& copyNode) : data(copyNode.data), next() {
                ;
            }
            
            /** \brief Destructs node */
            ~node(){
                ;
            }
        };
        
        std::size_t Size = 0; /**< Number of list's elements */
        node<T>* head = nullptr; /**< Pointer to head node with unused value*/
        node<T>* tail = nullptr; /**< Pointer to last node in list */
        
    public:
        
        /**
         * \brief Constructs an empty list
         */
        list() noexcept : Size(0), head(new node<T>()), tail(head) {
            ;
        }
        
        /**
         * \brief Constructs list from ilist in linear complexity
         * \param[in] ilist list of elements to be included in created list
         */
        list(std::initializer_list<T> ilist) noexcept : head(new node<T>()), tail(head) {
            for (auto i: ilist)
                this->push_back(i);
        }
        
        /**
         * \brief Move constructor
         * \param[in] LL list to be moved
         */
        list(list&& LL) noexcept : Size(std::move(LL.Size)), head(std::move(LL.head)), tail(std::move(LL.tail)) {
            LL.head = nullptr;
            LL.tail = nullptr;
        }
        
        /**
         * \brief Copy constructor
         * \param[in] LL list to be copied
         */
        list(const list& LL) noexcept : head(new node<T>()), tail(head){
            for (auto& e : LL)
                this->push_back(e);
        }
        
        /**
         * \brief Constructs lists with count instances of value
         * \param[in] count size of created list
         * \param[in] value instance to bo copied as list elements
         */
        explicit list(size_type count, const T& value = T()):Size(0), head(new node<T>()), tail(head){
            for(size_t i = 0; i < count; ++i)
                this->push_back(value);
            
        }
        
        /**
         * \brief Constructs lists with elements from [begin:end) range
         * \param[in] begin beginning of range
         * \param[in] end end of range
         */
        template<typename InputIterator>
        list(InputIterator begin, InputIterator end) noexcept : head(new node<T>()), tail(head) {
            while(begin != end)
                this->push_back(*(begin++));
        }
        
        /**
         * \brief Destroys list and it's elements
         */
        ~list(){
            this->clear();
        }
        
        /**
         * \brief Accesses first element in list
         */
        reference front(){
            return this->head->next->data;
        }
        
        /**
         * \brief Accesses last element in list
         */
        reference back() {
            return this->tail->data;
        }
        
        /**
         * \brief Accesses constant first element in list
         */
        const_reference front() const {
            return this->head->next->data;
        }
        
        /**
         * \brief Accesses constant last element in list
         */
        const_reference back() const {
            return this->tail->data;
        }
        
        /**
         * \brief Removes all elements from list
         * \details Removed elements are deleted and iterators and references to them are invalidated
         */
        void clear(){
            if (this->head != nullptr && this->Size > 0){
                node<T>* curr = this->head->next;
                
                while (curr && this->Size > 0){
                    this->head = curr->next;
                    delete curr;
                    
                    curr = this->head;
                    --this->Size;
                }
                this->tail = this->head;
                if (this->head == nullptr){
                    this->head = new node<T>();
                    this->tail = this->head;
                }
            }
        }
        
        /**
         * \brief Assigns count instances of value to this list.
         * \details Current elements of list are deleted in order to be replaced by value instances
         */
        void assign(size_type count, const T& value){
            this->clear();
            
            for(size_t i = 0; i < count; ++i){
                this->push_back(value);
            }
        }
        
        /**
         * \brief Assigns elements from [begin:end) range to this list
         * \details Current elements of list are deleted in order to be replaced by range elements
         * \param[in] begin beginning of range
         * \param[in] end end of range
         */
        template< class InputIterator >
        void assign(InputIterator begin, InputIterator end){
            this->clear();
            
            while(begin != end)
                this->push_back(*(begin++));
        }
        
        /**
         * \brief Assigns elements from LL to this list
         * \details Current elements of list are deleted in order to be replaced by copies of LL elements
         * \param[in] LL list to be copied
         */
        auto operator=(const list& LL) noexcept -> list<T>& {
            if (this->Size > 0)
                this->clear();
                
                for (auto& e : LL)
                    this->push_back(e);
                    
                    return *this;
        }
        
        /**
         * \brief Moves elements from _list to this list
         * \details Current elements of list are deleted in order to be replaced by LL elements
         * \param[in] _list list to be moved
         */
        auto operator=(list&& _list) noexcept -> list<T>& {
            this->head = std::move(_list.head);
            this->tail = std::move(_list.tail);
            this->Size = std::move(_list.Size);
            
            _list.head = nullptr;
            _list.tail = nullptr;
            
            _list.Size = 0;
            
            return *this;
        }
        
        /**
         * \brief Returns iterator to first element in the list
         */
        iterator begin() noexcept {
            return ForwardIterator<T>(this->head);
        }
        
        /**
         * \brief Returns iterator past the last element in the list
         */
        iterator end() noexcept {
            return ForwardIterator<T>(this->tail);
        }
        
        /**
         * \brief Returns const iterator to first element in the list
         */
        const_iterator begin() const noexcept {
            return ConstForwardIterator<T>(this->head);
        }
        
        /**
         * \brief Returns const iterator past the last element in the list
         */
        const_iterator end() const noexcept {
            return ConstForwardIterator<T>(this->tail);
        }
        
        /**
         * \brief Adds val as last element of this list
         * \param[in] val value to be added
         */
        void push_back(const_reference val) noexcept {
            node<T>* newNode = new node<T>(val);
            
            if (this->tail == this->head){
                newNode->next = tail;
                this->tail = newNode;
                this->head->next = newNode;
                
                ++this->Size;
                
                return;
            }
            
            this->tail->next = newNode;
            this->tail = this->tail->next;
            
            ++this->Size;
        }
        
        /**
         * \brief Adds ilist elements at the end of this list
         * \param[in] ilist list of elements to be added
         */
        void push_back(std::initializer_list<T> ilist) noexcept {
            for (auto i: ilist)
                this->push_back(i);
                }
        
        /**
         * \brief Adds list of elements at the end of this list
         * \param[in] first first of elements to be added
         * \param[in] t rest of elements to be added
         */
        template <typename... S>
        void push_back(const_reference first, S... t) {
            this->push_back(first);
            this->push_back(t...);
        }
        
        /**
         * \brief Adds val as first element of this list
         * \param[in] val value to be added
         */
        void push_front(T val) noexcept {
            node<T>* newNode = new node<T>(val);
            newNode->next = this->head->next;
            this->head->next = newNode;
            
            if (this->tail == this->head)
                this->tail = newNode;
            
            ++this->Size;
        }
        
        /**
         * \brief Adds ilist elements at the beginning of this list
         * \param[in] ilist list of elements to be added
         */
        void push_front(std::initializer_list<T> ilist) noexcept {
            for (auto i: ilist)
                this->push_front(i);
        }
        
        /**
         * \brief Removes last element from list and returns it's copy
         */
        auto pop_back() noexcept -> T {
            T e = this->tail->data;
            this->erase(this->begin() + ((int)this->Size-1));
            
            return e;
        }
        
        /**
         * \brief Removes first element from list and returns it's copy
         */
        auto pop_front() noexcept -> T {
            T e = this->head->next->data;
            this->erase(this->begin());
            
            return e;
        }
        
        /**
         * \brief Erases element at it
         * \returns iterator past the erased element
         */
        iterator erase(iterator it) noexcept {
            node<T>* prev_element = it.get();
            if(prev_element->next==this->tail)
                this->tail = prev_element;
            
            node<T>* del = prev_element->next;
            prev_element->next = del->next;
            
            delete del;
            
            --this->Size;
            
            return it;
        }
        
        /**
         * \brief Erases element at [begin:end) range
         * \returns iterator past the erased range
         */
        iterator erase(iterator begin,iterator end) noexcept {
            node<T>* endNode = end.get()->next;
            
            while(begin.get()->next != endNode)
                begin = this->erase(begin);
                return begin;
        }
        
        /**
         * \brief Checks if this list is empty
         * \returns true if this list is empty, false if this list is not empty
         */
        bool empty() const noexcept {
            return (this->size() == 0);
        }
        
        /**
         * \brief Returns number of elements in this list
         */
        size_type size() const noexcept{
            return this->Size;
        }
        
        /**
         * \brief Returns maximum number of elements this list can theoreticaly hold
         * \remarks Actual number may be limited by available memory
         */
        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max();
        }
        
        /**
         * \brief Inserts t value at it
         * \returns iterator to inserted element
         * \remarks previous element at it is not deleted and is now after inserted element
         */
        iterator insert(iterator it, const_reference t) noexcept {
            node<T>* element = new node<T>(t);
            element->next = it.get()->next;
            it.get()->next = element;
            
            if(it.get()==this->tail)
                this->tail = element;
            
            ++this->Size;
            
            return it;
        }
        
        /**
         * \brief Inserts count instances of value at it
         * \remarks previous element at it is not deleted and is now after inserted element
         */
        void insert(iterator it, size_type count, const T& value){
            for(size_t i = 0; i < count; ++i){
                ++(it = this->insert(it, value));
            }
        }
        
        /**
         * \brief Inserts elements of [begin:end) range at it
         * \remarks previous element at it is not deleted and is now after inserted element
         */
        template<class InputIterator>
        void insert(iterator pos, InputIterator begin, InputIterator end){
            while(begin != end){
                ++(pos = this->insert(pos, *(begin++)));
            }
        }
        
        /**
         * \brief Swaps elements of this and LL
         * \remarks No elements are copied or deleted
         */
        void swap(list& LL){
            std::swap(LL.head, this->head);
            std::swap(LL.tail, this->tail);
            std::swap(LL.Size, this->Size);
        }
        
        /**
         * \brief Compares identity and contents of list
         * \returns true if LL is this list or contents of this and LL compare equal
         */
        bool operator==(const list& LL) const {
            if(this==&LL)
                return true;
            
            if(this->size()!=LL.size())
                return false;
            
            auto thisIterator = this->begin();
            auto LLIterator = LL.begin();
            
            for(size_type i = 0; i < this->size();++i){
                if(!(*thisIterator == *LLIterator)) return false;
            }
            
            return true;
        }
        
        /**
         * \brief Changes list size to count
         * \remarks If this list is longer than count excessive elements are deleted
         * \remarks If this list is shorter than count list is padded with instances of value
         */
        void resize(size_type count, value_type value = T()) {
            if(count < this->Size){
                size_t diff = this->Size - count;
                
                for(size_t i = 0; i < diff; ++i){
                    this->pop_back();
                }
                
            }else{
                size_t diff = count - this->Size;
                
                for(size_t i = 0; i < diff; ++i){
                    this->push_back(value);
                }
            }
        }
        
        /**
         * \brief Reverses order of elements in list
         * \remarks No elements are deleted or copied
         */
        void reverse(){
            auto it = ++this->begin();
            
            while(it.hasNext()){
                this->splice(this->begin(), *this, it);
            }
        }
        
        /**
         * \brief Removes element that compare equal to value from this list
         */
        void remove(const T& value){
            this->remove_if([&value](const T& e)->bool {return e == value; });
        }
        
        /**
         * \brief Removes elements that satisfy predicate e.g. pred(elem) is true
         */
        template<class Predicate>
        void remove_if(Predicate pred){
            for(auto iterator = this->begin(); iterator != this->end();){
                if(pred(*iterator))
                    iterator = this->erase(iterator);
                else
                    ++iterator;
                
            }
        }
        
        /**
         * \brief Moves all elements from LL to this
         * \param[in] pos position where elements will be moved to
         * \param[in] LL list to be emptied
         * \remarks no elements are deleted or copied
         */
        void splice(const_iterator pos, list& LL){
            if(this == &LL)
                return;
            
            while(LL.Size>0){
                this->splice(pos, LL, LL.begin());
                ++pos;
            }
        }
        
        /**
         * \brief Moves element at it to position at pos
         * \param[in] pos position where element will be moved to
         * \param[in] LL list containing it
         * \param[in] it element to be moved before pos
         * \remarks no elements are deleted or copied
         */
        void splice(const_iterator pos, list& LL, const_iterator it){
            if(it.get()->next == nullptr)
                return;
            
            if(it.get()->next == LL.tail){
                LL.tail = it.get();
            }
            auto tmp = it.get()->next;
            it.get()->next = it.get()->next->next;
            tmp->next = pos.get()->next;
            pos.get()->next = tmp;
            
            if(pos.get() == this->tail)
                this->tail = tmp;
            
            --LL.Size;
            ++this->Size;
        }
        
        /**
         * \brief Moves all elements from [begin:end) range in LL to this
         * \param[in] pos position where elements will be moved to
         * \param[in] LL list containing range
         * \param[in] begin beginning of range
         * \param[in] end end of range
         * \remarks no elements are deleted or copied
         */
        void splice(const_iterator pos, list& LL, const_iterator begin, const_iterator end){
            auto tmp = end.get()->next;
            
            if(this == &LL){
                if(end.get() == this->tail)
                    this->tail = begin.get();
                
                if(pos.get() == this->tail)
                    this->tail = end.get();
                
                end.get()->next = pos.get()->next;
                pos.get()->next = begin.get()->next;
                begin.get()->next = tmp;
            }else{
                for(auto it = begin; it != end; ++it){
                    ++this->Size;
                    --LL.Size;
                }
                if(end.get() == LL.tail) 
                    LL.tail = begin.get();
                
                if(pos.get() == this->tail) 
                    this->tail = end.get();
                
                end.get()->next = pos.get()->next;
                pos.get()->next = begin.get()->next;
                begin.get()->next = tmp;
            }
        }
        
        /**
         * \brief Merges this and LL as lists sorted in ascending order
         * \param[in] LL list merged with
         * \remarks no elements are deleted or copied
         * \remarks operator < is used to compare elements
         */
        void merge(list& LL){
            this->merge(LL, std::less<T>());
        }
        
        /**
         * \brief Merges this and LL as sorted list
         * \param[in] LL list merged with
         * \param[in] comp Comparator that determines the order of merged elements
         * \remarks no elements are deleted or copied
         * \remarks If comp(a,b) is true a will appear before b in this list
         */
        template <class Compare>
        void merge(list& LL, Compare comp){
            if(this == &LL) 
                return;
            
            auto thisIt = this->begin();
            auto LLIt = LL.begin();
            
            while(thisIt.hasNext() && LLIt.hasNext()){
                if(comp(*LLIt, *thisIt)){
                    this->splice(thisIt, LL, LLIt);
                }++thisIt;
            }
            
            if(LLIt.hasNext())
                this->splice(thisIt, LL);
            
        }
        
        /**
         * \brief Sorts this list in ascending order
         * \remarks no elements are deleted or copied
         * \remarks operator < is used to compate lists
         */
        void sort(){
            this->sort(std::less<T>());
        }
        
        /**
         * \brief Sorts this list
         * \remarks no elements are deleted or copied
         * \remarks If comp(a,b) is true a will appear before b in this list
         */
        template<class Compare>
        void sort(Compare comp){
            iterator current = this->begin();
            
            for(size_t i = 0, max = (this->Size - 1); i < max;++i){
                auto tmp = current;
                
                for(auto it = current; it != this->end();++it){
                    if(comp(*it, *tmp)) 
                        tmp = it;
                }
                
                if(current!=tmp) 
                    this->splice(current, *this, tmp);
                
                ++current;
            }
        }
        
//        /**
//         * \brief Removes consecutive duplicates from list
//         * \details Preserves only first element of sequence of duplicates
//         * \remarks B is duplicate of A if A==B is true
//         */
//        void unique(){
//            this->unique(std::equal_to<T>());
//        }
        
        /**
         * \brief Removes consecutive duplicates from list
         * \details Preserves only first element of sequence of duplicates
         * \remarks B is duplicate of A if p(A,B) is true
         */
        template<class BinaryPredicate>
        void unique(BinaryPredicate p){
            auto a = this->begin();
            auto b = ++this->begin();
            
            while(b != this->end()){
                if(p(*a, *b)) {
                    b = this->erase(b);
                }else{
                    ++a;
                    ++b;
                }
            }
        }
    };
}
#endif /* list_h */
