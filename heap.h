#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> items_;
  int m_;
  PComparator comp_;

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
  : m_(m), comp_(c)
{
  if (m_ < 2){
    throw std::invalid_argument("m must be at least 2");
  }
}
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){

}
template <typename T, typename PComparator>
void Heap<T, PComparator>:: push(const T& item){
  T value = item;
  items_.push_back(value);
  std::size_t child = items_.size() - 1;
  while (child > 0){
    std::size_t parent = (child - 1) / m_;
    if (!comp_(value, items_[parent])){
      break;
    }
    items_[child] = items_[parent];
    child = parent;
  }
  items_[child] = value;
}
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return items_.size() == 0 ;
}
template <typename T, typename PComparator>
std::size_t Heap<T, PComparator>::size() const{
  return items_.size();
}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is Empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is Empty");
  }
  if (items_.size() == 1){
    items_.pop_back();
    return;
  }
  T value = items_.back();
  items_.pop_back();
  std::size_t parent = 0;
  while (true){
    std::size_t first_child = parent * static_cast<std::size_t>(m_) + 1;
    if (first_child >= items_.size()){
      break;
    }
    std::size_t best_child = first_child;
    std::size_t end_child = first_child + static_cast<std::size_t>(m_);
    if (end_child > items_.size()){
      end_child = items_.size();
    }
    for (std::size_t child = first_child + 1; child < end_child; ++child){
      if (comp_(items_[child], items_[best_child])){
        best_child = child;
      }
    }
    if (!comp_(items_[best_child], value)){
      break;
    }
    items_[parent] = items_[best_child];
    parent = best_child;
  }
  items_[parent] = value;
}



#endif

