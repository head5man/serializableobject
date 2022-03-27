#include "DeSerializer.h"
#include "ExceptionHelper.h"
#include "Enums.h"
#include "Utils.h"


namespace serializable
{
	int DeSerializer::DeSerialize(Serializable& serializable, const string& value)
	{
		int ret = -1;
		void* obj =  Parse(value);
		if (obj)
		{
			try
			{
				ret = DeSerialize(serializable, obj);
				Release(obj);
			}
			catch (...) 
			{
				Release(obj);
				rethrow_exception(std::current_exception());
			}
		}
		return ret;
	}

	int DeSerializer::DeSerialize(Serializable& serializable, void* data)
	{
		int ret = 0;
		for (size_t i = 0; i < serializable.m_members.size(); i++)
		{
			Serializable::member_t member = serializable.m_members.at(i);
			void* memberdata = GetMemberData(member, data);
			if (memberdata)
			{
				int error = DeSerializeMember(member, data);
				if (error)
				{
					//TODO log error
					if ((member.m_flags & (unsigned int)enums::SerializableFlags::FlagOptional) == 0)
					{
						throw Exceptions::InvalidArgument(utils::string_sprintf("Error(%d) while handling a required member: %s", error , member.m_tag.c_str()));
					}
				}
			}
			else if ((member.m_flags & (unsigned int)enums::SerializableFlags::FlagOptional) == 0)
			{
				throw Exceptions::InvalidArgument(utils::string_sprintf("Required member(%s) undefined", member.m_tag.c_str()));
			}
		}
		return ret;
	}
}