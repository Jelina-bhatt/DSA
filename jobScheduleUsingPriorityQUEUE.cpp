#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    string name;
    int priority;
    int burstTime;

    Job(string n, int p, int b) : name(n), priority(p), burstTime(b) {}
};

bool compare(Job a, Job b) {
    return a.priority > b.priority;
}

class JobScheduler {
    vector<Job> jobs;

public:
    void addJob(string name, int priority, int burstTime) {
        jobs.push_back(Job(name, priority, burstTime));
        sort(jobs.begin(), jobs.end(), compare);
    }

    void runNextJob() {
        if (jobs.empty()) {
            cout << "No jobs to run.\n";
            return;
        }

        Job job = jobs[0];
        cout << "Running job: " << job.name << " with priority " << job.priority << " and burst time " << job.burstTime << "ms\n";
        jobs.erase(jobs.begin());
    }

    void showJobs() {
        cout << "Current Job Queue:\n";
        for (auto j : jobs) {
            cout << " - " << j.name << " | Priority: " << j.priority << " | Burst Time: " << j.burstTime << "ms\n";
        }
    }
};

int main() {
    JobScheduler scheduler;
    scheduler.addJob("Job1", 3, 20);
    scheduler.addJob("Job2", 5, 10);
    scheduler.addJob("Job3", 1, 30);

    scheduler.showJobs();
    scheduler.runNextJob();
    scheduler.showJobs();

    return 0;
}
