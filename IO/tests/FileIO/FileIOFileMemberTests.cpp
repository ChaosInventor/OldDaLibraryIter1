#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../../include/platform_specific/FileIOLinux.hpp"

using namespace Library::IO;

TEST_CASE("Default constructor", "[IO][File][Linux][Member]")
{

    File l_file;

    CHECK(l_file.m_FileDescriptor == -1);
    CHECK(l_file.m_EndOfFile == false);

}

TEST_CASE("Copying and moving", "[IO][File][Linux][Member]")
{

    int l_randDescriptor = rand();
    bool l_randEOF = GENERATE(true, false);    

    File l_file;
    l_file.m_FileDescriptor = l_randDescriptor;
    l_file.m_EndOfFile = l_randEOF;

    File l_to;


    SECTION("Copy constructor")
    {
        l_to = File(l_file);
    }
    SECTION("Copy operator")
    {
        l_to = l_file;
    }
    SECTION("Moving")
    {
        SECTION("Constructor")
        {
            l_to = File((File&&)l_file);
        }
        SECTION("Operator")
        {
            l_to = (File&&)l_file;
        }

        CHECK(l_file.m_FileDescriptor == -1);
        CHECK(l_file.m_EndOfFile == false);
    }


    CHECK(l_to.m_FileDescriptor == l_randDescriptor);
    CHECK(l_to.m_EndOfFile == l_randEOF);

}

TEST_CASE("Construction from file descriptor", "[IO][File][Linux][Member]")
{

    int l_randDescriptor = rand();

    File l_file(l_randDescriptor);

    CHECK(l_file.m_FileDescriptor == l_randDescriptor);
    CHECK(l_file.m_EndOfFile == false);

}

TEST_CASE("Conversion to int", "[IO][File][Linux][Member]")
{

    int l_randDescriptor = rand();

    File l_file(l_randDescriptor);

    CHECK((int)l_file == l_randDescriptor);

}

TEST_CASE("Comparison", "[IO][File][Linux][Member]")
{

    int l_fileDescriptor1 = open("FileIOFileLinuxTestFile1.txt", O_RDONLY | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
    int l_fileDescriptor2 = open("FileIOFileLinuxTestFile1.txt", O_RDONLY | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
    int l_fileDescriptor3 = open("FileIOFileLinuxTestFile2.txt", O_RDONLY | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
    REQUIRE(l_fileDescriptor1 > -1);    
    REQUIRE(l_fileDescriptor2 > -1);
    REQUIRE(l_fileDescriptor3 > -1);

    File l_file(l_fileDescriptor1);
    File l_same(l_fileDescriptor2);
    File l_different(l_fileDescriptor3);

    CHECK(l_file == l_same);
    CHECK_FALSE(l_file == l_different);

    CHECK_FALSE(l_file != l_same);
    CHECK(l_file != l_different);

    close(l_fileDescriptor1);
    close(l_fileDescriptor2);
    close(l_fileDescriptor3);

}
