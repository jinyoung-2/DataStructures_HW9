/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
Node* make_newnode(int key);	/* 새로운 노드 생성 및 초기화하는 함수 */

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- [jinyounglee] [2020039063] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

/* inorderTraversal: LVR방식*/
void inorderTraversal(Node* ptr) 
{
	if(ptr)
	{
		inorderTraversal(ptr->left);	//left subtree로 이동
		printf("  [%d]  ",ptr->key);	//parent 노드값 출력
		inorderTraversal(ptr->right);	//right subtree로 이동
	}
	return ;	//해당노드가 NULL일 때
}

/* preorderTraversal: VLR방식*/
void preorderTraversal(Node* ptr)	
{
	if(ptr)
	{
		printf("  [%d]  ",ptr->key);	//parent 노드값 출력
		preorderTraversal(ptr->left);	//left subtree로 이동
		preorderTraversal(ptr->right);	//right subtree로 이동
	}
	return ;	//해당노드가 NULL일 때
}

/* postorderTraversal: LRV방식*/
void postorderTraversal(Node* ptr)
{
	if(ptr)
	{
		postorderTraversal(ptr->left);	//left subtree로 이동
		postorderTraversal(ptr->right);	//right subtree로 이동
		printf("  [%d]  ",ptr->key);	//parent 노드값 출력
	}
	return ;	//해당노드가 NULL일 때
}

/* 새로운 노드 생성 및 초기화하는 함수 */
Node* make_newnode(int key)
{
	Node* insertion_node=NULL;
	insertion_node=(Node*)malloc(sizeof(Node));

	insertion_node->key=key;
	insertion_node->left=NULL;
	insertion_node->right=NULL;
	return insertion_node;
}

/* 노드 삽입함수 */
int insert(Node* head, int key)
{
	//interative insertion
	Node* insertion_node=make_newnode(key);	 //삽입할 노드 메모리할당 및 초기화
	Node* parent=head;			//parent node를 가리키는 포인터 생성
	Node* child=head->left;		//child node를 가리키는 포인터 생성 

	//headnode의 left pointer가 가리키는 노드가 존재하지 않을 때(트리가 존재하지 않는 상태) 
	if(head->left==NULL)
	{
		head->left=insertion_node;		//head node의 left pointer가 삽입할 노드를 가리키도록 설정 
		return 0;
	}

	while(1)
	{
		//주어진 key값과 child노드의 데이터값과 동일할 때 -> 트리는 같은 값이 존재할 수 없으므로 에러가 발생함
		if(key==(child->key))
		{
			printf("ERROR: Already exists\n");
			return -1;
		}
		//주어진 key값이 child노드의 데이터값보다 작을 때
		if(key<(child->key))
		{
			//child노드의 left pointer가 NULL을 가리키면, NULL 위치에 새로운 노드를 삽입한다 
			if(child->left==NULL)
			{
				child->left=insertion_node;
				return 0;
			}
			//NULL이 아닐 시, child노드의 left pointer가 가리키는 노드로 이동
			parent=child;
			child=child->left;
		}
		//주어진 key값이 child노드의 데이터값보다 클 때
		if(key>(child->key))
		{
			//child노드의 right pointer가 NULL을 가리키면, NULL 위치에 새로운 노드를 삽입한다 
			if(child->right==NULL)
			{
				child->right=insertion_node;
				return 0;
			}
			//NULL이 아닐 시, child노드의 right pointer가 가리키는 노드로 이동
			parent=child;
			child=child->right;
		}
	}
}

int deleteLeafNode(Node* head, int key)
{

}

//순환함수
Node* searchRecursive(Node* ptr, int key)
{	
	/*노드가 존재하지 않을 때 -> 최종적으로 찾기 실패 */
	if(!ptr)			
		return NULL; //NULL반환

	/*노드가 존재할 때
		1.주어진 key값이 노드의 데이터값과 동일할 때
		2.주어진 키값이 노드의 데이터값보다 작을 때
		3.주어진 key값이 노드의 데이터값보다 클 때 */

	//주어진 key값이 노드의 데이터값과 동일할 때 -> 찾기 성공 
	if(key==ptr->key)
		return ptr;		//해당노드ptr 주소 반환
	//주어진 키값이 노드의 데이터값보다 작을 때
	if(key<ptr->key)
		return searchRecursive(ptr->left,key);	//rigth subtree 호출
	//주어진 key값이 노드의 데이터값보다 클 때
	if(key>ptr->key)
		return searchRecursive(ptr->right,key);	//left subtree 호출
}


//비순환함수(반복문 이용)
Node* searchIterative(Node* head, int key)
{
	Node* ptr=head->left;
	//ptr가 NULL이 아닐 때까지 반복(=노드가 존재할때까지 반복)
	while(ptr) 
	{
		//주어진 key값이 노드의 데이터값과 동일할 때, ptr을 반환함 -> 최종적으로 찾기 성공
		if(key==ptr->key)
			return ptr;		//해당노드ptr 주소 반환
		//주어진 키값이 노드의 데이터값보다 작을 때, ptr을 ptr의 left포인터가 가리키는 노드를 가리키도록 설정(=왼쪽 노드로 이동)
		if(key<ptr->key)
			ptr=ptr->left;	//rigth subtree로 이동
		//주어진 key값이 노드의 데이터값보다 클 때, ptr을 ptr의 right포인터가 가리키는 노드를 가리키도록 설정(=오른쪽 노드로 이동)
		if(key>ptr->key)
			ptr=ptr->right;	//left subtree로 이동
	}
	//노드가 존재하지 않을 때 NULL반환 -> 찾기 실패
	return NULL;
}

int freeBST(Node* head)
{
	//기존에 트리에 노드가 존재한다면, 해당 노드들을 모두 해제한다.
	if((head->left)!=NULL)
	{
		Node* free_node=head->left;
		while(free_node)
		{

			free(free_node);
		}
	}


	//head 메모리를 해제한다.
	free(head);
	return 0;
}


