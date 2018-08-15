#include <fringetree.h>

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


    auto list = Tree::empty();
    auto l1 = prepend(0, list);
    auto l2 = prepend(1, l1);
    auto l3 = prepend(2, l2);
    auto l4 = prepend(3, l3);
    auto l5 = prepend(4, l4);

    std::cout << "digraph G {\n";
    printer_ p2(std::cout);
    list->visit(p2);
    l1->visit(p2);
    l2->visit(p2);
    l3->visit(p2);
    l4->visit(p2);
    l5->visit(p2);
    std::cout << "}\n";
}
