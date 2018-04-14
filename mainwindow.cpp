#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :QWidget{parent}{
    navigation = new Navigation(this);
    now = alarm_list = new Alarm_list(this);
    alarm = new Alarm(this);
    alarm->hide();
    event_log = new Event_log(this);
    event_log->hide();
    channel = new Channel(this);
    channel->hide();
    layout = new QHBoxLayout;
    layout->addWidget(alarm_list);
    layout->addWidget(navigation);
    setLayout(layout);
//    setWindowFlags(windowFlags() & Qt::WindowMaximizeButtonHint & Qt::WindowMinimizeButtonHint);
    connect(navigation, &Navigation::show_alarm_list, this, &MainWindow::set_alarm_list);
    connect(navigation, &Navigation::show_alarm, this, &MainWindow::set_alarm);
    connect(navigation, &Navigation::show_event_log, this, &MainWindow::set_event_log);
    connect(navigation, &Navigation::show_channel, this, &MainWindow::set_channel);
    connect(alarm, &Alarm::cut_out_, alarm_list, &Alarm_list::not_available);
    connect(alarm, &Alarm::re_active, alarm_list, &Alarm_list::not_available);
    showFullScreen();
}

MainWindow::~MainWindow()
{
}

void MainWindow::set_alarm_list(bool tag){
    if(!tag)
        return;
    if(now == alarm_list)
        return;
    layout->replaceWidget(now, alarm_list);
    alarm_list->show();
    now->hide();
    now = alarm_list;
}

void MainWindow::set_alarm(bool tag){
    if(!tag)
        return;
    if(now == alarm)
        return;
    layout->replaceWidget(now, alarm);
    alarm->show();
    now->hide();
    now = alarm;
}

void MainWindow::set_event_log(bool tag){
    if(!tag)
        return;
    if(now == event_log)
        return;
    layout->replaceWidget(now, event_log);
    event_log->show();
    now->hide();
    now = event_log;
}

void MainWindow::set_channel(bool tag){
    if(!tag)
        return;
    if(now == channel)
        return;
    layout->replaceWidget(now, channel);
    channel->show();
    now->hide();
    now = channel;
}
