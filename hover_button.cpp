#include "hover_button.h"

void HoverButton::enterEvent(QEvent *event)
{
    emit hovered();
    QPushButton::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event)
{
    emit unhovered();
    QPushButton::leaveEvent(event);
}
