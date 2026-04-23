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
    printf("\n--- HOTEL STATUS ---\n");
    for (int i = FLOORS - 1; i >= 0; i--) {
        printf("Floor %2d: ", i);
        for (int j = 0; j < ROOMS; j++) {
            printf("%d ", hotelStatus[i][j]);
        }
        printf("\n");
    }
    printf("Total %d / %d empty room(s).\n", countEmptyRoom(), FLOORS*ROOMS);
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

// ===== PROBLEM 1: PUSH N GROUPS INTO HOTEL
int findEmptyRoomOnFloor(int floor) {
    for (int j = 0; j < ROOMS; j++) {
        if (hotelStatus[floor][j] == 0) {
            return j;
        }
    }
    return -1;
}
void findEmptyRoom(int *floor, int *room) {
    for (int i = 0; i < FLOORS; i++) {
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
void checkInGroups(int groupSizes, char *groupNames) {
    system("cls");
    printf("--- CHECK IN FOR GROUPS ---\n");
    printf("Group has %d people:\n", groupSizes);
    LinkedList group;
    initList(&group);
    int floor, room;
    for (int m = 0; m < groupSizes; m++) {
        if (m == 0) {
            room = findEmptyRoomOnFloor(0);
            if (room == -1) {
                printf("Error: Floor 0 is full.\n");
                return;
            }
            floor = 0;
        } else {
            findEmptyRoom(&floor, &room);
            if (floor == -1) {
                printf("Error: Hotel is full.\n");
                return;
            }
        }
        insertTailList(&group, groupNames[m], floor, room);
        hotelStatus[floor][room] = 1;
        printf(" %c : R%2d.%2d\n", groupNames[m], floor, room);
    }
    leader[group.head->room] = group.head;
    printf("Check in successful.\n");
    system("pause");
}

// ===== PROBLEM 2: GET INFORMATION GROUPS FROM LEADER
void getGroupInfro(int leaderRoom) {
    system("cls");
    Node *head = leader[leaderRoom];
    if (head == NULL) {
        printf("R%2d.%2d has no group leader.\n", 0, leaderRoom);
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
            printf(" --> %c : R%2d.%2d\n", curr->next->name, curr->next->floor, curr->next->room);
        }
        printf("\n");
        curr = curr->next;
    }
    system("pause");
}

// ===== PROBLEM 3: ADD NEW GUESTS TO THE GROUP
void addGuestToGroup(int leaderRoom, char guestNames) {
    system("cls");
    printf("--- ADD NEW GUESTS TO THE GROUP ---\n");
    Node *head = leader[leaderRoom];
    Node *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    int floor, room;
    findEmptyRoom(&floor, &room);
    if (floor == -1) {
        printf("Error: Hotel is full.\n");
        return;
    }
    Node *newGuest = makeNode(guestNames, floor, room);
    last->next = newGuest;
    last = newGuest;
    hotelStatus[floor][room] = 1;
    printf("Add successful.\n");
    system("pause");
}

// ===== PROBLEM 4: REMOVE GUESTS FROM GROUP
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
    printf("Check out for group at R%2d.%2d.\n", 0, leaderRoom);
    printf("Free rooms:\n");
    Node *curr = head;
    while (curr != NULL) {
        printf("R%2d.%2d ", curr->floor, curr->room);
        hotelStatus[curr->floor][curr->room] = 0;
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    leader[leaderRoom] = NULL;
    printf("Check out successful.\n");
    system("pause");
}

// === MENU 1: CHECK IN (PROBLEM 1 + PROBLEM 3)
void menuCheckIn() {
    int choice;
    do {
        system("cls");
        printf("==-- CHECK IN --==\n");
        printf("1. Check in group(s).\n");
        printf("2. Add a guest to a group.\n");
        printf("0. Back.\n");
        printf("Select a function: ");
        scanf("%d", &choice);
        if (choice == 1) {
            int groupSize;
            do {
                printf("Enter the number of members in the group: ");
                scanf("%d", &groupSize);
                if (groupSize < 0) printf("Error: invalid number.\n");
            } while (groupSize < 0);
            char *groupName = (char *) malloc((groupSize + 1) * sizeof(char));
            checkInGroups(groupSize, groupName);
            free(groupName);
        } else if (choice == 2) {
            int room;
            char newName;
            do {
                printf("Enter address of group leader (floor 0 - room ?): ");
                scanf("%d", &room);
                if (room < 0 || room >= ROOMS) printf("Error: invalid room.\n");
            } while (room < 0 || room >= ROOMS);
            printf("Enter guest name: ");
            scanf("%c", &newName);
            char name[] = {newName, '\0'};
            addGuestToGroup(room, name);
        } else if (choice == 0) system("pause");
        else printf("Error: invalid choice.\n");
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
        int leaderRoom, guestFloor, guestRoom;
        if (choice == 1) {
            do {
                printf("Enter address of group leader (floor 0 - room ?): ");
                scanf("%d", &leaderRoom);
                if (leaderRoom < 0 || leaderRoom >= ROOMS) printf("Error: invalid room.\n");
            } while (leaderRoom < 0 || leaderRoom >= ROOMS);
            do {
                printf("Enter address of guest (floor ? - room ?): ");
                scanf("%d%d", &guestFloor, &guestRoom);
                if (guestFloor < 0 || guestFloor >= FLOORS|| guestRoom < 0 || guestFloor >= ROOMS) printf("Error: invalid room.\n");
            } while (guestFloor < 0 || guestFloor >= FLOORS|| guestRoom < 0 || guestFloor >= ROOMS);
            removeGuestFromGroup(leaderRoom, guestFloor, guestRoom);
        } else if (choice == 2) {
            int floor, room;
            do {
                printf("Enter address of individual guest: ");
                scanf("%d%d", &guestFloor, &guestRoom);
                if (guestFloor < 0 || guestFloor >= FLOORS|| guestRoom < 0 || guestFloor >= ROOMS) printf("Error: invalid room.\n");
            } while (guestFloor < 0 || guestFloor >= FLOORS|| guestRoom < 0 || guestFloor >= ROOMS);
            if (hotelStatus[guestFloor][guestRoom] == 0) printf("Not found guest.\n");
            else {
                if (floor == 0 && leader[guestRoom] != NULL) printf("Error: This is leader's room.\n");
                else {
                    hotelStatus[guestFloor][guestRoom] = 0;
                    printf("Check out successful.\n");
                }
            }
        } else if (choice == 3) {
            do {
                printf("Enter address of group leader (floor 0 - room ?): ");
                scanf("%d", &leaderRoom);
                if (leaderRoom < 0 || leaderRoom >= ROOMS) printf("Error: invalid room.\n");
            } while (leaderRoom < 0 || leaderRoom >= ROOMS);
            checkoutGroup(leaderRoom);
        } else if (choice == 0) system("pause");
        else printf("Error: invalid choice.\n");
    } while (choice != 0);
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
    char *group[10] = {"ABSEFJKLSWQA", "TMKLJSAQCS", "HJSSASMQD", "SAQDASSAQDSQA", "QSAQEDFSSASXVBF", "HAVANTHAOTTHUS", "PHLAMDSATTHU", "PPNHUNGSVELEVEN", "LPTRUONGDS", "CHGIAOKDLH"};
    int choice;
    do {
        system("cls");
        printf("===== RESTAURANT MANAGEMENT =====\n");
        printf("1. Check in.\n");
        printf("2. Check out.\n");
        printf("3. Display hotel status.\n");
        printf("4. Display group information.\n");
        printf("0. Exit.\n--------------------\n");
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
                menuDisplayHotelStatus();
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
    printHotelStatus();
    return 0;
}