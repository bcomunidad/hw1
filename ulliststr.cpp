#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
  temp = head_;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val) {
  if(head_ == NULL) {     // if list is empty
    head_ = new Item();
    tail_ = head_;
    size_++;
    temp = head_;
    head_->first = 9;
    head_->val[head_->first] = val;
    head_->last = 10;
    head_->prev = 0;
  }
  else if(tail_->last == 10) {          // there's already an element in the end of the list
    tail_ = new Item();
    size_++;
    tail_->val[tail_->first] = val;
    tail_->last++;
    tail_->prev = temp;
    temp->next = tail_;
    temp = tail_;
  }
  else {   // there's space in the last list
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
    temp = tail_;
  }
}

void ULListStr::pop_back() {
  if(head_ == NULL) {   // empty list, there's nothing to pop
    return;
  }
  else if((tail_->last - tail_->first) == 1) {   // only one element in the list
    if(head_ == tail_) {    // there's only one list
      delete head_;
      head_ = tail_ = NULL;
      temp = head_;
      size_ = 0;
    }
    else {        // there's more than one list
      Item* del = tail_->prev;
      delete tail_;
      tail_ = del;
      tail_->next = NULL;
      temp = tail_;
      size_--;
    }

  }
  else {    // there's more than one element in the list
    tail_->last--;
    size_--;
    temp = tail_;
  }
}

void ULListStr::push_front(const std::string& val) {
  if(head_ == NULL) {    // if list is empty
    head_ = new Item();
    tail_ = head_;
    size_++;
    temp = head_;
    head_->val[0] = val;
    head_->last++;   // moving last pointer to next free location
    head_->prev = 0;
  }
  else if(head_->first == 0) {   // there's already an element at the front of list 
    head_ = new Item();
    size_++;
    head_->first = 9;
    head_->val[head_->first] = val;
    head_->last = 10;
    head_->prev = 0;
    head_->next = temp;
    temp->prev = head_;
    temp = head_;
  }
  else if(head_->first != 0 ) {      // there's space in the first list 
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
    temp = head_;
  }
}

void ULListStr::pop_front() {
  if(head_ == NULL) {   // empty list, there's nothing to pop
    return;
  }
  else if((head_->last - head_->first) == 1) {       // only one element in the list
    if(head_ == tail_) {      // there's only one list
      delete head_;
      head_ = tail_ = NULL;
      temp = head_;
      size_ = 0;
    }
    else {      // there's more than one list
      Item* del = head_->next;
      delete head_;
      head_ = del;
      head_->prev = 0;
      temp = head_;
      size_--;
    }
  }
  else {    // there's more than one element in the list
    head_->first++;
    size_--;
    temp = head_;
  }
}

std::string const & ULListStr::back() const {
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
if(head_ == NULL || loc >= size_ || loc < 0) {      // error cases return NULL
    return NULL;
  }
  Item* trav = head_;
  size_t track = 0;       
  size_t reset = head_->first;      
  while(track != loc) {
    track++;
    reset++;
    if(reset == trav->last) {
      if(trav->next == NULL && track == loc) {    // reset val isn't found
        return NULL;
      }
      trav = trav->next;
      reset = 0;
    }
  }
  return &trav->val[reset];
}

