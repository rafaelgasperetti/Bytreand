#pragma once

#include <Tools/StringUtils.h>
#include <Tools/Comparable.h>

class VectorUtils
{
	public:
		template<typename T, typename = enable_if<is_base_of<Comparable, T>::value>>
		static bool Exists(T* comp, vector<T*>* v)
		{
			if (comp != NULL)
			{
				for (T* c : (*v))
				{
					if (comp->Equals(c))
					{
						return true;
					}
				}
			}
			return false;
		}

		template<typename T, typename = enable_if<is_base_of<Comparable, T>::value>>
		static int IndexOf(T* comp, vector<T*>* v)
		{
			if (comp != NULL)
			{
				for (int i = 0; i < v->size(); i++)
				{
					if (comp->Equals((*v)[i]))
					{
						return i;
					}
				}
			}
			return -1;
		}

		template<typename T, typename = enable_if<is_base_of<Comparable, T>::value>>
		static int LastIndexOf(T* comp, vector<T*>* v)
		{
			int ret = -1;
			if (comp != NULL)
			{
				for (int i = 0; i < v->size(); i++)
				{
					if (comp->Equals((*v)[i]))
					{
						return ret = i;
					}
				}
			}
			return ret;
		}

		template<typename T, typename = enable_if<is_base_of<Comparable, T>::value>>
		static vector<int> IndexesOf(T* comp, vector<T*>* v)
		{
			vector<int> ret;
			if (comp != NULL)
			{
				for (int i = 0; i < v->size(); i++)
				{
					if (comp->Equals((*v)[i]))
					{
						ret.push_back(i);
					}
				}
			}
			return ret;
		}

		template<typename T>
		static void CopyValues(vector<T*>* from, vector<T*>* to)
		{
			if (from != NULL && to != NULL)
			{
				for (T* f : (*from))
				{
					to->push_back(f);
				}
			}
		}
};