#include <fringetree.h>

#include <gtest/gtest.h>

using namespace fringetree;

TEST(TreeTest, TestGTest) {
    ASSERT_EQ(1, 1);
}

TEST(TreeTest, Breathing) {
    Leaf<int, int> leaf;
    Branch<int, int> branch;
    Tree<int, int> t1{leaf};
    Tree<int, int> t2{branch};

    int ltag = t1.tag();
    int btag = t2.tag();

    ASSERT_EQ(0, ltag);
    ASSERT_EQ(0, btag);

}

TEST(TreeTest, makeLeaf) {
    using Tree = Tree<int, int>;
    std::shared_ptr<Tree> p;
    auto p2 = Tree::leaf(1);

    ASSERT_EQ(1, p2->tag());
    ASSERT_EQ(tag(p2), p2->tag());
}

TEST(TreeTest, makeBranch) {
    using Tree = Tree<int, int>;
    auto l1 = Tree::leaf(1);
    auto l2 = Tree::leaf(2);
    auto b1 = Tree::branch(l1, l2);
    ASSERT_EQ(2, b1->tag());
    ASSERT_EQ(tag(b1), b1->tag());

}