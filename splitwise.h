#ifndef SPLITWISE_H
#define SPLITWISE_H

#include <bits/stdc++.h>
using namespace std;

class User {
  int id;
  string name;

public:
  static int idIncrementer;

  User() : id(-1) {}

  User(string name) : id(idIncrementer++), name(name) {}

  int getId() { return id; }
  string getName() { return name; }
};

int User::idIncrementer = 0;

class Expense {
  int id;
  string name;
  double amount;
  int groupId;

public:
  static int idIncrementer;

  Expense() : id(-1) {}

  Expense(string name, double amount, int groupId = -1)
      : id(idIncrementer++), name(name), amount(amount), groupId(groupId) {}

  int getGroupId() const { return groupId; }
  void setGroupId(double _groupId) { this->groupId = _groupId; }

  int getId() const { return id; }
  string getName() const { return name; }
  double getAmount() const { return amount; }
};

class Share {
  int id;
  double netBalance;
  double owedShare;
  double paidShare;
  int userId;
  int expenseId;

public:
  static int idIncrementer;

  Share() : id(-1) {}

  Share(double netBalance, double owedShare, double paidShare, int userId, int expenseId)
      : id(idIncrementer++), netBalance(netBalance), owedShare(owedShare), paidShare(paidShare), userId(userId), expenseId(expenseId) {}

  int getId() const { return id; }
  double getNetBalance() const { return netBalance; }
  double getOwedShare() const { return owedShare; }
  double getPaidShare() const { return paidShare; }
  int getUserId() const { return userId; }
  int getExpenseId() const { return expenseId; }
};

int Share::idIncrementer = 0;

int Expense::idIncrementer = 0;

class Group {
  int id;
  string name;
  bool isDebtSimplified;

public:
  static int idIncrementer;

  Group() : id(-1) {}

  Group(string name, bool isDebtSimplified = false)
      : id(idIncrementer++), name(name), isDebtSimplified(isDebtSimplified) {}

  int getId() const { return id; }
  string getName() const { return name; }
  bool getIsDebtSimplified() const { return isDebtSimplified; }
  void setIsDebtSimplified(bool _isDebtSimplified) { this->isDebtSimplified = _isDebtSimplified; }
};

int Group::idIncrementer = 0;

class GroupMember {
  int id;
  int groupId;
  int userId;

public:
  static int idIncrementer;

  GroupMember() : id(-1) {}

  GroupMember(int groupId, int userId)
      : id(idIncrementer++), groupId(groupId), userId(userId) {}

  int getId() const { return id; }
  int getGroupId() const { return groupId; }
  int getUserId() const { return userId; }
};

int GroupMember::idIncrementer = 0;

class GroupMemberBalance {
  int id;
  int groupMemberId;
  double amount;

public:
  static int idIncrementer;

  GroupMemberBalance() : id(-1) {}

  GroupMemberBalance(int groupMemberId, double amount)
      : id(idIncrementer++), groupMemberId(groupMemberId), amount(amount) {}

  int getId() const { return id; }
  int getGroupMemberId() const { return groupMemberId; }
  double getAmount() const { return amount; }
  void setAmount(double _amount) { this->amount = _amount; }
};

int GroupMemberBalance::idIncrementer = 0;

class GroupRepaymentBalance {
  int id;
  double amount;
  int groupId;
  int fromUserId;
  int toUserId;

public:
  static int idIncrementer;

  GroupRepaymentBalance() : id(-1) {}

  GroupRepaymentBalance(double amount, double groupId, double fromUserId, double toUserId)
      : id(idIncrementer++), amount(amount), groupId(groupId), fromUserId(fromUserId), toUserId(toUserId) {}

  int getId() const { return id; }
  double getAmount() const { return amount; }
  int getGroupId() const { return groupId; }
  int getFromUserId() const { return fromUserId; }
  int getToUserId() const { return toUserId; }

  void setAmount(double _amount) { this->amount = _amount; }
  void setGroupId(double _groupId) { this->groupId = _groupId; }
  void setFromUserId(double _fromUserId) { this->fromUserId = _fromUserId; }
  void setToUserId(double _toUserId) { this->toUserId = _toUserId; }
};

int GroupRepaymentBalance::idIncrementer = 0;

class FriendShip {
  int id;
  int fromUserId;
  int toUserId;

public:
  static int idIncrementer;

  FriendShip() : id(-1) {}

  FriendShip(int fromUserId, int toUserId)
      : id(idIncrementer++), fromUserId(fromUserId), toUserId(toUserId) {}

  int getId() const { return id; }
  int getFromUserId() const { return fromUserId; }
  int getToUserId() const { return toUserId; }
};

int FriendShip::idIncrementer = 0;

class FriendShipBalance {
  int id;
  int friendShipId;
  double amount;

public:
  static int idIncrementer;

  FriendShipBalance() : id(-1) {}

  FriendShipBalance(int friendShipId, double amount)
      : id(idIncrementer++), friendShipId(friendShipId), amount(amount) {}

  int getId() const { return id; }
  int getFriendShipId() const { return friendShipId; }
  double getAmount() const { return amount; }
  void setAmount(double _amount) { this->amount = _amount; }
};

int FriendShipBalance::idIncrementer = 0;

class SplitWise {
private:
  map<int, User> users;
  map<int, Expense> expenses;
  map<int, Group> groups;
  map<int, GroupMember> groupMembers;
  map<int, GroupMemberBalance> groupMemberBalances;
  map<int, GroupRepaymentBalance> groupRepaymentBalances;
  map<int, Share> shares;

  // friends
  map<int, FriendShip> friendShips;
  map<int, FriendShipBalance> friendShipBalances;

  void updateShares(const Expense &expense, int paidByUserId, vector<int> &userIds) {
    double owedShare = (expense.getAmount() / userIds.size());
    for (double userId : userIds) {
      if (userId == paidByUserId) {
        Share share(owedShare - expense.getAmount(), owedShare, expense.getAmount(), userId, expense.getId());
        this->addShare(share);
      } else {
        Share share(owedShare, owedShare, 0, userId, expense.getId());
        this->addShare(share);
      }
    }
  }

  struct Repayment {
    int from_userId;
    int to_userId;
    double amount;
    Repayment(int from, int to, double amt) : from_userId(from), to_userId(to), amount(amt) {}
  };

  // updateGroupRepaymentBalances for a single Group
  void updateGroupRepaymentBalances(const Expense &expense) {
    map<int, Share> epxShares = getExpenseShares(expense);

    // userid, amount
    vector<pair<int, double>> creditors; // positive balance (they have to give money)
    vector<pair<int, double>> debtors;   // negative balance (they will collect money)

    for (const auto &[id, share] : epxShares) {
      if (share.getNetBalance() > 0) {
        creditors.push_back({share.getUserId(), share.getNetBalance()});
      } else if (share.getNetBalance() < 0) {
        debtors.push_back({share.getUserId(), share.getNetBalance()});
      }
    }

    vector<Repayment> simplifiedDebts = generateSimplifiedDebts(creditors, debtors);

    cout << "Simplified Debts for the group expense: " << expense.getName() << endl;
    printRepayments(simplifiedDebts);

    int groupId = expenses[epxShares.begin()->second.getExpenseId()].getGroupId();
    for (const auto &simplifiedDebt : simplifiedDebts) {
      int fromUserId = simplifiedDebt.from_userId, toUserId = simplifiedDebt.to_userId;
      double amount = simplifiedDebt.amount;
      bool isUpdate = false;
      for (const auto &[id, groupRepayment] : groupRepaymentBalances) {
        if (groupRepayment.getGroupId() == groupId) {
          if (groupRepayment.getFromUserId() == fromUserId && groupRepayment.getToUserId() == toUserId) {
            updateGroupRepaymentBalance(id, groupRepayment.getAmount() + amount);
            isUpdate = true;
            break;
          }
        }
      }
      if (!isUpdate) {
        addGroupRepaymentBalance(GroupRepaymentBalance(amount, groupId, fromUserId, toUserId));
      }
    }
  }

  // updateGroupMemberBalances for a single Group
  void updateGroupMemberBalances(const Expense &expense) {
    // get expense shares;
    map<int, Share> epxShares = getExpenseShares(expense);

    int groupId = expenses[epxShares.begin()->second.getExpenseId()].getGroupId();

    for (const auto &[id, share] : epxShares) {
      // get group member id for the share user
      int memberId = getUserGroupMemberId(share.getUserId(), groupId);

      bool isUpdate = false;
      for (const auto &[balanceId, groupBalance] : groupMemberBalances) {
        if (groupBalance.getGroupMemberId() == memberId) {
          updateGroupMemberBalance(balanceId, groupBalance.getAmount() + share.getNetBalance());
          isUpdate = true;
          break;
        }
      }

      if (!isUpdate) {
        addGroupMemberBalance(GroupMemberBalance(memberId, share.getNetBalance()));
      }
    }
  }

  void updateFriendShipBalances(const Expense &expense) {
    map<int, Share> epxShares = getExpenseShares(expense);

    // userid, amount
    vector<pair<int, double>> creditors; // positive balance (they have to give money)
    vector<pair<int, double>> debtors;   // negative balance (they will collect money)

    for (const auto &[id, share] : epxShares) {
      if (share.getNetBalance() > 0) {
        creditors.push_back({share.getUserId(), share.getNetBalance()});
      } else if (share.getNetBalance() < 0) {
        debtors.push_back({share.getUserId(), share.getNetBalance()});
      }
    }

    vector<Repayment> simplifiedDebts = generateSimplifiedDebts(creditors, debtors);

    cout << "Simplified Debts for the friend expense: " << expense.getName() << endl;
    printRepayments(simplifiedDebts);

    for (const auto &simplifiedDebt : simplifiedDebts) {
      int fromUserId = simplifiedDebt.from_userId, toUserId = simplifiedDebt.to_userId;
      double amount = simplifiedDebt.amount;
      bool isUpdate = false;
      int friendShipId = addFriendIfNotAlready(fromUserId, toUserId);
      FriendShip friendShip = friendShips[friendShipId];
      for (const auto &[id, friendShipBalance] : friendShipBalances) {
        int balanceFriendShipId = friendShipBalance.getFriendShipId();
        if (balanceFriendShipId == friendShipId) {
          if (friendShip.getFromUserId() == fromUserId && friendShip.getToUserId() == toUserId)
            updateFriendShipBalance(id, friendShipBalance.getAmount() + amount);
          else
            updateFriendShipBalance(id, friendShipBalance.getAmount() - amount);
          isUpdate = true;
          break;
        }
      }
      if (!isUpdate) {
        if (friendShip.getFromUserId() == fromUserId && friendShip.getToUserId() == toUserId)
          addFriendShipBalance(FriendShipBalance(friendShipId, amount));
        else
          addFriendShipBalance(FriendShipBalance(friendShipId, -amount));
      }
    }
  }

  // input -> creditor - userId, amount and debtors - userId, amount
  vector<Repayment> generateSimplifiedDebts(vector<pair<int, double>> creditors, vector<pair<int, double>> debtors) {
    vector<Repayment> repayments;

    auto comparator = [](pair<int, double> a, pair<int, double> b) { return a.second < b.second; };
    sort(creditors.begin(), creditors.end(), comparator);
    sort(debtors.begin(), debtors.end(), comparator);

    size_t i = 0, j = 0;
    while (i < creditors.size() && j < debtors.size()) {
      double creditAmount = creditors[i].second;
      double debtAmount = -debtors[j].second;
      double minAmount = std::min(creditAmount, debtAmount);

      repayments.emplace_back(creditors[i].first, debtors[j].first, minAmount);

      creditors[i].second -= minAmount;
      debtors[j].second += minAmount;

      if (creditors[i].second == 0)
        i++;
      if (debtors[j].second == 0)
        j++;
    }

    return repayments;
  }

  vector<Repayment> getGroupRepaymentBalances(int groupId) {
    // from, to amount - from > to
    map<pair<int, int>, double> repayments;
    for (const auto &[id, groupRepaymentBalance] : groupRepaymentBalances) {
      if (groupRepaymentBalance.getGroupId() == groupId) {
        if (groupRepaymentBalance.getFromUserId() > groupRepaymentBalance.getToUserId()) {
          repayments[{groupRepaymentBalance.getFromUserId(), groupRepaymentBalance.getToUserId()}] += groupRepaymentBalance.getAmount();
        } else {
          repayments[{groupRepaymentBalance.getToUserId(), groupRepaymentBalance.getFromUserId()}] -= groupRepaymentBalance.getAmount();
        }
      }
    }

    vector<Repayment> repaymentList;
    for (auto &[u, amount] : repayments) {
      if (amount > 0) {
        repaymentList.push_back(Repayment(u.first, u.second, amount));
      } else if (amount < 0) {
        repaymentList.push_back(Repayment(u.second, u.first, -amount));
      }
    }

    return repaymentList;
  }

  void printRepayments(vector<Repayment> repayments) {
    for (const auto repayment : repayments) {
      cout << users[repayment.from_userId].getName() << " -> " << users[repayment.to_userId].getName() << " : " << repayment.amount << endl;
    }
    cout << endl;
  }

  void makeEachOtherFriends(vector<int> userIds) {
    for (int i = 0; i < userIds.size(); i++) {
      for (int j = i + 1; j < userIds.size(); j++) {
        addFriendIfNotAlready(userIds[i], userIds[j]);
      }
    }
  }

  void _handleAddGroupExpense(const Expense &expense) {
    // update repayments
    updateGroupRepaymentBalances(expense);

    // update balances
    updateGroupMemberBalances(expense);

    // update friendShipBalance
    updateFriendShipBalances(expense);
  }

  void _handleAddFriendExpense(const Expense &expense) {
    updateFriendShipBalances(expense);
  }

  vector<Repayment> getRepaymentsBetweenFriends(int fromUserId, int toUserId) {
    vector<Repayment> repayments;
    int friendShipId = getFriendShipId(fromUserId, toUserId);
    if (friendShipId == -1)
      return repayments;

    FriendShip friendShip = friendShips[friendShipId];

    for (const auto &[id, friendShipBalance] : friendShipBalances) {
      if (friendShipBalance.getFriendShipId() == friendShipId) {
        if (friendShipBalance.getAmount() > 0) {
          repayments.emplace_back(friendShip.getFromUserId(), friendShip.getToUserId(), friendShipBalance.getAmount());
        } else if (friendShipBalance.getAmount() < 0) {
          repayments.emplace_back(friendShip.getToUserId(), friendShip.getFromUserId(), -friendShipBalance.getAmount());
        }
        break;
      }
    }

    return repayments;
  }

public:
  int addUser(User user) {
    users[user.getId()] = user;
    return user.getId();
  }
  int addGroup(const Group &group) {
    groups[group.getId()] = group;
    return group.getId();
  }
  int addGroupMember(const GroupMember &groupMember) {
    groupMembers[groupMember.getId()] = groupMember;
    return groupMember.getId();
  }
  int addGroupMemberBalance(const GroupMemberBalance &groupMemberBalance) {
    groupMemberBalances[groupMemberBalance.getId()] = groupMemberBalance;
    return groupMemberBalance.getId();
  }
  int addGroupRepaymentBalance(const GroupRepaymentBalance &groupRepaymentBalance) {
    groupRepaymentBalances[groupRepaymentBalance.getId()] = groupRepaymentBalance;
    return groupRepaymentBalance.getId();
  }
  int addShare(const Share &share) {
    shares[share.getId()] = share;
    return share.getId();
  }
  int addFriendShip(const FriendShip &friendShip) {
    friendShips[friendShip.getId()] = friendShip;
    return friendShip.getId();
  }
  int addFriendShipBalance(const FriendShipBalance &friendShipBalance) {
    friendShipBalances[friendShipBalance.getId()] = friendShipBalance;
    return friendShipBalance.getId();
  }

  int getFriendShipId(int userId1, int userId2) {
    for (const auto &[id, friendShip] : friendShips) {
      if ((friendShip.getFromUserId() == userId1 && friendShip.getToUserId() == userId2) || (friendShip.getFromUserId() == userId2 && friendShip.getToUserId() == userId1))
        return friendShip.getId();
    }
    return -1;
  }

  int addFriendIfNotAlready(int userId1, int userId2) {
    int friendShipId = getFriendShipId(userId1, userId2);
    if (friendShipId == -1) {
      friendShipId = addFriendShip(FriendShip(userId1, userId2));
    }
    return friendShipId;
  }

  void updateGroupRepaymentBalance(int id, double amount) { groupRepaymentBalances[id].setAmount(amount); }
  void updateGroupMemberBalance(int id, double amount) { groupMemberBalances[id].setAmount(amount); }
  void updateFriendShipBalance(int id, double amount) { friendShipBalances[id].setAmount(amount); }

  void addExpense(const Expense &expense, vector<int> userIds, int paidByUserId) {
    expenses[expense.getId()] = expense;

    // make each other friends
    makeEachOtherFriends(userIds);

    // create shares entity for this expense
    updateShares(expense, paidByUserId, userIds);

    if (expense.getGroupId() != -1) {
      _handleAddGroupExpense(expense);
    } else {
      _handleAddFriendExpense(expense);
    }
  }

  map<int, Share> getExpenseShares(const Expense &expense) {
    map<int, Share> expenseShares;
    for (const auto &[id, share] : shares) {
      if (share.getExpenseId() == expense.getId()) {
        expenseShares[share.getId()] = share;
      }
    }

    return expenseShares;
  }

  vector<int> getUserExpenseIds(int userId) {
    set<int> userExpenseIds;
    for (const auto &[shareId, share] : shares) {
      if (share.getUserId() == userId) {
        userExpenseIds.insert(share.getExpenseId());
      }
    }

    vector<int> userExpensesList(userExpenseIds.begin(), userExpenseIds.end());
    return userExpensesList;
  }

  vector<User> getExpenseUsers(int expenseId) {
    vector<User> expenseUsers;
    for (const auto &[shareId, share] : shares) {
      if (share.getExpenseId() == expenseId) {
        expenseUsers.push_back(users[share.getUserId()]);
      }
    }
    return expenseUsers;
  }

  int getUserGroupMemberId(int userId, int groupId) {
    for (const auto &[id, groupMember] : groupMembers) {
      if (groupMember.getUserId() == userId && groupMember.getGroupId() == groupId) {
        return groupMember.getId();
      }
    }

    return -1;
  }

  void printUsers() {
    for (auto &[id, user] : users) {
      cout << "User ID: " << user.getId() << ", Name: " << user.getName() << endl;
    }
  }

  void printAllFriendShips() {
    for (auto &[id, friendShip] : friendShips) {
      cout << "FriendShip ID: " << friendShip.getId() << ", From User ID: " << friendShip.getFromUserId() << ", To User ID: " << friendShip.getToUserId() << endl;
    }
  }

  void printExpenses() {
    for (auto &[id, expense] : expenses) {
      cout << "Expense ID: " << expense.getId() << ", Name: " << expense.getName()
           << ", Amount: " << expense.getAmount() << ", Group ID: " << expense.getGroupId() << endl;
    }
  }

  void printAllGroupRepaymentBalances() {
    for (const auto &[groupId, group] : groups) {
      cout << "Group Name: " << group.getName() << endl;
      vector<Repayment> repayments = getGroupRepaymentBalances(groupId);
      printRepayments(repayments);
    }
  }

  void printGroups() {
    for (const auto &[id, group] : groups) {
      cout << "Group ID: " << group.getId() << ", Name: " << group.getName()
           << ", Is Debt Simplified: " << group.getIsDebtSimplified() << endl;
    }
  }

  void printGroupMembersBalances() {
    for (const auto &[id, groupMemberBalance] : groupMemberBalances) {
      GroupMember member = groupMembers[groupMemberBalance.getGroupMemberId()];
      cout << "Group Name: " << groups[member.getGroupId()].getName() << ", User Name: " << users[member.getUserId()].getName() << ", Amount: " << groupMemberBalance.getAmount() << endl;
    }
  }

  void printShares() {
    for (const auto &[id, share] : shares) {
      Expense expense = expenses[share.getExpenseId()];
      Group group = groups[expense.getGroupId()];
      cout << "Group Name: " << group.getName() << ", Expense Name: " << expense.getName() << ", User Name: " << users[share.getUserId()].getName() << ", Owed: " << share.getOwedShare() << ", Paid: " << share.getPaidShare() << endl;
    }
  }

  void printUsersInGroup(int groupId) {
    for (const auto &[id, groupMember] : groupMembers) {
      if (groupMember.getGroupId() == groupId) {
        cout << "User ID: " << groupMember.getUserId();
        for (auto &[userid, user] : users) {
          if (user.getId() == groupMember.getUserId()) {
            cout << ", Name: " << user.getName();
            break;
          }
        }
        cout << endl;
      }
    }
  }

  void printUsersGroupRepaymentBalances(int userId, int groupId) {
    vector<Repayment> repayments = getGroupRepaymentBalances(groupId);
    vector<Repayment> userFilteredRepayments;
    for (auto repayment : repayments) {
      if (repayment.from_userId == userId || repayment.to_userId == userId) {
        userFilteredRepayments.push_back(repayment);
      }
    }
    printRepayments(userFilteredRepayments);
  }

  void printAllSimplifiedGroupRepaymentBalances() {
    for (const auto &[groupId, group] : groups) {
      vector<pair<int, double>> creditors;
      vector<pair<int, double>> debtors;

      for (const auto &[id, groupMemberBalance] : groupMemberBalances) {
        if (groupMembers[groupMemberBalance.getGroupMemberId()].getGroupId() == groupId) {
          if (groupMemberBalance.getAmount() > 0) {
            creditors.push_back({groupMembers[groupMemberBalance.getGroupMemberId()].getUserId(), groupMemberBalance.getAmount()});
          } else {
            debtors.push_back({groupMembers[groupMemberBalance.getGroupMemberId()].getUserId(), groupMemberBalance.getAmount()});
          }
        }
      }

      vector<Repayment> repayments = generateSimplifiedDebts(creditors, debtors);

      cout << "Group Name: " << group.getName() << endl;
      printRepayments(repayments);
    }
  }

  void printAllFriendShipsRepayments() {
    vector<Repayment> repayments;
    for (const auto &[balanceId, balance] : friendShipBalances) {
      FriendShip friendShip = friendShips[balance.getFriendShipId()];
      if (balance.getAmount() > 0) {
        repayments.push_back({friendShip.getFromUserId(), friendShip.getToUserId(), balance.getAmount()});
      } else if (balance.getAmount() < 0) {
        repayments.push_back({friendShip.getToUserId(), friendShip.getFromUserId(), -balance.getAmount()});
      }
    }
    printRepayments(repayments);
  }

  void printRepaymentsBetweenFriends(int fromUserId, int toUserId) {
    vector<Repayment> repayments = getRepaymentsBetweenFriends(fromUserId, toUserId);
    if (repayments.empty()) {
      cout << "No repayments between " << users[fromUserId].getName() << " and " << users[toUserId].getName() << endl;
      return;
    }
    printRepayments(repayments);
  }

  // Similarly, you can add print methods for other entities if needed.
};

#endif
