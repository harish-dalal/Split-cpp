#include "splitwise.h"
#include <ncurses.h>

void fillupData(SplitWise &splitwise) {
  splitwise.addUser(User("Harish"));    // 0
  splitwise.addUser(User("Siddhant"));  // 1
  splitwise.addUser(User("Digvijay"));  // 2
  splitwise.addUser(User("Rushikesh")); // 3
  splitwise.addUser(User("Amit"));      // 4
  splitwise.addUser(User("Jack"));      // 5

  splitwise.addGroup(Group("Groceries", false)); // 0

  splitwise.addGroupMember(GroupMember(0, 0)); // 0
  splitwise.addGroupMember(GroupMember(0, 1)); // 1
  splitwise.addGroupMember(GroupMember(0, 2)); // 2
  splitwise.addGroupMember(GroupMember(0, 3)); // 3
  splitwise.addGroupMember(GroupMember(0, 4)); // 4

  splitwise.addFriendShip(FriendShip(0, 5)); // Harish -> Jack

  Expense::Args args = {.name = "Buiscuit", .amount = 5000, .groupId = 0, .groupUserIds = vector<int>{0, 1, 2, 3, 4}, .paidByUserId = 0};
  splitwise.addExpense(args); // 0
}

int main() {
  SplitWise splitwise;
  fillupData(splitwise);
  int choice;
  while (true) {
    cout << "\n\n";
    cout << "SplitWise System Menu:\n";
    cout << "1. Add User\n";
    cout << "2. Add Expense\n";
    cout << "3. Add Group\n";
    cout << "4. Add User to Group\n";
    cout << "5. View Users\n";
    cout << "6. View Expenses\n";
    cout << "7. View Groups\n";
    cout << "8. View Users in Group\n";
    cout << "9. View User's Group repayments\n";
    cout << "10. View User's Group Simplified repayments\n";
    cout << "11. View Group Repayments\n";
    cout << "12. View Group Member Balances\n";
    cout << "13. View all shares\n";
    cout << "14. Add Friends Expense\n";
    cout << "15. Print 2 Friend's Repayment (Non Group)\n";
    cout << "16. Print 2 Friend's Repayment (Including Group)\n";
    cout << "17. Print all FriendShips\n";
    cout << "18. Print all friendShip repayments\n";
    cout << "19. Print all Users repayments\n";
    cout << "20. Change group isDebtSimplified\n";
    cout << "21. Print group repayments based on isDebtSimplified settings\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    // add user
    case 1: {
      string name;
      cout << "Enter user name: ";
      cin.ignore();
      getline(cin, name);
      User user(name);
      splitwise.addUser(user);
      break;
    }
    // add Expense
    case 2: {
      // Display all group
      splitwise.printGroups();
      cout << "Enter group ID: ";
      int groupId;
      cin >> groupId;
      string name;
      double amount;
      cout << "Enter expense name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter amount: ";
      cin >> amount;
      // display users for group
      splitwise.printGroupUsers(groupId);

      cout << "Enter number of users: ";
      int numUsers;
      cin >> numUsers;
      cout << "Enter user IDs: ";
      vector<int> userIds;
      int userId;
      while (numUsers--) {
        cin >> userId;
        userIds.push_back(userId);
      }

      cout << "Paid By user ID: ";
      int paidByUserId;
      cin >> paidByUserId;

      Expense::Args args = {.name = name, .amount = amount, .groupId = groupId, .groupUserIds = userIds, .paidByUserId = paidByUserId};
      splitwise.addExpense(args);
      break;
    }
    // add Group
    case 3: {
      string name;
      bool isDebtSimplified;
      cout << "Enter group name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Is debt simplified (1 for Yes, 0 for No): ";
      cin >> isDebtSimplified;
      Group group(name, isDebtSimplified);
      splitwise.addGroup(group);
      break;
    }
    // add User to Group
    case 4: {
      int userId, groupId;
      splitwise.printAllUsers();
      cout << "Enter user ID: ";
      cin >> userId;
      splitwise.printGroups();
      cout << "Enter group ID: ";
      cin >> groupId;
      GroupMember groupMember(groupId, userId);
      splitwise.addGroupMember(groupMember);
      break;
    }
    // View Users
    case 5:
      splitwise.printAllUsers();
      break;
    // View expenses
    case 6:
      splitwise.printExpenses();
      break;
    // View Groups
    case 7:
      splitwise.printGroups();
      break;
    // View Users in Group
    case 8: {
      splitwise.printGroups();
      cout << "Enter group ID: ";
      int groupId;
      cin >> groupId;
      splitwise.printUsersInGroup(groupId);
      break;
    }
    // View User's Group repayments
    case 9: {
      splitwise.printGroups();
      cout << "Enter group ID: ";
      int groupId;
      cin >> groupId;

      splitwise.printUsersInGroup(groupId);
      cout << "Enter user ID: ";
      int userId;
      cin >> userId;
      splitwise.printUsersGroupRepaymentBalances(userId, groupId);
      break;
    }
    // View User's Group Simplified repayments
    case 10: {
      cout << "to be added\n";
      splitwise.printAllSimplifiedGroupRepaymentBalances();
      break;
    }
    // view all repayment balances
    case 11: {
      splitwise.printAllGroupRepaymentBalances();
      break;
    }
    // View Group Member Balances
    case 12: {
      splitwise.printGroupMembersBalances();
      break;
    }
    // view all shares
    case 13: {
      splitwise.printShares();
      break;
    }
    // Add Friends Expense
    case 14: {
      string name;
      double amount;
      cout << "Enter expense name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter amount: ";
      cin >> amount;
      // display users for group
      splitwise.printAllUsers();

      cout << "Enter number of users: ";
      int numUsers;
      cin >> numUsers;
      cout << "Enter user IDs: ";
      vector<int> userIds;
      int userId;
      while (numUsers--) {
        cin >> userId;
        userIds.push_back(userId);
      }

      cout << "Paid By user ID: ";
      int paidByUserId;
      cin >> paidByUserId;

      Expense::Args args = {.name = name, .amount = amount, .friendUserIds = userIds, .paidByUserId = paidByUserId};
      splitwise.addExpense(args);
      break;
    }
    // Get Friends Repayment (Non group)
    case 15: {
      splitwise.printAllUsers();
      cout << "Enter user1 id: ";
      int user1Id;
      cin >> user1Id;
      cout << "Enter user2 id: ";
      int user2Id;
      cin >> user2Id;
      splitwise.printRepaymentsBetweenFriends(user1Id, user2Id);
      break;
    }
    // Get Friends Repayment (Including Groups)
    case 16: {
      splitwise.printAllUsers();
      cout << "Enter user1 id: ";
      int user1Id;
      cin >> user1Id;
      cout << "Enter user2 id: ";
      int user2Id;
      cin >> user2Id;
      splitwise.printRepaymentsBetweenFriends(user1Id, user2Id, true);
      break;
    }
    // Print all friendShips
    case 17: {
      splitwise.printAllFriendShips();
      break;
    }
    // Print all friendShips repayments
    case 18: {
      splitwise.printAllFriendShipsRepayments();
      break;
    }
    case 19: {
      cout << "To be added\n";
      break;
    }
    // update group is simplified debt
    case 20: {
      splitwise.printGroups();
      cout << "Enter group ID: ";
      int groupId;
      cin >> groupId;
      bool update = splitwise.updateGroupIsSimpfliedDebt(groupId);
      cout << "Group is simplified debt updated to: " << update << endl;
      break;
    }
    // print group repayments based on group isSimplified setting
    case 21: {
      splitwise.printGroups();
      cout << "Enter group ID: ";
      int groupId;
      cin >> groupId;
      splitwise.printGroupRepaymentBalances(groupId);
      break;
    }
    case 0:
      cout << "Exiting...\n";
      return 0;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}
