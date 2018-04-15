#include "alarm.h"
#include <QSqlError>
#include <QSqlQuery>
#include "connection.h"
#include <QDateTime>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
Alarm::Alarm(QWidget* parent):QWidget(parent){
    treeWidget = new QTreeWidget(this);
    treeWidget->setStyleSheet("background-color:rgb(52, 101, 164)");
    QStringList headers;
    headers<<"ID"<<"Description"<<"Status"<<"Time";
    treeWidget->setHeaderLabels(headers);
    tool_bar = new QWidget(this);
//    tool_bar->setStyleSheet("background-color:rgb(52, 101, 164)");
    cut_out = new QPushButton("CUT-OUT", tool_bar);
    cut_out->setStyleSheet("background-color:rgb(52, 101, 164)");
    active = new QPushButton("RE-active", tool_bar);
    active->setStyleSheet("background-color:rgb(52, 101, 164)");
    info = new QPushButton("Info", tool_bar);
    info->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_up = new QPushButton("Page-up", tool_bar);
    page_up->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_down = new QPushButton("Page-down", tool_bar);
    page_down->setStyleSheet("background-color:rgb(52, 101, 164)");
    tool_layout = new QHBoxLayout;
    tool_layout->addWidget(cut_out, 0, Qt::AlignLeft);
    tool_layout->addWidget(active, 0, Qt::AlignLeft);
    tool_layout->addWidget(info, 0, Qt::AlignLeft);
    tool_layout->addWidget(page_up, 0, Qt::AlignLeft);
    tool_layout->addWidget(page_down, 0, Qt::AlignLeft);
    QSpacerItem* s1 = new QSpacerItem( 1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    tool_layout->addItem(s1);
    layout = new QVBoxLayout;
    layout->addWidget(treeWidget);
    layout->addLayout(tool_layout, 0);
    setLayout(layout);
//    setStyleSheet("background-color:rgb(52, 101, 164)");

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    update_datebase();
    connect(cut_out, &QPushButton::clicked, this, &Alarm::cutout);
    connect(active, &QPushButton::clicked, this, &Alarm::un_cutout);
    connect(info, &QPushButton::clicked, this, &Alarm::information);
}

void Alarm::information(){
    QList<QTreeWidgetItem*> target_list = treeWidget->selectedItems();
    if(target_list.size() != 1){
        QMessageBox::critical(nullptr, "selected error:", "you can not select lots of item's to get the info, please try again");
        return;
    }
    for(QTreeWidgetItem* p : target_list){
        QSqlQuery query;
        if(!query.exec("select alarm_id, description, cause, effect, action from alarm where alarm_id =" + p->text(0) + ";")){
            QMessageBox::critical(nullptr, "exec sql Error:", "select alarm_id, description, cause, effect, action from alarm where alarm_id =" + p->text(0) + ";" + query.lastError().text());
            return;
        }
        if(query.next()){
            QMessageBox::information(nullptr, "alarm", "alarm_id: "+query.value(0).toString()+"\ndescription: "+query.value(1).toString()+"\ncause: "+query.value(2).toString()+"\neffect: "+ query.value(3).toString()+"\naction: "+query.value(4).toString());
        }
    }
}

void Alarm::cutout(){
    QList<QTreeWidgetItem*> target_list = treeWidget->selectedItems();
    for(QTreeWidgetItem* p : target_list){
        QSqlQuery query;
        if(!query.exec("update alarm set status = 0 where alarm_id = " + p->text(0) + ";")){
            QMessageBox::critical(nullptr, "exec sql Error:", "update alarm set status = 0 where alarm_id = " + p->text(0) + ";" + query.lastError().text());
            return;
        }
        p->setText(2, "cut-out");
        p->setText(3, QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        set_row_color(p, "gray");
        int x = p->text(0).toInt();
        event_log(7, "alarm id is "+p->text(0));
        emit cut_out_(x);
    }
}
void Alarm::un_cutout(){
    QList<QTreeWidgetItem*> target_list = treeWidget->selectedItems();
    for(QTreeWidgetItem* p : target_list){
        QSqlQuery query;
        if(!query.exec("update alarm set status = 1 where alarm_id = " + p->text(0) + ";")){
            QMessageBox::critical(nullptr, "exec sql Error:", "update alarm set status = 1 where alarm_id = " + p->text(0) + ";" + query.lastError().text());
            return;
        }
        p->setText(2, "normal");
        p->setText(3, QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        set_row_color(p, "green");
        event_log(6, "alarm id is "+p->text(0));
        emit re_active(p->text(0).toInt());
    }
}

void Alarm::update_datebase(){
    for(QTreeWidgetItem* p : list)
        p->~QTreeWidgetItem();
    list.clear();
    if(!list.isEmpty()){
        QMessageBox::critical(nullptr, "alarm update_datebase error", "list in not empty");
        return;
    }
    QSqlQuery query;
    if(!query.exec("select alarm_id, description, status from alarm;")){
        QMessageBox::critical(nullptr, "exec sql Error:", "select alarm_id, description, status from alarm;\n" + query.lastError().text());
        return;
    }
    while(query.next()){
        event_log(15, "the alarm id is " + query.value(0).toString() + " and the description is " + query.value(1).toString());
        QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
        item->setText(0, query.value(0).toString());
        item->setText(1, query.value(1).toString());
        item->setText(2, query.value(2).toInt() == 1 ? "nomal" : "cut-out");
        item->setText(3, QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        if(query.value(2).toInt() == 1)
            set_row_color(item, "green");
        else
            set_row_color(item, "gray");
        list.append(item);
    }
}
