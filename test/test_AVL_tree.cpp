#include "AVL_tree.h"
#include <gtest.h>

class AVL_tree_test : public ::testing::Test
{
protected:
    void SetUp()
    {
        tree = new AVL_tree;

        tree->insert(23);  

        tree->insert(12);  

        tree->insert(45);  

        tree->insert(5);   

    }

    void TearDown()
    {
        delete tree;
    }

    AVL_tree* tree;
};


TEST_F(AVL_tree_test, can_create_and_setup_tree)
{
    ASSERT_NO_THROW(this->SetUp());
}

TEST_F(AVL_tree_test, can_insert_new_values)
{
    this->SetUp();
    ASSERT_NO_THROW(this->tree->insert(7));  
}

TEST_F(AVL_tree_test, can_erase_existing_value)
{
    this->SetUp();
    ASSERT_NO_THROW(this->tree->erase(5));  
}

TEST_F(AVL_tree_test, throw_when_insert_duplicate)
{
    this->SetUp();
    ASSERT_ANY_THROW(this->tree->insert(12));  
}

TEST_F(AVL_tree_test, throw_when_erase_nonexistent)
{
    this->SetUp();
    ASSERT_ANY_THROW(this->tree->erase(99));  
}

TEST_F(AVL_tree_test, can_find_root_value)
{
    this->SetUp();
    Node* found = this->tree->find(23);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->value, 23);
}

TEST_F(AVL_tree_test, cant_find_nonexistent_value)
{
    this->SetUp();
    EXPECT_EQ(this->tree->find(2), nullptr);
}

TEST_F(AVL_tree_test, correct_leaf_height)
{
    this->SetUp();
    EXPECT_EQ(this->tree->find(5)->height, 1);
}

TEST_F(AVL_tree_test, height_changes_after_insert)
{
    this->SetUp();
    this->tree->insert(3);
    EXPECT_EQ(this->tree->find(5)->height, 2);
}

TEST_F(AVL_tree_test, root_height_after_operations)
{
    this->SetUp();
    this->tree->insert(25);
    EXPECT_EQ(this->tree->find(23)->height, 3);
}

TEST_F(AVL_tree_test, can_insert_single_node)
{
    AVL_tree temp_tree;
    temp_tree.insert(10);
    ASSERT_NE(temp_tree.find(10), nullptr);
}

TEST_F(AVL_tree_test, can_erase_single_node)
{
    AVL_tree temp_tree;
    temp_tree.insert(10);
    temp_tree.erase(10);
    ASSERT_EQ(temp_tree.find(10), nullptr);
}

TEST_F(AVL_tree_test, find_returns_null_in_empty_tree)
{
    AVL_tree temp_tree;
    ASSERT_EQ(temp_tree.find(10), nullptr);
}

TEST_F(AVL_tree_test, throw_when_double_erase)
{
    AVL_tree temp_tree;
    temp_tree.insert(10);
    temp_tree.erase(10);
    ASSERT_ANY_THROW(temp_tree.erase(10));
}

TEST_F(AVL_tree_test, height_updates_correctly)
{
    AVL_tree temp_tree;
    temp_tree.insert(10);
    temp_tree.insert(5);
    ASSERT_EQ(temp_tree.find(10)->height, 2);
}