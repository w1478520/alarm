#include "alarm_list.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlError>
#include "connection.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
Alarm_list::Alarm_list(QWidget* parent):QWidget(parent){
    treeWidget = new QTreeWidget(this);
    treeWidget->setStyleSheet("background-color:rgb(52, 101, 164)");
    QStringList headers;
    headers<<"Ack"<<"Description"<<"Status"<<"ID"<<"Time";
    treeWidget->setHeaderLabels(headers);
    tool_bar = new QWidget(this);
    ack_button = new QPushButton("ACK", tool_bar);
    ack_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    ack_all_button = new QPushButton("ACK ALL", tool_bar);
    ack_all_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    info = new QPushButton("Info", tool_bar);
    info->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_up = new QPushButton("Page-up", tool_bar);
    page_up->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_down = new QPushButton("Page-down", tool_bar);
    page_down->setStyleSheet("background-color:rgb(52, 101, 164)");
    QHBoxLayout* tool_layout = new QHBoxLayout;
    tool_layout->addWidget(ack_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(ack_all_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(info, 0, Qt::AlignLeft);
    tool_layout->addWidget(page_up, 0, Qt::AlignLeft);
    tool_layout->addWidget(page_down, 0, Qt::AlignLeft);
    QSpacerItem* s1 = new QSpacerItem( 1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    tool_layout->addItem(s1);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(treeWidget);
    layout->addLayout(tool_layout, 0);
    setLayout(layout);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(ack_button, &QPushButton::clicked, this, &Alarm_list::ack);
    connect(ack_all_button, &QPushButton::clicked, this, &Alarm_list::ack_all);
    connect(info, &QPushButton::clicked, this, &Alarm_list::information);
}
void Alarm_list::insert_data(int id){
    QSqlQuery query;
    qDebug()<<id;
    if(!query.exec("select alarm_id, ack, status, time from alarm_list where id = " + QString::number(id, 10) + ";")){
        QMessageBox::critical(nullptr, "exec sql Error:",
                              "select alarm_id, ack, status, time from alarm_list where id = " + QString::number(id, 10) + ";"
                              + "\n" + query.lastError().text());
        return;
    }
    int alarm_id;
    int ack;
    int status;
    QString time;
    QString description;

    if(query.next()){
        alarm_id = query.value(0).toInt();
        ack = query.value(1).toInt();
        status = query.value(2).toInt();
        time = query.value(3).toString();
    }
    QString status_string;
    if(status == 1)
        status_string = "Normal";
    else if(status == 2)
        status_string = "Alarm";
    else if(status == 3)
        status_string = "Low";
    else if(status == 4)
        status_string = "High";
    else if(status == 5)
        status_string = "Not Available";
    else
        QMessageBox::critical(nullptr, "select sql status Error:", "int alarm_list.cpp insert_data\n"+query.lastError().text());
    QSqlQuery query1;

    if(!query1.exec("select description from alarm where alarm_id = " + QString::number(alarm_id, 10) + ";")){
        QMessageBox::critical(nullptr, "exec sql Error:",
                              "select description from alarm where alarm_id = " + QString::number(alarm_id, 10) + ";"
                              + "\n" + query.lastError().text());
        return;
    }
    if(query1.next()){
        description = query1.value(0).toString();
    }
    QString filename{"./picture/" + QString::number(ack,10) + ".png"};
    time[10] = ' ';
    QTreeWidgetItem* temp = new QTreeWidgetItem(treeWidget);
    temp->setIcon(0, QIcon(filename));
    temp->setText(1, description);
    temp->setText(2, status_string);
    temp->setText(3, QString::number(alarm_id,10));
    temp->setText(4, time);
    if(status==1)
        set_row_color(temp, "green");
    else
        set_row_color(temp, "red");
    treeWidget->sortItems(4, Qt::DescendingOrder);
}
void Alarm_list::update_data(int id){
    QSqlQuery query;
    if(!query.exec("select alarm_id, ack, status, time from alarm_list where id = " + QString::number(id, 10) + ";")){
        QMessageBox::critical(nullptr, "exec sql Error:",
                              "select alarm_id, ack, status, time from alarm_list where id = " + QString::number(id, 10) + ";"
                              + "\n" + query.lastError().text());
        return;
    }
    int alarm_id;
    int ack;
    int status;
    QString time;
    QString description;

    if(query.next()){
        alarm_id = query.value(0).toInt();
        ack = query.value(1).toInt();
        status = query.value(2).toInt();
        time = query.value(3).toString();
    }
    QDateTime now = QDateTime::fromString(time,"yyyy-MM-dd HH:mm:ss");
    QString status_string;
    if(status == 1)
        status_string = "Normal";
    else if(status == 2)
        status_string = "Alarm";
    else if(status == 3)
        status_string = "Low";
    else if(status == 4)
        status_string = "High";
    else if(status == 5)
        return;
    else
        QMessageBox::critical(nullptr, "select sql status Error:", "int alarm_list.cpp insert_data\n"+query.lastError().text());
    QSqlQuery query1;
    if(!query1.exec("select description from alarm where alarm_id = " + QString::number(alarm_id, 10) + ";")){
        QMessageBox::critical(nullptr, "exec sql Error:",
                              "select description from alarm where alarm_id = " + QString::number(alarm_id, 10) + ";"
                              + "\n" + query.lastError().text());
        return;
    }
    if(query1.next()){
        description = query1.value(0).toString();
    }
    QString filename{"picture/" + QString::number(ack,10) + ".png"};
    qint64 min=99999999;
    QTreeWidgetItem* temp;
    auto list_item = treeWidget->findItems(description, 0, 1);
    for(QTreeWidgetItem* a:list_item){
        QDateTime past = QDateTime::fromString(a->text(3),"yyyy-MM-dd HH:mm:ss");
        qint64 x = past.secsTo(now);
        if(x < min && a->text(2) != "Normal"){
            min = x;
            temp = a;
        }
    }
    time[10] = ' ';
    temp->setIcon(0, QIcon(filename));
    temp->setText(1, description);
    temp->setText(2, status_string);
    temp->setText(3, QString::number(alarm_id,10));
    temp->setText(4, time);
    set_row_color(temp, status==1?"green":"red");
    treeWidget->sortItems(4, Qt::DescendingOrder);
}
void Alarm_list::ack(){
    QList<QTreeWidgetItem*> target_list = treeWidget->selectedItems();
    if(target_list.size() != 1){
        QMessageBox::critical(nullptr, "selected error:", "you have to select one item, please try again");
        return;
    }
    for(QTreeWidgetItem* p:target_list){
        QSqlQuery query;
        if(!query.exec("select alarm_id, ack, status, time from alarm_list where alarm_id = " + p->text(3) + ";")){
            QMessageBox::critical(nullptr, "exec sql Error:",
                                  "select ack, status, time from alarm_list where alarm_id = " + p->text(3) + ";"
                                  + "\n" + query.lastError().text());
            return;
        }
        while(query.next()){
            QString time = query.value(3).toString();
            time[10] = ' ';
            if(p->text(4) == time && query.value(1).toString() == "1"){
                sql_exec("update alarm_list set ack = 5 where id=" + p->text(3) + ";");
                p->setIcon(0, QIcon("picture/5.png"));
                set_row_color(p, "yellow");
                event_log(8, "the alarm_id is "+ query.value(0).toString());
            }
        }
    }
}
void Alarm_list::ack_all(){
    event_log(9, "all alarm");
    QList<QTreeWidgetItem*> target_list = treeWidget->findItems("", Qt::MatchContains, 3);
    for(QTreeWidgetItem* p:target_list){
        QSqlQuery query;
        if(!query.exec("select alarm_id, ack, status, time from alarm_list where alarm_id = " + p->text(3) + ";")){
            QMessageBox::critical(nullptr, "exec sql Error:",
                                  "select ack, status, time from alarm_list where alarm_id = " + p->text(3) + ";"
                                  + "\n" + query.lastError().text());
            return;
        }
        while(query.next()){
            QString time = query.value(3).toString();
            time[10] = ' ';
            if(p->text(4) == time && query.value(1).toString() == "1"){
                sql_exec("update alarm_list set ack = 5 where id=" + p->text(3) + ";");
                p->setIcon(0, QIcon("picture/5.png"));
                set_row_color(p, "yellow");
            }
        }
    }
}
void Alarm_list::information(){
    QList<QTreeWidgetItem*> target_list = treeWidget->selectedItems();
    if(target_list.size() != 1){
        QMessageBox::critical(nullptr, "selected error:", "you can not select lots of item's to get the info, please try again");
        return;
    }

    for(QTreeWidgetItem* p : target_list){
        QSqlQuery query;
        if(!query.exec("select alarm_id, description, cause, effect, action from alarm where alarm_id =" + p->text(3) + ";")){
            QMessageBox::critical(nullptr, "exec sql Error:", "select alarm_id, description, cause, effect, action from alarm where alarm_id =" + p->text(3) + ";" + query.lastError().text());
            return;
        }
        if(query.next()){
            QMessageBox::information(nullptr, "alarm", "alarm_id: "+query.value(0).toString()+"\ndescription: "+query.value(1).toString()+"\ncause: "+query.value(2).toString()+"\neffect: "+ query.value(3).toString()+"\naction: "+query.value(4).toString());
        }
    }
}
void Alarm_list::not_available(int alarm_id){
    QSqlQuery query;
    query.exec("select status from alarm_list where alarm_id = " + QString::number(alarm_id, 10) + ";");
    while(query.next()){
        if(query.value(0).toInt() == 1){
            QSqlQuery query2;
            query2.exec("update alarm_list set ack = 6 where alarm_id = "+QString::number(alarm_id, 10)+";");
        }
        else{
            QSqlQuery query2;
            query2.exec("update alarm_list set ack = 7 where alarm_id = "+QString::number(alarm_id, 10)+";");
        }
    }
    QList<QTreeWidgetItem*> lists = treeWidget->findItems(QString::number(alarm_id, 10), Qt::MatchFixedString, 3);
    for(QTreeWidgetItem*p : lists){
        if(p->text(2) != 1)
            p->setIcon(0, QIcon("picture/7.png"));
        else
            p->setIcon(0, QIcon("picture/6.png"));
        set_row_color(p, "gray");
    }
}
