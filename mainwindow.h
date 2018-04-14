#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "alarm_list.h"
#include "navigation.h"
#include "alarm.h"
#include "event_log.h"
#include "channel.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Alarm_list* alarm_list;
    Alarm* alarm;
    Event_log* event_log;
    Channel* channel;
    Navigation* navigation;
    QHBoxLayout* layout;
    QWidget* now;

    void set_alarm_list(bool);
    void set_alarm(bool);
    void set_event_log(bool);
    void set_channel(bool);
};

#endif // MAINWINDOW_H
