/* Copyright © 2022 Tuomas Lahtinen
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#pragma once

#include <string>
#include "Serializable.h"
#include "ExceptionHelper.h"

using namespace std;

namespace serializable
{
class DeSerializer
{
public:
    /// <summary>
    /// Identifier of DeSerializer implementation
    /// </summary>
    string m_id;

    /// <summary>
    /// Serializes the serializable
    /// </summary>
    /// <param name="serializable">Serializable data</param>
    /// <param name="data">serialized value of serializable</param>
    /// <returns>success = 0</returns>
    int DeSerialize(Serializable& serializable, const string& data);

    /// <summary>
    /// Serializes the serializable
    /// </summary>
    /// <param name="serializable">Serializable data</param>
    /// <param name="data">parsed intermediate object</param>
    /// <returns>success = 0</returns>
    int DeSerialize(Serializable& serializable, void* data);

    /// <summary>
    /// Implementation dependent member data getter
    /// </summary>
    virtual void* GetMemberData(const Serializable::member_t&, void*) = 0;

    /// <summary>
    /// DeSerializer implementation implements this function
    /// allowing individual members to be DeSerialized
    /// </summary>
    /// <param name="member">member to be serialized</param>
    /// <param name="value">parsed intermediate object</param>
    /// <returns>success = 0</returns>
    virtual int DeSerializeMember(Serializable::member_t& member, void*) = 0;

    /// <summary>
    /// Parse implementation dependent intermediate object from string
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    virtual void* Parse(const string& value) { throw Exceptions::NotImplementedException("Implement function"); };

    virtual void Release(void*) { throw Exceptions::NotImplementedException("Implement function"); }
};
}

