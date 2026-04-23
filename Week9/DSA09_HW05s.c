#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLOORS 17
#define ROOMS 12

typedef struct Node {
    char name;
    int floor;
    int room;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

int hotelStatus[FLOORS][ROOMS];
Node *leader[ROOMS];

void initHotel() {
    for (int i = 0; i < FLOORS; i++) {
        for (int j = 0; j < ROOMS; j++) {
            hotelStatus[i][j] = 0;
        }
    }
    for (int j = 0; j < ROOMS; j++) {
        leader[j] = NULL;
    }
}

int countEmptyRoom() {
    int count = 0;
    for (int i = 0; i < FLOORS; i++) {
        for (int j = 0; j < ROOMS; j++) {
            if (hotelStatus[i][j] == 0) count++;
        }
    }
    return count;
}

void printHotelStatus() {
    system("cls");
    printf("--- HOTEL STATUS ---\n");
    for (int i = FLOORS - 1; i >= 0; i--) {
        printf("Floor %2d: ", i);
        for (int j = 0; j < ROOMS; j++) {
            printf("%d ", hotelStatus[i][j]);
        }
        printf("\n");
    }
    printf("Total %d / %d empty room(s).\n", countEmptyRoom(), FLOORS*ROOMS);
    system("pause");
}

void initList(LinkedList *list) {
    list->head = NULL;
}

Node *makeNode(char name, int floor, int room) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->name = name;
    newNode->floor = floor;
    newNode->room = room;
    newNode->next = NULL;
    return newNode;
}

// ===== PROBLEM 1: CHECK IN FOR GROUP
int findEmptyRoomOnFloor(int floor) {
    for (int j = 0; j < ROOMS; j++) {
        if (hotelStatus[floor][j] == 0) {
            return j;
        }
    }
    return -1;
}

void findEmptyRoom(int *floor, int *room) {
    for (int i = 1; i < FLOORS; i++) {
        for (int j = 0; j < ROOMS; j++) {
            if (hotelStatus[i][j] == 0) {
                *floor = i;
                *room = j;
                return;
            }
        }
    }
    *floor = -1;
    *room = -1;
}

void insertTailList(LinkedList *list, char name, int floor, int room) {
    Node *newNode = makeNode(name, floor, room);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node *temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void checkInGroup(int groupSize, char *groupName) {
    system("cls");
    printf("--- CHECK IN FOR GROUP ---\n");
    printf("Group has %d people:\n", groupSize);
    LinkedList group;
    initList(&group);
    int floor, room;
    for (int m = 0; m < groupSize; m++) {
        if (m == 0) {
            room = findEmptyRoomOnFloor(0);
            if (room == -1) {
                printf("Error: Floor 0 is full.\n");
                system("pause");
                return;
            }
            floor = 0;
        } else {
            findEmptyRoom(&floor, &room);
            if (floor == -1) {
                printf("Error: Hotel is full.\n");
                system("pause");
                return;
            }
        }
        insertTailList(&group, groupName[m], floor, room);
        hotelStatus[floor][room] = 1;
        printf(" %c : R%2d.%2d\n", groupName[m], floor, room);
    }
    leader[group.head->room] = group.head;
    printf("Check in successful.\n");
    system("pause");
}

// ===== PROBLEM 2: GET INFORMATION GROUP FROM LEADER
void getGroupInfo(int leaderRoom) {
    system("cls");
    Node *head = leader[leaderRoom];
    if (head == NULL) {
        printf("R%2d.%2d has no group leader.\n", 0, leaderRoom);
        system("pause");
        return;
    }
    printf("--- GROUP INFORMATION ---\n");
    printf("Leader: R%2d.%2d\n", 0, leaderRoom);
    printf("Group member:\n");
    Node *curr = head;
    int count = 1;
    while (curr != NULL) {
        printf("%d. %c : R%2d.%2d", count++, curr->name, curr->floor, curr->room);
        if (curr->next != NULL) {
            printf(" --> %c : R%2d.%2d", curr->next->name, curr->next->floor, curr->next->room);
        }
        printf("\n");
        curr = curr->next;
    }
    system("pause");
}

// ===== PROBLEM 3: ADD NEW GUEST TO THE GROUP
void addGuestToGroup(int leaderRoom, char guestName) {
    system("cls");
    printf("--- ADD NEW GUEST TO THE GROUP ---\n");
    Node *head = leader[leaderRoom];
    if (head == NULL) {
        printf("Error: No group leader at R0.%d\n", leaderRoom);
        system("pause");
        return;
    }
    
    Node *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    
    int floor, room;
    findEmptyRoom(&floor, &room);
    if (floor == -1) {
        printf("Error: Hotel is full.\n");
        system("pause");
        return;
    }
    Node *newGuest = makeNode(guestName, floor, room);
    last->next = newGuest;
    hotelStatus[floor][room] = 1;
    printf(" %c : R%2d.%2d\n", guestName, floor, room);
    printf("Add successful.\n");
    system("pause");
}

// ===== PROBLEM 4: REMOVE GUEST FROM GROUP
int deleteValueList(LinkedList *list, int floor, int room) {
    Node *curr = list->head, *prev = NULL;
    while (curr != NULL && (curr->floor != floor || curr->room != room)) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return 0;
    if (prev == NULL) {
        list->head = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);
    return 1;
}

void removeGuestFromGroup(int leaderRoom, int guestFloor, int guestRoom) {
    system("cls");
    printf("--- REMOVE GUEST FROM GROUP ---\n");
    Node *head = leader[leaderRoom];
    if (head == NULL) {
        printf("Error: No group leader at R0.%d\n", leaderRoom);
        system("pause");
        return;
    }
    
    printf("Check out guest in R%2d.%2d (Leader in R%2d.%2d).\n", guestFloor, guestRoom, 0, leaderRoom);
    LinkedList group;
    group.head = head;
    int isLeader = group.head != NULL && group.head->floor == guestFloor && group.head->room == guestRoom;
    int deleted = deleteValueList(&group, guestFloor, guestRoom);
    
    if(deleted) {
        if (isLeader) {
            if (group.head != NULL) {
                Node *newHead = group.head;
                printf("New leader: (R%2d.%2d -> R%2d.%2d)\n", newHead->floor, newHead->room, 0, leaderRoom);
                hotelStatus[newHead->floor][newHead->room] = 0;
                newHead->floor = 0;
                newHead->room  = leaderRoom;
                hotelStatus[0][leaderRoom] = 1;
            } else {
                printf("Group is empty\n");
                hotelStatus[0][leaderRoom] = 0;
            }
        } else {
            hotelStatus[guestFloor][guestRoom] = 0;
            printf("Remove successful.\n");
        }
    } else {
        printf("Not found this guest.\n");
    }
    leader[leaderRoom] = group.head;
    system("pause");
}

// ===== PROBLEM 5: CHECK OUT FOR GROUP
void checkoutGroup(int leaderRoom) {
    system("cls");
    printf("--- CHECK OUT FOR GROUP ---\n");
    Node *head = leader[leaderRoom];
    if (head == NULL) {
        printf("Error: No group leader at R0.%d\n", leaderRoom);
        system("pause");
        return;
    }
    
    printf("Check out for group at R%2d.%2d.\n", 0, leaderRoom);
    printf("Free rooms: ");
    Node *curr = head;
    while (curr != NULL) {
        printf("R%2d.%2d ", curr->floor, curr->room);
        hotelStatus[curr->floor][curr->room] = 0;
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    leader[leaderRoom] = NULL;
    printf("\nCheck out successful.\n");
    system("pause");
}

// ===== DISPLAY LEADERS
void displayLeaders() {
    printf("\n--- LIST OF GROUP LEADERS ---\n");
    int count = 0;
    for (int j = 0; j < ROOMS; j++) {
        if (leader[j] != NULL) {
            count++;
            printf("%d. R0.%d - %c\n", count, j, leader[j]->name);
        }
    }
    if (count == 0) {
        printf("No groups found!\n");
    } else {
        printf("\nTotal: %d group(s).\n", count);
    }
}

// === MENU 1: CHECK IN (PROBLEM 1 + PROBLEM 3)
void menuCheckIn() {
    int choice;
    do {
        system("cls");
        printf("==-- CHECK IN --==\n");
        printf("1. Check in group.\n");
        printf("2. Add a guest to a group.\n");
        printf("0. Back.\n");
        printf("Select a function: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            int groupSize;
            do {
                printf("Enter the number of members in the group: ");
                scanf("%d", &groupSize);
                if (groupSize <= 0) printf("Error: invalid number.\n");
            } while (groupSize <= 0);
            
            char *groupName = (char *) malloc((groupSize + 1) * sizeof(char));
            printf("Enter names of members (e.g., ABCD): ");
            scanf("%s", groupName);
            
            checkInGroup(groupSize, groupName);
            free(groupName);
            
        } else if (choice == 2) {
            int room;
            char newName;
            do {
                printf("Enter address of group leader (floor 0 - room ?): ");
                scanf("%d", &room);
                if (room < 0 || room >= ROOMS) printf("Error: invalid room.\n");
            } while (room < 0 || room >= ROOMS);
            
            printf("Enter guest name (1 character): ");
            scanf(" %c", &newName);
            
            addGuestToGroup(room, newName);
            
        } else if (choice == 0) {
            // Back
        } else {
            printf("Error: invalid choice.\n");
            system("pause");
        }
    } while (choice != 0);
}

// === MENU 2: CHECK OUT (PROBLEM 4 + PROBLEM 5)
void menuCheckOut() {
    int choice;
    do {
        system("cls");
        printf("==-- CHECK OUT --==\n");
        printf("1. Check out for a guest in the group.\n");
        printf("2. Check out for individual guest.\n");
        printf("3. Check out for a group.\n");
        printf("0. Back.\n");
        printf("Select a function: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            int leaderRoom, guestFloor, guestRoom;
            do {
                printf("Enter address of group leader (floor 0 - room ?): ");
                scanf("%d", &leaderRoom);
                if (leaderRoom < 0 || leaderRoom >= ROOMS) printf("Error: invalid room.\n");
            } while (leaderRoom < 0 || leaderRoom >= ROOMS);
            
            do {
                printf("Enter address of guest (floor ? - room ?): ");
                scanf("%d%d", &guestFloor, &guestRoom);
                if (guestFloor < 0 || guestFloor >= FLOORS || guestRoom < 0 || guestRoom >= ROOMS) 
                    printf("Error: invalid address.\n");
            } while (guestFloor < 0 || guestFloor >= FLOORS || guestRoom < 0 || guestRoom >= ROOMS);
            
            removeGuestFromGroup(leaderRoom, guestFloor, guestRoom);
            
        } else if (choice == 2) {
            int guestFloor, guestRoom;
            do {
                printf("Enter address of individual guest (floor ? - room ?): ");
                scanf("%d%d", &guestFloor, &guestRoom);
                if (guestFloor < 0 || guestFloor >= FLOORS || guestRoom < 0 || guestRoom >= ROOMS) 
                    printf("Error: invalid address.\n");
            } while (guestFloor < 0 || guestFloor >= FLOORS || guestRoom < 0 || guestRoom >= ROOMS);
            
            if (hotelStatus[guestFloor][guestRoom] == 0) {
                printf("Not found guest.\n");
                system("pause");
            } else {
                if (guestFloor == 0 && leader[guestRoom] != NULL) {
                    printf("Error: This is leader's room.\n");
                    system("pause");
                } else {
                    hotelStatus[guestFloor][guestRoom] = 0;
                    printf("Check out successful.\n");
                    system("pause");
                }
            }
            
        } else if (choice == 3) {
            int leaderRoom;
            do {
                printf("Enter address of group leader (floor 0 - room ?): ");
                scanf("%d", &leaderRoom);
                if (leaderRoom < 0 || leaderRoom >= ROOMS) printf("Error: invalid room.\n");
            } while (leaderRoom < 0 || leaderRoom >= ROOMS);
            
            checkoutGroup(leaderRoom);
            
        } else if (choice == 0) {
            // Back
        } else {
            printf("Error: invalid choice.\n");
            system("pause");
        }
    } while (choice != 0);
}

// === MENU 3: DISPLAY GROUP INFORMATION (PROBLEM 2)
void menuDisplayGroup() {
    system("cls");
    displayLeaders();
    
    int totalLeaders = 0;
    for (int j = 0; j < ROOMS; j++) {
        if (leader[j] != NULL) totalLeaders++;
    }
    
    if (totalLeaders == 0) {
        system("pause");
        return;
    }
    
    int room;
    do {
        printf("\nEnter leader room to view details (floor 0 - room ?): ");
        scanf("%d", &room);
        if (room < 0 || room >= ROOMS) printf("Error: invalid room.\n");
    } while (room < 0 || room >= ROOMS);
    
    getGroupInfo(room);
}

int main() {
    initHotel();
    hotelStatus[0][10] = hotelStatus[0][11] = 1;
    hotelStatus[1][0] = hotelStatus[1][2] = hotelStatus[1][6] = hotelStatus[1][8] = hotelStatus[1][10] = 1;
    hotelStatus[2][0] = hotelStatus[2][3] = hotelStatus[2][5] = hotelStatus[2][7] = hotelStatus[2][8] = hotelStatus[2][11] = 1;
    hotelStatus[3][2] = hotelStatus[3][4] = hotelStatus[3][6] = hotelStatus[3][10] = 1;
    hotelStatus[4][0] = hotelStatus[4][3] = hotelStatus[4][8] = hotelStatus[4][9] = hotelStatus[4][11] = 1;
    hotelStatus[5][1] = hotelStatus[5][4] = hotelStatus[5][6] = hotelStatus[5][7] = hotelStatus[5][10] = hotelStatus[5][11] = 1;
    hotelStatus[6][0] = hotelStatus[6][2] = hotelStatus[6][5] = hotelStatus[6][11] = 1;
    hotelStatus[7][2] = hotelStatus[7][3] = hotelStatus[7][4] = hotelStatus[7][7] = hotelStatus[7][10] = 1;
    hotelStatus[8][1] = hotelStatus[8][6] = hotelStatus[8][8] = hotelStatus[8][9] = hotelStatus[8][11] = 1;
    hotelStatus[9][2] = hotelStatus[9][5] = hotelStatus[9][7] = hotelStatus[9][10] = hotelStatus[9][11] = 1;
    hotelStatus[10][0] = hotelStatus[10][3] = hotelStatus[10][6] = hotelStatus[10][8] = hotelStatus[10][9] = 1;
    hotelStatus[11][0] = hotelStatus[11][1] = hotelStatus[11][2] = hotelStatus[11][4] = hotelStatus[11][6] = hotelStatus[11][7] = hotelStatus[11][10] = hotelStatus[11][11] = 1;
    hotelStatus[12][2] = hotelStatus[12][3] = hotelStatus[12][5] = hotelStatus[12][9] = 1;
    hotelStatus[13][0] = hotelStatus[13][2] = hotelStatus[13][6] = hotelStatus[13][8] = hotelStatus[13][10] = hotelStatus[13][11] = 1;
    hotelStatus[14][1] = hotelStatus[14][4] = hotelStatus[14][5] = hotelStatus[14][7] = hotelStatus[14][10] = 1;
    hotelStatus[15][2] = hotelStatus[15][3] = hotelStatus[15][6] = hotelStatus[15][9] = hotelStatus[15][10] = hotelStatus[15][11] = 1;
    hotelStatus[16][3] = hotelStatus[16][7] = hotelStatus[16][10] = 1;
    char group[10][16] = {"ABSEFJKLSWQA", "TMKLJSAQCS", "HJSSASMQD", "SAQDASSAQDSQA", "QSAQEDFSSASXVBF", "HAVANTHAOTTHUS", "PHLAMDSATTHU", "PPNHUNGSVELEVEN", "LPTRUONGDS", "CHGIAOKDLH"};
    checkInGroup(12, group[0]);
    checkInGroup(10, group[1]);
    checkInGroup(9, group[2]);
    checkInGroup(13, group[3]);
    checkInGroup(15, group[4]);
    checkInGroup(14, group[5]);
    checkInGroup(12, group[6]);
    checkInGroup(15, group[7]);
    checkInGroup(10, group[8]);
    checkInGroup(10, group[9]);
    int choice;
    do {
        system("cls");
        printf("===== HOTEL MANAGEMENT =====\n");
        printf("1. Check in.\n");
        printf("2. Check out.\n");
        printf("3. Display hotel status.\n");
        printf("4. Display group information.\n");
        printf("0. Exit.\n");
        printf("----------------------------\n");
        printf("Select a function: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                menuCheckIn();
                break;
            case 2:
                menuCheckOut();
                break;
            case 3:
                printHotelStatus();
                break;
            case 4:
                menuDisplayGroup();
                break;
            case 0:
                printf("SEE YOU AGAIN!\n");
                system("pause");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 0);
    
    // Giải phóng bộ nhớ
    for (int j = 0; j < ROOMS; j++) {
        if (leader[j] != NULL) {
            Node *current = leader[j];
            while (current != NULL) {
                Node *temp = current;
                current = current->next;
                free(temp);
            }
        }
    }
    
    return 0;
}

/* OUTPUT 1: CHECK IN GROUP 1
--- CHECK IN FOR GROUP ---
Group has 12 people:
 A : R 0. 0
 B : R 1. 1
 S : R 1. 3
 E : R 1. 4
 F : R 1. 5
 J : R 1. 7
 K : R 1. 9
 L : R 1.11
 S : R 2. 1
 W : R 2. 2
 Q : R 2. 4
 A : R 2. 6
Check in successful.
Press any key to continue . . .
*/

/* OUTPUT 2: CHECK IN GROUP 2:
--- CHECK IN FOR GROUP ---
Group has 10 people:
 T : R 0. 1
 M : R 2. 9
 K : R 2.10
 L : R 3. 0
 J : R 3. 1
 S : R 3. 3
 A : R 3. 5
 Q : R 3. 7
 C : R 3. 8
 S : R 3. 9
Check in successful.
Press any key to continue . . . 
*/

/*
Tương tự: ...
*/

/* OUTPUT 11: MENU CHÍNH
===== HOTEL MANAGEMENT =====
1. Check in.
2. Check out.
3. Display hotel status.
4. Display group information.
0. Exit.
----------------------------
Select a function: 
*/

/* OUTPUT 12: FUNCTION 3
--- HOTEL STATUS ---
Floor 16: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor 15: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor 14: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor 13: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor 12: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor 11: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor 10: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  9: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  8: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  7: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  6: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  5: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  4: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  3: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  2: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  1: 1 1 1 1 1 1 1 1 1 1 1 1 
Floor  0: 1 1 1 1 1 1 1 1 1 1 1 1 
Total 0 / 204 empty room(s).
Press any key to continue . . . 
*/

/* OUTPUT 13: FUNCTION 4
--- LIST OF GROUP LEADERS ---
1. R0.0 - A
2. R0.1 - T
3. R0.2 - H
4. R0.3 - S
5. R0.4 - Q
6. R0.5 - H
7. R0.6 - P
8. R0.7 - P
9. R0.8 - L
10. R0.9 - C

Total: 10 group(s).

Enter leader room to view details (floor 0 - room ?): 
*/

/* OUTPUT 14: FUNCTION 4
--- GROUP INFORMATION ---
Leader: R 0. 1
Group member:
1. T : R 0. 1 --> M : R 2. 9
2. M : R 2. 9 --> K : R 2.10
3. K : R 2.10 --> L : R 3. 0
4. L : R 3. 0 --> J : R 3. 1
5. J : R 3. 1 --> S : R 3. 3
6. S : R 3. 3 --> A : R 3. 5
7. A : R 3. 5 --> Q : R 3. 7
8. Q : R 3. 7 --> C : R 3. 8
9. C : R 3. 8 --> S : R 3. 9
10. S : R 3. 9
Press any key to continue . . . 
*/

/* OUTPUT 15: FUNCTION 2.2
==-- CHECK OUT --==
1. Check out for a guest in the group.
2. Check out for individual guest.
3. Check out for a group.
0. Back.
Select a function: 2
Enter address of individual guest (floor ? - room ?): 0 11
Check out successful.
Press any key to continue . . . 
*/

/* OUTPUT 16: FUNCTION 2.3
--- CHECK OUT FOR GROUP ---
Check out for group at R 0. 2.
Free rooms: R 0. 2 R 3.11 R 4. 1 R 4. 2 R 4. 4 R 4. 5 R 4. 6 R 4. 7 R 4.10 
Check out successful.
Press any key to continue . . . 
*/

/* OUTPUT 17: FUNCTION 2.1
--- REMOVE GUEST FROM GROUP ---
Check out guest in R 1. 1 (Leader in R 0. 0).
Remove successful.
Press any key to continue . . . 
*/

/* OUTPUT 18: FUNCTION 1.2
--- ADD NEW GUEST TO THE GROUP ---
 X : R 1. 1
Add successful.
Press any key to continue . . . 
*/

/* OUTPUT 19: FUNCTION 0
===== HOTEL MANAGEMENT =====
1. Check in.
2. Check out.
3. Display hotel status.
4. Display group information.
0. Exit.
----------------------------
Select a function: 0
SEE YOU AGAIN!
Press any key to continue . . . 
*/