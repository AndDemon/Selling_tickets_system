#include <stdio.h> // підключення бібліотек
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


#pragma comment(lib,"shell32")//для використання відкриття посилань в браузері

using namespace std;

int callback_function(void* data, int argc, char** argv, char** azColName) {//функція для визначення оплати квитка
    char* pay = (char*)data;
    if (argc > 0) {
        strcpy(pay, argv[0]); // копіює значення стовпця paystatus до змінної pay
    }
    return 0;
}

void cool_design(char str[1000], int len) {//функція для виводу даних з бази даних в формі меню
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
    SetConsoleCP(1251);//встановлення encoding Cyrillic (Windows 1251) для відображення української мови
    SetConsoleOutputCP(1251);

    sqlite3 *db;//підключення бази даних 
    int rc = sqlite3_open("database.db", &db);      
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Unable to open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    char sql[2566];
    sprintf(sql, "CREATE TABLE IF NOT EXISTS tickets(id INTEGER PRIMARY KEY,  film_name TEXT, customer_name TEXT, booking_date TEXT, seans TEXT, seats INTEGER, tuppl TEXT, price TEXT, paystatus TEXT);");// створення таблиці квитків
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);

    sprintf(sql, "CREATE TABLE IF NOT EXISTS films(id INTEGER PRIMARY KEY, name TEXT, age TEXT, country TEXT, genre TEXT, cast TEXT, duration TEXT, about TEXT CHECK(LENGTH(about) <= 1000), link TEXT);");// створення таблиці фільмів
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);


    while ( 1 ) {
        one:
        system("cls");
        printf("+----------------------------------------------------------------------------------------------------+\n");// меню програми
        printf("| K - додавання фільмів                          Меню:                                               |\n");
        printf("+----------------------------------------------------------------------------------------------------+\n");
        printf("|                                              Прем'єри - 1                                          |\n");
        printf("|                                             Мої квитки - 2                                         |\n");
        printf("|                                            Про програму - 3                                        |\n");
        printf("|                                               Вийти - 4                                            |\n");
        printf("+----------------------------------------------------------------------------------------------------+\n");
        printf("Вибір опції: ");
        char menu;
        scanf("%s", &menu);
        if(menu=='1') {//якщо введено 1 то вивід фільмів
            while( 1 ){
                prems:
                system("cls");
                printf("+------------------------------------------------------------------------+---------------+-----------+\n");// вибірка фільмів з бази даних id та name
                printf("|                                              Прем'єри:                 | Оберіть фільм |           |\n");
                printf("+------------------------------------------------------------------------+---------------+-----------+\n");
                sqlite3_stmt *stmt;
                rc = sqlite3_prepare_v2(db, "SELECT * FROM films;", -1, &stmt, 0);//Вивести всі фільми з бази даних films 
                int cols = sqlite3_column_count(stmt);
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    const unsigned char *id = sqlite3_column_text(stmt, 0);
                    char bymam[1000];
                    strcpy(bymam, reinterpret_cast<const char*>(id));
                    cool_design(bymam, 88);//вивід id фільма через функцію
                    const unsigned char *name = sqlite3_column_text(stmt, 1);
                    char bymam1[1000];
                    strcpy(bymam1, reinterpret_cast<const char*>(name));
                    cool_design(bymam1, 88);//вивід назви фільма через функцію
                };
                printf("|                                               Меню - w                                             |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                
                char name[256];
                const unsigned char *namef;
                printf("Вибір опції: ");
                scanf("%s", name);
                if (name[0] == 'W' || name[0] == 'w' || name[0] == 'Ц' || name[0] == 'ц'){//перехід в меню якщо введено w
                    goto one;
                }
                film:
                system("cls");
                sqlite3_stmt *pooping;
                char query[1000];
                 
                sprintf(query, "SELECT * FROM films WHERE id = %s;", name);// вивід повної інф по id

                rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                printf("+----------------------------------------------------------------------------------------------------+\n");//після вибору фільма з бази даних виводиться повна інформація про цей фільм, користувач може повернутися назад, або забронювати квиток на цей фільм
                while (sqlite3_step(pooping) == SQLITE_ROW) {
                    namef = sqlite3_column_text(pooping, 1);
                    char bymam2[1000];
                    strcpy(bymam2, reinterpret_cast<const char*>(namef));
                    cool_design(bymam2, 88);//вивід інформації про фільм в функції 
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
                    printf("|                       Прем'єри - w  | Забронювати квиток - e  |  Трейлер - t                       |\n");
                    printf("+----------------------------------------------------------------------------------------------------+\n");
                    printf("Вибір опції: ");
                    char book[100];
                    scanf("%s", &book);
                    if (book[0] == 'W'|| book[0] == 'w' || book[0] == 'Ц' || book[0] == 'ц'){//назад якщо введено w
                        goto prems;
                    }
                    if (book[0] == 'T'|| book[0] == 't' || book[0] == 'Е' || book[0] == 'е'){
                        ShellExecuteA(0, "open", bymam9, NULL, NULL, SW_SHOWDEFAULT);//відкриття трейлера фільма в браузері якщо введено t
                        goto film;
                    }
                    if (book[0] == 'E' || book[0] == 'e' || book[0] == 'У' || book[0] == 'у'){//процес бронювання якщо введено e
                        system("cls");
                        char customer_name[255];
                        printf("+----------------------------------------------------------------------------------------------------+\n");//введення в змінну customer_name прізвище та ім'я клієнта
                        printf("|                                    Введіть ваше прізвище та ім'я:     Відмінити бронювання - w     |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf(": ");
                        scanf("%i", &customer_name);
                        fgets(customer_name, 255, stdin);
                        if (customer_name[0] == 'W' || customer_name[0] == 'w' || customer_name[0] == 'Ц' || customer_name[0] == 'ц'){//відміна бронювання якщо введено w
                            goto prems;
                        }
                        else{
                            while( 1 ){
                                system("cls");
                                int booking_date;
                                printf("+----------------------------------------------------------------------------------------------------+\n");//введення в змінну booking_date дату сеанса
                                printf("|                                    Оберіть дату(введіть число 1-31):                               |\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("Введіть число: ");
                                scanf("%d", &booking_date);
                                getchar();//// Очистка буферу вводу щоб програма не зависала
                                if((0 < booking_date) && (booking_date < 32)){//вибір дати сеанса
                                    while( 1 ){
                                        roffflan:
                                        system("cls");
                                        char seans[100];
                                        char time[100];
                                        printf("+----------------------------------------------------------------------------------------------------+\n");//введення в змінну time час сеансу
                                        printf("|                               Оберіть сеанс:                         Відмінити бронювання - w      |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("|            10:40 - 1           19:30 - 4                                                           |\n");
                                        printf("|            12:40 - 2                                                                               |\n");
                                        printf("|            15:50 - 3                                                                               |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("Вибір опції: ");
                                        scanf("%s", &seans);
                                        if (seans[0] == 'W' || seans[0] == 'w' || seans[0] == 'Ц' || seans[0] == 'ц'){//відміна бронювання якщо введено w
                                            goto prems;
                                        }
                                        if(seans[0] == '1'){//варіанти сеансів
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
                                            goto roffflan;//якщо введено щось інше, то goto 
                                        }
                                    
                                        seats:
                                        system("cls");
                                        char seats[100];
                                        char tuppl[100];
                                        char price[100];
                                        char query[100];
                                        while( 1 ){
                                            system("cls");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");//вибір місця в кінотеатрі в змінні tuppl та price вносяться дані про тип місця та ціну в залежності від номеру місця
                                            printf("|                               Оберіть місце:     | Про Vip місця - v, Відмінити бронювання - w     |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("|                      Звичайне місце(1-90) - 130 грн, Vip місце(91-104) - 230грн                    |\n");
                                            printf("|                        ______________-------------------------______________                       |\n");
                                            printf("|           ____________(                        Екран                        )____________          |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("|             (  ( 1) ( 2) ( 3) ( 4) ( 5) ( 6) ( 7) ( 8) ( 9) (10) (11) (12) (13) (14)               |\n");
                                            printf("|            (   (15) (16) (17) (18) (19) (20) (21) (22) (23) (24) (25) (26) (27) (28)               |\n");
                                            printf("|           (    (29) (30) (31) (32) (33) (34) (35) (36) (37) (38) (39) (40) (41) (42)               |\n");
                                            printf("| Звичайні:(               (43) (44) (45) (46) (47) (48) (49) (50) (51) (52) (53) (54)               |\n");     
                                            printf("|           (              (55) (56) (57) (58) (59) (60) (61) (62) (63) (64) (65) (66)               |\n");
                                            printf("|            (             (67) (68) (69) (70) (71) (72) (73) (74) (75) (76) (77) (78)               |\n");
                                            printf("|             (            (79) (80) (81) (82) (83) (84) (85) (86) (87) (88) (89) (90)               |\n");
                                            printf("| Vip:    ( 91) ( 92) ( 93) ( 94) ( 95) ( 96) ( 97) ( 98) ( 99) (100) (101) (102) (103) (104)        |\n");
                                            printf("|                                                                                                    |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("Вибір опції: ");
                                            scanf("%s", &seats);
                                            char query[1000];
                                            sprintf(query, "SELECT COUNT(*) FROM tickets WHERE film_name = '%s' AND booking_date = '%d' AND seans = '%s' AND seats = '%s';", namef, booking_date, time, seats);//перевірка, чи не заброньований вже квиток на цю дату, в цей час, на цей фільм
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
                                                        printf("+----------------------------------------------------------------------------------------------------+\n");//якщо користувач хоче зайняти місце, але воно вже зайняте виводиться дане попереджеення
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                   Місце номер %s вже заброньоване                                  |\n", seats);                                                 
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("|                                                                                                    |\n");
                                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                                        printf("|                                              Назад - w                                             |\n");
                                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                                        printf("Вибір опції: ");
                                                        scanf("%s", &error2);
                                                        if (error2[0] == 'W' || error2[0] == 'w' || error2[0] == 'Ц' || error2[0] == 'ц'){//назад якщо введено w
                                                            goto seats;
                                                        }
                                                        else{
                                                            ;//якщо введено щось інше, то цикл починається наново
                                                        }
                                                    }
                                                }
                                            }

                                            if(strcmp(seats, "1") == 0 || strcmp(seats, "2") == 0 || strcmp(seats, "3") == 0 || strcmp(seats, "4") == 0 || strcmp(seats, "5") == 0 || strcmp(seats, "6") == 0 || strcmp(seats, "7") == 0 || strcmp(seats, "8") == 0 || strcmp(seats, "9") == 0 || strcmp(seats, "10") == 0 || strcmp(seats, "11") == 0 || strcmp(seats, "12") == 0 || strcmp(seats, "13") == 0 || strcmp(seats, "14") == 0 || strcmp(seats, "15") == 0 || strcmp(seats, "16") == 0 || strcmp(seats, "17") == 0 || strcmp(seats, "18") == 0 || strcmp(seats, "19") == 0 || strcmp(seats, "20") == 0 || strcmp(seats, "21") == 0 || strcmp(seats, "22") == 0 || strcmp(seats, "23") == 0 || strcmp(seats, "24") == 0 || strcmp(seats, "25") == 0 || strcmp(seats, "26") == 0 || strcmp(seats, "27") == 0 || strcmp(seats, "28") == 0 || strcmp(seats, "29") == 0 || strcmp(seats, "30") == 0 || strcmp(seats, "31") == 0 || strcmp(seats, "32") == 0 || strcmp(seats, "33") == 0 || strcmp(seats, "34") == 0 || strcmp(seats, "35") == 0 || strcmp(seats, "36") == 0 || strcmp(seats, "37") == 0 || strcmp(seats, "38") == 0 || strcmp(seats, "39") == 0 || strcmp(seats, "40") == 0 || strcmp(seats, "41") == 0 || strcmp(seats, "42") == 0 || strcmp(seats, "43") == 0 || strcmp(seats, "44") == 0 || strcmp(seats, "45") == 0 || strcmp(seats, "46") == 0 || strcmp(seats, "47") == 0 || strcmp(seats, "48") == 0 || strcmp(seats, "49") == 0 || strcmp(seats, "50") == 0 || strcmp(seats, "51") == 0 || strcmp(seats, "52") == 0 || strcmp(seats, "53") == 0 || strcmp(seats, "54") == 0 || strcmp(seats, "55") == 0 || strcmp(seats, "56") == 0 || strcmp(seats, "57") == 0 || strcmp(seats, "58") == 0 || strcmp(seats, "59") == 0 || strcmp(seats, "60") == 0 || strcmp(seats, "61") == 0 || strcmp(seats, "62") == 0 || strcmp(seats, "63") == 0 || strcmp(seats, "64") == 0 || strcmp(seats, "65") == 0 || strcmp(seats, "66") == 0 || strcmp(seats, "67") == 0 || strcmp(seats, "68") == 0 || strcmp(seats, "69") == 0 || strcmp(seats, "70") == 0 || strcmp(seats, "71") == 0 || strcmp(seats, "72") == 0 || strcmp(seats, "73") == 0 || strcmp(seats, "74") == 0 || strcmp(seats, "75") == 0 || strcmp(seats, "76") == 0 || strcmp(seats, "77") == 0 || strcmp(seats, "78") == 0 || strcmp(seats, "79") == 0 || strcmp(seats, "80") == 0 || strcmp(seats, "81") == 0 || strcmp(seats, "82") == 0 || strcmp(seats, "83") == 0 || strcmp(seats, "84") == 0 || strcmp(seats, "85") == 0 || strcmp(seats, "86") == 0 || strcmp(seats, "87") == 0 || strcmp(seats, "88") == 0 || strcmp(seats, "89") == 0 || strcmp(seats, "90") == 0){//якщо місце від 1 до 90, то в змінні вноситься місце яке обрав користувач, ціна, та тип місця.
                                                strncpy(tuppl, "звичайне", sizeof(tuppl));//внесення в зміну дані про тип місця та ціну квитка
                                                strncpy(price, "130 грн", sizeof(price));
                                                goto finish1;
                                            }
                                            if(strcmp(seats, "91")==0 || strcmp(seats, "92")==0 || strcmp(seats, "93")==0 || strcmp(seats, "94")==0 || strcmp(seats, "95")==0 || strcmp(seats, "96")==0 || strcmp(seats, "97")==0 || strcmp(seats, "98")==0 || strcmp(seats, "99")==0 || strcmp(seats, "100")==0 || strcmp(seats, "101")==0 || strcmp(seats, "102")==0 || strcmp(seats, "103")==0 || strcmp(seats, "103")==0){//якщо місце від 91 до 103, то в змінні вноситься місце яке обрав користувач, ціна, та тип місця.
                                                strncpy(tuppl, "Vip", sizeof(tuppl));//внесення в зміну дані про тип місця та ціну квитка
                                                strncpy(price, "230 грн", sizeof(price));
                                                goto finish1;
                                            }

                                            if (seats[0] == 'W' || seats[0] == 'w' || seats[0] == 'Ц' || seats[0] == 'ц'){//відміна бронювання якщо введено w
                                                goto prems;
                                            }
                                            if (seats[0] == 'V' || seats[0] == 'v' || seats[0] == 'М' || seats[0] == 'м'){//вивід описа місць якщо ввести v
                                                while ( 1 ){
                                                    system("cls");
                                                    char vip[100];
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");// опис Vip місць
                                                    printf("|                                           Про vip місця                       Вибір місця - w      |\n");
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("| Це комфортні шкіряні крісла з пультом керування, які змінюють положення вашого тіла до лежачого.   |\n");
                                                    printf("| Мають розкладну підставку для ніг та підлокітники, на яких легко розмістити найбільше відро        |\n");
                                                    printf("| попкорну та прохолодний напій, не заважаючи сусідові. Вибираючи VIP-місця для перегляду фільму у   |\n");
                                                    printf("| remove_the_cinema, ви відчуєте більше!                                                             |\n");
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("Вибір опції: ");
                                                    scanf("%s", &vip);
                                                    if  (vip[0] == 'W' || vip[0] == 'w' || vip[0] == 'Ц' || vip[0] == 'ц'){//повернення до вибору місць якщо введено w
                                                        goto seats;
                                                    }
                                                    else{
                                                        ;//якщо введено щось інше, то цикл починається наново
                                                    }

                                                }
                                            }
                                            else{
                                                ;//якщо введено щось інше, то цикл починається наново
                                            }
                                        }
                                        
                                        finish1:
                                        sprintf(sql, "insert into tickets(film_name, customer_name, booking_date, seans, seats, tuppl, price, paystatus) values('%s', '%s', '%d', '%s', '%s', '%s', '%s', 'не оплачено');", namef, customer_name, booking_date, time, seats, tuppl, price);//введення в базу даних квитків інформацію зі змінних яку ми отримали раніше
                                        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                                        while( 1 ){
                                            system("cls");
                                            char finish[100];
                                            printf("+----------------------------------------------------------------------------------------------------+\n");// завершення бронювання дані про цей квиток уже в базі даних і користувач може одразу перейди до квитків
                                            printf("|                                       Бронювання завершено!                    Меню - w            |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("|                                      Перейти до квитків - k                                        |\n");
                                            printf("|   Інформація по бронюванню:                                                                        |\n");
                                            cool_design(bymam2, 88);//вивід інформації про бронювання через функцію 
                                            cool_design(time, 88);
                                            cool_design(seats, 88);
                                            cool_design(tuppl, 88);
                                            cool_design(price, 88);
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("Вибір опції: ");
                                            scanf("%s", &finish);
                                            if  (finish[0] == 'W' || finish[0] == 'w' || finish[0] == 'Ц' || finish[0] == 'ц'){//перехід до меню 
                                                goto one;
                                            }
                                            if  (finish[0] == 'K' || finish[0] == 'k' || finish[0] == 'Л' || finish[0] == 'л'){//перехід до квитків
                                                goto tickets;
                                            }
                                            else{//щось інше, цикл починається наново
                                                ;
                                            }
                                        }   
                                    }
                                }
                                else{
                                    ;//якщо введено щось інше, то цикл починається наново
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
                printf("+------------------------------------------------------------------------+----------------+----------+\n");// вибірка квитків з бази даних (не повна інформація)
                printf("|                                                Квитки:                 | Оберіть квиток |          |\n");
                printf("+------------------------------------------------------------------------+----------------+----------+\n");
                sqlite3_stmt *ticket;
                rc = sqlite3_prepare_v2(db, "SELECT * FROM tickets;", -1, &ticket, 0);
                int cols = sqlite3_column_count(ticket);
                while (sqlite3_step(ticket) == SQLITE_ROW) {//вивід квитка з бази даних tickets 
                    const unsigned char *id = sqlite3_column_text(ticket, 0);
                    printf("|%s - ",id);
                    const unsigned char *film_name = sqlite3_column_text(ticket, 1);
                    printf("%s, ",film_name);
                    const unsigned char *customer_name = sqlite3_column_text(ticket, 2);
                    printf("%s",customer_name);
                    const unsigned char *price = sqlite3_column_text(ticket, 7);
                    printf("|%s, ",price);
                    const unsigned char *paystatus = sqlite3_column_text(ticket, 8);
                    printf("%s;\n",paystatus);
                };
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("|                                               Меню - w                                             |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                char tick[256];
                printf("Вибір опції: ");
                scanf("%s", tick);
                system("cls");
                if (tick[0] == 'W' || tick[0] == 'w' || tick[0] == 'Ц' || tick[0] == 'ц'){//меню якщо введено w
                    goto one;
                }
                sqlite3_stmt *pooping;
                char query[1000];
                 
                sprintf(query, "SELECT COUNT(*) FROM tickets WHERE id = %s;", tick);//перевірка існування білета
                rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                if (sqlite3_step(pooping) == SQLITE_ROW) {
                    int ticketCount = sqlite3_column_int(pooping, 0);
                    if (ticketCount == 0) {
                        while ( 1 ){
                            system("cls");
                            char error1[100];
                            printf("+----------------------------------------------------------------------------------------------------+\n");//якщо користувач вводить id квитка якого немає, то виводиться дана помилка
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                Квиток с ID %s не знайдено в базі даних.                             |\n", tick);                                                 
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("|                                              Назад - w                                             |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("Вибір опції: ");
                            scanf("%s", &error1);
                            if (error1[0] == 'W' || error1[0] == 'w' || error1[0] == 'Ц' || error1[0] == 'ц'){//назад якщо введено w
                                goto tickets;
                            }
                            else{
                                ;//якщо введено щось інше, то цикл починається наново
                            }
                        }
                    }
                    else {
                        sprintf(query, "SELECT * FROM tickets WHERE id = %s;", tick);

                        rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                        printf("+----------------------------------------------------------------------------------------------------+\n");// після вибору квитка виводиться повна інформація з бази даних про цей квиток 
                        while (sqlite3_step(pooping) == SQLITE_ROW) {
                            const unsigned char *id = sqlite3_column_text(pooping, 0);
                            printf("|%s - ", id);
                            const unsigned char *film_name = sqlite3_column_text(pooping, 1);
                            printf("%s, прізвище  та ім'я - ", film_name);
                            const unsigned char *customer_name = sqlite3_column_text(pooping, 2);
                            printf("%s|дата - ", customer_name);
                            const unsigned char *booking_date = sqlite3_column_text(pooping, 3);
                            printf("%s, сеанс - ", booking_date);
                            const unsigned char *seans = sqlite3_column_text(pooping, 4);
                            printf("%s, місце - ", seans);
                            const unsigned char *seats = sqlite3_column_text(pooping, 5);
                            printf("%s, тип місця - ", seats);
                            const unsigned char *tuppl = sqlite3_column_text(pooping, 6);
                            printf("%s, ціна - ", tuppl);
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
                        printf("+----------------------------------------------------------------------------------------------------+\n");//якщо користувач нажимає на рандомні клавіші і вводе їх, то виводиться дана помилка
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                    Помилка при виконанні запиту...                                 |\n", tick);                                                 
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("|                                              Назад - w                                             |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("Вибір опції: ");
                        scanf("%s", &error2);
                        if (error2[0] == 'W' || error2[0] == 'w' || error2[0] == 'Ц' || error2[0] == 'ц'){//назад якщо введено w
                            goto tickets;
                        }
                        else{
                            ;//якщо введено щось інше, то цикл починається наново
                        }
                    }
                }
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("|                       Квитки - w  | Сплатити квиток - e | Відмінити бронювання - r                 |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("Вибір опції: ");
                char book[100];
                scanf("%s", &book);
                if (book[0] == 'W' || book[0] == 'w' || book[0] == 'Ц' || book[0] == 'ц'){//квитки якщо введено w
                    goto tickets;
                }
                if (book[0] == 'E' || book[0] == 'e' || book[0] == 'У' || book[0] == 'у'){//оплата квитка якщо введено e
                    while( 1 ){
                        system("cls");
                        char pay[100];
                        sprintf(sql, "SELECT paystatus FROM tickets WHERE id = '%s';", tick);
                        rc = sqlite3_exec(db, sql, callback_function, &pay, NULL); // тут callback_function - функція отримує значення стовпця paystatus і зберігає його в змінній pay
                        if (strcmp(pay, "оплачено") == 0) {
                            printf("+----------------------------------------------------------------------------------------------------+\n");// якщо квиток був оплачений раніше
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                    Квиток був оплачений раніше!                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("|                                              Назад - w                                             |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("Вибір опції: ");
                            scanf("%s", &pay);
                            if (pay[0] == 'W' || pay[0] == 'w' || pay[0] == 'Ц' || pay[0] == 'ц') {
                                goto tickets;
                            }
                            else{
                                ;//якщо введено щось інше, то цикл починається наново
                            }
                        } else {
                            sprintf(sql, "UPDATE tickets SET paystatus = 'оплачено' WHERE id = '%s';", tick);
                            rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                            printf("+----------------------------------------------------------------------------------------------------+\n");//оплата квитка
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                             Оплачено!!!                                            |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("|                                                                                                    |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("|                                              Назад - w                                             |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("Вибір опції: ");
                            scanf("%s", &pay);
                            if (pay[0] == 'W' || pay[0] == 'w' || pay[0] == 'Ц' || pay[0] == 'ц') {//назад якщо введено w
                                goto tickets;
                            }
                            else{
                                ;//якщо введено щось інше, то цикл починається наново
                            }
                        }
                    }
                }
                if (book[0] == 'К' || book[0] == 'к' || book[0] == 'R' || book[0] == 'r'){//відміна бронювання якщо введено r
                    while( 1 ){
                        system("cls");
                        char pay1[100];
                        sprintf(sql, "DELETE FROM tickets WHERE id = '%s';", tick);
                        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                        printf("+----------------------------------------------------------------------------------------------------+\n");// відміна бронювання
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                        Бронювання відмінилося!!!                                   |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("|                                                                                                    |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("|                                              Назад - w                                             |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("Вибір опції: ");
                        scanf("%s", &pay1);
                        if (pay1[0] == 'W' || pay1[0] == 'w' || pay1[0] == 'Ц' || pay1[0] == 'ц'){//назад якщо введено w
                            goto tickets;
                        }
                        else{
                            ;//якщо введено щось інше, то цикл починається наново
                        }
                    }
                }
            }
        }


        if(menu=='3') {// інформація про программу якщо введено 3
            char about[100];
            while( 1 ){
                system("cls");
                printf("+---------------------------------------------------------------------+-----------------------+------+\n");// інформація про программу для користувача
                printf("| Version 1.0 release                        Про програму:            |developer - Andrew165#1|      |\n");
                printf("+---------------------------------------------------------------------+-----------------------+------+\n");
                printf("| Привіт! Ласкаво просимо до програми по продажу квитків в кінотеатрі! Завдяки нашому сервісу ви     |\n");
                printf("| зможете придбати квитки на сеанси у кінотеатрі швидко та зручно.                                   |\n");
                printf("| Наша програма має дуже простий та зрозумілий інтерфейс. Все, що вам потрібно зробити, це вибрати   |\n");
                printf("| фільм, на який ви хочете піти, вказати прізвище та ім'я, вибрати зручний для вас сеанс та          |\n");
                printf("| забронювати квиток, помім в “Мої квитки” оплатити квиток. Ви також можете відмінити бронювання, але|\n");
                printf("| якщо ви вже оплатили гроші ми вам не повернемо.                                                    |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("|                                              Меню - w                                              |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("Вибір опції: ");
                scanf("%s", &about);
                if(about[0] == 'W' || about[0] == 'w' || about[0] == 'Ц' || about[0] == 'ц'){//назад якщо введено w
                    goto one;
                }
                else{
                    ;
                }
            }
        }








        if(menu == 'K' || menu == 'k' || menu == 'Л' || menu == 'л') {
            konnstr1:
            system("cls");
            char konstr[100];
            printf("+----------------------------------------------------------------------------------------------------+\n");// конструктор фільмів
            printf("|   Додати фільм - e                                                                                 |\n");
            printf("|   Видалити фільм - d                                                                               |\n");
            printf("+----------------------------------------------------------------------------------------------------+\n");
            printf("|                                              Назад - w                                             |\n");
            printf("+----------------------------------------------------------------------------------------------------+\n");
            printf("Вибір опції: ");
            scanf("%s", &konstr);
            if(konstr[0] == 'W' || konstr[0] == 'w' || konstr[0] == 'Ц' || konstr[0] == 'ц'){//назад якщо введено w
                goto one;
            }

            if(konstr[0] == 'E' || konstr[0] == 'e' || konstr[0] == 'У' || konstr[0] == 'у'){
                konnstr2:
                system("cls");
                char intfilm1[100];
                printf("+----------------------------------------------------------------------------------------------------+\n");// введення назви фільму в змінну
                printf("| Назад - w, не виходить введіть ww     Введіть назву фільму:                                        |\n");
                printf("+----------------------------------------------------------------------------------------------------+\n");
                printf("Введіть дані: ");
                getchar();
                fgets(intfilm1, 255, stdin);
                int len = strcspn(intfilm1, "\n"); 
                intfilm1[len] = '\0';
                if(intfilm1[0] == 'W' || intfilm1[0] == 'w' || intfilm1[0] == 'Ц' || intfilm1[0] == 'ц'){//назад якщо введено w
                    goto konnstr1;
                }
                else{
                    konnstr3:
                    system("cls");
                    char intfilm2[100];
                    printf("+----------------------------------------------------------------------------------------------------+\n");//введення вікового рейтинга фільма в змінну
                    printf("| Назад - w       Введіть віковий рейтинг фільму(у форматі: Вікові обмеження - 18+):                 |\n");
                    printf("+----------------------------------------------------------------------------------------------------+\n");
                    printf("Введіть дані: ");
                    fgets(intfilm2, 255, stdin);
                    int len = strcspn(intfilm2, "\n"); 
                    intfilm2[len] = '\0';
                    if(intfilm2[0] == 'W' || intfilm2[0] == 'w' || intfilm2[0] == 'Ц' || intfilm2[0] == 'ц'){//назад якщо введено w
                        goto konnstr2;
                    }
                    else{
                        konnstr4:
                        system("cls");
                        char intfilm3[100];
                        printf("+----------------------------------------------------------------------------------------------------+\n");// введення країни виробника фільма в змінну
                        printf("| Назад - w            Введіть країну виробника фільма(у форматі: Країна - США):                     |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("Введіть дані: ");
                        fgets(intfilm3, 255, stdin);
                        int len = strcspn(intfilm3, "\n"); 
                        intfilm3[len] = '\0';
                        if(intfilm3[0] == 'W' || intfilm3[0] == 'w' || intfilm3[0] == 'Ц' || intfilm3[0] == 'ц'){//назад якщо введено w
                            goto konnstr3;
                        }
                        else{
                            konnstr5:
                            system("cls");
                            char intfilm4[100];
                            printf("+----------------------------------------------------------------------------------------------------+\n");// введення жанра фільма в змінну
                            printf("| Назад - w            Введіть жанр фільма(у форматі: Жанр - Екшн, Фантастика):                      |\n");
                            printf("+----------------------------------------------------------------------------------------------------+\n");
                            printf("Введіть дані: ");
                            fgets(intfilm4, 255, stdin);
                            int len = strcspn(intfilm4, "\n"); 
                            intfilm4[len] = '\0';
                            if(intfilm4[0] == 'W' || intfilm4[0] == 'w' || intfilm4[0] == 'Ц' || intfilm4[0] == 'ц'){//назад якщо введено w
                                goto konnstr4;
                            }
                            else{
                                konnstr6:
                                system("cls");
                                char intfilm5[100];
                                printf("+----------------------------------------------------------------------------------------------------+\n");// введення головних акторів фільма в змінну
                                printf("| Назад - w  Введіть головних акторів фільма(у форматі: У головних ролях: Кріс Пратт, Зої Салдана...)|\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("Введіть дані: ");
                                fgets(intfilm5, 255, stdin);
                                int len = strcspn(intfilm5, "\n"); 
                                intfilm5[len] = '\0';
                                if(intfilm5[0] == 'W' || intfilm5[0] == 'w' || intfilm5[0] == 'Ц' || intfilm5[0] == 'ц'){//назад якщо введено w
                                    goto konnstr5;
                                }
                                else{
                                    konnstr7:
                                    system("cls");
                                    char intfilm6[100];
                                    printf("+----------------------------------------------------------------------------------------------------+\n");// введення тривалості фільма в змінну
                                    printf("| Назад - w        Введіть тривалість фільма(у форматі: Тривалість - 2:29 149 хв)                    |\n");
                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                    printf("Введіть дані: ");
                                    fgets(intfilm6, 255, stdin);
                                    int len = strcspn(intfilm6, "\n"); 
                                    intfilm6[len] = '\0';
                                    if(intfilm6[0] == 'W' || intfilm6[0] == 'w' || intfilm6[0] == 'Ц' || intfilm6[0] == 'ц'){//назад якщо введено w
                                        goto konnstr6;
                                    }
                                    else{
                                        konnstr8:
                                        system("cls");
                                        char intfilm7[100];
                                        printf("+----------------------------------------------------------------------------------------------------+\n");// введення опис фільма в змінну
                                        printf("| Назад - w                 Введіть опис фільма(у форматі: Опис фільму:...)                          |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("Введіть дані: ");
                                        fgets(intfilm7, 255, stdin);
                                        int len = strcspn(intfilm7, "\n"); 
                                        intfilm7[len] = '\0';
                                        if(intfilm7[0] == 'W' || intfilm7[0] == 'w' || intfilm7[0] == 'Ц' || intfilm7[0] == 'ц'){//назад якщо введено w
                                            goto konnstr7;
                                        }
                                        else{
                                            konnstr9:
                                            system("cls");
                                            char intfilm8[100];
                                            printf("+----------------------------------------------------------------------------------------------------+\n");// введення посилання на трейлер в змінну
                                            printf("| Назад - w                            Введіть посилання на трейлер:                                 |\n");
                                            printf("+----------------------------------------------------------------------------------------------------+\n");
                                            printf("Введіть дані: ");
                                            fgets(intfilm8, 255, stdin);
                                            int len = strcspn(intfilm8, "\n"); 
                                            intfilm8[len] = '\0';
                                            if(intfilm8[0] == 'W' || intfilm8[0] == 'w' || intfilm8[0] == 'Ц' || intfilm8[0] == 'ц'){//назад якщо введено w
                                                goto konnstr8;
                                            }
                                            else{
                                                sprintf(sql, "insert into films(name, age, country, genre, cast, duration, about, link) values('%s', '%s', '%d', '%s', '%s', '%s', '%s', '%s');", intfilm1, intfilm2, intfilm3, intfilm4, intfilm5, intfilm6, intfilm7, intfilm8);//введення в базу даних фільмів новий фільм інформацію про який ми отримали раніше зі змінних
                                                rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                                                while( 1 ){
                                                    system("cls");
                                                    char finishkon[100];
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");// завершення додавання нового фільму
                                                    printf("| Меню - w                           Додавання фільму завершено!                                     |\n");
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("|   Інформація про фільм який ви додали:                                                             |\n");
                                                    cool_design(intfilm1, 88);
                                                    cool_design(intfilm2, 88);
                                                    cool_design(intfilm3, 88);
                                                    cool_design(intfilm4, 88);
                                                    cool_design(intfilm5, 88);
                                                    cool_design(intfilm6, 88);
                                                    cool_design(intfilm7, 88);
                                                    cool_design(intfilm8, 88);
                                                    printf("+----------------------------------------------------------------------------------------------------+\n");
                                                    printf("Вибір опції: ");
                                                    scanf("%s", &finishkon);
                                                    if(finishkon[0] == 'W' || finishkon[0] == 'w' || finishkon[0] == 'Ц' || finishkon[0] == 'ц'){//меню якщо введено w
                                                        goto one;
                                                    }
                                                    else{
                                                        ;//якщо введено щось інше, то цикл починається наново
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





            if(konstr[0] == 'D' || konstr[0] == 'd' || konstr[0] == 'В' || konstr[0] == 'в'){//вивід всіх фільмів для видалення якщо введено d
                ddd:
                while( 1 ){
                    system("cls");
                    printf("+---------------------------------------------------------------------+----------------------------+-+\n");// видалення фільмів з бази даних
                    printf("|                                              Прем'єри:              | Оберіть фільм для видалення| |\n");
                    printf("+---------------------------------------------------------------------+----------------------------+-+\n");
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "SELECT * FROM films;", -1, &stmt, 0);// вивід всіх фільмів
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
                    printf("|                                              Назад - w                                             |\n");
                    printf("+----------------------------------------------------------------------------------------------------+\n");
                    
                    char name12[256];
                    const unsigned char *namef;
                    printf("Вибір опції: ");
                    scanf("%s", name12);
                    system("cls");
                    if (name12[0] == 'W' || name12[0] == 'w' || name12[0] == 'Ц' || name12[0] == 'ц'){//назад якщо введено w
                        goto konnstr1;
                    }
                    caca:
                    system("cls");
                    sqlite3_stmt *pooping;
                    char query[1000];
                     
                    sprintf(query, "SELECT * FROM films WHERE id = %s;", name12);

                    rc = sqlite3_prepare_v2(db, query, -1, &pooping, NULL);
                    printf("+----------------------------------------------------------------------------------------------------+\n");//вивід інформації про фільм який ми хочемо видалити
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
                        printf("|                                    Назад - w  | Видалити фільм - r                                 |\n");
                        printf("+----------------------------------------------------------------------------------------------------+\n");
                        printf("Вибір опції: ");
                        char book12[100];
                        scanf("%s", &book12);
                        if (book12[0] == 'W'|| book12[0] == 'w' || book12[0] == 'Ц' || book12[0] == 'ц'){//назад якщо введено w
                            goto ddd;
                        }
                        if (book12[0] == 'R'|| book12[0] == 'r' || book12[0] == 'К' || book12[0] == 'к'){//видалення фільму якщо введено r
                            while ( 1 ){
                                system("cls");
                                char yes[100];
                                printf("+----------------------------------------------------------------------------------------------------+\n");// попередження про видалення фільму
                                printf("|                                                                                                    |\n");
                                printf("|              Всі дані про цей фільм буде видалено, щоб підтвердити видалення введіть Y             |\n");
                                printf("|                                                                                                    |\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("|                                        Відмінити видалення - w                                     |\n");
                                printf("+----------------------------------------------------------------------------------------------------+\n");
                                printf("Введіть дані: ");
                                scanf("%s", &yes);
                                if (yes[0] == 'W'|| yes[0] == 'w' || yes[0] == 'Ц' || yes[0] == 'ц'){//відміна бронювання якщо введено w
                                    goto caca;
                                }
                                if (yes[0] == 'Y'|| yes[0] == 'y' || yes[0] == 'Н' || yes[0] == 'н'){//видалення фільму якщо введено y
                                    while( 1 ){
                                        system("cls");
                                        char remove1[100];
                                        sprintf(sql, "DELETE FROM films WHERE id = '%s';", name12);//видалення фільму по обраному id
                                        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                                        printf("+----------------------------------------------------------------------------------------------------+\n");// видалення фільму
                                        printf("|                                                                                                    |\n");
                                        printf("|                                         Фільм видалено!!!                                          |\n");
                                        printf("|                                                                                                    |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("|                                              Меню - w                                              |\n");
                                        printf("+----------------------------------------------------------------------------------------------------+\n");
                                        printf("Вибір опції: ");
                                        scanf("%s", &remove1);
                                        if (remove1[0] == 'W' || remove1[0] == 'w' || remove1[0] == 'Ц' || remove1[0] == 'ц'){//меню якщо введено w
                                            goto one;
                                        }
                                        else{
                                            ;//якщо введено щось інше, то цикл починається наново
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
            printf("Вихід.\n");//вихід з програми
            break;
        }
        else{
            ;
        }

    }
    return 0;   
}
