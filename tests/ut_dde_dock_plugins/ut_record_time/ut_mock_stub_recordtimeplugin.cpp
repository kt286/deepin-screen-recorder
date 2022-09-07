// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QWidget>
#include <gtest/gtest.h>
#include "ut_mock_pluginproxyinterface.h"

#define protected public
#define private public
#include "../../../src/dde-dock-plugins/recordtime/recordtimeplugin.h"

namespace  {
class TestRecordTimePlugin : public testing::Test
{
public:

    void SetUp() override
    {
        m_recordTimePlugin.reset(new RecordTimePlugin());
        m_recordTimePlugin->init(&mock_proxy);

    }
    void TearDown() override
    {
    }

public:
    MockPluginProxyInterface mock_proxy;
    std::shared_ptr<RecordTimePlugin> m_recordTimePlugin;
};
}

static const QString PLUGIN_NAME = QString("deepin-screen-recorder-plugin");
static const QString PLUGIN_DISPLAY_NAME = QString("deepin-screen-recorder");

TEST_F(TestRecordTimePlugin, pluginName)
{
    EXPECT_EQ(PLUGIN_NAME, m_recordTimePlugin->pluginName());
}

TEST_F(TestRecordTimePlugin, pluginIsDisable)
{
    m_recordTimePlugin->pluginIsDisable();
}

TEST_F(TestRecordTimePlugin, pluginStateSwitched)
{
    m_recordTimePlugin->pluginStateSwitched();
}

TEST_F(TestRecordTimePlugin, pluginDisplayName)
{
    EXPECT_EQ(PLUGIN_DISPLAY_NAME, m_recordTimePlugin->pluginDisplayName());
}

TEST_F(TestRecordTimePlugin, pluginIsAllowDisable)
{
    EXPECT_EQ(true, m_recordTimePlugin->pluginIsAllowDisable());
}

TEST_F(TestRecordTimePlugin, itemWidget)
{
    m_recordTimePlugin->m_timeWidget = new TimeWidget();
    EXPECT_TRUE(nullptr != m_recordTimePlugin->itemWidget("dummy"));
    m_recordTimePlugin->clear();

}

TEST_F(TestRecordTimePlugin, onStart)
{
    emit m_recordTimePlugin->m_dBusService->start();
    m_recordTimePlugin->clear();
}

TEST_F(TestRecordTimePlugin, onStop)
{
    m_recordTimePlugin->m_checkTimer = new QTimer();
    m_recordTimePlugin->m_timer = new QTimer();
    m_recordTimePlugin->m_timeWidget = new TimeWidget();
    emit m_recordTimePlugin->m_dBusService->stop();
    m_recordTimePlugin->clear();
}

TEST_F(TestRecordTimePlugin, refresh)
{
    m_recordTimePlugin->m_checkTimer = new QTimer();
    m_recordTimePlugin->m_timer = new QTimer();
    m_recordTimePlugin->m_timeWidget = new TimeWidget();
    m_recordTimePlugin->refresh();
    m_recordTimePlugin->clear();

}

TEST_F(TestRecordTimePlugin, onRecording)
{
    m_recordTimePlugin->m_timer = new QTimer();
    m_recordTimePlugin->m_timeWidget = new TimeWidget();
    m_recordTimePlugin->m_bshow = true;
    m_recordTimePlugin->m_dBusService->recording();
    m_recordTimePlugin->clear();
}

TEST_F(TestRecordTimePlugin, onPause)
{
    m_recordTimePlugin->m_checkTimer = new QTimer();
    m_recordTimePlugin->m_timer = new QTimer();
    m_recordTimePlugin->m_timeWidget = new TimeWidget();
    m_recordTimePlugin->m_bshow = true;
    m_recordTimePlugin->m_dBusService->pause();
    m_recordTimePlugin->clear();

}
//TEST_F(TestRecordTimePlugin, onStopTimes)
//{
//    m_recordTimePlugin->m_checkTimer = new QTimer();
//    emit m_recordTimePlugin->m_dBusService->stop();
//    //连续点击，触发停止信号
//    emit m_recordTimePlugin->m_dBusService->stop();
//    EXPECT_EQ(nullptr, m_recordTimePlugin->m_checkTimer);
//}
