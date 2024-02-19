#define CATCH_CONFIG_MAIN
#include<catch.hpp>
#include "../ScopedObject.hpp"

struct SomeObject
{

    bool* m_Pointer;

    SomeObject(bool* p_pointer) : m_Pointer(p_pointer) { }

    bool operator== (SomeObject p_other)
    {
        return m_Pointer == p_other.m_Pointer;
    }
    bool operator!= (SomeObject p_other)
    {
        return m_Pointer != p_other.m_Pointer;
    }

};
void SomeDestructionFunction(SomeObject& p_object, void (&p_deallocate) (void*))
{

    if(p_object.m_Pointer != nullptr)
    {
        *p_object.m_Pointer = true;
    }
    //Just to make sure.
    p_deallocate(nullptr);

}

TEST_CASE("Construction test", "[ScopedObject][Construction]")
{

    bool l_dummyBool;

    SomeObject l_someObject1 = &l_dummyBool;
    SomeObject l_someObject2 = nullptr;

    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject1(l_someObject1);
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject2(l_someObject2);
    
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject3 = l_someObject1;
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject4 = l_someObject2;

    CHECK(((SomeObject)l_scopedObject1 == l_scopedObject3));
    CHECK(((SomeObject)l_scopedObject2 == l_scopedObject4));
    CHECK(((SomeObject)l_scopedObject1 != l_scopedObject4));
    CHECK(((SomeObject)l_scopedObject2 != l_scopedObject3));

}

TEST_CASE("Copying an moving", "[ScopedObject][Copying][Moving]")
{

    SomeObject l_someObject1 = nullptr;
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject(l_someObject1);

    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject1(l_scopedObject);
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject2(
        (ScopedObject<SomeObject, SomeDestructionFunction>&&)l_scopedObject
    );
    
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject3 = l_scopedObject;
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject4 = 
        (ScopedObject<SomeObject, SomeDestructionFunction>&&)l_scopedObject;


    CHECK((l_scopedObject1.m_Object == l_someObject1));
    CHECK((l_scopedObject2.m_Object == l_someObject1));
    CHECK((l_scopedObject3.m_Object == l_someObject1));
    CHECK((l_scopedObject4.m_Object == l_someObject1));

}

TEST_CASE("Set object reference")
{

    bool l_dummyBool;

    SomeObject l_someObject = nullptr;
    SomeObject l_someObject2 = &l_dummyBool;
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject = l_someObject;

    l_scopedObject = l_someObject2;

    CHECK(&l_scopedObject.m_Object == &l_scopedObject.m_Object);

}

TEST_CASE("To object reference")
{

    SomeObject l_someObject = nullptr;
    ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject = l_someObject;

    SomeObject& l_someObject2 = l_scopedObject;

    CHECK(&l_someObject2 == &l_someObject);

}

TEST_CASE("Destructor test", "[ScopedObject][Destructor]")
{

    bool l_called = false;
    bool l_called2 = false;

    do
    {
        SomeObject l_someObject = &l_called;
        ScopedObject<SomeObject, SomeDestructionFunction> l_scopedObject = l_someObject; 

        SomeObject l_someObject2 = &l_called2;
        ScopedObject<SomeObject, SomeDestructionFunction, free> l_scopedObject2 = l_someObject2; 
    } while(0);

    CHECK(l_called == true);
    CHECK(l_called2 == true);

}