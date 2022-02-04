#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

enum EventType{wake, sleep, guard_change};

struct Event{
    int year;
    int month;
    int day;
    int hour;
    int minutes;

    EventType event;
    int guard;
};

ifstream& operator>>(ifstream& input, Event& t ){
    char c;
    input >> c;
    input>>t.year;
    input>>c;
    input>>t.month;
    input >> c;
    input>>t.day;
    input>>t.hour;
    input >> c;
    input>>t.minutes;
    input >> c;
    string s;
    input >> s;
    if( s=="Guard"){
        t.event=guard_change;
        input >> c;
        input >> t.guard;
        input >> s;
    }else if(s=="wakes"){
        t.event=wake;
    } else {
        t.event = sleep;
    }
    input >> s;
    return input;
}

bool operator<(const Event& t1, const Event& t2){
    if(t1.year!=t2.year) return t1.year<t2.year;
    if(t1.month!=t2.month) return t1.month<t2.month;
    if(t1.day!=t2.day) return t1.day<t2.day;
    if(t1.hour!=t2.hour) return t1.hour<t2.hour;
    if(t1.minutes<t2.minutes) return t1.minutes<t2.minutes;
    return t1.event==guard_change;
}

bool operator==(const Event& t1, const Event& t2){
    return  t1.year==t2.year && t1.month==t2.month && t1.day==t2.day
            && t1.hour==t2.hour && t1.minutes==t2.minutes;
}

void part_1(){
    ifstream input;
    input.open("input.txt");
    set<Event> events;
    map<int,int> guards_time_asleep;
    Event e;
    input >> e;
    while(input){
        events.insert(e);
//        cout << e.hour << ":" << e.minutes << endl;

        input >> e;
    }
    int current_guard;
    int sleep_start;
    for( auto e:events){
        if(e.event==guard_change){
            current_guard = e.guard;
        } else if(e.event==sleep){
            sleep_start=e.minutes;
        } else {

            if(guards_time_asleep.count(current_guard)){
                guards_time_asleep[current_guard] += e.minutes-sleep_start;
            } else {
                guards_time_asleep[current_guard] = e.minutes-sleep_start;
            }

            if(current_guard==3109){
                cout <<sleep_start<< " to " << e.minutes << endl;
                cout << "Total time: " << guards_time_asleep[3109] << endl;
            }
        }
    }
    int max_sleep = 0;
    int max_sleep_guard;
    for(auto g:guards_time_asleep){
        if( (g.second) >max_sleep){
            max_sleep= g.second;
            max_sleep_guard = g.first;
        }
    }

    int min_asleep [60] = {0};

    for( auto e:events){
        if(e.event==guard_change){
            current_guard = e.guard;
        } else if(e.event==sleep&&current_guard==max_sleep_guard){
            sleep_start=e.minutes;
        } else if(current_guard==max_sleep_guard){
            for(int i=sleep_start; i<e.minutes;i++){
                min_asleep[i]++;
            }
        }
    }
    int max_minute_minutes=0;
    int max_minute;
    for(int minute=0; minute<60; minute++ ){
        if(min_asleep[minute]>max_minute_minutes){
            max_minute=minute;
            max_minute_minutes=min_asleep[minute];
        }
    }
    cout << "The answer to part 1 is: " << max_minute*max_sleep_guard << endl;
}

int max_minute_slept(set<Event> events, int guard_id){

}

void part_2(){
    ifstream input;
    input.open("input.txt");
    set<Event> events;

    Event e;
    input >> e;
    int next_id = 0;
    vector<int> guards;
    map<int,int> guard_ids;
    while(input){
        events.insert(e);
//        cout << e.hour << ":" << e.minutes << endl;
        if(e.event==guard_change){
            if( guard_ids.count(e.guard)==0){
                guards.push_back(e.guard);
                guard_ids[e.guard]=next_id;
                next_id++;
            }
        }
        input >> e;
    }
    map<int,int> guard_minute_minutes;
    int current_guard;
    int sleep_start;
    for( auto e:events){
        if(e.event==guard_change){
            current_guard = e.guard;
        } else if(e.event==sleep){
            sleep_start=e.minutes;
        } else {
            for(int i=current_guard*100+sleep_start; i<100*current_guard+e.minutes; i++ )
            if(guard_minute_minutes.count(i)){
                guard_minute_minutes[i] += 1;
            } else {
                guard_minute_minutes[i] = 1;
            }
        }
    }

    int max_minutes=0;
    int weird_index;

    for( auto g:guard_minute_minutes){
        if(g.second>max_minutes){
            max_minutes=g.second;
            weird_index=g.first;
        }
    }

    cout << "The answer to part 2 is: " << (weird_index/100)*(weird_index%100) << endl;
}

int main()
{
    part_2();
    return 0;
}
