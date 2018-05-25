#ifndef SETTINGCONFIG_H
#define SETTINGCONFIG_H
 
#include <QString>
#include <QSettings>
class Setting
{
public:
    static Setting *getInstance();
    QSettings *getSetting() { return m_settings; }
    void save();
private:
    static Setting *s_setting;
    QSettings *m_settings;
	Setting();
	~Setting();
};

#endif
