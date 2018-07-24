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
    Branch() : tag_(0), left_(0), right_(0) {}
    Branch(Tag                               tag,
           std::shared_ptr<Tree<Tag, Value>> left,
           std::shared_ptr<Tree<Tag, Value>> right)
        : tag_(tag), left_(left), right_(right) {}
    auto tag() const -> Tag { return tag_; }
};

template<typename Tag, typename Value>
class Leaf {
    Tag tag_;
    Value v_;
  public:
    Leaf() : tag_(0), v_(0) {};
    Leaf(Tag tag, Value v) : tag_(tag), v_(v) {}
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

    static auto leaf(Value const& v) -> std::shared_ptr<Tree> {
        return std::make_shared<Tree>(Leaf_(1, v));
    }

    static auto branch(std::shared_ptr<Tree> left, std::shared_ptr<Tree> right)
        -> std::shared_ptr<Tree> {
        return std::make_shared<Tree>(
            Branch_((left->tag() + right->tag()), left, right));
    }
};

constexpr auto tag = [](auto tree) {return tree->tag();};

// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================


}  // close package namespace

#endif
