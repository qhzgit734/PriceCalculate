#include "WinowMain.h"

// #include <QDebug>

// 全局变量

QString strText;
bool a1 = false;
bool a2 = false;
bool b1 = false;
bool b2 = false;
bool c1 = false;
bool c2 = false;
bool c3 = false;
bool c4 = false;
extern int FE;
extern int CU;
extern QJsonObject rootObj;

WinowMain::WinowMain(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::WinowMainClass())
{
	ui->setupUi(this);
	init();

}

WinowMain::~WinowMain()
{
	delete pCurrentItem;
	delete WinHelp; WinHelp = NULL;
	delete WinSet; WinSet = NULL;
	delete ui;
}

// 初始化init
void WinowMain::init()
{
	pCurrentItem = new QTreeWidgetItem();
	WinHelp = new WindowHelp(NULL);
	WinSet = new WindowSet(NULL);

	ui->stackedWidget->setCurrentIndex(0);

	// 关联信号槽
	connect(ui->treeWidget, &QTreeWidget::currentItemChanged,
		this, &WinowMain::stackedWidget_setCurrentIndex);
	connect(ui->pushButton, &QPushButton::clicked,
		this, &WinowMain::show_result);
	connect(ui->pushButton_2, &QPushButton::clicked,
		this, &WinowMain::show_result);
	connect(ui->pushButton_3, &QPushButton::clicked,
		this, &WinowMain::show_result);
	connect(ui->pushButton_4, &QPushButton::clicked,
		this, &WinowMain::show_result);
	connect(ui->pushButton_5, &QPushButton::clicked,
		this, &WinowMain::show_result);
	connect(ui->pushButton_6, &QPushButton::clicked,
		this, &WinowMain::show_result);
	connect(ui->pushButton_7, &QPushButton::clicked,
		this, &WinowMain::show_result);
	connect(ui->actionHelp, &QAction::triggered,
		this, [=] {show_win(WinHelp); });
	connect(ui->actionSet, &QAction::triggered,
		this, [=] {show_win(WinSet); });

}

// 打开新窗口函数
void WinowMain::show_win(QWidget* widget)
{
	widget->show();
	widget->raise();
}

// 页面切换函数
void WinowMain::stackedWidget_setCurrentIndex()
{
	pCurrentItem = ui->treeWidget->currentItem();
	strText = pCurrentItem->text(0);
	// qDebug() << "if之前" << strText;
	if (strText == "镀锌薄钢板" || strText == "镀锌圆钢")
	{
		if (strText == "镀锌薄钢板")
		{
			ui->label_4->setText("除税单价(元/m2)");
		}
		else
		{
			ui->label_4->setText("除税单价(元/m)");
		}
		ui->lineEdit_2->setText(rootObj["PriceKg"][strText].toString());
		ui->stackedWidget->setCurrentIndex(1);
		// qDebug() << strText;
	}
	else if (strText == "镀锌钢板" || strText == "铜板" || strText == "角钢")
	{
		if (strText == "角钢")
		{
			ui->label_13->setText("除税单价(元/m)");
		}
		else
		{
			ui->label_13->setText("除税单价(元/块)");
		}
		ui->lineEdit_7->setText(rootObj["PriceKg"][strText].toString());
		ui->stackedWidget->setCurrentIndex(2);
		// qDebug() << strText;
	}
	else if (strText == "槽钢")
	{
		ui->lineEdit_9->setText(rootObj["PriceKg"][strText].toString());
		ui->stackedWidget->setCurrentIndex(3);
	}
	else if (strText == "镀锌扁钢")
	{
		ui->lineEdit_14->setText(rootObj["PriceKg"][strText].toString());
		ui->stackedWidget->setCurrentIndex(4);
	}
	else if (strText == "镀锌钢管" || strText == "无缝钢管" || strText == "不锈钢管" || strText == "焊接钢管")
	{
		ui->lineEdit_19->setText(rootObj["PriceKg"][strText].toString());
		ui->stackedWidget->setCurrentIndex(5);
	}
	else if (strText == "桥架")
	{
		ui->stackedWidget->setCurrentIndex(6);
	}
	else if (strText == "抗震支架")
	{
		ui->stackedWidget->setCurrentIndex(7);
	}
	else if (strText == "风管防火阀" || strText == "风管排烟阀" || strText == "风管止回阀" || strText == "风管调节阀"
		|| strText == "风管插板（密闭）阀" || strText == "风口-单层" || strText == "风口-双层" || strText == "风口-排烟"
		|| strText == "风口-防火" || strText == "风口-防雨" || strText == "静压箱" || strText == "静压箱-消声"
		|| strText == "消声器ZP100" || strText == "消声弯头")
	{
		if (strText == "静压箱" || strText == "静压箱-消声" || strText == "消声器ZP100")
		{
			ui->lineEdit_28->setEnabled(true);
		}
		else
		{
			ui->lineEdit_28->setEnabled(false);
		}

		if (ui->radioButton->isChecked())
		{
			QString str_value = "镀锌钢板";
			ui->lineEdit_30->setText(rootObj["PriceKg"][str_value].toString());
		}
		else if (ui->radioButton_2->isChecked())
		{
			QString str_value = "铝合金";
			ui->lineEdit_30->setText(rootObj["PriceKg"][str_value].toString());
		}
		ui->stackedWidget->setCurrentIndex(8);
	}
	else
	{
		ui->stackedWidget->setCurrentIndex(0);
		// qDebug() << strText;
	}
}

void WinowMain::show_result()
{
	Calculate Cal;

	if (strText == "镀锌薄钢板" || strText == "镀锌圆钢")
	{
		Cal.a = ui->lineEdit->text().toDouble();
		Cal.d = ui->lineEdit_2->text().toDouble();
		Cal.xs = Cal.cal_xs();
		Cal.r = Cal.cal_r();
		QString str_xs = QString::number(Cal.xs, 'f', 3);
		QString str_r = QString::number(Cal.r, 'f', 2);
		ui->label_6->setText(str_xs);
		ui->lineEdit_3->setText(str_r);
	}
	else if (strText == "镀锌钢板" || strText == "铜板" || strText == "角钢")
	{
		Cal.a = ui->lineEdit_4->text().toDouble();
		Cal.b = ui->lineEdit_5->text().toDouble();
		Cal.c = ui->lineEdit_6->text().toDouble();
		Cal.d = ui->lineEdit_7->text().toDouble();
		Cal.xs = Cal.cal_xs();
		Cal.r = Cal.cal_r();
		QString str_xs = QString::number(Cal.xs, 'f', 3);
		QString str_r = QString::number(Cal.r, 'f', 2);
		ui->label_14->setText(str_xs);
		ui->lineEdit_8->setText(str_r);
	}
	else if (strText == "槽钢")
	{
		Cal.d = ui->lineEdit_9->text().toDouble();
		if (ui->comboBox->currentText() == "10#")
		{
			Cal.xs = 10.007;
		}

		Cal.r = Cal.cal_r();
		QString str_xs = QString::number(Cal.xs, 'f', 3);
		QString str_r = QString::number(Cal.r, 'f', 2);
		ui->label_15->setText(str_xs);
		ui->lineEdit_10->setText(str_r);
	}
	else if (strText == "镀锌扁钢")
	{
		Cal.a = ui->lineEdit_12->text().toDouble();
		Cal.b = ui->lineEdit_11->text().toDouble();
		Cal.d = ui->lineEdit_14->text().toDouble();
		Cal.xs = Cal.cal_xs();
		Cal.r = Cal.cal_r();
		QString str_xs = QString::number(Cal.xs, 'f', 3);
		QString str_r = QString::number(Cal.r, 'f', 2);
		ui->label_20->setText(str_xs);
		ui->lineEdit_13->setText(str_r);
	}
	else if (strText == "镀锌钢管" || strText == "无缝钢管" || strText == "不锈钢管" || strText == "焊接钢管")
	{
		// Cal.a = ui->lineEdit_16->text().toDouble();
		Cal.b = ui->lineEdit_15->text().toDouble();
		Cal.c = ui->lineEdit_18->text().toDouble();
		Cal.d = ui->lineEdit_19->text().toDouble();
		Cal.xs = Cal.cal_xs();
		Cal.r = Cal.cal_r();
		QString str_xs = QString::number(Cal.xs, 'f', 3);
		QString str_r = QString::number(Cal.r, 'f', 2);
		ui->label_27->setText(str_xs);
		ui->lineEdit_17->setText(str_r);
	}
	else if (strText == "桥架")
	{
		Cal.a = ui->lineEdit_20->text().toDouble();
		Cal.b = ui->lineEdit_21->text().toDouble();
		Cal.c = ui->lineEdit_22->text().toDouble();
		Cal.d = ui->lineEdit_23->text().toDouble();
		Cal.e = ui->lineEdit_24->text().toDouble();
		if (ui->checkBox->isChecked())
		{
			Cal.xs = (Cal.d + Cal.e) / (Cal.a + Cal.b);
		}
		else
		{
			Cal.xs = (Cal.d + Cal.e * 2) / (Cal.a + Cal.b * 2);
		}

		Cal.r = Cal.cal_r();
		QString str_r = QString::number(Cal.r, 'f', 2);
		ui->lineEdit_25->setText(str_r);
	}
	else if (strText == "风管防火阀" || strText == "风管排烟阀" || strText == "风管止回阀" || strText == "风管调节阀"
		|| strText == "风管插板（密闭）阀" || strText == "风口-单层" || strText == "风口-双层" || strText == "风口-排烟"
		|| strText == "风口-防火" || strText == "风口-防雨" || strText == "静压箱" || strText == "静压箱-消声"
		|| strText == "消声器ZP100" || strText == "消声弯头")
	{
		Cal.a = ui->lineEdit_26->text().toDouble();
		Cal.b = ui->lineEdit_27->text().toDouble();
		Cal.c = ui->lineEdit_28->text().toDouble();
		Cal.d = ui->lineEdit_30->text().toDouble();

		a1 = ui->radioButton->isChecked();
		a2 = ui->radioButton_2->isChecked();
		b1 = ui->radioButton_7->isChecked();
		b2 = ui->radioButton_8->isChecked();
		c1 = ui->radioButton_3->isChecked();
		c2 = ui->radioButton_4->isChecked();
		c3 = ui->radioButton_5->isChecked();
		c4 = ui->radioButton_6->isChecked();

		Cal.jz = Cal.cal_jz();
		Cal.xs = Cal.cal_xs();
		Cal.r = Cal.cal_r();

		QString str_r = QString::number(Cal.r, 'f', 2);
		ui->lineEdit_29->setText(str_r);
	}
}

// Calculate类
Calculate::Calculate()
{}

Calculate::~Calculate()
{}
// 计算基准价格函数
double Calculate::cal_jz()
{
	if (strText == "风管防火阀")
	{
		if (a * b / pow(10, 6) <= 1)
		{
			jz = a * b / pow(10, 6) * 1290 + 200;
		}
		else
		{
			jz = a * b / pow(10, 6) * 1110 + 230;
		}
	}
	else if (strText == "风管排烟阀")
	{
		if (a * b / pow(10, 6) <= 1)
		{
			jz = a * b / pow(10, 6) * 1350 + 385;
		}
		else
		{
			jz = a * b / pow(10, 6) * 1255 + 430;
		}
	}
	else if (strText == "风管止回阀")
	{
		jz = a * b / pow(10, 6) * 740 + 135;
	}
	else if (strText == "风管调节阀")
	{
		jz = a * b / pow(10, 6) * 355 + 55;
	}
	else if (strText == "风管插板（密闭）阀")
	{
		jz = (a + b) * 2 / 1000 * 240 * 0.6;
	}
	else if (strText == "风口-单层")
	{
		jz = a * b / pow(10, 6) * 485 + 60;
	}
	else if (strText == "风口-双层")
	{
		jz = a * b / pow(10, 6) * 540 + 75;
	}
	else if (strText == "风口-排烟")
	{
		jz = a / 1000 * (b / 1000 + 0.2) * 1695 + 575;
	}
	else if (strText == "风口-防火")
	{
		jz = a / 1000 * (b / 1000 + 0.2) * 790 + 520;
	}
	else if (strText == "风口-防雨")
	{
		jz = a * b / pow(10, 6) * 560 + 60;
	}
	else if (strText == "静压箱")
	{
		jz = (a + b) * 2 * c / pow(10, 6) * 46.66;
	}
	else if (strText == "静压箱-消声")
	{
		jz = (a * b + a * c + b * c) / pow(10, 6) * 2 * 395;
	}
	else if (strText == "消声器ZP100")
	{
		jz = (a * b + a * c + b * c) / pow(10, 6) * 2 * 655;
	}
	else if (strText == "消声弯头")
	{
		jz = (a * b + a * (a + 250) + b * (a + 250)) / pow(10, 6) * 2 * 200;
	}

	if (c1)
	{
		jz = jz;
	}
	else if (c2)
	{
		jz += 400;
	}
	else if (c3)
	{
		jz += 700;
	}
	else if (c4)
	{
		jz += 1000;
	}
	return jz;
}

// 计算系数函数
double Calculate::cal_xs()
{
	if (strText == "镀锌薄钢板")
	{
		xs = a / 1000 * FE;
	}
	else if (strText == "镀锌钢板")
	{
		xs = a * b * c * FE / pow(10, 9);
	}
	else if (strText == "铜板")
	{
		xs = a * b * c * CU / pow(10, 9);
	}
	else if (strText == "角钢")
	{
		xs = (c * (a + b - c)) * FE / pow(10, 6);
	}
	else if (strText == "镀锌圆钢")
	{
		xs = pow(a / 2 / 1000, 2) * 3.14 * 1 * FE;
	}
	else if (strText == "镀锌扁钢")
	{
		xs = a * b * 1000 * FE / pow(10, 9);
	}
	else if (strText == "镀锌钢管")
	{
		xs = (b - c) * c * 0.02466 * 1.06;
	}
	else if (strText == "无缝钢管" || strText == "焊接钢管")
	{
		xs = (b - c) * c * 0.02466;
	}
	else if (strText == "不锈钢管")
	{
		xs = (b - c) * c * 0.02491;
	}
	else if (strText == "风管防火阀" || strText == "风管排烟阀" || strText == "风管止回阀" || strText == "风管调节阀"
		|| strText == "风管插板（密闭）阀" || strText == "风口-单层" || strText == "风口-双层" || strText == "风口-排烟"
		|| strText == "风口-防火" || strText == "风口-防雨" || strText == "静压箱" || strText == "静压箱-消声"
		|| strText == "消声器ZP100" || strText == "消声弯头")
	{
		if (b1)
		{
			xs = 1;
		}
		else if (b2)
		{
			xs = 1.15;
		}
	}

	return xs;
}

// 计算结果函数
double Calculate::cal_r()
{
	if (strText == "桥架")
	{
		r = c * xs;
	}
	else if (strText == "风管防火阀" || strText == "风管排烟阀" || strText == "风管止回阀" || strText == "风管调节阀"
		|| strText == "风管插板（密闭）阀" || strText == "风口-单层" || strText == "风口-双层" || strText == "风口-排烟"
		|| strText == "风口-防火" || strText == "风口-防雨" || strText == "静压箱" || strText == "静压箱-消声"
		|| strText == "消声器ZP100" || strText == "消声弯头")
	{
		if (a1)
		{
			r = jz * (1 + 0.03 * (d - 6.2) / 0.3) * xs / 1.13;
		}
		else if (a2)
		{
			r = jz * (1 + 0.05 * (d - 22) / 1.5) * 0.45 * xs / 1.13;
		}
	}
	else
	{
		r = d * xs;
	}

	return r;
}