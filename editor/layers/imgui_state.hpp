#pragma once

#include "ui/layout.hpp"
#include <fluffy/layer/layer.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <opengl.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class ImGuiState : public Layer<ImGuiState>
{
public:
    bool isShielding() const override
    {
        return false;
    }

    void initialize() override
    {
        FLUFFY_PROFILE_FUNCTION();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.ConfigWindowsResizeFromEdges = true;
        io.ConfigDockingWithShift       = true;
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding              = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        configureTheme();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)getContext()->video->getWindow()->getNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void terminate() override
    {
        FLUFFY_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void fixUpdate(Time dt) override
    {
        FLUFFY_PROFILE_FUNCTION();

        auto     definition = getContext()->video->getWindow()->getDefinition();
        ImGuiIO& io         = ImGui::GetIO();
        io.DeltaTime        = dt.seconds();
        io.DisplaySize      = { definition.width * 1.f, definition.height * 1.f };
    }

    void begin() override
    {
        FLUFFY_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void render(RenderContext& context) override
    {
        FLUFFY_PROFILE_FUNCTION();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    }

    void end() override
    {
        FLUFFY_PROFILE_FUNCTION();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = (GLFWwindow*)getContext()->video->getWindow()->getNativeWindow();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void onEvent(Event& event) override
    {
    }

    void configureTheme()
    {
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        auto& styles = ImGui::GetStyle();

        io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Regular.ttf", 15.f);
        // Icon font
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig         icons_config;
        icons_config.MergeMode  = true;
        icons_config.PixelSnapH = true;
        io.Fonts->AddFontFromFileTTF("assets/fonts/" FONT_ICON_FILE_NAME_FAS, 13.0f, &icons_config, icons_ranges);

        io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Bold.ttf", 15.f);

        ImVec4* colors = styles.Colors;

        // Text
        colors[ImGuiCol_Text] = Layout::WhiteColor;

        // Window
        colors[ImGuiCol_WindowBg]  = Layout::DarkGrayColor;
        colors[ImGuiCol_ChildBg]   = Layout::DarkGrayColor;
        colors[ImGuiCol_PopupBg]   = Layout::DarkGrayColor;
        colors[ImGuiCol_MenuBarBg] = Layout::DarkGrayColor;

        // Headers
        colors[ImGuiCol_Header]           = Layout::DarkBlueColor;
        colors[ImGuiCol_HeaderHovered]    = Layout::LightBlueColor;
        colors[ImGuiCol_HeaderActive]     = Layout::BlueColor;
        colors[ImGuiCol_TitleBg]          = Layout::DarkGrayColor;
        colors[ImGuiCol_TitleBgActive]    = Layout::DarkGrayColor;
        colors[ImGuiCol_TitleBgCollapsed] = Layout::DarkGrayColor;

        // Tabs
        colors[ImGuiCol_Tab]                = Layout::BlueColor;
        colors[ImGuiCol_TabHovered]         = Layout::LightBlueColor;
        colors[ImGuiCol_TabActive]          = Layout::LightBlueColor;
        colors[ImGuiCol_TabUnfocused]       = Layout::BlueColor;
        colors[ImGuiCol_TabUnfocusedActive] = Layout::BlueColor;

        // Fields
        colors[ImGuiCol_FrameBg]        = Layout::GrayColor;
        colors[ImGuiCol_FrameBgHovered] = Layout::LightGrayColor;
        colors[ImGuiCol_FrameBgActive]  = Layout::LightGrayColor;

        // Buttons
        colors[ImGuiCol_Button]        = Layout::BlueColor;
        colors[ImGuiCol_ButtonHovered] = Layout::LightBlueColor;
        colors[ImGuiCol_ButtonActive]  = Layout::DarkBlueColor;

        //        colors[ImGuiCol_Border]                = Layout::BlackColor;

        //        colors[ImGuiCol_PopupBg]               = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        //        colors[ImGuiCol_Border]                = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        //        colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        //        colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        //
        //        colors[ImGuiCol_TitleBg]               = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
        //        colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        //        colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        //        colors[ImGuiCol_MenuBarBg]             = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        //        colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        //        colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        //        colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        //        colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        //        colors[ImGuiCol_CheckMark]             = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        //        colors[ImGuiCol_SliderGrab]            = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        //        colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
        //        colors[ImGuiCol_Header]                = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        //        colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        //        colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        //        colors[ImGuiCol_Separator]             = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        //        colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        //        colors[ImGuiCol_SeparatorActive]       = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        //        colors[ImGuiCol_ResizeGrip]            = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        //        colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        //        colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        //        colors[ImGuiCol_Tab]                   = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        //        colors[ImGuiCol_TabHovered]            = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        //        colors[ImGuiCol_TabActive]             = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        //        colors[ImGuiCol_TabUnfocused]          = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        //        colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        //        colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        //        colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        //        colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        //        colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        //        colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        //        colors[ImGuiCol_DragDropTarget]        = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        //        colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        //        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        //        colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        //        colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }
};