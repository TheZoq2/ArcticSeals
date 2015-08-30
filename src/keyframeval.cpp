#include "keyframeval.h"

template <class T>
KeyframeVal<T>::KeyframeVal()
{
    this->changed = false;
}

template <class T>
T& KeyframeVal<T>::operator=(T other)
{
    this->changed = true;
    this->value = other;

    return *this;
}
template <class T>
T KeyframeVal<T>::val()
{
    return value;
}

template <class T>
bool KeyframeVal<T>::isChanged()
{
    return changed;
}
