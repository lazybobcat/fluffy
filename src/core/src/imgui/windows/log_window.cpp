#include <fluffy/imgui/windows/log_window.hpp>

using namespace Fluffy;

LogWindowSink::LogWindowSink(LogWindow* window)
  : mWindow(window)
{
    setLevel(LogLevel::Debug);
}

void LogWindowSink::log(LogLevel level, const String& message)
{
    std::ostringstream os;
    os << "[" << currentDateTime() << "] [" << level << "] " << message << '\n';
    mWindow->log(os.str());
}

/**********************************************************************************************************************/

LogWindow::LogWindow(const ImGuiWindowDefinition& properties)
  : ImGuiWindow({ properties.title, properties.openControl, properties.flags })
{
    Logger::addSink(new LogWindowSink(this));
}

void LogWindow::log(const String& message)
{
    FLUFFY_PROFILE_FUNCTION();

    int old_size = mBuffer.size();
    mBuffer.append(message.c_str());
    for (int new_size = mBuffer.size(); old_size < new_size; old_size++) {
        if (mBuffer[old_size] == '\n') {
            mLineOffsets.push_back(old_size + 1);
        }
    }
}

void LogWindow::clear()
{
    mBuffer.clear();
    mLineOffsets.clear();
    mLineOffsets.push_back(0);
}

void LogWindow::customRender()
{
    FLUFFY_PROFILE_FUNCTION();

    mFilter.Draw("Filter");

    ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    if (mCopy) {
        ImGui::LogToClipboard();
        mCopy = false;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    const char* buf     = mBuffer.begin();
    const char* buf_end = mBuffer.end();

    if (mFilter.IsActive()) {
        for (int line_no = 0; line_no < mLineOffsets.Size; line_no++) {
            const char* line_start = buf + mLineOffsets[line_no];
            const char* line_end   = (line_no + 1 < mLineOffsets.Size) ? (buf + mLineOffsets[line_no + 1] - 1) : buf_end;
            if (mFilter.PassFilter(line_start, line_end)) {
                ImGui::TextUnformatted(line_start, line_end);
            }
        }
    } else {
        ImGuiListClipper clipper;
        clipper.Begin(mLineOffsets.size());
        while (clipper.Step()) {
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++) {
                const char* line_start = buf + mLineOffsets[line_no];
                const char* line_end   = (line_no + 1 < mLineOffsets.Size) ? (buf + mLineOffsets[line_no + 1] - 1) : buf_end;
                ImGui::TextUnformatted(line_start, line_end);
            }
        }
        clipper.End();
    }

    ImGui::PopStyleVar();

    if (mAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }

    renderContextMenu();

    ImGui::EndChild();
}

void LogWindow::renderContextMenu()
{
    if (ImGui::BeginPopupContextWindow()) {
        ImGui::MenuItem("Enable auto-scroll", nullptr, &mAutoScroll);
        ImGui::Separator();
        if (ImGui::MenuItem("Copy")) {
            mCopy = true;
        }
        if (ImGui::MenuItem("Clear")) {
            clear();
        }
        ImGui::EndPopup();
    }
}
