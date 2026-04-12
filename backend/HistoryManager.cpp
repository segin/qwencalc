#include "HistoryManager.h"
#include <sstream>
#include <iomanip>

namespace qwencalc {

HistoryManager::HistoryManager()
    : maxEntries(50) {
}

void HistoryManager::addEntry(const std::string& expression, double result) {
    HistoryEntry entry;
    entry.expression = expression;
    entry.result = result;
    entry.timestamp = std::time(nullptr);
    
    history.push_back(entry);
    
    while (static_cast<int>(history.size()) > maxEntries) {
        history.pop_front();
    }
}

void HistoryManager::clear() {
    history.clear();
}

int HistoryManager::size() const {
    return static_cast<int>(history.size());
}

std::string HistoryManager::getHistory() const {
    std::ostringstream ss;
    for (const auto& entry : history) {
        ss << entry.expression << " = " << std::setprecision(10) << entry.result << "\n";
    }
    return ss.str();
}

std::vector<std::string> HistoryManager::getHistoryList() const {
    std::vector<std::string> list;
    for (const auto& entry : history) {
        std::ostringstream ss;
        ss << entry.expression << " = " << std::setprecision(10) << entry.result;
        list.push_back(ss.str());
    }
    return list;
}

double HistoryManager::getLastResult() const {
    if (history.empty()) {
        return 0.0;
    }
    return history.back().result;
}

std::string HistoryManager::getLastEntry() const {
    if (history.empty()) {
        return "";
    }
    std::ostringstream ss;
    ss << history.back().expression << " = " << std::setprecision(10) << history.back().result;
    return ss.str();
}

void HistoryManager::setMaxEntries(int max) {
    if (max >= 1) {
        maxEntries = max;
        trimHistory();
    }
}

int HistoryManager::getMaxEntries() const {
    return maxEntries;
}

void HistoryManager::trimHistory() {
    while (static_cast<int>(history.size()) > maxEntries) {
        history.pop_front();
    }
}

bool HistoryManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& entry : history) {
        file << entry.expression << " " << entry.result << " " << entry.timestamp << "\n";
    }
    
    file.close();
    return true;
}

bool HistoryManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        history.clear();
        return true;
    }
    
    history.clear();
    
    std::string expression;
    double result;
    time_t timestamp;
    
    while (file >> expression >> result >> timestamp) {
        HistoryEntry entry;
        entry.expression = expression;
        entry.result = result;
        entry.timestamp = timestamp;
        history.push_back(entry);
    }
    
    file.close();
    return true;
}

} // namespace qwencalc