#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Node
{
public:
	int key;

	Node* Left;
	Node* Right;
};


Node* Insert_BT(Node* root, int key)
{
	if (root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		root->Left = root->Right = NULL;

		root->key = key;

		return root;
	}
	else
	{
		if (key < root->key)
		{
			root->Left = Insert_BT(root->Left, key);
		}
		else
		{
			root->Right = Insert_BT(root->Right, key);
		}
	}
	return root;
}

void Delete_BT(Node* root, int key)
{
	Node* tmp = NULL;

	if (root == NULL)
	{
		return;
	}
	else if (root->key > key)
	{
		Delete_BT(root->Left, key);
	}
	else if (root->key < key)
	{
		Delete_BT(root->Right, key);
	}
	else
	{
		if (root->Right != NULL)
		{
			for (Node* p = root->Right; ; p = p->Left)
			{
				if (p->Left == NULL)
				{
					tmp = p;
					break;
				}
			}
			root->key = tmp->key;

			for (Node* p = root->Right; ; p = p->Left)
			{
				if (p->Left == tmp)
				{
					p->Left = NULL;
					free(tmp);
					return;
				}

				else if (p->Left == NULL)
				{
					root->Right = NULL;
					free(tmp);
					return;
				}
			}
		}
		else if (root->Left != NULL)
		{
			tmp = root;
			root = root->Left;
			free(tmp);
			return;
		}
		else if (root->Left == NULL && root->Right == NULL)
		{
			tmp = root;
			root = NULL;
			free(tmp);
			return;
		}
	}
}


int main()
{
	Node* root = NULL;
	root = Insert_BT(root, 3);
	root = Insert_BT(root, 4);
	root = Insert_BT(root, 2);
	Delete_BT(root, 2);
	std::cout << "commit test" << std::endl;
}