#ifndef KeyboardInstaller_H
#define KeyboardInstaller_H

#include "KeyBoard/Keyboard.h"


class KeyboardInstaller : public QObject
{
public:
    static KeyboardInstaller* getInstance();
    static void installObject(QObject *obj);
    static void removeObject(QObject *obj);

private:
    KeyboardInstaller();
    static KeyboardInstaller* baseDialog;
    static QMutex mutex;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // KeyboardInstaller_H
