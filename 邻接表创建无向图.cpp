#include<bits/stdc++.h>
#define MVNum 100//��󶥵���
typedef  char VerTexType;//������������� 
typedef struct ArcNode//�߽�� 
{
	//adjacent���ڵ� vertex���� 
	int adjvex;//�ñ���ָ��Ķ���λ��[�±�]
	struct ArcNode *nextarc ;//ָ����һ���ߵ�ָ��
	int info;//Ȩֵ 
}ArcNode;

typedef struct VNode//������Ϣ 
{
	VerTexType data;
	ArcNode *firstarc;//ָ���һ�������ý��ı߽��ָ�� 
}Vnode,AdjList[MVNum];

typedef struct
{
	AdjList vertices;//Vnode��㹹�ɵ����� 
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͱ��� 
}ALGraph;

int LocateVex(ALGraph G,VerTexType v)//���ҽ���ڶ�����λ�� 
{
	for(int i=0;i<G.vexnum;i++)
	if(G.vertices[i].data==v)
	return i;
	return -1;//û���ҵ� 
}

void CreateUDG(ALGraph &G)//Unconditional Dependency Graph����������ͼ 
{
	VerTexType v1,v2;//���� 
	ArcNode *p1,*p2;// �߽��ָ�� ����������ͼ����Ҫ�������� 
	//�����ڽӱ��ʾ��,��������ͼG
	std::cout<<"�����ܶ��������ܱ���: ";
	std::cin>>G.vexnum>>G.arcnum; 
	std::cout<<"���붥���ֵ\n";
	for(int i=0;i<G.vexnum;i++)
	{
		std::cin>>G.vertices[i].data;//���붥��ֵ
		G.vertices[i].firstarc=nullptr; 
	}
	for(int k=0;k<G.arcnum;k++)//������߹����ڽӱ�
	{
		std::cout<<"\n����������(����  ���� ): ";
		std::cin>>v1>>v2;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//�����ڶ�����е�����
		
		p1=new(std::nothrow) ArcNode;if(!p1){std::cerr<<"�����ڴ����"<<std::endl;abort();}
		p1->adjvex=j;
		//�ڶ���vi��λ����ͷ�巨�����뵽����vi�ı߱�ͷ�� 
		p1->nextarc=G.vertices[i].firstarc; G.vertices[i].firstarc=p1; 
		
		p2=new(std::nothrow) ArcNode;if(!p2){std::cerr<<"�����ڴ����"<<std::endl;abort();}
		p2->adjvex=i;//�ڽӵ� ���Ϊi
		//�ڶ���vj��λ����ͷ�巨�����뵽����vj�ı߱�ͷ�� 
		p2->nextarc=G.vertices[j].firstarc;G.vertices[j].firstarc=p2; 
	} 
} 
void ShowGraph(ALGraph G)
{
	int i,j;
	ArcNode *p;//�߽��ָ��
	for(i=0;i<G.vexnum;i++)
	{
		std::cout<<i<<" ["<<G.vertices[i].data<<"|--]-> ";//���������Ϣ
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)//��������ߵ���Ϣ
		std::cout<<"["<<p->adjvex<<"|--]-> ";
		std::cout.put('\n'); 
	} 
} 

void CreateUDG_pushback(ALGraph &G)//��������ͼ β�巨 [�˽�]
{
	ArcNode *p1=nullptr,*r1=nullptr,*r2=nullptr;//r1��r2��ʾβָ�� 
	int i,j;
	VerTexType v1,v2;
	std::cout<<"��������ͼ�� ���ٸ�����ͱ�\n";
	std::cin>>G.vexnum>>G.arcnum;
	std::cout<<"�������붥�������\n";
	for(int k=0;k<G.vexnum;k++)
	{
		std::cin>>G.vertices[k].data;
		G.vertices[k].firstarc=nullptr;
	}	
	std::cout<<"�������루���㣬���㣩\n";
	for(int k=0;k<G.arcnum;k++)
	{
		std::cin>>v1>>v2;
		i=LocateVex(G,v1),j=LocateVex(G,v2);//�ҵ���������� 
		
		p1=new(std::nothrow) ArcNode;
		p1->adjvex=j;p1->nextarc=nullptr;
	    r1= G.vertices[i].firstarc;
		if(r1==nullptr)
		 G.vertices[i].firstarc=p1;	//ʵ������������ִֻ��һ�� 
		else
			r1->nextarc=p1;//����βָ������ 
			r1=p1;//βָ���ƶ�����ǰָ���λ�� 
		
			//�ڶ������ָ��������ƣ�˼��һ��һ�� 
		p1=new(std::nothrow) ArcNode;
		p1->adjvex=i;p1->nextarc=nullptr;
		r2= G.vertices[j].firstarc;
		if(r2==nullptr)
		 G.vertices[j].firstarc=p1;
		else
		r2->nextarc=p1;
		r2=p1;
	}
}
//-�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������� 
bool visited[MVNum];//��־����
void DFS(ALGraph &G,int v)//������ȱ����ڽӱ�
{
	ArcNode *p=nullptr;//����ָ�� 
	int w=0;//��ȡ������±� 
	std::cout<<G.vertices[v].data<<" ";
	visited[v]=true;
	p=G.vertices[v].firstarc;//ָ��v�ĵ�һ���߽��
	 while(p!=nullptr)
	 {
	 	w=p->adjvex;
	 	if(visited[w]==false)//���wδ��������ݹ����DFS 
	 	DFS(G,w);
	 	p=p->nextarc;//pָ����һ���߽��
	 }
} 
void DFS_Traverse(ALGraph G)
{
	
	for(int i=0;i<G.vexnum;i++)//��ֹ����ͨ��ͼ����Ҫ��һ��δ�����ʵĶ�����Ϊ��ʼ�� 
	{
		if(!visited[i])
		DFS(G,i);
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------- 
bool visited_bfs[MVNum];
void BFS(ALGraph G,int v)//Breadth First Search
{
       std::queue<int> q;//�洢�Ѿ������ʵĽ�� 
		std::cout<<G.vertices[v].data<<" ";
		visited_bfs[v]=true;
		q.push(v);
		while(!q.empty())//���в���Ϊ��
		{
			int u=q.front();q.pop();//���������������ڽӵ� 
			for(auto p=G.vertices[u].firstarc;p;p=p->nextarc)//�����ڽӵı߽�� 
			{
				if(!visited_bfs[p->adjvex])//�ñ���ָ��Ķ���[�±�]û�б����� 
				{
					std::cout<<G.vertices[p->adjvex].data<<" ";
					visited_bfs[p->adjvex]=1;//��־����ı�
					q.push(p->adjvex); 
				}//if	
        	}//for 
		}//while 
}

void BFS_Traverse(ALGraph G)
{
	for(int i=0;i<G.vexnum;i++)//��ֹ����ͨ��ͼ 
		if(!visited_bfs[i])//�����ж���δ���������ͼ������ѡһ����Ϊ��ʼ�� 
		BFS(G,i);
		std::cout.put('\n');
}
int main()
{
	memset(visited,0,sizeof(bool)); 
	memset(visited_bfs,0,sizeof(bool)); 
	ALGraph G;
	CreateUDG(G);
	ShowGraph(G);
	/*��������
	�����ܶ��������ܱ���: 4 3
    ���붥���ֵ A B C D
	����������(����  ���� ):A B
	                        A C
							B D
	�����A->2->1
	      B->3->0
		  C->0
		  D->1*/
   std::cout<<"�������������\n";
	DFS_Traverse(G);
	std::cout<<"\n�������������\n";
    BFS_Traverse(G);
	/*�����Ĳ������� 
	8 9
	12345678
	1 2 
	
	1 3 
	
	2 4 
	
	2 5 

	4 8 
	
	5 8 
	
	3 6 
	
	3 7 
	
	6 7 
  ������������������
		1 3 7 6 2 5 8 4
		�������������
		1 3 2 7 6 5 4 8 */
	return 0;
}
