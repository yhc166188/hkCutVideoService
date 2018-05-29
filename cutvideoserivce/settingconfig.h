#ifndef SETTINGCONFIG_H
#define SETTINGCONFIG_H
 
#include <QString>
#include <QSettings>
class Setting
{
public:
    static Setting *getInstance();
    QSettings *getSetting() { return m_settings; }
    void  resetSetting();
    void save();
private:
    static Setting *s_setting;
    QSettings *m_settings = nullptr;
	Setting();
	~Setting();
};

#endif
