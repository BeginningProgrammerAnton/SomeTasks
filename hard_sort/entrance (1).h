#pragma once

#include <stdexcept>
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

struct StudentName {
    std::string name, surname;
};

struct Date {
    int year, month, day;
};
struct Students {
    StudentName studentName;
    Date date;
    int numball;
    std::vector<std::string> prefer;
};

bool Cmp1(Students s1, Students s2) {
    if (s1.numball != s2.numball) {
        return s1.numball > s2.numball;
    }
    if (s1.date.year != s2.date.year) {
        return s1.date.year < s2.date.year;
    }
    if (s1.date.month != s2.date.month) {
        return s1.date.month < s2.date.month;
    }
    if (s1.date.day != s2.date.day) {
        return s1.date.day < s2.date.day;
    }
    if (s1.studentName.surname != s2.studentName.surname) {
        return s1.studentName.surname < s2.studentName.surname;
    }
    if (s1.studentName.name != s2.studentName.name) {
        return s1.studentName.name < s2.studentName.name;
    }
    return false;
}

bool Cmp2(Students st1, Students st2) {
    if (st1.studentName.surname != st2.studentName.surname) {
        return st1.studentName.surname < st2.studentName.surname;
    }
    if (st1.studentName.name != st2.studentName.name) {
        return st1.studentName.name < st2.studentName.name;
    }
    if (st1.date.year != st2.date.year) {
        return st1.date.year < st2.date.year;
    }
    if (st1.date.month != st2.date.month) {
        return st1.date.month < st2.date.month;
    }
    if (st1.date.day != st2.date.day) {
        return st1.date.day < st2.date.day;
    }
    return false;
}

std::map<std::string, std::vector<StudentName>> GetStudents(
    const std::vector<std::pair<std::string, int>>& university_info,
    const std::vector<std::tuple<StudentName, Date, int, std::vector<std::string>>>&
        students_info) {
    std::map<std::string, std::vector<StudentName>> mappy;
    std::vector<std::pair<Students, std::string>> vec1;
    std::vector<Students> vec_st;
    std::vector<Students> vec_st_nm;
    std::vector<StudentName> vec_st_nm2;
    std::map<std::string, int> my_univers;
    std::map<std::string, std::vector<Students>> my_univers_st;
    for (size_t i = 0; i < students_info.size(); ++i) {
        Students students;
        students.studentName = std::get<0>(students_info[i]);
        students.date = std::get<1>(students_info[i]);
        students.numball = std::get<2>(students_info[i]);
        students.prefer = std::get<3>(students_info[i]);
        vec_st.emplace_back(students);
    }
    std::sort(vec_st.begin(), vec_st.end(), Cmp1);
    for (auto x : university_info) {
        my_univers.insert({x.first, x.second});
        my_univers_st.insert({x.first, {}});
        mappy.insert({x.first, {}});
    }
    for (auto x : vec_st) {
        for (auto y : x.prefer) {
            if (my_univers[y]) {
                my_univers[y]--;
                my_univers_st[y].push_back(x);
                break;
            }
        }
    }
    for (auto& [x, x_students] : my_univers_st) {
        std::sort(x_students.begin(), x_students.end(), Cmp2);
    }
    for (auto& [x, x_students] : my_univers_st) {
        for (auto y : x_students) {
            mappy[x].push_back(y.studentName);
        }
    }
    return mappy;
}
