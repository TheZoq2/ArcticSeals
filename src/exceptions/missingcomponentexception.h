#ifndef H_MISSING_COMPONENT_EXCEPTION
#define H_MISSING_COMPONENT_EXCEPTION

#include <exception>
#include <typeinfo>
#include <string>

namespace zen
{
    class MissingComponentException : public std::exception
    {
        public:
            MissingComponentException(std::type_info type)
            {
                this->typeName = type.name();
            }

            virtual const char* what() const throw() override
            {
                std::string msg;
                msg.append("Entity did not contain requested component ");
                msg.append(typeName);

                return msg.data();
            }
        private:
            std::string typeName;
    };
}
#endif
