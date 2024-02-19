#include <catch2/catch.hpp>

#include "../../include/IO.hpp"

using namespace Library;
using namespace Library::IO;

Size DummyRead(Byte*, const Size&, void*);
Size DummyWrite(const Byte*, const Size&, void*);

const char* DummyError(void*);

bool DummyEnd(void*);


TEST_CASE("Stream type checking", "[IO][Stream][Immutable]")
{

    int l_thing = 0;
    void* l_dummyThing = &l_thing;

    Stream l_null;
    Stream l_readOnly(DummyRead, DummyEnd, nullptr, l_dummyThing);
    Stream l_writeOnly(DummyWrite, DummyEnd, nullptr, l_dummyThing);
    Stream l_readWrite(DummyRead, DummyWrite, DummyEnd, nullptr, l_dummyThing);
    Stream l_infinite;
    Stream l_finite(nullptr, nullptr, nullptr, DummyError, nullptr);

    CHECK(StreamIsNull(l_null));
    CHECK_FALSE(StreamIsNull(l_readOnly));
    CHECK_FALSE(StreamIsNull(l_writeOnly));
    CHECK_FALSE(StreamIsNull(l_readWrite));
    CHECK(StreamIsNull(l_infinite));
    CHECK(StreamIsNull(l_finite));

    CHECK_FALSE(StreamIsReadOnly(l_null));
    CHECK(StreamIsReadOnly(l_readOnly));
    CHECK_FALSE(StreamIsReadOnly(l_writeOnly));
    CHECK_FALSE(StreamIsReadOnly(l_readWrite));
    CHECK_FALSE(StreamIsReadOnly(l_infinite));
    CHECK_FALSE(StreamIsReadOnly(l_finite));

    CHECK_FALSE(StreamIsWriteOnly(l_null));
    CHECK_FALSE(StreamIsWriteOnly(l_readOnly));
    CHECK(StreamIsWriteOnly(l_writeOnly));
    CHECK_FALSE(StreamIsWriteOnly(l_readWrite));
    CHECK_FALSE(StreamIsWriteOnly(l_infinite));
    CHECK_FALSE(StreamIsWriteOnly(l_finite));

    CHECK_FALSE(StreamIsReadWrite(l_null));
    CHECK_FALSE(StreamIsReadWrite(l_readOnly));
    CHECK_FALSE(StreamIsReadWrite(l_writeOnly));
    CHECK(StreamIsReadWrite(l_readWrite));
    CHECK_FALSE(StreamIsReadWrite(l_infinite));
    CHECK_FALSE(StreamIsReadWrite(l_finite));

    CHECK(StreamIsInfinite(l_null));
    CHECK_FALSE(StreamIsInfinite(l_readOnly));
    CHECK_FALSE(StreamIsInfinite(l_writeOnly));
    CHECK_FALSE(StreamIsInfinite(l_readWrite));
    CHECK(StreamIsInfinite(l_infinite));
    CHECK_FALSE(StreamIsInfinite(l_finite));

    CHECK_FALSE(StreamIsFinite(l_null));
    CHECK(StreamIsFinite(l_readOnly));
    CHECK(StreamIsFinite(l_writeOnly));
    CHECK(StreamIsFinite(l_readWrite));
    CHECK_FALSE(StreamIsFinite(l_infinite));
    CHECK(StreamIsFinite(l_finite));


}
