#ifndef H_MISSING_COMPONENT_EXCEPTION
#define H_MISSING_COMPONENT_EXCEPTION

#include <exception>

namespace zen
{
    template<T>
    class MissingComponentException : public std::exception
    {
        public:
            MissingComponentException()
            {

            }
        private:
    };
}
#endif
