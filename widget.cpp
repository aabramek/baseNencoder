#include "widget.h"
#include "baseN.h"

#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QFileDialog>
#include <QFile>
#include <QDataStream>

static constexpr int TEXT_EDIT_MINIMUM_WIDTH = 500;
static constexpr int TEXT_EDIT_MINIMUM_HEIGHT = 150;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , userInput(new QPlainTextEdit)
    , result(new QPlainTextEdit)
    , encodingType(new QComboBox)
    , openFileDialog(new QPushButton("Choose file"))
    , fileName(new QLineEdit)
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
    result->setReadOnly(true);

    std::array<const char*, 2> encodingTypes = {
        "Base64",
        "Base32"
    };

    std::for_each(encodingTypes.begin(), encodingTypes.end(), [this](const char *s){
        encodingType->addItem(s);
    });

    fileName->setPlaceholderText("Enter filename");

    QHBoxLayout *fileNameLayout = new QHBoxLayout;
    fileNameLayout->addWidget(fileName);
    fileNameLayout->addWidget(openFileDialog);

    QFormLayout *form = new QFormLayout;
    form->addRow("Filename", fileNameLayout);
    form->addRow("Encoding type", encodingType);

    mainLayout->addWidget(l0);
    mainLayout->addWidget(userInput);
    mainLayout->addWidget(l1);
    mainLayout->addWidget(result);
    mainLayout->addLayout(form);
    mainLayout->addWidget(button);

    connect(openFileDialog, &QPushButton::clicked, this, &Widget::selectFileName);
    connect(button, &QPushButton::clicked, this, &Widget::encode);
}

Widget::~Widget() {}

void Widget::encode()
{
    QByteArray data;
    QFile file(fileName->text());
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        data = file.readAll();
        file.close();
    }
    else {
        data = userInput->toPlainText().toUtf8();
    }
    QString encoded;
    switch (encodingType->currentIndex()) {
    case 0:
        encoded = BaseNEncoder::encode64(data);
        break;
    case 1:
        encoded = BaseNEncoder::encode32(data);
        break;
    }
    result->setPlainText(encoded);
}

void Widget::selectFileName()
{
    QString selectedFileName = QFileDialog::getOpenFileName(this, "Choose file");
    fileName->setText(selectedFileName);
}
