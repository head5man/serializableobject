#pragma once
#include <stdexcept>
#include <exception>
#include <iostream>
#include <string>




namespace Exceptions
{
	namespace Helpers
	{
		std::string what(const std::exception_ptr& eptr = std::current_exception())
		{
			if (!eptr) { throw Exceptions::BadException(); }

			try { std::rethrow_exception(eptr); }
			catch (const Exceptions::Exception& e) { return e.what(); }
			catch (const std::string& e) { return e; }
			catch (const char* e) { return e; }
			catch (...) { return "who knows"; }
		}
	}

	/// <summary>
	/// An exception and parent class of all the standard C++ exceptions.
	/// </summary>
	typedef std::exception Exception;
	
	/// <summary>
	/// This can be thrown by new.
	/// </summary>
	typedef std::bad_alloc BadAlloc;
	
	/// <summary>
	/// This can be thrown by dynamic_cast.
	/// </summary>
	//typedef std::bad_cast std_bad_cast;

	/// <summary>
	/// This is useful device to handle unexpected exceptions in a C++ program
	/// </summary>
	typedef std::bad_exception BadException;

	/// <summary>
	/// This can be thrown by typeid.
	/// </summary>
	//typedef std::bad_typeid std_bad_typeid

	/// <summary>
	/// An exception that theoretically can be detected by reading the code.
	/// </summary>
	typedef std::logic_error LogicError;

	/// <summary>
	/// This is an exception thrown when a mathematically invalid domain is used
	/// </summary>
	typedef std::domain_error DomainError;

	/// <summary>
	/// This is thrown due to invalid arguments.
	/// </summary>
	typedef std::invalid_argument InvalidArgument;

	/// <summary>
	/// This is thrown when a too big std::string is created
	/// </summary>
	typedef std::length_error LengthError;
	
	/// <summary>
	/// This can be thrown by the at method from for example a std::vectorand std::bitset<>::operator[]().
	/// </summary>
	typedef std::out_of_range OutOfRange;

	/// <summary>
	/// An exception that theoretically can not be detected by reading the code.
	/// </summary>
	typedef std::runtime_error RuntimeError;

	/// <summary>
	/// This is thrown if a mathematical overflow occurs.
	/// </summary>
	typedef std::overflow_error OverflowError;

	/// <summary>
	/// This is occured when you try to store a value which is out of range.
	/// </summary>
	typedef std::range_error RangeError;

	/// <summary>
	/// This is thrown if a mathematical underflow occurs.
	/// </summary>
	typedef std::underflow_error UnderflowError;

	class NotImplementedException : public std::exception { public: NotImplementedException(std::string message) :std::exception(message.c_str()) {} };
}
