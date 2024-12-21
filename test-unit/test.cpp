/*#include "../src/main.cpp"
#include "../src/AVL.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
		this one -> g++ -Wall -Werror -Wuninitialized -o build/test test-unit/test.cpp; build/test




TEST_CASE("Test: search bad number id") {
    AVLTree tree;

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.search(1392392399);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\n");
}


TEST_CASE("Test: insert bad name(number)") {
    AVLTree tree;

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.insert("A11y", 45679999);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\n");
}

TEST_CASE("Test: insert bad name (symbol)") {
    AVLTree tree;

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.insert("Dani@l", 27782901);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\n");
}

TEST_CASE("Test: remove bad number id") {
    AVLTree tree;

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.remove(1323);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\n");
}

TEST_CASE("Test: search id that is not there") {
    AVLTree tree;

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    tree.insert("Jamie", 38219380);

    tree.search(38129381);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "successful\nunsuccessful\n");
}


//three edge cases for various functions

TEST_CASE("Test: Remove nonexistant number") {
    AVLTree tree;
    tree.insert("James", 19381939);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.remove(19213810);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\n");
}

TEST_CASE("Test: search for non existant number") {
    AVLTree tree;
    tree.insert("Trifon", 98765432);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.search(87654321);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\n");
}

TEST_CASE("Test: insert duplicate number ") {
    AVLTree tree;
    tree.insert("Charlie", 00000001);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.insert("Charlie", 00000001);

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\n");
}

//Test all four rotation cases

TEST_CASE("Test Right Rotation") {
    AVLTree tree;

    tree.insert("Ape", 12345678);
    tree.insert("Boni", 23456789);
    tree.insert("Crune", 34567890);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    tree.printInorder();

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "Ape, Boni, Crune\n");
}

TEST_CASE("Test Left Rotation") {
    AVLTree tree;

    tree.insert("Crune", 34567890);
    tree.insert("Boni", 23456789);
    tree.insert("Ape", 12345678);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.printPreorder();

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "Boni, Ape, Crune\n");
}

TEST_CASE("Test Right-Left Rotation") {
    AVLTree tree;

    tree.insert("Ape", 12345678);
    tree.insert("Crune", 34567890);
    tree.insert("Boni", 23456789);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    tree.printInorder();

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "Ape, Boni, Crune\n");
}

TEST_CASE("Test Left-Right Rotation") {
    AVLTree tree;

    tree.insert("Crune", 34567890);
    tree.insert("Ape", 12345678);
    tree.insert("Boni", 23456789);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    tree.printPostorder();

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "Ape, Crune, Boni\n");
}




// Test all three deletion cases (no children, one child, two children)
TEST_CASE("Test: no children") {
    AVLTree tree;

    tree.insert("James", 10000010);
    tree.insert("Pale", 10000020);
    tree.insert("Conner", 10000030);

    tree.remove(10000020);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    tree.printInorder();

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "James, Conner\n");
}

TEST_CASE("Test: one child") {
    AVLTree tree;

    tree.insert("James", 10000010);
    tree.insert("Pale", 10000020);
    tree.insert("Conner", 10000030);

    tree.remove(10000020);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    tree.printPreorder();

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "Conner, James\n");
}

TEST_CASE("Test: two children") {
    AVLTree tree;

    tree.insert("Pale", 10000020);
    tree.insert("James", 10000010);
    tree.insert("Conner", 10000030);
    tree.insert("Dole", 10000040);
    tree.insert("Olay", 10000050);

    tree.remove(10000020);

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    tree.printInorder();

    std::cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "James, Conner, Dole, Olay\n");
}*/