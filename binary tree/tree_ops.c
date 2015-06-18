#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<float.h>
#include"queue.c"


void insert(btree **root,int data)
{
	btree *node;
	node=(btree*)malloc(sizeof(struct Btree));
	node->left=0;
	node->right=0;
	node->tdata=data;
	if(!node)
	{
		printf("no space\n");
		exit(1);
	}
	if(!(*root))
	{
		(*root)=node;
		return;
	}
	queue *q;
	btree *temp;
	q=create_queue();
	enqueue(&q,(*root));
	while(!isEmpty(q))
	{
		temp=dequeue(q);
		if(temp->left)
		enqueue(&q,temp->left);
		else
		{
			temp->left=node;
			delete(q);
			return;
		}
		
		if(temp->right)
		enqueue(&q,temp->right);
		else
		{
			temp->right=node;
			delete(q);
			return;
		}
	}
	delete(q);
}

btree *maxNode(btree *root)
{
	queue *q;
	q=create_queue();
	btree *temp,*max;
	max=root;
	if(!root)
	return 0;
	enqueue(&q,root);
	while(!isEmpty(q))
	{
		temp=dequeue(q);
		if(max->tdata<temp->tdata)
		max=temp;
		if(temp->left)
		enqueue(&q,temp->left);
		if(temp->right)
		enqueue(&q,temp->right);
	}
	return max;
}

btree *minNode(btree *root)
{
	queue *q;
	q=create_queue();
	btree *temp,*max;
	max=root;
	if(!root)
	return 0;
	enqueue(&q,root);
	while(!isEmpty(q))
	{
		temp=dequeue(q);
		if(max->tdata>temp->tdata)
		max=temp;
		if(temp->left)
		enqueue(&q,temp->left);
		if(temp->right)
		enqueue(&q,temp->right);
	}
	return max;
}

void inorder(btree *root)
{
	if(root)
	{
		inorder(root->left);
		printf("%d\t",root->tdata);
		inorder(root->right);
	}
}

void preorder(btree *root)
{
	if(root)
	{
		printf("%d\t",root->tdata);
		preorder(root->left);
		preorder(root->right);
	}
}

void levelorder(btree *root)
{
	queue *q;
	btree *temp;
	q=create_queue();
	if(!root)
	{
		printf("tree is empty\n");
		return ;
	}
	enqueue(&q,root);
	while(!isEmpty(q))
	{
		temp=dequeue(q);
		printf("%d\t",temp->tdata);
		if(temp->left)
		enqueue(&q,temp->left);
		if(temp->right)
		enqueue(&q,temp->right);
	}
	printf("\n");
	delete(q);
}

void deleteTree(btree *root)
{
	if(root)
	{
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
	}
}

int height(btree *root)
{
	int left,right;
	if(!root)
	return 0;
	left=height(root->left);
	right=height(root->right);
	if(left>right)
	return left+1;
	else
	return right+1;
}

/*int height(btree *root)
{
	queue *q;
	q=create_queue();
	int level=1;
	if(!root)
	return 0;
	enqueue(&q,root);
	enqueue(&q,0);
	while(!isEmpty(q))
	{
		root=dequeue(q);
		if(root==0)
		{
			enqueue(&q,0);
			printf("hello\n");
			level++;
		}
		else
		{
			if(root->left)
			enqueue(&q,root->left);
			if(root->right)
			enqueue(&q,root->right);
		}
	}	
	return level;
}*/
void print_arr(int arr[],int size)
{
	int i;
	for(i=0;i<size;i++)
	printf("%d-->",arr[i]);
	printf("null\n");
}

void leafpath(btree *root,int path[],int pathlen)//set pathlen=0 and call the function
{
	if(!root)
	return;
	path[pathlen++]=root->tdata;
	if(!root->left && !root->right)
	print_arr(path,pathlen);
	else
	{
		leafpath(root->left,path,pathlen);
		leafpath(root->right,path,pathlen);
	}
}

void mirror(btree **root)
{
	btree *temp;
	if(!(*root))
	return;
	temp=(*root)->left;
	(*root)->left=(*root)->right;
	(*root)->right=temp;
	mirror(&((*root)->left));
	mirror(&((*root)->right));
}

int main()
{
	btree *root=0,*temp;
	int i,path[10];
	for(i=1;i<10;i++)
	insert(&root,i%5);
	//preorder(root);
	//printf("\n");
	inorder(root);
	printf("\n");
	//levelorder(root);
	/*printf("max = %d\n",(maxNode(root))->tdata);
	printf("min = %d\n",(minNode(root))->tdata);
	printf("height = %d\n",height(root));
	i=0;
	leafpath(root,path,i);
	mirror(&root);
	preorder(root);*/
	return 0;
}
