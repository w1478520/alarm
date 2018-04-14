#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "ui_navigation.h"
#include <QWidget>
#include <QDialog>
#include <QPushButton>
namespace Ui {
class Navigation;
}

class Navigation : public QWidget, public Ui_navigation
{
    Q_OBJECT

public:
    explicit Navigation(QWidget *parent = 0);
    ~Navigation();

private slots:
    void alarm_layout_toggle(bool);
    void engine_layout_toggle(bool);
    void auxiliary_layout_toggle(bool);
    void maintenance_layout_toggle(bool);
    void alarm_list_button_toggle(bool);
    void event_log_button_toggle(bool);
    void manual_button_toggle(bool);
    void channel_button_toggle(bool);
    void engine1_button_toggle(bool);
    void engine2_button_toggle(bool);
    void engine3_button_toggle(bool);
    void engine4_button_toggle(bool);
    void auxiliary1_button_toggle(bool);
    void auxiliary2_button_toggle(bool);
    void auxiliary3_button_toggle(bool);
    void auxiliary4_button_toggle(bool);
    void maintenance1_button_toggle(bool);
    void maintenance2_button_toggle(bool);
    void maintenance3_button_toggle(bool);
    void maintenance4_button_toggle(bool);
signals:
    void show_alarm_list(bool);
    void show_alarm(bool);
    void show_event_log(bool);
    void show_channel(bool);
private:
    void alarm_layout_hide();
    void alarm_layout_show();
    void engine_layout_hide();
    void engine_layout_show();
    void auxiliary_layout_show();
    void auxiliary_layout_hide();
    void maintenance_layout_hide();
    void maintenance_layout_show();
    void button_toggle(QPushButton*);
    int button_number = 16;
    QPushButton* buttons[16];
};

#endif // NAVIGATION_H
