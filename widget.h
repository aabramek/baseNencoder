#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void encode();
    void selectFileName();

private:
    QPlainTextEdit *userInput;
    QPlainTextEdit *result;
    QComboBox *encodingType;
    QPushButton *openFileDialog;
    QLineEdit *fileName;
};
#endif // WIDGET_H
