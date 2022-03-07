#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <optional>


void untraceable();




struct NonMovable{
    NonMovable() = default;
    NonMovable(NonMovable const&) = default;
};

void f(NonMovable s);
void f(std::string s);
void g(const std::string &s);

class B {
    std::string s;
public:
    template<typename T>
    explicit B( T&& s ) : s{std::move<T>( s) } {}

    void print() {
        std::cout << s;
    }
};

template<typename T>
class A {
    T s;
public:
    A( T&& s ) : s{std::move<T>( s) } {}

    void print() {
        std::cout << s;
    }
};

void test() {
    std::string s="****";
    f(std::move(s));
    g(std::move(s)); // Noncompliant: s is cast back to const l-value reference. s will not be moved.

    const std::string constS="***";
    f(std::move(constS)); // Noncompliant: constS will not be moved.

    NonMovable t;
    f(std::move(t)); // Noncompliant: std::move is useless on non-movable objects like t. Copy constructor is called.
}

class BaseException { };
class DerivedException: public BaseException { };

int main() {
    std::cout << "Hello, World!" << std::endl;

    try {
        untraceable();
    }
    catch ( BaseException const& b ) {
        std::cout << "base";
    }
    catch( int i ) {
        std::cout << i;
    }
    catch ( DerivedException const& d ) {
        std::cout << "derived";
    }

    int i = 42;

    auto p = std::unique_ptr<int>( new int(42) );



    return 0;
}

namespace geometry { // Noncompliant
    namespace deep {
        namespace common {
            class point {
            };
        }
    }
}

namespace geometry { // Noncompliant since C++20
    namespace deep {
        inline namespace triangle {
            class edge {
            };
        }
    }
}


void it() {

    std::vector<std::string> strings{"one", "two", "three"};

    std::vector<std::string>::const_iterator it = strings.begin(); // clang-tidy, only
    std::vector<std::string>::const_iterator it2 = strings.cbegin(); // both
    std::vector<std::string>::iterator it3 = strings.begin(); // both

}



void starts_with() {

    std::string str = "prefixed string";

    if( 6 <= str.size() && str.substr( 0, 6 ) == "prefix" ) { // Noncompliant
        std::cout << str << " starts with the prefix\n";
    }
//    if (6 <= str.size() && std::string_view(str.begin(), str.begin() + 6) == "prefix") { // Noncompliant
//        std::cout <<str <<" starts with the prefix\n";
//    }
    if (6 <= str.size() && std::string_view(str.data(), 6) == "prefix") { // Noncompliant
        std::cout <<str <<" starts with the prefix\n";
    }
    if (7 <= str.size() && str.substr(str.size() - 7) == "postfix") { // Noncompliant
        std::cout <<str <<" ends with the postfix\n";
    }
    if( 6 <= str.size() && std::string_view( str ).substr( 0, 6 ) == "prefix" ) {
        std::cout << str << " starts with the prefix\n";
    }
}


int redundant_casts(int i) {
    int result = static_cast<int>(i + 42); // Noncompliant
    return (int) result; // Noncompliant
}


void optional_value_or() {
    std::optional<std::string> arg;

    if (arg.has_value()) { // Noncompliant, the entire if statement can be simplified to a simpler statement using "value_or(default_value)"
        std::cout << arg.value();
    } else {
        std::cout << "magic";
    }

    // another way to check presence and access value
    std::cout << (arg ? *arg : "magic"); // Noncompliant, replace the ternary operator by using "value_or(default_value)"

}

void type_aliasing() {

    typedef int Integer;

    typedef Integer* PInteger;
//    using PInteger = int*;

    typedef void (*FunctionPointerType)(int);

    // member function typedef?
}
