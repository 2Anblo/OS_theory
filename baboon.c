#define Semaphore int


enum direction {WEST=0,EAST=1};
Semaphore mutex;//互斥信号量 初始化为1
Semaphore blocked[2];//阻塞信号量 均初始化为0
int blockedCnt[2];// 两端等待的狒狒数量
int travellers [2];// 向两端爬绳子的狒狒数量
//(任一时刻travellers数组中有一个元素值为0)
Baboon(direction dir)
{
	int revdir =!dir;//另一头方向为revdir
	down(mutex);
	while (travellers[revdir])
	{
		blockedCnt[dir]++;//被阻塞的狒狒+1
		up(mutex);
		down(blocked[dir]);//该端狒狒被阻塞
		down(mutex);
	}
	travellers[dir]++;//对面走完了 这一端可以走
	
	up(mutex);
	
	
	// 该端过桥
	down(mutex);
	travellers[dir]--;
	if (!travellers[dir]){
	//假如是最后一个走这个方向的狒狒
	//唤醒另一端被阻塞的狒狒
	while(blockedCnt[revdir]--)
		up(blocked[revdir]);
	}
	up(mutex);
}