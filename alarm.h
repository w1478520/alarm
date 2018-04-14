#ifndef ALARM_H
#define ALARM_H
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
class Alarm:public QWidget{
    Q_OBJECT
public:
    Alarm(QWidget*);
    void update_datebase();
    void cutout();
    void un_cutout();
    void information();
private:
    QList<QTreeWidgetItem*> list;
    QWidget* tool_bar;
    QTreeWidget* treeWidget;
    QPushButton* cut_out;
    QPushButton* active;
    QPushButton* info;
    QPushButton* page_up;
    QPushButton* page_down;
    QHBoxLayout* tool_layout;
    QVBoxLayout* layout;
signals:
    void cut_out_(int);
    void re_active(int);
};
#endif // ALARM_H
