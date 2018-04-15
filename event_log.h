#ifndef EVENT_LOG_H
#define EVENT_LOG_H
#include <QTreeWidget>
#include <QPushButton>
class Event_log:public QWidget{
    Q_OBJECT
public:
    Event_log(QWidget*);
    void display_event_log();
private:
    QTreeWidget* treeWidget;
    QWidget* tool_bar;
    QPushButton* search_time_button;
    QPushButton* search_class_button;
    QPushButton* search_description_button;
    QPushButton* export_button;
    QPushButton* page_up;
    QPushButton* page_down;
    void setColor(int, QTreeWidgetItem*);
};
#endif // EVENT_LOG_H
