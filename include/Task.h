#pragma once
#include <string>
#include <vector>

struct Task {
  std::string description;
  bool done;
};

void saveTasksToFile(const std::vector<Task>& tasks, const std::string& fileName);
std::vector<Task> loadTasksFromFile(const std::string& fileName);
