#define _CRT_SECURE_NO_WARNINGS
#define BLACK 0
#define RED 1
#include <iostream>

using namespace std;

class Node
{
public:
	int key;

	bool Color; // BLACK : 0, RED : 1

	Node* Parent;

	Node* Left;
	Node* Right;
};


Node* Check_Tree(Node* root, Node* NIL, bool PrevColor, int level)
{
	if (level == 0)
	{
		if (root->Color == BLACK)
		{
			if(root->Left != NIL)
				Check_Tree(root->Left, NIL, BLACK, level + 1);
			if (root->Right != NIL)
				Check_Tree(root->Right, NIL, BLACK, level + 1);
		}
	}
	else
	{
		if (root->Color == BLACK)
		{
			if (PrevColor == BLACK)
			{
				cout << "규칙 위반 발생! " << level << "층의 " << root->key << "의 값을 가진 노드" << endl;
				cout << "사유 : 부모와 자식의 색이 같음, 색 : BLACK, NIL 아님" << endl;
			}
		}
		else if (root->Color == RED)
		{
			if (PrevColor == RED)
			{
				cout << "규칙 위반 발생! " << level << "층의 " << root->key << "의 값을 가진 노드" << endl;
				cout << "사유 : 부모와 자식의 색이 같음, 색 : RED, NIL 아님" << endl;
			}
		}
	}
}

void Init_BT(Node* root, Node* NIL, int key)
{
	NIL = (Node*)malloc(sizeof(Node));
	NIL->Parent = NULL;
	NIL->Left = NULL;
	NIL->Right = NULL;
	NIL->Color = BLACK;

	Node* root = (Node*)malloc(sizeof(Node));
	root->Parent = NIL;
	root->key = key;
	root->Left = NIL;
	root->Right = NIL;
	root->Color = BLACK;
}

Node* Insert_BT(Node* root, Node* NIL, int key, int level)
{
	if (root->key < key)
	{
		if (root->Left == NIL)
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->Left = NIL;
			newNode->Right = NIL;
			newNode->Color = RED;
			newNode->Parent = root;
			root->Left = NIL;
		}
		else
		{
			Insert_BT(root->Left, NIL, key, level + 1);
		}
	}
	else if (root->key > key)
	{
		if (root->Right == NIL)
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->Left = NIL;
			newNode->Right = NIL;
			newNode->Color = RED;
			newNode->Parent = root;
			root->Right = NIL;
		}
		else
		{
			Insert_BT(root->Right, NIL, key, level + 1);
		}
	}
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
	Node* NIL = NULL;
	Node* root = NULL;

	Init_BT(root, NIL, 0);


}