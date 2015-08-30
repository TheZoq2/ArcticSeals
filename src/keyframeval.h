#ifndef H_KEYFRAME_VALUE
#define H_KEYFRAME_VALUE

template <class T>
class KeyframeVal
{
public:
    KeyframeVal();

    T& operator=(T other);

    T val();

    bool isChanged();
private:
    T value;

    bool changed; //if this value should be changed this keyframe
};
#endif
