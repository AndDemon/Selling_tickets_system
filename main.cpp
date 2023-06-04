#include <stdio.h> // ���������� �������
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <windows.h>
#include <fstream>
#include <list>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdbool.h>

#pragma comment(lib,"shell32")//��� ������������ �������� �������� � �������

using namespace std;

int callback_function(void* data, int argc, char** argv, char** azColName) {//������� ��� ���������� ������ ������
    char* pay = (char*)data;
    if (argc > 0) {
        strcpy(pay, argv[0]); // ����� �������� ������� paystatus �� ����� pay
    }
    return 0;
}

void cool_design(char str[1000], int len) {//������� ��� ������ ����� � ���� ����� � ���� ����
    int i = 0;
    int strLen = strlen(str);
    while (i < strLen) {
        int j = i + len;
        if (j >= strLen) {
            j = strLen;
        } else {
            while (j > i && str[j] != ' ') {
                j--;
            }
            if (j == i) {
                j = i + len;
            }
        }
        int width = len + 6;
        char temp = str[j];
        str[j] = '\0';
        std::cout << "|      " << std::left << std::setw(width) << &str[i] << "|" << std::endl;
        str[j] = temp;
        i = j + 1;
    }
}

int main() {
    system("color 03");
    SetConsoleCP(1251);//������������ encoding Cyrillic (Windows 1251) ��� ����������� ��������� ����
    SetConsoleOutputCP(1251);

    sqlite3 *db;//���������� ���� ����� 
    int rc = sqlite3_open("database.db", &db);      
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Unable to open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    char sql[2566];
    sprintf(sql, "CREATE TABLE IF NOT EXISTS tickets(id INTEGER PRIMARY KEY,  film_name TEXT, customer_name TEXT, booking_date TEXT, seans TEXT, seats INTEGER, tuppl TEXT, price TEXT, paystatus TEXT);");// ��������� ������� ������
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);

    sprintf(sql, "CREATE TABLE IF NOT EXISTS films(id INTEGER PRIMARY KEY, name TEXT, age TEXT, country TEXT, genre TEXT, cast TEXT, duration TEXT, about TEXT CHECK(LENGTH(about) <= 1000), link TEXT);");// ��������� ������� ������
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);



    while ( 1 ) {
        one:
        system("cls");
        printf("+----------------------------------------------------------------------------------------------------+\n");// ����
        printf("| K - ��������� ������                          ����:                                               |\n");
        printf("+----------------------------------------------------------------------------------------------------+\n");
        printf("|                                              ����'��� - 1                                          |\n");
        printf("|                                             �� ������ - 2                                         |\n");
        printf("|                                            ��� �������� - 3                                        |\n");
        printf("|                                               ����� - 4                                            |\n");
        printf("+----------------------------------------------------------------------------------------------------+\n");
        printf("���� �����: ");
        char menu;
        scanf("%s", &menu);
        if(menu=='1') {//���� ������� 1 �� ���� ������
            while( 1 ){
                prems:
                system("cls");
                printf("+------------------------------------------------------------------------+---------------+-----------+\n");// ������ ������ � ���� ����� id �� name
                printf("|                                              ����'���:                 | ������ ����� |           |\n");
                printf("+------------------------------------------------------------------------+---------------+-----------+\n");
                sqlite3_stmt *stmt;
                rc = sqlite3_prepare_v2(db, "SELECT * FROM films;", -1, &stmt, 0);//������� �� ������ � ���� ����� films 
                int cols = sqlite3_column_count(stmt);
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    const unsigned char *id = sqlite3_column_text(stmt, 0);
                    char bymam[1000];
                    strcpy(bymam, reinterpret_cast<const char*>(id));
                    cool_design(bymam, 88);//���� id ������ ����� �������
                    const unsigned char *name = sqlite3_column_text(stmt, 1);
                    char bymam1[1000];
                    strcpy(bymam1, reinterpret_cast<const char*>(name));
                    cool_design(bymam1, 88);//���� ����� ������ ����� �������
                };
                printf("|                                               ���� - w                                             |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                
                char name[256];
                const unsigned char *namef;
                printf("���� �����: ");
                scanf("%s", name);
                if (name[0] == 'W' || name[0] == 'w' || name[0] == '�' || name[0] == '�'){//������� � ���� ���� ������� w
                    goto one;
                }
                film:
                system("cls");
                sqlite3_stmt *pooping;
                char query[1000];
                 
                sprintf(query, "SELECT * FROM films WHERE id = %s;", name);// ���� ����� ��� �� id

                rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                printf("+----------------------------------------------------------------------------------------------------+\n");//���� ������ ������ � ���� ����� ���������� ����� ���������� ��� ��� �����, ���������� ���� ����������� �����, ��� ����������� ������ �� ��� �����
                while (sqlite3_step(pooping) == SQLITE_ROW) {
                    namef = sqlite3_column_text(pooping, 1);
                    char bymam2[1000];
                    strcpy(bymam2, reinterpret_cast<const char*>(namef));
                    cool_design(bymam2, 88);//���� ���������� ��� ����� � ������� 
                    const unsigned char *age = sqlite3_column_text(pooping, 2);
                    char bymam3[1000];
                    strcpy(bymam3, reinterpret_cast<const char*>(age));
                    cool_design(bymam3, 88);
                    const unsigned char *country = sqlite3_column_text(pooping, 3);
                    char bymam4[1000];
                    strcpy(bymam4, reinterpret_cast<const char*>(country));
                    cool_design(bymam4, 88);
                    const unsigned char *genre = sqlite3_column_text(pooping, 4);
                    char bymam5[1000];
                    strcpy(bymam5, reinterpret_cast<const char*>(genre));
                    cool_design(bymam5, 88);
                    const unsigned char *cast = sqlite3_column_text(pooping, 5);
                    char bymam6[1000];
                    strcpy(bymam6, reinterpret_cast<const char*>(cast));
                    cool_design(bymam6, 88);
                    const unsigned char *duration = sqlite3_column_text(pooping, 6);
                    char bymam7[1000];
                    strcpy(bymam7, reinterpret_cast<const char*>(duration));
                    cool_design(bymam7, 88);
                    const unsigned char *about = sqlite3_column_text(pooping, 7);
                    char bymam8[1000];
                    strcpy(bymam8, reinterpret_cast<const char*>(about));
                    cool_design(bymam8, 88);
                    const unsigned char *link = sqlite3_column_text(pooping, 8);
                    char bymam9[1000];
                    strcpy(bymam9, reinterpret_cast<const char*>(link));
                
                    printf("+----------------------------------------------------------------------------------------------------+\n");
                    printf("|                       ����'��� - w  | ����������� ������ - e  |  ������� - t                       |\n");
                    printf("+----------------------------------------------------------------------------------------------------+\n");
                    printf("���� �����: ");
                    char book[100];
                    scanf("%s", &book);
                    if (book[0] == 'W'|| book[0] == 'w' || book[0] == '�' || book[0] == '�'){//����� ���� ������� w
                        goto prems;
                    }
                    if (book[0] == 'T'|| book[0] == 't' || book[0] == '�' || book[0] == '�'){
                        ShellExecuteA(0, "open", bymam9, NULL, NULL, SW_SHOWDEFAULT);//�������� �������� ������ � ������� ���� ������� t
                        goto film;
                    }
                    if (book[0] == 'E' || book[0] == 'e' || book[0] == '�' || book[0] == '�'){//������ ���������� ���� ������� e
                        system("cls");
                        char customer_name[255];
                        printf("+----------------------------------------------------------------------------------------------------+\n");//�������� � ����� customer_name ������� �� ��'� �볺���
                        printf("|                                    ������ ���� ������� �� ��'�:     ³������ ���������� - w     |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf(": ");
                        scanf("%i", &customer_name);
                        fgets(customer_name, 255, stdin);
                        if (customer_name[0] == 'W' || customer_name[0] == 'w' || customer_name[0] == '�' || customer_name[0] == '�'){//����� ���������� ���� ������� w
                            goto prems;
                        }
                        else{
                            while( 1 ){
                                system("cls");
                                int booking_date;
                                printf("+----------------------------------------------------------------------------------------------------+\n");//�������� � ����� booking_date ���� ������
                                printf("|                                    ������ ����(������ ����� 1-31):                               |\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("������ �����: ");
                                scanf("%d", &booking_date);
                                getchar();//// ������� ������ ����� ��� �������� �� ��������
                                if((0 < booking_date) && (booking_date < 32)){//���� ���� ������
                                    while( 1 ){
                                        roffflan:
                                        system("cls");
                                        char seans[100];
                                        char time[100];
                                        printf("+----------------------------------------------------------------------------------------------------+\n");//�������� � ����� time ��� ������
                                        printf("|                               ������ �����:                         ³������ ���������� - w      |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("|            10:40 - 1           19:30 - 4                                                           |\n");
                                        printf("|            12:40 - 2                                                                               |\n");
                                        printf("|            15:50 - 3                                                                               |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("���� �����: ");
                                        scanf("%s", &seans);
                                        if (seans[0] == 'W' || seans[0] == 'w' || seans[0] == '�' || seans[0] == '�'){//����� ���������� ���� ������� w
                                            goto prems;
                                        }
                                        if(seans[0] == '1'){//������� ������
                                           strncpy(time, "10:40", sizeof(time));
                                           goto seats;
                                        }
                                        if(seans[0] == '2'){
                                           strncpy(time, "12:40", sizeof(time));
                                           goto seats;
                                        }
                                        if(seans[0] == '3'){
                                           strncpy(time, "15:50", sizeof(time));
                                           goto seats;
                                        }
                                        if(seans[0] == '4'){
                                           strncpy(time, "19:30", sizeof(time));
                                           goto seats;
                                        }
                                        else{
                                            goto roffflan;//���� ������� ���� ����, �� goto 
                                        }
                                    
                                        seats:
                                        system("cls");
                                        char seats[100];
                                        char tuppl[100];
                                        char price[100];
                                        char query[100];
                                        while( 1 ){
                                            system("cls");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");//���� ���� � �������� � ���� tuppl �� price ��������� ��� ��� ��� ���� �� ���� � ��������� �� ������ ����
                                            printf("|                               ������ ����:     | ��� Vip ���� - v, ³������ ���������� - w     |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("|                      �������� ����(1-90) - 130 ���, Vip ����(91-104) - 230���                    |\n");
                                            printf("|                        ______________-------------------------______________                       |\n");
                                            printf("|           ____________(                        �����                        )____________          |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("|             (  ( 1) ( 2) ( 3) ( 4) ( 5) ( 6) ( 7) ( 8) ( 9) (10) (11) (12) (13) (14)               |\n");
                                            printf("|            (   (15) (16) (17) (18) (19) (20) (21) (22) (23) (24) (25) (26) (27) (28)               |\n");
                                            printf("|           (    (29) (30) (31) (32) (33) (34) (35) (36) (37) (38) (39) (40) (41) (42)               |\n");
                                            printf("| �������:(               (43) (44) (45) (46) (47) (48) (49) (50) (51) (52) (53) (54)               |\n");     
                                            printf("|           (              (55) (56) (57) (58) (59) (60) (61) (62) (63) (64) (65) (66)               |\n");
                                            printf("|            (             (67) (68) (69) (70) (71) (72) (73) (74) (75) (76) (77) (78)               |\n");
                                            printf("|             (            (79) (80) (81) (82) (83) (84) (85) (86) (87) (88) (89) (90)               |\n");
                                            printf("| Vip:    ( 91) ( 92) ( 93) ( 94) ( 95) ( 96) ( 97) ( 98) ( 99) (100) (101) (102) (103) (104)        |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("���� �����: ");
                                            scanf("%s", &seats);
                                            char query[1000];
                                            sprintf(query, "SELECT COUNT(*) FROM tickets WHERE film_name = '%s' AND booking_date = '%d' AND seans = '%s' AND seats = '%s';", namef, booking_date, time, seats);//��������, �� �� ������������� ��� ������ �� �� ����, � ��� ���, �� ��� �����
                                            sqlite3_stmt* stmt;
                                            int result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
                                            if (result == SQLITE_OK) {
                                                result = sqlite3_step(stmt);
                                                int count = sqlite3_column_int(stmt, 0);
                                                sqlite3_finalize(stmt);

                                                if (count > 0) {
                                                    while( 1 ){
                                                        system("cls");
                                                        char error2[100];
                                                        printf("+----------------------------------------------------------------------------------------------------+\n");//���� ���������� ���� ������� ����, ��� ���� ��� ������� ���������� ���� �������������
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                   ̳��� ����� %s ��� ������������                                  |\n", seats);                                                 
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                                        printf("|                                              ����� - w                                             |\n");
                                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                                        printf("���� �����: ");
                                                        scanf("%s", &error2);
                                                        if (error2[0] == 'W' || error2[0] == 'w' || error2[0] == '�' || error2[0] == '�'){//����� ���� ������� w
                                                            goto seats;
                                                        }
                                                        else{
                                                            ;//���� ������� ���� ����, �� ���� ���������� ������
                                                        }
                                                    }
                                                }
                                            }

                                            if(strcmp(seats, "1") == 0 || strcmp(seats, "2") == 0 || strcmp(seats, "3") == 0 || strcmp(seats, "4") == 0 || strcmp(seats, "5") == 0 || strcmp(seats, "6") == 0 || strcmp(seats, "7") == 0 || strcmp(seats, "8") == 0 || strcmp(seats, "9") == 0 || strcmp(seats, "10") == 0 || strcmp(seats, "11") == 0 || strcmp(seats, "12") == 0 || strcmp(seats, "13") == 0 || strcmp(seats, "14") == 0 || strcmp(seats, "15") == 0 || strcmp(seats, "16") == 0 || strcmp(seats, "17") == 0 || strcmp(seats, "18") == 0 || strcmp(seats, "19") == 0 || strcmp(seats, "20") == 0 || strcmp(seats, "21") == 0 || strcmp(seats, "22") == 0 || strcmp(seats, "23") == 0 || strcmp(seats, "24") == 0 || strcmp(seats, "25") == 0 || strcmp(seats, "26") == 0 || strcmp(seats, "27") == 0 || strcmp(seats, "28") == 0 || strcmp(seats, "29") == 0 || strcmp(seats, "30") == 0 || strcmp(seats, "31") == 0 || strcmp(seats, "32") == 0 || strcmp(seats, "33") == 0 || strcmp(seats, "34") == 0 || strcmp(seats, "35") == 0 || strcmp(seats, "36") == 0 || strcmp(seats, "37") == 0 || strcmp(seats, "38") == 0 || strcmp(seats, "39") == 0 || strcmp(seats, "40") == 0 || strcmp(seats, "41") == 0 || strcmp(seats, "42") == 0 || strcmp(seats, "43") == 0 || strcmp(seats, "44") == 0 || strcmp(seats, "45") == 0 || strcmp(seats, "46") == 0 || strcmp(seats, "47") == 0 || strcmp(seats, "48") == 0 || strcmp(seats, "49") == 0 || strcmp(seats, "50") == 0 || strcmp(seats, "51") == 0 || strcmp(seats, "52") == 0 || strcmp(seats, "53") == 0 || strcmp(seats, "54") == 0 || strcmp(seats, "55") == 0 || strcmp(seats, "56") == 0 || strcmp(seats, "57") == 0 || strcmp(seats, "58") == 0 || strcmp(seats, "59") == 0 || strcmp(seats, "60") == 0 || strcmp(seats, "61") == 0 || strcmp(seats, "62") == 0 || strcmp(seats, "63") == 0 || strcmp(seats, "64") == 0 || strcmp(seats, "65") == 0 || strcmp(seats, "66") == 0 || strcmp(seats, "67") == 0 || strcmp(seats, "68") == 0 || strcmp(seats, "69") == 0 || strcmp(seats, "70") == 0 || strcmp(seats, "71") == 0 || strcmp(seats, "72") == 0 || strcmp(seats, "73") == 0 || strcmp(seats, "74") == 0 || strcmp(seats, "75") == 0 || strcmp(seats, "76") == 0 || strcmp(seats, "77") == 0 || strcmp(seats, "78") == 0 || strcmp(seats, "79") == 0 || strcmp(seats, "80") == 0 || strcmp(seats, "81") == 0 || strcmp(seats, "82") == 0 || strcmp(seats, "83") == 0 || strcmp(seats, "84") == 0 || strcmp(seats, "85") == 0 || strcmp(seats, "86") == 0 || strcmp(seats, "87") == 0 || strcmp(seats, "88") == 0 || strcmp(seats, "89") == 0 || strcmp(seats, "90") == 0){//���� ���� �� 1 �� 90, �� � ���� ��������� ���� ��� ����� ����������, ����, �� ��� ����.
                                                strncpy(tuppl, "��������", sizeof(tuppl));//�������� � ���� ��� ��� ��� ���� �� ���� ������
                                                strncpy(price, "130 ���", sizeof(price));
                                                goto finish1;
                                            }
                                            if(strcmp(seats, "91")==0 || strcmp(seats, "92")==0 || strcmp(seats, "93")==0 || strcmp(seats, "94")==0 || strcmp(seats, "95")==0 || strcmp(seats, "96")==0 || strcmp(seats, "97")==0 || strcmp(seats, "98")==0 || strcmp(seats, "99")==0 || strcmp(seats, "100")==0 || strcmp(seats, "101")==0 || strcmp(seats, "102")==0 || strcmp(seats, "103")==0 || strcmp(seats, "103")==0){//���� ���� �� 91 �� 103, �� � ���� ��������� ���� ��� ����� ����������, ����, �� ��� ����.
                                                strncpy(tuppl, "Vip", sizeof(tuppl));//�������� � ���� ��� ��� ��� ���� �� ���� ������
                                                strncpy(price, "230 ���", sizeof(price));
                                                goto finish1;
                                            }

                                            if (seats[0] == 'W' || seats[0] == 'w' || seats[0] == '�' || seats[0] == '�'){//����� ���������� ���� ������� w
                                                goto prems;
                                            }
                                            if (seats[0] == 'V' || seats[0] == 'v' || seats[0] == '�' || seats[0] == '�'){//���� ����� ���� ���� ������ v
                                                while ( 1 ){
                                                    system("cls");
                                                    char vip[100];
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");// ���� Vip ����
                                                    printf("|                                           ��� vip ����                       ���� ���� - w      |\n");
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("| �� �������� ����� ����� � ������� ���������, �� ������� ��������� ������ ��� �� ��������.   |\n");
                                                    printf("| ����� ��������� �������� ��� �� �� ����������, �� ���� ����� ��������� �������� ����        |\n");
                                                    printf("| �������� �� ����������� ����, �� ��������� ������. ��������� VIP-���� ��� ��������� ������ �   |\n");
                                                    printf("| remove_the_cinema, �� ������ �����!                                                             |\n");
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("���� �����: ");
                                                    scanf("%s", &vip);
                                                    if  (vip[0] == 'W' || vip[0] == 'w' || vip[0] == '�' || vip[0] == '�'){//���������� �� ������ ���� ���� ������� w
                                                        goto seats;
                                                    }
                                                    else{
                                                        ;//���� ������� ���� ����, �� ���� ���������� ������
                                                    }

                                                }
                                            }
                                            else{
                                                ;//���� ������� ���� ����, �� ���� ���������� ������
                                            }
                                        }
                                        
                                        finish1:
                                        sprintf(sql, "insert into tickets(film_name, customer_name, booking_date, seans, seats, tuppl, price, paystatus) values('%s', '%s', '%d', '%s', '%s', '%s', '%s', '�� ��������');", namef, customer_name, booking_date, time, seats, tuppl, price);//�������� � ���� ����� ������ ���������� � ������ ��� �� �������� �����
                                        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                                        while( 1 ){
                                            system("cls");
                                            char finish[100];
                                            printf("+----------------------------------------------------------------------------------------------------+\n");// ���������� ���������� ��� ��� ��� ������ ��� � ��� ����� � ���������� ���� ������ ������� �� ������
                                            printf("|                                       ���������� ���������!                    ���� - w            |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("|                                      ������� �� ������ - k                                        |\n");
                                            printf("|   ���������� �� ����������:                                                                        |\n");
                                            cool_design(bymam2, 88);//���� ���������� ��� ���������� ����� ������� 
                                            cool_design(time, 88);
                                            cool_design(seats, 88);
                                            cool_design(tuppl, 88);
                                            cool_design(price, 88);
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("���� �����: ");
                                            scanf("%s", &finish);
                                            if  (finish[0] == 'W' || finish[0] == 'w' || finish[0] == '�' || finish[0] == '�'){//������� �� ���� 
                                                goto one;
                                            }
                                            if  (finish[0] == 'K' || finish[0] == 'k' || finish[0] == '�' || finish[0] == '�'){//������� �� ������
                                                goto tickets;
                                            }
                                            else{//���� ����, ���� ���������� ������
                                                ;
                                            }
                                        }   
                                    }
                                }
                                else{
                                    ;//���� ������� ���� ����, �� ���� ���������� ������
                                }
                            }
                        }
                    }
                }
            }   
        }



        if(menu=='2') {
            while ( 1 ){
                tickets:
                system("cls");
                printf("+----------------------------------------------------------------------------------------------------+\n");// ������ ������ � ���� ����� (�� ����� ����������)
                printf("                                                ������:                 | ������ ������ |            \n");
                sqlite3_stmt *ticket;
                rc = sqlite3_prepare_v2(db, "SELECT * FROM tickets;", -1, &ticket, 0);
                int cols = sqlite3_column_count(ticket);
                while (sqlite3_step(ticket) == SQLITE_ROW) {//���� ������ � ���� ����� tickets 
                    const unsigned char *id = sqlite3_column_text(ticket, 0);
                    printf("%s - ",id);
                    const unsigned char *film_name = sqlite3_column_text(ticket, 1);
                    printf("%s, ",film_name);
                    const unsigned char *customer_name = sqlite3_column_text(ticket, 2);
                    printf("%s",customer_name);
                    const unsigned char *price = sqlite3_column_text(ticket, 7);
                    printf("%s, ",price);
                    const unsigned char *paystatus = sqlite3_column_text(ticket, 8);
                    printf("%s;\n",paystatus);
                };
                printf("                                                                                                      \n");
                printf("                                               ���� - w                                               \n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                char tick[256];
                printf("���� �����: ");
                scanf("%s", tick);
                system("cls");
                if (tick[0] == 'W' || tick[0] == 'w' || tick[0] == '�' || tick[0] == '�'){//���� ���� ������� w
                    goto one;
                }
                sqlite3_stmt *pooping;
                char query[1000];
                 
                sprintf(query, "SELECT COUNT(*) FROM tickets WHERE id = %s;", tick);//�������� ��������� �����
                rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                if (sqlite3_step(pooping) == SQLITE_ROW) {
                    int ticketCount = sqlite3_column_int(pooping, 0);
                    if (ticketCount == 0) {
                        while ( 1 ){
                            system("cls");
                            char error1[100];
                            printf("+----------------------------------------------------------------------------------------------------+\n");//���� ���������� ������� id ������ ����� ����, �� ���������� ���� �������
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                ������ � ID %s �� �������� � ��� �����.                             |\n", tick);                                                 
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("|                                              ����� - w                                             |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("���� �����: ");
                            scanf("%s", &error1);
                            if (error1[0] == 'W' || error1[0] == 'w' || error1[0] == '�' || error1[0] == '�'){//����� ���� ������� w
                                goto tickets;
                            }
                            else{
                                ;//���� ������� ���� ����, �� ���� ���������� ������
                            }
                        }
                    }
                    else {
                        sprintf(query, "SELECT * FROM tickets WHERE id = %s;", tick);

                        rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                        printf("+----------------------------------------------------------------------------------------------------+\n");// ���� ������ ������ ���������� ����� ���������� � ���� ����� ��� ��� ������ 
                        while (sqlite3_step(pooping) == SQLITE_ROW) {
                            const unsigned char *id = sqlite3_column_text(pooping, 0);
                            printf("%s - ", id);
                            const unsigned char *film_name = sqlite3_column_text(pooping, 1);
                            printf("%s, �������  �� ��'� - ", film_name);
                            const unsigned char *customer_name = sqlite3_column_text(pooping, 2);
                            printf("%s���� - ", customer_name);
                            const unsigned char *booking_date = sqlite3_column_text(pooping, 3);
                            printf("%s, ����� - ", booking_date);
                            const unsigned char *seans = sqlite3_column_text(pooping, 4);
                            printf("%s, ���� - ", seans);
                            const unsigned char *seats = sqlite3_column_text(pooping, 5);
                            printf("%s, ��� ���� - ", seats);
                            const unsigned char *tuppl = sqlite3_column_text(pooping, 6);
                            printf("%s, ���� - ", tuppl);
                            const unsigned char *price = sqlite3_column_text(pooping, 7);
                            printf("%s, ", price);
                            const unsigned char *paystatus = sqlite3_column_text(pooping, 8);
                            printf("%s;\n",paystatus);
                        }
                    }
                }   
                else {
                    while ( 1 ){
                        system("cls");
                        char error2[100];
                        printf("+----------------------------------------------------------------------------------------------------+\n");//���� ���������� ������ �� ������� ������ � ����� ��, �� ���������� ���� �������
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                    ������� ��� �������� ������...                                 |\n", tick);                                                 
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("|                                              ����� - w                                             |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("���� �����: ");
                        scanf("%s", &error2);
                        if (error2[0] == 'W' || error2[0] == 'w' || error2[0] == '�' || error2[0] == '�'){//����� ���� ������� w
                            goto tickets;
                        }
                        else{
                            ;//���� ������� ���� ����, �� ���� ���������� ������
                        }
                    }
                }
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("                        ������ - w  | �������� ������ - e | ³������ ���������� - r                  \n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("���� �����: ");
                char book[100];
                scanf("%s", &book);
                if (book[0] == 'W' || book[0] == 'w' || book[0] == '�' || book[0] == '�'){//������ ���� ������� w
                    goto tickets;
                }
                if (book[0] == 'E' || book[0] == 'e' || book[0] == '�' || book[0] == '�'){//������ ������ ���� ������� e
                    while( 1 ){
                        system("cls");
                        char pay[100];
                        sprintf(sql, "SELECT paystatus FROM tickets WHERE id = '%s';", tick);
                        rc = sqlite3_exec(db, sql, callback_function, &pay, NULL); // ��� callback_function - ������� ������ �������� ������� paystatus � ������ ���� � ����� pay
                        if (strcmp(pay, "��������") == 0) {
                            printf("+----------------------------------------------------------------------------------------------------+\n");// ���� ������ ��� ��������� �����
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                    ������ ��� ��������� �����!                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("|                                              ����� - w                                             |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("���� �����: ");
                            scanf("%s", &pay);
                            if (pay[0] == 'W' || pay[0] == 'w' || pay[0] == '�' || pay[0] == '�') {
                                goto tickets;
                            }
                            else{
                                ;//���� ������� ���� ����, �� ���� ���������� ������
                            }
                        } else {
                            sprintf(sql, "UPDATE tickets SET paystatus = '��������' WHERE id = '%s';", tick);
                            rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                            printf("+----------------------------------------------------------------------------------------------------+\n");//������ ������
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                             ��������!!!                                            |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("|                                              ����� - w                                             |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("���� �����: ");
                            scanf("%s", &pay);
                            if (pay[0] == 'W' || pay[0] == 'w' || pay[0] == '�' || pay[0] == '�') {//����� ���� ������� w
                                goto tickets;
                            }
                            else{
                                ;//���� ������� ���� ����, �� ���� ���������� ������
                            }
                        }
                    }
                }
                if (book[0] == '�' || book[0] == '�' || book[0] == 'R' || book[0] == 'r'){//����� ���������� ���� ������� r
                    while( 1 ){
                        system("cls");
                        char pay1[100];
                        sprintf(sql, "DELETE FROM tickets WHERE id = '%s';", tick);
                        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                        printf("+----------------------------------------------------------------------------------------------------+\n");// ����� ����������
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                        ���������� ���������!!!                                   |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("|                                              ����� - w                                             |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("���� �����: ");
                        scanf("%s", &pay1);
                        if (pay1[0] == 'W' || pay1[0] == 'w' || pay1[0] == '�' || pay1[0] == '�'){//����� ���� ������� w
                            goto tickets;
                        }
                        else{
                            ;//���� ������� ���� ����, �� ���� ���������� ������
                        }
                    }
                }
            }
        }


        if(menu=='3') {// ���������� ��� ��������� ���� ������� 3
            char about[100];
            while( 1 ){
                system("cls");
                printf("+---------------------------------------------------------------------+-----------------------+------+\n");// ���������� ��� ��������� ��� �����������
                printf("| Version 1.0 release                        ��� ��������:            |developer - Andrew165#1|      |\n");
                printf("+---------------------------------------------------------------------+-----------------------+------+\n");
                printf("| �����! ������� ������� �� �������� �� ������� ������ � ��������! ������� ������ ������ ��     |\n");
                printf("| ������� �������� ������ �� ������ � �������� ������ �� ������.                                   |\n");
                printf("| ���� �������� �� ���� ������� �� ��������� ���������. ���, �� ��� ������� �������, �� �������   |\n");
                printf("| �����, �� ���� �� ������ ���, ������� ������� �� ��'�, ������� ������� ��� ��� ����� ��          |\n");
                printf("| ����������� ������, ���� � ��� ������ �������� ������. �� ����� ������ ������� ����������, ���|\n");
                printf("| ���� �� ��� �������� ����� �� ��� �� ���������.                                                    |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("|                                              ���� - w                                              |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("���� �����: ");
                scanf("%s", &about);
                if(about[0] == 'W' || about[0] == 'w' || about[0] == '�' || about[0] == '�'){//����� ���� ������� w
                    goto one;
                }
                else{
                    ;
                }
            }
        }








        if(menu == 'K' || menu == 'k' || menu == '�' || menu == '�') {
            konnstr1:
            system("cls");
            char konstr[100];
            printf("+----------------------------------------------------------------------------------------------------+\n");// ����������� ������
            printf("|   ������ ����� - e                                                                                 |\n");
            printf("|   �������� ����� - d                                                                               |\n");
            printf("+----------------------------------------------------------------------------------------------------+\n");
            printf("|                                              ����� - w                                             |\n");
            printf("+----------------------------------------------------------------------------------------------------+\n");
            printf("���� �����: ");
            scanf("%s", &konstr);
            if(konstr[0] == 'W' || konstr[0] == 'w' || konstr[0] == '�' || konstr[0] == '�'){//����� ���� ������� w
                goto one;
            }

            if(konstr[0] == 'E' || konstr[0] == 'e' || konstr[0] == '�' || konstr[0] == '�'){
                konnstr2:
                system("cls");
                char intfilm1[100];
                printf("+----------------------------------------------------------------------------------------------------+\n");// �������� ����� ������ � �����
                printf("| ����� - w, �� �������� ������ ww     ������ ����� ������:                                        |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("������ ���: ");
                getchar();
                fgets(intfilm1, 255, stdin);
                int len = strcspn(intfilm1, "\n"); 
                intfilm1[len] = '\0';
                if(intfilm1[0] == 'W' || intfilm1[0] == 'w' || intfilm1[0] == '�' || intfilm1[0] == '�'){//����� ���� ������� w
                    goto konnstr1;
                }
                else{
                    konnstr3:
                    system("cls");
                    char intfilm2[100];
                    printf("+----------------------------------------------------------------------------------------------------+\n");//�������� ������� �������� ������ � �����
                    printf("| ����� - w       ������ ������ ������� ������(� ������: ³��� ��������� - 18+):                 |\n");
                    printf("+----------------------------------------------------------------------------------------------------+\n");
                    printf("������ ���: ");
                    fgets(intfilm2, 255, stdin);
                    int len = strcspn(intfilm2, "\n"); 
                    intfilm2[len] = '\0';
                    if(intfilm2[0] == 'W' || intfilm2[0] == 'w' || intfilm2[0] == '�' || intfilm2[0] == '�'){//����� ���� ������� w
                        goto konnstr2;
                    }
                    else{
                        konnstr4:
                        system("cls");
                        char intfilm3[100];
                        printf("+----------------------------------------------------------------------------------------------------+\n");// �������� ����� ��������� ������ � �����
                        printf("| ����� - w            ������ ����� ��������� ������(� ������: ����� - ���):                     |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("������ ���: ");
                        fgets(intfilm3, 255, stdin);
                        int len = strcspn(intfilm3, "\n"); 
                        intfilm3[len] = '\0';
                        if(intfilm3[0] == 'W' || intfilm3[0] == 'w' || intfilm3[0] == '�' || intfilm3[0] == '�'){//����� ���� ������� w
                            goto konnstr3;
                        }
                        else{
                            konnstr5:
                            system("cls");
                            char intfilm4[100];
                            printf("+----------------------------------------------------------------------------------------------------+\n");// �������� ����� ������ � �����
                            printf("| ����� - w            ������ ���� ������(� ������: ���� - ����, ����������):                      |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("������ ���: ");
                            fgets(intfilm4, 255, stdin);
                            int len = strcspn(intfilm4, "\n"); 
                            intfilm4[len] = '\0';
                            if(intfilm4[0] == 'W' || intfilm4[0] == 'w' || intfilm4[0] == '�' || intfilm4[0] == '�'){//����� ���� ������� w
                                goto konnstr4;
                            }
                            else{
                                konnstr6:
                                system("cls");
                                char intfilm5[100];
                                printf("+----------------------------------------------------------------------------------------------------+\n");// �������� �������� ������ ������ � �����
                                printf("| ����� - w  ������ �������� ������ ������(� ������: � �������� �����: ��� �����, �� �������...)|\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("������ ���: ");
                                fgets(intfilm5, 255, stdin);
                                int len = strcspn(intfilm5, "\n"); 
                                intfilm5[len] = '\0';
                                if(intfilm5[0] == 'W' || intfilm5[0] == 'w' || intfilm5[0] == '�' || intfilm5[0] == '�'){//����� ���� ������� w
                                    goto konnstr5;
                                }
                                else{
                                    konnstr7:
                                    system("cls");
                                    char intfilm6[100];
                                    printf("+----------------------------------------------------------------------------------------------------+\n");// �������� ��������� ������ � �����
                                    printf("| ����� - w        ������ ��������� ������(� ������: ��������� - 2:29 149 ��)                    |\n");
                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                    printf("������ ���: ");
                                    fgets(intfilm6, 255, stdin);
                                    int len = strcspn(intfilm6, "\n"); 
                                    intfilm6[len] = '\0';
                                    if(intfilm6[0] == 'W' || intfilm6[0] == 'w' || intfilm6[0] == '�' || intfilm6[0] == '�'){//����� ���� ������� w
                                        goto konnstr6;
                                    }
                                    else{
                                        konnstr8:
                                        system("cls");
                                        char intfilm7[100];
                                        printf("+----------------------------------------------------------------------------------------------------+\n");// �������� ���� ������ � �����
                                        printf("| ����� - w                 ������ ���� ������(� ������: ���� ������:...)                          |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("������ ���: ");
                                        fgets(intfilm7, 255, stdin);
                                        int len = strcspn(intfilm7, "\n"); 
                                        intfilm7[len] = '\0';
                                        if(intfilm7[0] == 'W' || intfilm7[0] == 'w' || intfilm7[0] == '�' || intfilm7[0] == '�'){//����� ���� ������� w
                                            goto konnstr7;
                                        }
                                        else{
                                            konnstr9:
                                            system("cls");
                                            char intfilm8[100];
                                            printf("+----------------------------------------------------------------------------------------------------+\n");// �������� ��������� �� ������� � �����
                                            printf("| ����� - w                            ������ ��������� �� �������:                                 |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("������ ���: ");
                                            fgets(intfilm8, 255, stdin);
                                            int len = strcspn(intfilm8, "\n"); 
                                            intfilm8[len] = '\0';
                                            if(intfilm8[0] == 'W' || intfilm8[0] == 'w' || intfilm8[0] == '�' || intfilm8[0] == '�'){//����� ���� ������� w
                                                goto konnstr8;
                                            }
                                            else{
                                                sprintf(sql, "insert into films(name, age, country, genre, cast, duration, about, link) values('%s', '%s', '%d', '%s', '%s', '%s', '%s', '%s');", intfilm1, intfilm2, intfilm3, intfilm4, intfilm5, intfilm6, intfilm7, intfilm8);//�������� � ���� ����� ������ ����� ����� ���������� ��� ���� �� �������� ����� � ������
                                                rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                                                while( 1 ){
                                                    system("cls");
                                                    char finishkon[100];
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");// ���������� ��������� ������ ������
                                                    printf("| ���� - w                           ��������� ������ ���������!                                     |\n");
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("|   ���������� ��� ����� ���� �� ������:                                                             |\n");
                                                    cool_design(intfilm1, 88);
                                                    cool_design(intfilm2, 88);
                                                    cool_design(intfilm3, 88);
                                                    cool_design(intfilm4, 88);
                                                    cool_design(intfilm5, 88);
                                                    cool_design(intfilm6, 88);
                                                    cool_design(intfilm7, 88);
                                                    cool_design(intfilm8, 88);
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("���� �����: ");
                                                    scanf("%s", &finishkon);
                                                    if(finishkon[0] == 'W' || finishkon[0] == 'w' || finishkon[0] == '�' || finishkon[0] == '�'){//���� ���� ������� w
                                                        goto one;
                                                    }
                                                    else{
                                                        ;//���� ������� ���� ����, �� ���� ���������� ������
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }





            if(konstr[0] == 'D' || konstr[0] == 'd' || konstr[0] == '�' || konstr[0] == '�'){//���� ��� ������ ��� ��������� ���� ������� d
                ddd:
                while( 1 ){
                    system("cls");
                    printf("+---------------------------------------------------------------------+----------------------------+-+\n");// ��������� ������ � ���� �����
                    printf("|                                              ����'���:              | ������ ����� ��� ���������| |\n");
                    printf("+---------------------------------------------------------------------+----------------------------+-+\n");
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "SELECT * FROM films;", -1, &stmt, 0);// ���� ��� ������
                    int cols = sqlite3_column_count(stmt);
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        const unsigned char *id = sqlite3_column_text(stmt, 0);
                        char bymam[1000];
                        strcpy(bymam, reinterpret_cast<const char*>(id));
                        cool_design(bymam, 88);
                        const unsigned char *name = sqlite3_column_text(stmt, 1);
                        char bymam1[1000];
                        strcpy(bymam1, reinterpret_cast<const char*>(name));
                        cool_design(bymam1, 88);
                    };
                    printf("|                                              ����� - w                                             |\n");
                    printf("+----------------------------------------------------------------------------------------------------+\n");
                    
                    char name12[256];
                    const unsigned char *namef;
                    printf("���� �����: ");
                    scanf("%s", name12);
                    system("cls");
                    if (name12[0] == 'W' || name12[0] == 'w' || name12[0] == '�' || name12[0] == '�'){//����� ���� ������� w
                        goto konnstr1;
                    }
                    caca:
                    system("cls");
                    sqlite3_stmt *pooping;
                    char query[1000];
                     
                    sprintf(query, "SELECT * FROM films WHERE id = %s;", name12);

                    rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                    printf("+----------------------------------------------------------------------------------------------------+\n");//���� ���������� ��� ����� ���� �� ������ ��������
                    while (sqlite3_step(pooping) == SQLITE_ROW) {
                        namef = sqlite3_column_text(pooping, 1);
                        char bymam2[1000];
                        strcpy(bymam2, reinterpret_cast<const char*>(namef));
                        cool_design(bymam2, 88);
                        const unsigned char *age = sqlite3_column_text(pooping, 2);
                        char bymam3[1000];
                        strcpy(bymam3, reinterpret_cast<const char*>(age));
                        cool_design(bymam3, 88);
                        const unsigned char *country = sqlite3_column_text(pooping, 3);
                        char bymam4[1000];
                        strcpy(bymam4, reinterpret_cast<const char*>(country));
                        cool_design(bymam4, 88);
                        const unsigned char *genre = sqlite3_column_text(pooping, 4);
                        char bymam5[1000];
                        strcpy(bymam5, reinterpret_cast<const char*>(genre));
                        cool_design(bymam5, 88);
                        const unsigned char *cast = sqlite3_column_text(pooping, 5);
                        char bymam6[1000];
                        strcpy(bymam6, reinterpret_cast<const char*>(cast));
                        cool_design(bymam6, 88);
                        const unsigned char *duration = sqlite3_column_text(pooping, 6);
                        char bymam7[1000];
                        strcpy(bymam7, reinterpret_cast<const char*>(duration));
                        cool_design(bymam7, 88);
                        const unsigned char *about = sqlite3_column_text(pooping, 7);
                        char bymam8[1000];
                        strcpy(bymam8, reinterpret_cast<const char*>(about));
                        cool_design(bymam8, 88);
                        const unsigned char *link = sqlite3_column_text(pooping, 8);
                        char bymam9[1000];
                        strcpy(bymam9, reinterpret_cast<const char*>(link));
                    
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("|                                    ����� - w  | �������� ����� - r                                 |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("���� �����: ");
                        char book12[100];
                        scanf("%s", &book12);
                        if (book12[0] == 'W'|| book12[0] == 'w' || book12[0] == '�' || book12[0] == '�'){//����� ���� ������� w
                            goto ddd;
                        }
                        if (book12[0] == 'R'|| book12[0] == 'r' || book12[0] == '�' || book12[0] == '�'){//��������� ������ ���� ������� r
                            while ( 1 ){
                                system("cls");
                                char yes[100];
                                printf("+----------------------------------------------------------------------------------------------------+\n");// ������������ ��� ��������� ������
                                printf("|                                                                                                    |\n");
                                printf("|              �� ��� ��� ��� ����� ���� ��������, ��� ���������� ��������� ������ Y             |\n");
                                printf("|                                                                                                    |\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("|                                        ³������ ��������� - w                                     |\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("������ ���: ");
                                scanf("%s", &yes);
                                if (yes[0] == 'W'|| yes[0] == 'w' || yes[0] == '�' || yes[0] == '�'){//����� ���������� ���� ������� w
                                    goto caca;
                                }
                                if (yes[0] == 'Y'|| yes[0] == 'y' || yes[0] == '�' || yes[0] == '�'){//��������� ������ ���� ������� y
                                    while( 1 ){
                                        system("cls");
                                        char remove1[100];
                                        sprintf(sql, "DELETE FROM films WHERE id = '%s';", name12);//��������� ������ �� �������� id
                                        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                                        printf("+----------------------------------------------------------------------------------------------------+\n");// ��������� ������
                                        printf("|                                                                                                    |\n");
                                        printf("|                                         Գ��� ��������!!!                                          |\n");
                                        printf("|                                                                                                    |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("|                                              ���� - w                                              |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("���� �����: ");
                                        scanf("%s", &remove1);
                                        if (remove1[0] == 'W' || remove1[0] == 'w' || remove1[0] == '�' || remove1[0] == '�'){//���� ���� ������� w
                                            goto one;
                                        }
                                        else{
                                            ;//���� ������� ���� ����, �� ���� ���������� ������
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if(menu=='4') {
            printf("�����.\n");//����� � ��������
            break;
        }
        else{
            ;
        }

    }
    return 0;   
}