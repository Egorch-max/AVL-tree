#pragma once

#include <iostream>

struct Node
{
    std::size_t value;

    int height;

    Node* left;

    Node* right;

    Node(std::size_t val)
    {
        value = val;

        left = nullptr;

        right = nullptr;

        height = 1;
    }
};

class AVL_tree
{
private:
    Node* root;

    int get_height(Node* current) const
    {
        if (current)
        {
            return current->height;
        }
        else
        {
            return 0;
        }
    }

    int balance_factor(Node* current) const
    {
        return get_height(current->right) - get_height(current->left);
    }

    void update_height(Node* current)
    {
        current->height = std::max(get_height(current->left), get_height(current->right)) + 1;
    }

    Node* rotate_right(Node* pivot)
    {
        Node* new_root = pivot->left;

        pivot->left = new_root->right;

        new_root->right = pivot;

        update_height(pivot);

        update_height(new_root);

        return new_root;
    }

    Node* rotate_left(Node* pivot)
    {
        Node* new_root = pivot->right;

        pivot->right = new_root->left;

        new_root->left = pivot;

        update_height(pivot);

        update_height(new_root);

        return new_root;
    }

    Node* balance(Node* current)
    {
        update_height(current);

        if (balance_factor(current) == 2)
        {
            if (balance_factor(current->right) < 0)
            {
                current->right = rotate_right(current->right);
            }
            return rotate_left(current);
        }

        if (balance_factor(current) == -2)
        {
            if (balance_factor(current->left) > 0)
            {
                current->left = rotate_left(current->left);
            }
            return rotate_right(current);
        }

        return current;
    }

    Node* insert(Node* current, std::size_t value)
    {
        if (!current)
        {
            return new Node(value);
        }

        if (current->value > value)
        {
            current->left = insert(current->left, value);
        }
        else if (current->value < value)
        {
            current->right = insert(current->right, value);
        }
        else
        {
            throw std::logic_error("duplicate_value");
        }

        return balance(current);
    }

    Node* erase(Node* current, std::size_t value)
    {
        if (!current)
        {
            throw std::logic_error("value_not_found");
        }

        if (current->value > value)
        {
            current->left = erase(current->left, value);
        }
        else if (current->value < value)
        {
            current->right = erase(current->right, value);
        }
        else
        {
            Node* left_child = current->left;

            Node* right_child = current->right;

            delete current;

            if (!right_child)
            {
                return left_child;
            }

            Node* min_node = find_min(right_child);

            min_node->right = remove_min(right_child);

            min_node->left = left_child;

            return balance(min_node);
        }

        return balance(current);
    }

    Node* remove_min(Node* current)
    {
        if (!current->left)
        {
            return current->right;
        }

        current->left = remove_min(current->left);

        return balance(current);
    }

    Node* find_min(Node* current)
    {
        while (current && current->left)
        {
            current = current->left;
        }
        return current;
    }

    Node* find(Node* current, std::size_t value)
    {
        if (!current)
        {
            return nullptr;
        }

        if (current->value == value)
        {
            return current;
        }

        return find(value < current->value ? current->left : current->right, value);
    }

    void clear_tree(Node* current)
    {
        if (current)
        {
            clear_tree(current->left);

            clear_tree(current->right);

            delete current;
        }
    }

    void print_tree(Node* current) const
    {
        if (!current)
        {
            return;
        }

        std::cout << current->value << std::endl;

        print_tree(current->left);

        print_tree(current->right);
    }

public:
    AVL_tree(Node* node = nullptr) : root(node) {}

    void insert(std::size_t value)
    {
        root = insert(root, value);
    }

    void erase(std::size_t value)
    {
        root = erase(root, value);
    }

    Node* find(std::size_t value)
    {
        return find(root, value);
    }

    void print() const
    {
        print_tree(root);
    }

    ~AVL_tree()
    {
        clear_tree(root);
    }
};