#pragma once

#include "ui/icons_font_awesome.hpp"
#include <fluffy/scene/entity.hpp>
#include <fluffy/text/string.hpp>
#include <imgui.h>
#include <imgui_internal.h>

namespace Fluffy::Layout {

/////////////////////////////////////////////////////////////////////////////////////////////////
/// COLORS
/////////////////////////////////////////////////////////////////////////////////////////////////

static ImVec4 WhiteColor = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
static ImVec4 BlackColor = ImVec4(0.10f, 0.08f, 0.12f, 1.00f);

static ImVec4 RedColor      = ImVec4{ 0.88f, 0.39f, 0.40f, 1.f };
static ImVec4 DarkRedColor  = ImVec4{ 0.69f, 0.23f, 0.35f, 1.f };
static ImVec4 LightRedColor = ImVec4{ 0.95f, 0.58f, 0.50f, 1.f };

static ImVec4 GreenColor      = ImVec4{ 0.51f, 0.58f, 0.28f, 1.f };
static ImVec4 DarkGreenColor  = ImVec4{ 0.27f, 0.44f, 0.18f, 1.f };
static ImVec4 LightGreenColor = ImVec4{ 0.65f, 0.69f, 0.31f, 1.f };

static ImVec4 BlueColor      = ImVec4{ 0.25f, 0.32f, 0.45f, 1.f };
static ImVec4 DarkBlueColor  = ImVec4{ 0.19f, 0.22f, 0.26f, 1.f };
static ImVec4 LightBlueColor = ImVec4{ 0.42f, 0.51f, 0.63f, 1.f };

static ImVec4 YellowColor      = ImVec4{ 0.79f, 0.6f, 0.20f, 1.f };
static ImVec4 DarkYellowColor  = ImVec4{ 0.72f, 0.42f, 0.12f, 1.f };
static ImVec4 LightYellowColor = ImVec4{ 0.8f, 0.71f, 0.43f, 1.f };

static ImVec4 GrayColor      = ImVec4{ 0.43f, 0.46f, 0.48f, 1.f };
static ImVec4 DarkGrayColor  = ImVec4{ 0.22f, 0.23f, 0.26f, 1.f };
static ImVec4 LightGrayColor = ImVec4{ 0.70f, 0.74f, 0.71f, 1.f };

/////////////////////////////////////////////////////////////////////////////////////////////////
/// WIDGETS
/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline void drawComponent(Entity entity, const String& title, const std::function<void(Entity)>& contents)
{
    if (!entity.has<T>()) {
        return;
    }

    ImGuiIO& io                     = ImGui::GetIO();
    auto     boldFont               = io.Fonts->Fonts[1];
    ImVec2   contentRegionAvailable = ImGui::GetContentRegionAvail();
    auto     flags                  = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
    ImGui::Separator();

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImGui::PushFont(boldFont);
    bool  open       = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, "%s", title.c_str());
    ImGui::PopFont();
    ImGui::PopStyleVar();
    ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);

    if (ImGui::Button(ICON_FA_COG, ImVec2{ lineHeight, lineHeight })) {
        ImGui::OpenPopup("ComponentSettings");
    }

    bool removeComponent = false;
    if (ImGui::BeginPopup("ComponentSettings")) {
        if (ImGui::MenuItem(ICON_FA_TRASH "  Remove component")) {
            removeComponent = true;
        }

        ImGui::EndPopup();
    }

    if (open) {
        contents(entity);
        ImGui::Dummy(ImVec2(0, 10.f));
        ImGui::TreePop();
    }

    if (removeComponent) {
        entity.remove<T>();
    }
}

inline void drawXYZ(const String& label, Vector3f& values, float reset = 0.f, float step = 1.f)
{
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);

    ImGui::SetColumnWidth(0, 100.f);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    float  lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
    ImVec2 buttonSize = { lineHeight + 3.f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, DarkRedColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, RedColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, DarkRedColor);
    if (ImGui::Button("X", buttonSize)) {
        values.x = reset;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, step, 0.f, 0.f, "%.1f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, GreenColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, LightGreenColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, GreenColor);
    if (ImGui::Button("Y", buttonSize)) {
        values.y = reset;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, step, 0.f, 0.f, "%.1f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, BlueColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, LightBlueColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, BlueColor);
    if (ImGui::Button("Z", buttonSize)) {
        values.z = reset;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, step, 0.f, 0.f, "%.1f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::Columns(1);

    ImGui::PopID();
}

inline bool drawColorPicker(const String& label, Vector4f& values)
{
    bool modified = false;
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);

    ImGui::SetColumnWidth(0, 100.f);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    if (ImGui::ColorEdit4(label.c_str(), glm::value_ptr(values), ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs)) {
        modified = true;
    }
    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();

    return modified;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////

}