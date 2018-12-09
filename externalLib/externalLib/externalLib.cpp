#include "externalLib.h"
int main()
{
	Customer* head = fileToList();

	printList(head);
	if (head != NULL)
		freeMem(head);

	getchar();
}

Customer* fileToList()
{
	std::ifstream CustomersFile("Customers.txt");
	if (!CustomersFile.is_open())
	{
		std::cout << "Error opening Customers.txt!\n";
		return NULL;
	}
	string currLine = "";
	string brokenInfo;
	Customer* head = NULL;
	Customer* temp = NULL;
	while (CustomersFile.peek() != EOF)
	{
		if (head == NULL)
		{
			temp = new Customer();
			head = temp;
		}
		else
		{
			temp->next = new Customer();
			temp = temp->next;
		}
		std::getline(CustomersFile, currLine);
		std::getline(CustomersFile, currLine);
		brokenInfo = currLine.substr(currLine.find("Name:") + 5);
		strcpy(temp->firstname, brokenInfo.substr(0, brokenInfo.find(' ')).c_str());
		strcpy(temp->lastname, brokenInfo.substr(brokenInfo.find(' ') + 1).c_str());

		std::getline(CustomersFile, currLine);
		strcpy(temp->id, currLine.substr(currLine.find("Id:") + 3).c_str());

		std::getline(CustomersFile, currLine);
		strcpy(temp->email, currLine.substr(currLine.find("Email:") + 6).c_str());

		std::getline(CustomersFile, currLine);
		strcpy(temp->phone, currLine.substr(currLine.find("Phone:") + 6).c_str());

		std::getline(CustomersFile, currLine);
		brokenInfo = currLine.substr(currLine.find("Birthdate:") + 10);
		if (brokenInfo != "")
		{
			temp->birthday.day = atoi(brokenInfo.substr(0, 2).c_str());
			temp->birthday.month = atoi(brokenInfo.substr(3, 2).c_str());
			temp->birthday.year = atoi(brokenInfo.substr(6, 4).c_str());
		}

		std::getline(CustomersFile, currLine);
		temp->status = atoi(currLine.substr(currLine.find("Status:") + 7).c_str());

		std::getline(CustomersFile, currLine);
		brokenInfo = currLine.substr(currLine.find("Insertion date:") + 15);
		if (brokenInfo != "")
		{
			temp->inserted.day = atoi(brokenInfo.substr(0, 2).c_str());
			temp->inserted.month = atoi(brokenInfo.substr(3, 2).c_str());
			temp->inserted.year = atoi(brokenInfo.substr(6, 4).c_str());
		}
		std::getline(CustomersFile, currLine);
		brokenInfo = currLine.substr(currLine.find("Courses:") + 8);
		if (brokenInfo != "")
		{

			char str[12];
			strcpy(str, brokenInfo.c_str());
			char* course = strtok(str, ",");
			while (course != NULL)
			{
				temp->courses[atoi(course) - 1] = true;
				course = strtok(NULL, ",");
			}
		}

	}
	assignHistory(head);
	CustomersFile.close();
	return head;
}
void assignHistory(Customer* head)
{
	std::ifstream historyFile("History.txt");
	if (!historyFile.is_open())
	{
		std::cout << "Error opening History.txt!\n";
		return;
	}
	string currLine = "";
	string id;
	Customer* nodeToInsert = NULL;
	string brokenInfo;
	while (historyFile.peek() != EOF)
	{
		std::getline(historyFile, currLine);
		if (currLine == "****")
		{
			std::getline(historyFile, currLine);
			id = currLine.substr(currLine.find("Id:") + 3);
			nodeToInsert = findNodeById(id, head);
			if (nodeToInsert == NULL)//in case Customer does not exist
				continue;
			std::getline(historyFile, currLine);
			strcpy(nodeToInsert->history[nodeToInsert->history_amount].representativeName, (currLine.substr(currLine.find("Rep. name:") + 10)).c_str());
			std::getline(historyFile, currLine);
			strcpy(nodeToInsert->history[nodeToInsert->history_amount].representativeId, (currLine.substr(currLine.find("Rep. id:") + 8)).c_str());
			std::getline(historyFile, currLine);
			brokenInfo = currLine.substr(currLine.find("Date:") + 5);
			if (brokenInfo != "")
			{
				nodeToInsert->history[nodeToInsert->history_amount].date.day = atoi(brokenInfo.substr(0, 2).c_str());
				nodeToInsert->history[nodeToInsert->history_amount].date.month = atoi(brokenInfo.substr(3, 2).c_str());
				nodeToInsert->history[nodeToInsert->history_amount].date.year = atoi(brokenInfo.substr(6, 4).c_str());
			}
			nodeToInsert->history_amount++;
			std::getline(historyFile, currLine);//get rid of "Note:"
			continue;
		}
		if (nodeToInsert == NULL)//in case Customer does not exist
			continue;

		strcat(nodeToInsert->history[nodeToInsert->history_amount - 1].Note, (currLine + '\n').c_str());

	}
}
Customer* findNodeById(string id, Customer* Node)
{
	while (Node != NULL)
	{
		if (id == Node->id)
			break;
		Node = Node->next;
	}
	return Node;
}

void printList(Customer* node)
{
	while (node != NULL)
	{
		std::cout << node->firstname << std::endl;

		std::cout << node->lastname << std::endl;

		std::cout << node->id << std::endl;

		std::cout << node->email << std::endl;

		std::cout << node->phone << std::endl;

		std::cout << node->status << std::endl;

		std::cout << node->birthday.day << "." << node->birthday.month << "." << node->birthday.year << std::endl;

		std::cout << node->inserted.day << "." << node->inserted.month << "." << node->inserted.year << std::endl;

		std::cout << node->courses[0] << ", " << node->courses[1] << ", " << node->courses[2] << ", " << node->courses[3] << ", "
			<< node->courses[4] << ", " << node->courses[5] << ", " << std::endl << std::endl;

		std::cout << "****History:****" << std::endl;
		for (int i = 0; i < node->history_amount; i++)
		{
			std::cout << i + 1 << std::endl << node->history[i].date.day << "." << node->history[i].date.month << "." << node->history[i].date.year << std::endl << node->history[i].representativeName
				<< std::endl << node->history[i].representativeId << std::endl << "Note:\n" << node->history[i].Note << std::endl << "---" << std::endl;
		}
		std::cout << "****************" << std::endl << std::endl;
		node = node->next;
	}
}
void freeMem(Customer* Node)
{
	if (Node->next != NULL)
		freeMem(Node->next);
	delete Node;
}

Customer* listToArray(int* size) {
	Customer* cust_arr = new Customer[globalList.size];
	
	for (int i = 0; i < globalList.size; i++) {
		cust_arr[i] = *ExtractFromList(i)->customer;
	}
	*size = globalList.size;
	return cust_arr;
}

void freeArray(Customer* arr) {
	delete[] arr;
	arr = NULL;
}

std::string DateToStr(Date date) {
	//date -> xx/xx/xxxx'\0'
	std::string str;
	str += std::to_string(date.day) + "/" + std::to_string(date.month) + "/" + std::to_string(date.year);
	return str;
}

void AddToList( Customer &customer) {
	if (globalList.head == nullptr) {
		globalList.head = new Node;
		globalList.head->customer = &customer;
	}
	else if (globalList.tail == nullptr) {
		globalList.tail = new Node;
		globalList.tail->customer = &customer;
		globalList.head->next = globalList.tail;
	}
	else {
		Node* node = new Node;
		node->previous = globalList.tail;
		node->customer = &customer;
		globalList.tail->next = node;
		globalList.tail = node;
	}
	globalList.size++;
}

void RemoveNode(Node *node) {
	if (globalList.head == node) {
		globalList.head = node->next;
	}
	else if (globalList.tail == node) {
		globalList.tail->previous->next = nullptr;
		globalList.tail = node->previous;

	}
	else {
		node->next->previous = node->previous;
		node->previous->next = node->next;
	}
	delete node;
	globalList.size--;
}

Node* ExtractFromList(int index) {
	Node* node;
	if (globalList.head != nullptr) {
		node = globalList.head;
		for (int i = 0; i < index; i++) {
			if (node->next != nullptr) {
				node = node->next;
			}
			else
			{
				break;
			}
		}
		return node;
	}
	return NULL;
}

bool AddToEOF(Customer cust) {
	///Add new customer to the end of file.

	string file_name = "Customers";
	string txt = "****\n";
	string line = "";
	std::ofstream file_out(file_name + ".txt", std::ios::app);
	if (!file_out.is_open())
	{
		return false;
	}

	txt += cust.firstname;
	txt += "\n";
	txt += cust.lastname;
	txt += "\n";
	txt += cust.id;
	txt += "\n";
	txt += cust.phone;
	txt += "\n";
	txt += cust.email;
	txt += "\n";
	txt += DateToStr(cust.birthday);
	txt += "\n";
	txt += DateToStr(cust.inserted);
	txt += "\n****\n";


	file_out << txt;

	file_out.close();

	return true;
}