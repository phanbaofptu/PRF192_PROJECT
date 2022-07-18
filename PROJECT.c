//Student Name: Phan Gia Bao
//Student ID: DE170027
#include<stdio.h>
#include<math.h>
void function_Calc_Fuel(int time, int averagespeed, double gasoline){
	printf("How many minutes did you drive?\n");
	scanf("%d",&time);
	double h=(double)time/60;
	printf("What was the average speed of the car during that time?\n");
	scanf("%d",&averagespeed);
	printf("How many gallons of gas did your car use?\n");
	scanf("%lf",&gasoline);
	printf("Your car averaged %.2lf miles per gallon.\n",((h*averagespeed)/gasoline));
	}
	
void fuction_Calc_Dis(int r, int revolution, double PI){
	printf("What is the radius of your tires, in inches?\n");
	scanf("%d",&r);
	printf("How many revolutions did your car's tires make?\n");
	scanf("%d",&revolution);
	printf("Your car traveled %.2lf miles.\n", 2*r*PI*revolution*0.0000157828283);
}

void RevisedFuelEconomy(int r,int revolution, double g, double PI){
	printf("What is the radius of your tires, in inches?\n");
	double miles=0.0000157828283;
	scanf("%d",&r);
	printf("How many revolutions did your car's tires make?\n");
	scanf("%d",&revolution);
	printf("How many gallons of gas did your car use?\n");
	scanf("%lf",&g);
	printf("Your car averaged %.2lf miles per gallon. \n",(2*r*PI*revolution*miles)/g);
}

int main(){
	double time, averagespeed, gasoline, r, revolution;
	double g;
	double PI = 2 * acos(0);
	int select;
	do{	
		printf("\n1 - Calculating Fuel Economy");
	 	printf("\n2 - Calculating Distance Traveled");
		printf("\n3 - Revised Fuel Economy Calculation");
		printf("\n4 - Quit\n");
		printf("\nChoice feature: ");
		scanf("%d",&select);
	
		switch(select){
			case 1:
				function_Calc_Fuel(time,averagespeed,gasoline);
				break;
			case 2:
				fuction_Calc_Dis(r,revolution,PI);
				break;
			case 3:
				RevisedFuelEconomy(r,revolution,g,PI);
				break;
			case 4:
				break;
		}
	}
	while(select>0&&select<4);
}
