#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/graphics/render_target.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/imgui/imgui_panel.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <fluffy/signal/signal.hpp>

namespace Fluffy {

class ViewportWindow : public ImGuiPanel
{
public:
    Signal<>         OnFocusGained;
    Signal<>         OnFocusLost;
    Signal<Painter&> OnRender;

public:
    ViewportWindow(const ImGuiPanelDefinition& properties, Context& context);

    void update(Time dt) override;
    void onEvent(Event& event) override;

protected:
    void customRender(RenderContext& context) override;
    void begin() override;
    void end() override;

private:
    Context&                    mContext;
    Camera                      mCamera;
    Ref<Texture2D>              mRenderTexture;
    Unique<TextureRenderTarget> mRenderTarget;
    Vector2f                    mViewportSize    = { 1280.f, 720.f };
    bool                        mViewportFocused = false;
};
}