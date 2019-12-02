#include "additionals.h"


int get_date(char* result){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string new_result;
    std::string date = std::to_string(ltm->tm_mday);
    std::string month = std::to_string(ltm->tm_mon);
    new_result += (date.length() < 2 ? "0" : "") + date + "-" +
            (month.length() < 2 ? "0" : "") + month + "-" + std::to_string(ltm->tm_year);
    strncpy (result, new_result.c_str(), 10);
    result[10] = '\0';
    return EXIT_SUCCESS;
}

int get_time(char* result){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string new_result;
    std::string hour = std::to_string(ltm->tm_hour);
    std::string minute = std::to_string(ltm->tm_min);
    std::string second = std::to_string(ltm->tm_sec);
    new_result += (hour.length() < 2 ? "0" : "") + hour + ":" +
                  (minute.length() < 2 ? "0" : "") + minute + ":" +
                  (second.length() < 2 ? "0" : "") + second;
    strncpy (result, new_result.c_str(), 8);
    result[8] = '\0';
    return EXIT_SUCCESS;
}

int get_greetings(char* result){
    strncpy (result, "Hello world!", 12);
    result[12] = '\0';
    return EXIT_SUCCESS;
}

int count_words(char* result){
    int number_of_words = 0;
    bool word = false;
    for (int i = 0; i < strlen(result); i++){
        if (isalpha(result[i])){
            if (!word) {
                number_of_words++;
                word = true;
            }
        } else{
            word = false;
        }
    }
    std::string str_number = std::to_string(number_of_words);
    strncpy (result, str_number.c_str(), str_number.length());
    result[str_number.length()] = '\0';
    return EXIT_SUCCESS;
}