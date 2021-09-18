#include "viewport_window.hpp"
#include <fluffy/input/input.hpp>
#include <fluffy/scene/components.hpp>
#include <imgui_internal.h>
#include <opengl_texture.hpp>

using namespace Fluffy;

constexpr float iconSize    = 32.f;
constexpr float textureSize = 320.f;

ViewportWindow::ViewportWindow(const ImGuiPanelDefinition& properties, Context& context)
  : ImGuiPanel(properties)
  , mContext(context)
  , mCamera(45.f, 1920.f / 1080.f, 0.1f, 1000000.f)
{
    mRenderTexture = Texture2D::create(1920, 1080);
    mRenderTarget  = mContext.video->createTextureRenderTarget();
    mRenderTarget->setTarget(mRenderTexture);

    // Icons
    mPlayIcon            = Texture2D::create("assets/textures/icons.png", { 0, 0, 32, 32 });
    mStopIcon            = Texture2D::create("assets/textures/icons.png", { 32, 0, 32, 32 });
    mCameraResetIcon     = Texture2D::create("assets/textures/icons.png", { 128, 0, 32, 32 });
    mCameraPointToIcon   = Texture2D::create("assets/textures/icons.png", { 160, 0, 32, 32 });
    mGuizmoTranslateIcon = Texture2D::create("assets/textures/icons.png", { 0, 32, 32, 32 });
    mGuizmoScaleIcon     = Texture2D::create("assets/textures/icons.png", { 32, 32, 32, 32 });
    mGuizmoRotateIcon    = Texture2D::create("assets/textures/icons.png", { 64, 32, 32, 32 });
}

void ViewportWindow::onEvent(Event& event)
{
    if (Event::KeyPressed == event.type) {
        switch (event.key.code) {
            case Keyboard::Key::T:
                changeGuizmo(ViewportGuizmo::Translate);
                break;

            case Keyboard::Key::R:
                changeGuizmo(ViewportGuizmo::Rotate);
                break;

            case Keyboard::Key::S:
                changeGuizmo(ViewportGuizmo::Scale);
                break;

            default:
                break;
        }
    }

    if (mViewportFocused && !isPlaying()) {
        mCamera.onEvent(event);
    }
}

void ViewportWindow::update(Time dt)
{
    if (mViewportFocused && !isPlaying()) {
        mCamera.onUpdate(dt);
    }
}

void ViewportWindow::play()
{
    if (mSceneState == SceneState::Edit) {
        mSceneState = SceneState::Play;
        OnPlay.emit();
        OnViewportResized.emit(mViewportSize);
    } else {
        mSceneState = SceneState::Edit;
    }
}

void ViewportWindow::customRender(RenderContext& context)
{
    UI_Toolbar();

    // Handle viewport / size
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (mViewportSize != Vector2f(viewportPanelSize.x, viewportPanelSize.y) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0) {
        mViewportSize = Vector2f(viewportPanelSize.x, viewportPanelSize.y);
        mCamera.setTargetSize(mViewportSize);
        OnViewportResized.emit(mViewportSize);
    }

    // Handle focus
    bool focused = ImGui::IsWindowFocused();
    if (focused != mViewportFocused) {
        focused ? OnFocusGained.emit() : OnFocusLost.emit();

        mViewportFocused = focused;
    }

    // Draw scene
    ImGui::Image((void*)dynamic_cast<OpenglTexture2D&>(*mRenderTexture).getRendererId(), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

    // Draw guizmos
    if (mSelectedEntity && mSelectedEntity.has<TransformComponent>() && SceneState::Edit == mSceneState) {
        ImGuizmo::SetOrthographic(mCamera.getType() == Camera::CameraType::Orthographic ? true : false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

        // Camera
        auto cameraView       = mCamera.getViewMatrix();
        auto cameraProjection = mCamera.getProjectionMatrix();

        // Entity
        auto& Ctransform = mSelectedEntity.get<TransformComponent>();
        auto  transform  = Ctransform.getTransformMatrix();
        transform        = glm::translate(transform, Ctransform.getOrigin());

        // Snap
        float snapValues[3] = { 0.1f, 0.1f, 0.1f };
        if (Input::isKeyPressed(Keyboard::Key::LeftControl)) {
            snapValues[0] = snapValues[1] = snapValues[2] = (ViewportGuizmo::Rotate == mGuizmo) ? 45.f : 1.f;
        }

        // Guizmo
        ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)mGuizmo, ImGuizmo::WORLD, glm::value_ptr(transform), nullptr, snapValues);
        if (ImGuizmo::IsUsing()) {
            float matrixTranslation[3], matrixRotation[3], matrixScale[3];
            ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), matrixTranslation, matrixRotation, matrixScale);

            if (ViewportGuizmo::Rotate == mGuizmo) {
                Ctransform.setRotation({ matrixRotation[0], matrixRotation[1], matrixRotation[2] });
            } else if (ViewportGuizmo::Translate == mGuizmo) {
                Ctransform.setPosition({ matrixTranslation[0], matrixTranslation[1], matrixTranslation[2] });
            } else {
                Ctransform.setScale({ matrixScale[0], matrixScale[1], matrixScale[2] });
            }
        }
    }
}

void ViewportWindow::begin()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGuiPanel::begin();
    ImGuizmo::BeginFrame();
}

void ViewportWindow::end()
{
    ImGuiPanel::end();
    ImGui::PopStyleVar();
}

void ViewportWindow::UI_Toolbar()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 32));
    ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    auto window = ImGui::GetCurrentWindow();
    window->DC.LayoutType = ImGuiLayoutType_Horizontal;

    constexpr float size = iconSize;

    // Current Transformation Icon
    {
        auto icon = (mGuizmo == ViewportGuizmo::Translate) ? mGuizmoTranslateIcon : (mGuizmo == ViewportGuizmo::Rotate ? mGuizmoRotateIcon : mGuizmoScaleIcon);
        if (ImGui::ImageButton((void*)dynamic_cast<OpenglTexture2D&>(*icon).getRendererId(), ImVec2(size, size), { 0, 0 }, { 1, 1 }, 0)) {
            switch (mGuizmo) {
                case Translate:
                    changeGuizmo(Rotate);
                    break;

                case Rotate:
                    changeGuizmo(Scale);
                    break;

                case Scale:
                    changeGuizmo(Translate);
                    break;
            }
        }
    }

    ImGui::Separator();

    // Camera buttons
    {
        if (ImGui::ImageButton((void*)dynamic_cast<OpenglTexture2D&>(*mCameraResetIcon).getRendererId(), ImVec2(size, size), { 0, 0 }, { 1, 1 }, 0)) {
            mCamera.resetRotation();
        }

        if (mSelectedEntity && mSelectedEntity.has<TransformComponent>()) {
            if (ImGui::ImageButton((void*)dynamic_cast<OpenglTexture2D&>(*mCameraPointToIcon).getRendererId(), ImVec2(size, size), { 0, 0 }, { 1, 1 }, 0)) {
                auto& Ctransform = mSelectedEntity.get<TransformComponent>();
                mCamera.setLookAt(Ctransform.getPosition());
            }
        }
    }

    ImGui::Separator();

    // Play & Stop buttons
    {
        auto icon = mSceneState == SceneState::Edit ? mPlayIcon : mStopIcon;
        if (ImGui::ImageButton((void*)dynamic_cast<OpenglTexture2D&>(*icon).getRendererId(), ImVec2(size, size), { 0, 0 }, { 1, 1 }, 0)) {
            play();
        }
    }

    ImGui::End();
    ImGui::PopStyleVar(3);
}

void ViewportWindow::onEntitySelected(Entity entity)
{
    mSelectedEntity = entity;
}

void ViewportWindow::onEntityUnselected()
{
    mSelectedEntity = Entity::INVALID;
}

void ViewportWindow::changeGuizmo(ViewportGuizmo guizmo)
{
    mGuizmo = guizmo;
}
