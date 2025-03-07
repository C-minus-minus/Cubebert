#include "table_manager.h"

int main() {
    TableManager* tableManager = new TableManager();
    tableManager->generateTables();
    tableManager->writeTablesToFile();
    delete tableManager;
    return 0;
}