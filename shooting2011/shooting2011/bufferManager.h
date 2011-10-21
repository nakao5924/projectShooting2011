#ifndef __BUFFER_MANAGER_H__
#define __BUFFER_MANAGER_H__

#include <algorithm>

template<class T>
class BufferManager{
private:
  T* buffer;
  int bufferSize;
  void expandBuffer(int newSize);
public:
  BufferManager();
  ~BufferManager();

  T &operator [](int index);
  const T &operator [](int index)const;
  T *getBufferData();
};

template<class T>
BufferManager<T>::BufferManager(){
  buffer = static_cast<T *>(NULL);
  bufferSize = 0;
}

template<class T>
BufferManager<T>::~BufferManager(){
  delete[] buffer;
}

template<class T>
void BufferManager<T>::expandBuffer(int newSize){
  if(newSize <= bufferSize){
    return;
  }
  newSize = max(newSize, bufferSize * 2);
  T *newBuffer = new T[newSize];
  for(int i = 0; i < bufferSize; ++i){
    newBuffer[i] = buffer[i];
  }
  delete[] buffer;
  buffer = newBuffer;
  bufferSize = newSize;
}

template<class T>
T &BufferManager<T>::operator [](int index){
  assert(index >= 0);
  expandBuffer(index + 1);
  return buffer[index];
}
template<class T>
const T &BufferManager<T>::operator [](int index)const{
  assert(index >= 0 && index < bufferSize);
  return buffer[index];
}

template<class T>
T *BufferManager<T>::getBufferData(){
  return buffer;
}

#endif //__BUFFER_MANAGER_H__