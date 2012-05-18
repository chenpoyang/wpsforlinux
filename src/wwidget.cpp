#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QTextStream>
#include <iostream>
#include "wwidget.h"

WWidget::WWidget(QWidget *parent) :
	QWidget(parent)
{
    init_widget();  /* 初始化界面的控件 */
    init_connection();  /* 初始化控件之间的消息响应 */

    /* 设置默认的文件路径 */
    QString fir_str("../test/file1.txt");
    QString sec_str("../test/file2.txt");
    fir_file_le.setText(fir_str);
    sec_file_le.setText(sec_str);
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

/* 对给定两文件的绝对路径, 将两文件中相同的行去掉,输入文件分别备份 */
void WWidget::deal_with_file(const QString fir_path, const QString sec_path)
{
    /* 备份文件 */
    const QString fir_bak = backup_file(fir_path);
    const QString sec_bak = backup_file(sec_path);
    QHash<QString, bool> str_hash;
    QString fir_line, sec_line;

    QFile fir_in(fir_bak), sec_in(sec_bak);
    QTextStream fir_ts(&fir_in), sec_ts(&sec_in);

std::cout << "dealing with the files, please wait...." << std::endl;
std::cout << "fir = " << fir_bak.toStdString() << std::endl;
std::cout << "sec = " << sec_bak.toStdString() << std::endl;

    if (!fir_in.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "can not open file:" << fir_bak.toStdString() << std::endl;
        return;
    }
    if (!sec_in.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "can not open file:" << sec_bak.toStdString() << std::endl;
        return;
    }

    /* 寻找相同的行, 保存于str_hash中 */
    while (!fir_ts.atEnd())
    {
        sec_ts.seek(0);
        fir_line = fir_ts.readLine();
        while (!sec_ts.atEnd())
        {
            sec_line = sec_ts.readLine();
            /* 相等 */
            if (QString::compare(fir_line, sec_line) == 0)
            {
                str_hash[fir_line] = true;
            }
        }
    }

    if (str_hash.size() <= 0)
    {
        return; /* do not exist the same line! */
    }

    QFile::remove(fir_path);
    QFile::remove(sec_path);
    reflesh_file(fir_path, fir_bak, str_hash);
    reflesh_file(sec_path, sec_bak, str_hash);
}

/* 删除相同的行,并更新文件 */
void WWidget::reflesh_file(const QString filename,
                           const QString bak,
                           const QHash<QString, bool> &str_hash)
{
    QFile in(bak);
    QFile out(filename);
    QString str;

    if (QFile::exists(filename))
    {
        QFile::remove(filename);
    }

    if ((!in.open(QIODevice::ReadOnly | QIODevice::Text)) ||
            (!out.open(QIODevice::Append | QIODevice::Text)))
    {
        std::cout << "open file error!" << std::endl;
        return;
    }
    QTextStream in_ts(&in), out_ts(&out);

    while (!in_ts.atEnd())
    {
        str = in_ts.readLine();
        if (str_hash[str] == true)
        {
            continue;   /* 相同行, 不写入文件 */
        }

        str.append("\n");
        out_ts << str;
        std::cout << str.toStdString() << std::endl;
    }
    out.flush();
}

/* 备份文件, 将文件备份为filename_bak */
QString WWidget::backup_file(const QString file_abs_path)
{
    QString str, filename, dir, bak_filename;
    int index, len;

    /* filename.bak 文件所在的目录 */
    index = file_abs_path.lastIndexOf(QRegExp("/"));
    len = file_abs_path.length();
    if (index >= 0 && index < len)
    {
        dir = file_abs_path.left(index + 1);
    }
    else
    {
        dir = QString("./");
    }

    /* 获取纯文件名, eg:filename.txt ---> filename */
    str = get_filename(file_abs_path);
    len = str.length();
    index = str.lastIndexOf('.');
    if (index >= 0 && index < len)
    {
        filename = str.left(index);
    }
    else
    {
        filename = str;
    }

    filename.append(".bak");
    bak_filename = dir.append(filename);

    /* backup */
    if (QFile::exists(bak_filename))
    {
        QMessageBox::warning(this, tr("Warnning"), tr("Previous backup exist, overwrite!"));
        QFile::remove(bak_filename);
    }
    QFile::copy(file_abs_path, bak_filename);
    std::cout << "backup filename = " <<  dir.toStdString() << std::endl;

    return dir;
}

/* 执行两件文的操作 */
void WWidget::exec_remove_lines()
{
    bool exist = false;

    fir_file_str = fir_file_le.text();
    sec_file_str = sec_file_le.text();
    exist = judge_file(fir_file_str);
    if (!exist)
    {
        return;
    }
    exist = judge_file(sec_file_str);
    if (!exist)
    {
        return;
    }

    deal_with_file(fir_file_str, sec_file_str);
}

/* 第一个文本输入域的文体 */
void WWidget::get_fir_le_text(const QString str)
{
    fir_file_str = str;
}

/* 第二个文本输入域的文体 */
void WWidget::get_sec_le_text(const QString str)
{
    sec_file_str = str;
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
