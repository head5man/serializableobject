#pragma once

#include <limits>
#include "CppUnitTest.h"
#include "pch.h"

#include "../../source/Serializable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace serializable;

namespace TestClasses
{
	class SerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("bool", &m_bool, typeid(bool)),
			member_t("int", &m_int, typeid(int)),
			member_t("double", &m_double, typeid(double)),
			member_t("string", &m_string, typeid(string))
		};
	public:
		bool m_bool{ false };
		int m_int{ -1 };
		double m_double{ std::numeric_limits<double>::quiet_NaN() };
		string m_string{};

		SerializableObject()
		{
			m_objectname = __func__;
			InitMembers(members);
		}

		SerializableObject& operator = (const SerializableObject& source)
		{
			this->FromSerializable((Serializable*)&source);
			return *this;
		}

		void SetTestValues(const string& stringvalue = "first")
		{
			m_bool = true;
			m_int = 1;
			m_double = 1.0;
			m_string = stringvalue;
		}

		void VerifyTestValues(const string& stringvalue = "first")
		{
			Assert::IsTrue(m_bool);
			Assert::AreEqual(1, m_int);
			Assert::AreEqual(1.0, m_double);
			Assert::AreEqual(0, m_string.compare(stringvalue));
		}
	};

	class ComplexSerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("serializable", &m_serializable, typeid(Serializable)),
			member_t("bool", &m_bool, typeid(bool)),
			member_t("int", &m_int, typeid(int)),
			member_t("double", &m_double, typeid(double)),
			member_t("string", &m_string, typeid(string))
		};
	public:
		SerializableObject m_serializable{};
		bool m_bool{ false };
		int m_int{ -1 };
		double m_double{ std::numeric_limits<double>::quiet_NaN() };
		string m_string{};

		ComplexSerializableObject()
		{
			m_objectname = __func__;
			InitMembers(members);
		}

		ComplexSerializableObject& operator = (const ComplexSerializableObject& source)
		{
			this->FromSerializable((Serializable*)&source);
			return *this;
		}

		void SetTestValues()
		{
			m_bool = false;
			m_int = 2;
			m_double = 2.0;
			m_string = "second";
		}

		void VerifyTestValues()
		{
			Assert::IsFalse(m_bool);
			Assert::AreEqual(2, m_int);
			Assert::AreEqual(2.0, m_double);
			Assert::AreEqual(0, m_string.compare("second"));
		}
	};

	class TwoComplexSerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("serializable", &m_serializable, typeid(Serializable)),
			member_t("bool", &m_bool, typeid(bool)),
			member_t("int", &m_int, typeid(int)),
			member_t("double", &m_double, typeid(double)),
			member_t("string", &m_string, typeid(string))
		};
	public:
		ComplexSerializableObject m_serializable{};
		bool m_bool{ false };
		int m_int{ -1 };
		double m_double{ std::numeric_limits<double>::quiet_NaN() };
		string m_string{};

		TwoComplexSerializableObject()
		{
			m_objectname = __func__;
			InitMembers(members);
		}

		TwoComplexSerializableObject& operator = (const TwoComplexSerializableObject& source)
		{
			this->FromSerializable((Serializable*)&source);
			return *this;
		}

		void SetTestValues()
		{
			m_bool = true;
			m_int = 3;
			m_double = 3.0;
			m_string = "third";
		}

		void VerifyTestValues()
		{
			Assert::IsTrue(m_bool);
			Assert::AreEqual(3, m_int);
			Assert::AreEqual(3.0, m_double);
			Assert::AreEqual(0, m_string.compare("third"));
		}
	};

	class VectorIntSerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("vectorint", &m_vectorint, typeid(int), (unsigned)SerializableFlags::FlagVector)
		};
	public:
		vector<int> m_vectorint{};

		void SetTestValues()
		{
			for (int i = 0; i < 10; i++)
				m_vectorint.push_back(i);
		}

		void VerifyTestValues()
		{
			for (int i = 0; i < 10; i++)
				Assert::AreEqual(i, m_vectorint.at(i));
		}

		VectorIntSerializableObject()
		{
			m_objectname = __func__;
			InitMembers(members);
		}

		VectorIntSerializableObject& operator = (const VectorIntSerializableObject& source)
		{
			this->FromSerializable((Serializable*)&source);
			return *this;
		}
	};

	class VectorDoubleSerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("vectordouble", &m_vectordouble, typeid(double), (unsigned)SerializableFlags::FlagVector)
		};
	public:
		vector<double> m_vectordouble{};

		void SetTestValues()
		{
			for (double i = 0; i < 10; i++)
				m_vectordouble.push_back(i / 10);
		}

		void VerifyTestValues()
		{
			for (double i = 0; i < 10; i++)
				Assert::AreEqual(i / 10, m_vectordouble.at((size_t)i));
		}

		VectorDoubleSerializableObject()
		{
			m_objectname = __func__;
			InitMembers(members);
		}

		VectorDoubleSerializableObject& operator = (const VectorDoubleSerializableObject& source)
		{
			this->FromSerializable((Serializable*)&source);
			return *this;
		}
	};

	class VectorBoolSerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("vectorbool", &m_vectorbool, typeid(bool), (unsigned)SerializableFlags::FlagVector)
		};
	public:
		vector<bool> m_vectorbool{};

		void SetTestValues()
		{
			for (int i = 0; i < 10; i++)
				m_vectorbool.push_back((bool)((i & 1) != 0));
		}

		void VerifyTestValues()
		{
			for (int i = 0; i < 10; i++)
			{
				bool value = m_vectorbool.at(i);
				Assert::AreEqual((bool)((i & 1) != 0), (bool)m_vectorbool.at(i));
			}
		}

		VectorBoolSerializableObject()
		{
			m_objectname = __func__;
			InitMembers(members);
		}

		VectorBoolSerializableObject& operator = (const VectorBoolSerializableObject& source)
		{
			this->FromSerializable((Serializable*)&source);
			return *this;
		}
	};

	class VectorStringSerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("vectorstring", &m_vectorstring, typeid(string), (unsigned)SerializableFlags::FlagVector)
		};
	public:
		vector<string> m_vectorstring{};

		void SetTestValues()
		{
			for (int i = 0; i < 10; i++)
			{
				stringstream ss;
				ss << "stringvalue" << i;
				m_vectorstring.push_back(ss.str());
			}
		}

		void VerifyTestValues()
		{
			for (int i = 0; i < 10; i++)
			{
				stringstream ss;
				ss << "stringvalue" << i;
				Assert::AreEqual(0, m_vectorstring.at(i).compare(ss.str()));
			}
		}

		VectorStringSerializableObject()
		{
			m_objectname = __func__;
			InitMembers(members);
		}

		VectorStringSerializableObject& operator = (const VectorStringSerializableObject& source)
		{
			this->FromSerializable((Serializable*)&source);
			return *this;
		}
	};

	class VectorSerializableSerializableObject : public Serializable
	{
		const vector<member_t> members{
			member_t("vectorserializable", &m_vectorserializable, typeid(Serializable), (unsigned)SerializableFlags::FlagVector)
		};
		vector<SerializableObject> m_vectorserializable;
	public:
		void SetTestValues()
		{
			for (int i = 0; i < 10; i++)
			{
				SerializableObject serializable;
				stringstream ss;
				ss << "stringvalue" << i;
				serializable.SetTestValues(ss.str());
				m_vectorserializable.push_back(serializable);
			}
		}

		void VerifyTestValues()
		{
			for (int i = 0; i < 10; i++)
			{
				SerializableObject* serializable = &m_vectorserializable[i];
				Assert::IsNotNull(serializable);
				stringstream ss;
				ss << "stringvalue" << i;
				serializable->VerifyTestValues(ss.str());
			}
		}
	};
}
