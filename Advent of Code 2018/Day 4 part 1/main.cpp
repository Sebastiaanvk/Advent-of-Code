#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

enum What{new_guard, fall_asleep, wake_up};

struct Event
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;

    What what;
    int id;
};

ifstream& operator>>(ifstream& inputfile, Event& event)
{
    //pre-cond:
    assert(true);
    //post-cond:
    //inputfile has been read up to and including all members of one Event entry, including the last separating newline.
    //These members are stored in event.
    char c;
    string str;
    inputfile >>c >> event.year >> c>> event.month >> c >> event.day;
    inputfile >> event.hour >> c >> event.minutes >> c;
    inputfile >> str;
    event.id = 0;
    if(str=="Guard")
    {
        event.what = new_guard;
        inputfile >> c >> event.id;
    }
    else if(str=="wakes")
        event.what = wake_up;
    else
        event.what = fall_asleep;
    getline(inputfile, str);
    return inputfile;
}

bool operator<(const Event& a, const Event& b)
{
    if(a.year==b.year)
    {
        if(a.month==b.month)
        {
            if(a.day==b.day)
            {
                if(a.hour==b.hour)
                    return a.minutes<b.minutes;
                return a.hour<b.hour;
            }
            return a.day<b.day;
        }
        return a.month<b.month;
    }
    return a.year<b.year;
}

bool operator==(const Event& a, const Event& b)
{
    return a.year==b.year&&a.month==b.month&&a.day==b.day&&a.hour==b.hour&&a.minutes&&b.minutes;
}

//	derived ordering on Event values:
bool operator>(const Event& a, const Event& b)
{
	return b < a ;
}

bool operator<=(const Event& a, const Event& b)
{
	return !(b < a) ;
}

bool operator>=(const Event& a, const Event& b)
{
	return b <= a ;
}

void display_event(Event& event)
{
    cout << "Moment: "<< event.year << " " << event.month << " " << event.day << " " << event.hour << " " << event.minutes << endl;
    switch(event.what)
    {
        case new_guard: cout << "New guard";break;
        case fall_asleep: cout << "Falls asleep";break;
        case wake_up: cout << "Wakes up"; break;
    }
    cout << " id: " << event.id << endl;
}



void read_input(vector<Event>& events)
{
    //pre-cond:
    assert(true);
    //post-cond:
    //opens the inputfile with name "AoC4.txt" and reads and saves the entries as Event to the vector events
    ifstream inputfile;
    inputfile.open("AoC4.txt");
    Event event;
    inputfile >> event;
    while(inputfile)
    {
        events.push_back(event);
        inputfile >> event;
    }
}

int main()
{
    vector<Event> events;
    read_input(events);
    display_event(events[0]);
    display_event(events[2]);
    display_event(events[15]);
    return 0;
}
