#pragma once

#include "contrib/imguizmo/ImGuizmo.h"
#include "graphics/editor_camera.hpp"
#include <fluffy/definitions.hpp>
#include <fluffy/graphics/render_target.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/imgui/imgui_panel.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <fluffy/scene/entity.hpp>
#include <fluffy/signal/signal.hpp>

namespace Fluffy {

enum ViewportGuizmo
{
    Translate = ImGuizmo::TRANSLATE,
    Rotate    = ImGuizmo::ROTATE,
    Scale     = ImGuizmo::SCALE,
};

enum ViewportTool
{
    Selection,
    Move,
    Zoom,
};

class ViewportWindow : public ImGuiPanel
{
public:
    enum class SceneState
    {
        Edit = 0,
        Play = 1
    };

public:
    Signal<>         OnPlay;
    Signal<>         OnFocusGained;
    Signal<>         OnFocusLost;
    Signal<Vector2f> OnViewportResized;

    Ref<Slot> EntitySelectedSlot;
    Ref<Slot> EntityUnselectedSlot;

public:
    ViewportWindow(const ImGuiPanelDefinition& properties, Context& context);

    void update(Time dt) override;
    void onEvent(Event& event) override;

    void play();

    void onEntitySelected(Entity entity);
    void onEntityUnselected();

    const Vector2f& getViewportSize() const { return mViewportSize; }

    bool          isPlaying() const { return SceneState::Play == mSceneState; }
    EditorCamera& getCamera() { return mCamera; }

    TextureRenderTarget* getRenderTarget() const { return mRenderTarget.get(); }

protected:
    void customRender(RenderContext& context) override;
    void begin() override;
    void end() override;

    void changeGuizmo(ViewportGuizmo guizmo);

    void UI_Toolbar();

private:
    Context&     mContext;
    EditorCamera mCamera;

    SceneState                  mSceneState = SceneState::Edit;
    Ref<Texture2D>              mRenderTexture;
    Unique<TextureRenderTarget> mRenderTarget;
    Vector2f                    mViewportSize    = { 1280.f, 720.f };
    bool                        mViewportFocused = false;
    Entity                      mSelectedEntity  = Entity::INVALID;

    // Tools
    ViewportTool   mTool   = ViewportTool::Selection;
    ViewportGuizmo mGuizmo = ViewportGuizmo::Translate;

    // Icons
    Ref<Texture2D> mGuizmoTranslateIcon;
    Ref<Texture2D> mGuizmoRotateIcon;
    Ref<Texture2D> mGuizmoScaleIcon;
    Ref<Texture2D> mPlayIcon;
    Ref<Texture2D> mStopIcon;
    Ref<Texture2D> mCameraResetIcon;
    Ref<Texture2D> mCameraPointToIcon;
};
}