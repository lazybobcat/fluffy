#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_panel.hpp>
#include <fluffy/profiling/profiler.hpp>

namespace Fluffy {

class LogWindow;

class LogWindowSink : public BaseLoggerSink
{
public:
    explicit LogWindowSink(LogWindow* window);

    void log(LogLevel level, const String& message) override;

private:
    LogWindow* mWindow;
};

class LogWindow : public ImGuiPanel
{
public:
    explicit LogWindow(const ImGuiPanelDefinition& properties);

    void log(const String& message);
    void clear();

protected:
    void customRender(RenderContext& context) override;

private:
    void renderContextMenu();

private:
    ImGuiTextBuffer        mBuffer;
    ImGuiTextFilter        mFilter;
    ImVector<unsigned int> mLineOffsets;
    bool                   mAutoScroll = true;
    bool                   mCopy       = false;
};
}
