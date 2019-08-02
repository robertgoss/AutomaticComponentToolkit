'''++

Copyright (C) 2019 Numbers developers

All rights reserved.

This file has been generated by the Automatic Component Toolkit (ACT) version 1.6.0-RC1.

Abstract: This is an autogenerated Python file in order to allow an easy
 use of Numbers library

Interface version: 1.0.0

'''


import ctypes
import platform
import enum
import os

name = "numbers"

'''Definition of domain specific exception
'''
class ENumbersException(Exception):
	def __init__(self, code, message = ''):
		self._code = code
		self._message = message
	
	def __str__(self):
		if self._message:
			return 'NumbersException ' + str(self._code) + ': '+ str(self._message)
		return 'NumbersException ' + str(self._code)

'''Definition of binding API version
'''
class BindingVersion(enum.IntEnum):
	MAJOR = 1
	MINOR = 0
	MICRO = 0

'''Definition Error Codes
'''
class ErrorCodes(enum.IntEnum):
	SUCCESS = 0
	NOTIMPLEMENTED = 1
	INVALIDPARAM = 2
	INVALIDCAST = 3
	BUFFERTOOSMALL = 4
	GENERICEXCEPTION = 5
	COULDNOTLOADLIBRARY = 6
	COULDNOTFINDLIBRARYEXPORT = 7
	INCOMPATIBLEBINARYVERSION = 8

'''Definition of Function Table
'''
class FunctionTable:
	numbers_createvariable = None
	numbers_getversion = None
	numbers_getlasterror = None
	numbers_releaseinstance = None
	numbers_acquireinstance = None
	numbers_getsymbollookupmethod = None
	numbers_variable_getvalue = None
	numbers_variable_setvalue = None


'''Wrapper Class Implementation
'''
class Wrapper:

	def __init__(self, libraryName = None, symbolLookupMethodAddress = None):
		ending = ''
		if platform.system() == 'Windows':
			ending = 'dll'
		elif platform.system() == 'Linux':
			ending = 'so'
		elif platform.system() == 'Darwin':
			ending = 'dylib'
		else:
			raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY)
		
		if (not libraryName) and (not symbolLookupMethodAddress):
			libraryName = os.path.join(os.path.dirname(os.path.realpath(__file__)),'numbers')
		
		if libraryName is not None:
			path = libraryName + '.' + ending
			try:
				self.lib = ctypes.CDLL(path)
			except Exception as e:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(e) + '| "'+path + '"' )
			
			self._loadFunctionTable()
		elif symbolLookupMethodAddress is not None:
				self.lib = FunctionTable()
				self._loadFunctionTableFromMethod(symbolLookupMethodAddress)
		else:
			raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(e))
		
		self._checkBinaryVersion()
	
	def _loadFunctionTableFromMethod(self, symbolLookupMethodAddress):
		try:
			symbolLookupMethodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_char_p, ctypes.POINTER(ctypes.c_void_p))
			symbolLookupMethod = symbolLookupMethodType(int(symbolLookupMethodAddress))
			
			methodAddress = ctypes.c_void_p()
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_createvariable")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_double, ctypes.POINTER(ctypes.c_void_p))
			self.lib.numbers_createvariable = methodType(int(methodAddress.value))
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_getversion")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32))
			self.lib.numbers_getversion = methodType(int(methodAddress.value))
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_getlasterror")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_void_p, ctypes.c_uint64, ctypes.POINTER(ctypes.c_uint64), ctypes.c_char_p, ctypes.POINTER(ctypes.c_bool))
			self.lib.numbers_getlasterror = methodType(int(methodAddress.value))
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_releaseinstance")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_void_p)
			self.lib.numbers_releaseinstance = methodType(int(methodAddress.value))
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_acquireinstance")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_void_p)
			self.lib.numbers_acquireinstance = methodType(int(methodAddress.value))
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_getsymbollookupmethod")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.POINTER(ctypes.c_void_p))
			self.lib.numbers_getsymbollookupmethod = methodType(int(methodAddress.value))
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_variable_getvalue")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_void_p, ctypes.POINTER(ctypes.c_double))
			self.lib.numbers_variable_getvalue = methodType(int(methodAddress.value))
			
			err = symbolLookupMethod(ctypes.c_char_p(str.encode("numbers_variable_setvalue")), methodAddress)
			if err != 0:
				raise ENumbersException(ErrorCodes.COULDNOTLOADLIBRARY, str(err))
			methodType = ctypes.CFUNCTYPE(ctypes.c_int32, ctypes.c_void_p, ctypes.c_double)
			self.lib.numbers_variable_setvalue = methodType(int(methodAddress.value))
			
		except AttributeError as ae:
			raise ENumbersException(ErrorCodes.COULDNOTFINDLIBRARYEXPORT, ae.args[0])
		
	def _loadFunctionTable(self):
		try:
			self.lib.numbers_createvariable.restype = ctypes.c_int32
			self.lib.numbers_createvariable.argtypes = [ctypes.c_double, ctypes.POINTER(ctypes.c_void_p)]
			
			self.lib.numbers_getversion.restype = ctypes.c_int32
			self.lib.numbers_getversion.argtypes = [ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32)]
			
			self.lib.numbers_getlasterror.restype = ctypes.c_int32
			self.lib.numbers_getlasterror.argtypes = [ctypes.c_void_p, ctypes.c_uint64, ctypes.POINTER(ctypes.c_uint64), ctypes.c_char_p, ctypes.POINTER(ctypes.c_bool)]
			
			self.lib.numbers_releaseinstance.restype = ctypes.c_int32
			self.lib.numbers_releaseinstance.argtypes = [ctypes.c_void_p]
			
			self.lib.numbers_acquireinstance.restype = ctypes.c_int32
			self.lib.numbers_acquireinstance.argtypes = [ctypes.c_void_p]
			
			self.lib.numbers_getsymbollookupmethod.restype = ctypes.c_int32
			self.lib.numbers_getsymbollookupmethod.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
			
			self.lib.numbers_variable_getvalue.restype = ctypes.c_int32
			self.lib.numbers_variable_getvalue.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_double)]
			
			self.lib.numbers_variable_setvalue.restype = ctypes.c_int32
			self.lib.numbers_variable_setvalue.argtypes = [ctypes.c_void_p, ctypes.c_double]
			
		except AttributeError as ae:
			raise ENumbersException(ErrorCodes.COULDNOTFINDLIBRARYEXPORT, ae.args[0])
	
	def _checkBinaryVersion(self):
		nMajor, nMinor, _ = self.GetVersion()
		if (nMajor != BindingVersion.MAJOR) or (nMinor < BindingVersion.MINOR):
			raise ENumbersException(ErrorCodes.INCOMPATIBLEBINARYVERSION)
	
	def checkError(self, instance, errorCode):
		if errorCode != ErrorCodes.SUCCESS.value:
			if instance:
				if instance._wrapper != self:
					raise ENumbersException(ErrorCodes.INVALIDCAST, 'invalid wrapper call')
			message,_ = self.GetLastError(instance)
			raise ENumbersException(errorCode, message)
	
	def CreateVariable(self, InitialValue):
		dInitialValue = ctypes.c_double(InitialValue)
		InstanceHandle = ctypes.c_void_p()
		self.checkError(None, self.lib.numbers_createvariable(dInitialValue, InstanceHandle))
		if InstanceHandle:
			InstanceObject = Variable(InstanceHandle, self)
		else:
			raise ENumbersException(ErrorCodes.INVALIDCAST, 'Invalid return/output value')
		
		return InstanceObject
	
	def GetVersion(self):
		pMajor = ctypes.c_uint32()
		pMinor = ctypes.c_uint32()
		pMicro = ctypes.c_uint32()
		self.checkError(None, self.lib.numbers_getversion(pMajor, pMinor, pMicro))
		
		return pMajor.value, pMinor.value, pMicro.value
	
	def GetLastError(self, InstanceObject):
		InstanceHandle = None
		if InstanceObject:
			InstanceHandle = InstanceObject._handle
		else:
			raise ENumbersException(ErrorCodes.INVALIDPARAM, 'Invalid return/output value')
		nErrorMessageBufferSize = ctypes.c_uint64(0)
		nErrorMessageNeededChars = ctypes.c_uint64(0)
		pErrorMessageBuffer = ctypes.c_char_p(None)
		pHasError = ctypes.c_bool()
		self.checkError(None, self.lib.numbers_getlasterror(InstanceInstanceHandle, nErrorMessageBufferSize, nErrorMessageNeededChars, pErrorMessageBuffer, pHasError))
		nErrorMessageBufferSize = ctypes.c_uint64(nErrorMessageNeededChars.value)
		pErrorMessageBuffer = (ctypes.c_char * (nErrorMessageNeededChars.value))()
		self.checkError(None, self.lib.numbers_getlasterror(InstanceHandle, nErrorMessageBufferSize, nErrorMessageNeededChars, pErrorMessageBuffer, pHasError))
		
		return pErrorMessageBuffer.value.decode(), pHasError.value
	
	def ReleaseInstance(self, InstanceObject):
		InstanceHandle = None
		if InstanceObject:
			InstanceHandle = InstanceObject._handle
		else:
			raise ENumbersException(ErrorCodes.INVALIDPARAM, 'Invalid return/output value')
		self.checkError(None, self.lib.numbers_releaseinstance(InstanceHandle))
		
	
	def AcquireInstance(self, InstanceObject):
		InstanceHandle = None
		if InstanceObject:
			InstanceHandle = InstanceObject._handle
		else:
			raise ENumbersException(ErrorCodes.INVALIDPARAM, 'Invalid return/output value')
		self.checkError(None, self.lib.numbers_acquireinstance(InstanceHandle))
		
	
	def GetSymbolLookupMethod(self):
		pSymbolLookupMethod = ctypes.c_void_p()
		self.checkError(None, self.lib.numbers_getsymbollookupmethod(pSymbolLookupMethod))
		
		return pSymbolLookupMethod.value
	


''' Class Implementation for Base
'''
class Base:
	def __init__(self, handle, wrapper):
		if not handle or not wrapper:
			raise ENumbersException(ErrorCodes.INVALIDPARAM)
		self._handle = handle
		self._wrapper = wrapper
	
	def __del__(self):
		self._wrapper.ReleaseInstance(self)


''' Class Implementation for Variable
'''
class Variable(Base):
	def __init__(self, handle, wrapper):
		Base.__init__(self, handle, wrapper)
	def GetValue(self):
		pValue = ctypes.c_double()
		self._wrapper.checkError(self, self._wrapper.lib.numbers_variable_getvalue(self._handle, pValue))
		
		return pValue.value
	
	def SetValue(self, Value):
		dValue = ctypes.c_double(Value)
		self._wrapper.checkError(self, self._wrapper.lib.numbers_variable_setvalue(self._handle, dValue))
		
	
		