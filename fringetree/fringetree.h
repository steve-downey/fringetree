// fringetree.h                                                       -*-C++-*-
#ifndef INCLUDED_FRINGETREE
#define INCLUDED_FRINGETREE

#include <memory>
#include <variant>

namespace fringetree {

template<typename Tag, typename Value>
class Branch;

template<typename Tag, typename Value>
class Leaf;

template<typename Tag, typename Value>
class Tree;

template<typename Tag, typename Value>
class Branch {
    Tag tag_;
    std::shared_ptr<Tree<Tag, Value>> left_;
    std::shared_ptr<Tree<Tag, Value>> right_;
  public:
    auto tag() const -> Tag {return tag_;}
};

template<typename Tag, typename Value>
class Leaf {
    Tag tag_;
    Value v_;
  public:
    auto tag() const -> Tag {return tag_;}
};

template<typename Tag, typename Value>
class Tree {
    using Leaf_ = Leaf<Tag, Value>;
    using Branch_ = Branch<Tag, Value>;
    std::variant<Leaf_,
                 Branch_> data;

  public:
    Tree(Leaf_ const& leaf) : data(leaf) {}
    Tree(Branch_ const& branch) : data(branch) {}

    auto tag() -> Tag {
        return std::visit(
            [](auto&& v) {
                return v.tag();
            },
            data);
    }
};


// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================


}  // close package namespace

#endif
