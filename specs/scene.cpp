//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 26/04/18.
//

int main(void)
{
    Scene myScene;
    GameObject object = myScene.createObject(); // Entity like handle
    object.component<TransformComponent>()->position.x = 100;
    object.assign<ScriptComponent>();

    GameObject child = myScene.createObject();

    object.attach(child);
    myScene.attach(object);
}