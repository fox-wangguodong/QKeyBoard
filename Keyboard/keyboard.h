#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QPlainTextEdit>
#include <QTableWidget>
#include <QTextEdit>
#include <QWidget>
#include <QtGui>
#include <QtSql>

class QLineEdit;
class QPushButton;

namespace Ui {
class Keyboard;
}

//定义文字选择个数
#define N_CANDIDATE 7

class Keyboard : public QWidget
{
    Q_OBJECT
public:
    static Keyboard *getInstance();

private:
    explicit Keyboard(QWidget *parent = 0);//构造函数私有,不能创建对象
    ~Keyboard();

    static Keyboard *instance;
    static QMutex mutex;


    //记录当前传进来的编辑控件
    void setLineEdit(QLineEdit *);
    void setTextEdit(QTextEdit *);
    void setPlainTextEdit(QPlainTextEdit *);
    void setQTableWidgetItem(QTableWidgetItem *);


    //文本检索
    QStringList getCandidate(const QString &keys);
    //清空检索到的结果
    void clearText();
    //处理拼音
    void handlePY(QString key);
    //设置大小写
    void setUpperLetter(bool upper);

private:
    Ui::Keyboard *ui;

    QString outputText;//要输出的文本

    int type = 0;//记录当前文本的控件类型：1:lineEdit; 2:textEdit; 3:plainTextEdit; 4:tableWidgetItem
    QTextEdit *outputTextEdit;
    QLineEdit *outputLineEdit;
    QPlainTextEdit *outputPlainTextEdit;
    QTableWidgetItem *outputTableWidgetItem;

    //文字选择框个数
    QPushButton *btnText[N_CANDIDATE];
    bool shift;
    bool bCh;
    QStringList strResults;
    int total_pages, cur_page;
    QSqlDatabase db;

private slots:

    //文本触发
    void slotSelectWord();
    //数字触发
    void slotSelectDigital();
    //键盘按钮触发
    void keyboardHandler();
    //lineEdit文本改变时触发
    void on_lineEdit_textChanged(const QString &arg1);
    //shift触发
    void on_shift_clicked();
    //字母、符号切换触发
    void on_char_2_toggled(bool checked);
    //编辑框文本清空触发
    void on_clear_clicked();
    //backspace触发
    void on_backButton_clicked();
    //last文本触发
    void on_btnPrev_clicked();
    //next文本触发
    void on_btnNext_clicked();
    //中英文切换触发
    void on_btnEnCh_clicked();
    //关闭按钮触发
    void on_btnClose_clicked();
    //Enter按钮触发
    void on_enterButton_clicked();


    //接收到lineEdit传来的信号
    void run_keyboard_lineEdit();
    //接收到textEdit传来的信号
    void run_keyboard_textEdit();
    //接受到plainTextEdit传来的信号
    void run_keyboard_plainTextEdit();
    //接受到QTableWidgetItem传来的信号
    void run_keyboard_QTableWidgetItem(QTableWidgetItem* tableWidgetItem);


signals:

};

#endif // KEYBOARD_H
