#include <fringetree/fringetree.h>

#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    using namespace fringetree;

    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    auto t1 = prepend(0, t);
    auto t2 = append(4, t1);

    //    printer(std::cout, t_);

    std::cout << "digraph G {\n";
    printer_ p(std::cout);
    t->visit(p);
    t1->visit(p);
    t2->visit(p);
    std::cout << "}\n";
}