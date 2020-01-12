#include "SingletonBase.h"

template <typename T>
T* SingletonBase<T>::_Instance = nullptr;

