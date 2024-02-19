#ifndef DYNAMIC_NUMBER__DATA_STRUCTURES_DYNAMIC_NUMBER_DYNAMIC_NUMBER_HPP
#define DYNAMIC_NUMBER__DATA_STRUCTURES_DYNAMIC_NUMBER_DYNAMIC_NUMBER_HPP

#include<stdlib.h>

namespace DataStructures::DynamicNumber
{

    struct DynamicNumber
    {
        unsigned char* m_Buffer;

        DynamicNumber() { }
        DynamicNumber(const DynamicNumber&);
        DynamicNumber(DynamicNumber&&);

        DynamicNumber(const unsigned char&);
        DynamicNumber(const unsigned short&);
        DynamicNumber(const unsigned int&);
        DynamicNumber(const unsigned long&);

        DynamicNumber& operator= (const DynamicNumber&);
        DynamicNumber& operator= (DynamicNumber&&);

        DynamicNumber& operator= (const unsigned char&);
        DynamicNumber& operator= (const unsigned short&);
        DynamicNumber& operator= (const unsigned int&);
        DynamicNumber& operator= (const unsigned long&);

        DynamicNumber& operator+ (const unsigned char&);
        DynamicNumber& operator+ (const unsigned short&);
        DynamicNumber& operator+ (const unsigned int&);
        DynamicNumber& operator+ (const unsigned long&);
        DynamicNumber& operator+= (const unsigned char&);
        DynamicNumber& operator+= (const unsigned short&);
        DynamicNumber& operator+= (const unsigned int&);
        DynamicNumber& operator+= (const unsigned long&);

        DynamicNumber& operator- (const unsigned char&);
        DynamicNumber& operator- (const unsigned short&);
        DynamicNumber& operator- (const unsigned int&);
        DynamicNumber& operator- (const unsigned long&);
        DynamicNumber& operator-= (const unsigned char&);
        DynamicNumber& operator-= (const unsigned short&);
        DynamicNumber& operator-= (const unsigned int&);
        DynamicNumber& operator-= (const unsigned long&);

        DynamicNumber& operator* (const unsigned char&);
        DynamicNumber& operator* (const unsigned short&);
        DynamicNumber& operator* (const unsigned int&);
        DynamicNumber& operator* (const unsigned long&);
        DynamicNumber& operator*= (const unsigned char&);
        DynamicNumber& operator*= (const unsigned short&);
        DynamicNumber& operator*= (const unsigned int&);
        DynamicNumber& operator*= (const unsigned long&);

        DynamicNumber& operator/ (const unsigned char&);
        DynamicNumber& operator/ (const unsigned short&);
        DynamicNumber& operator/ (const unsigned int&);
        DynamicNumber& operator/ (const unsigned long&);
        DynamicNumber& operator/= (const unsigned char&);
        DynamicNumber& operator/= (const unsigned short&);
        DynamicNumber& operator/= (const unsigned int&);
        DynamicNumber& operator/= (const unsigned long&);

    };

    void CreateEmptyDynamicNumberAt(DynamicNumber&);
    void CreateDynamicNumberAtOfSizeUsingAllocator(
        DynamicNumber&, const Size&,
        void* (&) (Size), void (*) (void*), void*
    );

    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber&, const unsigned char&,
        void* (&) (Size), void (*) (void*), void*
    );
    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber&, const unsigned short&,
        void* (&) (Size), void (*) (void*), void*
    );
    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber&, const unsigned int&,
        void* (&) (Size), void (*) (void*), void*
    );
    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber&, const unsigned long&,
        void* (&) (Size), void (*) (void*), void*
    );
    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber& outp_buffer, const unsigned char& p_number
    )
    {
        CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
            outp_buffer, p_number,
            malloc, nullptr, nullptr
        );
    }
    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber& outp_buffer, const unsigned short& p_number
    )
    {
        CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
            outp_buffer, p_number,
            malloc, nullptr, nullptr
        );
    }
    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber& outp_buffer, const unsigned int& p_number
    )
    {
        CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
            outp_buffer, p_number,
            malloc, nullptr, nullptr
        );
    }
    void CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
        DynamicNumber& outp_buffer, const unsigned long& p_number
    )
    {
        CreateDynamicNumberAtFromUnsignedNumberUsingAllocator(
            outp_buffer, p_number,
            malloc, nullptr, nullptr
        );
    }

    DynamicNumber& MakeCopyAtOfDynamicNumberUsingAllocator(
        DynamicNumber&, const DynamicNumber&,
        void* (&) (Size), void (*) (void*), void*
    );
    DynamicNumber& MakeCopyAtOfDynamicNumberUsingAllocator(
        DynamicNumber& outp_buffer, const DynamicNumber& p_number
    )
    {
        return MakeCopyAtOfDynamicNumberUsingAllocator(
            outp_buffer, p_number,
            malloc, nullptr, nullptr
        );
    }

    void ToDynamicNumberAddUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned char&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void ToDynamicNumberAddUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned short&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void ToDynamicNumberAddUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned int&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void ToDynamicNumberAddUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned long&, 
        void (&) (void*, Size), void (*) (void*), void*
    );

    void SubtractDynamicNumberByUnsignedNumberUsingReallocator(
        DynamicNumber&, const unsigned char&,
        void (&) (void*, Size), void (*) (void*), void*
    );
    void SubtractDynamicNumberByUnsignedNumberUsingReallocator(
        DynamicNumber&, const unsigned short&,
        void (&) (void*, Size), void (*) (void*), void*
    );
    void SubtractDynamicNumberByUnsignedNumberUsingReallocator(
        DynamicNumber&, const unsigned int&,
        void (&) (void*, Size), void (*) (void*), void*
    );
    void SubtractDynamicNumberByUnsignedNumberUsingReallocator(
        DynamicNumber&, const unsigned long&,
        void (&) (void*, Size), void (*) (void*), void*
    );

    void MutlipyDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned char&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void MutlipyDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned short&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void MutlipyDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned int&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void MutlipyDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned long&, 
        void (&) (void*, Size), void (*) (void*), void*
    );

    void DivideDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned char&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void DivideDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned short&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void DivideDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned int&, 
        void (&) (void*, Size), void (*) (void*), void*
    );
    void DivideDynamicNumberByUnsigedNumberUsingReallocator(
        DynamicNumber&, const unsigned long&, 
        void (&) (void*, Size), void (*) (void*), void*
    );

}

#endif // !DYNAMIC_NUMBER__DATA_STRUCTURES_DYNAMIC_NUMBER_DYNAMIC_NUMBER_HPP