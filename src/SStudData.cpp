#include "SStudData.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

SMark::SMark(const std::string &subject, int mark)
    : Subject(subject), Mark(mark) {}

SStudData::SStudData(const std::string &name, int id) : Name(name), ID(id) {}

void SStudData::addMark(const SMark &mark) { Marks.push_back(mark); }

std::string SStudData::getName() const { return Name; }

int SStudData::getID() const { return ID; }

std::vector<SMark> SStudData::getMarks() const { return Marks; }

SStudData &SStudData::operator=(const SStudData &other) {
  if (this == &other) return *this;  // проверка на самоприсваивание

  Name = other.Name;
  ID = other.ID;
  Marks = other.Marks;

  return *this;
}

std::ostream &operator<<(std::ostream &out, const std::vector<SStudData> &vec) {
  for (const auto &data : vec) {
    out << data << "\n";
  }
  return out;
}

std::ostream &operator<<(std::ostream &out, const SStudData &data) {
  out << "Name: " << data.Name << "\n";
  out << "ID: " << data.ID << "\n";
  out << "Marks:\n";
  for (const auto &mark : data.Marks) {
    out << "  Subject: " << mark.Subject << ", Mark: " << mark.Mark << "\n";
  }
  return out;
}

std::vector<SStudData> SStudData::readFromFile(const std::string &filename) {
  std::vector<SStudData> students;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    std::string name;
    std::string id;

    name = line.substr(0, line.find(';'));
    line = line.substr(line.find(';') + 1);
    id = line.substr(0, line.find(';'));
    line = line.substr(line.find(';') + 1);

    SStudData student(name, std::stoi(id));

    std::string subject;
    std::string mark;
    while (line.find(',') != std::string::npos) {
      subject = line.substr(0, line.find('-'));
      line = line.substr(line.find('-') + 1);
      mark = line.substr(0, line.find(','));
      line = line.substr(line.find(',') + 1);

      SMark smark(subject, std::stoi(mark));

      student.addMark(smark);
    }

    subject = line.substr(0, line.find('-'));
    line = line.substr(line.find('-') + 1);
    mark = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1);

    SMark smark(subject, std::stoi(mark));

    student.addMark(smark);

    students.push_back(student);
  }

  return students;
}

bool SStudData::hasSubject(const std::string &subject) const {
  for (const auto &mark : Marks) {
    if (mark.Subject == subject) {
      return true;
    }
  }
  return false;
}

void SStudData::sortStudents(std::vector<SStudData> &students) {
  std::sort(students.begin(), students.end(),
            [](const SStudData &a, const SStudData &b) {
              if (a.Name == b.Name) {
                return a.ID < b.ID;  // ascending by ID
              }
              return a.Name > b.Name;  // descending by Name
            });
}

std::map<int, SStudData> SStudData::formMap(
    const std::vector<SStudData> &students) {
  std::map<int, SStudData> studentMap;
  for (const auto &student : students) {
    studentMap[student.getID()] = student;
  }
  return studentMap;
}

SStudData SStudData::findMaxTotalScoreStudent(
    const std::map<int, SStudData> &studentMap) {
  if (studentMap.empty()) {
    throw std::runtime_error("Student map is empty");
  }

  auto maxStudentIt = std::max_element(
      studentMap.begin(), studentMap.end(), [](const auto &a, const auto &b) {
        int totalScoreA = 0;
        for (const auto &mark : a.second.getMarks()) {
          totalScoreA += mark.Mark;
        }

        int totalScoreB = 0;
        for (const auto &mark : b.second.getMarks()) {
          totalScoreB += mark.Mark;
        }

        return totalScoreA < totalScoreB;
      });

  return maxStudentIt->second;
}

std::vector<SStudData> SStudData::findStudentsWithoutFailures(
    const std::map<int, SStudData> &studentMap) {
  std::vector<SStudData> studentsWithoutFailures;

  for (const auto &pair : studentMap) {
    bool hasFailures = false;
    for (const auto &mark : pair.second.getMarks()) {
      if (mark.Mark == 2) {
        hasFailures = true;
        break;
      }
    }
    if (!hasFailures) {
      studentsWithoutFailures.push_back(pair.second);
    }
  }

  return studentsWithoutFailures;
}

double SStudData::calculateAverageScore() const {
  if (Marks.empty()) {
    return 0.0;
  }

  int totalScore = 0;
  for (const auto &mark : Marks) {
    totalScore += mark.Mark;
  }

  return static_cast<double>(totalScore) / Marks.size();
}

void SStudData::printSortedStudents(
    const std::map<int, SStudData> &studentMap) {
  std::vector<SStudData> students;

  for (const auto &pair : studentMap) {
    students.push_back(pair.second);
  }

  std::sort(students.begin(), students.end(),
            [](const SStudData &a, const SStudData &b) {
              if (a.getName() == b.getName()) {
                return a.calculateAverageScore() > b.calculateAverageScore();
              }
              return a.getName() < b.getName();
            });

  for (const auto &student : students) {
    std::cout << student.getName() << " " << student.calculateAverageScore()
              << " " << student.getID() << "\n";
  }
}
void SStudData::printStudentsInScoreRange(
    const std::map<int, SStudData> &studentMap, double minScore,
    double maxScore) {
  std::vector<SStudData> studentsInRange;

  for (const auto &pair : studentMap) {
    double avgScore = pair.second.calculateAverageScore();
    if (avgScore >= minScore && avgScore <= maxScore) {
      studentsInRange.push_back(pair.second);
    }
  }

  std::cout << "Студенты, средний балл которых находится в диапазоне "
            << minScore << " - " << maxScore << ":\n";
  for (const auto &student : studentsInRange) {
    std::cout << "ID: " << student.getID() << ", Name: " << student.getName()
              << ", Average Score: " << student.calculateAverageScore() << "\n";
  }
}

std::vector<SStudData> SStudData::printStudentsBySubject(
    const std::map<int, SStudData> &studentMap, const std::string &subject) {
  std::vector<SStudData> studentsBySubject;

  for (const auto &pair : studentMap) {
    if (pair.second.hasSubject(subject)) {
      studentsBySubject.push_back(pair.second);
    }
  }

  std::cout << "Студенты, которые сдавали предмет " << subject << ":\n";
  for (const auto &student : studentsBySubject) {
    std::cout << "ID: " << student.getID() << ", Name: " << student.getName()
              << ", Average Score: " << student.calculateAverageScore() << "\n";
  }

  return studentsBySubject;
}

std::map<std::string, int> SStudData::countStudentsPerSubject(
    const std::map<int, SStudData> &studentMap) {
  std::map<std::string, int> subjectCount;

  for (const auto &pair : studentMap) {
    const auto &marks = pair.second.getMarks();
    for (const auto &mark : marks) {
      subjectCount[mark.Subject]++;
    }
  }

  return subjectCount;
}
