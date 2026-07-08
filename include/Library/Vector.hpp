#pragma once
#include <vector>
#include <list>
#include <memory>


namespace QuoteList
{
	struct Vector
	{
		template <typename T>
		static std::vector<T*> ListToVector(const std::list<std::unique_ptr<T>>& list)
		{
			std::vector<T*> destVector;
			destVector.reserve(list.size());

			for (const std::unique_ptr<T>& ptr : list)
			{
				if (ptr)
				{
					destVector.push_back(ptr.get());
				}
			}

			return destVector;
		}


		template <typename T>
		static std::vector<T> PtrVectorToValues(const std::vector<T*>& vec)
		{
			std::vector<T> destVector;
			destVector.reserve(vec.size());

			for (const T* ptr : vec)
			{
				destVector.push_back(*ptr);
			}

			return destVector;
		}
	};
}
