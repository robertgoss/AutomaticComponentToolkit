/*++

Copyright (C) 2019 ACT Developers


This file has been generated by the Automatic Component Toolkit (ACT) version 1.6.0-RC1.

Abstract: This is an autogenerated C++ Implementation file with the basic internal
 exception type in order to allow an easy use of Optional Class Library

Interface version: 1.0.0

*/


#include <string>

#include "optclass_interfaceexception.hpp"

/*************************************************************************************************************************
 Class EOptClassInterfaceException
**************************************************************************************************************************/
EOptClassInterfaceException::EOptClassInterfaceException(OptClassResult errorCode)
	: m_errorMessage("OptClass Error " + std::to_string (errorCode))
{
	m_errorCode = errorCode;
}

EOptClassInterfaceException::EOptClassInterfaceException(OptClassResult errorCode, std::string errorMessage)
	: m_errorMessage(errorMessage + " (" + std::to_string (errorCode) + ")")
{
	m_errorCode = errorCode;
}

OptClassResult EOptClassInterfaceException::getErrorCode ()
{
	return m_errorCode;
}

const char * EOptClassInterfaceException::what () const noexcept
{
	return m_errorMessage.c_str();
}
