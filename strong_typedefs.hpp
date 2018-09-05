#ifndef STRONG_TYPEDEFS_HPP
#define STRONG_TYPEDEFS_HPP
#include <iostream>

// You do not have to understand what exactly happens here.
// The macro DHBW_STRONG_TYPEDEF(<Type>,<Typedefname>) allows us to define so called strong typedefs.
// e.G. DHBW_STRONG_TYPEDEF(my_index, size_t) defines a new type called my_index which is basically
//      a size_t but neither size_t can be casted into a my_index nor the other way round.
// my_index(3) creates a my_index with value 3. The function to_base_type converts the strong typedef
// to its basic type.
//
// Using the macro DHBW_STRONG_INDEX_TYPEDEF our type will also support increment and decrement 
// operations.

namespace ScotlandYard 
{

template <typename T, typename Parameter>
class NamedType
{
public:
    explicit NamedType(T const& value_) : _value(value_) {}
    explicit NamedType(T&& value_) : _value(std::move(value_)) {}
    T const& to_base_type() const {return _value; }
	bool operator==(NamedType<T,Parameter> const & other) const {return _value == other._value; };
protected:
    T _value;
};

template <typename T, typename Parameter>
class NamedTypeWithInDecrement : public NamedType<T,Parameter>
{
public:
	explicit NamedTypeWithInDecrement(T const & value_): NamedType<T,Parameter>(value_) {};
	explicit NamedTypeWithInDecrement(T&& value_): NamedType<T,Parameter>(std::move(value_)) {};

	// prefix increment (i.e. ++type)
	NamedTypeWithInDecrement& operator++(); 
	// prefix decrement (i.e. --type)
    NamedTypeWithInDecrement& operator--(); 
	// postfix increment (i.e. type++)
    NamedTypeWithInDecrement operator++(int);
	// postfix decrement (i.e. type--)
    NamedTypeWithInDecrement operator--(int);
};

// Overload output operator 
template <typename T, typename Parameter>
std::ostream& operator<<(std::ostream& os, NamedType<T, Parameter> const & type)  
{  
    os << type.to_base_type();  
    return os;  
}  

// Overload less operator
template <typename T, typename Parameter>
bool operator<(NamedType<T, Parameter> const & lhs, NamedType<T, Parameter> const & rhs)
{
    return lhs.to_base_type() < rhs.to_base_type();
}

// prefix increment operator
template <typename T, typename Parameter>
NamedTypeWithInDecrement<T,Parameter>& NamedTypeWithInDecrement<T,Parameter>::operator++()
{
	++(this->_value);
	return *this;
}

// prefix decrement operator
template <typename T, typename Parameter>
NamedTypeWithInDecrement<T,Parameter>& NamedTypeWithInDecrement<T,Parameter>::operator--()
{
	--(this->_value);
	return *this;
}

// prefix increment operator
template <typename T, typename Parameter>
NamedTypeWithInDecrement<T,Parameter> NamedTypeWithInDecrement<T,Parameter>::operator++(int)
{
	NamedTypeWithInDecrement<T,Parameter> copy(this->_value);
	++(this->_value);
	return copy;
}

// prefix decrement operator
template <typename T, typename Parameter>
NamedTypeWithInDecrement<T,Parameter> NamedTypeWithInDecrement<T,Parameter>::operator--(int)
{
	NamedTypeWithInDecrement<T,Parameter> copy(this->_value);
	--(this->_value);
	return copy;
}

#define STRONG_TYPEDEF(X,Y) \
 using X = NamedType<Y, struct X ## Dummy >
 
#define STRONG_INDEX_TYPEDEF(X,Y) \
 using X = NamedTypeWithInDecrement<Y, struct X ## Dummy >

} //namespace ScotlandYard
#endif // STRONG_TYPEDEFS_HPP