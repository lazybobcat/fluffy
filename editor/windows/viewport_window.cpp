#include "viewport_window.hpp"
#include <opengl_texture.hpp>

using namespace Fluffy;

ViewportWindow::ViewportWindow(const ImGuiWindowDefinition& properties, Context& context)
  : ImGuiWindow(properties)
  , mContext(context)
  , mCamera({ 0.f, 0.f }, { 1280, 720 }) //@todo change editor camera to a perspective camera?
{
    mRenderTexture = Texture2D::create(1280, 720);
    mRenderTarget  = mContext.video->createTextureRenderTarget();
    mRenderTarget->setTarget(mRenderTexture);
}

void ViewportWindow::onEvent(Event& event)
{
}

void ViewportWindow::update(Time dt)
{
    if (mViewportFocused) {
        // @todo camera movements
    }
}

void ViewportWindow::customRender(RenderContext& context)
{
    // Handle viewport / size
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (mViewportSize != Vector2f(viewportPanelSize.x, viewportPanelSize.y) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0) {
        mViewportSize = Vector2f(viewportPanelSize.x, viewportPanelSize.y);
        mCamera.setViewportSize(mViewportSize);
    }

    /**
     * There is an issue when we resize the main window without resizing the viewport window:
     * the viewport doesn't keep the proper aspect ratio and gets distorted (window gl viewport changes).
     * This line fixes it but it may not be the prettiest thing.
     */
    glViewport(0, 0, mRenderTexture->getSize().x, mRenderTexture->getSize().y);

    // render scene
    context.with(*mRenderTarget).with(mCamera).bind([&](Painter& painter) {
        OnRender.emit(painter);
    });

    // Handle focus
    bool focused = ImGui::IsWindowFocused();
    if (focused != mViewportFocused) {
        focused ? OnFocusGained.emit() : OnFocusLost.emit();

        mViewportFocused = focused;
    }

    // Draw scene
    ImGui::Image((void*)dynamic_cast<OpenglTexture2D&>(*mRenderTexture).getRendererId(), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
}
