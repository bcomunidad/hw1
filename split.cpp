/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

void split(Node*& in, Node*& odds, Node*& evens)
{
  if(in == nullptr) {   // "in" is empty
    return;
  }
  Node* temp = in->next;
  if(in->next == NULL) {    // the end of "in" list
    if(in->value % 2 != 0) {    // last value is odd
      if(evens == in) {     
        evens = nullptr;      
      }
      odds = in;
      in = nullptr;
    }
    else {    // last value is even
      if(odds == in) {      
        odds = nullptr;
      }
      evens = in;
      in = nullptr;
    }
    return;
  }
  else if(in->value % 2 != 0) {   // value is odd
    if(evens == in) {             // putting an end to the evens list
      evens = nullptr;
    }
    odds = in;
    in = nullptr;   
    split(temp, odds->next, evens);
  }
  else {                // value is even
    if(odds == in) {    // putting an end to the odds list
      odds = nullptr;
    }
    evens = in;
    in = nullptr;
    split(temp, odds, evens->next);
  }
}
