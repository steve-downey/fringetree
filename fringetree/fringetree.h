// fringetree.h                                                       -*-C++-*-
#ifndef INCLUDED_FRINGETREE
#define INCLUDED_FRINGETREE

#include <memory>
#include <variant>
#include <vector>

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
    auto value() const -> Value { return v_; }
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

constexpr inline struct breadth {
    template <typename T, typename V>
    auto operator()(Empty<T, V> const&) const -> T {
        return 0;
    }

    template <typename T, typename V>
    auto operator()(Leaf<T, V> const&) const -> T {
        return 1;
    }

    template <typename T, typename V>
    auto operator()(Branch<T, V> const& b) const -> T {
        return b.left()->visit(*this) + b.right()->visit(*this);
    }
} breadth_;

constexpr auto breadth = [](auto tree) { return tree->visit(breadth_); };

constexpr inline struct depth {
    template <typename T, typename V>
    auto operator()(Empty<T, V> const&) const -> T {
        return 0;
    }

    template <typename T, typename V>
    auto operator()(Leaf<T, V> const&) const -> T {
        return 1;
    }

    template <typename T, typename V>
    auto operator()(Branch<T, V> const& b) const -> T {
        auto leftDepth  = (b.left()->visit(*this))+ 1;
        auto rightDepth = (b.right()->visit(*this)) + 1;

        return (leftDepth > rightDepth) ? leftDepth : rightDepth;
    }
} depth_;

constexpr auto depth = [](auto tree) { return tree->visit(depth_); };

constexpr inline struct flatten {
    template <typename T, typename V>
    auto operator()(Empty<T, V> const&) const -> std::vector<V> {
        return std::vector<V>{};
    }

    template <typename T, typename V>
    auto operator()(Leaf<T, V> const& l) const -> std::vector<V> {
        std::vector<V> v;
        v.emplace_back(l.value());
        return v;
    }

    template <typename T, typename V>
    auto operator()(Branch<T, V> const& b) const -> std::vector<V>{
        auto leftFlatten  = b.left()->visit(*this);
        auto rightFlatten = b.right()->visit(*this);
        leftFlatten.insert(
            leftFlatten.end(), rightFlatten.begin(), rightFlatten.end());
        return leftFlatten;
    }
} flatten_;

constexpr auto flatten = [](auto tree) { return tree->visit(flatten_); };

// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================

} // namespace fringetree

#endif
