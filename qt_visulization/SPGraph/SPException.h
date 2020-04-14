#ifndef SPGRAPH_SPEXCEPTION_H
#define SPGRAPH_SPEXCEPTION_H

#include <stdexcept>
#include <string>
#include <utility>

template <class T>
class SPGraph;
template <class T>
class SPiterator;
template <class T>
class Node;

template <class T>
class SPException: public std::exception
{
public:
    SPException(const char* message, SPGraph<T>* g):
            msg_(message), invoked_from(g)
    {}

    SPException(std::string  message, SPGraph<T>* g):
            msg_(std::move(message)), invoked_from(g)
    {}

    ~SPException() override = default;

    [[nodiscard]] const char* what() const noexcept override{
        return msg_.c_str();
    }

protected:
    std::string msg_;
    SPGraph<T>* invoked_from{};
};

template <class T>
class SPinvalidIt : public std::exception
{
public:
    SPinvalidIt(const char* message, const SPiterator<T>* g):
            msg_(message), it(g)
    {}

    SPinvalidIt(std::string  message,const SPiterator<T>* g):
    msg_(std::move(message)), it(g)
    {}

    ~SPinvalidIt() override = default;

    [[nodiscard]] const char* what() const noexcept override{
        return msg_.c_str();
    }

    const SPiterator<T>* it;
protected:
    std::string msg_;
};

template <class T>
class SPInvalidComposition : public SPException<T>
{
public:
    enum opType { Series, Parallel };
    enum nodeType { Source, Terminal };

    SPInvalidComposition(const std::string& str, SPGraph<T>* f, const SPGraph<T>* s, opType ot, nodeType np) : SPException<T>(str, f) {}
    SPGraph<T>* second = nullptr;
};

#endif //SPGRAPH_SPEXCEPTION_H
