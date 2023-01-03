#include "WindowSet.h"

QString str_key;
int FE = 7850;
int CU = 8960;
QJsonObject rootObj;


WindowSet::WindowSet(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::WindowSetClass())
{
	ui->setupUi(this);
	init();
}

WindowSet::~WindowSet()
{
	delete pCurrentset;
	delete ui;
}

void WindowSet::init()
{	
	pCurrentset = new QTreeWidgetItem();
	ui->lineEdit->setEnabled(false);

	connect(ui->pushButton, &QPushButton::clicked,
		this, &WindowSet::save_json);
	connect(ui->lineEdit, &QLineEdit::textEdited,
		this, &WindowSet::change_json);
	connect(ui->treeWidget, &QTreeWidget::currentItemChanged,
		this, &WindowSet::lineEdit_set);

	QFileInfo fi("./config.json");
	if (!fi.isFile())
	{
		create_json();
	}
	read_json();
}

// 页面切换函数
void WindowSet::lineEdit_set()
{
	pCurrentset = ui->treeWidget->currentItem();
	str_key = pCurrentset->text(0);
	if (str_key == "密度设置(kg/m3)" || str_key == "除税单价设置(元/kg)")
	{
		ui->lineEdit->setEnabled(false);
	}
	else
	{
		ui->lineEdit->setEnabled(true);
		if (str_key == "铁" || str_key == "铜")
		{
			ui->lineEdit->setText(rootObj["constant"][str_key].toString());
		}
		else
		{
			ui->lineEdit->setText(rootObj["PriceKg"][str_key].toString());
		}
	}
}

void WindowSet::read_json()
{
	QFile file("./config.json");
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "can't open error!";
		return;
	}

	// 读取文件的全部内容
	QTextStream stream(&file);
	QString str = stream.readAll();
	file.close();
	// QJsonParseError类用于在JSON解析期间报告错误。
	QJsonParseError jsonError;
	// 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
	// 如果解析成功，返回QJsonDocument对象，否则返回null
	QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
	// 判断是否解析失败
	if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
		qDebug() << "Json格式错误！" << jsonError.error;
		return;
	}
	// 获取根 { }
	rootObj = doc.object();
}

void WindowSet::create_json()
{
	// 定义 { } 对象
	QJsonObject constant_obj;
	// 插入元素，对应键值对
	constant_obj.insert("铁", "7850");
	constant_obj.insert("铜", "8960");
	QJsonObject PriceKg_obj;
	PriceKg_obj.insert("镀锌薄钢板", "4.64");
	PriceKg_obj.insert("镀锌钢板", "4.16");
	PriceKg_obj.insert("铜板", "43.55");
	PriceKg_obj.insert("角钢", "5.02");
	PriceKg_obj.insert("槽钢", "4.41");
	PriceKg_obj.insert("镀锌圆钢", "4.2");
	PriceKg_obj.insert("镀锌扁钢", "5.5");
	PriceKg_obj.insert("镀锌钢管", "5.03");
	PriceKg_obj.insert("无缝钢管", "5.01");
	PriceKg_obj.insert("不锈钢管", "27.5");
	PriceKg_obj.insert("焊接钢管", "4.4");
	PriceKg_obj.insert("铝合金", "22");
	// 定义根节点	也即是最外层 { }
	rootObj.insert("constant", constant_obj);
	rootObj.insert("PriceKg", PriceKg_obj);

	save_json();
}

// 改变配置文件函数
void WindowSet::change_json()
{
	QString str_value = ui->lineEdit->text();
	if (str_key == "铁" || str_key == "铜")
	{
		QJsonObject inter_Object = rootObj["constant"].toObject();
		inter_Object[str_key] = str_value;
		rootObj["constant"] = inter_Object;
		FE = str_value.toInt();
		CU = str_value.toInt();
	}
	else
	{
		QJsonObject inter_Object = rootObj["PriceKg"].toObject();
		inter_Object[str_key] = str_value;
		rootObj["PriceKg"] = inter_Object;
	}
}

void WindowSet::save_json()
{
	// 将json对象里的数据转换为字符串
	QJsonDocument doc;
	doc.setObject(rootObj);

	QFile file("./config.json");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		qDebug() << "can't open error!";
		return;
	}

	// 写入文件
	QTextStream stream(&file);
	stream << doc.toJson();
	file.close();
}