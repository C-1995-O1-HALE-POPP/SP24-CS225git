#include "list.h"
using namespace std;
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
int main() {
  List<int> list1;
  list1.insertFront(9);
  list1.insertFront(8);
  list1.insertFront(7);
  list1.insertFront(6);
  list1.insertFront(4);
  list1.insertFront(3);
  list1.insertFront(1);
  List<int> list2;
  list2.insertFront(7);
  list2.insertFront(5);
  list2.insertFront(2);
  list1.print(cout);
  list2.print(cout);
  list1.mergeWith(list2);
  list1.print(cout);


  return 0;
}
