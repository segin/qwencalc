#include "HistoryManager.h"

namespace qwencalc {

HistoryManager::HistoryManager()
    : maxEntries(50) {
}

void HistoryManager::addEntry(const std::string& expression, double result) {
    history.push_back(std::make_pair(expression, result));
    
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
    std::string result;
    for (const auto& entry : history) {
        result += entry.first + " = " + std::to_string(entry.second) + "\n";
    }
    return result;
}

std::vector<std::string> HistoryManager::getHistoryList() const {
    std::vector<std::string> list;
    for (const auto& entry : history) {
        list.push_back(entry.first + " = " + std::to_string(entry.second));
    }
    return list;
}

double HistoryManager::getLastResult() const {
    if (history.empty()) {
        return 0.0;
    }
    return history.back().second;
}

std::string HistoryManager::getLastEntry() const {
    if (history.empty()) {
        return "";
    }
    return history.back().first + " = " + std::to_string(history.back().second);
}

void HistoryManager::setMaxEntries(int max) {
    if (max > 10) {
        maxEntries = max;
    }
}

int HistoryManager::getMaxEntries() const {
    return maxEntries;
}

} // namespace qwencalc
