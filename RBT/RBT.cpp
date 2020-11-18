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

Node* ROOT;

void Left_Rotate(Node*& node, Node* NIL)
{
	if (node->Right == NIL || node == NIL)
	{
		return;
	}

	Node* tmp = node->Right;

	node->Right = node->Right->Left;

	if (NIL != node->Right)
	{
		node->Right->Parent = node;
	}

	tmp->Left = node;
	tmp->Parent = node->Parent;

	if (node->Parent != NIL)
	{
		if (node->Parent->Left == node)
			node->Parent->Left = tmp;
		else
			node->Parent->Right = tmp;
	}

	node->Parent = tmp;

	if (ROOT == node)
	{
		ROOT = tmp;
	}
}

void Right_Rotate(Node*& node, Node* NIL)
{
	if (node->Left == NIL || node == NIL)
	{
		return;
	}

	Node* tmp = node->Left;

	node->Left = node->Left->Right;

	if (node->Left != NIL)
	{
		node->Left->Parent = node;
	}

	tmp->Right = node;
	tmp->Parent = node->Parent;

	if (node->Parent != NIL)
	{
		if (node->Parent->Left == node)
		{
			node->Parent->Left = tmp;
		}
		else
		{
			node->Parent->Right = tmp;
		}
	}

	node->Parent = tmp;

	if (ROOT == node)
	{
		ROOT = tmp;
	}
}

void Check_Tree(Node*& root, Node*& NIL, bool PrevColor, int level)
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
		else
		{
			cout << "규칙 위반 발생! " << level << "번 층의 " << root->key << "의 값을 가진 노드" << endl;
			cout << "사유 : 루트 노드가 레드" << endl;
			root->Color = BLACK;
		}
	}
	else
	{
		if (root->Color == RED)
		{
			if (PrevColor == RED)
			{
				cout << "규칙 위반 발생! " << level << "번 층의 " << root->key << "의 값을 가진 노드" << endl;
				cout << "사유 : 부모가 레드인데 자식도 레드" << endl;

				//삼촌 노드 체크

				//부모가 왼쪽 노드일때
				if (root->Parent->Parent->Left == root->Parent)
				{
					//삼촌 노드가 블랙/NIL일때 회전
					if (root->Parent->Parent->Right->Color == BLACK)
					{
						Right_Rotate(root->Parent->Parent, NIL);
					}
					//삼촌 노드가 레드일때 색상변경
					else if (root->Parent->Parent->Right->Color == RED)
					{
						//조부모를 레드, 부모를 블랙, 삼촌을 블랙으로
						root->Parent->Color = BLACK;

						//증조부모가 NIL이면 조부모는 루트 노드
						if (root->Parent->Parent->Parent == NIL)
						{
							//루트 노드는 항상 블랙
							root->Parent->Parent->Color = BLACK;
						}
						else
						{
							//조부모가 루트노드가 아닐경우
							root->Parent->Parent->Color = RED;
						}

						root->Parent->Parent->Right->Color = BLACK;
					}
				}

				//부모가 오른쪽 노드일때
				else if (root->Parent->Parent->Right == root->Parent)
				{
					//삼촌 노드가 블랙/NIL일때 회전
					if (root->Parent->Parent->Left->Color == BLACK)
					{
						Left_Rotate(root->Parent->Parent, NIL);
					}
					//삼촌 노드가 레드일때 색상변경
					else if (root->Parent->Parent->Left->Color == RED)
					{
						//조부모를 레드, 부모를 블랙, 삼촌을 블랙으로
						root->Parent->Color = BLACK;

						//증조부모가 NIL이면 조부모는 루트 노드
						if (root->Parent->Parent->Parent == NIL)
						{
							//루트 노드는 항상 블랙
							root->Parent->Parent->Color = BLACK;
						}
						else
						{
							//조부모가 루트노드가 아닐경우
							root->Parent->Parent->Color = RED;
						}

						root->Parent->Parent->Left->Color = BLACK;
					}
				}

			}
		}

		if (root->Left != NIL)
			Check_Tree(root->Left, NIL, root->Color, level + 1);
		if (root->Right != NIL)
			Check_Tree(root->Right, NIL, root->Color, level + 1);
	}
}


void Init_BT(Node*& root, Node*& NIL, int key)
{
	NIL = (Node*)malloc(sizeof(Node));
	NIL->Parent = NULL;
	NIL->Left = NULL;
	NIL->Right = NULL;
	NIL->Color = BLACK;

	root = (Node*)malloc(sizeof(Node));
	root->Parent = NIL;
	root->key = key;
	root->Left = NIL;
	root->Right = NIL;
	root->Color = BLACK;
}

void Insert_BT(Node*& root, Node*& NIL, int key, int level)
{
	if (root->key > key)
	{
		if (root->Left == NIL)
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->Left = NIL;
			newNode->Right = NIL;
			newNode->Color = RED;
			newNode->Parent = root;
			root->Left = newNode;
		}
		else
		{
			Insert_BT(root->Left, NIL, key, level + 1);
		}
	}
	else if (root->key < key)
	{
		if (root->Right == NIL)
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->Left = NIL;
			newNode->Right = NIL;
			newNode->Color = RED;
			newNode->Parent = root;
			root->Right = newNode;
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

	Init_BT(ROOT, NIL, 15);
	Insert_BT(ROOT, NIL, 5, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);

	Insert_BT(ROOT, NIL, 25, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);

	Insert_BT(ROOT, NIL, 3, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);

	Insert_BT(ROOT, NIL, 11, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);

	Insert_BT(ROOT, NIL, 6, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);

	Insert_BT(ROOT, NIL, 18, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);

	Insert_BT(ROOT, NIL, 20, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);

	Insert_BT(ROOT, NIL, 40, 0);
	Check_Tree(ROOT, NIL, BLACK, 0);
}