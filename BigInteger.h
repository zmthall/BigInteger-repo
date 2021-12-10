#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <string>

class BigInteger{
public:
	std::vector<uint8_t> ByteArr;
	std::vector<long long unsigned int> IntArr;
	size_t SizeByte;
	size_t SizeNibble;
	size_t SizeBit;

	// construction
	BigInteger()
		: SizeByte{}, SizeNibble{}, SizeBit{}
	{
		ByteArr.push_back(0);
		IntArr.push_back(0);
	}
	
	BigInteger(long long unsigned int);
	BigInteger(long long int unsigned, long long unsigned int);
	BigInteger(long long unsigned int, long long unsigned int, long long unsigned int);
	BigInteger(long long unsigned int, long long unsigned int, long long unsigned int, long long unsigned int);
	BigInteger(std::vector<long long unsigned int>);
	
	~BigInteger() = default;
	
	// move and copy construction
	BigInteger(const BigInteger&);
	BigInteger(BigInteger&&);
	
	// move and copy assignment
	BigInteger operator=(const BigInteger&);
	BigInteger operator=(BigInteger&&);
	
	// used to turn the long long unsigned ints into a byte array
	std::vector<uint8_t> MakeByteArr() const;
	
	// conversion operators
	operator char();
	operator bool();
	operator int();
	operator unsigned int();
	operator long int();
	operator unsigned long int();
	operator long long int();
	operator unsigned long long int();

	// unary operators
	BigInteger& operator++();
	BigInteger operator++(int);
	BigInteger& operator--();
	BigInteger operator--(int);
	BigInteger operator!();
	
	// Arithmetic operators
	template<typename T>
	friend BigInteger operator+(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) + rSide; }
	template<typename T>
	friend BigInteger operator+(const BigInteger& lSide, const T& rSide) { return lSide + BigInteger(rSide); }
	friend BigInteger operator+(const BigInteger&, const BigInteger&);
	
	template<typename T>
	friend BigInteger operator-(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) - rSide; }
	template<typename T>
	friend BigInteger operator-(const BigInteger& lSide, const T& rSide) { return lSide - BigInteger(rSide); }
	friend BigInteger operator-(const BigInteger&, const BigInteger&);
	
	template<typename T>
	friend BigInteger operator*(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) * rSide; }
	template<typename T>
	friend BigInteger operator*(const BigInteger& lSide, const T& rSide) { return lSide * BigInteger(rSide); }
	friend BigInteger operator*(const BigInteger&, const BigInteger&);
	
	//Arithmetic assignment operators
	
	// relational operators
	template<typename T>
	friend bool operator==(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) == rSide; }
	template<typename T>
	friend bool operator==(const BigInteger& lSide, const T& rSide) { return lSide == BigInteger(rSide); }
	friend bool operator==(const BigInteger&, const BigInteger&);
	
	template<typename T>
	friend bool operator!=(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) != rSide; }
	template<typename T>
	friend bool operator!=(const BigInteger& lSide, const T& rSide) { return lSide != BigInteger(rSide); }
	friend bool operator!=(const BigInteger&, const BigInteger&);
	
	template<typename T>
	friend bool operator<(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) < rSide; }
	template<typename T>
	friend bool operator<(const BigInteger& lSide, const T& rSide) { return lSide < BigInteger(rSide); }
	friend bool operator<(const BigInteger&, const BigInteger&);
	
	template<typename T>
	friend bool operator>(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) > rSide; }
	template<typename T>
	friend bool operator>(const BigInteger& lSide, const T& rSide) { return lSide > BigInteger(rSide); }
	friend bool operator>(const BigInteger&, const BigInteger&);
	
	template<typename T>
	friend bool operator<=(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) <= rSide; }
	template<typename T>
	friend bool operator<=(const BigInteger& lSide, const T& rSide) { return lSide <= BigInteger(rSide); }
	friend bool operator<=(const BigInteger&, const BigInteger&);
	
	template<typename T>
	friend bool operator>=(const T& lSide, const BigInteger& rSide) { return BigInteger(lSide) >= rSide; }
	template<typename T>
	friend bool operator>=(const BigInteger& lSide, const T& rSide) { return lSide >= BigInteger(rSide); }
	friend bool operator>=(const BigInteger&, const BigInteger&);
	
	// bitwise operators


	// utility based functions
	void EraseZeros();
	void Resize();
	void print();
};
#endif /* BIGINTEGER_H */