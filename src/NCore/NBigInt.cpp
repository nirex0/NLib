#if defined __GNUC__
#include <stdio.h>
#include <string.h>
#endif

#include "NBigInt.h"

namespace NLib
{
#define INT_BIT_LENGTH_IS_POWER_OF_TWO

	namespace
	{
		const unsigned int INTEGER_LOW_HALF_MASK = 0xFFFF;
		const unsigned int INTEGER_BIT_COUNT = 32;
		const unsigned int INTEGER_HALF_BIT_COUNT = 16;
		const int INTEGER_MAXIMUM_BASE = 90;
		const double D_MAX_UNSIGNED_VALUE = 4294967296.0;

		const char DIGIT_ARRAY[INTEGER_MAXIMUM_BASE] =
		{
			'0', '1', '2', '3', '4', '5', '6', '7',
			'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
			'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
			'O', 'P', 'Q', 'R', 'S', 'T', 'W', 'X',
			'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'w', 'x',
			'y', 'z', '.', ',', '?', '/', '\\', '|',
			'<', '>', ':', ';', '"', '\'', '{', '}',
			'[', ']', '`', '~', '!', '@', '#', '$',
			'%', '^', '&', '*', '(', ')', '-', '_',
			'+', '='
		};

		const unsigned int BIT_MASK_ARRAY[5] =
		{
			0xAAAAAAAA,
			0xCCCCCCCC,
			0xF0F0F0F0,
			0xFF00FF00,
			0xFFFF0000
		};

		const unsigned int BIT_MASK_TABLE_LENGTH = sizeof(BIT_MASK_ARRAY) / sizeof(unsigned int);

#ifdef LARGE_INT_ALTERNATE_POP_COUNT
		const unsigned int MASK_1 = 011111111111;
		const unsigned int MASK_3 = 033333333333;
		const unsigned int MASK_7 = 030707070707;
#endif
	};

	std::istream& operator>>(std::istream& is, NBigInt& value)
	{
		const unsigned int max_string_length = 2048;
		char* number_ptr = new char[max_string_length];

		if (number_ptr != 0)
		{
			is.get(number_ptr, max_string_length - 1);
			int length = (int)is.gcount();
			number_ptr[length] = '\0';

			unsigned int base;

			switch (is.flags() & std::ios_base::basefield)
			{
			case std::ios_base::oct:
				base = 8;
				break;
			case std::ios_base::dec:
				base = 10;
				break;
			case std::ios_base::hex:
				base = 16;
				break;
			default:
				base = 10;
				break;
			}

			value.SetValue(number_ptr, base);

			delete[] number_ptr;
		}

		return is;
	}

	
	std::ostream& operator<<(std::ostream& os, const NBigInt& value)
	{
		unsigned int base;

		switch (os.flags() & std::ios_base::basefield)
		{
		case std::ios_base::oct:
			base = 8;
			break;
		case std::ios_base::dec:
			base = 10;
			break;
		case std::ios_base::hex:
			base = 16;
			break;
		default:
			base = 10;
			break;
		}

		std::string number_string;
		value.GetNumberString(number_string, base);
		os << number_string.c_str();

		return os;
	}
	
	NBigInt::NBigInt()
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		SetIntegerLength(1);
		m_array_ptr[0] = 0;
	}

	NBigInt::NBigInt(const NBigInt& value)
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		Copy(value);
	}

	NBigInt::NBigInt(long value)
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		SetIntegerLength(1);
		m_negative_flag = value < 0;
		m_array_ptr[0] =			m_negative_flag ? (unsigned int)(-value) : (unsigned int)(value);
	}


	NBigInt::NBigInt(unsigned long value)
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		SetIntegerLength(1);
		m_array_ptr[0] = value;
	}
	
	NBigInt::NBigInt(int value)
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		SetIntegerLength(1);
		m_negative_flag = value < 0;
		m_array_ptr[0] =			m_negative_flag ? (unsigned int)(-value) : (unsigned int)(value);
	}
	
	NBigInt::NBigInt(unsigned int value)
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		SetIntegerLength(1);
		m_array_ptr[0] = value;
	}

	NBigInt::NBigInt(const char* psznumber_ptr)
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		SetValue(psznumber_ptr, m_default_base);
	}

	NBigInt::NBigInt(const char* binary_data_ptr,
		unsigned int length)
		: m_array_length(0)
		, m_integer_length(0)
		, m_default_base(10)
		, m_array_ptr(0)
		, m_negative_flag(false)
	{
		SetBinaryValue(binary_data_ptr, length);
	}

	NBigInt::~NBigInt()
	{
		delete[] m_array_ptr;
	}
	
	void NBigInt::SetDefaultBase(unsigned int default_base)
	{
		if ((default_base == 0) || (default_base > INTEGER_MAXIMUM_BASE))
		{
			throw NBigIntException("Illegal base");
		}

		m_default_base = default_base;
	}
	
	unsigned int NBigInt::GetBinaryValue(unsigned char* binary_data_ptr) const
	{
		unsigned int length = sizeof(unsigned int)* m_integer_length;
		
		char* source_ptr = reinterpret_cast<char*>(&m_array_ptr[0]);
		unsigned int leading_zero_count = 0;

		for (unsigned int i = length - 1; i >= 0; --i)
		{
			if (source_ptr[i] == 0)
			{
				leading_zero_count++;
			}
			else
			{
				break;
			}
		}

		length -= leading_zero_count;

		if (binary_data_ptr != 0)
		{
			for (unsigned int j = 0; j < length; ++j)
			{
				binary_data_ptr[j] = source_ptr[j];
			}
		}

		return length;
	}

	void NBigInt::SetBinaryValue(const char* binary_data_ptr, unsigned int length)
	{
		m_negative_flag = false;

		unsigned int array_length = (length + 3) >> 2;
		SetIntegerLength(array_length);

		char* destination_ptr = reinterpret_cast<char*>(m_array_ptr);
		unsigned int i = 0;

		for (i = 0; i < length; ++i)
		{
			destination_ptr[i] = binary_data_ptr[i];
		}

		unsigned int index_one_past_final_byte = m_integer_length << 2;

		if (length < index_one_past_final_byte)
		{
			for (i = length; i < index_one_past_final_byte; ++i)
			{
				destination_ptr[i] = 0;
			}
		}

		Normalize();

		return;
	}

	void NBigInt::GetNumberString(std::string& number_string, unsigned int base) const
	{		
		number_string.erase();

		switch (base)
		{
		case 8:

			GetBase8NumberString(number_string);
			break;

		case 10:

			GetBase10NumberString(number_string);
			break;

		case 16:

			GetBase16NumberString(number_string);
			break;

		default:
			
			NBigInt x_temp = *this;

			do
			{
				NBigInt x_mult = x_temp / base;
				NBigInt x_part = x_mult * base;
				unsigned int digit_index = (unsigned int)(x_temp - x_part);
				number_string += DIGIT_ARRAY[digit_index];
				x_temp = x_mult;
			} while (!x_temp.IsZero());
		

			char* number_ptr = const_cast<char*>(number_string.data());
			unsigned int length = number_string.length();

			for (unsigned int i = 0; i < (length >> 1); ++i)
			{
				char temp = number_ptr[i];
				number_ptr[i] = number_ptr[(length - i) - 1];
				number_ptr[(length - i) - 1] = temp;
			}

			break;
		}

		if (IsNegative())
		{
			number_string.insert(0, "-");
		}

		return;
	}
	
	bool NBigInt::SetValue(const char* number_ptr, unsigned int base)
	{
		SetToZero();

		bool success_flag = number_ptr != 0;

		if (success_flag)
		{
			size_t length = ::strlen(number_ptr);

			if (length > 0)
			{
				size_t index = 0;

				for (index = 0; index < length; ++index)
				{
					if (!::isspace((int)(number_ptr[index])))
					{
						break;
					}
				}

				m_negative_flag = number_ptr[index] == '-';

				if (m_negative_flag)
				{
					++index;
				}

				if (number_ptr[index] == '+')
				{
					++index;
				}
				for (; index < length; ++index)
				{
					if (!::isspace((int)(number_ptr[index])))
					{
						break;
					}
				}

				switch (base)
				{
				case 8:

					success_flag = SetValueWithBase8String(number_ptr + index);
					break;

				case 10:

					success_flag = SetValueWithBase10String(number_ptr + index);
					break;

				case 16:

					success_flag = SetValueWithBase16String(number_ptr + index);
					break;

				default:
				{
					bool success_flag = true;

					for (size_t i = index; i < length; ++i)
					{
						int digit = ::tolower((int)(number_ptr[i]));

						if (::isxdigit(digit))
						{
							if ((digit >= 'a') && (digit <= 'f'))
							{
								digit = digit + 10 - (int)('a');
							}
							else
							{
								digit = digit - (int)('0');
							}

							if ((unsigned int)(digit) < base)
							{
								operator*=(base);
								operator+=(digit);
							}
							else
							{
								success_flag = false;
								break;
							}
						}
						else
						{
							break;
						}
					}
				}

				break;
				}
			}
		}
		
		Normalize();

		return success_flag;
	}

	unsigned int NBigInt::LeadingBitPosition() const
	{
		unsigned int leading_bit_position = 0;

		int leading_value_index = m_integer_length - 1;

		if (m_array_ptr[m_integer_length - 1] == 0)
		{
			leading_value_index--;
		}

		if (leading_value_index > 0)
		{
			unsigned int leading_value = m_array_ptr[leading_value_index];

			unsigned int bit_position_addend = INTEGER_HALF_BIT_COUNT;

			for (unsigned int i = BIT_MASK_TABLE_LENGTH - 1; int(i) >= 0; --i)
			{
				unsigned int bit_mask = BIT_MASK_ARRAY[i];

				if ((leading_value & bit_mask) != 0)
				{
					leading_bit_position += bit_position_addend;
					leading_value = leading_value & bit_mask;
					bit_position_addend = bit_position_addend >> 1;
				}
			}

			leading_bit_position = (INTEGER_BIT_COUNT * leading_value_index) + leading_bit_position;
		}


		return leading_bit_position;
	}

	unsigned int NBigInt::PopulationCount() const
	{
		unsigned int bit_count = 0;

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			bit_count += PopulationCount32Bit(m_array_ptr[i]);
		}

		return bit_count;
	}

	NBigInt NBigInt::operator=(const NBigInt& value)
	{
		Copy(value);
		return *this;
	}

	NBigInt NBigInt::operator=(long value)
	{
		Copy(NBigInt(value));
		return *this;
	}

	NBigInt NBigInt::operator=(unsigned long value)
	{
		Copy(NBigInt(value));
		return *this;
	}

	NBigInt NBigInt::operator=(int value)
	{
		Copy(NBigInt(value));
		return *this;
	}

	NBigInt NBigInt::operator=(unsigned int value)
	{
		Copy(NBigInt(value));
		return *this;
	}

	NBigInt NBigInt::operator=(const char* psznumber_ptr)
	{
		SetValue(psznumber_ptr, m_default_base);
		return *this;
	}

	NBigInt NBigInt::operator+=(const NBigInt& addend)
	{
		bool negative_flag_0 = IsNegative();
		bool negative_flag_1 = addend.IsNegative();

		if (negative_flag_0 ^ negative_flag_1)
		{
			m_negative_flag = negative_flag_0 ^ SubtractPositiveArray(addend);
		}
		else
		{
			AddPositiveArray(addend);
		}

		Normalize();

		return *this;
	}

	NBigInt NBigInt::operator+=(long addend)
	{
		return operator+=(NBigInt(addend));
	}

	NBigInt NBigInt::operator+=(unsigned long addend)
	{
		return operator+=(NBigInt(addend));
	}

	NBigInt NBigInt::operator+=(int addend)
	{
		return operator+=(NBigInt(addend));
	}

	NBigInt NBigInt::operator+=(unsigned int addend)
	{
		return operator+=(NBigInt(addend));
	}

	NBigInt NBigInt::operator-=(const NBigInt& subtrahend)
	{
		bool negative_flag_0 = IsNegative();
		bool negative_flag_1 = subtrahend.IsNegative();

		if (negative_flag_0 ^ negative_flag_1)
		{
			AddPositiveArray(subtrahend);
		}
		else
		{
			m_negative_flag = negative_flag_0 ^ SubtractPositiveArray(subtrahend);
		}

		Normalize();

		return *this;
	}

	NBigInt NBigInt::operator-=(long subtrahend)
	{
		return operator-=(NBigInt(subtrahend));
	}

	NBigInt NBigInt::operator-=(unsigned long subtrahend)
	{
		return operator-=(NBigInt(subtrahend));
	}

	NBigInt NBigInt::operator-=(int subtrahend)
	{
		return operator-=(NBigInt(subtrahend));
	}

	NBigInt NBigInt::operator-=(unsigned int subtrahend)
	{
		return operator-=(NBigInt(subtrahend));
	}

	NBigInt NBigInt::operator*=(const NBigInt& x_multiplier)
	{
		NBigInt product = 0;

		product.SetIntegerLength(m_integer_length + x_multiplier.m_integer_length);

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			unsigned int a0 = m_array_ptr[i] & INTEGER_LOW_HALF_MASK;
			unsigned int a1 = m_array_ptr[i] >> INTEGER_HALF_BIT_COUNT;

			for (unsigned int j = 0; j < x_multiplier.m_integer_length; ++j)
			{
				unsigned int b0 = x_multiplier.m_array_ptr[j] & INTEGER_LOW_HALF_MASK;
				unsigned int b1 = x_multiplier.m_array_ptr[j] >> INTEGER_HALF_BIT_COUNT;

				unsigned int a0b0 = a0 * b0;
				unsigned int a0b1 = a0 * b1;
				unsigned int a1b0 = a1 * b0;
				unsigned int a1b1 = a1 * b1;

				unsigned int a0b1L = a0b1 << INTEGER_HALF_BIT_COUNT;
				unsigned int p0 = a0b0 + a0b1L;
				unsigned int low_dword_carry = (p0 < a0b1L) ? 1 : 0;
				unsigned int a1b0L = a1b0 << INTEGER_HALF_BIT_COUNT;
				unsigned int temp = p0 + a1b0L;
				low_dword_carry += (temp < p0) ? 1 : 0;
				p0 = temp;

				unsigned int a0b1H = a0b1 >> INTEGER_HALF_BIT_COUNT;
				unsigned int p1 = a1b1 + a0b1H;
				unsigned int a1b0H = a1b0 >> INTEGER_HALF_BIT_COUNT;
				p1 = p1 + a1b0H + low_dword_carry;

				unsigned int index = i + j;
				AccumulateWithCarry(product, index, p0);

				AccumulateWithCarry(product, index + 1, p1);
			}
		}

		product.Normalize();

		product.m_negative_flag = IsNegative() ^ x_multiplier.IsNegative();

		Copy(product);

		return *this;
	}

	void NBigInt::AccumulateWithCarry(NBigInt &product,
		int index,
		unsigned int value)
	{
		bool sum_overflows = true;

		while ((sum_overflows) && (index < (int)(product.m_integer_length)))
		{
			unsigned int temp = product.m_array_ptr[index];
			temp = temp + value;
			sum_overflows = temp < value;
			value = 1;
			product.m_array_ptr[index] = temp;
			++index;
		}
	}

	NBigInt NBigInt::operator*=(long multiplier)
	{
		return operator*=(NBigInt(multiplier));
	}

	NBigInt NBigInt::operator*=(unsigned long multiplier)
	{
		return operator*=(NBigInt(multiplier));
	}

	NBigInt NBigInt::operator*=(int multiplier)
	{
		return operator*=(NBigInt(multiplier));
	}

	NBigInt NBigInt::operator*=(unsigned int multiplier)
	{
		return operator*=(NBigInt(multiplier));
	}

	NBigInt NBigInt::operator/=(const NBigInt& divisor)
	{
		if (divisor.IsZero())
		{
			throw NBigIntException("Divide by zero");
		}

		bool quotient_sign = IsNegative() ^ divisor.IsNegative();
		
		NBigInt numerator = *this;

		numerator.m_negative_flag = false;

		SetToZero();

		if (!numerator.IsZero())
		{
			int scale_shift = 0;
			NBigInt denom = divisor;

			while (denom < numerator)
			{
				denom.ShiftLeft(1);
				++scale_shift;
			}

			while (numerator >= denom)
			{
				NBigInt difference = numerator - denom;

				denom.ShiftRight(1);
				ShiftLeft(1);

				if (!difference.IsNegative())
				{
					++m_array_ptr[0];
					numerator = difference;
				}
			}

			*this <<= scale_shift;

			Normalize();

			m_negative_flag = quotient_sign;
		}

		return *this;
	}

	NBigInt NBigInt::operator/=(long divisor)
	{
		return operator/=(NBigInt(divisor));
	}

	NBigInt NBigInt::operator/=(unsigned long divisor)
	{
		return operator/=(NBigInt(divisor));
	}

	NBigInt NBigInt::operator/=(int divisor)
	{
		return operator/=(NBigInt(divisor));
	}

	NBigInt NBigInt::operator/=(unsigned int divisor)
	{
		return operator/=(NBigInt(divisor));
	}
	
	NBigInt NBigInt::operator<<=(const NBigInt& shift_count)
	{
		if (shift_count.FitsIn32Bits())
		{
			if (shift_count.IsNegative())
			{
				ShiftRight(shift_count.m_array_ptr[0]);
			}
			else
			{
				ShiftLeft(shift_count.m_array_ptr[0]);
			}
		}
		else
		{
			SetToZero();
		}

		return *this;
	}

	NBigInt NBigInt::operator<<=(long shift_count)
	{
		return operator<<=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator<<=(unsigned long shift_count)
	{
		return operator<<=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator<<=(int shift_count)
	{
		return operator<<=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator<<=(unsigned int shift_count)
	{
		return operator<<=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator>>=(const NBigInt& shift_count)
	{
		if (shift_count.FitsIn32Bits())
		{
			if (shift_count.IsNegative())
			{
				ShiftLeft(shift_count.m_array_ptr[0]);
			}
			else
			{
				ShiftRight(shift_count.m_array_ptr[0]);
			}
		}
		else
		{
			SetToZero();
		}

		return *this;
	}

	NBigInt NBigInt::operator>>=(long shift_count)
	{
		return operator>>=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator>>=(unsigned long shift_count)
	{
		return operator>>=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator>>=(int shift_count)
	{
		return operator>>=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator>>=(unsigned int shift_count)
	{
		return operator>>=(NBigInt(shift_count));
	}

	NBigInt NBigInt::operator%=(const NBigInt& divisor)
	{
		NBigInt x_temp(*this);
		operator/=(divisor);
		operator*=(divisor);
		return operator-=(x_temp);
	}

	NBigInt NBigInt::operator%=(long divisor)
	{
		return operator%=(NBigInt(divisor));
	}

	NBigInt NBigInt::operator%=(unsigned long divisor)
	{
		return operator%=(NBigInt(divisor));
	}

	NBigInt NBigInt::operator%=(int divisor)
	{
		return operator%=(NBigInt(divisor));
	}

	NBigInt NBigInt::operator%=(unsigned int divisor)
	{
		return operator%=(NBigInt(divisor));
	}

	NBigInt NBigInt::operator^=(const NBigInt& value)
	{
		unsigned int largest_integer_length =
			m_integer_length < value.m_integer_length ? value.m_integer_length : m_integer_length;

		SetIntegerLength(largest_integer_length);

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			m_array_ptr[i] ^= value.GetSafeArrayValue(i);
		}

		Normalize();

		return *this;
	}

	NBigInt NBigInt::operator^=(long value)
	{
		return operator%=(NBigInt(value));
	}

	NBigInt NBigInt::operator^=(unsigned long value)
	{
		return operator%=(NBigInt(value));
	}

	NBigInt NBigInt::operator^=(int value)
	{
		return operator%=(NBigInt(value));
	}

	NBigInt NBigInt::operator^=(unsigned int value)
	{
		return operator%=(NBigInt(value));
	}

	NBigInt NBigInt::operator&=(const NBigInt& value)
	{
		unsigned int largest_integer_length =
			m_integer_length < value.m_integer_length ? value.m_integer_length : m_integer_length;

		SetIntegerLength(largest_integer_length);

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			m_array_ptr[i] &= value.GetSafeArrayValue(i);
		}

		Normalize();

		return *this;
	}

	NBigInt NBigInt::operator&=(unsigned long value)
	{
		return operator&=(NBigInt(value));
	}

	NBigInt NBigInt::operator&=(int value)
	{
		return operator&=(NBigInt(value));
	}

	NBigInt NBigInt::operator&=(unsigned int value)
	{
		return operator&=(NBigInt(value));
	}

	NBigInt NBigInt::operator|=(const NBigInt& value)
	{
		unsigned int largest_integer_length =
			m_integer_length < value.m_integer_length ? value.m_integer_length : m_integer_length;

		SetIntegerLength(largest_integer_length);

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			m_array_ptr[i] |= value.GetSafeArrayValue(i);
		}

		Normalize();

		return *this;
	}

	NBigInt NBigInt::operator|=(long value)
	{
		return operator|=(NBigInt(value));
	}

	NBigInt NBigInt::operator|=(unsigned long value)
	{
		return operator|=(NBigInt(value));
	}

	NBigInt NBigInt::operator|=(int value)
	{
		return operator|=(NBigInt(value));
	}

	NBigInt NBigInt::operator|=(unsigned int value)
	{
		return operator|=(NBigInt(value));
	}
	
	NBigInt NBigInt::operator!()
	{
		if (IsZero())
		{
			m_array_ptr[0] = (unsigned int)(-1);
			m_integer_length = 1;
		}
		else
		{
			SetToZero();
		}

		return *this;
	}

	NBigInt NBigInt::operator~()
	{
		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			m_array_ptr[i] = ~m_array_ptr[i];
		}

		Normalize();

		return *this;
	}

	NBigInt NBigInt::operator+()
	{
		return *this;
	}

	NBigInt NBigInt::operator-()
	{
		m_negative_flag = !m_negative_flag;
		return *this;
	}

	const NBigInt NBigInt::operator++()
	{
		operator+=(1);
		return *this;
	}

	const NBigInt NBigInt::operator--()
	{
		operator-=(1);
		return *this;
	}

	const NBigInt NBigInt::operator++(int)
	{
		NBigInt x_temp = *this;
		operator+=(1);
		return x_temp;
	}

	const NBigInt NBigInt::operator--(int)
	{
		NBigInt x_temp = *this;
		operator-=(1);
		return x_temp;
	}

	bool NBigInt::operator==(const NBigInt& value) const
	{
		unsigned int largest_integer_length =
			m_integer_length < value.m_integer_length ? value.m_integer_length : m_integer_length;

		bool bEqual = true;

		for (unsigned int i = largest_integer_length - 1; (int)(i) >= 0; --i)
		{
			if (GetSafeArrayValue(i) != value.GetSafeArrayValue(i))
			{
				bEqual = false;
				break;
			}
		}

		return bEqual;
	}

	bool NBigInt::operator==(long value) const
	{
		return operator==(NBigInt(value));
	}

	bool NBigInt::operator==(unsigned long value) const
	{
		return operator==(NBigInt(value));
	}

	bool NBigInt::operator==(int value) const
	{
		return operator==(NBigInt(value));
	}

	bool NBigInt::operator==(unsigned int value) const
	{
		return operator==(NBigInt(value));
	}

	bool NBigInt::operator!=(const NBigInt& value) const
	{
		return !operator==(value);
	}

	bool NBigInt::operator!=(long value) const
	{
		return operator!=(NBigInt(value));
	}

	bool NBigInt::operator!=(unsigned long value) const
	{
		return operator!=(NBigInt(value));
	}

	bool NBigInt::operator!=(int value) const
	{
		return operator!=(NBigInt(value));
	}

	bool NBigInt::operator!=(unsigned int value) const
	{
		return operator!=(NBigInt(value));
	}

	bool NBigInt::operator<(const NBigInt& value) const
	{
		bool is_less_than_flag = false;

		if (IsNegative())
		{
			if (!value.IsNegative())
			{
				is_less_than_flag = true;
			}
			else
			{
				is_less_than_flag = LessThanPositiveArrayCompare(value, *this);
			}
		}
		else
		{
			is_less_than_flag = LessThanPositiveArrayCompare(*this, value);
		}

		return is_less_than_flag;
	}

	bool NBigInt::operator<(long value) const
	{
		return operator<(NBigInt(value));
	}

	bool NBigInt::operator<(unsigned long value) const
	{
		return operator<(NBigInt(value));
	}

	bool NBigInt::operator<(int value) const
	{
		return operator<(NBigInt(value));
	}

	bool NBigInt::operator<(unsigned int value) const
	{
		return operator<(NBigInt(value));
	}

	bool NBigInt::operator>(const NBigInt& value) const
	{
		return ((!operator<(value)) && (!operator==(value)));
	}

	bool NBigInt::operator>(long value) const
	{
		return operator>(NBigInt(value));
	}

	bool NBigInt::operator>(unsigned long value) const
	{
		return operator>(NBigInt(value));
	}

	bool NBigInt::operator>(int value) const
	{
		return operator>(NBigInt(value));
	}

	bool NBigInt::operator>(unsigned int value) const
	{
		return operator>(NBigInt(value));
	}

	bool NBigInt::operator<=(const NBigInt& value) const
	{
		return !operator>(value);
	}

	bool NBigInt::operator<=(long value) const
	{
		return operator<=(NBigInt(value));
	}

	bool NBigInt::operator<=(unsigned long value) const
	{
		return operator<=(NBigInt(value));
	}

	bool NBigInt::operator<=(int value) const
	{
		return operator<=(NBigInt(value));
	}

	bool NBigInt::operator<=(unsigned int value) const
	{
		return operator<=(NBigInt(value));
	}

	bool NBigInt::operator>=(const NBigInt& value) const
	{
		return !operator<(value);
	}

	bool NBigInt::operator>=(long value) const
	{
		return operator<(NBigInt(value));
	}

	bool NBigInt::operator>=(unsigned long value) const
	{
		return operator<(NBigInt(value));
	}

	bool NBigInt::operator>=(int value) const
	{
		return operator<(NBigInt(value));
	}

	bool NBigInt::operator>=(unsigned int value) const
	{
		return operator<(NBigInt(value));
	}

	NBigInt::operator long() const
	{
		return (long)(m_array_ptr[0]);
	}

	NBigInt::operator unsigned long() const
	{
		return (unsigned long)(m_array_ptr[0]);
	}

	NBigInt::operator int() const
	{
		return (int)(m_array_ptr[0]);
	}

	NBigInt::operator unsigned int() const
	{
		return (m_array_ptr[0]);
	}

	NBigInt::operator short() const
	{
		return (short)(m_array_ptr[0]);
	}

	NBigInt::operator unsigned short() const
	{
		return (unsigned short)(m_array_ptr[0]);
	}

	NBigInt::operator char() const
	{
		return (char)(m_array_ptr[0]);
	}

	NBigInt::operator unsigned char() const
	{
		return (unsigned char)(m_array_ptr[0]);
	}

	NBigInt::operator bool() const
	{
		unsigned int temp = 0;

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			temp = temp | m_array_ptr[i];
		}

		return temp != 0;
	}

	NBigInt::operator float() const
	{
	#if defined __GNUC__
		double Temp = double(*this);
		return float(Temp);
	#else
		long double Temp = long double(*this);
		return float(Temp);
	#endif
	}

	NBigInt::operator double() const
	{
	#if defined __GNUC__
		double Temp = double(*this);
		return Temp;
	#else
		long double Temp = long double(*this);
		return double(Temp);
	#endif
	}

	NBigInt::operator long double() const
	{
		NBigInt x_temp;

		long double temp = 0;

		for (unsigned int i = m_integer_length - 1; (int)(i) >= 0; ++i)
		{
			temp = D_MAX_UNSIGNED_VALUE * temp;
			temp = temp + m_array_ptr[i];
		}

		return temp;
	}

	#ifdef _DEBUG
	void NBigInt::DebugDump(const char* pszText)
	{
		if (pszText != 0)
		{
			std::cout << pszText << std::endl;
		}

		std::cout << "Length = " << m_integer_length << std::endl;

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			std::cout << i << "    " << m_array_ptr[i] << std::endl;
		}

		return;
	}

	#endif

	void NBigInt::Copy(const NBigInt& that)
	{
		SetIntegerLength(that.m_integer_length);

		m_negative_flag = that.m_negative_flag;

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			m_array_ptr[i] = that.m_array_ptr[i];
		}

		return;
	}

	void NBigInt::AddPositiveArray(const NBigInt& addend)
	{
		if (m_integer_length < addend.m_integer_length)
		{
			SetIntegerLength(addend.m_integer_length, true);
		}

		unsigned int carry = 0;

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			unsigned int addend_array_value = addend.GetSafeArrayValue(i);
			m_array_ptr[i] = m_array_ptr[i] + addend_array_value + carry;
			carry = (m_array_ptr[i] < addend_array_value) ? 1 : 0;
		}

		if (carry == 1)
		{
			SetIntegerLength(m_integer_length + 1, true);
			m_array_ptr[m_integer_length - 1] = 1;
		}

		return;
	}

	bool NBigInt::SubtractPositiveArray(const NBigInt& subtrahend)
	{
		if (m_integer_length < subtrahend.m_integer_length)
		{
			SetIntegerLength(subtrahend.m_integer_length, true);
		}

		unsigned int most_significant_array_value = m_array_ptr[m_integer_length - 1];

		bool borrow = false;

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			unsigned int minuend_array_value = m_array_ptr[i];
			unsigned int subtrahend_array_value = subtrahend.GetSafeArrayValue(i);
			unsigned int difference = minuend_array_value - subtrahend_array_value;
			m_array_ptr[i] = difference - (borrow ? 1 : 0);

			borrow = borrow & (difference == 0);

			if (!borrow)
			{
				borrow = minuend_array_value < subtrahend_array_value;
			}
		}

		bool reverse_sign =
			m_array_ptr[m_integer_length - 1] > most_significant_array_value;

		if (reverse_sign)
		{
			operator~();
			NBigInt xOne(1);
			AddPositiveArray(xOne);
		}

		return reverse_sign;
	}

	void NBigInt::ShiftLeft(unsigned int shift_count)
	{
		if (shift_count != 0)
		{
			bool bNonZero = false;

			unsigned int nonzero_array_index = 0;

			for (nonzero_array_index = m_integer_length - 1;
				(int)(nonzero_array_index) >= 0;
				--nonzero_array_index)
			{
				if (m_array_ptr[nonzero_array_index] != 0)
				{
					bNonZero = true;
					break;
				}
			}

			if (bNonZero)
			{
				unsigned int most_significant_value = m_array_ptr[nonzero_array_index];
				unsigned int bit_position = 0;

				for (bit_position = 0;
					bit_position < INTEGER_BIT_COUNT;
					++bit_position)
				{
					if ((int)(most_significant_value) < 0)
					{
						break;
					}

					most_significant_value <<= 1;
				}

				bit_position = INTEGER_BIT_COUNT - 1 - bit_position;

				unsigned int array_bit_position =
					INTEGER_BIT_COUNT * nonzero_array_index + bit_position;

				unsigned int final_shift_position = array_bit_position + shift_count;

				
				unsigned int integer_length =
					(final_shift_position + INTEGER_BIT_COUNT) / INTEGER_BIT_COUNT;

				SetIntegerLength(integer_length, true);

				unsigned int array_shift_value = shift_count / INTEGER_BIT_COUNT;

				if (array_shift_value != 0)
				{
					for (unsigned int i = m_integer_length - 1;
						(int)(i) >= 0;
						--i)
					{
						m_array_ptr[i] = GetSafeArrayValue(i - array_shift_value);
					}
				}

				unsigned int remaining_shift_count = shift_count
					- (array_shift_value * INTEGER_BIT_COUNT);

				for (unsigned int i = m_integer_length - 1;
					(int)(i) >= 0;
					--i)
				{
					m_array_ptr[i] = (m_array_ptr[i] << remaining_shift_count)
						| (GetSafeArrayValue(i - 1)
							>> (INTEGER_BIT_COUNT - remaining_shift_count));
				}

				Normalize();
			}
		}

		return;
	}

	void NBigInt::ShiftRight(unsigned int shift_count)
	{
		if (shift_count != 0)
		{
			if (shift_count < m_integer_length * INTEGER_BIT_COUNT)
			{
				unsigned int array_shift_value = shift_count / INTEGER_BIT_COUNT;

				if (array_shift_value != 0)
				{
					for (unsigned int i = 0; i < m_integer_length - array_shift_value; ++i)
					{
						m_array_ptr[i] = m_array_ptr[i + array_shift_value];
					}
				}

				unsigned int remaining_shift_count = shift_count
					- (array_shift_value * INTEGER_BIT_COUNT);

				for (unsigned int i = 0; i < m_integer_length; ++i)
				{
					m_array_ptr[i] = (m_array_ptr[i] >> remaining_shift_count)
						| (GetSafeArrayValue(i + 1)
							<< (INTEGER_BIT_COUNT - remaining_shift_count));
				}

				Normalize();
			}
			else
			{
				SetToZero();
			}
		}

		return;
	}

	bool NBigInt::IsZero() const
	{
		unsigned int temp = 0;

		for (unsigned int i = 0; i < m_integer_length; ++i)
		{
			temp |= m_array_ptr[i];
		}

		return temp == 0;
	}

	bool NBigInt::IsNegative() const
	{
		return m_negative_flag;
	}

	bool NBigInt::FitsIn32Bits() const
	{
		return m_integer_length == 1;
	}

	void NBigInt::SetIntegerLength(unsigned int integer_length, bool copy_data_flag)
	{
		bool reallocate_array_memory = integer_length > m_array_length;

		if (!reallocate_array_memory)
		{
			reallocate_array_memory = integer_length < (m_array_length >> 2);
			copy_data_flag = true;
		}

		if (reallocate_array_memory)
		{
			unsigned int * array_ptr = new unsigned int[integer_length];

			bool memory_allocated = array_ptr != 0;

			if (memory_allocated)
			{
				if (copy_data_flag)
				{
					unsigned int copy_length = integer_length;

					if (m_integer_length < integer_length)
					{
						copy_length = m_integer_length;
					}

					for (unsigned int i = 0; i < copy_length; ++i)
					{
						array_ptr[i] = m_array_ptr[i];
					}

					if (copy_length < integer_length)
					{
						for (unsigned int j = copy_length; j < integer_length; ++j)
						{
							array_ptr[j] = 0;
						}
					}

				}
				else
				{
					for (unsigned int i = 0; i < integer_length; ++i)
					{
						array_ptr[i] = 0;
					}
				}

				delete[] m_array_ptr;

				m_array_ptr = array_ptr;

				m_array_length = integer_length;
			}
			else
			{
				throw NBigIntException("Memory allocation failed");
			}
		}

		m_integer_length = integer_length;

		return;
	}

	void NBigInt::SetToZero()
	{
		SetIntegerLength(1);
		m_array_ptr[0] = 0;
		return;
	}

	unsigned int NBigInt::GetSafeArrayValue(unsigned int index) const
	{
		unsigned int array_value;

		if (index < m_integer_length)
		{
			array_value = m_array_ptr[index];
		}
		else
		{
			array_value = 0;
		}

		return array_value;
	}

	void NBigInt::Normalize()
	{
		unsigned int integer_length = 1;

		for (unsigned int i = m_integer_length - 1; i > 0; --i)
		{
			if (m_array_ptr[i] != 0)
			{
				integer_length = i + 1;
				break;
			}
		}

		m_integer_length = integer_length;

		return;
	}

	bool NBigInt::LessThanPositiveArrayCompare(const NBigInt& value_0, const NBigInt& value_1) const
	{
		unsigned int largest_integer_length = value_0.m_integer_length > value_1.m_integer_length ? value_0.m_integer_length : value_1.m_integer_length;

		bool is_less_than_flag = false;

		for (unsigned int i = largest_integer_length - 1; (int)(i) >= 0; --i)
		{
			unsigned int array_value_0 = value_0.GetSafeArrayValue(i);
			unsigned int array_value_1 = value_1.GetSafeArrayValue(i);

			if (array_value_0 < array_value_1)
			{
				is_less_than_flag = true;
			}
			else if (array_value_0 > array_value_1)
			{
				break;
			}
		}

		return is_less_than_flag;
	}

	unsigned int NBigInt::PopulationCount32Bit(unsigned int value) const
	{
	#ifndef LARGE_INT_ALTERNATE_POP_COUNT

		unsigned int shift_value = 1;

		for (unsigned int i = 0; i < BIT_MASK_TABLE_LENGTH; ++i)
		{
			unsigned int bit_mask = BIT_MASK_ARRAY[i];
			value = ((value & bit_mask) >> shift_value) + (value & ~bit_mask);
			shift_value = shift_value << 1;
		}

		return value;

	#else
		unsigned int temp = value - ((value >> 1) & MASK_3) - ((value >> 2) & MASK_1);
		temp = (temp + (temp >> 3)) & MASK_7;
		return temp % 63;
	#endif
	}

	void NBigInt::GetBase8NumberString(std::string& number_string) const
	{
		std::string base8_digits_string;
		GetBase8Digits(base8_digits_string);

		number_string.erase();

		for (unsigned int i = 0; i < base8_digits_string.length(); ++i)
		{
			number_string += base8_digits_string[i] + '0';
		}

		return;
	}

	void NBigInt::GetBase8Digits(std::string& base8_digits_string) const
	{
		base8_digits_string.erase();

		unsigned int current_bit_position_plus_one = INTEGER_BIT_COUNT * m_integer_length;

		unsigned int extra_bits = current_bit_position_plus_one % 3;
		unsigned int index = m_integer_length - 1;

		while (current_bit_position_plus_one != 0)
		{
			char base8_digit;

			switch (extra_bits)
			{
			case 0:

				base8_digits_string += (char)((m_array_ptr[index] >> 29) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 26) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 23) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 20) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 17) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 14) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 11) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 8) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 5) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 2) & 7);
				break;

			case 1:

				base8_digit = (char)(((GetSafeArrayValue(index + 1) & 3) << 1)
					| ((m_array_ptr[index] >> 31) & 1));
				base8_digits_string += base8_digit;

				base8_digits_string += (char)((m_array_ptr[index] >> 28) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 25) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 22) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 19) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 16) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 13) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 10) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 7) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 4) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 1) & 7);
				break;

			case 2:

				base8_digit = (char)(((GetSafeArrayValue(index + 1) & 1) << 2)
					| ((m_array_ptr[index] >> 30) & 3));
				base8_digits_string += base8_digit;

				base8_digits_string += (char)((m_array_ptr[index] >> 27) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 24) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 21) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 18) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 15) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 12) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 9) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 6) & 7);
				base8_digits_string += (char)((m_array_ptr[index] >> 3) & 7);
				base8_digits_string += (char)(m_array_ptr[index] & 7);
				break;

			default:

				break;
			}

			index--;
			extra_bits = (extra_bits + 1) % 3;
			current_bit_position_plus_one -= INTEGER_BIT_COUNT;
		}

		StripLeadingZeroDigits(base8_digits_string, 0);

		return;
	}

	void NBigInt::GetBase10NumberString(std::string& number_string) const
	{
		NBigInt x_temp = *this;

		std::string digits_string;
		x_temp.GetBase8Digits(digits_string);

		char* digit_array_ptr = const_cast<char*>(digits_string.data());
		unsigned int digit_length = (unsigned int)(digits_string.length());

		char* subtrahend_ptr = new char[digit_length];

		if (subtrahend_ptr == 0)
		{
			throw NBigIntException("Memory allocation failed");;
		}

		for (unsigned int k = 0; k < digit_length - 1; ++k)
		{
			unsigned int j = 0;

			for (j = k + 1; (int)(j) >= 0; --j)
			{
				subtrahend_ptr[j] = 0;
			}

			for (j = k; (int)(j) >= 0; --j)
			{
				char doubled_digit = digit_array_ptr[j] << 1;

				if (doubled_digit > 9)
				{
					subtrahend_ptr[j + 1] += doubled_digit - 10;
					subtrahend_ptr[j] += 1;
				}
				else
				{
					subtrahend_ptr[j + 1] += doubled_digit;
				}
			}

			for (unsigned int m = k + 1; (int)(m) >= 0; --m)
			{
				char difference = digit_array_ptr[m] - subtrahend_ptr[m];

				if (difference < 0)
				{
					digit_array_ptr[m] = difference + 10;

					if ((int)(m - 1) >= 0)
					{
						digit_array_ptr[m - 1] -= 1;
					}
				}
				else
				{
					digit_array_ptr[m] = difference;
				}
			}
		}

		delete[] subtrahend_ptr;

		unsigned int first_nonzero_position = 0;

		for (first_nonzero_position = 0;
			first_nonzero_position < digits_string.length();
			++first_nonzero_position)
		{
			if (digits_string[first_nonzero_position] != 0)
			{
				break;
			}
		}

		number_string.erase();

		for (unsigned int j = first_nonzero_position;
			j < digits_string.length();
			++j)
		{
			number_string += digits_string[j] + '0';
		}

		return;
	}

	void NBigInt::GetBase16NumberString(std::string& number_string) const
	{
		number_string.erase();
		
		for (unsigned int i = m_integer_length - 1; (int)(i) >= 0; --i)
		{
			unsigned int hex_digits = m_array_ptr[i];

			for (int iShift = 28; iShift >= 0; iShift -= 4)
			{
				number_string += DIGIT_ARRAY[((hex_digits >> iShift) & 0x0F)];
			}
		}

		StripLeadingZeroDigits(number_string, '0');

		return;
	}

	void NBigInt::StripLeadingZeroDigits(std::string & number_string,
		char zero_digit) const
	{
		int start_position = 0;
		int digit_length = number_string.length();

		for (int index = 0; index < digit_length - 1; ++index)
		{
			if (number_string[index] == zero_digit)
			{
				++start_position;
			}
			else
			{
				break;
			}
		}

		if (start_position != 0)
		{
			if (start_position > 0)
			{
				number_string = number_string.substr(start_position);
			}
			else
			{
				number_string = number_string.substr(digit_length - 1);
			}
		}

		return;
	}
	
	bool NBigInt::SetValueWithBase8String(const char* base8_digits_ptr)
	{
		size_t digit_length = ::strlen(base8_digits_ptr);

		std::string digits_string = base8_digits_ptr;

		char* digit_array_ptr = const_cast<char*>(digits_string.data());
		digit_length = (unsigned int)(digits_string.length());

		bool success_flag = false;

		for (int i = 0; i < (int)(digit_length); ++i)
		{
			char digit = digit_array_ptr[i];

			success_flag = ((digit >= '0') && (digit < '8'));

			if (success_flag)
			{
				digit_array_ptr[i] = digit - '0';
			}
			else
			{
				break;
			}
		}

		if (success_flag)
		{
			StripLeadingZeroDigits(digits_string, 0);
			SetValueWithBase8DigitValues(digits_string);
		}

		return success_flag;
	}

	void NBigInt::SetValueWithBase8DigitValues(const std::string & base8_digit_string)
	{
		unsigned int number_of_digits = base8_digit_string.length();
		unsigned int current_bit_position_plus_one = 3 * number_of_digits;
		unsigned int integer_length = (current_bit_position_plus_one + (INTEGER_BIT_COUNT - 1)) / INTEGER_BIT_COUNT;

		SetIntegerLength(integer_length);

		current_bit_position_plus_one -= 3;
		unsigned int array_index = integer_length - 1;

		for (unsigned int octal_digit_index = 0; octal_digit_index < number_of_digits; ++octal_digit_index)
		{
	#ifdef INT_BIT_LENGTH_IS_POWER_OF_TWO
			unsigned int shift_value = current_bit_position_plus_one & (INTEGER_BIT_COUNT - 1);
	#else
			unsigned int shift_value = current_bit_position_plus_one % INTEGER_BIT_COUNT;
	#endif
			current_bit_position_plus_one -= 3;

			unsigned int octal_digit = 0;

			switch (shift_value)
			{
			case 0:
			case 1:
			case 2:
			{
				octal_digit = (unsigned int)(base8_digit_string[octal_digit_index]);
				m_array_ptr[array_index] |= octal_digit << shift_value;
			}

			--array_index;
			break;

			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
			{
				octal_digit = (unsigned int)(base8_digit_string[octal_digit_index]);
				m_array_ptr[array_index] |= octal_digit << shift_value;
			}

			break;

			case 30:
			{
				octal_digit = (unsigned int)(base8_digit_string[octal_digit_index]);
				m_array_ptr[array_index] |= (octal_digit & 3) << 30;

				if (array_index + 1 < integer_length)
				{
					m_array_ptr[array_index + 1] |= (octal_digit & 4) >> 2;
				}
			}

			break;

			case 31:
			{
				octal_digit = (unsigned int)(base8_digit_string[octal_digit_index]);
				m_array_ptr[array_index] |= (octal_digit & 1) << 31;

				if (array_index + 1 < integer_length)
				{
					m_array_ptr[array_index + 1] |= ((octal_digit & 6) >> 1);
				}
			}

			break;

			default:

				break;
			}
		}

		return;
	}

	bool NBigInt::SetValueWithBase10String(const char* digits_ptr)
	{
		std::string base8_digit_string;

		bool success_flag = ConvertDecimalStringToOctalDigits(digits_ptr, base8_digit_string);

		if (success_flag)
		{
			SetValueWithBase8DigitValues(base8_digit_string);
		}

		return success_flag;
	}

	bool NBigInt::ConvertDecimalStringToOctalDigits(const char* decimal_digits_ptr, std::string & digits_string) const
	{
		size_t digit_length = ::strlen(decimal_digits_ptr);

		digits_string = decimal_digits_ptr;

		unsigned int padding = ((200 * digit_length) / 1000) + 1;

		char* padding_ptr = new char[padding];

		if (padding_ptr == 0)
		{
			throw NBigIntException("Memory allocation failed");
		}

		for (unsigned int i = 0; i < padding; ++i)
		{
			padding_ptr[i] = 0;
		}

		digits_string.insert(0, padding_ptr, padding);

		delete[] padding_ptr;

		digit_length = (unsigned int)(digits_string.length());
		char* digit_array_ptr = const_cast<char*>(digits_string.data());

		bool success_flag = false;

		unsigned int i = 0;

		for (i = padding; i < digit_length; ++i)
		{
			char digit = digit_array_ptr[i];

			success_flag = ::isdigit(digit) != 0;

			if (success_flag)
			{
				digit_array_ptr[i] = digit - '0';
			}
			else
			{
				break;
			}
		}

		if (success_flag)
		{
			char* addend_ptr = new char[digit_length + 1];

			if (addend_ptr == 0)
			{
				throw NBigIntException("Memory allocation failed");
			}

			for (unsigned int k = 0; k < digit_length - 1; ++k)
			{
				unsigned int j = 0;

				for (j = k + 1; (int)(j) >= 0; --j)
				{
					addend_ptr[j] = 0;
				}

				for (j = k; (int)(j) >= 0; --j)
				{
					char doubled_digit = digit_array_ptr[j] << 1;

					if (doubled_digit > 7)
					{
						addend_ptr[j + 1] += doubled_digit - 8;
						addend_ptr[j] += 1;
					}
					else
					{
						addend_ptr[j + 1] += doubled_digit;
					}
				}

				for (unsigned int m = k + 1; (int)(m) >= 0; --m)
				{
					char sum = digit_array_ptr[m] + addend_ptr[m];

					if (sum > 7)
					{
						digit_array_ptr[m] = sum - 8;

						if ((int)(m - 1) >= 0)
						{
							digit_array_ptr[m - 1] += 1;
						}
					}
					else
					{
						digit_array_ptr[m] = sum;
					}
				}
			}

			delete[] addend_ptr;

			unsigned int start_position = 0;

			for (unsigned int i = 0; i < digits_string.length(); ++i)
			{
				if ((digits_string[i] != 0) || (i == digits_string.length() - 1))
				{
					start_position = i;
					break;
				}
			}

			if (start_position != 0)
			{
				digits_string = digits_string.substr(start_position);
			}
		}

		return success_flag;
	}
	
	bool NBigInt::SetValueWithBase16String(const char* digits_ptr)
	{
		bool success_flag = true;
		std::string hex_number_string = digits_ptr;

		unsigned int number_of_digits = hex_number_string.length();
		char* hex_digits_ptr = const_cast<char*>(hex_number_string.data());

		for (unsigned int i = 0; i < number_of_digits; ++i)
		{
			int digit = (int)(hex_digits_ptr[i]);

			success_flag = ::isxdigit(digit) != 0;

			if (success_flag)
			{
				if (::isdigit(digit))
				{
					hex_digits_ptr[i] = (char)(digit - '0');
				}
				else
				{
					hex_digits_ptr[i] = (char)(::toupper(digit)) + 10 - 'A';
				}
			}
			else
			{
				break;
			}
		}

		if (success_flag)
		{
			StripLeadingZeroDigits(hex_number_string, 0);
			SetValueWithBase16DigitValues(hex_number_string);
		}

		return success_flag;
	}

	void NBigInt::SetValueWithBase16DigitValues(const std::string& base16_digit_values_string)
	{
		unsigned int number_of_digits = base16_digit_values_string.length();
		unsigned int integer_length = (number_of_digits + 7) >> 3;

		SetIntegerLength(integer_length);
		
		unsigned int array_index = integer_length - 1;
		unsigned int current_digit_index = 0;
		unsigned int extra_digits = number_of_digits - ((integer_length - 1) << 3);
		unsigned int hex_digit;

		switch (extra_digits)
		{
		case 7:
		{
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 24;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 20;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 16;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 12;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 8;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 4;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index--] |= hex_digit;
		}

		break;

		case 6:
		{
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 20;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 16;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 12;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 8;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 4;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index--] |= hex_digit;
		}

		break;

		case 5:
		{
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 16;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 12;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 8;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 4;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index--] |= hex_digit;
		}

		break;

		case 4:
		{
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 12;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 8;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 4;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index--] |= hex_digit;
		}

		break;

		case 3:
		{
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 8;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 4;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index--] |= hex_digit;
		}

		break;

		case 2:
		{
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index] |= hex_digit << 4;
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index--] |= hex_digit;
		}

		break;

		case 1:
		{
			hex_digit = base16_digit_values_string[current_digit_index++];
			m_array_ptr[array_index--] |= hex_digit;
		}

		break;

		case 0:
		default:

			break;
		}

		if (number_of_digits > 7)
		{
			for (unsigned int hex_digitIndex = current_digit_index;
				hex_digitIndex < number_of_digits;
				hex_digitIndex += 8)
			{
				unsigned int hex_digit_0 = base16_digit_values_string[hex_digitIndex];
				unsigned int hex_digit_1 = base16_digit_values_string[hex_digitIndex + 1];
				unsigned int hex_digit_2 = base16_digit_values_string[hex_digitIndex + 2];
				unsigned int hex_digit_3 = base16_digit_values_string[hex_digitIndex + 3];
				unsigned int hex_digit_4 = base16_digit_values_string[hex_digitIndex + 4];
				unsigned int hex_digit_5 = base16_digit_values_string[hex_digitIndex + 5];
				unsigned int hex_digit_6 = base16_digit_values_string[hex_digitIndex + 6];
				unsigned int hex_digit_7 = base16_digit_values_string[hex_digitIndex + 7];
				m_array_ptr[array_index--] =
					(hex_digit_0 << 28) | (hex_digit_1 << 24) |
					(hex_digit_2 << 20) | (hex_digit_3 << 16) |
					(hex_digit_4 << 12) | (hex_digit_5 << 8) |
					(hex_digit_6 << 4) | hex_digit_7;
			}
		}

		return;
	}

	NBigInt operator+(const NBigInt& addend_a, const NBigInt& addend_b)
	{
		return NBigInt(addend_a) += addend_b;
	}

	NBigInt operator+(const NBigInt& x_addend, int addend)
	{
		return x_addend + NBigInt(addend);
	}

	NBigInt operator+(int addend, const NBigInt& x_addend)
	{
		return x_addend + addend;
	}

	NBigInt operator+(const NBigInt& x_addend, unsigned int addend)
	{
		return x_addend + NBigInt(addend);
	}

	NBigInt operator+(unsigned int addend, const NBigInt& x_addend)
	{
		return x_addend + addend;
	}

	NBigInt operator-(const NBigInt& minuend, const NBigInt& subtrahend)
	{
		return NBigInt(minuend) -= subtrahend;
	}

	NBigInt operator-(const NBigInt& minuend, int subtrahend)
	{
		return minuend - NBigInt(subtrahend);
	}

	NBigInt operator-(int minuend, const NBigInt& subtrahend)
	{
		return NBigInt(minuend) - subtrahend;
	}
	
	NBigInt operator-(const NBigInt& minuend, unsigned int subtrahend)
	{
		return minuend - NBigInt(subtrahend);
	}

	NBigInt operator-(unsigned int minuend, const NBigInt& subtrahend)
	{
		return NBigInt(minuend) - subtrahend;
	}

	NBigInt operator*(const NBigInt& multiplier_a, const NBigInt& multiplier_b)
	{
		return NBigInt(multiplier_a) *= multiplier_b;
	}

	NBigInt operator*(const NBigInt& x_multiplier, int multiplier)
	{
		return x_multiplier * NBigInt(multiplier);
	}

	NBigInt operator*(int multiplier, const NBigInt& x_multiplier)
	{
		return x_multiplier * multiplier;
	}

	NBigInt operator*(const NBigInt& x_multiplier, unsigned int multiplier)
	{
		return x_multiplier * NBigInt(multiplier);
	}

	NBigInt operator*(unsigned int multiplier, const NBigInt& x_multiplier)
	{
		return x_multiplier * multiplier;
	}

	NBigInt operator/(const NBigInt& x_dividend, const NBigInt& x_denominator)
	{
		return NBigInt(x_dividend) /= x_denominator;
	}
	
	NBigInt operator/(const NBigInt& x_dividend, int divisor)
	{
		return x_dividend / NBigInt(divisor);
	}

	NBigInt operator/(int dividend, const NBigInt& x_denominator)
	{
		return NBigInt(dividend) / x_denominator;
	}

	NBigInt operator/(const NBigInt& x_dividend, unsigned int divisor)
	{
		return x_dividend / NBigInt(divisor);
	}

	NBigInt operator/(unsigned int dividend, const NBigInt& x_denominator)
	{
		return NBigInt(dividend) / x_denominator;
	}

	NBigInt operator<<(const NBigInt& value, const NBigInt& x_shift_count)
	{
		return NBigInt(value) <<= x_shift_count;
	}

	NBigInt operator<<(const NBigInt& value, int shift_count)
	{
		return value << NBigInt(shift_count);
	}

	NBigInt operator<<(int value, const NBigInt& x_shift_count)
	{
		return NBigInt(value) << x_shift_count;
	}

	NBigInt operator<<(const NBigInt& value, unsigned int shift_count)
	{
		return value << NBigInt(shift_count);
	}

	NBigInt operator<<(unsigned int value, const NBigInt& x_shift_count)
	{
		return NBigInt(value) << x_shift_count;
	}

	NBigInt operator>>(const NBigInt& value, const NBigInt& x_shift_count)
	{
		return NBigInt(value) >>= x_shift_count;
	}

	NBigInt operator>>(const NBigInt& value, int shift_count)
	{
		return value >> NBigInt(shift_count);
	}

	NBigInt operator>>(int value, const NBigInt& x_shift_count)
	{
		return NBigInt(value) >> x_shift_count;
	}
	
	NBigInt operator>>(const NBigInt& value, unsigned int shift_count)
	{
		return value >> NBigInt(shift_count);
	}

	NBigInt operator>>(unsigned int value, const NBigInt& x_shift_count)
	{
		return NBigInt(value) >> x_shift_count;
	}

	NBigInt operator%(const NBigInt& x_dividend, const NBigInt& x_denominator)
	{
		return NBigInt(x_dividend) %= x_denominator;
	}

	NBigInt operator%(const NBigInt& x_dividend, int divisor)
	{
		return x_dividend % NBigInt(divisor);
	}

	NBigInt operator%(int dividend, const NBigInt& x_denominator)
	{
		return NBigInt(dividend) % x_denominator;
	}

	NBigInt operator%(const NBigInt& x_dividend, unsigned int divisor)
	{
		return x_dividend % NBigInt(divisor);
	}

	NBigInt operator%(unsigned int dividend, const NBigInt& x_denominator)
	{
		return NBigInt(dividend) % x_denominator;
	}

	NBigInt operator^(const NBigInt& value_a, const NBigInt& value_b)
	{
		return NBigInt(value_a) ^= value_b;
	}
	
	NBigInt operator^(const NBigInt& x_value, int value)
	{
		return x_value % NBigInt(value);
	}

	NBigInt operator^(int value, const NBigInt& x_value)
	{
		return x_value % value;
	}
	
	NBigInt operator^(const NBigInt& x_value, unsigned int value)
	{
		return x_value % NBigInt(value);
	}

	NBigInt operator^(unsigned int value, const NBigInt& x_value)
	{
		return x_value % value;
	}

	NBigInt operator&(const NBigInt& value_a, const NBigInt& value_b)
	{
		return NBigInt(value_a) &= value_b;
	}

	NBigInt operator&(const NBigInt& x_value, int value)
	{
		return x_value & NBigInt(value);
	}

	NBigInt operator&(int value, const NBigInt& x_value)
	{
		return x_value & value;
	}

	NBigInt operator&(const NBigInt& x_value, unsigned int value)
	{
		return x_value & NBigInt(value);
	}

	NBigInt operator&(unsigned int value, const NBigInt& x_value)
	{
		return x_value & value;
	}

	NBigInt operator|(const NBigInt& value_a, const NBigInt& value_b)
	{
		return NBigInt(value_a) |= value_b;
	}
	
	NBigInt operator|(const NBigInt& x_value, int value)
	{
		return x_value | NBigInt(value);
	}

	NBigInt operator|(int value, const NBigInt& x_value)
	{
		return x_value | value;
	}

	NBigInt operator|(const NBigInt& x_value, unsigned int value)
	{
		return x_value | NBigInt(value);
	}

	NBigInt operator|(unsigned int value, const NBigInt& x_value)
	{
		return x_value | value;
	}
}