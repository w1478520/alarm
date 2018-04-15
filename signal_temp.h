#ifndef SIGNAL_TEMP_H
#define SIGNAL_TEMP_H
#include <QObject>
class Signal_temp: public QObject {
    Q_OBJECT
public:
    Signal_temp();
    ~Signal_temp();
signals:
    void notify_event_log();
};


#endif // SIGNAL_TEMP_H
