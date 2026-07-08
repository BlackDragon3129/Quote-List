#pragma once
#include <iostream>
#include <type_traits>


namespace QuoteList
{
	struct Math
	{
		template<typename T>
		static T Clamp(const T& val, const T& min, const T& max)
		{
			static_assert(std::is_arithmetic_v<T>, "Math::Clamp T must be a number type");

			if (val < min)
				return min;
			else if (val > max)
				return max;
			return val;
		}

		template<typename T>
		static T ClampReverse(const T& val, const T& min, const T& max)
		{
			static_assert(std::is_arithmetic_v<T>, "Math::Clamp T must be a number type");

			if (val < min)
				return max;
			else if (val > max)
				return min;
			return val;
		}
	};
}
