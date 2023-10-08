#include<stdio.h>
#include<windows.h>

void telaMenu(){
	int x = 1, y = 1, x2 = 0, y2 = 0;
	for(int i = 0; i < 6; i++){
		if(i%2 == 0){
			y++;
			x = 1;
			y2 = y2 + 10;
			x2 = 0;
		}
		if(i != 0)
			x2 = x2 + 20;
		gotoxy(x*x2, y*y2);
		printf("-");
		x++;
	}  
}

int main(void){
	int x, y;
	
	/*gotoxy(10,10);
	printf("a");
	gotoxy(20,10);
	printf("a");
	gotoxy(10,20);
	printf("a");
	gotoxy(20,20);
	printf("a");
	*/
	telaMenu();
}
