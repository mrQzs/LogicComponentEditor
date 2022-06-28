#include "YDJogButton.h"

YDJogButton::YDJogButton(QWidget *parent) : QPushButton{parent} {}

void YDJogButton::mousePressEvent(QMouseEvent *) { emit sigStart(); }

void YDJogButton::mouseReleaseEvent(QMouseEvent *) { emit sigStop(); }
