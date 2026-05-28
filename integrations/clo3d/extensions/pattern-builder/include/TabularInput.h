//
// Created by emily on 03/04/2026.
//

#ifndef CHRYSALIS_TABULARINPUT_H
#define CHRYSALIS_TABULARINPUT_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class TabularInput;
}

QT_END_NAMESPACE

class TabularInput : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)

public:
    explicit TabularInput(QWidget *parent = nullptr);

    ~TabularInput() override;

    QString getTitle() const;
    void setTitle(const QString& title) const;

private:
    Ui::TabularInput *ui;
};


#endif //CHRYSALIS_TABULARINPUT_H