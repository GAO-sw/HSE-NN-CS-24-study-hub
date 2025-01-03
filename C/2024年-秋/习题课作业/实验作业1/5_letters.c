//检查用户输入得字符串1)是否为5个 2)是否全部为字母
//Проверить, является ли введенная пользователем строка 1) состоящей из 5 символов 2) содержащей только буквы
int check_char(char target[]) {
    if (strlen(target) != 5) {
        return 0;  // 输入的字符数量不是 5
                  // Введено не 5 символов
    }
    for (int i = 0; i < 5; i++) {
        if (!((target[i] >= 'A' && target[i] <= 'Z') || (target[i] >= 'a' && target[i] <= 'z'))) {
            return 1;  // 存在非字母字符
                      // Присутствуют небуквенные символы
        }
    }
    return 2;  // 符合要求
               // Соответствует требованиям
}

//比较player1 和 player2 输入的字符串并用matched数组记录，符合条件的字符
//Сравнить строки player1 и player2 и записать совпадающие символы в массив matched
void compare_char(char target[], char attempt[], int message[]) {
    int matched[5] = {0};  //matched记录目标字符串中的字符是否已经被匹配过
                          //matched записывает, были ли уже сопоставлены символы в целевой строке
    for (int i = 0; i < 5; i++) {
        if (target[i] == attempt[i]) {
            message[i] = 1; // 标记相同位置且相同字符的下标为1
                           // Отметить индекс как 1 для одинаковых символов в одинаковых позициях
            matched[i] = 1;  
        } else {
            int found = 0;
            for (int j = 0; j < 5; j++) {
                if (j != i && !matched[j] && target[j] == attempt[i]) {
                    found = 1;
                    matched[j] = 1;  
                    break;
                }
            }
            message[i] = found ? 2 : 0; // 不同位置同字符标记为2；未出现标记为0
                                       // Отметить 2 для одинаковых символов в разных позициях; 0 для отсутствующих
        }
    }
}

//清空输入缓冲区
//Очистить буфер ввода
void clear_input_buffer() {
    int x;
    while ((x = getchar()) != '\n' && x != EOF);
}

int main() {
    char target[6];  //存储出题者player1输入的题目字符串
                     //Хранить целевую строку, введенную player1
    int num_win = 0;  //答题者player2 获胜的次数
                      //Количество побед player2
    int num_lost = 0; //答题者player2 失败的次数
                      //Количество поражений player2
    int total_attempts = 0;  // player2 的尝试总数
                            // Общее количество попыток player2
    int average_attempts = 0; //player2 每局游戏的平均尝试次数
                             //Среднее количество попыток player2 за игру

    while (1) {
        printf("Player 1, please input 5 letters:\n");

        while (1) {
            scanf("%5s", target);   
            clear_input_buffer();  // 清空输入缓冲区
                                  // Очистить буфер ввода

            int result_1 = check_char(target);  //根据检查输入的字符串的结果，给出下一步提示
                                               //На основе результата проверки строки выдать следующую подсказку
            if (result_1 == 0) {
                printf("Player 1 inputted more or less than 5 valid characters, please input 5 letters.\n");
            } else if (result_1 == 1) {
                printf("Player 1 contains non-letter characters, please input 5 letters.\n");
            } else if (result_1 == 2) {
                printf("Player 1 has inputted 5 letters. Now it's Player 2's turn.\n");
                break;  // 输入符合要求，退出循环
                       // Ввод соответствует требованиям, выйти из цикла
            }
        }

        char attempt[6];  //存储答题者player2 每次尝试的字符串
                         //Хранить строку каждой попытки player2
        int message[5];   //记录出题者player1和答题者player2的字符串比较结果
                         //Записывать результаты сравнения строк player1 и player2
        int count;   //记录相同位置相同字符的次数，达到5次即胜利
                    //Подсчитывать количество одинаковых символов в одинаковых позициях, победа при достижении 5
        int win = 0;  //标记符号用来打印是否赢得游戏
                      //Флаг для отображения результата игры

        char difficulty[10];   //存储难度选择的选项
                              //Хранить выбранный уровень сложности
        int times;    //记录不同难度下可以尝试的次数
                     //Записывать количество доступных попыток в зависимости от сложности

        // 选择难度。简答模式6次，困难模式4次
        // Выбор сложности. Легкий режим - 6 попыток, сложный режим - 4 попытки
        while (1) {
            printf("Player 2, please choose difficulty: easy or hard:\n");
            scanf("%s", difficulty);
            clear_input_buffer();  // 清空输入缓冲区
                                  // Очистить буфер ввода

            if (strcmp(difficulty, "easy") == 0) {
                times = 6;
                printf("You have 6 attempts to guess.\n");
                break;
            } else if (strcmp(difficulty, "hard") == 0) {
                times = 4;
                printf("You have 4 attempts to guess.\n");
                break;
            } else {
                printf("Invalid input. Please input 'easy' or 'hard'.\n");
            }
        }

        // 玩家 2 尝试猜测
        // Попытки угадывания Player 2
        int attempts_used = 0;  //单次循环中的尝试次数
                               //Количество использованных попыток в текущем цикле
        for (int i = times; i > 0; i--) {
            count = 0;  // 每次新尝试前重置 count
                       // Сбросить count перед каждой новой попыткой
            printf("Player 2, please input 5 letters\n");
            scanf("%5s", attempt);
            clear_input_buffer();  // 清空输入缓冲区
                                  // Очистить буфер ввода
            attempts_used++;  // 记录使用的尝试次数
                            // Записать количество использованных попыток

            //判断答题者Player 2 的输入是否合规，若合规则无打印继续游戏，若不合规则给出提出并要求重新开始循环并输入直到合规为止
            //Проверить правильность ввода Player 2, если правильно - продолжить игру без вывода, если неправильно - вывести подсказку и начать цикл заново
            int result_2 = check_char(attempt);
            if (result_2 == 0) {
                printf("Player 2 inputted more or less than 5 characters, please input 5 letters.\n");
                continue;
            } else if (result_2 == 1) {
                printf("Player 2 inputted non-letter characters, please input 5 letters.\n");
                continue;
            }

            //开始比较字符串
            //Начать сравнение строк
            compare_char(target, attempt, message);
            for (int j = 0; j < 5; j++) {
                if (message[j] == 1) {
                    printf("The letter No.%d is on the right position; ", j + 1);
                    count++;
                } else if (message[j] == 2) {
                    printf("The letter No.%d exists in the target, but not on the right position; ", j + 1);
                }
            }
            printf("\n");

            if (count == 5) {
                win = 1;
                break;
            }
            printf("Player 2 has %d attempts left!\n", i - 1);
        }

        // 判断玩家 2 的胜利或失败情况
        // Определить результат игры Player 2 (победа или поражение)
        if (win == 1) {
            printf("Player 2 won the game!!!\n");
            num_win++;
        } else {
            printf("Player 2 lost! The answer is %s\n", target);
            num_lost++;
        }

        // 更新总尝试次数
        // Обновить общее количество попыток
        total_attempts += attempts_used;

        // 计算平均尝试次数
        // Вычислить среднее количество попыток
        if ((num_lost + num_win) > 0) {
            average_attempts = total_attempts / (num_lost + num_win);
        }

        // 输出总的胜利和失败次数
        // Вывести общее количество побед и поражений
        printf("Total wins: %d\n", num_win);
        printf("Total losses: %d\n", num_lost);
        printf("Average attempts: %d\n", average_attempts);

        // 询问是否继续游戏
        // Спросить о продолжении игры
        char continue_game[10];
        printf("Do you want to play again? (yes/no):\n");
        scanf("%s", continue_game);
        clear_input_buffer();

        if (strcmp(continue_game, "no") == 0) {
            break;
        }
    }

    return 0;
}