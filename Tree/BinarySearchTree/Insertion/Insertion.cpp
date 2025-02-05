using System;

class Node
{
    public int Key { get; set; }
    public Node Left { get; set; }
    public Node Right { get; set; }

    public Node(int key)
    {
        Key = key;
        Left = Right = null;
    }
}

class BinaryTree
{
    public Node Root { get; set; }

    public BinaryTree()
    {
        Root = null;
    }

    public Node Insert(Node root, int key)
    {
        if (root == null)
            return new Node(key);

        if (key < root.Key)
        {
            root.Left = Insert(root.Left, key);
        }
        else if (key > root.Key)
        {
            root.Right = Insert(root.Right, key);
        }

        return root;
    }

    public void InorderTraversal(Node root)
    {
        if (root != null)
        {
            InorderTraversal(root.Left);
            Console.WriteLine(root.Key);
            InorderTraversal(root.Right);
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        BinaryTree tree = new BinaryTree();

        int[] keys = { 10, 6, 14, 5, 25, 15, 8, 11, 18 };
        foreach (int key in keys)
        {
            tree.Root = tree.Insert(tree.Root, key);
        }

        Console.WriteLine("Inorder Traversal of the BST:");
        tree.InorderTraversal(tree.Root);
    }
}
