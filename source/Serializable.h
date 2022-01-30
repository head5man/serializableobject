/* Copyright © 2022 Tuomas Lahtinen
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#pragma once

#include <string>
#include <vector>
#include <typeinfo>
#include <sstream>
#include "Enums.h"
using namespace std;

namespace serializable 
{
/// <summary>
/// Serializable defines a class that can be Serialized/Deserialized
/// </summary>
class Serializable
{
public:
	/// <summary>
	/// defined for each serializable member
	/// </summary>
	struct member_t {
		string m_tag; void* m_reference; string m_type; unsigned m_flags;

		member_t(const string& tag, void* reference, const type_info& type, unsigned flags = (unsigned)SerializableFlags::FlagNone) :
			m_tag(tag), 
			m_reference(reference), 
			m_type(type.name()),
			m_flags(flags)
		{}
	};
		
	/// <summary>
	/// Member definitions initialized by derived class
	/// </summary>
	vector<member_t> m_members{};
	/// <summary>
	/// Classname of derived class if initialized
	/// </summary>
	string m_objectname{""};
		
	/// <summary>
	/// Initialize member definitions in constructor of derived class
	/// </summary>
	/// <param name="members"></param>
	void InitMembers(const vector<member_t>& members);

	/// <summary>
	/// Get value of member
	/// </summary>
	/// <typeparam name="T">type of value</typeparam>
	/// <param name="tag">key</param>
	/// <param name="value">value assigned from member</param>
	/// <returns></returns>
	template<typename T>
	bool GetValue(const string& tag, T* value);

	/// <summary>
	/// Set value of member
	/// </summary>
	/// <typeparam name="T">type of value</typeparam>
	/// <param name="tag">key</param>
	/// <param name="value">typed value</param>
	template<typename T>
	void SetValue(const string& tag, T* value);
	
	/// <summary>
	/// Cannot get typed value for objects inheriting Serializable
	/// NOTE: wouldn't be an issue if Serializable object would allocate memory
	/// instead of using class member references
	/// </summary>
	/// <param name="tag"></param>
	/// <returns>
	/// reference - to memory containing the member value
	/// nullptr - if tag is not found
	/// </returns>
	void* GetValueReference(const string& tag);


	/// <summary>
	/// Copy values from another Serializable using member definitions
	/// </summary>
	/// <param name="other">Serializable</param>
	void FromSerializable(Serializable* other);

	Serializable& operator =(const Serializable& other)
	{
		FromSerializable((Serializable*) &other);
		return *this;
	}

	void* operator [](const string& tag)
	{
		void* ret{ nullptr };
		member_t* member{nullptr};
		GetMember(tag, &member);
		if (member)
		{
			ret = member->m_reference;
		}
		return ret;
	}

private:
	bool GetMember(const string& tag, member_t** member);

	bool CopyMember(member_t& from, member_t& to);

	bool CopyVector(member_t& from, member_t& to, bool israw);
};

}
