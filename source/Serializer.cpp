/* Copyright © 2022 Tuomas Lahtinen
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#include "Serializer.h"

using namespace serializable;

int Serializer::Serialize(const Serializable& serializabledata, string& value)
{
	int ret = 0;
	try
	{
		stringstream ss;
		for (size_t i = 0; i < serializabledata.m_members.size(); i++)
		{
			string value{};
			Serializable::member_t member = serializabledata.m_members.at(i);
			int error = SerializeMember(member, value);
			if (!error)
			{
				ss << value;
			}
			else ret = -1;
			//TODO log error
		}
		value = ss.str();
	}
	catch (...) { ret = -2; }

	return ret;
}
