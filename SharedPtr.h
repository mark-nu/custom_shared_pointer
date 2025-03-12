#include <cstdint>

using namespace std;

template <typename T>
class SharedPtr
{
private:
    uint32_t *_refCount = nullptr;
    T *_ptr = nullptr;

    void __cleanup__() noexcept
    {
        if (_refCount != nullptr)
        {
            cout << "count: " << *(this->_refCount) << endl;
            if (--(*_refCount) == 0)
            {
                if (_ptr != nullptr)
                {
                    delete _ptr;
                }
                delete _refCount;
            }
        }
    }

public:
    SharedPtr() noexcept : _ptr(nullptr), _refCount(new uint32_t(0)) {}

    SharedPtr(T *object) noexcept : _ptr(object), _refCount(new uint32_t(1)) {}

    SharedPtr(const SharedPtr &obj) noexcept
    {
        this->_ptr = obj._ptr;
        this->_refCount = obj._refCount;

        if (this->_ptr != nullptr)
        {
            (*this->_refCount)++;
        }

        cout << "copy count (): " << *(this->_refCount) << endl;
    }

    SharedPtr(SharedPtr &&obj) noexcept
    {
        cout << "Moving" << endl;
        this->_ptr = obj._ptr;
        this->_refCount = obj._refCount;

        obj._ptr = nullptr;
        obj._refCount = nullptr;
    }

    ~SharedPtr() noexcept
    {
        __cleanup__();
    }

    SharedPtr &operator=(const SharedPtr &obj) noexcept
    {
        this->_ptr = obj._ptr;
        this->_refCount = obj._refCount;

        if (this->_ptr != nullptr)
        {
            (*this->_refCount)++;
        }
        cout << "copy count =: " << *(this->_refCount) << endl;

        return *this;
    }

    SharedPtr &operator=(SharedPtr &&obj) noexcept
    {
        cout << "Moving operator" << endl;
        if (this != &obj)
        {
            __cleanup__();

            this->_ptr = obj._ptr;
            this->_refCount = obj._refCount;

            obj._ptr = nullptr;
            obj._refCount = nullptr;
        }

        return *this;
    }

    T *operator->() noexcept
    {
        return this->_ptr;
    }

    void reset() noexcept
    {
        __cleanup__();
    }

    uint32_t getRefCount() noexcept
    {
        return *_refCount;
    }
};