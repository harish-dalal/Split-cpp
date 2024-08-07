#include "splitwise.h"
#include <ncurses.h>

void fillupData(SplitWise &splitwise) {
  splitwise.addUser(User("Harish"));
  splitwise.addUser(User("Siddhant"));
  splitwise.addUser(User("Digvijay"));
  splitwise.addUser(User("Rushikesh"));
  splitwise.addUser(User("Amit"));

  splitwise.addGroup(Group("Groceries", false));

  splitwise.addGroupMember(GroupMember(0, 0));
  splitwise.addGroupMember(GroupMember(0, 1));
  splitwise.addGroupMember(GroupMember(0, 2));
  splitwise.addGroupMember(GroupMember(0, 3));
  splitwise.addGroupMember(GroupMember(0, 4));

  splitwise.addExpense(Expense("Buiscuit", 5000, 0), vector<int>{0, 1, 2, 3, 4}, 0);
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
      double groupId;
      cin >> groupId;
      string name;
      double amount;
      cout << "Enter expense name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter amount: ";
      cin >> amount;
      // display users for group
      splitwise.printUsers();

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

      Expense expense(name, amount, groupId);
      splitwise.addExpense(expense, userIds, paidByUserId);
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
      splitwise.printUsers();
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
      splitwise.printUsers();
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
    case 0:
      cout << "Exiting...\n";
      return 0;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}
