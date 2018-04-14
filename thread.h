#ifndef THREAD_H
#define THREAD_H
#include <QThread>

class Thread:public QThread {
    Q_OBJECT
signals:
    void alarm_modify(int);
    void alarm_occur(int);
    void channel_in(int);
    void test_signal(int);
    void close_signal(int);
    void remove_channel(int);
protected:
    void run();
};


#endif // THREAD_H
