#include "WindowHelp.h"
#include <QDesktopServices>

WindowHelp::WindowHelp(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::WindowHelpClass())
{
	ui->setupUi(this);
	init();
}

WindowHelp::~WindowHelp()
{
	delete ui;
}

// 初始化init
void WindowHelp::init()
{
	connect(ui->commandLinkButton, &QPushButton::clicked,
		this, &WindowHelp::open_url);
}

// 打开网页函数
void WindowHelp::open_url()
{
	QDesktopServices::openUrl(QUrl("https://github.com/qhzgit734?tab=repositories"));
}

