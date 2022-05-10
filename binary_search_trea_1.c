/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
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
void inorderTraversal(Node* ptr);	  /* 중위 선회 함수 */
void preorderTraversal(Node* ptr);    /* 선위 선회 함수 */
void postorderTraversal(Node* ptr);	  /* 후위 선회 함수 */
int insert(Node* head, int key);  /* 트리 노드 삽입 */
int deleteLeafNode(Node* head, int key);  /* 단말 노드 삭제 */
Node* searchRecursive(Node* ptr, int key);  /* 재귀적인 노드 찾기 */
Node* searchIterative(Node* head, int key);  /* 반복 노드 찾기 */
int freeBST(Node* head); /* 전체 노드 삭제 */

int main()
{
	char command;
	int key;
	Node* head = NULL;      //헤드 노드는 비어있는 상태
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("[----- [Cho Min Woo] [2019038019] -----]\n\n");
		printf("\n----------------------------------------------------------------\n");
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

int initializeBST(Node** h) {  //트리 초기화

	if(*h != NULL)  //비어잇지 않다면 전체를 초기화 한다.
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node));//헤드 노드 생성
	(*h)->left = NULL;	 //루트임.
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)       // 중위 순회
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)   //전위 순회
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)  //후위 순회
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));         // 새로운 노드를 생성
	newNode->key = key; 
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {         // 헤드가 비어있을 경우
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;   //헤드부터 탐색

	Node* parentNode = NULL;
	while(ptr != NULL) {

		if(ptr->key == key) return 1;  // 값이 중복됨 -> 다시 시작

		parentNode = ptr;        // 부모부터 다시 탐색

		if(ptr->key < key)       //오른쪽 서브 트리
			ptr = ptr->right;        
		else                     // 왼쪽 서브트리
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)       //기존값보다 크면 왼쪽에 
		parentNode->left = newNode;
	else                            // 기존값보다 작으면 오른쪽
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)   // 삭제하는 노드가 단말인 경우
{
	if (head == NULL) {                   // 헤드 노드가 비어있는 경우
		printf("\n Nothing to delete!!\n");  // 삭제할 것이 없음
		return -1;
	}

	if (head->left == NULL) {                  //왼쪽 자식 노드가 비어있는 경우
		printf("\n Nothing to delete!!\n");    // 삭제할 것이 없음
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {  // 자식 노드 모두 비어있는 경우

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}





