# ![ACT logo](../../Documentation/images/ACT_logo_50px.png) Automatic Component Toolkit

## Example: Component injection and shared ownership

This example demonstrates the usage of the `importcomponent`-element in the reference counting mechanism provided by ACT.

The Numbers-component provides a class `Variable` that can hold a numerical value.
The Calculation-component provides a class `Calculator` that can sum or multiply instances of class `Variable`.


### How to run the example:
1. Run ACT for `Calculation.xml` (This repo already contains autogenerated sources and a working implementation).
	ACT automatically also generates the Numbers-component from `Numbers.xml`.
2. Build one of the implementations:
	1. C++
	2. Pascal
3. Build and run one of the following examples
	1. CppDynamic
	2. Cpp
	3. Pascal
	4. Python

### How does component-injection work:
1. To be injected, the Numbers-component must specify a `symbollookupmethod` in its component definition-file.
The `symbollookupmethod` provides the addresses of all functions exported by the Numbers-component and is generated and implemented automatically by ACT.

2. The definition of the Numbers-component is injected into the component `Calculator` via the `importcomponent` in the `Calculation.xml`-file. 
To allow injecting any of the imported components into the Calculation-component, it must provide a `injectionmethod`. The `injectionmethod` takes the `symbollookupmethod` of the injected componenent (Numbers) to create a language binding of that component inside the outer component (Calculation) at runtime.

3. The Numbers-component is injected into the Calculation-component at runtime via an explicit call of
`calculationWrapper->InjectComponent("Numbers", numbersWrapper->GetSymbolLookupMethod());` (analogously in other languages).


### How does reference-counting/shared ownership  work in ACT:
1. Reference-counting for all classes is now (v1.6.0) the default in ACT.
	It is implemented in the base-class by
	- an integer member `m_nReferenceCount` within the base-class of a component
	and methods
	- `IncRefCount` which increases the reference count of an instance.
	- `DecRefCount` which decreases the reference count and deletes the instance, if it has reached zero.
	
	In addition:
	- The `releasemethod` now (v1.6.0) does not simple delete/free an instance of a class, but instead calls `DecRefCount`.
	- All components must define an `acquiremethod` in the global section of their xml. Its autogenerated implementation calls `IncRefCount`.
	- In order to use shared-pointers of instances of ACT-classes (C++ only, not Pascal), only use the autogenerated `shared_ptr<>`-classes `$NameSpace::PI$ClassName`. They have a custom deletor that correctly calls `DecRefCount`.

2. A Calculator instance can enlist a Variable-instance.
	The implementation of the enlist-method increases the reference-count of the enlisted Variable-instance, i.e.
	it acquires shared ownership of it. Thus, one can release the ownership of this Variable-instance on the user-code side.
	
3. One can retrieve a Variable-instance that is enlisted in a Calculator. This also increases the reference-count of this instance.

4. Reference-counting can be disabled by modifing the implemetation of a component's base class:
	- Remove the `m_nReferenceCount`-member of the base class.
	- Modify the `IncRefCount`-method to do nothing.
	- Mpdify the `DecRefCount`-method such that it always deletes the instance.
