#include <iostream>
#include <string>

template<typename T>
class UniqPtr {
public:
    UniqPtr() : ptr(nullptr) {}

  
    explicit UniqPtr(T* p) : ptr(p) {}

   
    UniqPtr(const UniqPtr&) = delete; 
    UniqPtr& operator=(const UniqPtr&) = delete; 

    
    UniqPtr(UniqPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    
    UniqPtr& operator=(UniqPtr&& other) noexcept {
        if (this != &other) {
            free(); 
            ptr = other.ptr; 
            other.ptr = nullptr;
        }
        return *this;
    }

    
    ~UniqPtr() {
        free(); 
    }

    
    void free() {
        delete ptr;
        ptr = nullptr;
    }

    
    void swap(UniqPtr& other) noexcept {
        T* temp = ptr;
        ptr = other.ptr;
        other.ptr = temp;
    }

    
    T* relise() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    
    T* get() const {
        return ptr;
    }

private:
    T* ptr; 
};

int main() {
    setlocale(LC_ALL, "ru");
    UniqPtr<int> p1(new int(5));
    std::cout << "Значение: " << *p1.get() << std::endl;

    UniqPtr<int> p2(new int(10));
    p1.swap(p2);

    std::cout << "После обмена p1 имеет значение: " << (p1.get() ? std::to_string(*p1.get()) : "nullptr") << "\n";
    std::cout << "После обмена p2 имеет значение: " << (p2.get() ? std::to_string(*p2.get()) : "nullptr") << "\n";

    p1.free(); 
    p2.free(); 

    return 0;
}