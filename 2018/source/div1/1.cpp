// 2. �������

// �����ǵ�
// 1. DFS�� ������ �� �ִ°�?
// 2. DFS�� Ž�� ���� �� ���� Ž���� ���� ���� Ž������ ������ �湮 ���θ� �ʱ�ȭ �� �� �ִ°�?

#include <cstdio>
#include <utility>

#define DIRECTION 4
#define SIZE 101
#define MAX(x,y) ((x)>(y))?x:y

int x_direction[DIRECTION]={-1,1,0,0};
int y_direction[DIRECTION]={0,0,-1,1}; //������� ��,��,��,�� Ž�� ����

using namespace std;

void search(int x,int y,int map[][SIZE],int max_tail[][SIZE],int visited[],int sum[][SIZE],int n,int m){
	int next_x; //���� x����
	int next_y; //���� y����
	
	visited[map[x][y]]=1; //���� ���� ��ȣ üũ	 	
	
	for(int i=0;i<DIRECTION;i++){
		next_x=x+x_direction[i];
		next_y=y+y_direction[i];
		
		if(next_x>=0 && next_x<n && next_y>=0 && next_y<m && visited[map[next_x][next_y]]==0 && map[x][y]<map[next_x][next_y]){
			max_tail[next_x][next_y]=MAX(max_tail[next_x][next_y],max_tail[x][y]+1);
			//�̹� Ž������ ������ ���� ������ ������ �ٸ� ��θ� ���� ���� �� �ִ� ���� ���� �� �ִ� ����
			sum[next_x][next_y]=MAX(sum[next_x][next_y],sum[x][y]+map[next_x][next_y]); 
			//�̹� Ž������ ������ ���� ������ ��ȣ�� �հ� �ٸ� ��θ� ���� ���� �� �ִ� ���� ��ȣ�� �� �� �ִ� ����
			search(next_x,next_y,map,max_tail,visited,sum,n,m);
			visited[map[next_x][next_y]]=0; 			
			//�ٸ� Ž���� ���� �ش� Ž������ �̵��ߴ� �湮 ���� <�ʱ�ȭ>
		}
		// Ž�� ����
		// 1. ������ �̵��� ������ ���� ���� ����
		// 2. ������ ���� ������ ���� ���� �����ΰ� Ȯ��
		// 3. ������ ���� ������ �ڽ��� ��Ҵ� ������ȣ ���� ū�� Ȯ��
	}
}//DFS ���� �Լ�
pair<int,int> max(int max_tail[][SIZE],int sum[][SIZE],int n,int m){
	pair<int,int> ret=make_pair(0,0); //first : ���� ���� , second : ���� ��ȣ ��
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(ret.first<=max_tail[i][j]){
				ret.first=max_tail[i][j];
				ret.second=MAX(ret.second,sum[i][j]);				
			}			
		}
	}
	return ret;
}//DFS Ž���� ���� �� ���� ������ �ִ񰪰� ���� ��ȣ ���� �ִ� ����
int main(){
	int n; //�� ����
	int m; //�� ����
	int map[SIZE][SIZE]={0}; //�Է°�
	int max_tail[SIZE][SIZE]={0}; //���� ��ȣ�� �ִ� ����
	int sum[SIZE][SIZE]={0}; //���� ��ȣ ���� �ִ�
	int visited[SIZE*SIZE]={0}; //�迭�� ���� ��Ҵ� ���� ��ȣ üũ
	pair<int,int> p;
	
	scanf("%d %d",&n,&m);
	
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&map[i][j]);
	
	max_tail[0][0]=1;
	sum[0][0]=map[0][0]; //�ʱⰪ ����
	search(0,0,map,max_tail,visited,sum,n,m);
	
	p=max(max_tail,sum,n,m);
	printf("%d %d",p.first,p.second);
	
	return 0;
}
//�ð� ���⵵ : 4(4���� Ž��)*100(���� ����)*100(���� ����)*4(����:max_tail,sum,visited,max) = 160000
//���� ���⵵ : 101(���� ����)*101(���� ����)*4(int:4Byte)*4(�迭:map,max_tail,sum,visited) = 163216 (0.16MB)