#include "channel.h"
#include "connection.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
Channel::Channel(QWidget* parent):QWidget(parent){
    treeWidget = new QTreeWidget(this);
    tool_bar = new QWidget(this);
    test_button = new QPushButton("Test", tool_bar);
    test_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    test_all_button = new QPushButton("Test ALL", tool_bar);
    test_all_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    close_button = new QPushButton("Close", tool_bar);
    close_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_up = new QPushButton("Page-up", tool_bar);
    page_up->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_down = new QPushButton("Page-down", tool_bar);
    page_down->setStyleSheet("background-color:rgb(52, 101, 164)");
    QHBoxLayout* tool_layout = new QHBoxLayout;
    tool_layout->addWidget(test_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(test_all_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(close_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(page_up, 0, Qt::AlignLeft);
    tool_layout->addWidget(page_down, 0, Qt::AlignLeft);
    QSpacerItem* s1 = new QSpacerItem( 1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    tool_layout->addItem(s1);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(treeWidget);
    layout->addLayout(tool_layout, 0);
    setLayout(layout);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    treeWidget->setStyleSheet("background-color:rgb(52, 101, 164)");
    QStringList headers;
    headers<<"channel id"<<"Description"<<"Time"<<"Status";
    treeWidget->setHeaderLabels(headers);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(test_button, &QPushButton::clicked, this, &Channel::test);
    connect(test_all_button, &QPushButton::clicked, this, &Channel::test_all);
    connect(close_button, &QPushButton::clicked, this, &Channel::close);
}

void Channel::new_channel(int channel_id){
    QSqlQuery query;
    if(!query.exec("select channel_id, description, time, status from channel where channel_id = " + QString::number(channel_id, 10) + ";")){
        QMessageBox::critical(nullptr, "exec sql Error:",
                              "select channel_id, description, time, status from channel where channel_id = " + QString::number(channel_id, 10) + ";"
                              + "\n" + query.lastError().text());
        return;
    }
    QString channel_id_string;
    QString descriotion;
    QString time;
    QString status;
    if(!query.next()){
        QMessageBox::critical(nullptr, "get data Error:",
                              "select channel_id, description, time, status from channel where channel_id = " + QString::number(channel_id, 10) + ";"
                              + "\n" + query.lastError().text());
        return;
    }
    else{
        channel_id_string = query.value(0).toString();
        descriotion = query.value(1).toString();
        time = query.value(2).toString();
        time[10] = ' ';
        if(query.value(3).toInt() == 1)
            status = "Connected";
        else
            status = "Unknow";
    }
    QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
    item->setText(0, channel_id_string);
    item->setText(1, descriotion);
    item->setText(2, time);
    item->setText(3, status);
    if(status == "Connected")
        set_row_color(item, "green");
    else
        set_row_color(item, "red");
}

void Channel::test(){

    QList<QTreeWidgetItem*> targets = treeWidget->selectedItems();
    for(QTreeWidgetItem* p:targets){
        event_log(2, "channel id is " + p->text(0));
        emit test_signal(p->text(0).toInt());
    }
}

void Channel::test_all(){
    event_log(2, "test all channel");
    QList<QTreeWidgetItem*> list = treeWidget->findItems("", Qt::MatchContains, 0);
    for(QTreeWidgetItem* p:list){
        emit test_signal(p->text(0).toInt());
    }
}

void Channel::close(){
    QList<QTreeWidgetItem*> targets = treeWidget->selectedItems();
    for(QTreeWidgetItem* p:targets){
        event_log(3, "the channel id is "+p->text(0));
        emit close_signal(p->text(0).toInt());
    }
}

void Channel::remove_item(int channel_id){
    QList<QTreeWidgetItem*> list = treeWidget->findItems("", Qt::MatchContains, 0);
    for(QTreeWidgetItem*p : list){
        if(p->text(0).toInt() == channel_id){
            delete p;
        }
    }
}
