#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Task structure
struct Task {
    string description;
    bool completed;
};

// Function to load tasks from file
vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream file("tasks.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string desc;
        int completed;
        iss >> completed;
        getline(iss, desc);
        tasks.push_back({desc, static_cast<bool>(completed)});
    }
    file.close();
    return tasks;
}

// Function to save tasks to file
void saveTasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task.completed << " " << task.description << endl;
    }
    file.close();
}

// Function to display tasks
void showTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks found!\n";
        return;
    }
    cout << "\nTo-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << (tasks[i].completed ? "[✔] " : "[ ] ") << i + 1 << ". " << tasks[i].description << endl;
    }
}

// Function to add a task
void addTask(vector<Task>& tasks) {
    cout << "Enter task description: ";
    cin.ignore();
    string desc;
    getline(cin, desc);
    tasks.push_back({desc, false});
    saveTasks(tasks);
    cout << "Task added successfully!\n";
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    showTasks(tasks);
    if (tasks.empty()) return;

    cout << "Enter task number to mark as completed: ";
    int num;
    cin >> num;

    if (num > 0 && num <= (int)tasks.size()) {
        tasks[num - 1].completed = true;
        saveTasks(tasks);
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

// Function to delete a task
void deleteTask(vector<Task>& tasks) {
    showTasks(tasks);
    if (tasks.empty()) return;

    cout << "Enter task number to delete: ";
    int num;
    cin >> num;

    if (num > 0 && num <= (int)tasks.size()) {
        tasks.erase(tasks.begin() + num - 1);
        saveTasks(tasks);
        cout << "Task deleted successfully!\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

int main() {
    vector<Task> tasks = loadTasks();
    int choice;

    do {
        cout << "\n===== To-Do List Manager =====\n";
        cout << "1. View Tasks\n2. Add Task\n3. Mark Task as Completed\n4. Delete Task\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: showTasks(tasks); break;
            case 2: addTask(tasks); break;
            case 3: markTaskCompleted(tasks); break;
            case 4: deleteTask(tasks); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
