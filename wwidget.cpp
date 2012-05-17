#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "wwidget.h"

WWidget::WWidget(QWidget *parent) :
	QWidget(parent)
{
    init_widget();
    init_connection();
}

/**
 * @brief	初始化WWidget类的信号与槽
 */
void WWidget::init_connection()
{
    /* 第一个按钮的事件响应 */
    connect(&fir_file_btn, SIGNAL(clicked()), this, SLOT(fir_filename_from_fdlg()));
    connect(&fir_file_le, SIGNAL(textChanged(QString)), this, SLOT(get_fir_le_text(QString)));
    /* 第二个按钮的事件响应 */
    connect(&sec_file_btn, SIGNAL(clicked()), this, SLOT(sec_filename_from_fdlg()));
    connect(&sec_file_le, SIGNAL(textChanged(QString)), this, SLOT(get_sec_le_text(QString)));

    /* 执行移除重复行操作 */
    connect(&process_btn, SIGNAL(clicked()), this, SLOT(exec_remove_lines()));
}

/* 执行两件文的操作 */
void WWidget::exec_remove_lines()
{
    fir_file_str = fir_file_le.text();
    sec_file_str = sec_file_le.text();
    judge_file(fir_file_str);
    judge_file(sec_file_str);

std::cout << get_filename(fir_file_str).toStdString() << std::endl;
}

/* 第一个文本输入域的文体 */
void WWidget::get_fir_le_text(const QString str)
{
    fir_file_str = str;
    std::cout << "TextChanged" << str.toStdString() << std::endl;
}

/* 第二个文本输入域的文体 */
void WWidget::get_sec_le_text(const QString str)
{
    sec_file_str = str;
    std::cout << "TextChanged" << str.toStdString() << std::endl;
}

/* 判断文件是否存在 */
bool WWidget::judge_file(const QString filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,
            tr("Warnning!"),
            tr("Cannot open the file, make sure the file is exist!"),
            QMessageBox::Cancel, QMessageBox::Ok);

        return false;
    }
    file.close();

    return true;
}
/* 从文件对话框中选择一个文件 */
void WWidget::fir_filename_from_fdlg()
{
    fir_file_str = QFileDialog::getOpenFileName(this,
                    tr("Open Text"), tr("./"), tr("Text Files (*.txt)"));
    fir_file_le.setText(fir_file_str);    /* 设置单行文本框值 */
}

/* 从文件对话框中选择第二个文件 */
void WWidget::sec_filename_from_fdlg()
{
    sec_file_str = QFileDialog::getOpenFileName(this,
                    tr("Open Text"), tr("./"), tr("Text Files (*.txt)"));
    sec_file_le.setText(sec_file_str);  /* 设置单行文本框值 */
}

/**
 * @brief    初始化控件
 */
void WWidget::init_widget()
{
    move(480, 325);
    resize(375, 125);
    setWindowTitle(QObject::tr("Widget"));

    /* 按钮属性设置 */
    fir_file_btn.setText(QObject::tr("choose file1"));
    sec_file_btn.setText(QObject::tr("choose file2"));
    process_btn.setText(QObject::tr("process"));
    process_btn.setShortcut(QObject::tr("Enter"));

    /* 布局管理器管理控件 */
    fir_file_le.resize(150, 20);
    sec_file_le.resize(150, 20);
    layout.addWidget(&fir_file_le, 0, 0, 1, 1);
    layout.addWidget(&fir_file_btn, 0, 1, 1, 1);
    layout.addWidget(&sec_file_le, 1, 0, 1, 1);
    layout.addWidget(&sec_file_btn, 1, 1, 1, 1);
    layout.addWidget(&process_btn, 2, 1, 1, 1);
    layout.setSpacing(10);  /* 控件间的间隔 */

    setLayout(&layout);
}

/* 获取文件名 */
QString WWidget::get_filename(const QString filename)
{
    bool exist = false;
    int index, len;
    QString file_str;
std::cout << filename.toStdString() << std::endl;
    exist = judge_file(filename);
    if (!exist)
    {
        return "";
    }

    index = filename.lastIndexOf(QRegExp("/"));
    len = filename.length();
    if (index >= 0 && index < len)
    {
        /* 最右边len - index - 1个字符 */
        file_str = filename.right(len - index - 1);
    }
    else
    {
        file_str = filename;
    }

    return file_str;
}

WWidget::~WWidget()
{
}
