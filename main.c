#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include<windows.h>
//#include<unistd.h>
typedef struct {
    char* Name;
    int hp ;
    char* Key;
    int current_room;
    char* Sword;
    char* Helmet;
    bool wheel_spinning;
} MainCharacter;
void MainCharacterSet(MainCharacter* main_character, char* name, int hp, char* key) {
    main_character->Name = malloc(sizeof(char) * 20);
    main_character->Key =  malloc(sizeof(char) * 20);
    main_character->Sword = malloc(sizeof (char )*20);
    main_character->Helmet = malloc(sizeof (char )*20);
    main_character->wheel_spinning = false;
    strcpy(main_character->Name, name);
    main_character->hp = hp;
    strcpy(main_character->Key,key ? key : "");
    main_character->current_room = 0;

}
void saveGame(MainCharacter *main_character) {
    char filename[30];
    snprintf(filename, sizeof(filename), "%s.sav", main_character->Name);
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Unable to save the game.\n");
        return;
    }
    fwrite(main_character, sizeof(MainCharacter), 1, file);
    fclose(file);
    printf("Game saved successfully!\n");
}
bool loadGame(const char *player_name, MainCharacter *main_character) {
    char filename[30];
    snprintf(filename, sizeof(filename), "%s.sav", player_name);
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return false;
    }
    fread(main_character, sizeof(MainCharacter), 1, file);
    fclose(file);
    return true;
}
void fightMonster(MainCharacter* main_character){
    int goblin_hp = 50;
    int goblin_attack = 7;
    int player_attack = 7;
    if(strcmp(main_character->Sword, "Diamond Sword") == 0){
        player_attack = 11;
    }
    while (1){
        if (goblin_hp<=0){
            printf("Congratulations, you won.\n");
            return;
        } else{
            printf("A goblin stands in front of you with a gun and attacks you and of course you start to defend yourself.\n");
            printf("You hit the goblin\n");
            goblin_hp -= player_attack;
            printf("The hp of a goblin %d\n",goblin_hp);
            printf("The goblin hits you.");
            main_character->hp -= goblin_attack;
            printf("The hp of you %d\n",main_character->hp);
            if (main_character->hp <= 0) {
                printf("You have been defeated by the goblin. Game Over.\n");
                exit(0);
            }
            sleep(0.5);

        }

    }
}
void launchRoom(MainCharacter* main_character){
    while (1){
        switch (main_character->current_room) {
            case 0:
                printf("Oh god no, you were walking in the woods and saw an object you didn't recognize,\n"
                       "you got curious and decided to pick it up and it teleported you to a dungeon.\n"
                       "A mysterious voice whispers to you that you need to find two keys to get out of the dungeon.\n"
                       "There are 5 mysterious rooms that you must enter to find the key, but beware of the dangers that the rooms hold.\n"
                       "Enter the numbers from 1 to 3 to move to one of the rooms or select 0 or 9 to go back or quit the game.\n");
                int a_0;
                scanf("%d",&a_0);
                switch (a_0) {
                    case 0:
                        main_character->current_room = 0;
                        break;
                    case 1:
                        main_character->current_room = 1;
                        break;
                    case 2:
                        main_character->current_room = 2;
                        break;
                    case 3:
                        main_character->current_room = 3;
                        break;
                    case 9:
                        exit(0);
                    default:
                        printf("Invalid room. Try again.\n");
                        continue;
                }
                break;

            case 1:
                printf("You have chosen one of the rooms and found a sword in it, but this is not the end,\n"
                       "because ahead of you have 2 more rooms and you need to choose to go back or forward to one of the 2 rooms\n"
                       "Select 1 or 2 to go further into the rooms or select 0 or 9 to go back or exit the game\n");
                if(strcmp(main_character->Sword, "Diamond Sword") == 0){} else {
                    strcpy(main_character->Sword, "Diamond Sword");
                }
                int a_1;
                scanf("%d",&a_1);
                switch (a_1) {
                    case 0:
                        main_character->current_room = 0;
                        break;
                    case 1:
                        main_character->current_room = 4;
                        break;
                    case 2:
                        main_character->current_room = 5;
                        break;
                    case 9:
                        exit(0);
                    default:
                        printf("Invalid room. Try again.\n");
                        continue;
                }
                break;
            case 2:
                printf("You've chosen room number 2\n"
                       "You saw the wheel of luck start to spin.\n"
                       "You don't realize what's happening but a quiet \n "
                       "and mysterious voice whispers to you the terms of the wheel \n"
                       "“In this wheel you can fight a goblin, stay unharmed and do nothing or get a secret buff”.\n");
                sleep(0.5);
                if(main_character->wheel_spinning){
                    printf("You've already spun the wheel. To spin the wheel again, exit the room and re-enter.\n");
                } else{
                    int rand_value_1 = rand() % 4;
                    switch (rand_value_1) {
                        case 0:
                            printf("Congratulations on the wheel you're on. Nothing's gonna happen to you.\n");
                            break;
                        case 1:
                            printf("Congratulations on the wheel you're on. Nothing's gonna happen to you.\n");
                            break;
                        case 3:
                            fightMonster(main_character);
                            printf("Congratulations, you killed the goblin that gave you the loot.\n");
                            int rand_value_4 = rand() % 2;
                            if(rand_value_4 == 0){
                                main_character->hp += 20;
                                printf("you've been given extra hp\n");
                            } else {
                                printf("you got the loot");
                                if(strcmp(main_character->Key, "Key") == 0){
                                    printf("You've already taken the Key, you can't take it a second time.\n");
                                } else {
                                    printf("you've been given the key you need to get out of the dungeon.\n");
                                    strcpy(main_character->Key, "Key");
                                }
                            }
                            break;
                        case 4:
                            printf("Secret Buff");
                            break;
                    }

                }
                sleep(1);
                printf("Next you see 2 rooms you can enter them by pressing 1 or 2,\n"
                       " or you can go back by pressing 0 or exit the game by pressing 9.\n");
                int a_2;
                scanf("%d",&a_2);
                switch (a_2) {
                    case 0:
                        main_character ->wheel_spinning = false;
                        main_character->current_room = 0;
                        break;
                    case 1:
                        main_character ->wheel_spinning = false;
                        main_character->current_room = 6;
                        break;
                    case 2:
                        main_character ->wheel_spinning = false;
                        main_character->current_room = 7;
                        break;
                    case 9:
                        main_character ->wheel_spinning = false;
                        exit(0);
                    default:
                        printf("Invalid room. Try again.\n");
                        main_character ->wheel_spinning = true;
                        break;
                }
                break;
        case 3:
            printf("You get into the room and you smell a pungent odor. \n"
                   "and you see a skeleton on the wall and a helmet next to it. \n"
                   "You put it on, of course, because you're scared and you need protection.\n");
            if(strcmp(main_character->Helmet, "Helmet") == 0){
                printf("You've already taken the helmet, you can't take it a second time.\n");
            } else {
                printf("You took the helmet and gained extra hp\n");
                main_character->hp += 50;
            }
            sleep(0.5);
            printf("Then you see 3 rooms and think about where to go,\n"
                   " press 1 to 3 to enter the rooms or 0 to return or 9 to exit the game.\n");
                int a_3;
                scanf("%d",&a_3);
                switch (a_3) {
                    case 0:
                        main_character->current_room = 0;
                        break;
                    case 1:
                        main_character->current_room = 9;
                        break;
                    case 2:
                        main_character->current_room = 10;
                        break;
                    case 3:
                        main_character->current_room = 11;
                        break;
                    case 9:
                        exit(0);
                    default:
                        printf("Invalid room. Try again.\n");
                        continue;
                }
            break;
        case 4:
            printf("You entered the room and realized that it was empty you will have to go back,\n"
                   " to go back write 0 or 9 if you want to leave\n");
            int a_4;
            scanf("%d",&a_4);
            switch (a_4) {
                case 0:
                    main_character->current_room = 1;
                    break;
                case 9:
                    exit(0);
                default:
                    printf("Invalid room. Try again.\n");
                    continue;
            }
            break;
        case 5:
            printf("You walk into a room and see a key on the floor and you think \n"
                   "you need it to get out of the dungeon and you'd be right.\n"
                   "To go back, write 0 and to quit, write 9.\n");
            if(strcmp(main_character->Key, "Key") == 0){
                printf("You've already taken the Key, you can't take it a second time.\n");
            } else {
                strcpy(main_character->Key, "Key");
            }

            int a_5;
            scanf("%d",&a_5);
            switch (a_5) {
                case 0:
                    main_character->current_room = 1;
                    break;
                case 9:
                    exit(0);
                default:
                    printf("Invalid room. Try again.\n");
                    continue;
            }
            break;
        case 6:
            printf("Oh no you went into the room and found the boss he closed the gate \n"
                   " and if you don't defeat him you can't escape.\n"
                   "To go back, write 0 and to quit, write 9.\n");
            fightMonster(main_character);
            int rand_value_5 = rand() % 2;
            if(rand_value_5 == 0){
                main_character->hp += 20;
                printf("you've been given extra hp\n");
            } else {
                printf("you got the loot");
                if(strcmp(main_character->Key, "Key") == 0){
                    printf("You've already taken the Key, you can't take it a second time.\n");
                } else {
                    printf("you've been given the key you need to get out of the dungeon.\n");
                    strcpy(main_character->Key, "Key");
                }
            }
            int a_6;
            scanf("%d",&a_6);
            switch (a_6) {
                case 0:
                    main_character->current_room = 2;
                    break;
                case 9:
                    exit(0);
                default:
                    printf("Invalid room. Try again.\n");
                    continue;
            }
            break;
        case 7:
            printf("You entered the room and realized that it was empty you will have to go back,\n"
                   "to go back write 0 or 9 if you want to leave.\n");
                int a_7;
                scanf("%d",&a_7);
                switch (a_7) {
                    case 0:
                        main_character->current_room = 2;
                        break;
                    case 9:
                        exit(0);
                    default:
                        printf("Invalid room. Try again.\n");
                        continue;
                }
                break;
        case 8:
            printf("You entered the room and realized that it was empty you will have to go back,\n"
                   "to go back write 0 or 9 if you want to leave.\n");
                int a_8;
                scanf("%d",&a_8);
                switch (a_8) {
                    case 0:
                        main_character->current_room = 3;
                        break;
                    case 9:
                        exit(0);
                    default:
                        printf("Invalid room. Try again.\n");
                        continue;
                }
                break;
        case 9:
            if(strcmp(main_character->Key, "Key") == 0){
                printf("You see a gate and there is a lock you take your key and get out of the dungeon,\n"
                       " congratulations you have won good luck in future adventures!\n");
                exit(0);
            } else {
                printf("You saw a gate and there was a lock and unfortunately \n"
                       " you don't have the key you have to go back and find the key.\n"
                       "To go back, write 0 and to quit, write 9.\n");
            }
                int a_9;
                scanf("%d",&a_9);
                switch (a_9) {
                    case 0:
                        main_character->current_room = 3;
                        break;
                    case 9:
                        exit(0);
                    default:
                        printf("Invalid room. Try again.\n");
                        continue;
                }
                break;
        case 10:
            printf("you hit and suddenly all the light disappeared was visible only the wheel of fortune \n"
                   "where 2 outcomes were spinning, but what are the outcomes remains a mystery.\n");
                if(main_character->wheel_spinning){
                    printf("You've already spun the wheel. To spin the wheel again, exit the room and re-enter.\n");
                } else {
                    int rand_value_2 = rand() % 2;
                    if(rand_value_2 == 0){
                        main_character->hp +=50;
                        printf("Congratulations on your extra hp.\n");
                    } else{
                        printf("You didn't get anything\n");
                    }
                }
                sleep(0.5);
                printf("To go back, write 0 and to quit, write 9.\n");
                int a_10;
                scanf("%d",&a_10);
                switch (a_10) {
                    case 0:
                        main_character->wheel_spinning = false;
                        main_character->current_room = 3;
                        break;
                    case 9:
                        exit(0);
                    default:
                        main_character->wheel_spinning = true;
                        printf("Invalid room. Try again.\n");
                        continue;
                }
        };
    }

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <player_name>\n", argv[0]);
        return 1;
    }

    srand((unsigned int) time(NULL));
    MainCharacter main_character;

    // Try to load the game
    if (loadGame(argv[1], &main_character)) {
        printf("Welcome back, %s! Your game has been loaded.\n", argv[1]);
    } else {
        // Create a new game
        printf("Starting a new game for %s.\n", argv[1]);
        MainCharacterSet(&main_character, argv[1], 100, NULL);
    }

    while (1) {
        launchRoom(&main_character);

        printf("Do you want to save the game? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            saveGame(&main_character);
        }

        printf("Do you want to quit the game? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            printf("Goodbye!\n");
            break;
        }
    }

    return 0;
}