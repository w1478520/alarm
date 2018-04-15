#include "event_log.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <connection.h>
Event_log::Event_log(QWidget* parent):QWidget(parent){
    treeWidget = new QTreeWidget(this);
    tool_bar = new QWidget(this);
    search_time_button = new QPushButton("Search Time...", tool_bar);
    search_time_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    search_class_button = new QPushButton("Search Class...", tool_bar);
    search_class_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    search_description_button = new QPushButton("Search description...", tool_bar);
    search_description_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    export_button = new QPushButton("Export...", tool_bar);
    export_button->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_up = new QPushButton("Page-up", tool_bar);
    page_up->setStyleSheet("background-color:rgb(52, 101, 164)");
    page_down = new QPushButton("Page-down", tool_bar);
    page_down->setStyleSheet("background-color:rgb(52, 101, 164)");
    QHBoxLayout* tool_layout = new QHBoxLayout;
    tool_layout->addWidget(search_time_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(search_class_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(search_description_button, 0, Qt::AlignLeft);
    tool_layout->addWidget(export_button, 0, Qt::AlignLeft);
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
    headers<<"Event Id"<<"Time"<<"Class"<<"Description";
    treeWidget->setHeaderLabels(headers);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void Event_log::display_event_log(){
    QList<QTreeWidgetItem*> lists = treeWidget->findItems("", Qt::MatchContains, 0);
    for(QTreeWidgetItem* p:lists){
        p->~QTreeWidgetItem();
    }
    QSqlQuery query;
    if(!query.exec("select event_id, time, class, description from event_log;")){
        QMessageBox::critical(nullptr, "exec sql error: ", "in display_event_log");
        return;
    }
    while (query.next()){
        QString time = query.value(1).toString();
        time[10] = ' ';
        QTreeWidgetItem* p = new QTreeWidgetItem(treeWidget);
        p->setText(0, query.value(0).toString());
        p->setText(1, time);
        p->setText(2, class_num_to_string(query.value(2).toInt()));
        p->setText(3, query.value(3).toString());
        setColor(query.value(2).toInt(), p);
    }
    treeWidget->sortItems(0, Qt::DescendingOrder);
}

void Event_log::setColor(int a, QTreeWidgetItem* p){
    switch (a) {
    case 1: set_row_color(p, "green"); return;
    case 2: set_row_color(p, "yellow"); return;
    case 3: set_row_color(p, "red"); return;
    case 4: set_row_color(p, "red"); return;
    case 5: set_row_color(p, "red"); return;
    case 6: set_row_color(p, "green"); return;
    case 7: set_row_color(p, "red"); return;
    case 8: set_row_color(p, "yellow"); return;
    case 9: set_row_color(p, "yellow"); return;
    case 10: set_row_color(p, "green"); return;
    case 11: set_row_color(p, "red"); return;
    case 12: set_row_color(p, "red"); return;
    case 13: set_row_color(p, "red"); return;
    case 14: set_row_color(p, "grey"); return;
    case 15: set_row_color(p, "green"); return;
    default:
        return;
    }
}
