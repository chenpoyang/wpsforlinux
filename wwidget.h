#ifndef __WWIDGET_H__
#define __WWIDGET_H__

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>
#include <QtCore/QFile>
#include <QtCore/QString>

/**
 * @brief    WWidget: wps widget类, 从QT库的QWidget类继承
 */
class WWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WWidget(QWidget *parent = 0);
    virtual ~WWidget();

private:
    void init_widget();    /* 初始化控件 */
    void init_connection();    /* 初始化信号与槽 */
    bool judge_file(const QString filename);  /* 判断文件是否存在 */
    QString get_filename(const QString filename);    /* 获取文件名 */

signals:

private slots:
    void fir_filename_from_fdlg();    /* 从文件对话框中选择第一个文件 */
    void sec_filename_from_fdlg();    /* 从文件对话框中选择第二个文件 */
    void exec_remove_lines();         /* 执行两件文的操作 */

private:
    /* 两个选择文件的按钮, 及一个执行命令的按钮 */
    QPushButton fir_file_btn, sec_file_btn;
    /* 两个文本输入域, 用于保存输入文件的绝对路径名 */
    QLineEdit fir_file_le, sec_file_le;
    /* 两文件的绝对路径名 */
    QString fir_file_str, sec_file_str;

    /* 执行按钮 */
    QPushButton process_btn;

    /* 布局管理器 */
    QGridLayout layout;

    QFile file_one, file_two;
};

#endif /* __WWIDGET_H__ */
