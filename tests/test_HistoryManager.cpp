#include <gtest/gtest.h>
#include "HistoryManager.h"
#include <ctime>
#include <fstream>
#include <limits>

using namespace qwencalc;

class HistoryManagerTest : public ::testing::Test {
protected:
    HistoryManager manager;
    
    void SetUp() override {
        manager.setMaxEntries(50);
    }
    
    void TearDown() override {
        manager.clear();
    }
};

TEST_F(HistoryManagerTest, DefaultConstructor) {
    HistoryManager hm;
    EXPECT_EQ(hm.getMaxEntries(), 50);
}

TEST_F(HistoryManagerTest, AddEntry) {
    manager.addEntry("2 + 2", 4.0);
    EXPECT_EQ(manager.size(), 1);
    EXPECT_DOUBLE_EQ(manager.getLastResult(), 4.0);
}

TEST_F(HistoryManagerTest, AddMultipleEntries) {
    manager.addEntry("1 + 1", 2.0);
    manager.addEntry("3 * 3", 9.0);
    manager.addEntry("10 / 2", 5.0);
    
    EXPECT_EQ(manager.size(), 3);
    EXPECT_DOUBLE_EQ(manager.getLastResult(), 5.0);
}

TEST_F(HistoryManagerTest, MaxEntriesLimit) {
    manager.setMaxEntries(3);
    
    manager.addEntry("1", 1.0);
    manager.addEntry("2", 2.0);
    manager.addEntry("3", 3.0);
    manager.addEntry("4", 4.0);
    
    EXPECT_EQ(manager.size(), 3);
    EXPECT_EQ(manager.getLastResult(), 4.0);
}

TEST_F(HistoryManagerTest, Clear) {
    manager.addEntry("1 + 1", 2.0);
    manager.addEntry("2 + 2", 4.0);
    
    manager.clear();
    EXPECT_EQ(manager.size(), 0);
}

TEST_F(HistoryManagerTest, GetLastResultEmpty) {
    EXPECT_DOUBLE_EQ(manager.getLastResult(), 0.0);
}

TEST_F(HistoryManagerTest, GetLastResultValid) {
    manager.addEntry("5 * 5", 25.0);
    EXPECT_DOUBLE_EQ(manager.getLastResult(), 25.0);
}

TEST_F(HistoryManagerTest, GetLastEntryEmpty) {
    EXPECT_EQ(manager.getLastEntry(), "");
}

TEST_F(HistoryManagerTest, GetLastEntryValid) {
    manager.addEntry("3 + 3", 6.0);
    EXPECT_EQ(manager.getLastEntry(), "3 + 3 = 6");
}

TEST_F(HistoryManagerTest, GetHistory) {
    manager.addEntry("1 + 1", 2.0);
    manager.addEntry("2 + 2", 4.0);
    
    std::string history = manager.getHistory();
    EXPECT_NE(history.find("1 + 1"), std::string::npos);
    EXPECT_NE(history.find("2 + 2"), std::string::npos);
}

TEST_F(HistoryManagerTest, GetHistoryList) {
    manager.addEntry("1 + 1", 2.0);
    manager.addEntry("2 + 2", 4.0);
    
    auto list = manager.getHistoryList();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "1 + 1 = 2");
    EXPECT_EQ(list[1], "2 + 2 = 4");
}

TEST_F(HistoryManagerTest, SetMaxEntries) {
    manager.setMaxEntries(100);
    EXPECT_EQ(manager.getMaxEntries(), 100);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
    
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
}

TEST_F(HistoryManagerTest, TimestampField) {
    manager.addEntry("1 + 1", 2.0);
    
    std::vector<std::string> list = manager.getHistoryList();
    EXPECT_EQ(list.size(), 1);
}

TEST_F(HistoryManagerTest, SaveToFile) {
    manager.addEntry("3 + 3", 6.0);
    manager.addEntry("4 * 4", 16.0);
    
    bool result = manager.saveToFile("/tmp/test_history.txt");
    EXPECT_TRUE(result);
}

TEST_F(HistoryManagerTest, LoadFromFile) {
    manager.saveToFile("/tmp/test_history_load.txt");
    
    HistoryManager manager2;
    bool result = manager2.loadFromFile("/tmp/test_history_load.txt");
    EXPECT_TRUE(result);
}

TEST_F(HistoryManagerTest, LoadEmptyFile) {
    HistoryManager manager2;
    bool result = manager2.loadFromFile("/tmp/test_history_empty.txt");
    EXPECT_TRUE(result);
    EXPECT_EQ(manager2.size(), 0);
}

TEST_F(HistoryManagerTest, InvalidMaxEntries) {
    manager.setMaxEntries(5);
    EXPECT_EQ(manager.getMaxEntries(), 5);
}

