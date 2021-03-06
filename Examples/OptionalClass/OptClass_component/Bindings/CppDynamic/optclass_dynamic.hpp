/*++

Copyright (C) 2019 ACT Developers


This file has been generated by the Automatic Component Toolkit (ACT) version 1.6.0.

Abstract: This is an autogenerated C++-Header file in order to allow an easy
 use of Optional Class Library

Interface version: 1.0.0

*/

#ifndef __OPTCLASS_CPPHEADER_DYNAMIC_CPP
#define __OPTCLASS_CPPHEADER_DYNAMIC_CPP

#include "optclass_types.hpp"
#include "optclass_dynamic.h"


#ifdef _WIN32
#include <windows.h>
#else // _WIN32
#include <dlfcn.h>
#endif // _WIN32
#include <string>
#include <memory>
#include <vector>
#include <exception>

namespace OptClass {

/*************************************************************************************************************************
 Forward Declaration of all classes
**************************************************************************************************************************/
class CWrapper;
class CBase;

/*************************************************************************************************************************
 Declaration of deprecated class types
**************************************************************************************************************************/
typedef CWrapper COptClassWrapper;
typedef CBase COptClassBase;

/*************************************************************************************************************************
 Declaration of shared pointer types
**************************************************************************************************************************/
typedef std::shared_ptr<CWrapper> PWrapper;
typedef std::shared_ptr<CBase> PBase;

/*************************************************************************************************************************
 Declaration of deprecated shared pointer types
**************************************************************************************************************************/
typedef PWrapper POptClassWrapper;
typedef PBase POptClassBase;


/*************************************************************************************************************************
 Class EOptClassException 
**************************************************************************************************************************/
class EOptClassException : public std::exception {
protected:
	/**
	* Error code for the Exception.
	*/
	OptClassResult m_errorCode;
	/**
	* Error message for the Exception.
	*/
	std::string m_errorMessage;

public:
	/**
	* Exception Constructor.
	*/
	EOptClassException(OptClassResult errorCode, const std::string & sErrorMessage)
		: m_errorMessage("OptClass Error " + std::to_string(errorCode) + " (" + sErrorMessage + ")")
	{
		m_errorCode = errorCode;
	}

	/**
	* Returns error code
	*/
	OptClassResult getErrorCode() const noexcept
	{
		return m_errorCode;
	}

	/**
	* Returns error message
	*/
	const char* what() const noexcept
	{
		return m_errorMessage.c_str();
	}

};

/*************************************************************************************************************************
 Class CInputVector
**************************************************************************************************************************/
template <typename T>
class CInputVector {
private:
	
	const T* m_data;
	size_t m_size;
	
public:
	
	CInputVector( const std::vector<T>& vec)
		: m_data( vec.data() ), m_size( vec.size() )
	{
	}
	
	CInputVector( const T* in_data, size_t in_size)
		: m_data( in_data ), m_size(in_size )
	{
	}
	
	const T* data() const
	{
		return m_data;
	}
	
	size_t size() const
	{
		return m_size;
	}
	
};

// declare deprecated class name
template<typename T>
using COptClassInputVector = CInputVector<T>;

/*************************************************************************************************************************
 Class CWrapper 
**************************************************************************************************************************/
class CWrapper {
public:
	
	CWrapper(void* pSymbolLookupMethod)
	{
		CheckError(nullptr, initWrapperTable(&m_WrapperTable));
		CheckError(nullptr, loadWrapperTableFromSymbolLookupMethod(&m_WrapperTable, pSymbolLookupMethod));
		
		CheckError(nullptr, checkBinaryVersion());
	}
	
	CWrapper(const std::string &sFileName)
	{
		CheckError(nullptr, initWrapperTable(&m_WrapperTable));
		CheckError(nullptr, loadWrapperTable(&m_WrapperTable, sFileName.c_str()));
		
		CheckError(nullptr, checkBinaryVersion());
	}
	
	static PWrapper loadLibrary(const std::string &sFileName)
	{
		return std::make_shared<CWrapper>(sFileName);
	}
	
	static PWrapper loadLibraryFromSymbolLookupMethod(void* pSymbolLookupMethod)
	{
		return std::make_shared<CWrapper>(pSymbolLookupMethod);
	}
	
	~CWrapper()
	{
		releaseWrapperTable(&m_WrapperTable);
	}
	
	inline void CheckError(CBase * pBaseClass, OptClassResult nResult);

	inline void AcquireInstance(CBase * pInstance);
	inline void ReleaseInstance(CBase * pInstance);
	inline void GetVersion(OptClass_uint32 & nMajor, OptClass_uint32 & nMinor, OptClass_uint32 & nMicro);
	inline bool GetLastError(CBase * pInstance, std::string & sErrorMessage);
	inline void SetJournal(const std::string & sFileName);
	inline void CreateInstanceWithName(const std::string & sIdentifier);
	inline PBase FindInstanceA(const std::string & sIdentifier);
	inline void FindInstanceB(const std::string & sIdentifier, PBase & pInstance);
	inline bool UseInstanceMaybe(CBase * pInstance);

private:
	sOptClassDynamicWrapperTable m_WrapperTable;
	
	OptClassResult checkBinaryVersion()
	{
		OptClass_uint32 nMajor, nMinor, nMicro;
		GetVersion(nMajor, nMinor, nMicro);
		if ( (nMajor != OPTCLASS_VERSION_MAJOR) || (nMinor < OPTCLASS_VERSION_MINOR) ) {
			return OPTCLASS_ERROR_INCOMPATIBLEBINARYVERSION;
		}
		return OPTCLASS_SUCCESS;
	}
	OptClassResult initWrapperTable(sOptClassDynamicWrapperTable * pWrapperTable);
	OptClassResult releaseWrapperTable(sOptClassDynamicWrapperTable * pWrapperTable);
	OptClassResult loadWrapperTable(sOptClassDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName);
	OptClassResult loadWrapperTableFromSymbolLookupMethod(sOptClassDynamicWrapperTable * pWrapperTable, void* pSymbolLookupMethod);

	friend class CBase;

};

	
/*************************************************************************************************************************
 Class CBase 
**************************************************************************************************************************/
class CBase {
public:
	
protected:
	/* Wrapper Object that created the class. */
	CWrapper * m_pWrapper;
	/* Handle to Instance in library*/
	OptClassHandle m_pHandle;

	/* Checks for an Error code and raises Exceptions */
	void CheckError(OptClassResult nResult)
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->CheckError(this, nResult);
	}
public:
	/**
	* CBase::CBase - Constructor for Base class.
	*/
	CBase(CWrapper * pWrapper, OptClassHandle pHandle)
		: m_pWrapper(pWrapper), m_pHandle(pHandle)
	{
	}

	/**
	* CBase::~CBase - Destructor for Base class.
	*/
	virtual ~CBase()
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->ReleaseInstance(this);
		m_pWrapper = nullptr;
	}

	/**
	* CBase::GetHandle - Returns handle to instance.
	*/
	OptClassHandle GetHandle()
	{
		return m_pHandle;
	}
	
	friend class CWrapper;
};
	
	/**
	* CWrapper::AcquireInstance - Acquire shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	inline void CWrapper::AcquireInstance(CBase * pInstance)
	{
		OptClassHandle hInstance = nullptr;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		CheckError(nullptr,m_WrapperTable.m_AcquireInstance(hInstance));
	}
	
	/**
	* CWrapper::ReleaseInstance - Releases shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	inline void CWrapper::ReleaseInstance(CBase * pInstance)
	{
		OptClassHandle hInstance = nullptr;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		CheckError(nullptr,m_WrapperTable.m_ReleaseInstance(hInstance));
	}
	
	/**
	* CWrapper::GetVersion - retrieves the binary version of this library.
	* @param[out] nMajor - returns the major version of this library
	* @param[out] nMinor - returns the minor version of this library
	* @param[out] nMicro - returns the micro version of this library
	*/
	inline void CWrapper::GetVersion(OptClass_uint32 & nMajor, OptClass_uint32 & nMinor, OptClass_uint32 & nMicro)
	{
		CheckError(nullptr,m_WrapperTable.m_GetVersion(&nMajor, &nMinor, &nMicro));
	}
	
	/**
	* CWrapper::GetLastError - Returns the last error recorded on this object
	* @param[in] pInstance - Instance Handle
	* @param[out] sErrorMessage - Message of the last error
	* @return Is there a last error to query
	*/
	inline bool CWrapper::GetLastError(CBase * pInstance, std::string & sErrorMessage)
	{
		OptClassHandle hInstance = nullptr;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		OptClass_uint32 bytesNeededErrorMessage = 0;
		OptClass_uint32 bytesWrittenErrorMessage = 0;
		bool resultHasError = 0;
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, 0, &bytesNeededErrorMessage, nullptr, &resultHasError));
		std::vector<char> bufferErrorMessage(bytesNeededErrorMessage);
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, bytesNeededErrorMessage, &bytesWrittenErrorMessage, &bufferErrorMessage[0], &resultHasError));
		sErrorMessage = std::string(&bufferErrorMessage[0]);
		
		return resultHasError;
	}
	
	/**
	* CWrapper::SetJournal - Handles Library Journaling
	* @param[in] sFileName - Journal FileName
	*/
	inline void CWrapper::SetJournal(const std::string & sFileName)
	{
		CheckError(nullptr,m_WrapperTable.m_SetJournal(sFileName.c_str()));
	}
	
	/**
	* CWrapper::CreateInstanceWithName - Creates an instance of Base class with a given identifier (but does not return it)
	* @param[in] sIdentifier - Identifier of the new instance
	*/
	inline void CWrapper::CreateInstanceWithName(const std::string & sIdentifier)
	{
		CheckError(nullptr,m_WrapperTable.m_CreateInstanceWithName(sIdentifier.c_str()));
	}
	
	/**
	* CWrapper::FindInstanceA - Finds a Base class instance by Identifier
	* @param[in] sIdentifier - Identifier of the tnstance to query
	* @return Base class instance
	*/
	inline PBase CWrapper::FindInstanceA(const std::string & sIdentifier)
	{
		OptClassHandle hInstance = nullptr;
		CheckError(nullptr,m_WrapperTable.m_FindInstanceA(sIdentifier.c_str(), &hInstance));
		
		if (hInstance) {
			return std::make_shared<CBase>(this, hInstance);
		} else {
			return nullptr;
		}
	}
	
	/**
	* CWrapper::FindInstanceB - Finds a Base class instance by Identifier
	* @param[in] sIdentifier - Identifier of the tnstance to query
	* @param[out] pInstance - Base class instance
	*/
	inline void CWrapper::FindInstanceB(const std::string & sIdentifier, PBase & pInstance)
	{
		OptClassHandle hInstance = nullptr;
		CheckError(nullptr,m_WrapperTable.m_FindInstanceB(sIdentifier.c_str(), &hInstance));
		if (hInstance) {
			pInstance = std::make_shared<CBase>(this, hInstance);
		} else {
			pInstance = nullptr;
		}
	}
	
	/**
	* CWrapper::UseInstanceMaybe - Uses a Base class instance
	* @param[in] pInstance - Base class instance
	* @return Was the Instance used?
	*/
	inline bool CWrapper::UseInstanceMaybe(CBase * pInstance)
	{
		OptClassHandle hInstance = nullptr;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		bool resultIsUsed = 0;
		CheckError(nullptr,m_WrapperTable.m_UseInstanceMaybe(hInstance, &resultIsUsed));
		
		return resultIsUsed;
	}
	
	inline void CWrapper::CheckError(CBase * pBaseClass, OptClassResult nResult)
	{
		if (nResult != 0) {
			std::string sErrorMessage;
			if (pBaseClass != nullptr) {
				GetLastError(pBaseClass, sErrorMessage);
			}
			throw EOptClassException(nResult, sErrorMessage);
		}
	}
	

	inline OptClassResult CWrapper::initWrapperTable(sOptClassDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return OPTCLASS_ERROR_INVALIDPARAM;
		
		pWrapperTable->m_LibraryHandle = nullptr;
		pWrapperTable->m_AcquireInstance = nullptr;
		pWrapperTable->m_ReleaseInstance = nullptr;
		pWrapperTable->m_GetVersion = nullptr;
		pWrapperTable->m_GetLastError = nullptr;
		pWrapperTable->m_SetJournal = nullptr;
		pWrapperTable->m_CreateInstanceWithName = nullptr;
		pWrapperTable->m_FindInstanceA = nullptr;
		pWrapperTable->m_FindInstanceB = nullptr;
		pWrapperTable->m_UseInstanceMaybe = nullptr;
		
		return OPTCLASS_SUCCESS;
	}

	inline OptClassResult CWrapper::releaseWrapperTable(sOptClassDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return OPTCLASS_ERROR_INVALIDPARAM;
		
		if (pWrapperTable->m_LibraryHandle != nullptr) {
		#ifdef _WIN32
			HMODULE hModule = (HMODULE) pWrapperTable->m_LibraryHandle;
			FreeLibrary(hModule);
		#else // _WIN32
			dlclose(pWrapperTable->m_LibraryHandle);
		#endif // _WIN32
			return initWrapperTable(pWrapperTable);
		}
		
		return OPTCLASS_SUCCESS;
	}

	inline OptClassResult CWrapper::loadWrapperTable(sOptClassDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName)
	{
		if (pWrapperTable == nullptr)
			return OPTCLASS_ERROR_INVALIDPARAM;
		if (pLibraryFileName == nullptr)
			return OPTCLASS_ERROR_INVALIDPARAM;
		
		#ifdef _WIN32
		// Convert filename to UTF16-string
		int nLength = (int)strlen(pLibraryFileName);
		int nBufferSize = nLength * 2 + 2;
		std::vector<wchar_t> wsLibraryFileName(nBufferSize);
		int nResult = MultiByteToWideChar(CP_UTF8, 0, pLibraryFileName, nLength, &wsLibraryFileName[0], nBufferSize);
		if (nResult == 0)
			return OPTCLASS_ERROR_COULDNOTLOADLIBRARY;
		
		HMODULE hLibrary = LoadLibraryW(wsLibraryFileName.data());
		if (hLibrary == 0) 
			return OPTCLASS_ERROR_COULDNOTLOADLIBRARY;
		#else // _WIN32
		void* hLibrary = dlopen(pLibraryFileName, RTLD_LAZY);
		if (hLibrary == 0) 
			return OPTCLASS_ERROR_COULDNOTLOADLIBRARY;
		dlerror();
		#endif // _WIN32
		
		#ifdef _WIN32
		pWrapperTable->m_AcquireInstance = (POptClassAcquireInstancePtr) GetProcAddress(hLibrary, "optclass_acquireinstance");
		#else // _WIN32
		pWrapperTable->m_AcquireInstance = (POptClassAcquireInstancePtr) dlsym(hLibrary, "optclass_acquireinstance");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_AcquireInstance == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_ReleaseInstance = (POptClassReleaseInstancePtr) GetProcAddress(hLibrary, "optclass_releaseinstance");
		#else // _WIN32
		pWrapperTable->m_ReleaseInstance = (POptClassReleaseInstancePtr) dlsym(hLibrary, "optclass_releaseinstance");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_ReleaseInstance == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetVersion = (POptClassGetVersionPtr) GetProcAddress(hLibrary, "optclass_getversion");
		#else // _WIN32
		pWrapperTable->m_GetVersion = (POptClassGetVersionPtr) dlsym(hLibrary, "optclass_getversion");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetVersion == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetLastError = (POptClassGetLastErrorPtr) GetProcAddress(hLibrary, "optclass_getlasterror");
		#else // _WIN32
		pWrapperTable->m_GetLastError = (POptClassGetLastErrorPtr) dlsym(hLibrary, "optclass_getlasterror");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetLastError == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_SetJournal = (POptClassSetJournalPtr) GetProcAddress(hLibrary, "optclass_setjournal");
		#else // _WIN32
		pWrapperTable->m_SetJournal = (POptClassSetJournalPtr) dlsym(hLibrary, "optclass_setjournal");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_SetJournal == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_CreateInstanceWithName = (POptClassCreateInstanceWithNamePtr) GetProcAddress(hLibrary, "optclass_createinstancewithname");
		#else // _WIN32
		pWrapperTable->m_CreateInstanceWithName = (POptClassCreateInstanceWithNamePtr) dlsym(hLibrary, "optclass_createinstancewithname");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_CreateInstanceWithName == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_FindInstanceA = (POptClassFindInstanceAPtr) GetProcAddress(hLibrary, "optclass_findinstancea");
		#else // _WIN32
		pWrapperTable->m_FindInstanceA = (POptClassFindInstanceAPtr) dlsym(hLibrary, "optclass_findinstancea");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_FindInstanceA == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_FindInstanceB = (POptClassFindInstanceBPtr) GetProcAddress(hLibrary, "optclass_findinstanceb");
		#else // _WIN32
		pWrapperTable->m_FindInstanceB = (POptClassFindInstanceBPtr) dlsym(hLibrary, "optclass_findinstanceb");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_FindInstanceB == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_UseInstanceMaybe = (POptClassUseInstanceMaybePtr) GetProcAddress(hLibrary, "optclass_useinstancemaybe");
		#else // _WIN32
		pWrapperTable->m_UseInstanceMaybe = (POptClassUseInstanceMaybePtr) dlsym(hLibrary, "optclass_useinstancemaybe");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_UseInstanceMaybe == nullptr)
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		pWrapperTable->m_LibraryHandle = hLibrary;
		return OPTCLASS_SUCCESS;
	}

	inline OptClassResult CWrapper::loadWrapperTableFromSymbolLookupMethod(sOptClassDynamicWrapperTable * pWrapperTable, void* pSymbolLookupMethod)
{
		if (pWrapperTable == nullptr)
			return OPTCLASS_ERROR_INVALIDPARAM;
		if (pSymbolLookupMethod == nullptr)
			return OPTCLASS_ERROR_INVALIDPARAM;
		
		typedef OptClassResult(*SymbolLookupType)(const char*, void**);
		
		SymbolLookupType pLookup = (SymbolLookupType)pSymbolLookupMethod;
		
		OptClassResult eLookupError = OPTCLASS_SUCCESS;
		eLookupError = (*pLookup)("optclass_acquireinstance", (void**)&(pWrapperTable->m_AcquireInstance));
		if ( (eLookupError != 0) || (pWrapperTable->m_AcquireInstance == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_releaseinstance", (void**)&(pWrapperTable->m_ReleaseInstance));
		if ( (eLookupError != 0) || (pWrapperTable->m_ReleaseInstance == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_getversion", (void**)&(pWrapperTable->m_GetVersion));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetVersion == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_getlasterror", (void**)&(pWrapperTable->m_GetLastError));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetLastError == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_setjournal", (void**)&(pWrapperTable->m_SetJournal));
		if ( (eLookupError != 0) || (pWrapperTable->m_SetJournal == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_createinstancewithname", (void**)&(pWrapperTable->m_CreateInstanceWithName));
		if ( (eLookupError != 0) || (pWrapperTable->m_CreateInstanceWithName == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_findinstancea", (void**)&(pWrapperTable->m_FindInstanceA));
		if ( (eLookupError != 0) || (pWrapperTable->m_FindInstanceA == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_findinstanceb", (void**)&(pWrapperTable->m_FindInstanceB));
		if ( (eLookupError != 0) || (pWrapperTable->m_FindInstanceB == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("optclass_useinstancemaybe", (void**)&(pWrapperTable->m_UseInstanceMaybe));
		if ( (eLookupError != 0) || (pWrapperTable->m_UseInstanceMaybe == nullptr) )
			return OPTCLASS_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		return OPTCLASS_SUCCESS;
}

	
	
	/**
	 * Method definitions for class CBase
	 */

} // namespace OptClass

#endif // __OPTCLASS_CPPHEADER_DYNAMIC_CPP

