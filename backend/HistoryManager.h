#pragma once

#include <ctime>
#include <deque>
#include <fstream>
#include <string>
#include <vector>

namespace qwencalc {

struct HistoryEntry {
    std::string expression;
    double result;
    time_t timestamp;
};

class HistoryManager {
  public:
    HistoryManager();

    void addEntry(const std::string &expression, double result);

    void clear();

    int size() const;

    std::string getHistory() const;
    std::vector<std::string> getHistoryList() const;

    double getLastResult() const;
    std::string getLastEntry() const;

    void setMaxEntries(int maxEntries);
    int getMaxEntries() const;

    bool saveToFile(const std::string &filename);
    bool loadFromFile(const std::string &filename);

  private:
    std::deque<HistoryEntry> history;
    int maxEntries;

    void trimHistory();
};

} // namespace qwencalc
