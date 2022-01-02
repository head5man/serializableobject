/* Copyright © 2022 Tuomas Lahtinen
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#include "Serializable.h"

namespace serializable
{

	/*****************************************************************/

	void Serializable::InitMembers(const vector<member_t>& members)
	{
		m_members.assign(members.begin(), members.end());
	}

	/*****************************************************************/

	template<typename T>
	bool Serializable::GetValue(const string& tag, T* value)
	{
		bool ret = false;
		member_t* member{ nullptr };
		if (GetMember(tag, &member))
		{
			if (member)
			{
				if (0 == member->m_type.compare(typeid(T).name()))
				{
					ret = true;
					T* valref = static_cast<T*>(member->m_reference);
					*value = *valref;
				}
				// If using reference T& and T is a derived class of Serializable.
				// There is no instance of this function.
				/*else if (0 == member->m_type.compare(typeid(Serializable).name()))
				{
					Serializable* pvalue = (Serializable*)&value;
					Serializable* pmember = static_cast<Serializable*>(member->m_reference);
					*pvalue = *pmember;
					ret = true;
				}*/
			}
		}
		return ret;
	}
	
	/*****************************************************************/

	template<typename T>
	void Serializable::SetValue(const string& tag, T* value)
	{
		member_t* member{ nullptr };
		if (GetMember(tag, &member) && member)
		{
			if (0 == member->m_type.compare(typeid(T).name()))
			{
				T* valref = static_cast<T*>(member->m_reference);
				*valref = *value;
			}
			// If using reference T& and T is a derived class of Serializable.
			// There is no instance of this function.
			/*else if (0 == member->m_type.compare(typeid(Serializable).name()))
			{
				Serializable* pvalue = (Serializable*)value;
				Serializable* pmember = static_cast<Serializable*>(member->m_reference);
				*pmember = *pvalue;
			}*/
		}
	}

	// Opting to do single compilation of this source. 
	// Keeping the declarations away from the header. 
	// This requires handling derived classes via cast (Serializable*)&DerivedSerializable.
	// Other solution is to move all code to header and compile 
	// as part of derived class.
	template bool Serializable::GetValue<int>(const string&, int*);
	template bool Serializable::GetValue<bool>(const string&, bool*);
	template bool Serializable::GetValue<double>(const string&, double*);
	template bool Serializable::GetValue<string>(const string&, string*);
	template bool Serializable::GetValue<Serializable>(const string&, Serializable*);

	template void Serializable::SetValue<int>(const string&, int*);
	template void Serializable::SetValue<bool>(const string&, bool*);
	template void Serializable::SetValue<double>(const string&, double*);
	template void Serializable::SetValue<string>(const string&, string*);
	template void Serializable::SetValue<Serializable>(const string&, Serializable*);

	/*****************************************************************/

	void* Serializable::GetValueReference(const string& tag)
	{
		return (*this)[tag];
	}

	/*****************************************************************/

	bool Serializable::GetMember(const string& tag, member_t** member)
	{
		bool ret = false;
		for (size_t i = 0; member && i < m_members.size(); i++)
		{
			member_t* item = &m_members.at(i);
			if (0 == item->m_tag.compare(tag))
			{
				ret = true;
				*member = item;
				break;
			}
		}
		return ret;
	}

	/*****************************************************************/

	void Serializable::FromSerializable(Serializable* other)
	{
		for (size_t i = 0; i < other->m_members.size(); i++)
		{
			member_t mi = other->m_members.at(i);
			for (size_t j = 0; j < this->m_members.size(); j++)
			{
				member_t mj = this->m_members.at(j);
				if ((0 == mi.m_tag.compare(mj.m_tag)) && (0 == mi.m_type.compare(mj.m_type)))
				{
					CopyMember(mi, mj);
				}
			}
		}
	}

	/*****************************************************************/

	bool Serializable::CopyMember(member_t& from, member_t& to)
	{
		bool ret = true;
		bool israw = (from.m_flags & (unsigned)SerializableFlags::FlagRaw) != 0;
		bool isvector = (from.m_flags & (unsigned)SerializableFlags::FlagVector) != 0;
		try
		{
			if (isvector)
			{
				CopyVector(from, to, israw);
			}
			else
			{
				if (israw)
				{
					*((string*)to.m_reference) = *((string*)from.m_reference);
				}
				else
				{
					if (0 == from.m_type.compare(typeid(bool).name()))
					{
						*((bool*)to.m_reference) = *((bool*)from.m_reference);
					}
					else if (0 == from.m_type.compare(typeid(int).name()))
					{
						*((int*)to.m_reference) = *((int*)from.m_reference);
					}
					else if (0 == from.m_type.compare(typeid(double).name()))
					{
						*((double*)to.m_reference) = *((double*)from.m_reference);
					}
					else if (0 == from.m_type.compare(typeid(string).name()))
					{
						*((string*)to.m_reference) = *((string*)from.m_reference);
					}
					else if (0 == from.m_type.compare(typeid(Serializable).name()))
					{
						*((Serializable*)to.m_reference) = *((Serializable*)from.m_reference);
					}
					else
					{
						stringstream ss;
						ss << "cannot copy type " << from.m_type << endl;
						throw ss.str().c_str();
					}
				}
			}
		}
		catch (...)
		{
			ret = false;
			// logging ?
		}
		return ret;
	}

	/*****************************************************************/

	bool Serializable::CopyVector(member_t& from, member_t& to, bool israw)
	{
		bool ret = true;
		try
		{
			if (israw)
			{
				*((vector<string>*)to.m_reference) = *((vector<string>*)from.m_reference);
			}
			else
			{
				if (0 == from.m_type.compare(typeid(bool).name()))
				{
					*((vector<bool>*)to.m_reference) = *((vector<bool>*)from.m_reference);
				}
				else if (0 == from.m_type.compare(typeid(int).name()))
				{
					*((vector<int>*)to.m_reference) = *((vector<int>*)from.m_reference);
				}
				else if (0 == from.m_type.compare(typeid(double).name()))
				{
					*((vector<double>*)to.m_reference) = *((vector<double>*)from.m_reference);
				}
				else if (0 == from.m_type.compare(typeid(string).name()))
				{
					*((vector<string>*)to.m_reference) = *((vector<string>*)from.m_reference);
				}
				else if (0 == from.m_type.compare(typeid(Serializable).name()))
				{
					*((vector<Serializable>*)to.m_reference) = *((vector<Serializable>*)from.m_reference);
				}
				else
				{
					stringstream ss;
					ss << "cannot copy type vector<" << from.m_type << ">" << endl;
					throw ss.str().c_str();
				}
			}
		}
		catch (...)
		{
			// logging ?
			ret = false;
		}
		return ret;
	}

}
