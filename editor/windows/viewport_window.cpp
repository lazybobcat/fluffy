#include "viewport_window.hpp"
#include <opengl_texture.hpp>
#include <utility>

using namespace Fluffy;

ViewportWindow::ViewportWindow(const ImGuiWindowDefinition& properties, Context& context)
  : ImGuiWindow(properties), mContext(context), mCameraController({ 1280, 720 })
{
    mRenderTexture = Texture2D::create(1280, 720);
    mRenderTarget  = mContext.video->createTextureRenderTarget();
    mRenderTarget->setTarget(mRenderTexture);
}

void ViewportWindow::onEvent(Event& event)
{
    if (mViewportFocused)
        mCameraController.onEvent(event);
}

void ViewportWindow::update(Time dt)
{
    if (mViewportFocused)
        mCameraController.update(dt);
}

void ViewportWindow::customRender(RenderContext& context)
{
    // render scene
    context.with(*mRenderTarget).with(mCameraController.getCamera()).bind([&](Painter& painter) {
        OnRender.emit(painter);
    });

    // Handle focus
    bool focused = ImGui::IsWindowFocused();
    if (focused != mViewportFocused) {
        focused ? OnFocusGained.emit() : OnFocusLost.emit();

        mViewportFocused = focused;
    }

    // Handle viewport / size
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (mViewportSize != Vector2f(viewportPanelSize.x, viewportPanelSize.y) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0) {
        mViewportSize = Vector2f(viewportPanelSize.x, viewportPanelSize.y);
        mCameraController.resize({(std::uint32_t)mViewportSize.x, (std::uint32_t)mViewportSize.y});
    }
    ImGui::Image((void*)dynamic_cast<OpenglTexture2D&>(*mRenderTexture).getRendererId(), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
}
