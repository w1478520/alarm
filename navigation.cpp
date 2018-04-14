#include "navigation.h"
#include "ui_navigation.h"

Navigation::Navigation(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    layout()->setSizeConstraint(QLayout::SetNoConstraint);
    alarm_layout_hide();
    engine_layout_hide();
    auxiliary_layout_hide();
    maintenance_layout_hide();
    QObject::connect(alarm_button, SIGNAL(toggled(bool)),this, SLOT(alarm_layout_toggle(bool)));
    QObject::connect(engine_button, SIGNAL(toggled(bool)),this, SLOT(engine_layout_toggle(bool)));
    QObject::connect(auxiliary_button, SIGNAL(toggled(bool)),this, SLOT(auxiliary_layout_toggle(bool)));
    QObject::connect(maintenance_button, SIGNAL(toggled(bool)),this, SLOT(maintenance_layout_toggle(bool)));
    QObject::connect(alarm_list_button, SIGNAL(toggled(bool)),this, SLOT(alarm_list_button_toggle(bool)));
    QObject::connect(event_log_button, SIGNAL(toggled(bool)),this, SLOT(event_log_button_toggle(bool)));
    QObject::connect(manual_button, SIGNAL(toggled(bool)),this, SLOT(manual_button_toggle(bool)));
    QObject::connect(channel_button, SIGNAL(toggled(bool)),this, SLOT(channel_button_toggle(bool)));
    QObject::connect(engine1_button, SIGNAL(toggled(bool)),this, SLOT(engine1_button_toggle(bool)));
    QObject::connect(engine2_button, SIGNAL(toggled(bool)),this, SLOT(engine2_button_toggle(bool)));
    QObject::connect(engine3_button, SIGNAL(toggled(bool)),this, SLOT(engine3_button_toggle(bool)));
    QObject::connect(engine4_button, SIGNAL(toggled(bool)),this, SLOT(engine4_button_toggle(bool)));
    QObject::connect(auxiliary1_button, SIGNAL(toggled(bool)),this, SLOT(auxiliary1_button_toggle(bool)));
    QObject::connect(auxiliary2_button, SIGNAL(toggled(bool)),this, SLOT(auxiliary2_button_toggle(bool)));
    QObject::connect(auxiliary3_button, SIGNAL(toggled(bool)),this, SLOT(auxiliary3_button_toggle(bool)));
    QObject::connect(auxiliary4_button, SIGNAL(toggled(bool)),this, SLOT(auxiliary4_button_toggle(bool)));
    QObject::connect(maintenance1_button, SIGNAL(toggled(bool)),this, SLOT(maintenance1_button_toggle(bool)));
    QObject::connect(maintenance2_button, SIGNAL(toggled(bool)),this, SLOT(maintenance2_button_toggle(bool)));
    QObject::connect(maintenance3_button, SIGNAL(toggled(bool)),this, SLOT(maintenance3_button_toggle(bool)));
    QObject::connect(maintenance4_button, SIGNAL(toggled(bool)),this, SLOT(maintenance4_button_toggle(bool)));

    buttons[0] = alarm_list_button;
    buttons[1] = event_log_button;
    buttons[2] = manual_button;
    buttons[3] = channel_button;
    buttons[4] = engine1_button;
    buttons[5] = engine2_button;
    buttons[6] = engine3_button;
    buttons[7] = engine4_button;
    buttons[8] = auxiliary1_button;
    buttons[9] = auxiliary2_button;
    buttons[10] = auxiliary3_button;
    buttons[11] = auxiliary4_button;
    buttons[12] = maintenance1_button;
    buttons[13] = maintenance2_button;
    buttons[14] = maintenance3_button;
    buttons[15] = maintenance4_button;
    connect(alarm_list_button, &QPushButton::toggled, this, &Navigation::show_alarm_list);
    connect(manual_button, &QPushButton::toggled, this, &Navigation::show_alarm);
    connect(event_log_button, &QPushButton::toggled, this, &Navigation::show_event_log);
    connect(channel_button, &QPushButton::toggled, this, &Navigation::show_channel);
}

void Navigation::alarm_layout_hide(){
    alarm_list_button->hide();
    channel_button->hide();
    event_log_button->hide();
    manual_button->hide();
}
void Navigation::alarm_layout_show(){
    alarm_list_button->show();
    channel_button->show();
    event_log_button->show();
    manual_button->show();
}
void Navigation::alarm_layout_toggle(bool){
    if( alarm_button->isChecked() ){
        alarm_layout_show();
        auxiliary_button->setChecked(false);
        engine_button->setChecked(false);
        maintenance_button->setChecked(false);
    }
    else
        alarm_layout_hide();
}
void Navigation::engine_layout_toggle(bool){
    if( engine_button->isChecked() ){
        engine_layout_show();
        auxiliary_button->setChecked(false);
        alarm_button->setChecked(false);
        maintenance_button->setChecked(false);
    }
    else
        engine_layout_hide();
}
void Navigation::auxiliary_layout_toggle(bool){
    if( auxiliary_button->isChecked() ){
        auxiliary_layout_show();
        alarm_button->setChecked(false);
        engine_button->setChecked(false);
        maintenance_button->setChecked(false);
    }
    else
        auxiliary_layout_hide();
}
void Navigation::maintenance_layout_toggle(bool){
    if( maintenance_button->isChecked() ){
        maintenance_layout_show();
        auxiliary_button->setChecked(false);
        engine_button->setChecked(false);
        alarm_button->setChecked(false);
    }
    else
        maintenance_layout_hide();
}

void Navigation::engine_layout_hide(){
    engine1_button->hide();
    engine2_button->hide();
    engine3_button->hide();
    engine4_button->hide();
}
void Navigation::engine_layout_show(){
    engine1_button->show();
    engine2_button->show();
    engine3_button->show();
    engine4_button->show();
}
void Navigation::auxiliary_layout_show(){
    auxiliary1_button->show();
    auxiliary2_button->show();
    auxiliary3_button->show();
    auxiliary4_button->show();
}
void Navigation::auxiliary_layout_hide(){
    auxiliary1_button->hide();
    auxiliary2_button->hide();
    auxiliary3_button->hide();
    auxiliary4_button->hide();
}
void Navigation::maintenance_layout_hide(){
    maintenance1_button->hide();
    maintenance2_button->hide();
    maintenance3_button->hide();
    maintenance4_button->hide();
}
void Navigation::maintenance_layout_show(){
    maintenance1_button->show();
    maintenance2_button->show();
    maintenance3_button->show();
    maintenance4_button->show();
}

void Navigation::button_toggle(QPushButton* target){
    for(int i=0; i<button_number; i++){
        if(buttons[i] == target){
            ;
        }
        else{
            buttons[i]->setChecked(false);
        }
    }
}

void Navigation::alarm_list_button_toggle(bool){
    if( alarm_list_button->isChecked() ){
        button_toggle(alarm_list_button);
    }
    else{
        ;
    }
}
void Navigation::event_log_button_toggle(bool){
    if( event_log_button->isChecked() )
        button_toggle(event_log_button);
    else{
        ;
    }
}
void Navigation::manual_button_toggle(bool){
    if( manual_button->isChecked() )
        button_toggle(manual_button);
    else{
        ;
    }
}
void Navigation::channel_button_toggle(bool){
    if( channel_button->isChecked() )
        button_toggle(channel_button);
    else{
        ;
    }
}
void Navigation::engine1_button_toggle(bool){
    if( engine1_button->isChecked() )
        button_toggle(engine1_button);
    else{
        ;
    }
}
void Navigation::engine2_button_toggle(bool){
    if( engine2_button->isChecked() )
        button_toggle(engine2_button);
    else{
        ;
    }
}
void Navigation::engine3_button_toggle(bool){
    if( engine3_button->isChecked() )
        button_toggle(engine3_button);
    else{
        ;
    }
}
void Navigation::engine4_button_toggle(bool){
    if( engine4_button->isChecked() )
        button_toggle(engine4_button);
    else{
        ;
    }
}
void Navigation::auxiliary1_button_toggle(bool){
    if( auxiliary1_button->isChecked() )
        button_toggle(auxiliary1_button);
    else{
        ;
    }
}
void Navigation::auxiliary2_button_toggle(bool){
    if( auxiliary2_button->isChecked() )
        button_toggle(auxiliary2_button);
    else{
        ;
    }
}
void Navigation::auxiliary3_button_toggle(bool){
    if( auxiliary3_button->isChecked() )
        button_toggle(auxiliary3_button);
    else{
        ;
    }
}
void Navigation::auxiliary4_button_toggle(bool){
    if( auxiliary4_button->isChecked() )
        button_toggle(auxiliary4_button);
    else{
        ;
    }
}
void Navigation::maintenance1_button_toggle(bool){
    if( maintenance1_button->isChecked() )
        button_toggle(maintenance1_button);
    else{
        ;
    }
}
void Navigation::maintenance2_button_toggle(bool){
    if( maintenance2_button->isChecked() )
        button_toggle(maintenance2_button);
    else{
        ;
    }
}
void Navigation::maintenance3_button_toggle(bool){
    if( maintenance3_button->isChecked() )
        button_toggle(maintenance3_button);
    else{
        ;
    }
}
void Navigation::maintenance4_button_toggle(bool){
    if( maintenance4_button->isChecked() )
        button_toggle(maintenance4_button);
    else{
        ;
    }
}


Navigation::~Navigation()
{
}
