#ifndef CPP_DEMO_LAYER_MAINSCENE_H
#define CPP_DEMO_LAYER_MAINSCENE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"



class PageManager;
class MainScene : public SuperPage, public State<LogicDirector>
{
    friend PageManager;
public:
    CREATE_FUNC(MainScene);

    void loadUI() override;
    void unloadUI() override { removeAllChildrenWithCleanup(true); }

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

protected:
    MainScene();
    ~MainScene();
    void addQuitButton();
    void quitGame(cocos2d::CCObject *sender);

private:
    cocos2d::CCLayer        *backLayer_;
    cocos2d::CCLayer        *middleLayer_;
    cocos2d::CCLayer        *frontLayer_;
    StateMachine<MainScene> *stateMachine_;
};

MainScene* mainScene();

#endif