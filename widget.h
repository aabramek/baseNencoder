#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTextEdit *userInput;
    QTextEdit *result;
};
#endif // WIDGET_H
