#include "keyboardinstaller.h"

#include <QLineEdit>
#include <QTextEdit>


KeyboardInstaller* KeyboardInstaller::baseDialog = nullptr;
QMutex KeyboardInstaller::mutex;


KeyboardInstaller::KeyboardInstaller()
{

}


KeyboardInstaller *KeyboardInstaller::getInstance()
{
    if(baseDialog == nullptr){
        mutex.lock();
        if(baseDialog == nullptr){
            baseDialog = new KeyboardInstaller();
        }
        mutex.unlock();
    }
    return baseDialog;
}

void KeyboardInstaller::installObject(QObject *parent)
{
    if(parent != nullptr){
        QList<QWidget*> lole = parent->findChildren<QWidget*>();
        QListIterator<QWidget*> it(lole);
        while(it.hasNext()){
            QWidget *leField = it.next();
            if(QLineEdit *le = qobject_cast<QLineEdit*>(leField)){
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->installEventFilter(listener);
                Keyboard* keyboard = Keyboard::getInstance();
                connect(le, SIGNAL(selectionChanged()), keyboard, SLOT(run_keyboard_lineEdit()));
            }
            if(QTextEdit *le = qobject_cast<QTextEdit*>(leField)){
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->installEventFilter(listener);
                Keyboard* keyboard = Keyboard::getInstance();
                connect(le, SIGNAL(selectionChanged()), keyboard, SLOT(run_keyboard_textEdit()));
            }
            if(QPlainTextEdit *le = qobject_cast<QPlainTextEdit*>(leField)){
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->installEventFilter(listener);
                Keyboard* keyboard = Keyboard::getInstance();
                connect(le, SIGNAL(selectionChanged()), keyboard, SLOT(run_keyboard_plainTextEdit()));
            }
            if(QTableWidget *le = qobject_cast<QTableWidget*>(leField)){
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->installEventFilter(listener);

                Keyboard* keyboard = Keyboard::getInstance();
                connect(le, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), keyboard, SLOT(run_keyboard_QTableWidgetItem(QTableWidgetItem*)));
            }
        }
    }
}

void KeyboardInstaller::removeObject(QObject *parent)
{
    if(parent != nullptr){
        QList<QWidget*> lole = parent->findChildren<QWidget*>();
        QListIterator<QWidget*> it(lole);
        while(it.hasNext()){
            QWidget *leField = it.next();
            if(QLineEdit *le = qobject_cast<QLineEdit*>(leField)){                
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->removeEventFilter(listener);
            }
            if(QTextEdit *le = qobject_cast<QTextEdit*>(leField)){
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->removeEventFilter(listener);
            }
            if(QPlainTextEdit *le = qobject_cast<QPlainTextEdit*>(leField)){
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->removeEventFilter(listener);
            }
            if(QTableWidget *le = qobject_cast<QTableWidget*>(leField)){
                KeyboardInstaller *listener = KeyboardInstaller::getInstance();
                le->removeEventFilter(listener);
            }
        }
    }
}


bool KeyboardInstaller::eventFilter(QObject *watched, QEvent *event)
{
    if(QLineEdit *le = qobject_cast<QLineEdit*>(watched))
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit le->selectionChanged();
        }
    }
    return QObject::eventFilter(watched, event);
}
