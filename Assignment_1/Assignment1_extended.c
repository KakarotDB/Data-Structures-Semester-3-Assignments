#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADD(a, b) (a+b)

#define FREE(a) {free(a); a = NULL;} //macro to free dynamically allocated memory and set it to null

//Assignment 1 extension - Making a student register via dynamic memory allocation
//Started on 29th July, 2025. Most functions completed by 30th July, 2025.
//Completed program on 30th July, 2025.
typedef struct Student {
    char *name;
    int roll;
    char telephone[13];
    char *address;
} Student;

typedef struct SReg {
    int maxStuds;
    int count;
    Student **arrStudPtr;
} SReg;

Student* createStudentRecord() {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        return NULL;
    }

    char tempBuffer[256]; //temporary buffer for inputs

    printf("Enter student name: ");
    fgets(tempBuffer, sizeof(tempBuffer), stdin);
    tempBuffer[strcspn(tempBuffer, "\n")] = '\0'; //replacing new line character with null terminator
    newStudent->name = (char *)malloc(strlen(tempBuffer) + 1); //+1 for null terminated character
    if (newStudent->name == NULL) {
        free(newStudent);
        return NULL;
    }
    strcpy(newStudent->name, tempBuffer);

    printf("Enter roll number: ");
    scanf("%d", &newStudent->roll);
    while (getchar() != '\n');

    printf("Enter telephone number (max 10 digits): ");
    fgets(newStudent->telephone, sizeof(newStudent->telephone), stdin);
    newStudent->telephone[strcspn(newStudent->telephone, "\n")] = '\0'; //replacing newline character from fgets() with null-character

    printf("Enter address: ");
    fgets(tempBuffer, sizeof(tempBuffer), stdin);
    tempBuffer[strcspn(tempBuffer, "\n")] = '\0';
    newStudent->address = (char *)malloc(strlen(tempBuffer) + 1);
    if (newStudent->address == NULL) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }
    strcpy(newStudent->address, tempBuffer);

    return newStudent;
}

Student* createStudentRecordFromFile(FILE *file) {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        return NULL;
    }

    int name_len, address_len;

    if (fread(&name_len, sizeof(int), 1, file) != 1) {
        free(newStudent);
        return NULL;
    }
    newStudent->name = (char *)malloc(name_len);
    if (newStudent->name == NULL) {
        free(newStudent);
        return NULL;
    }
    if (fread(newStudent->name, sizeof(char), name_len, file) != (size_t)name_len) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }

    if (fread(&newStudent->roll, sizeof(int), 1, file) != 1) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }

    if (fread(newStudent->telephone, sizeof(char), sizeof(newStudent->telephone), file) != sizeof(newStudent->telephone)) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }

    if (fread(&address_len, sizeof(int), 1, file) != 1) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }
    newStudent->address = (char *)malloc(address_len);
    if (newStudent->address == NULL) {
        free(newStudent->name);
        free(newStudent);
        return NULL;
    }
    if (fread(newStudent->address, sizeof(char), address_len, file) != (size_t)address_len) {
        free(newStudent->name);
        free(newStudent->address);
        free(newStudent);
        return NULL;
    }

    return newStudent;
}


void freeStudentRecord(Student *sp) {
    if (sp == NULL) {
        return;
    }
    FREE(sp->name);
    FREE(sp->address);
    FREE(sp);
}

int add(SReg* sReg, Student* s) { //adds a Student in the register
    if (sReg == NULL || s == NULL) {
        return 0; //return 0 if register or student is null
    }
    if (sReg->count >= sReg->maxStuds) {
        printf("Register is full. Cannot add more students.\n");
        return 0; //return 0 if register has max students
    }
    for (int i = 0; i < sReg->count; i++) {
        if (sReg->arrStudPtr[i]->roll == s->roll) {
            return 0; //If Already present, returns 0
        }
    }
    sReg->arrStudPtr[sReg->count] = s;
    sReg->count++;
    return 1; //returns 1 for successful operation
}

int get(SReg* sReg, int roll) { //gets a student from the register with same roll number
    if (sReg == NULL || sReg->count == 0) {
        return -1; //no students in register
    }
    for (int i = 0; i < sReg->count; i++) {
        if (sReg->arrStudPtr[i]->roll == roll) {
            return i; //returns index of found student
        }
    }
    return -1; //student not found in register
}

int delete(SReg* sReg, int roll) { //deletes student from register by rewriting
    if (sReg == NULL || sReg->count == 0) {
        return 0;
    }
    int foundIndex = -1;
    for (int i = 0; i < sReg->count; i++) {
        if (sReg->arrStudPtr[i]->roll == roll) {
            foundIndex = i; //returns index of student if present in register
            break;
        }
    }
    if (foundIndex == -1) {
        return 0; //if student is not present in register
    }

    freeStudentRecord(sReg->arrStudPtr[foundIndex]);

    for (int i = foundIndex; i < sReg->count - 1; i++) {
        sReg->arrStudPtr[i] = sReg->arrStudPtr[i + 1]; //overrides (deletes) current position student
                                                        //and replaces it with the next position, for all positions
    }
    sReg->count--; //decreases count by 1
    return 1; //1 for successful operation
}

int modify(SReg* sReg, Student* s) {
    if (sReg == NULL || sReg->count == 0 || s == NULL) return 0;
    for (int i = 0; i < sReg->count; i++) {
        if (s->roll == sReg->arrStudPtr[i]->roll) {
            free(sReg->arrStudPtr[i]->name);
            free(sReg->arrStudPtr[i]->address);

            sReg->arrStudPtr[i]->name = (char *)malloc(strlen(s->name) + 1);
            if (sReg->arrStudPtr[i]->name == NULL) return 0;
            strcpy(sReg->arrStudPtr[i]->name, s->name);

            strcpy(sReg->arrStudPtr[i]->telephone, s->telephone);

            sReg->arrStudPtr[i]->address = (char *)malloc(strlen(s->address) + 1);
            if (sReg->arrStudPtr[i]->address == NULL) {
                free(sReg->arrStudPtr[i]->name);
                return 0;
            }
            strcpy(sReg->arrStudPtr[i]->address, s->address);
            return 1; //returns 1 for successful operation, 0 otherwise.
        }
    }
    return 0;
}

void sortStudents(SReg* sReg) {
    if (sReg == NULL || sReg->count <= 1) {
        return;
    }
    int n = sReg->count;
    Student *temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(sReg->arrStudPtr[j]->name, sReg->arrStudPtr[j + 1]->name) > 0) {
                temp = sReg->arrStudPtr[j];
                sReg->arrStudPtr[j] = sReg->arrStudPtr[j + 1];
                sReg->arrStudPtr[j + 1] = temp;
                //bubble sort algorithm O(n^2)
            }
        }
    }
}

int exportRegister(SReg* sReg, char* fname) { //export register to file
    if (sReg == NULL || fname == NULL || strlen(fname) == 0) {
        printf("Error : Invalid register or filename provided for export\n");
        return 0;
    }
    FILE *file = fopen(fname, "wb");
    if (file == NULL) {
        printf("Error opening file");
        return 0;
    }

    if (fwrite(&sReg->maxStuds, sizeof(int), 1, file) != 1 ||
        fwrite(&sReg->count, sizeof(int), 1, file) != 1) {
        printf("Error writing SReg metadata to file");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < sReg->count; i++) {
        Student *s = sReg->arrStudPtr[i];
        int name_len = strlen(s->name) + 1;
        int address_len = strlen(s->address) + 1;

        if (fwrite(&name_len, sizeof(int), 1, file) != 1 ||
            fwrite(s->name, sizeof(char), name_len, file) != (size_t)name_len ||
            fwrite(&s->roll, sizeof(int), 1, file) != 1 ||
            fwrite(s->telephone, sizeof(char), sizeof(s->telephone), file) != sizeof(s->telephone) ||
            fwrite(&address_len, sizeof(int), 1, file) != 1 ||
            fwrite(s->address, sizeof(char), address_len, file) != (size_t)address_len) {
            printf("Error writing student data to file");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1; //successful operation
}

int loadRegister(SReg* sReg, char* fname) { //loading register from file
    if (sReg == NULL || fname == NULL || strlen(fname) == 0) {
        printf("Error : Invalid register or filename provided for load\n");
        return 0;
    }
    FILE *file = fopen(fname, "rb");
    if (file == NULL) {
        printf("Error loading file !");
        return 0;
    }

    for (int i = 0; i < sReg->count; i++) {
        freeStudentRecord(sReg->arrStudPtr[i]);
    }
    free(sReg->arrStudPtr);
    sReg->arrStudPtr = NULL;
    sReg->count = 0;
    sReg->maxStuds = 0;

    int loadedMaxStuds = 0;
    int loadedCount = 0;

    if (fread(&loadedMaxStuds, sizeof(int), 1, file) != 1 ||
        fread(&loadedCount, sizeof(int), 1, file) != 1) {
        printf("Error reading SReg metadata from file !");
        fclose(file);
        return 0;
    }

    if (loadedCount < 0 || loadedCount > loadedMaxStuds) {
        printf("Error: Invalid student count found in the file - (%d)\n", loadedCount);
        fclose(file);
        return 0;
    }

    sReg->arrStudPtr = (Student **)malloc(sizeof(Student *) * loadedMaxStuds);
    if (sReg->arrStudPtr == NULL) {
        printf("Memory allocation failed for arrStudPtr during load !");
        fclose(file);
        return 0;
    }
    sReg->maxStuds = loadedMaxStuds;

    for (int i = 0; i < loadedCount; i++) {
        Student *loadedStudent = createStudentRecordFromFile(file);
        if (loadedStudent == NULL) {
            printf("Error reading student data from file");
            for (int j = 0; j < i; j++) {
                freeStudentRecord(sReg->arrStudPtr[j]);
            }
            free(sReg->arrStudPtr);
            sReg->arrStudPtr = NULL;
            sReg->count = 0;
            sReg->maxStuds = 0;
            fclose(file);
            return 0;
        }
        sReg->arrStudPtr[i] = loadedStudent;
        sReg->count++;
    }

    fclose(file);
    return 1;
}

int countDigits(int n) { //counting Digits of a number (Used to check for correct Roll No. Input)
    int count = 0;
    if (n == 0) return 1;
    while(n > 0) {
        n/=10;
        count++;
    }
    return count;
}

int main(){
    //variable declaration zone
    SReg reg;
    int max_students_input;

    printf("Enter the maximum number of students this register can hold: ");
    scanf("%d", &max_students_input);
    while (getchar() != '\n');

    if (max_students_input <= 0) {
        printf("Invalid maximum student count. Exiting.\n");
        return 1;
    }

    reg.maxStuds = max_students_input;
    reg.count = 0;
    reg.arrStudPtr = (Student **)malloc(sizeof(Student *) * reg.maxStuds);
    if (reg.arrStudPtr == NULL) {
        printf("Memory allocation failed for student register. Exiting.\n");
        return 1;
    }
    //variable declaration zone
    int choice = 0;
    Student *temp_student_ptr = NULL;
    int roll_input = 0;
    char filename[256];
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
                if (reg.count >= reg.maxStuds) {
                    printf("Cannot add student: Register is full (max %d students).\n", reg.maxStuds);
                    break;
                }
                temp_student_ptr = createStudentRecord();
                if (temp_student_ptr == NULL) {
                    printf("Failed to create student record due to memory error.\n");
                    break;
                }

                if(countDigits(temp_student_ptr->roll) != 6) {
                    printf("Roll number has to be six digits! Student not added.");
                    freeStudentRecord(temp_student_ptr);
                    break;
                }
                if (strlen(temp_student_ptr->telephone) == 0) {
                    printf("Telephone number cannot be empty ! Student not added.");
                    freeStudentRecord(temp_student_ptr);
                    break;
                }

                operation_result_flag = add(&reg, temp_student_ptr);
                if (operation_result_flag == 0) {
                    printf("Student already exists in register /Error Occurred");
                    freeStudentRecord(temp_student_ptr);
                } else {
                    printf("Student added successfully!");
                }
                break;
            case 2: //getting student
                printf("Enter roll number to get details of student : ");
                scanf("%d", &roll_input);
                if (countDigits(roll_input) != 6) {
                    printf("Roll numbers should be inputted in six digit format with no leading zeroes !");
                    continue;
                }
                current_student_index = get(&reg, roll_input);
                if (current_student_index == -1) {
                    printf("This roll no. does not exist in the register");
                } else {
                    printf("Successfully found student!\n"
                           "Details are as follows : \n"
                           "Name : %s\n"
                           "Roll : %d\n"
                           "Telephone : %s\n"
                           "Address : %s\n",
                           reg.arrStudPtr[current_student_index]->name,
                           reg.arrStudPtr[current_student_index]->roll,
                           reg.arrStudPtr[current_student_index]->telephone,
                           reg.arrStudPtr[current_student_index]->address
                    );
                }
                break;
            case 3: //deleting student
                printf("Enter roll number of student to delete : ");
                scanf("%d", &roll_input);
                operation_result_flag = delete(&reg, roll_input);
                if (operation_result_flag == 1) {
                    printf("Student deleted successfully");
                } else {
                    printf("Student with given roll number not found/deletion failed");
                }
                break;
            case 4: //modifying student record
                printf("Enter roll number of student to modify : ");
                scanf("%d", &roll_input); 
                while(getchar() != '\n');
                current_student_index = get(&reg, roll_input);
                if (current_student_index == -1) {
                    printf("Student does not exist inside register");
                    continue;
                }
                
                Student temp_mod_student;
                temp_mod_student.roll = roll_input;

                char name_buffer[256];
                printf("Enter new name [Last name, First name] : ");
                fgets(name_buffer, sizeof(name_buffer), stdin);
                name_buffer[strcspn(name_buffer, "\n")] = '\0';
                temp_mod_student.name = name_buffer;

                printf("Enter new telephone number : ");
                fgets(temp_mod_student.telephone, sizeof(temp_mod_student.telephone), stdin);
                temp_mod_student.telephone[strcspn(temp_mod_student.telephone, "\n")] = '\0';

                char address_buffer[256];
                printf("Enter new address : ");
                fgets(address_buffer, sizeof(address_buffer), stdin);
                address_buffer[strcspn(address_buffer, "\n")] = '\0';
                temp_mod_student.address = address_buffer;

                operation_result_flag = modify(&reg, &temp_mod_student);
                if (operation_result_flag == 1) {
                    printf("Student with given roll no. successfully modified");
                } else {
                    printf("Student could not be modified!");
                }
                break;
            case 5: //sorting students alphabetically
                sortStudents(&reg);
                printf("Students sorted in alphabetical order!\n");
                printf("Current student list after sorting : \n");
                if (reg.count == 0) {
                    printf("Register is empty\n");
                } else {
                    for (int i = 0; i < reg.count; i++) {
                        printf("%d. Name : %s\n   Roll : %d\n", i + 1,
                               reg.arrStudPtr[i]->name, reg.arrStudPtr[i]->roll);
                    }
                }
                break;
            case 6: //saving to register
                printf("Enter a filename to save the register : ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                if (exportRegister(&reg, filename) == 1) {
                    printf("Register successfully saved to %s. \n", filename);
                } else {
                    printf("Failed to save register!");
                }
                break;
            case 7: //loading from register
                printf("Enter filename to load register from : ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                operation_result_flag = loadRegister(&reg, filename);
                if (operation_result_flag == 1) {
                    printf("Successfully loaded the register!");
                } else {
                    printf("Failed to load register!");
                }
                break;
            default:
                printf("Wrong choice!/Exited Program\n");
                break;
        }
    }
    while(choice != 0);

    for (int i = 0; i < reg.count; i++) {
        freeStudentRecord(reg.arrStudPtr[i]);
    }
    FREE(reg.arrStudPtr);
	printf("%p\n", reg.arrStudPtr);
    return 0;
}
