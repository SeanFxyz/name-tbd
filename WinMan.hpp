#pragma once
#include "Win.hpp"
#include "Observer.hpp"

using namespace std;

class WinMan: public Observer {
public:
    void add_win(Win *win) {
        win->add_observer(this, "set_z");
        insert_win(win);
    }
    void remove_win(Win *win) {
        win->remove_observer(this, "set_z");// Finish this

    }
    virtual void on_notify(Subject *the_subject, string the_event) {
        if (the_event == "set_z") {
            vector<Win*>::iterator it = find_win((Win*)(the_subject));
            if (it == windows.end()) cerr << "Subject window not found in window list" << endl;
            Win *tmp = *it;
            windows.erase(it);
            auto tmp_z = tmp->get_z();
            insert_win(tmp);
        }
    }
    void draw() {
        wnoutrefresh(stdscr);
        for (Win *w : windows) {
            //werase(w->get_window());
            wnoutrefresh(w->get_window());
        }
        doupdate();
    }
private:
    void insert_win(Win *win) {
        if (windows.empty()) {
            windows.push_back(win);
        } else {
            vector<Win*>::iterator it = windows.begin();
            auto getz = (*it)->get_z();
            while (it != windows.end() && (*it)->get_z() < win->get_z())
                it++;
            if ((*it)->get_z() >= win->get_z()) {
                windows.insert(it, win);
            } else {
                windows.push_back(win);
            }
        }
        for (auto window : windows) {
            cerr << window << "; ";
        }
        cerr << endl;
    }
    vector<Win*>::iterator find_win(Win *win) {
        vector<Win*>::iterator it;
        for (it = windows.begin(); it != windows.end(); it++) {
            if (static_cast<Win*>(*it) == win) {
                return it;
            }
        }
        return it;
    }
    vector<Win*> windows;
};
