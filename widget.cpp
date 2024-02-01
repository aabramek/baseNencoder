#include "widget.h"

#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QPushButton>

static constexpr int TEXT_EDIT_MINIMUM_WIDTH = 500;
static constexpr int TEXT_EDIT_MINIMUM_HEIGHT = 150;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , userInput(new QTextEdit)
    , result(new QTextEdit)
{
    setWindowTitle("Base64 Encoder");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QFont labelFont("Cambria", 14);

    QLabel *l0 = new QLabel;
    l0->setText("Type in text");
    l0->setAlignment(Qt::AlignLeft);
    l0->setMargin(5);
    l0->setFont(labelFont);

    QLabel *l1 = new QLabel;
    l1->setText("Result");
    l1->setAlignment(Qt::AlignLeft);
    l1->setMargin(5);
    l1->setFont(labelFont);

    QPushButton *button = new QPushButton;
    button->setText("Encode");
    button->setFont(labelFont);

    userInput->setMinimumWidth(TEXT_EDIT_MINIMUM_WIDTH);
    userInput->setMinimumHeight(TEXT_EDIT_MINIMUM_HEIGHT);
    result->setMinimumWidth(TEXT_EDIT_MINIMUM_WIDTH);
    result->setMinimumHeight(TEXT_EDIT_MINIMUM_HEIGHT);

    mainLayout->addWidget(l0);
    mainLayout->addWidget(userInput);
    mainLayout->addWidget(l1);
    mainLayout->addWidget(result);
    mainLayout->addWidget(button);
}

Widget::~Widget() {}
