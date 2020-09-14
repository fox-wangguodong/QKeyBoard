/*
 * Author: LT Thomas <ltjr@ti.com>
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#include "keyboard.h"
#include "ui_keyboard.h"
#include <QDesktopWidget>
#include <QTextEdit>
#include <QtGui>

Keyboard* Keyboard::instance = NULL;
QMutex Keyboard::mutex;

Keyboard* Keyboard::getInstance()
{
    if (!instance) {
        mutex.lock();
        if (!instance) {
            instance = new Keyboard();
        }
        mutex.unlock();
    }
    return instance;
}

Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏
    //设置键盘布局位置
    QApplication* app = dynamic_cast<QApplication*>(QApplication::instance());
    QDesktopWidget *desktop = app->desktop();
    this->setGeometry(0,desktop->height()-600*(desktop->height()/1080),desktop->width(),600*(desktop->height()/1080));


    connect(ui->Buttonq, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonw, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttone, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonr, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttont, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttony, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonu, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttoni, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttono, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonp, SIGNAL(clicked()), this, SLOT(keyboardHandler()));

    connect(ui->Buttona, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttons, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttond, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonf, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttong, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonh, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonj, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonk, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonl, SIGNAL(clicked()), this, SLOT(keyboardHandler()));

    connect(ui->Buttonz, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonx, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonc, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonv, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonb, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonn, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->Buttonm, SIGNAL(clicked()), this, SLOT(keyboardHandler()));

    connect(ui->Button0, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button1, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button2, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button3, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button4, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button5, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button6, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button7, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button8, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->Button9, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));

    connect(ui->btnText1, SIGNAL(clicked()), this, SLOT(slotSelectWord()));
    connect(ui->btnText2, SIGNAL(clicked()), this, SLOT(slotSelectWord()));
    connect(ui->btnText3, SIGNAL(clicked()), this, SLOT(slotSelectWord()));
    connect(ui->btnText4, SIGNAL(clicked()), this, SLOT(slotSelectWord()));
    connect(ui->btnText5, SIGNAL(clicked()), this, SLOT(slotSelectWord()));
    connect(ui->btnText6, SIGNAL(clicked()), this, SLOT(slotSelectWord()));
    connect(ui->btnText7, SIGNAL(clicked()), this, SLOT(slotSelectWord()));

    connect(ui->space, SIGNAL(clicked()), this, SLOT(keyboardHandler()));
    connect(ui->btnComma, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->btnDot, SIGNAL(clicked()), this, SLOT(slotSelectDigital()));
    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(on_btnClose_clicked()));


    ui->widget_chinese_select->hide();//初始化时隐藏文字选择栏

    bCh = false;//中文模式
    outputText = "";//编辑框文本清空
    shift = false;//大小写模式:小写
    ui->lineEdit->setFocus();//编辑框获取焦点

    btnText[0] = ui->btnText1;
    btnText[1] = ui->btnText2;
    btnText[2] = ui->btnText3;
    btnText[3] = ui->btnText4;
    btnText[4] = ui->btnText5;
    btnText[5] = ui->btnText6;
    btnText[6] = ui->btnText7;
    ui->btnPrev->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnPrev->hide();
    ui->btnNext->hide();

    //加载数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("py.db");
    QSqlDatabase::removeDatabase("SQLITE");
}

Keyboard::~Keyboard()
{
    delete ui;
}


QStringList Keyboard::getCandidate(const QString &keys)
{
    QStringList list;
    list.clear();
    if (keys == "")
        return list;

    if (!db.open()) {
        qDebug("### %s %d, %s", __FUNCTION__, __LINE__, db.lastError().text().data());
        return list;
    }

    QSqlQuery query(db);
    QString sql;
    sql = "SELECT val FROM pytable WHERE key LIKE " + QString("'") + keys + QString("%'");
    query.prepare(sql);
    if (!query.exec()) {
        qDebug("### %s %d, %s", __FUNCTION__, __LINE__, qPrintable(query.lastError().text()));
        db.close();
        return list;
    }

    while (query.next()) {
        QString val = query.value(0).toString();
        list.append(val.split(" "));
    }

    db.close();
    return list;
}

void Keyboard::clearText()
{
    for (int i = 0; i < N_CANDIDATE; i++){
        btnText[i]->setText("");
    }
}

void Keyboard::handlePY(QString key)
{
    int cnt, i;
    QString py = ui->btnHint->text();
    py += key;
    ui->btnHint->setText(py);
    strResults = getCandidate(py);

    clearText();

    cnt = strResults.length();
    total_pages = cnt / N_CANDIDATE;
    cur_page = 0;
    if (cnt > N_CANDIDATE) {
        cnt = N_CANDIDATE;
    }

    for (i = 0; i < cnt; i++)
        btnText[i]->setText(strResults.at(i));
    if (total_pages > 1) {
        ui->btnPrev->setEnabled(false);
        ui->btnNext->setEnabled(true);
    } else {
        ui->btnPrev->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }

    if (cnt) {
        ui->btnPrev->show();
        ui->btnNext->show();
    } else {
        ui->btnPrev->hide();
        ui->btnNext->hide();
    }
}

void Keyboard::setUpperLetter(bool upper)
{
    if (upper) {
        ui->Buttonq->setText("Q");
        ui->Buttonw->setText("W");
        ui->Buttone->setText("E");
        ui->Buttonr->setText("R");
        ui->Buttont->setText("T");
        ui->Buttony->setText("Y");
        ui->Buttonu->setText("U");
        ui->Buttoni->setText("I");
        ui->Buttono->setText("O");
        ui->Buttonp->setText("P");

        ui->Buttona->setText("A");
        ui->Buttons->setText("S");
        ui->Buttond->setText("D");
        ui->Buttonf->setText("F");
        ui->Buttong->setText("G");
        ui->Buttonh->setText("H");
        ui->Buttonj->setText("J");
        ui->Buttonk->setText("K");
        ui->Buttonl->setText("L");

        ui->Buttonz->setText("Z");
        ui->Buttonx->setText("X");
        ui->Buttonc->setText("C");
        ui->Buttonv->setText("V");
        ui->Buttonb->setText("B");
        ui->Buttonn->setText("N");
        ui->Buttonm->setText("M");
    } else {
        ui->Buttonq->setText("q");
        ui->Buttonw->setText("w");
        ui->Buttone->setText("e");
        ui->Buttonr->setText("r");
        ui->Buttont->setText("t");
        ui->Buttony->setText("y");
        ui->Buttonu->setText("u");
        ui->Buttoni->setText("i");
        ui->Buttono->setText("o");
        ui->Buttonp->setText("p");

        ui->Buttona->setText("a");
        ui->Buttons->setText("s");
        ui->Buttond->setText("d");
        ui->Buttonf->setText("f");
        ui->Buttong->setText("g");
        ui->Buttonh->setText("h");
        ui->Buttonj->setText("j");
        ui->Buttonk->setText("k");
        ui->Buttonl->setText("l");

        ui->Buttonz->setText("z");
        ui->Buttonx->setText("x");
        ui->Buttonc->setText("c");
        ui->Buttonv->setText("v");
        ui->Buttonb->setText("b");
        ui->Buttonn->setText("n");
        ui->Buttonm->setText("m");
    }
}


void Keyboard::slotSelectWord()
{
    QPushButton *button = (QPushButton *)sender();
    int pos = ui->lineEdit->cursorPosition();
    outputText.insert(pos, button->text());
    ui->lineEdit->setText(outputText);
    ui->lineEdit->setCursorPosition(pos + button->text().length());
    ui->btnHint->setText("");
    clearText();
    ui->btnPrev->hide();
    ui->btnNext->hide();
}

void Keyboard::slotSelectDigital()
{
    QPushButton *button = (QPushButton *)sender();
    int pos = ui->lineEdit->cursorPosition();
    if (!bCh || (ui->btnHint->text() == "")) {
        outputText.insert(pos, button->text());
        ui->lineEdit->setText(outputText);
        ui->lineEdit->setCursorPosition(pos + 1);
    } else {
        handlePY(button->text());
    }
}

void Keyboard::keyboardHandler()
{
    QPushButton *button = (QPushButton *)sender();
    QString inputText;
    int i, pos;

    inputText = button->text();
    pos = ui->lineEdit->cursorPosition();

    if (inputText == tr("空格"))
    {
        outputText.insert(pos, " ");
    }
    else if(inputText == "&&")
    {
        outputText.insert(pos, "&&");
    }
    else if(inputText == "\\")
    {
        outputText.insert(pos, "\\");
    }
    else
    {
        if(shift)
        {
            //shift = false;
            outputText.insert(pos, inputText.toUpper());
        } else {
            if (bCh) {
                handlePY(inputText);
                return;
            } else {
                outputText.insert(pos, inputText);
            }
        }
    }

    ui->lineEdit->setText(outputText);
    ui->lineEdit->setCursorPosition(pos + 1);
}

//lineEdit文本改变时
void Keyboard::on_lineEdit_textChanged(const QString &arg1)
{
    outputText = arg1;
    ui->lineEdit->setText(outputText);
    ui->lineEdit->setFocus();
}

void Keyboard::on_shift_clicked()
{
    shift = !shift;
    if (shift) {
        setUpperLetter(true);
    } else {
        setUpperLetter(false);
    }
}


void Keyboard::on_char_2_toggled(bool checked)
{
    if(checked)
    {
        ui->Button0->setText("`");
        ui->Button1->setText("~");
        ui->Button2->setText("!");
        ui->Button3->setText("@");
        ui->Button4->setText("#");
        ui->Button5->setText("$");
        ui->Button6->setText("%");
        ui->Button7->setText("^");
        ui->Button8->setText("&&");// trUtf8("\u0040")
        ui->Button9->setText("*");

        ui->Buttonq->setText("(");
        ui->Buttonw->setText(")");
        ui->Buttone->setText("-");
        ui->Buttonr->setText("_");
        ui->Buttont->setText("=");
        ui->Buttony->setText("+");
        ui->Buttonu->setText("[");
        ui->Buttoni->setText("]");
        ui->Buttono->setText("{");
        ui->Buttonp->setText("}");

        ui->Buttona->setText(trUtf8("\\"));
        ui->Buttons->setText("|");
        ui->Buttond->setText(";");
        ui->Buttonf->setText(":");
        ui->Buttong->setText("'");
        ui->Buttonh->setText("\"");
        ui->Buttonj->setText("/");
        ui->Buttonk->setText("?");
        ui->Buttonl->setText("");

        ui->Buttonz->setText("<");
        ui->Buttonx->setText(">");
        ui->Buttonc->setText(",");
        ui->Buttonv->setText(".");
        ui->Buttonb->setText("");
        ui->Buttonn->setText("");
        ui->Buttonm->setText("");

    }
    else
    {
        ui->Button0->setText("0");
        ui->Button1->setText("1");
        ui->Button2->setText("2");
        ui->Button3->setText("3");
        ui->Button4->setText("4");
        ui->Button5->setText("5");
        ui->Button6->setText("6");
        ui->Button7->setText("7");
        ui->Button8->setText("8");
        ui->Button9->setText("9");

        setUpperLetter(false);
    }
}


void Keyboard::on_clear_clicked()
{
    QString py = ui->btnHint->text();
    if (py.length()) {
        ui->btnHint->setText("");
        handlePY("");
    } else {
        outputText="";
        ui->lineEdit->setText(outputText);
    }
}

//Backspace按钮
void Keyboard::on_backButton_clicked()
{
    QString py = ui->btnHint->text();
    if (py.length()) {
        py.remove(py.length() - 1, 1);
        ui->btnHint->setText(py);
        handlePY("");
    } else {
        int pos;
        pos = ui->lineEdit->cursorPosition();
        outputText.remove(pos - 1, 1);
        ui->lineEdit->setText(outputText);
        ui->lineEdit->setCursorPosition(pos - 1);
    }
}


//文字选择上一个
void Keyboard::on_btnPrev_clicked()
{
    int i, cnt;
    cur_page--;
    if (cur_page == 0)
        ui->btnPrev->setEnabled(false);
    cnt = N_CANDIDATE;

    clearText();
    for (i = 0; i < cnt; i++)
        btnText[i]->setText(strResults.at(cur_page * N_CANDIDATE + i));

    ui->btnNext->setEnabled(true);
}

//文字选择下一个
void Keyboard::on_btnNext_clicked()
{
    int i, cnt;
    cur_page++;
    if (cur_page == total_pages) {
        ui->btnNext->setEnabled(false);
        cnt = strResults.length() - cur_page * N_CANDIDATE;
    } else {
        cnt = N_CANDIDATE;
    }

    clearText();
    for (i = 0; i < cnt; i++)
        btnText[i]->setText(strResults.at(cur_page * N_CANDIDATE + i));
    ui->btnPrev->setEnabled(true);
}


//中英文切换按钮
void Keyboard::on_btnEnCh_clicked()
{
    bCh = !bCh;
    if (bCh) {
        ui->btnEnCh->setText(tr("中"));
        ui->widget_chinese_select->show();
        ui->widget_number->hide();
    } else {
        ui->btnEnCh->setText(tr("英"));
        ui->widget_chinese_select->hide();
        ui->widget_number->show();
    }
}

//关闭对话框按钮
void Keyboard::on_btnClose_clicked()
{
    this->close();
}

//Enter按钮
void Keyboard::on_enterButton_clicked()
{
    if(type == 1){
        outputLineEdit->setText(outputText);
    }
    if(type == 2){
        outputTextEdit->setPlainText(outputText);
    }
    if(type == 3){
        outputPlainTextEdit->setPlainText(outputText);
    }
    if(type == 4){
        outputTableWidgetItem->setText(outputText);
    }
    outputText="";
    ui->lineEdit->setText(outputText);
    close();
}

void Keyboard::setLineEdit(QLineEdit* line)
{
    type = 1;//记录当前文本的控件类型：1:lineEdit; 2:textEdit; 3:plainTextEdit
    outputLineEdit = line;//保存lineEdit指针
    ui->lineEdit->setText(line->text());//将当前传进来的lineEdit内容显示到编辑框
}


void Keyboard::setTextEdit(QTextEdit* textEdit)
{
    type = 2;//记录当前文本的控件类型：1:lineEdit; 2:textEdit; 3:plainTextEdit
    outputTextEdit = textEdit;//保存TextEdit指针
    ui->lineEdit->setText(textEdit->toPlainText());//将当前传进来的textEdit内容显示到编辑框
}

void Keyboard::setPlainTextEdit(QPlainTextEdit* plainTextEdit)
{
    type = 3;//记录当前文本的控件类型：1:lineEdit; 2:textEdit; 3:plainTextEdit
    outputPlainTextEdit = plainTextEdit;//保存plainTextEdit指针
    ui->lineEdit->setText(plainTextEdit->toPlainText());//将当前传进来的plainTextEdit内容显示到编辑框
}

void Keyboard::setQTableWidgetItem(QTableWidgetItem *tableWidgetItem)
{
    type = 4;//记录当前文本的控件类型：1:lineEdit; 2:textEdit; 3:plainTextEdit
    outputTableWidgetItem = tableWidgetItem;//保存plainTextEdit指针
    ui->lineEdit->setText(tableWidgetItem->text());//将当前传进来的plainTextEdit内容显示到编辑框
}

//接受传递过来的lineEdit
void Keyboard::run_keyboard_lineEdit()
{
    QLineEdit *line = (QLineEdit *)sender();
    setLineEdit(line);
    setWindowModality(Qt::ApplicationModal);
    show();
}

//接受传递过来的textEdit
void Keyboard::run_keyboard_textEdit()
{
    QTextEdit *textEdit = (QTextEdit *)sender();
    setTextEdit(textEdit);
    setWindowModality(Qt::ApplicationModal);
    show();
}

//接受传递过来的textEdit
void Keyboard::run_keyboard_plainTextEdit()
{
    QPlainTextEdit *plainTextEdit = (QPlainTextEdit *)sender();
    setPlainTextEdit(plainTextEdit);
    setWindowModality(Qt::ApplicationModal);
    show();
}

void Keyboard::run_keyboard_QTableWidgetItem(QTableWidgetItem* tableWidgetItem)
{
    setQTableWidgetItem(tableWidgetItem);
    setWindowModality(Qt::ApplicationModal);
    show();
}
