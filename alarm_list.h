#ifndef ALARM_LIST_H
#define ALARM_LIST_H

#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
class Alarm_list: public QWidget {
    Q_OBJECT
public:
    Alarm_list(QWidget*);

    void insert_data(int);
    void update_data(int);
    void ack();
    void ack_all();
    void information();
    void not_available(int);
private:
    int now;
    QTreeWidget* treeWidget;
    QWidget* tool_bar;
    QPushButton* ack_button;
    QPushButton* ack_all_button;
    QPushButton* page_up;
    QPushButton* page_down;
    QPushButton* info;
};
#endif
