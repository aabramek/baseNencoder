#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void encode();
    void selectFileName();
    void saveResult();

private:
    QPlainTextEdit *userInput;
    QPlainTextEdit *result;
    QComboBox *encodingType;
    QPushButton *openFileDialog;
    QLineEdit *fileName;
    QPushButton *saveResultButton;
    QByteArray encodedData;
    QMessageBox *saveResultFailureMB;
};
#endif // WIDGET_H
