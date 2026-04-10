#include "HistoryManager.h"
#include <sstream>

namespace qwencalc {

HistoryManager::HistoryManager()
    : maxEntries(100) {}

void HistoryManager::addEntry(const std::string& expression, double result) {
    history.push_back(std::make_pair(expression, result));
    
    if (static_cast<int>(history.size()) > maxEntries) {
        history.pop_back();
    }
}

void HistoryManager::clear() {
    history.clear();
}

int HistoryManager::size() const {
    return static_cast<int>(history.size());
}

std::string HistoryManager::getHistory() const {
    std::stringstream ss;
    for (const auto& entry : history) {
        ss << entry.first << " = " << entry.second << "\n";
    }
    return ss.str();
}

std::vector<std::string> HistoryManager::getHistoryList() const {
    std::vector<std::string> entries;
    for (const auto& entry : history) {
        entries.push_back(entry.first + " = " + std::to_string(entry.second));
    }
    return entries;
}

double HistoryManager::getLastResult() const {
    if (history.empty()) {
        return 0.0;
    }
    return history.front().second;
}

std::string HistoryManager::getLastEntry() const {
    if (history.empty()) {
        return "";
    }
    return history.front().first;
}

void HistoryManager::setMaxEntries(int maxEntries) {
    maxEntries = std::max(1, maxEntries);
    this->maxEntries = maxEntries;
    
    while (static_cast<int>(history.size()) > maxEntries) {
        history.pop_back();
    }
}

int HistoryManager::getMaxEntries() const {
    return maxEntries;
}

} // namespace qwencalc
