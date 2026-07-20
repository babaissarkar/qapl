#pragma once

#include <QPushButton>

class HoverButton : public QPushButton
{
    Q_OBJECT

public:
    using QPushButton::QPushButton;

signals:
    void hovered();
    void unhovered();

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};
