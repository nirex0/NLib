//© 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_BIGINT_H_
#define _N_BIGINT_H_

#include "NDefines.h"
#include <iostream>
#include <exception>

class NBigIntException : public std::exception
{
public:

	NBigIntException(const char* exception_text)
		: std::exception(exception_text)
	{
	}

	~NBigIntException()
	{
	}
};
namespace NLib
{
	class NAPI NBigInt
	{
	public:

		friend std::istream& operator>>(std::istream& is, NBigInt& value);

		friend std::ostream& operator<<(std::ostream& os, const NBigInt& value);

		NBigInt(void);

		NBigInt(const NBigInt& value);

		NBigInt(long value);

		NBigInt(unsigned long value);

		NBigInt(int value);

		NBigInt(unsigned int value);

		NBigInt(const char* psznumber_ptr);

		NBigInt(const char* binary_data_ptr, unsigned int length);

		virtual ~NBigInt(void);

		void SetDefaultBase(unsigned int default_base);

		unsigned int GetBinaryValue(unsigned char* binary_data_ptr = 0) const;

		void SetBinaryValue(const char* binary_data_ptr, unsigned int length);

		void GetNumberString(std::string& number_string, unsigned int base) const;

		bool SetValue(const char* number_ptr, unsigned int base);

		unsigned int LeadingBitPosition() const;

		unsigned int PopulationCount() const;

		NBigInt operator=(const NBigInt& value);

		NBigInt operator=(long value);

		NBigInt operator=(unsigned long value);

		NBigInt operator=(int value);

		NBigInt operator=(unsigned int value);

		NBigInt operator=(const char* psznumber_ptr);

		NBigInt operator+=(const NBigInt& addend);

		NBigInt operator+=(long addend);

		NBigInt operator+=(unsigned long addend);

		NBigInt operator+=(int addend);

		NBigInt operator+=(unsigned int addend);

		NBigInt operator-=(const NBigInt& subtrahend);

		NBigInt operator-=(long subtrahend);

		NBigInt operator-=(unsigned long subtrahend);

		NBigInt operator-=(int subtrahend);

		NBigInt operator-=(unsigned int subtrahend);

		NBigInt operator*=(const NBigInt& multiplier);

	protected:

		void AccumulateWithCarry(NBigInt& product, int index, unsigned int value);

	public:

		NBigInt operator*=(long multiplier);

		NBigInt operator*=(unsigned long multiplier);

		NBigInt operator*=(int multiplier);

		NBigInt operator*=(unsigned int multiplier);

		NBigInt operator/=(const NBigInt& divisor);

		NBigInt operator/=(long divisor);

		NBigInt operator/=(unsigned long divisor);

		NBigInt operator/=(int divisor);

		NBigInt operator/=(unsigned int divisor);

		NBigInt operator<<=(const NBigInt& shift_count);

		NBigInt operator<<=(long shift_count);

		NBigInt operator<<=(unsigned long shift_count);

		NBigInt operator<<=(int shift_count);

		NBigInt operator<<=(unsigned int shift_count);

		NBigInt operator>>=(const NBigInt& shift_count);

		NBigInt operator>>=(long shift_count);

		NBigInt operator>>=(unsigned long shift_count);

		NBigInt operator>>=(int shift_count);

		NBigInt operator>>=(unsigned int shift_count);

		NBigInt operator%=(const NBigInt& divisor);

		NBigInt operator%=(long divisor);

		NBigInt operator%=(unsigned long divisor);

		NBigInt operator%=(int divisor);

		NBigInt operator%=(unsigned int divisor);

		NBigInt operator^=(const NBigInt& value);

		NBigInt operator^=(long value);

		NBigInt operator^=(unsigned long value);

		NBigInt operator^=(int value);

		NBigInt operator^=(unsigned int value);

		NBigInt operator&=(const NBigInt& value);

		NBigInt operator&=(unsigned long value);

		NBigInt operator&=(int value);

		NBigInt operator&=(unsigned int value);

		NBigInt operator|=(const NBigInt& value);

		NBigInt operator|=(long value);

		NBigInt operator|=(unsigned long value);

		NBigInt operator|=(int value);

		NBigInt operator|=(unsigned int value);

		NBigInt operator!();

		NBigInt operator~();

		NBigInt operator+();

		NBigInt operator-();

		const NBigInt operator++();

		const NBigInt operator--();

		const NBigInt operator++(int);

		const NBigInt operator--(int);

		bool operator==(const NBigInt& value) const;

		bool operator==(long value) const;

		bool operator==(unsigned long value) const;

		bool operator==(int value) const;

		bool operator==(unsigned int value) const;

		bool operator!=(const NBigInt& value) const;

		bool operator!=(long value) const;

		bool operator!=(unsigned long value) const;

		bool operator!=(int value) const;

		bool operator!=(unsigned int value) const;

		bool operator<(const NBigInt& value) const;

		bool operator<(long value) const;

		bool operator<(unsigned long value) const;

		bool operator<(int value) const;

		bool operator<(unsigned int value) const;

		bool operator>(const NBigInt& value) const;

		bool operator>(long value) const;

		bool operator>(unsigned long value) const;

		bool operator>(int value) const;

		bool operator>(unsigned int value) const;

		bool operator<=(const NBigInt& value) const;

		bool operator<=(long value) const;

		bool operator<=(unsigned long value) const;

		bool operator<=(int value) const;

		bool operator<=(unsigned int value) const;

		bool operator>=(const NBigInt& value) const;

		bool operator>=(long value) const;

		bool operator>=(unsigned long value) const;

		bool operator>=(int value) const;

		bool operator>=(unsigned int value) const;

		operator long() const;

		operator unsigned long() const;

		operator int() const;

		operator unsigned int() const;

		operator short() const;

		operator unsigned short() const;

		operator char() const;

		operator unsigned char() const;

		operator bool() const;

		operator float() const;

		operator double() const;

		operator long double() const;

#ifdef _DEBUG

		void DebugDump(const char* pszText = 0);

#endif

	private:

		void Copy(const NBigInt& that);

		void AddPositiveArray(const NBigInt& addend);

		bool SubtractPositiveArray(const NBigInt& subtrahend);

		void ShiftLeft(unsigned int shift_count);

		void ShiftRight(unsigned int shift_count);

		bool IsZero() const;

		bool IsNegative() const;

		bool FitsIn32Bits() const;

		void SetIntegerLength(unsigned int integer_length, bool copy_data_flag = false);

		void SetToZero();

		unsigned int GetSafeArrayValue(unsigned int iIndex) const;

		void Normalize();

		bool LessThanPositiveArrayCompare(const NBigInt& value_0, const NBigInt& value_1) const;

		unsigned int PopulationCount32Bit(unsigned int value) const;

		void GetBase8NumberString(std::string& number_string) const;

		void GetBase8Digits(std::string& base8_digits_string) const;

		void GetBase10NumberString(std::string& number_string) const;

		void GetBase16NumberString(std::string& number_string) const;

		void StripLeadingZeroDigits(std::string& number_string, char zero_digit) const;

		bool SetValueWithBase8String(const char* digits_ptr);

		void SetValueWithBase8DigitValues(const std::string& base8_digit_string);

		bool SetValueWithBase10String(const char* digits_ptr);

		bool ConvertDecimalStringToOctalDigits(const char* decimal_digits_ptr, std::string& digits_string) const;

		bool SetValueWithBase16String(const char* digits_ptr);

		void SetValueWithBase16DigitValues(const std::string& base16_digit_values_string);

	private:

		unsigned int m_array_length;
		unsigned int m_integer_length;
		unsigned int m_default_base;
		unsigned int* m_array_ptr;
		bool m_negative_flag;

	};

	NBigInt operator+(const NBigInt& addend_a, const NBigInt& addend_b);

	NBigInt operator+(const NBigInt& x_addend, int addend);

	NBigInt operator+(int addend, const NBigInt& x_addend);

	NBigInt operator+(const NBigInt& x_addend, unsigned int addend);

	NBigInt operator+(unsigned int addend, const NBigInt& x_addend);

	NBigInt operator-(const NBigInt& minuend, const NBigInt& subtrahend);

	NBigInt operator-(const NBigInt& minuend, int subtrahend);

	NBigInt operator-(int minuend, const NBigInt& subtrahend);

	NBigInt operator-(const NBigInt& minuend, unsigned int subtrahend);

	NBigInt operator-(unsigned int minuend, const NBigInt& subtrahend);

	NBigInt operator*(const NBigInt& multiplier_a, const NBigInt& multiplier_b);

	NBigInt operator*(const NBigInt& x_multiplier, int multiplier);

	NBigInt operator*(int multiplier, const NBigInt& x_multiplier);

	NBigInt operator*(const NBigInt& x_multiplier, unsigned int multiplier);

	NBigInt operator*(unsigned int multiplier, const NBigInt& x_multiplier);

	NBigInt operator/(const NBigInt& x_dividend, const NBigInt& x_denominator);

	NBigInt operator/(const NBigInt& x_dividend, int divisor);

	NBigInt operator/(int dividend, const NBigInt& x_denominator);


	NBigInt operator/(const NBigInt& x_dividend, unsigned int divisor);

	NBigInt operator/(unsigned int dividend, const NBigInt& x_denominator);

	NBigInt operator<<(const NBigInt& value, const NBigInt& x_shift_count);

	NBigInt operator<<(const NBigInt& value, int shift_count);

	NBigInt operator<<(int value, const NBigInt& x_shift_count);

	NBigInt operator<<(const NBigInt& value, unsigned int shift_count);

	NBigInt operator<<(unsigned int value, const NBigInt& x_shift_count);

	NBigInt operator>>(const NBigInt& value, const NBigInt& x_shift_count);

	NBigInt operator>>(const NBigInt& value, int shift_count);

	NBigInt operator>>(int value, const NBigInt& x_shift_count);

	NBigInt operator>>(const NBigInt& value, unsigned int shift_count);

	NBigInt operator>>(unsigned int value, const NBigInt& x_shift_count);

	NBigInt operator%(const NBigInt& x_dividend, const NBigInt& x_denominator);

	NBigInt operator%(const NBigInt& x_dividend, int divisor);

	NBigInt operator%(int dividend, const NBigInt& x_denominator);

	NBigInt operator%(const NBigInt& x_dividend, unsigned int divisor);

	NBigInt operator%(unsigned int dividend, const NBigInt& x_denominator);

	NBigInt operator^(const NBigInt& value_a, const NBigInt& value_b);

	NBigInt operator^(const NBigInt& x_value,
		int value);

	NBigInt operator^(int value, const NBigInt& x_value);

	NBigInt operator^(const NBigInt& x_value, unsigned int value);

	NBigInt operator^(unsigned int value, const NBigInt& x_value);

	NBigInt operator&(const NBigInt& value_a, const NBigInt& value_b);

	NBigInt operator&(const NBigInt& x_value, int value);

	NBigInt operator&(int value, const NBigInt& x_value);

	NBigInt operator&(const NBigInt& x_value, unsigned int value);

	NBigInt operator&(unsigned int value, const NBigInt& x_value);

	NBigInt operator|(const NBigInt& value_a, const NBigInt& value_b);

	NBigInt operator|(const NBigInt& x_value, int value);

	NBigInt operator|(int value, const NBigInt& x_value);

	NBigInt operator|(const NBigInt& x_value, unsigned int value);

	NBigInt operator|(unsigned int value, const NBigInt& x_value);
}

#endif // !_N_BIGINT_H_
