#include <iostream>
#include <map>
#include <vector>

#include "SStudData.h"

int main() {
  // Чтение данных из файла
  std::vector<SStudData> students = SStudData::readFromFile("Data.txt");

  // Вывод списка студентов
  std::cout << "Исходный список студентов:\n";
  std::cout << students;

  // Сортировка студентов
  SStudData::sortStudents(students);
  std::cout << "\n-----------------------------------------------\n";
  std::cout << "Отсортированный список студентов:\n";
  std::cout << students;

  // Формирование карты студентов по ID
  std::map<int, SStudData> studentMap = SStudData::formMap(students);
  std::cout << "\n-----------------------------------------------\n";
  std::cout << "Карта студентов (ID -> Student):\n";
  for (const auto &pair : studentMap) {
    std::cout << "ID: " << pair.first << ", Student: " << pair.second << "\n";
  }

  // Поиск студента с максимальной общей оценкой
  try {
    SStudData maxTotalScoreStudent =
        SStudData::findMaxTotalScoreStudent(studentMap);
    std::cout << "\n-----------------------------------------------\n";
    std::cout << "Студент с максимальной общей оценкой:\n";
    std::cout << maxTotalScoreStudent;
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
  }

  // Поиск студентов без неудовлетворительных оценок
  std::vector<SStudData> studentsWithoutFailures =
      SStudData::findStudentsWithoutFailures(studentMap);
  std::cout << "\n-----------------------------------------------\n";
  std::cout << "Студенты без неудовлетворительных оценок:\n";
  for (const auto &student : studentsWithoutFailures) {
    std::cout << student << "\n";
  }

  // Вычисление среднего балла для каждого студента
  std::cout << "\n-----------------------------------------------\n";
  std::cout << "Средний балл для каждого студента:\n";
  for (const auto &student : students) {
    std::cout << "ID: " << student.getID() << ", Name: " << student.getName()
              << ", Average Score: " << student.calculateAverageScore() << "\n";
  }

  // Вывод списка студентов в формате "Фамилия Средний Балл ID", отсортированный
  // по фамилии и среднему баллу
  std::cout << "\n-----------------------------------------------\n";
  std::cout << "Список студентов в формате 'Фамилия Средний Балл ID':\n";
  SStudData::printSortedStudents(studentMap);

  // Поиск и вывод студентов, средний балл которых находится в заданном
  // диапазоне
  double minScore = 3.0;
  double maxScore = 4.5;
  std::cout << "\n-----------------------------------------------\n";
  SStudData::printStudentsInScoreRange(studentMap, minScore, maxScore);

  // Поиск и вывод студентов, которые сдавали указанный предмет
  std::string subject = "Math";
  std::cout << "\n-----------------------------------------------\n";
  SStudData::printStudentsBySubject(studentMap, subject);

  // Подсчет и вывод количества студентов, сдававших каждый предмет
  std::map<std::string, int> subjectCount =
      SStudData::countStudentsPerSubject(studentMap);
  std::cout << "\n-----------------------------------------------\n";
  std::cout << "Количество студентов, сдававших каждый предмет:\n";
  for (const auto &pair : subjectCount) {
    std::cout << "Subject: " << pair.first << ", Count: " << pair.second
              << "\n";
  }

  return 0;
}