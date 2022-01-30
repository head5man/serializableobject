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

#include "Serializable.h"
using namespace std;

namespace serializable
{

/// <summary>
/// Serializer defines interface class to serialize Serializable data
/// </summary>
class Serializer
{
public:
    /// <summary>
    /// Identifier of serializer implementation
    /// </summary>
    string m_id;

    /// <summary>
    /// Serializes the serializable
    /// </summary>
    /// <param name="serializable">Serializable data</param>
    /// <param name="value">serialized value of serializable</param>
    /// <returns>success = 0</returns>
    int Serialize(const Serializable& serializable, string& value);
    
    /// <summary>
    /// Serializer implementation implements this function
    /// allowing individual members to be serialized
    /// </summary>
    /// <param name="member">member to be serialized</param>
    /// <param name="value">serialized value of member</param>
    /// <returns>success = 0</returns>
    virtual int SerializeMember(const Serializable::member_t& member, string& value) = 0;
};

}
