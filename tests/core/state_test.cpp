#include <bandit/bandit.h>
#include <fluffy/layer/layer.hpp>
#include <fluffy/layer/layer_stack.hpp>

using namespace bandit;
using namespace snowhouse;

class TestState : public Fluffy::Layer<TestState>
{
public:
    void fixUpdate(Time dt) override
    {
    }
    void render(RenderContext& context) override
    {
    }
    void onEvent(Event& event) override
    {
    }
};

// @todo more tests here

go_bandit([]() {
    describe("State", [&]() {
        Ref<Context> context = CreateRef<Context>();
        LayerStack   layerStack(context);

        describe("LayerStack", [&]() {
            it("should be empty at initialization", [&]() {
                AssertThat(layerStack.isEmpty(), Equals(true));
                AssertThat(layerStack.pendingListSize(), Equals(static_cast<unsigned int>(0)));
            });

            it("should add pending change when state is pushed", [&]() {
                Ref<BaseLayer> layer = CreateRef<TestState>();
                layerStack.push(layer);

                AssertThat(layerStack.isEmpty(), Equals(true));
                AssertThat(layerStack.pendingListSize(), Equals(static_cast<unsigned int>(1)));
            });
        });
    });
});