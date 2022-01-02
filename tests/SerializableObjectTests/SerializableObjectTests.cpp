#include "pch.h"
#include "CppUnitTest.h"
#include "SerializableTestClasses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SerializableObject
{
	TEST_CLASS(Members)
	{
	public:
		TEST_METHOD(DeclareSerializableObjectGetValuesExpectTrue)
		{
			TestClasses::SerializableObject serializable;
			bool _bool;
			string _string;
			double _double;
			int _int;
			Assert::IsTrue(serializable.GetValue("bool", &_bool));
			Assert::IsTrue(serializable.GetValue("int", &_int));
			Assert::IsTrue(serializable.GetValue("double", &_double));
			Assert::IsTrue(serializable.GetValue("string", &_string));
		}

		TEST_METHOD(DeclareSerializableObjectSetValuesGetValuesExpectSetValues)
		{
			TestClasses::SerializableObject serializable;
			bool bool_ = true, _bool;
			string string_ = "stringvalue", _string;
			double double_ = 1234.5678, _double;
			int int_ = 100, _int;
			serializable.SetValue("bool", &bool_);
			Assert::IsTrue(serializable.GetValue("bool", &_bool));
			Assert::IsTrue(_bool);

			serializable.SetValue("int", &int_);
			Assert::IsTrue(serializable.GetValue("int", &_int));
			Assert::AreEqual(100, _int);

			serializable.SetValue("double", &double_);
			Assert::IsTrue(serializable.GetValue("double", &_double));
			Assert::AreEqual(1234.5678, _double);

			serializable.SetValue("string", &string_);
			Assert::IsTrue(serializable.GetValue("string", &_string));
			Assert::AreEqual("stringvalue", _string.c_str());
		}

		TEST_METHOD(DeclareComplexSerializableObjectGetValuesExpectSetValues)
		{
			TestClasses::SerializableObject simple;
			TestClasses::ComplexSerializableObject complex;

			simple.SetTestValues();
			complex.SetValue("serializable", (Serializable*)&simple);

			TestClasses::SerializableObject* serializable = (TestClasses::SerializableObject*)complex["serializable"];
			Assert::IsNotNull(serializable);

			serializable->VerifyTestValues();
		}

		TEST_METHOD(CopyComplexSerializableGetValuesExpectTheSame)
		{
			TestClasses::ComplexSerializableObject complex;

			complex.m_serializable.SetTestValues();

			TestClasses::ComplexSerializableObject copy = complex;

			TestClasses::SerializableObject* serializable = (TestClasses::SerializableObject*)copy["serializable"];
			Assert::IsNotNull(serializable);

			serializable->VerifyTestValues();
		}

		TEST_METHOD(CopyTwoComplexSerializableGetValuesExpectTheSame)
		{
			TestClasses::SerializableObject simple;
			TestClasses::ComplexSerializableObject complex;
			TestClasses::TwoComplexSerializableObject twocomplex;
			
			simple.SetTestValues();
			complex.SetTestValues();
			twocomplex.SetTestValues();

			complex.SetValue("serializable", (Serializable*)&simple);
			twocomplex.SetValue("serializable", (Serializable*)&complex);

			TestClasses::TwoComplexSerializableObject twocomplexcopy = twocomplex;

			TestClasses::ComplexSerializableObject* complex_reference = (TestClasses::ComplexSerializableObject*)twocomplexcopy["serializable"];
			Assert::IsNotNull(complex_reference);
			TestClasses::SerializableObject* simple_reference = (TestClasses::SerializableObject*)(*complex_reference)["serializable"];
			Assert::IsNotNull(simple_reference);
			twocomplexcopy.VerifyTestValues();
			complex_reference->VerifyTestValues();
			simple_reference->VerifyTestValues();
		}

		TEST_METHOD(DeclareVectorObjectsSetTestValuesCopyVectorObjectsVerifyTestValues)
		{
			TestClasses::VectorIntSerializableObject vectorint;
			TestClasses::VectorBoolSerializableObject vectorbool;
			TestClasses::VectorDoubleSerializableObject vectordouble;
			TestClasses::VectorStringSerializableObject vectorstring;
			TestClasses::VectorSerializableSerializableObject vectorserializable;
			vectorint.SetTestValues();
			vectorbool.SetTestValues();
			vectordouble.SetTestValues();
			vectorstring.SetTestValues();
			vectorserializable.SetTestValues();
			TestClasses::VectorIntSerializableObject copyint = vectorint;
			TestClasses::VectorBoolSerializableObject copybool = vectorbool;
			TestClasses::VectorDoubleSerializableObject copydouble = vectordouble;
			TestClasses::VectorStringSerializableObject copystring = vectorstring;
			TestClasses::VectorSerializableSerializableObject copyserializable = vectorserializable;
			copyint.VerifyTestValues();
			copybool.VerifyTestValues();
			copydouble.VerifyTestValues();
			copystring.VerifyTestValues();
			copyserializable.VerifyTestValues();
		}

		TEST_METHOD(AllocateVectorObjectsSetTestValuesCopyVectorObjectsDeleteVectorObjectsVerifyTestValues)
		{
			TestClasses::VectorIntSerializableObject* vectorint = new TestClasses::VectorIntSerializableObject();
			TestClasses::VectorBoolSerializableObject* vectorbool = new TestClasses::VectorBoolSerializableObject();
			TestClasses::VectorDoubleSerializableObject* vectordouble = new TestClasses::VectorDoubleSerializableObject();
			TestClasses::VectorStringSerializableObject* vectorstring = new TestClasses::VectorStringSerializableObject();
			TestClasses::VectorSerializableSerializableObject* vectorserializable = new TestClasses::VectorSerializableSerializableObject();
			Assert::IsNotNull(vectorint);
			Assert::IsNotNull(vectorbool);
			Assert::IsNotNull(vectordouble);
			Assert::IsNotNull(vectorstring);
			Assert::IsNotNull(vectorserializable);
			vectorint->SetTestValues();
			vectorbool->SetTestValues();
			vectordouble->SetTestValues();
			vectorstring->SetTestValues();
			vectorserializable->SetTestValues();
			TestClasses::VectorIntSerializableObject copyint = *vectorint;
			TestClasses::VectorBoolSerializableObject copybool = *vectorbool;
			TestClasses::VectorDoubleSerializableObject copydouble = *vectordouble;
			TestClasses::VectorStringSerializableObject copystring = *vectorstring;
			TestClasses::VectorSerializableSerializableObject copyserializable = *vectorserializable;
			delete vectorint;
			delete vectorbool;
			delete vectordouble;
			delete vectorstring;
			delete vectorserializable;
			vectorint = nullptr;
			vectorbool = nullptr;
			vectordouble = nullptr;
			vectorstring = nullptr;
			vectorserializable = nullptr;

			copyint.VerifyTestValues();
			copybool.VerifyTestValues();
			copydouble.VerifyTestValues();
			copystring.VerifyTestValues();
			copyserializable.VerifyTestValues();
		}
	};
}
