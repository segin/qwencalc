#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <vector>
#include <deque>

namespace qwencalc {

class HistoryManager {
public:
    HistoryManager();
    
    void addEntry(const std::string& expression, double result);
    
    void clear();
    
    int size() const;
    
    std::string getHistory() const;
    std::vector<std::string> getHistoryList() const;
    
    double getLastResult() const;
    std::string getLastEntry() const;
    
    void setMaxEntries(int maxEntries);
    int getMaxEntries() const;
    
private:
    std::deque<std::pair<std::string, double>> history;
    int maxEntries;
};

} // namespace qwencalc

#endif // HISTORY_MANAGER_H
