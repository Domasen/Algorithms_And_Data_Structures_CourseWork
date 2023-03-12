//3 homework - Domas Nemanius
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER 0
#define UPPER 100
#define CLIENTS 1000

#define EXPERIENCED_WORKING_TIME 15
#define INEXPERIENCED_WORKING_TIME 30

//bank staff structure
typedef struct Cashier {
    int totalServiseTime;		//how much time the employee worked in total
	int freeTime;
	int serviceTime;			
	int remainingServiceTime;			
} Cashier;

//bank customer structure
typedef struct Client {
	int waitingTicket;
	int waitingTime;
} Client;

//Function prototypes
int random(int lower, int upper);
void inicializesExperiencedCashiersStructure(Cashier experiencedCashierArray[], int numberOfExperiencedCashiers);
void inicializesInexperiencedCashiersStructure(Cashier inexperiencedCashierArray[], int numberOfInexperiencedCashiers);
void clientWaitingTime(Client clientArray[], int inProgressClients, int queueSize);
float averageClientWaitingTime(Client clientArray[], int queueSize);
int maxClientWaitingTime(Client clientArray[], int queueSize);
float averageCashierEmployment(int numberOfExperiencedCashiers, int numberOfInexperiencedCashiers, Cashier inexperiencedCashierArray[],
							   Cashier experiencedCashierArray[], int workingTime);
void printExperiencedCashiersStatistics(Cashier experiencedCashierArray[], int numberOfExperiencedCashiers);
void printInexperiencedCashiersStatistics( Cashier inexperiencedCashierArray[], int numberOfInexperiencedCashiers);
void printClientsStatistics(Client clientArray[], int queueSize);

int main() {
	time_t t;
	srand((unsigned) time(&t));
	int queueSize = 0;
	int maxQueueSize = 0;
	int absentClient = 0;
	int inProgressClients = 0;	//how many customers are being served at the moment
	int doneClients = 0;
	int workingTime = 0;
	
	int numberOfInexperiencedCashiers;
	int numberOfExperiencedCashiers;

	printf("Enter number of experieced cashiers: ");
	scanf("%d", &numberOfExperiencedCashiers);
	printf("Enter number of inexperieced cashiers: ");
	scanf("%d", &numberOfInexperiencedCashiers);
	
	if(numberOfExperiencedCashiers <= 0 && numberOfInexperiencedCashiers <= 0) {
		printf("Bank can't work without cashiers");
		return 0;
	}

	int probabilityOfArrivalOfTheCustomers = 50;
	
	//inicialization of experienced bank employees
	Cashier experiencedCashierArray[numberOfExperiencedCashiers];
	inicializesExperiencedCashiersStructure(experiencedCashierArray, numberOfExperiencedCashiers);
	
	//inicialization of inexperienced bank employees
	Cashier inexperiencedCashierArray[numberOfInexperiencedCashiers];
	inicializesInexperiencedCashiersStructure(inexperiencedCashierArray, numberOfInexperiencedCashiers);
	
	
	Client *clientArray = (Client*) calloc(0, sizeof(Client)); 

	int isBankClosed = 0;
	int bankWorkingLimit = 480;	//after a while the bank does not accept customers 
	while(!isBankClosed) {
		if (bankWorkingLimit > 0) {
			int probability = random(LOWER, UPPER);
			if(probability <= probabilityOfArrivalOfTheCustomers) {
				queueSize++;
				clientArray = (Client*) realloc(clientArray, queueSize * sizeof(Client));
				clientArray[queueSize-1].waitingTicket = queueSize;
				clientArray[queueSize-1].waitingTime = 0;
				
				if (queueSize - inProgressClients > maxQueueSize) maxQueueSize = queueSize - inProgressClients;
			} else {
				absentClient++;
			}
		}

		
		if (queueSize > inProgressClients) {
			for(int i = 0; i < numberOfExperiencedCashiers; ++i) {
				if (experiencedCashierArray[i].remainingServiceTime == 0) { //checks if there is a free cashier
					experiencedCashierArray[i].remainingServiceTime = experiencedCashierArray[i].serviceTime; 
					inProgressClients++; 
				}
				
				if (queueSize == inProgressClients) break;
			}		
		}

		if (queueSize > inProgressClients) {
			for(int i = 0; i < numberOfInexperiencedCashiers; ++i) {
				if (inexperiencedCashierArray[i].remainingServiceTime == 0) {
					inexperiencedCashierArray[i].remainingServiceTime = inexperiencedCashierArray[i].serviceTime;
					inProgressClients++;
				}
				
				if (queueSize == inProgressClients) break;
			}		
		}
		
		for(int i = 0; i < numberOfExperiencedCashiers; ++i) {
			if (experiencedCashierArray[i].remainingServiceTime > 0) {
				//calculates how many Clients have already been served
				if (experiencedCashierArray[i].remainingServiceTime == 1) {
					doneClients++;	
				}
				experiencedCashierArray[i].remainingServiceTime--;
				experiencedCashierArray[i].totalServiseTime++;
			} else {
				experiencedCashierArray[i].freeTime++;
			}
		}
		
		for(int i = 0; i < numberOfInexperiencedCashiers; ++i) {
			if (inexperiencedCashierArray[i].remainingServiceTime > 0) {
				if (inexperiencedCashierArray[i].remainingServiceTime == 1) {
					doneClients++;
				}
				inexperiencedCashierArray[i].remainingServiceTime--;
				inexperiencedCashierArray[i].totalServiseTime++;
			} else {
				inexperiencedCashierArray[i].freeTime++;
			}
		}
		
		
		clientWaitingTime(clientArray, inProgressClients, queueSize);
		
		workingTime++;
		bankWorkingLimit--;	//minus to prevent customers from coming after business hours
		if (bankWorkingLimit < 0 && doneClients == queueSize) isBankClosed = 1;
	}
	

	printf("-----------------------------------------------------------------------\n");
	printf("Bank working time: %d minutes, which is equivalent to %d hours and %d minutes\n",
			workingTime, workingTime/60, workingTime%60);
	printf("Worked overtime: %d minutes, which is equivalent to %d hours and %d minutes\n",
			bankWorkingLimit * -1, (bankWorkingLimit * -1) / 60, (bankWorkingLimit * -1) % 60);
	printf("Average Cachier employment is %.0f %% \n", averageCashierEmployment(numberOfExperiencedCashiers,
													   numberOfInexperiencedCashiers, inexperiencedCashierArray,
							   						   experiencedCashierArray, workingTime));
	printf("-----------------------------------------------------------------------\n");		
	printf("Number of customers served: %d\n", doneClients);
	printf("Average client waiting time is: %.2f minutes\n", averageClientWaitingTime(clientArray, queueSize));
	printf("Maximum client waiting time is: %d minutes\n", maxClientWaitingTime(clientArray, queueSize));
	printf("-----------------------------------------------------------------------\n");
	printf("Max queue size %d\n", maxQueueSize);
	printf("Absent customers: %d\n", absentClient);
	printf("-----------------------------------------------------------------------\n");


	printExperiencedCashiersStatistics(experiencedCashierArray, numberOfExperiencedCashiers);

	printInexperiencedCashiersStatistics(inexperiencedCashierArray, numberOfInexperiencedCashiers);
	
	//printClientsStatistics(clientArray, queueSize);
	
	return 0;
}

//Generate random number
int random(int lower, int upper){
	return (rand() % (upper - lower + 1)) + lower;
}

//Inicializes the numberOfExperiencedCashiers Structure
void inicializesExperiencedCashiersStructure(Cashier experiencedCashierArray[], int numberOfExperiencedCashiers){
	for(int i = 0; i < numberOfExperiencedCashiers; ++i) {
		experiencedCashierArray[i].totalServiseTime = 0;
		experiencedCashierArray[i].freeTime = 0;
		experiencedCashierArray[i].serviceTime = EXPERIENCED_WORKING_TIME;
		experiencedCashierArray[i].remainingServiceTime = 0;
	}
}

//Inicializes the numberOfInexperiencedCashiers Structure
void inicializesInexperiencedCashiersStructure(Cashier inexperiencedCashierArray[], int numberOfInexperiencedCashiers){
	for(int i = 0; i < numberOfInexperiencedCashiers; ++i) {
		inexperiencedCashierArray[i].totalServiseTime = 0;
		inexperiencedCashierArray[i].freeTime = 0;
		inexperiencedCashierArray[i].serviceTime = INEXPERIENCED_WORKING_TIME;
		inexperiencedCashierArray[i].remainingServiceTime = 0;
	}
}

//a function that finds the clent's  waiting time 
void clientWaitingTime(Client clientArray[], int inProgressClients, int queueSize){
	for(int i = inProgressClients; i < queueSize; ++i) {
		clientArray[i].waitingTime++;
	}
}
	
//a function that finds the average customer wait time 
float averageClientWaitingTime(Client clientArray[], int queueSize){
	int timeSum = 0;
	float averageWaitingTime = 0;
	for(int i = 0; i < queueSize; ++i){
		timeSum += clientArray[i].waitingTime;
	}
	averageWaitingTime = timeSum/queueSize;
	return averageWaitingTime;
}

//a function that finds the maximum customer wait time 
int maxClientWaitingTime(Client clientArray[], int queueSize){
	int maxWaitingTime = 0;
	for(int i = 0; i < queueSize; ++i){
		if(clientArray[i].waitingTime > maxWaitingTime){
			maxWaitingTime = clientArray[i].waitingTime;
		}
	}
	return maxWaitingTime;
}
	
//a function that finds the percentage of average employment
float averageCashierEmployment(int numberOfExperiencedCashiers, int numberOfInexperiencedCashiers, Cashier inexperiencedCashierArray[],
							   Cashier experiencedCashierArray[], int workingTime){
	int allCashiers = numberOfExperiencedCashiers + numberOfInexperiencedCashiers;
	int allCashiersWorkingTime = 0, experiencedCashiersWorkingTime = 0, 
	inexperiencedCashiersWorkingTime = 0;
	float averageAllCaschiersWorkingTime = 0;
	float Workingpercentage;
	
	for(int i = 0; i < numberOfExperiencedCashiers; ++i){
		experiencedCashiersWorkingTime += experiencedCashierArray[i].totalServiseTime;
	}
	
	for(int i = 0; i < numberOfInexperiencedCashiers; ++i){
		inexperiencedCashiersWorkingTime += inexperiencedCashierArray[i].totalServiseTime;
	}
	
	allCashiersWorkingTime = experiencedCashiersWorkingTime + inexperiencedCashiersWorkingTime;
	averageAllCaschiersWorkingTime = (allCashiersWorkingTime)/allCashiers;
	Workingpercentage = (averageAllCaschiersWorkingTime/workingTime)*100;
	return Workingpercentage;
}

//a function that prints inexperienced caschiers statistics
void printExperiencedCashiersStatistics(Cashier experiencedCashierArray[], int numberOfExperiencedCashiers){
	printf("Experienced cashiers:\n");
	
	for(int i = 0; i < numberOfExperiencedCashiers; ++i) {
		printf("Cashier no: %d\n", i + 1);
		printf("Free time: %d minutes\n", experiencedCashierArray[i].freeTime);
		printf("Working time: %d minutes, which is equivalent to %d hours and %d minutes\n", 
		experiencedCashierArray[i].totalServiseTime, experiencedCashierArray[i].totalServiseTime / 60,
		experiencedCashierArray[i].totalServiseTime % 60);
		printf("**************************\n");
	}
	printf("-----------------------------------------------------------------------\n");
}

//a function that prints experienced caschiers statistics
void printInexperiencedCashiersStatistics(Cashier inexperiencedCashierArray[], int numberOfInexperiencedCashiers){
	printf("Inexperienced cashiers:\n");
	
	for(int i = 0; i < numberOfInexperiencedCashiers; ++i) {
		printf("Cashier no: %d\n", i + 1);
		printf("Free time: %d minutes\n", inexperiencedCashierArray[i].freeTime);
		printf("Working time: %d minutes, which is equivalent to %d hours and %d minutes\n", 
		inexperiencedCashierArray[i].totalServiseTime, inexperiencedCashierArray[i].totalServiseTime / 60,
		inexperiencedCashierArray[i].totalServiseTime % 60);
		printf("**************************\n");
	}
	printf("-----------------------------------------------------------------------\n");
}
	
//a function that prints customers statistics
void printClientsStatistics(Client clientArray[], int queueSize){
	printf("Clients:\n");
	
	for(int i = 0; i < queueSize; ++i) {
		printf("Client no: %d\n", i + 1);
		printf("Client waiting ticket: %d\n", clientArray[i].waitingTicket);
		printf("Client waiting time: %d minutes, which is equivalent to %d hours and %d minutes\n", 
		clientArray[i].waitingTime, clientArray[i].waitingTime / 60, clientArray[i].waitingTime % 60);
		printf("**************************\n");
	}
	printf("-----------------------------------------------------------------------\n");
}

