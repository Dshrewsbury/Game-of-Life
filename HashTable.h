// Lab 11
// Programmer: Daniel Shrewsbury
// Editor(s) used: XP Notepad
// Compiler(s) used: VC++ 2010 Express
//

#include <cassert>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

#ifndef HashTable_h
#define HashTable_h

template<class DataType, int CAPACITY>
class HashTable
{
  public:
  void insert(DataType&);
  bool first(DataType&);
  bool getNext(DataType&);
  int size() const {return count;}
  bool remove(DataType&);
  bool replace(DataType&);
  bool retrieve(DataType&);
  HashTable();
  void clear();


  private:
  typename list<DataType>::const_iterator itCurrent; 
  int currentIndex;
  list<DataType> data[CAPACITY];
  int getWrappedIndex(DataType&);
  int count;

};

template<class DataType, int CAPACITY>
HashTable<DataType, CAPACITY>::HashTable()
{
  count = 0;
  currentIndex = -1;
}

template<class DataType, int CAPACITY>
void HashTable<DataType, CAPACITY>::clear()
{
  //count = 0;
  currentIndex = -1;
  DataType temp;
  if (first(temp)) do
  {
    remove(temp);
  } while (first(temp));
}

template<class DataType, int CAPACITY>
bool HashTable<DataType, CAPACITY>::remove(DataType& parameter)
{
  int i = getWrappedIndex(parameter);  //(wrapped index of data item to be matched) 
  typename list<DataType>::const_iterator it; // const_ for retrieve only! 
  it = find(data[i].begin(), data[i].end(), parameter); 
  if (it == data[i].end()) return false; 

  data[i].erase(it);
  --count;

  return true;
}

template<class DataType, int CAPACITY>
bool HashTable<DataType, CAPACITY>::replace(DataType& parameter)
{
  int i = getWrappedIndex(parameter);  //(wrapped index of data item to be matched) 
  typename list<DataType>::iterator it; // const_ for retrieve only! 
  it = find(data[i].begin(), data[i].end(), parameter); 
  if (it == data[i].end()) return false; 

  *it = parameter; 

  return true;
}

template<class DataType, int CAPACITY>
bool HashTable<DataType, CAPACITY>::retrieve(DataType& parameter)
{
  int i = getWrappedIndex(parameter);  //(wrapped index of data item to be matched) 
  typename list<DataType>::const_iterator it; // const_ for retrieve only! 
  it = find(data[i].begin(), data[i].end(), parameter); 
  if (it == data[i].end()) return false; 

  parameter = *it;

  return true;
}

template<class DataType, int CAPACITY>
void HashTable<DataType, CAPACITY>::insert(DataType& parameter)
{
  int i = getWrappedIndex(parameter);           //(wrapped index to store data item) 
  typename list<DataType>::iterator it; 
  it = find(data[i].begin(), data[i].end(), parameter); 
  if (it != data[i].end()) *it = parameter; // replace 
  else {data[i].push_back(parameter); ++count;}
}

template<class DataType, int CAPACITY>
bool HashTable<DataType, CAPACITY>::first(DataType& parameter)
{
  assert(currentIndex >= -1 && currentIndex < CAPACITY);
  for (currentIndex = 0; currentIndex < CAPACITY; currentIndex++)
  {
    if (!data[currentIndex].empty())
    {
      itCurrent = data[currentIndex].begin();
      break;
  } }
  if (currentIndex == CAPACITY) currentIndex = -1;
  if (currentIndex == -1) return false;
  parameter = *itCurrent;
  return true;
}

template<class DataType, int CAPACITY>
bool HashTable<DataType, CAPACITY>::getNext(DataType& parameter)
{
  assert(currentIndex >= -1 && currentIndex < CAPACITY);
  if (currentIndex == -1) return false;
  assert(!data[currentIndex].empty());
  if (++itCurrent == data[currentIndex].end())
  {
    for (currentIndex = currentIndex + 1; currentIndex < CAPACITY; currentIndex++)
    {
      if (!data[currentIndex].empty())
      {
        itCurrent = data[currentIndex].begin();
        break;
  } } }
  if (currentIndex == CAPACITY) currentIndex = -1;
  else parameter = *itCurrent;
  return currentIndex >= 0;
}

template<class DataType, int CAPACITY>
int HashTable<DataType, CAPACITY>::getWrappedIndex(DataType& parameter)
{
   int desiredIndex = parameter.hashCode();
   int wrappedIndex = desiredIndex % CAPACITY;
   if(wrappedIndex < 0) wrappedIndex = wrappedIndex + CAPACITY;
   return wrappedIndex;
}

#endif