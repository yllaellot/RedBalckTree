#pragma once

#include "RedBlackTree.h"
#include <cstdint>
#include <utility>

#define Black RedBlackTree<T>::Color::BLACK
#define Red RedBlackTree<T>::Color::RED
#define Upper_bound RedBlackTree::Type::UPPER
#define Lower_bound RedBlackTree::Type::LOWER

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::left_rotate(Node* node)
{
    Node* buff{node->right};
    node->right = buff->left;

    if (buff->left != TNULL_) buff->left->parent = node;

    buff->parent = node->parent;

    if (node->parent == nullptr) root_ = buff;
    else if (node == node->parent->left) node->parent->left = buff;
    else node->parent->right = buff;

    buff->left = node;
    node->parent = buff;
    buff->cnt += node->cnt + 1;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::right_rotate(Node* node)
{
    Node* buff{node->left};
    node->left = buff->right;

    if (buff->right != TNULL_) buff->right->parent = node;

    buff->parent = node->parent;

    if (node->parent == nullptr) root_ = buff;
    else if (node == node->parent->right) node->parent->right = buff;
    else node->parent->left = buff;

    buff->right = node;
    node->parent = buff;
    node->cnt -= buff->cnt + 1;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::set_color(Node* node_, Color color_)
{
    node_->color = color_;
}


template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::equel_color(Node* node_, Color color_)
{
    return (node_->color == color_);
}

template<class T, class CMP>
inline void  RedBlackTree<T, CMP>::Node::set(Node* node_)
{
    this = node_;
}

template<class T, class CMP>
void RedBlackTree<T, CMP>::balance_delete(Node* node)
{
    Node* brother;

    while (node != root_ && node->color == Black)
    {
        if (node == node->parent->left)
        {
            brother = node->parent->right;

            if (equel_color(brother, Red))
            {
                set_color(brother, Black);
                set_color(node->parent, Red);
                left_rotate(node->parent);

                brother = node->parent->right;
            }

            if (equel_color(brother->left, Black) && equel_color(brother->right, Black))
            {
                set_color(brother, Red);
                node = node->parent;
            }
            else
            {
                if (equel_color(brother->right, Black))
                {
                    set_color( brother->left, Black);
                    set_color(brother, Red);

                    right_rotate(brother);

                    brother = node->parent->right;
                }

                set_color(brother, node->parent->color);
                set_color(node->parent, Black);
                set_color(brother->right, Black);

                left_rotate(node->parent);

                node = root_;
            }
        }
        else
        {
            brother = node->parent->left;

            if (equel_color(brother, Red)) 
            {
                set_color(brother, Black);
                set_color(node->parent, Red);

                right_rotate(node->parent);

                brother = node->parent->left;
            }

            if (equel_color(brother->left, Black) && equel_color(brother->right, Black))
            {
                set_color(brother, Red);
                node = node->parent;
            }

            else
            {
                if (equel_color(brother->left, Black))
                {
                    set_color(brother->right, Black);
                    set_color(brother, Red);

                    left_rotate(brother);
    
                    brother = node->parent->left;
                }

                set_color(brother, node->parent->color);
                set_color(node->parent, Black);
                set_color(brother->left, Black);

                right_rotate(node->parent);

                node = root_;
            }
        }
    }

    set_color(node, Black);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::swap(Node* src, Node* dst)
{
    if (src->parent == nullptr) root_ = dst;
    else if (src == src->parent->left) src->parent->left = dst;
    else src->parent->right = dst;

    dst->parent = src->parent;
}

template<class T, class CMP>
void RedBlackTree<T, CMP>::balance_insert(Node* node)
{
    Node* uncle;

    while (equel_color(node->parent, Red))
    {
        if (node->parent == node->parent->parent->right)
        {
            uncle = node->parent->parent->left;

            if (equel_color(uncle, Red))
            {
                set_color(uncle, Black);
                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                node = node->parent->parent;
            }

            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    right_rotate(node);
                }
                
                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                left_rotate(node->parent->parent);
            }
        }
        else
        {
            uncle = node->parent->parent->right;

            if (equel_color(uncle, Red))
            {
                set_color(uncle, Black);
                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    left_rotate(node);
                }

                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                right_rotate(node->parent->parent);
            }
        }

        if (node == root_) break;
    }

    set_color(root_, Black);
}

template<class T, class CMP>
void RedBlackTree<T, CMP>::free_node(Node* ptr)
{
    std::vector<Node*> stack_node;
    stack_node.push_back(root_);

    while (stack_node.size())
    {
        ptr = stack_node.back();
        stack_node.pop_back();

        if (ptr == TNULL_) continue;

        stack_node.push_back(ptr->left);
        stack_node.push_back(ptr->right);

        delete ptr;
    }
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::copy_tree(Node* dst, Node* src, Node* otherTNULL, Node* parent)
{
    std::vector<std::pair<Node*, Node*>> stack_node;
    std::vector<Node*> stack_parent;
    
    stack_node.push_back({src, dst});
    stack_parent.push_back(parent);

    while(stack_node.size())
    {
        auto [cur_node, dst_node] = stack_node.back();
        Node* cur_parent = stack_parent.back();

        stack_node.pop_back();
        stack_parent.pop_back();

        if(cur_node == otherTNULL) dst_node = otherTNULL;
        else
        {
            dst_node->data = cur_node->data;
            dst_node->color = cur_node->color;
            dst_node->cnt = cur_node->cnt;
            dst_node->parent = cur_parent;

            dst_node->right = new Node{};
            dst_node->left = new Node{};

            stack_node.push_back({cur_node->right, dst_node->right});
            stack_parent.push_back(dst_node);

            stack_node.push_back({cur_node->left, dst_node->left});
            stack_parent.push_back(dst_node);
        }
    }
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase_helper(Node* node)
{
    Node* buff_1;
    Node* buff_2 = node;

    Color y_original_color = buff_2->color;

    if (node->left == TNULL_)
    {
        buff_1 = node->right;
        swap(node, node->right);
    }
    else if (node->right == TNULL_)
    {
        buff_1 = node->left;
        swap(node, node->left);
    }
    else
    {
        buff_2 = node->right;

        while (buff_2->left != TNULL_)
        {
            buff_2->cnt--;
            buff_2 = buff_2->left;
        }

        y_original_color = buff_2->color;
        buff_1 = buff_2->right;

        if (buff_2->parent == node) buff_1->parent = buff_2;
        else
        {
            swap(buff_2, buff_2->right);

            buff_2->right = node->right;
            buff_2->right->parent = buff_2;
        }

        swap(node, buff_2);

        buff_2->left = node->left;
        buff_2->left->parent = buff_2;

        set_color(buff_2, node->color);
        buff_2->cnt = node->cnt + 1;
    }

    delete node;

    if (y_original_color == Black) balance_delete(buff_1);
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::range_queries_search(const T& key1, const T& key2)
{
    Node* node = root_;
    Node* result = nullptr;
    int64_t last_r = 0;
    int64_t num_elems = 0;
    bool is_min = true;

    //subtract number of elements in [min_elem, key1) 
    while (node != TNULL_)
    {
        if (!CMP{}(node->data, key1)) // key1 <= node->key()
        {
            num_elems -= last_r;
            last_r = 0;
            result = std::exchange(node, node->left);
        }
        else
        {
            is_min = false;
            last_r += node->cnt + 1;
            node = node->right;
        }
    }

    if (result == nullptr) return 0;

    if (is_min && result->data != key1) num_elems = 0;
    else
    {
        if (CMP{}(result->data, key1)){num_elems -= 1;}
        num_elems -= result->cnt;
    }

    node = root_;
    result = nullptr;
    last_r = 0;
    is_min = true;

    //add number of elements in [min_elem, key2]
    while (node != TNULL_)
    {
        if (CMP{}(key2, node->data)) // key2 < node->key()
        {
            num_elems += last_r;
            last_r = 0;
            result = std::exchange(node, node->left);
        }
        else
        {
            is_min = false;
            last_r += node->cnt + 1;
            node = node->right;
        }
    }

    if (result == nullptr) num_elems += size();
    else
    {
        if (is_min && result->data != key1) num_elems = 0;
        else num_elems += result->cnt;
    }

    return num_elems;
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::range_queries(const T& key1, const T& key2)
{
    if (key2 <= key1) return 0;

    return range_queries_search(key1, key2);
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree::Node::Node(T data_,
                                                      Node* parent_,
                                                      Node* left_,
                                                      Node* right_, 
                                                      Color color_,
                                                      int64_t cnt_) :
    data(data_),
    parent(parent_),
    left(left_),
    right(right_),
    color(color_),
    cnt(cnt_)
{}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree::Node::Node(Node* node_) :
    data(node_->data),
    parent(node_->parent),
    left(node_->left),
    right(node_->right),
    color(node_->color),
    cnt(node_->cnt)
{}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree() :
    TNULL_(new Node{T(0), nullptr, nullptr, nullptr, Black, -1 }),
    root_(TNULL_),
    elements_(0)
{}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(const std::initializer_list<T> list) : RedBlackTree()
{
    for (auto& now : list) insert(now);
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(const RedBlackTree<T, CMP>& rhs) : RedBlackTree()
{
    elements_ = rhs.elements_;
    if (rhs.root_ != rhs.TNULL_)
    {
        root_ = new Node;
        copy_tree(root_, rhs.root_, rhs.TNULL_, nullptr);
    }
}

template<class T, class CMP>
inline void  RedBlackTree<T, CMP>::set(Node* TNULL, Node* root, int64_t elements)
{
    TNULL_ = TNULL;
    root_= root;
    elements_ = elements;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(RedBlackTree<T, CMP>&& rhs) noexcept
{
    set(rhs.TNULL_, rhs.root_, rhs.elements_);
    rhs.set(nullptr, nullptr, 0);
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>& RedBlackTree<T, CMP>::operator=(const RedBlackTree<T, CMP>& rhs)
{
    if (this == &rhs) return *this;
    if (root_ != TNULL_) free_node(root_);

    elements_ = rhs.elements_;

    if (rhs.root_ != rhs.TNULL_)
    {
        root_ = new Node;
        copy_tree(root_, rhs.root_, rhs.TNULL_, nullptr);
    }
    else root_ = TNULL_;

    return *this;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>& RedBlackTree<T, CMP>::operator=(RedBlackTree<T, CMP>&& rhs) noexcept
{
    if (this == &rhs) return *this;

    if (root_ != TNULL_) free_node(root_);

    delete TNULL_;

    set(rhs.TNULL_, rhs.root_, rhs.elements_);
    rhs.set(nullptr, nullptr, 0);

    return *this;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::insert(const T& key)
{ 
    elements_++;

    Node* node = new Node{key, nullptr, TNULL_, TNULL_, Red, 0};

    set_color(node, Red);

    Node* parent = nullptr;
    Node* curr = root_;

    while (curr != TNULL_)
    {
        parent = curr;

        if (CMP{}(node->data, curr->data))
        {
            curr->cnt++;
            curr = curr->left;
        }
        else if (node->data == curr->data)
        {
            delete node;
            elements_--;

            while (curr->parent != nullptr)
            {
                if (curr == curr->parent->left) curr->parent->cnt--;
                curr = curr->parent;
            }

            return;
        }
        else curr = curr->right;
    }

    node->parent = parent;
    node->cnt = node->left->cnt + 1;

    if (parent == nullptr) root_ = node;
    else if (CMP{}(node->data, parent->data)) parent->left = node;
    else parent->right = node;

    if (node->parent == nullptr)
    {
        set_color(node, Black);
        return;
    }

    if (node->parent->parent == nullptr) return;

    balance_insert(node);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase(const T& key)
{
    if (elements_ == 0) return;

    elements_--;

    Node* node = root_;
    Node* helper = TNULL_;
    Node* buff = nullptr;

    while (node != TNULL_)
    {
        buff = node;

        if (node->data == key) helper = node;

        if (CMP{}(node->data, key)) 
        {
            node = node->right;
        }
        else 
        {
            node->cnt--;
            node = node->left;
        }
    }

    if (helper == TNULL_)
    {
        elements_++;

        if (CMP{}(key, buff->data)) buff->cnt++;

        while (buff->parent != nullptr)
        {
            if (buff == buff->parent->left) buff->parent->cnt++;

            buff = buff->parent;
        };
    
        return;
    }

    erase_helper(helper);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase(ConstIterator it)
{
    if (it.ptr == nullptr || it.ptr == TNULL_) return;

    elements_--;

    Node* curr = it.ptr;

    curr->cnt--;

    while (curr->parent != nullptr)
    {
        if (curr == curr->parent->left) curr->parent->cnt--;
        curr = curr->parent;
    }

    erase_helper(it.ptr);
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::size() const
{
    return elements_;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::find(const T& key) const
{
    Node* node = root_;
    Node* res_n = TNULL_;

    while (node != TNULL_)
    {
        if (node->data == key) res_n = node;

        if (CMP{}(node->data, key)) node = node->right;
        else node = node->left;
    }

    if (res_n == TNULL_) return end();

    return ConstIterator{res_n, TNULL_, root_};
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::order_of_key(const T& key) const
{
    Node* curr = root_;
    int64_t key_order = 0;

    while (curr != TNULL_ && curr->data != key) 
    {
        if (CMP{}(key, curr->data)) curr  = curr->left;
        else 
        {
            key_order += curr->cnt + 1;
            curr  = curr->right;
        }
    }

    if (curr  == TNULL_) return elements_;

    key_order += curr->cnt;

    return key_order;
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::order_of_key(const ConstIterator it) const
{
    return it.order();
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::operator==(const RedBlackTree<T, CMP>& rhs) const
{
    if (elements_ != rhs.elements_) return false;

    auto it1 = begin(), it2 = rhs.begin();

    while (it1 != end())
    {
        if (*it1 != *it2) return true;
        it1++;
        it2++;
    }

    return true;
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::operator!=(const RedBlackTree<T, CMP>& rhs) const
{
    if (elements_ != rhs.elements_) return true;

    auto it1 = begin(), it2 = rhs.begin();

    while (it1 != end())
    {
        if (*it1 != *it2) return true;

        it1++;
        it2++;
    }

    return false;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::~RedBlackTree()
{
    free_node(root_);
    delete TNULL_;
}
