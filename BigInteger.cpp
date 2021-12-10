#include "BigInteger.h"

BigInteger::BigInteger(long long unsigned int value)
{
	IntArr.push_back(value);
	ByteArr = {MakeByteArr()};
	SizeByte = ByteArr.size();
	SizeNibble = ByteArr.size()*2;
	SizeBit = ByteArr.size()*8;
}

BigInteger::BigInteger(long long unsigned int value1, long long unsigned int value2)
{
	IntArr.push_back(value1);
	IntArr.push_back(value2);
	ByteArr = {MakeByteArr()};
	SizeByte = ByteArr.size();
	SizeNibble = ByteArr.size()*2;
	SizeBit = ByteArr.size()*8;
}

BigInteger::BigInteger(long long unsigned int value1, long long unsigned int value2, long long unsigned int value3)
{
	IntArr.push_back(value1);
	IntArr.push_back(value2);
	IntArr.push_back(value3);
	ByteArr = {MakeByteArr()};
	SizeByte = ByteArr.size();
	SizeNibble = ByteArr.size()*2;
	SizeBit = ByteArr.size()*8;
}

BigInteger::BigInteger(long long unsigned int value1, long long unsigned int value2, long long unsigned int value3, long long unsigned int value4)
{
	IntArr.push_back(value1);
	IntArr.push_back(value2);
	IntArr.push_back(value3);	
	IntArr.push_back(value4);
	ByteArr = {MakeByteArr()};
	SizeByte = ByteArr.size();
	SizeNibble = ByteArr.size()*2;
	SizeBit = ByteArr.size()*8;
}

BigInteger::BigInteger(std::vector<long long unsigned int> value)
	: IntArr{value}
{
	ByteArr = {MakeByteArr()};
	SizeByte = ByteArr.size();
	SizeNibble = ByteArr.size()*2;
	SizeBit = ByteArr.size()*8;
}

BigInteger::BigInteger(const BigInteger& obj)
{
	ByteArr = obj.ByteArr;
	IntArr = obj.IntArr;
	SizeByte = obj.SizeByte;
	SizeNibble = obj.SizeNibble;
	SizeBit = obj.SizeBit;
}

BigInteger::BigInteger(BigInteger&& obj)
{
	ByteArr = obj.ByteArr;
	IntArr = obj.IntArr;
	SizeByte = obj.SizeByte;
	SizeNibble = obj.SizeNibble;
	SizeBit = obj.SizeBit;
	
	obj.ByteArr.clear();
	obj.ByteArr.push_back(0);
	obj.IntArr.clear();
	obj.IntArr.push_back(0);
	obj.SizeByte = 0;
	obj.SizeNibble = 0;
	obj.SizeBit = 0;
}

BigInteger BigInteger::operator=(const BigInteger& obj)
{
	if(*this == obj)
		return *this;
		
	ByteArr = obj.ByteArr;
	IntArr = obj.IntArr;
	SizeByte = obj.SizeByte;
	SizeNibble = obj.SizeNibble;
	SizeBit = obj.SizeBit;
	
	return *this;
}

BigInteger BigInteger::operator=(BigInteger&& obj)
{
	if(*this == obj)
	{
		obj.ByteArr.clear();
		obj.ByteArr.push_back(0);
		obj.IntArr.clear();
		obj.IntArr.push_back(0);
		obj.SizeByte = 0;
		obj.SizeNibble = 0;
		obj.SizeBit = 0;
		return *this;
	}
		
	ByteArr = obj.ByteArr;
	IntArr = obj.IntArr;
	SizeByte = obj.SizeByte;
	SizeNibble = obj.SizeNibble;
	SizeBit = obj.SizeBit;
	
	obj.ByteArr.clear();
	obj.ByteArr.push_back(0);
	obj.IntArr.clear();
	obj.IntArr.push_back(0);
	obj.SizeByte = 0;
	obj.SizeNibble = 0;
	obj.SizeBit = 0;
	
	return *this;	
}

std::vector<uint8_t> BigInteger::MakeByteArr() const
{
	std::vector<uint8_t> tempByteArr;
	std::vector<long long unsigned int> tempIntArr;
	size_t count{};
	
	if(IntArr.size() == 1 && IntArr[0] == 0)
		return std::vector<uint8_t>{0};
		
	for(size_t i{}; i < IntArr.size(); i++)
	{
		long long unsigned int tempInt{IntArr[i]};
		while(tempInt)
		{
			tempIntArr.push_back(tempInt);
			tempInt >>= 8;
			
			tempIntArr[count] = tempIntArr[count] - (tempInt << 8);
			count++;
		}
	}
	
	for(size_t i{tempIntArr.size() - 1}; i < tempIntArr.size(); i--)
	{
		tempByteArr.push_back(tempIntArr[i]);
	}
	
	return tempByteArr;
}

BigInteger::operator char()
{
	if(ByteArr[0] <= 0x7F && SizeByte == sizeof(char))
		return ByteArr[0];
	else
		throw std::runtime_error{"Narrowing."};
}

BigInteger::operator bool()
{
	if(SizeByte == 0)
		return false;
		
	return true;
}

BigInteger::operator int()
{
	if(ByteArr[0] <= 0x7F && SizeByte == sizeof(int))
	{
		int result{};
		size_t count{SizeByte - 2};
		for(size_t i{}; i < SizeByte; i++)
		{
			int temp = ByteArr[i];
			for(size_t j{count--}; j < SizeByte; j--)
				temp <<= 8;
				
			result += temp;	
		}
		
		return result;
	} else {
		throw std::runtime_error{"Narrowing."};
	}
}

BigInteger::operator unsigned int()
{
	if(SizeByte == sizeof(unsigned int))
	{
		unsigned int result{};
		size_t count{SizeByte - 2};
		for(size_t i{}; i < SizeByte; i++)
		{
			unsigned int temp = ByteArr[i];
			for(size_t j{count--}; j < SizeByte; j--)
				temp <<= 8;
				
			result += temp;	
		}
		
		return result;
	} else {
		throw std::runtime_error{"Narrowing."};
	}
}

BigInteger::operator long int()
{
	if(ByteArr[0] <= 0x7F && SizeByte == sizeof(long int))
	{
		long int result{};
		size_t count{SizeByte - 2};
		for(size_t i{}; i < SizeByte; i++)
		{
			long int temp = ByteArr[i];
			for(size_t j{count--}; j < SizeByte; j--)
				temp <<= 8;
				
			result += temp;	
		}
		
		return result;
	} else {
		throw std::runtime_error{"Narrowing."};
	}
}

BigInteger::operator unsigned long int()
{
	if(SizeByte == sizeof(unsigned long int))
	{
		unsigned long int result{};
		size_t count{SizeByte - 2};
		for(size_t i{}; i < SizeByte; i++)
		{
			unsigned long int temp = ByteArr[i];
			for(size_t j{count--}; j < SizeByte; j--)
				temp <<= 8;
				
			result += temp;	
		}
		
		return result;
	} else {
		throw std::runtime_error{"Narrowing."};
	}
}

BigInteger::operator long long int()
{
	if(ByteArr[0] <= 0x7F && SizeByte == sizeof(long long int))
	{
		long long int result{};
		size_t count{SizeByte - 2};
		for(size_t i{}; i < SizeByte; i++)
		{
			long long int temp = ByteArr[i];
			for(size_t j{count--}; j < SizeByte; j--)
				temp <<= 8;
				
			result += temp;	
		}
		
		return result;
	} else {
		throw std::runtime_error{"Narrowing."};
	}
}

BigInteger::operator unsigned long long int()
{
		if(SizeByte == sizeof(unsigned long long int))
	{
		unsigned long long int result{};
		size_t count{SizeByte - 2};
		for(size_t i{}; i < SizeByte; i++)
		{
			unsigned long long int temp = ByteArr[i];
			for(size_t j{count--}; j < SizeByte; j--)
				temp <<= 8;
				
			result += temp;	
		}
		
		return result;
	} else {
		throw std::runtime_error{"Narrowing."};
	}
}

BigInteger& BigInteger::operator++()
{
	*this = *this + 1;
	return *this;
}

BigInteger BigInteger::operator++(int)
{
	BigInteger old = *this;
	++(*this);
	return old;
}

BigInteger& BigInteger::operator--()
{
	*this = *this - 1;
	return *this;
}

BigInteger BigInteger::operator--(int)
{
	BigInteger old = *this;
	--(*this);
	return old;
}

BigInteger BigInteger::operator!()
{
	if(*this)
		return false;
	return true;
}

BigInteger operator+(const BigInteger& lSide, const BigInteger& rSide)
{
	bool flag{false};
	BigInteger lTemp{lSide};
	BigInteger rTemp{rSide};
	BigInteger result{lTemp};
	size_t diff{0};
	
	if(lTemp.SizeByte > rTemp.SizeByte) {
		std::cout << "here\n";
		diff = lTemp.SizeByte - rTemp.SizeByte;
		
		for(size_t i{}; i < diff; i++)
			rTemp.ByteArr.insert(rTemp.ByteArr.begin(), 0);
		
	} else if(lTemp.SizeByte < rTemp.SizeByte) {
		diff = rTemp.SizeByte - lTemp.SizeByte;
		result = rTemp;
		
		for(size_t i{}; i < diff; i++)
			lTemp.ByteArr.insert(lTemp.ByteArr.begin(), 0);
	
	}
	
	size_t Index{result.SizeByte};

	
	for(size_t i{Index}; i-- > 0;)
	{
		if((lTemp.ByteArr[i] + rTemp.ByteArr[i]) > 0xFF)
		{
			if(i == 0)
			{
				result.ByteArr.insert(result.ByteArr.begin(), 1);
				flag = false;
			} else {
				if(flag)			
					result.ByteArr[i] = (lTemp.ByteArr[i] + rTemp.ByteArr[i] + flag) - 0x100;
				else
					result.ByteArr[i] = (lTemp.ByteArr[i] + rTemp.ByteArr[i]) - 0x100;

				flag = true;
			}
		} else if((lTemp.ByteArr[i] + rTemp.ByteArr[i]) <= 0xFF) {
			if(flag)
			{
				if((lTemp.ByteArr[i] + rTemp.ByteArr[i] + flag) > 0xFF)
				{
					if(i == 0)
					{
						result.ByteArr[i] = 0;
						result.ByteArr.insert(result.ByteArr.begin(), 1);
					} else {
						result.ByteArr[i] = 0;
						flag = true;
					}
				} else {
					result.ByteArr[i] = (lTemp.ByteArr[i] + rTemp.ByteArr[i] + flag);
					flag = false;
				}
			} else {
				result.ByteArr[i] = (lTemp.ByteArr[i] + rTemp.ByteArr[i]);
			}
		}
		
	}
	
	return result;
}

BigInteger operator-(const BigInteger& lSide, const BigInteger& rSide)
{
	BigInteger result{lSide};
	if(lSide == rSide)
		return BigInteger{};
	else if(lSide < rSide)
		throw std::overflow_error{"Overflow error."};
	else if(lSide > rSide)
	{
		size_t diff{(lSide.SizeByte - rSide.SizeByte) - 1};
		size_t rIndex{rSide.SizeByte - 1};
		size_t lIndex{lSide.SizeByte - 1};
		
		while(lIndex != diff)
		{
			if(lSide.ByteArr[lIndex] < rSide.ByteArr[rIndex])
			{
				uint16_t temp = 0x100 + result.ByteArr[lIndex];
				result.ByteArr[lIndex] = temp - rSide.ByteArr[rIndex];
				result.ByteArr[lIndex - 1] -= 1;
			} else {
				result.ByteArr[lIndex] -= rSide.ByteArr[rIndex];
			}
			lIndex--; rIndex--;
		}
			
		result.EraseZeros();
	}
	
	return result;
}

BigInteger operator*(const BigInteger& lSide, const BigInteger& rSide)
{
	BigInteger result{lSide};
	
	if(lSide == 0 || rSide == 0)
		return BigInteger{};
	
	return result;
}

bool operator==(const BigInteger& lSide, const BigInteger& rSide)
{
	if(lSide.ByteArr == rSide.ByteArr)
		return true;
	return false;
}

bool operator!=(const BigInteger& lSide, const BigInteger& rSide)
{
	if(lSide == rSide)
		return false;
	return true;
}

bool operator<(const BigInteger& lSide, const BigInteger& rSide)
{
	if(lSide.SizeBit < rSide.SizeBit)
		return true;
	else if(lSide.SizeBit == rSide.SizeBit)
	{
		for(size_t i{}; i < lSide.SizeByte; i++)
		{
			if(lSide.ByteArr[i] < rSide.ByteArr[i])
				return true;
			else if(lSide.ByteArr[i] > rSide.ByteArr[i])
				return false;
		}
	}
	return false;
}

bool operator>(const BigInteger& lSide, const BigInteger& rSide)
{
	if(lSide < rSide)
		return false;
	else if(lSide.SizeBit == rSide.SizeBit)
		for(size_t i{}; i < lSide.SizeByte; i++)
			if(lSide.ByteArr[i] > rSide.ByteArr[i])
				return true;
	return true;
}

bool operator<=(const BigInteger& lSide, const BigInteger& rSide)
{
	if(lSide < rSide || lSide == rSide)
		return true;
	else
		return false;
}

bool operator>=(const BigInteger& lSide, const BigInteger& rSide)
{
	if(lSide <= rSide)
		return false;
	else
		return true;
}

void BigInteger::Resize()
{
	SizeByte = ByteArr.size();
	SizeNibble = SizeByte*2;
	SizeBit = SizeByte*8;
	
	return;
}

void BigInteger::EraseZeros()
{
	std::vector<uint8_t>::iterator it = ByteArr.begin();
	for(size_t i{}; i < ByteArr.size(); i++)
	if(ByteArr[i] != 0)
	{
		if(i == 0)
			return;
		it += i;
		break;
	}
	
	ByteArr.erase(ByteArr.begin(), it);
	Resize();
	return;
}

void BigInteger::print()
{
	for(size_t i{}; i < ByteArr.size(); i++)
	{
		if(ByteArr[i] == 0 && ByteArr.size() > 1)
			std::cout << '0';
		std::cout << std::hex << +ByteArr[i];
	}
		
	std::cout << std::dec << std::endl;
	
	return;
}