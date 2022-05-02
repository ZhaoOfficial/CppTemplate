#include <complex>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>

#include "book/chapter4.hpp"
#include "common.hpp"
#include "spdlog/spdlog.h"

int main() {

    spdlog::info("Test variadic parameters.");
    {
        std::cout << "Test print1\n";
        Coding::print1();
        Coding::print1(1, 1.5, "Test");
        std::cout << "Test print2\n";
        Coding::print2();
        Coding::print2(1, 1.5, "Test");
        std::cout << "Test print\n";
        Coding::print();
        Coding::print(1, 1.5, "Test");
        Coding::count();
        Coding::count(1, 1.5, "Test");
    }
    spdlog::info("Test fold expressions.");
    {
        Coding::print<'\n', '\0'>(
            "Rule of the fold expressions, `op` can be any C++ valid opeerators:",
            "/--------------------------------------------------------------------------\\",
            "|      Fold Expression      |                  Evaluation                  |",
            "|   (... op pack)           |  (((pack1 op pack2) op pack3) ... op packN)  |",
            "|   (pack op ...)           |  (pack1 op ( ... (packN-1 op packN)))        |",
            "|   (init op ... op pack)   |  (((init op pack1) op pack2) ... op packN)   |",
            "|   (pack op ... op init)   |  (pack1 op ( ... (packN op init)))           |",
            "\\--------------------------------------------------------------------------/"
        );
        std::cout << "Fold sum: " << Coding::foldSum(1, 2, 3, 4, 5, 6, 7, 8, 9) << '\n';

        auto left = &Coding::Node::left;
        auto right = &Coding::Node::right;
        Coding::Node data[7] = {0, 1, 2, 3, 4, 5, 6};
        Coding::Node* root = &data[0];
        root->left = &data[1];
        root->right = &data[2];
        root->left->left = &data[3];
        root->left->right = &data[4];
        root->right->left = &data[5];
        root->right->right = &data[6];

        Coding::print<'_'>(
            "Traversing the tree:",
            Coding::traverse(root)->value,
            Coding::traverse(root, left)->value,
            Coding::traverse(root, right)->value,
            Coding::traverse(root, left, left)->value,
            Coding::traverse(root, left, right)->value,
            Coding::traverse(root, right, left)->value,
            Coding::traverse(root, right, right)->value
        );
    }
    spdlog::info("Test application of variadic templates.");
    {
        auto sp = std::make_shared<std::complex<double>>(1.5, 3.5);
        Coding::print("Complex:", sp->real(), sp->imag());
    }
    spdlog::info("Test variadic class templates and variadic expressions.");
    {
        Coding::printDouble(
            1,
            std::complex<double>(1.2, 3.6),
            std::string("no")
        );
        Coding::addOne(1.1f, 2.2, 3u, 4ul, 5);
        Coding::print(
            "Is homogeneous:",
            Coding::is_homogeneous(1, 2, 3),
            Coding::is_homogeneous(1, 2u, 3l)
        );

        std::vector<std::string> vs {"first", "second", "third", "forth"};
        Coding::printElems(vs, 2, 0, 3);
        Coding::printIndex<2, 0, 3, 1>(vs);
        Coding::print<'\n'>(
            "The variadic templates can be used in class templates.",
            "And there is deduction guides for the variadic templates."
        );
    }
    spdlog::info("Test variadic base class and `using`.");
    {
        using CustomerOp = Coding::Overloader<Coding::CustomerHash, Coding::CustomerEq>;
        std::unordered_set<Coding::Customer, Coding::CustomerHash, Coding::CustomerEq> set1;
        std::unordered_set<Coding::Customer, CustomerOp, CustomerOp> set2;

        set1.emplace("first");
        set2.emplace("second");
        Coding::print(set1.cbegin()->getName(), set2.cbegin()->getName());
    }

    return 0;
}
