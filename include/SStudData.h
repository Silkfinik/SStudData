#ifndef SSTUDDATA_H
#define SSTUDDATA_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

// Structure to hold the subject and mark
struct SMark {
  std::string Subject;  // предмет
  int Mark;             // оценка

  // Constructor
  SMark(const std::string &subject, int mark);
};

// Class to hold the student data
class SStudData {
  std::string Name;  // фамилия
  int ID;            // номер зачетки
  std::vector<SMark> Marks;  // рез-ты сессии - пустой на момент создания

 public:
  // Constructor
  SStudData(const std::string &name, int id);
  SStudData() = default;

  // Method to add a mark
  void addMark(const SMark &mark);

  // Get-methods
  std::string getName() const;
  int getID() const;
  std::vector<SMark> getMarks() const;

  // Overload assignment operator
  SStudData &operator=(const SStudData &other);

  // Overload << operator for output
  friend std::ostream &operator<<(std::ostream &out, const SStudData &data);

  // Read data from a text file and form a vector of SStudData objects
  static std::vector<SStudData> readFromFile(const std::string &filename);

  // Sort SStudData objects by two criteria: descending by last name, then
  // ascending by ID
  static void sortStudents(std::vector<SStudData> &students);

  // Form a map<int, SStudData> from the vector, with the key being the student
  // ID
  static std::map<int, SStudData> formMap(
      const std::vector<SStudData> &students);

  // Find the student with the maximum total score
  static SStudData findMaxTotalScoreStudent(
      const std::map<int, SStudData> &studentMap);

  // Find all students who didn't fail any subject (no grade 2)
  static std::vector<SStudData> findStudentsWithoutFailures(
      const std::map<int, SStudData> &studentMap);

  // Calculate the average score for each student
  double calculateAverageScore() const;

  // Check if the student has taken a specific subject
  bool hasSubject(const std::string &subject) const;

  // Output the list of students in the format "Last Name Average Score ID"
  // sorted by last name and average score
  static void printSortedStudents(const std::map<int, SStudData> &studentMap);

  // Output the list of students whose average score falls within a given range
  static void printStudentsInScoreRange(
      const std::map<int, SStudData> &studentMap, double minScore,
      double maxScore);

  // Output the list of students who took a specified subject
  static std::vector<SStudData> printStudentsBySubject(
      const std::map<int, SStudData> &studentMap, const std::string &subject);

  // Count how many students took each subject
  static std::map<std::string, int> countStudentsPerSubject(
      const std::map<int, SStudData> &studentMap);
};

// Overload << operator for outputting a vector of SStudData
std::ostream &operator<<(std::ostream &out, const std::vector<SStudData> &vec);

#endif  // SSTUDDATA_H
