#include "settingconfig.h"
#include <QtWidgets/QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>
#include "defaultsetting.h"
#include <QFile>
Setting *Setting::s_setting = nullptr;

Setting::Setting()
{
    resetSetting();
}

Setting::~Setting() {
	if (m_settings)
	{
		delete m_settings;
	}
    if (s_setting)
    {
        delete s_setting;
        s_setting = nullptr;
    }
}

Setting *Setting::getInstance()
{
    if (s_setting == nullptr)
		s_setting = new Setting;

    return s_setting;
}

void Setting::save()
{
	
}

void  Setting::resetSetting()
{
    if (m_settings)
    {
        delete m_settings;
        m_settings = nullptr;
    }
    QString CurPath = QCoreApplication::applicationDirPath();
    QString configINIFilePath = CurPath + "//config.ini";
    
    m_settings = new QSettings(configINIFilePath, QSettings::IniFormat);
    m_settings->setIniCodec("UTF-8"); // �� ini ֧������
    QStringList defineKeys;
    for (auto i : defaultSetting::settings)
    {
        QString key = QString("basic/") + i[0];
        defineKeys.push_back(key);
        if (!m_settings->contains(key))
            m_settings->setValue(key, i[1]);
    }
}