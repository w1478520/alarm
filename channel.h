#ifndef CHANNEL_H
#define CHANNEL_H
#include<QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
class Channel:public QWidget{
  Q_OBJECT
public:
    Channel(QWidget*);
    void new_channel(int);
    void test();
    void test_all();
    void close();
    void remove_item(int);
private:
    QTreeWidget* treeWidget;
    QWidget* tool_bar;
    QPushButton* close_button;
    QPushButton* test_button;
    QPushButton* test_all_button;
    QPushButton* page_up;
    QPushButton* page_down;
signals:
    void close_signal(int);
    void test_signal(int);
};
#endif // CHANNEL_H
