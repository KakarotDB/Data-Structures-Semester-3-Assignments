#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STUDENTS 100
//functions available in the program :
//add - adds student in register 
//get - gets student(if present) with roll number 
//delete - deletes 
//modify - modifies
//sort - sorts 
//file handling functions will be implemented later, this is the first version done in
//lab (dated - 25th July 2025)
//Work done after lab (Home) : 
//Added file handilng functions for exporting and loading, fixed errors, added main function
//Done on 25th July, 2025.
//Finished main method on 26th July, 2025. Debugging on 27th.
//Finished debugging on 27th. Functions work properly.
typedef struct {
	char name[51];
	int roll;
	char telephone[13];
	char address[120];
}student;

typedef struct {
	int count;
	student studentArray[MAX_STUDENTS];
}studentRegister;

int add(studentRegister* sReg, student s){ //adds a Student in the register
    if (sReg == NULL)
    {
        return 0; //return 0 if register is null
    }
    if (sReg->count >= MAX_STUDENTS)
    {
        return 0; //return 0 if register has max students
    }
	for(int i = 0; i < sReg->count; i++){
		if(sReg->studentArray[i].roll == s.roll){
			return 0; //If Already present, returns 0
		}
	}
	sReg->studentArray[sReg->count] = s;
	sReg->count++;
	return 1; //returns 1 for successfull operation
}

int get(studentRegister* sReg, int roll){ //gets a student from the register
    if(sReg == NULL || sReg->count == 0){
        return -1; //no students in register
    }
	for(int i = 0; i < sReg->count; i++){
		if(sReg->studentArray[i].roll == roll) { 
			return i; //returns index of found student
		}
    }
	return -1; //student not found in register
}

int delete(studentRegister* sReg, int roll) { //deletes student from register by rewriting 
	if(sReg == NULL || sReg->count == 0)
    {
        return 0; 
    }
    int foundIndex = -1;
    for (int i = 0; i < sReg->count; i++)
    {
        if (sReg->studentArray[i].roll == roll)
        {
            foundIndex = i; //returns index of student if present in register
            break;
        }    
    }
    if (foundIndex == -1)
    {
        return 0; //if student is not present in register
    }
    for (int i = foundIndex; i < sReg->count - 1; i++)
    {
        sReg->studentArray[i] = sReg->studentArray[i + 1]; //overrides (deletes) current position student 
                                                           //and replaces it with the next position, for all positions
    }
    sReg->count--; //decreases count by 1
    return 1; //1 for successfull operation
}

int modify(studentRegister* sReg, student s) {
    if (sReg == NULL || sReg->count == 0) return 0;
	for (int i = 0; i < sReg->count; i++)
    {
        if (s.roll == sReg->studentArray[i].roll)
        {
            strcpy(sReg->studentArray[i].name, s.name);
            sReg->studentArray[i].roll = s.roll;
            strcpy(sReg->studentArray[i].telephone, s.telephone);
            strcpy(sReg->studentArray[i].address, s.address);
            return 1; //returns 1 for successfull operation, 0 otherwise.
        }     
    }
    return 0;
}

void sortStudents(studentRegister* sReg) {
    if (sReg == NULL || sReg->count == 0)
    {
        return;
    }
	int n = sReg->count;
	student temp;
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++) {
			if (strcmp(sReg->studentArray[j].name, sReg->studentArray[j + 1].name) > 0)
            {
                temp = sReg->studentArray[j];
                sReg->studentArray[j] = sReg->studentArray[j + 1];
                sReg->studentArray[j + 1] = temp;
                //bubble sort algorithm O(n^2)
            }
            
        }
    }
}

int count(studentRegister sReg) {
	return sReg.count + 1;
}

int exportRegister(studentRegister* sReg, char* fname) { //export register to file
    if(sReg == NULL || fname == NULL || strlen(fname) == 0) {
        printf("Error : Invalid register or filename provided for export\n");
        return 0;
    }
    FILE *file = fopen(fname, "wb");
    if (file == NULL)
    {
        printf("Error opening file");
        return 0;
    }
    if (fwrite(&sReg->count, sizeof(int), 1, file) != 1)
    {
        printf("Error writing student count to file");
        fclose(file);
        return 0;
    }
    if (fwrite(sReg->studentArray, sizeof(student), sReg->count, file) != (size_t) sReg->count)
    {
        printf("Error writing student data to file");
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1; //successfull operation
}

int loadRegister(studentRegister* sReg, char* fname) { //loading register from file
    if (sReg == NULL || fname == NULL || strlen(fname) == 0)
    {
        printf("Error : Invalid register or filename provided for load\n");
        return 0;
    }
    FILE *file = fopen(fname, "rb");
    if (file == NULL)
    {
        printf("Error loading file !");
        return 0;
    }
    sReg->count = 0;
    int loadedCount = 0;
    if (fread(&loadedCount, sizeof(int), 1, file) != 1)
    {
        printf("Error reading student count from file !");
        fclose(file);
        return 0;    
    }
    if (loadedCount < 0 || loadedCount > MAX_STUDENTS)
    {
        printf("Error: Invalid student count found in the file - (%d)\n", loadedCount);
        fclose(file);
        return 0;
    }
    if (fread(sReg->studentArray, sizeof(student), loadedCount, file) != (size_t) loadedCount)
    {
        printf("Error reading student data from file");
        fclose(file);
        return 0;
    }
    sReg->count = loadedCount;
    fclose(file);
    return 1;
}

int countDigits(int n) { //counting Digits of a number (Used to check for correct Roll No. Input)
    int count = 0;
    while(n > 0) {
        n/=10;
        count++;
    }
    return count;
}

int main(){
    //variable declaration zone
    studentRegister reg; 
    reg.count = 0; //initializing count of students to 0 
    int choice = 0;
    student temp_student; //temp student for input
    int roll_input = 0;
    char filename[100];
    int operation_result_flag = -1;
    int current_student_index = -1;
    printf("Welcome to student register program, Enter : \n"
		   "1 : Add a student\n"
		   "2 : Get a student\n"
		   "3 : Delete a Student from the register\n"
		   "4 : Modify student record\n"
		   "5 : Sort all students alphabetically\n"
           "6 : Save register to file\n" 
           "7 : Load register from file\n" 
	);
    do {
        printf("\nEnter your choice (0 to exit) : ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        switch(choice) {
            case 1: //adding student
                printf("Enter details of student (Last_Name, First name) : ");
                fgets(temp_student.name, sizeof(temp_student.name), stdin);
                temp_student.name[strcspn(temp_student.name, "\n")] = '\0';
                printf("Roll No. : ");
                scanf("%d", &temp_student.roll);
                if(countDigits(temp_student.roll) != 6)
                {
                    printf("Roll number has to be six digits! Enter choice again");
                    continue;
                }
                
                while(getchar() != '\n');
                printf("Telephone number [XXXXX XXXXX] : ");
                fgets(temp_student.telephone, sizeof(temp_student.telephone), stdin);
                temp_student.telephone[strcspn(temp_student.telephone, "\n")] = '\0';
                if (strlen(temp_student.telephone) == 0)
                {
                    printf("Telephone number cannot be empty ! Choose again");
                    continue;
                }
                printf("Address : ");
                fgets(temp_student.address, sizeof(temp_student.address), stdin);
                temp_student.address[strcspn(temp_student.address, "\n")] = '\0';
                
                operation_result_flag = add(&reg, temp_student);
                if (operation_result_flag == 0)
                {
                    printf("Student already exists in register /Error Occurred");
                }
                else
                    printf("Student added succcessfully!");
                break;
            case 2: //getting student
                printf("Enter roll number to get details of student : ");
                scanf("%d", &roll_input);
                if (countDigits(roll_input) != 6)
                {
                    printf("Roll numbers should be inputted in six digit format with no leading zeroes !");
                    continue;
                }
                current_student_index = get(&reg, roll_input);
                if (current_student_index == -1)
                {
                    printf("This roll no. does not exist in the register");
                }
                else {
                    printf("Successfully found student!\n"
                           "Details are as follows : \n"
                           "Name : %s\n"
                           "Roll : %d\n"
                           "Telephone : %s\n"
                           "Address : %s\n",
                           reg.studentArray[current_student_index].name,
                           reg.studentArray[current_student_index].roll,
                           reg.studentArray[current_student_index].telephone,
                           reg.studentArray[current_student_index].address
                    );
                }
                break;
            case 3: //deleting student
                printf("Enter roll number of student to delete : ");
                scanf("%d", &roll_input);
                operation_result_flag = delete(&reg, roll_input);
                if (operation_result_flag == 1)
                {
                    printf("Student deleted successfully");
                }
                else {
                    printf("Student with given roll number not found/deletion failed");
                }
                break;
            case 4: //modifying student record
                printf("Enter roll number of student to modify : ");
                scanf("%d", &temp_student.roll);
                while(getchar() != '\n');
                operation_result_flag = get(&reg, temp_student.roll);
                if (operation_result_flag == -1)
                {
                    printf("Student does not exist inside register");
                    continue;
                }
                printf("Enter new name [Last name, First name] : ");
                fgets(temp_student.name, sizeof(temp_student.name), stdin);
                temp_student.name[strcspn(temp_student.name, "\n")] = '\0';
                printf("Enter new telephone number : ");
                fgets(temp_student.telephone, sizeof(temp_student.telephone), stdin);
                temp_student.telephone[strcspn(temp_student.telephone, "\n")] = '\0';
                printf("Enter new address : ");
                fgets(temp_student.address, sizeof(temp_student.address), stdin);
                temp_student.address[strcspn(temp_student.address, "\n")] = '\0';

                operation_result_flag = modify(&reg, temp_student);
                if (operation_result_flag == 1)
                {
                    printf("Student with given roll no. successfully modified");
                }
                else
                    printf("Student could not be modified!");
                break;
            case 5: //sorting students alphabetically
                sortStudents(&reg);
                printf("Students sorted in alphabetical order!\n");
                printf("Current student list after sorting : \n");
                if (reg.count == 0)
                {
                    printf("Register is empty\n");
                }
                else {
                    for (int i = 0; i < reg.count; i++)
                    {
                        printf("%d. Name : %s\n   Roll : %d\n", i + 1, 
                            reg.studentArray[i].name, reg.studentArray[i].roll);
                    }
                }
                break;
            case 6: //saving to register
                printf("Enter a filename to save the register : ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                if (exportRegister(&reg, filename) == 1)
                {
                    printf("Register successfully saved to %s. \n", filename);
                }
                else
                    printf("Failed to save register!");
                break;
            case 7: 
                printf("Enter filename to load register from : ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                operation_result_flag = loadRegister(&reg, filename);
                if (operation_result_flag == 1)
                {
                    printf("Successfully loaded the register!");
                }
                else {
                    printf("Failed to load register!");
                }
                break;
            default:
                printf("Wrong choice!/Exited Program");
                break;            
        }
    }
    while(choice != 0);
    return 0;
}
