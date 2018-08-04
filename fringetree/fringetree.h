// fringetree.h                                                       -*-C++-*-
#ifndef INCLUDED_FRINGETREE
#define INCLUDED_FRINGETREE

#include <memory>
#include <variant>

namespace fringetree {

template <typename Tag, typename Value>
class Branch;

template <typename Tag, typename Value>
class Leaf;

template <typename Tag, typename Value>
class Empty;

template <typename Tag, typename Value>
class Tree;

template <typename Tag, typename Value>
class Branch {
    Tag                               tag_;
    std::shared_ptr<Tree<Tag, Value>> left_;
    std::shared_ptr<Tree<Tag, Value>> right_;

  public:
    Branch() : tag_(0), left_(0), right_(0) {}
    Branch(Tag                               tag,
           std::shared_ptr<Tree<Tag, Value>> left,
           std::shared_ptr<Tree<Tag, Value>> right)
        : tag_(tag), left_(left), right_(right) {}
    auto tag() const -> Tag { return tag_; }
    auto left() const { return left_; }
    auto right() const { return right_; }
};

template <typename Tag, typename Value>
class Leaf {
    Tag   tag_;
    Value v_;

  public:
    Leaf() : tag_(0), v_(0){};
    Leaf(Tag tag, Value v) : tag_(tag), v_(v) {}
    auto tag() const -> Tag { return tag_; }
};

template <typename Tag, typename Value>
class Empty {
  public:
    Empty(){};
    auto tag() const -> Tag { return {}; };
};

template <typename Tag, typename Value>
class Tree {
  public:
    using Leaf_   = Leaf<Tag, Value>;
    using Branch_ = Branch<Tag, Value>;
    using Empty_  = Empty<Tag, Value>;

  private:
    std::variant<Empty_, Leaf_, Branch_> data_;

  public:
    Tree(Empty_ const& empty) : data_(empty) {}
    Tree(Leaf_ const& leaf) : data_(leaf) {}
    Tree(Branch_ const& branch) : data_(branch) {}

    auto tag() -> Tag {
        return std::visit([](auto&& v) { return v.tag(); }, data_);
    }

    static auto empty() -> std::shared_ptr<Tree> {
        return std::make_shared<Tree>(Empty_{});
    }

    static auto leaf(Value const& v) -> std::shared_ptr<Tree> {
        return std::make_shared<Tree>(Leaf_{1, v});
    }

    static auto branch(std::shared_ptr<Tree> left, std::shared_ptr<Tree> right)
        -> std::shared_ptr<Tree> {
        return std::make_shared<Tree>(
            Branch_{(left->tag() + right->tag()), left, right});
    }

    template <typename Callable>
    auto visit(Callable&& c) const {
        return std::visit(c, data_);
    }
};

constexpr auto tag = [](auto tree) { return tree->tag(); };

namespace detail {
template <typename T, typename V>
struct breadth_;
}

template <typename T, typename V>
auto breadth(Tree<T, V> const& tree) -> int {
    return tree.visit(detail::breadth_<T, V>{});
}

namespace detail {
template <typename T, typename V>
struct breadth_ {
    auto operator()(Empty<T, V> const&) { return 0; }
    auto operator()(Leaf<T, V> const&) { return 1; }
    auto operator()(Branch<T, V> const& b) {
        return breadth(*(b.left())) + breadth(*(b.right()));
    }
};
} // namespace detail

namespace detail {
template <typename T, typename V>
struct depth_;
}

template <typename T, typename V>
auto depth(Tree<T, V> const& tree) -> int {
    return tree.visit(detail::depth_<T, V>{});
}

namespace detail {
template <typename T, typename V>
struct depth_ {
    auto operator()(Empty<T, V> const&) { return 0; }
    auto operator()(Leaf<T, V> const&) { return 1; }
    auto operator()(Branch<T, V> const& b) {
        auto leftDepth  = depth(*(b.left())) + 1;
        auto rightDepth = depth(*(b.right())) + 1;

        return (leftDepth > rightDepth) ? leftDepth : rightDepth;
    }
};
} // namespace detail

// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================

} // namespace fringetree

#endif
