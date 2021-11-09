/*
* Copyright (C) 2011 ~ 2021 Uniontech Software Technology Co.,Ltd
*
* Author:      wangchao <wangchao@uniontech.com>
* Maintainer:  wangchao <wangchao@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SYSTEMPROTECTIONSETTING_H
#define SYSTEMPROTECTIONSETTING_H

#include "dsettingsdialog.h"
#include <qsettingbackend.h>

#include <QObject>
#include <DLineEdit>
#include <QDBusInterface>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE
DTK_USE_NAMESPACE

class SystemProtectionSetting : public QObject
{
    Q_OBJECT
public:
    explicit SystemProtectionSetting(QObject *parent = nullptr);
    virtual ~SystemProtectionSetting();

    /*!
     * 获取设置界面实例
     */
    static SystemProtectionSetting* instance();

    /*!
     * 获取设置界面实例
     */
    void setSettingDialog(DSettingsDialog *settingsDialog);
    /*!
     * 注册自定义样式DSetting Item , 监测开关Item
     */
    static QPair<QWidget*, QWidget*> createProtectionSwitchHandle(QObject *obj);
    /*!
     * 注册自定义样式DSetting Item , 监测Cpu/Memory占用率设置Item
     */
    static QPair<QWidget*, QWidget*> createAlarmUsgaeSettingHandle(QObject *obj);
    /*!
     * 注册自定义样式DSetting Item , 监测报警间隔设置Item
     */
    static QPair<QWidget*, QWidget*> createAlarmIntervalSettingHandle(QObject *obj);
    /*!
     * 注册自定义样式DSetting Item , 系统通知设置跳转Item
     */
    static QPair<QWidget*, QWidget*> createSettingLinkButtonHandle(QObject *obj);
    /*!
     * 获取DSetting指针
     */
    DSettings *getDSettingPointor();
    //!
    //! \brief setLastValidAlarm 如果上次设置值合法，当前输入值不合法，显示上次输入的合法值
    //! \param lineEdit 文本内容输入框 maxValue 阈值上界 minvalue 阈值下界 num 上次合法值
    //!
    static void setLastValidAlarm(DLineEdit *lineEdit,DTK_CORE_NAMESPACE::DSettingsOption *option,int maxValue,int minValue,int num);

    //!
    //! \brief lineEditChanged 文字输入框焦点改变及回车事件处理函数
    //! \param focus 焦点改变
    //! \param edit 文字输出框对象
    //! \param option dialog句柄
    //! \param maxValue 最大值
    //! \param minValue 最小值
    //!
    static void lineEditChanged(bool focus, DLineEdit *edit, DTK_CORE_NAMESPACE::DSettingsOption *option, int maxValue, int minValue);


private:
    //!
    //! \brief regularNumber 规范数字信息正确显示
    //! \param lineEdit 文本内容输入框
    //!
    void regularNumber(DLineEdit *lineEdit);

signals:

public slots:
    /*!
     * 系统通知Item Button Clicked处理槽函数
     */
    void onMessgaeSetting(QVariant value);
    /*!
     * 监测功能设置修改槽函数
     */
    void onSettingItemChanged(const QString &key, const QVariant &value);
    /*!
     * 更新数据后台，应对于外部修改配置文件，保持初始状态和配置文件一致
     */
    void onUpdateNewBackend();

private:
    Dtk::Core::QSettingBackend *mBackend;
    DSettings *mDsettings;
    QDBusInterface mDaemonInterface;
    //设置静态成员变量 ，保存上次合法设置的CPU、内存阈值以及通知间隔时间
    static int m_lastValidCPUValue ;
    static int m_lastValidMemoryValue ;
    static int m_lastValidInternalValue ;
};

#endif // SYSTEMPROTECTIONSETTING_H
