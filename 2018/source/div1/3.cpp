// ���丮�� LCS
// �����ǵ�
// 1. DP�� ������ ����ִ� LCS �˰����� �˰� �ִ°�?
// 2. DP�� ������ �� �޸𸮸� �ּ�ȭ �� �� �ִ°�?
// 3. ���丮�� ���� �־��� ���� ū ���� ǥ���س� �� �ִ°�?

#include <cstdio>

#define MAX(x,y) ((x)>(y))?x:y
#define SIZE 10000 //1~3000 -> 3000���� 9131�ڸ�(���丮�� �Լ� �������� ���Ⱑ��)


int factorial(int number,int* seq){	
	int tmp_seq[SIZE]={0};
	int start_index;
	int end_index=1;
	int tmp=0;
	
	tmp_seq[1]=1;
	
	for(int i=2;i<=number;i++){		
		for(int j=1;j<=end_index;j++){
			tmp+=tmp_seq[j]*i;
			tmp_seq[j]=tmp%10;			
			tmp/=10;
		} // �־��� �ڸ��� ������ ó��				 
		while(tmp){
			tmp_seq[++end_index]=tmp%10;
			tmp/=10;
		} // ������ �ڸ����� ����� �����ִ� tmp�� ó�� -> �ڸ��� Ȯ��		
	}
	
	for(int i=1;i<=end_index;i++)
		seq[end_index-i+1]=tmp_seq[i]; //�迭 ����
	
	return end_index;
}//���丮�� ��� -> �� �ڸ����� �迭�� ����
int lcs(int* seq_1,int* seq_2,int seq_length_1,int seq_length_2){
	int check[2][SIZE]={0};	//�ڸ����� ũ�� ������ �迭�� �ּ�ȭ
	int index=0;
	int max;	
	
	for(int i=1;i<=seq_length_1;i++){
		index=(index+1)%2; //�ε��� ���� 0,1
		for(int j=1;j<=seq_length_2;j++){
			if(seq_1[i]==seq_2[j]){
				if(index==1)
					check[index][j]=MAX(check[index-1][j-1]+1,MAX(check[index-1][j],check[index][j-1]));				
				else
					check[index][j]=MAX(check[index+1][j-1]+1,MAX(check[index+1][j],check[index][j-1]));					
			}
			else{
				if(index==1)
					check[index][j]=MAX(check[index-1][j],check[index][j-1]);
				else
					check[index][j]=MAX(check[index+1][j],check[index][j-1]);
			}
		}			
	}
	max=check[index][seq_length_2];

	return max;
}//���س� ������ LCS ���
int main(){
	int num1;
	int num2; //�־��� �� A,B
	int seq_1[SIZE]={0};
	int seq_2[SIZE]={0}; //A,B�� ���� ���س� ���丮���� �� �ڸ���
	int seq_length_1; //A! ����
	int seq_length_2; //B! ����
	
	scanf("%d %d",&num1,&num2);
	
	seq_length_1=factorial(num1,seq_1);
	seq_length_2=factorial(num2,seq_2);
	
	printf("%d",lcs(seq_1,seq_2,seq_length_1,seq_length_2));	
	
	return 0;
}


// �ִ� �޸� : Check �迭 : 2(index)*10000(SIZE)*4Byte(int) = 80000(Byte) (128MB�̳�)
// �ð�        : LCS�Լ� ��� : worst case - 10000*10000*2(if����) = 2*10^8 (1���̳�)
