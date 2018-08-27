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


TEST(TreeTest, breadth) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    auto i =  breadth(t);
    ASSERT_EQ(3, i);

    auto empty = Tree::empty();
    ASSERT_EQ(0, breadth(empty));

    auto t2 = Tree::branch(
        Tree::branch(Tree::empty(), Tree::leaf(1)),
        Tree::branch(Tree::leaf(2), Tree::empty())
        );
    ASSERT_EQ(2, breadth(t2));
}

TEST(TreeTest, depth) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    auto i =  depth(t);
    ASSERT_EQ(3, i);

    auto empty = Tree::empty();
    ASSERT_EQ(0, depth(empty));

    auto t2 = Tree::branch(
        Tree::branch(Tree::empty(), Tree::leaf(1)),
        Tree::branch(Tree::leaf(2), Tree::empty())
        );
    ASSERT_EQ(3, depth(t2));
}

TEST(TreeTest, flatten) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    std::vector<int> expected1 = {1, 2, 3};
    auto i =  flatten(t);
    ASSERT_EQ(expected1, i);

    std::vector<int> expected2 = {};
    auto empty = Tree::empty();
    ASSERT_EQ(expected2, flatten(empty));

    std::vector<int> expected3 = {1, 2};
    auto t2 = Tree::branch(
        Tree::branch(Tree::empty(), Tree::leaf(1)),
        Tree::branch(Tree::leaf(2), Tree::empty())
        );
    ASSERT_EQ(expected3, flatten(t2));
}

TEST(TreeTest, prepend) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    auto t_ = prepend(0, t);

    std::vector<int> expected1 = {0, 1, 2, 3};
    auto i =  flatten(t_);
    ASSERT_EQ(expected1, i);

    std::vector<int> expected2 = {0};
    auto empty = Tree::empty();
    auto empty_ = prepend(0, empty);
    ASSERT_EQ(expected2, flatten(empty_));

    std::vector<int> expected3 = {0, 1, 2};
    auto t3 = Tree::branch(
        Tree::branch(Tree::empty(), Tree::leaf(1)),
        Tree::branch(Tree::leaf(2), Tree::empty())
        );
    auto t3_ = prepend(0, t3);
    ASSERT_EQ(expected3, flatten(t3_));


    auto l_ = prepend(0, Tree::leaf(1));
    ASSERT_EQ(std::vector({0,1}), flatten(l_));
}

TEST(TreeTest, append) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    auto t_ = append(0, t);

    std::vector<int> expected1 = {1, 2, 3, 0};
    auto i =  flatten(t_);
    ASSERT_EQ(expected1, i);

    std::vector<int> expected2 = {0};
    auto empty = Tree::empty();
    auto empty_ = append(0, empty);
    ASSERT_EQ(expected2, flatten(empty_));

    std::vector<int> expected3 = {1, 2, 0};
    auto t3 = Tree::branch(
        Tree::branch(Tree::empty(), Tree::leaf(1)),
        Tree::branch(Tree::leaf(2), Tree::empty())
        );
    auto t3_ = append(0, t3);
    ASSERT_EQ(expected3, flatten(t3_));


    auto l_ = append(0, Tree::leaf(1));
    ASSERT_EQ(std::vector({1,0}), flatten(l_));
}

TEST(TreeTest, leftView) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

     auto vl = view_l(t);
     ASSERT_EQ(vl.isView(), true);
     auto v = vl.view();
     ASSERT_EQ(v.v_, 1);

     std::vector<int> expected1 = {2, 3};
     auto i =  flatten(v.tree_);
     ASSERT_EQ(expected1, i);

     auto empty = Tree::empty();
     auto vl_empty = view_l(empty);
     ASSERT_EQ(vl_empty.isView(), false);
     ASSERT_EQ(vl_empty.isNil(), true);

     std::vector<int> expected3 = {1, 2, 0};
     auto t3 = Tree::branch(
         Tree::branch(Tree::empty(), Tree::leaf(1)),
         Tree::branch(Tree::leaf(2), Tree::empty())
         );
     auto vl3 = view_l(t3);
     ASSERT_EQ(vl3.isView(), true);
     auto v3 = vl3.view();
     ASSERT_EQ(v3.v_, 1);

     auto l_ = Tree::leaf(7);
     auto vl4 = view_l(l_);
     ASSERT_EQ(vl4.isView(), true);
     auto v4= vl4.view();
     ASSERT_EQ(v4.v_, 7);
     ASSERT_EQ(v4.tree_->isEmpty(), true);
}

TEST(TreeTest, rightView) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    auto vr = view_r(t);
    ASSERT_EQ(vr.isView(), true);
    auto v = vr.view();
    ASSERT_EQ(v.v_, 3);

    std::vector<int> expected1 = {1, 2};
    auto i =  flatten(v.tree_);
    ASSERT_EQ(expected1, i);

    auto empty = Tree::empty();
    auto vr_empty = view_r(empty);
    ASSERT_EQ(vr_empty.isView(), false);
    ASSERT_EQ(vr_empty.isNil(), true);

    std::vector<int> expected3 = {1, 2, 0};
    auto t3 = Tree::branch(
        Tree::branch(Tree::empty(), Tree::leaf(1)),
        Tree::branch(Tree::leaf(2), Tree::empty())
        );
    auto vr3 = view_r(t3);
    ASSERT_EQ(vr3.isView(), true);
    auto v3 = vr3.view();
    ASSERT_EQ(v3.v_, 2);

    auto l_ = Tree::leaf(7);
    auto vr4 = view_r(l_);
    ASSERT_EQ(vr4.isView(), true);
    auto v4= vr4.view();
    ASSERT_EQ(v4.v_, 7);
    ASSERT_EQ(v4.tree_->isEmpty(), true);
}

TEST(TreeTest, listOps) {
    using Tree = Tree<int, int>;
    auto t = Tree::branch(
        Tree::branch(Tree::leaf(1), Tree::leaf(2)),
        Tree::leaf(3)
        );

    ASSERT_EQ(head(t), 1);
    ASSERT_EQ(last(t), 3);

    std::vector<int> expected1 = {2, 3};
    ASSERT_EQ(expected1, flatten(tail(t)));

    std::vector<int> expected2 = {1, 2};
    ASSERT_EQ(expected2, flatten(init(t)));

    auto t3 = Tree::branch(
        Tree::branch(Tree::empty(), Tree::leaf(1)),
        Tree::branch(Tree::leaf(2), Tree::empty())
        );

    ASSERT_EQ(head(t3), 1);
    ASSERT_EQ(last(t3), 2);
    ASSERT_EQ(std::vector<int>{2}, flatten(tail(t3)));
    ASSERT_EQ(std::vector<int>{1}, flatten(init(t3)));

    auto l = Tree::leaf(7);
    ASSERT_EQ(head(l), 7);
    ASSERT_EQ(last(l), 7);
    ASSERT_EQ(std::vector<int>{}, flatten(tail(l)));
    ASSERT_EQ(std::vector<int>{}, flatten(init(l)));

}
