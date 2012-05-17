#include "wwidget.h"

WWidget::WWidget(QWidget *parent) :
	QWidget(parent)
{
    init_widget();
}

WWidget::~WWidget()
{
}

/**
 * @brief	初始化控件
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

/**
 * @brief	初始化WWidget类的信号与槽
 */
void WWidget::init_connection()
{
}
