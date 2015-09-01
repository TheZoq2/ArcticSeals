#ifndef H_KEYFRAME_VALUE
#define H_KEYFRAME_VALUE

template <class T>
class KeyframeVal
{
public:
    KeyframeVal()
    {
        this->changed = false;
    }

    T operator=(T other)
    {
        this->changed = true;
        this->value = other;
    
        return *this;
    }

    T val()
    {
        return value;
    }

    bool isChanged()
    {
        return changed;
    }

private:
    T value;

    bool changed; //if this value should be changed this keyframe
};
#endif
